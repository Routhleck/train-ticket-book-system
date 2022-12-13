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
#include <string.h>
#include <time.h>

#define MYPORT  7000
#define BUFFER_SIZE 1024


int main()
{
    // 用户id初始化
    int user_id = 0;
    std::cout << "请输入用户id: ";
    std::cin >> user_id;
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
    int command = 0;
    char data[30];
    

    ///定义sockfd
    sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip

    //连接服务器，成功返回0，错误返回-1
    while (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    bool input = true;
    bool exit_flag = false;
    int exit_time = 2;
    while(1){
        if (exit_flag == true) {
            std::cout << "退出" << std::endl;
            break;
            
        }
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(sock_cli, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/
        if(maxfd < sock_cli)
            maxfd = sock_cli;
        /*设置超时时间*/
        tv.tv_sec = 500;
        tv.tv_usec = 0;
        /*等待聊天*/
        if (input == true) std::cout << "请输入操作：\n 1:订票  2:退票  3:余票查询  4:购票查询  5:站点查询  0:退出客户端" << std::endl;
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1){
            printf("select出错，客户端程序退出\n");
            break;
        }else if(retval == 0){
            // printf("客户端没有任何输入信息，并且服务器也没有信息到来，waiting...\n");
            continue;
        }else{
            /*服务器发来了消息*/
            if(FD_ISSET(sock_cli,&rfds)){
                char recvbuf[BUFFER_SIZE];
                int len;
                len = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
                printf("%s", recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
                input = true;
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds)){
                bool flag = true;
                std::cin >> command;
                // 忽略回车
                std::cin.ignore();
                switch (command) {
                case 0:
                    exit_flag = true;
                    break;
                case 1:
                    std::cout << "请输入订票信息，格式为(出发站点id 到达站点id)" << std::endl;
                    // 获取输入的字符串
                    std::cin.getline(data, 30);
                    break;
                case 2:
                    std::cout << "请输入退票id" << std::endl;
                    std::cin.getline(data, 30);
                    break;
                case 3:
                    
                    break;
                case 4:
                    
                    break;
                case 5:
                        
                    break;
                default:
                    std::cout << "输入错误" << std::endl;
                    break;
                }
                char sendbuf[BUFFER_SIZE];
                char command_char[10];
                sprintf(command_char, "%d %d", command, user_id);
                // 将command与data拼接给sendbuf赋值
                std::string str = "";
                str += command_char;
                str += " ";
                str += data;
                strcpy(sendbuf, str.c_str());
                // std::cout << sendbuf << std::endl;
                send(sock_cli, sendbuf, strlen(sendbuf),0); //发送
                // 清空data
                memset(data, 0, sizeof(data));
                memset(sendbuf, 0, sizeof(sendbuf));
                input = false;
            }
        }
        continue;
        
    }

    close(sock_cli);
    return 0;
}