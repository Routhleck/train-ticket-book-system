#include "ticket.h"
// 输入始发地与终点，返回车票信息
int getTrainId(int ticket_start, int ticket_end, int station_amount, std::vector<train>& train_vector);

// 按level排序
std::vector<train> sortByLevel(std::vector<train> train_vector, int target_level);

// 找的符合条件的车次
int findTrainId (int train_direction, int train_start, int train_end, int train_level, std::vector<train>& train_vector);

void addTicket (int& ticket_num, int ticket_start, int ticket_end, int station_amount, std::vector<train>& train_vector, std::vector<ticket>& ticket_vector, std::vector<station>& station_vector);