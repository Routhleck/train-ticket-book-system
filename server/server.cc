#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#define PORT 7001
#define QUEUE 20

#include "include/ticket.h"
#include "include/ticketManage.h"
#include <vector>

// station init
void init_station(std::vector<station>& stations) {
    stations.push_back(station(1, "A", 0));
    stations.push_back(station(2, "B", 10));
    stations.push_back(station(3, "C", 20));
    stations.push_back(station(4, "D", 30));
    stations.push_back(station(5, "E", 40));
    stations.push_back(station(6, "F", 50));
    stations.push_back(station(7, "G", 60));
    stations.push_back(station(8, "H", 70));
    stations.push_back(station(9, "I", 80));
    stations.push_back(station(10, "J", 90));
}

// train init
void init_train(std::vector<train>& trains, std::vector<station>& stations) {
    trains.push_back(train(1, 1, 10, 10, 1));
    trains.push_back(train(2, 3, 7, 5, 2));
    trains.push_back(train(3, 1, 5, 3, 3));
    trains.push_back(train(4, 5, 10, 3, 1));
    trains.push_back(train(5, 10, 6, 3, 2));
    trains.push_back(train(6, 7, 1, 10, 3));
    trains.push_back(train(7, 10, 1, 5, 1));
}

void init_ticket(int &ticket_num, std::vector<ticket>& tickets, std::vector<train>& trains) {
    
    // 从ticket_data中读取数据
    FILE *fp = fopen("ticket_data", "r");
    fscanf(fp, "%d", &ticket_num);
    int ticket_id, train_id, user_id, ticket_start, ticket_end, ticket_price;
    while (fscanf(fp, "%d %d %d %d %d %d", &user_id, &ticket_id, &train_id, &ticket_start, &ticket_end, &ticket_price) != EOF) {
        tickets.push_back(ticket(ticket_id, train_id, user_id, ticket_start, ticket_end, ticket_price));
        // 为trains中get_train_id为train_id的train add_train_passenger_now
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].get_train_id() == train_id) {
                trains[i].add_train_passenger_now();
                break;
            }
        }
    }
}

void save_ticket(int ticket_num, std::vector<ticket> tickets) {
    // 数据保存到ticket_data中，第一行为ticket_num，后面每行为一张票的信息(车票id,车次id,出发站,到达站,车票价格)
    FILE *fp = fopen("ticket_data", "w");
    fprintf(fp, "%d\n", ticket_num);
    for (int i = 0; i < tickets.size(); i++) {
        fprintf(fp, "%d %d %d %d %d %d\n", tickets[i].get_user_id(), tickets[i].get_ticket_id(), tickets[i].get_train_id(), tickets[i].get_ticket_start(), tickets[i].get_ticket_end(), tickets[i].get_ticket_price());
    }
    fclose(fp);
}

// 根据空格分离字符串
void split_space(int *num, char *buffer) {
    char *p = strtok(buffer, " ");
    int i = 0;
    while (p != NULL) {
        num[i] = atoi(p);
        p = strtok(NULL, " ");
        i++;
    }
}

int main() {
    // 初始化station、train、ticket
    std::vector<station> stations;
    std::vector<train> trains;
    std::vector<ticket> tickets;
    int ticket_num = 1;

    init_station(stations);
    init_train(trains, stations);
    init_ticket(ticket_num, tickets, trains);

    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;     //选择器


    /*创建socket*/
    int ss = socket(AF_INET, SOCK_STREAM, 0);   //AF_INET   IPV4   ;SOCK_STREAM   TCP
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*bind*/
    if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1) {
        perror("bind");
        exit(1);
    }
    /*listen*/
    if(listen(ss, QUEUE) == -1) {
        perror("listen");
        exit(1);
    }
    /*connect*/
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    ///成功返回非负描述字，出错返回-1
    int conn = accept(ss, (struct sockaddr*)&client_addr, &length);   //目测需要客户端部分的addr
    if( conn < 0 ) {
        perror("connect");
        exit(1);
    }
    std::cout << "connect success!" << std::endl;
    bool exit_flag = false;
    while(1) {
        if (exit_flag) break;
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(conn, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/
        if(maxfd < conn)
            maxfd = conn;
        /*设置超时时间*/
        tv.tv_sec = 500;
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1){
            printf("select出错，客户端程序退出\n");
            break;
        }else if(retval == 0){
            // printf("服务端没有任何输入信息，并且客户端也没有信息到来，waiting...\n");
            continue;
        }else{
            /*客户端发来了消息*/
            if(FD_ISSET(conn,&rfds)){
                char buffer[1024];
                // memset(buffer, 0 ,sizeof(buffer));
                int len = recv(conn, buffer, sizeof(buffer), 0);
                std::cout << buffer << std::endl;
                // 若buffer第一位为0.则退出循环
                switch (buffer[0]) {
                    case '0':
                        printf("客户端退出，服务端也退出\n");
                        exit_flag = true;
                        break;
                    case '1':
                    {
                        printf("客户端购买车票\n");
                        // 将buffer按空格拆分为int数组
                        int num[4];
                        split_space(num,buffer);
                        bool ifAdd = addTicket(num[1], ticket_num, num[2],num[3], trains, tickets, stations);
                        // 将tickets保存到ticket_data文件中
                        save_ticket(ticket_num, tickets);

                        // 返回购买的车票信息(车票id,车次id,出发站,到达站,车票价格)
                        char buffer[1024];
                        if (ifAdd == true) sprintf(buffer, "购票成功\n车票id: %d\t车票车次id: %d\t车票始发站id:%d\t车票终点站id:%d\t车票价格:%d\n", tickets[tickets.size() - 1].get_ticket_id(), tickets[tickets.size() - 1].get_train_id(), tickets[tickets.size() - 1].get_ticket_start(), tickets[tickets.size() - 1].get_ticket_end(), tickets[tickets.size() - 1].get_ticket_price());
                        else sprintf(buffer, "购票失败，没有符合的车票");
                        send(conn, buffer, sizeof(buffer), 0);
                        break;
                    }
                    case '2':
                    {
                        printf("客户端退票\n");
                        // 将buffer按空格拆分为int数组
                        int num2[3];
                        split_space(num2, buffer);
                        bool ifDelete = deleteTicket(num2[1], num2[2], tickets, trains);
                        char buffer2[1024];
                        if (ifDelete == true) sprintf(buffer2, "退票成功\n");
                        else sprintf(buffer2, "退票失败\n");
                        send(conn, buffer2, sizeof(buffer2), 0);
                        save_ticket(ticket_num, tickets);
                        break;
                    }
                    case '3':
                    {
                        printf("客户端余票查询\n");
                        char buffer3[1024] = "";
                        checkRestTicket(buffer3, trains);
                        send(conn, buffer3, sizeof(buffer3), 0);
                        break;
                    }
                    case '4':
                    {
                        int num4[2];
                        split_space(num4, buffer);
                        printf("客户端用户已购票查询");
                        char buffer4[1024] = "";
                        checkBuyTicket(num4[1], buffer4, tickets);
                        send(conn, buffer4, sizeof(buffer4), 0);
                        break;
                    }
                    default:
                    {
                        printf("客户端输入错误\n");
                        break;
                    }
                }
                
                //send(conn, buffer, len , 0);把数据回发给客户端
            }
        }
    }
    close(conn);
    close(ss);
    return 0;
}