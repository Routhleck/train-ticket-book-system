#ifndef TICKETMANAGE_H_H
#define TICKETMANAGE_H_H
#include "ticket.h"
// 站点查询
void stationQuery(char*buffer, std::vector<station>& station_vector);

// 输入始发地与终点，返回车票信息
int getTrainId(int ticket_start, int ticket_end, std::vector<train>& train_vector);

// 按level排序
std::vector<train> sortByLevel(std::vector<train> train_vector, int target_level);

// 找的符合条件的车次
int findTrainId (int train_direction, int train_start, int train_end, int train_level, std::vector<train>& train_vector);

// 添加车票
bool addTicket (int user_id, int& ticket_num, int ticket_start, int ticket_end, std::vector<train>& train_vector, std::vector<ticket>& ticket_vector, std::vector<station>& station_vector);

// 添加车票（无算法）
bool addTicketNoOptimized(int user_id, int& ticket_num, int ticket_start, int ticket_end, std::vector<train>& train_vector, std::vector<ticket>& ticket_vector, std::vector<station>& station_vector);

// 退票
bool deleteTicket (int user_id, int ticket_id, std::vector<ticket>& ticket_vector, std::vector<train>& train_vector); 

// 查看余票
void checkRestTicket (char* buffer,std::vector<train>& train_vector);

// 查看自己购票
void checkBuyTicket(int user_id, char* buffer, std::vector<ticket>& ticket_vector);


#endif