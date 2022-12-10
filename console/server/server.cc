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
#define PORT 7000
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
    trains.push_back(train(1, 1, 10, 10, 1, sizeof(stations)));
    trains.push_back(train(2, 3, 7, 5, 2, sizeof(stations)));
    trains.push_back(train(3, 1, 5, 3, 3, sizeof(stations)));
    trains.push_back(train(4, 5, 10, 3, 1, sizeof(stations)));
    trains.push_back(train(5, 10, 6, 3, 2, sizeof(stations)));
    trains.push_back(train(6, 7, 1, 10, 3, sizeof(stations)));
    trains.push_back(train(7, 10, 1, 5, 1, sizeof(stations)));
}

void init_ticket(int &ticket_num, std::vector<station>& stations, std::vector<train>& trains, std::vector<ticket>& tickets) {
    addTicket(ticket_num, 3,7, sizeof(stations), trains, tickets, stations);
    addTicket(ticket_num, 1,10, sizeof(stations), trains, tickets, stations);
    addTicket(ticket_num, 5,7, sizeof(stations), trains, tickets, stations);
    addTicket(ticket_num, 1,10, sizeof(stations), trains, tickets, stations);
    addTicket(ticket_num, 1,10, sizeof(stations), trains, tickets, stations);
    addTicket(ticket_num, 1,10, sizeof(stations), trains, tickets, stations);
}

int main() {
    // 初始化station、train、ticket
    std::vector<station> stations;
    std::vector<train> trains;
    std::vector<ticket> tickets;
    int ticket_num = 1;

    init_station(stations);
    init_train(trains, stations);
    init_ticket(ticket_num, stations, trains, tickets);

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
    while(1) {
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
                // 若buffer第一位为0.则退出循环
                switch (buffer[0]) {
                    case '0':
                        printf("客户端退出，服务端也退出\n");
                        break;
                    case '1':
                        printf("客户端购买车票\n");
                        break;
                    case '2':
                        printf("客户端退票\n");
                        break;
                    case '3':
                        printf("客户端余票查询\n");
                        break;
                    default:
                        printf("客户端输入错误\n");
                        break;
                }
                std::cout << buffer << std::endl;
                //send(conn, buffer, len , 0);把数据回发给客户端
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds)){
                char buf[1024];
                fgets(buf, sizeof(buf), stdin);
                //printf("you are send %s", buf);
                send(conn, buf, sizeof(buf), 0);
            }
        }
    }
    close(conn);
    close(ss);
    return 0;
}