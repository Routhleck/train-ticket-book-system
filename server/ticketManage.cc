#include "include/ticketManage.h"
#include <string.h>

int getTrainId(int ticket_start, int ticket_end, std::vector<train>& train_vector) {

    // 若始发地与终点相同，返回错误
    if (ticket_start == ticket_end) {
        std::cout << "始发地与终点相同" << std::endl;
        return -1;
    }

    // 通过始发地与终点判断车次方向
    int train_direction = 0;
    if (ticket_start < ticket_end) {
        train_direction = 1;
    }
    // 判断该车票的距离
    int ticket_distance = abs(ticket_end - ticket_start);
    // 选择符合条件的车次
    int train_id = findTrainId(train_direction, ticket_start, ticket_end, ticket_distance, train_vector);
    return train_id;
}

std::vector<train> sortByLevel(std::vector<train> train_vector, int target_distance) {
    // std::cout << target_distance << std::endl;
    // 按照车次距离排序
    std::vector<train> train_vector_level;
    // 取大于等于target_distance的车次，从小到大排序
    for (int i = 0; i < train_vector.size(); i++) {
        if (train_vector[i].get_train_distance() >= target_distance) {
            train_vector_level.push_back(train_vector[i]);
        }
    }
    // 从小到大排序
    for (int i = 0; i < train_vector_level.size(); i++) {
        for (int j = i + 1; j < train_vector_level.size(); j++) {
            if (train_vector_level[i].get_train_distance() > train_vector_level[j].get_train_distance()) {
                train temp = train_vector_level[i];
                train_vector_level[i] = train_vector_level[j];
                train_vector_level[j] = temp;
            }
        }
    }
    return train_vector_level;
}

int findTrainId(int train_direction, int train_start, int train_end, int train_distance, std::vector<train>& train_vector) {
    std::vector<train> temp_train;
    // 按照车次距离排序
    temp_train = sortByLevel(train_vector, train_distance);
    // 找到符合条件的车次
    for (int i = 0; i < temp_train.size(); i++) {
        if (temp_train[i].get_train_direction() == train_direction) {
            if (train_direction == 1) {
                if (temp_train[i].get_train_start() <= train_start) {
                    if (temp_train[i].get_train_end() >= train_end) {
                        if (temp_train[i].get_train_passenger_now() == temp_train[i].get_train_passenger_capcacity()) {
                            // std::cout << "该车次已满" << std::endl;
                            continue;
                        }
                        else {
                            return temp_train[i].get_train_id();
                        }
                    }
                }
            }
            else {
                if (temp_train[i].get_train_start() >= train_start) {
                    if (temp_train[i].get_train_end() <= train_end) {
                        if (temp_train[i].get_train_passenger_now() == temp_train[i].get_train_passenger_capcacity()) {
                            // std::cout << "该车次已满" << std::endl;
                            continue;
                        }
                        else {
                            return temp_train[i].get_train_id();
                        }
                    }
                }
            }
        }
    }
    std::cout << "没有符合条件的车次" << std::endl;
    return -1;
}

bool addTicket(int user_id, int& ticket_num, int ticket_start, int ticket_end, std::vector<train>& train_vector, std::vector<ticket>& ticket_vector, std::vector<station>& station_vector) {
    int ticket_id = getTrainId(ticket_start, ticket_end, train_vector);
    if (ticket_id == -1) {
        return false;
    }
    station start = station_vector[ticket_start - 1];
    station end = station_vector[ticket_end - 1];

    // 找到id为ticket_id的train
    for (int i = 0; i < train_vector.size(); i++) {
        if (train_vector[i].get_train_id() == ticket_id) {
            // 乘客数+1
            train_vector[i].add_train_passenger_now();
            // 生成车票
            ticket new_ticket(ticket_num, ticket_id, user_id, ticket_start, ticket_end, start, end, train_vector[i]);
            // 打印车票
            // new_ticket.print_ticket();

            ticket_vector.push_back(new_ticket);
            ticket_num++;
            break;
        }
    }
    return true;
}

bool addTicketNoOptimized(int user_id, int& ticket_num, int ticket_start, int ticket_end, std::vector<train>& train_vector, std::vector<ticket>& ticket_vector, std::vector<station>& station_vector) {
    int ticket_id = -1;

    // 通过始发地与终点判断车次方向
    int train_direction = 0;
    if (ticket_start < ticket_end) {
        train_direction = 1;
    }
    for (int i = 0; i < train_vector.size(); i++) {
        if (train_vector[i].get_train_direction() == train_direction) {
            if (train_direction == 1) {
                if (train_vector[i].get_train_start() <= ticket_start) {
                    if (train_vector[i].get_train_end() >= ticket_end) {
                        if (train_vector[i].get_train_passenger_now() == train_vector[i].get_train_passenger_capcacity()) {
                            // std::cout << "该车次已满" << std::endl;
                            continue;
                        }
                        else {
                            ticket_id = train_vector[i].get_train_id();
                            break;
                        }
                    }
                }
            }
            else {
                if (train_vector[i].get_train_start() >= ticket_start) {
                    if (train_vector[i].get_train_end() <= ticket_end) {
                        if (train_vector[i].get_train_passenger_now() == train_vector[i].get_train_passenger_capcacity()) {
                            // std::cout << "该车次已满" << std::endl;
                            continue;
                        }
                        else {
                            ticket_id = train_vector[i].get_train_id();
                            break;
                        }
                    }
                }
            }
        }
    }
    station start = station_vector[ticket_start - 1];
    station end = station_vector[ticket_end - 1];

    // 找到id为ticket_id的train
    for (int i = 0; i < train_vector.size(); i++) {
        if (train_vector[i].get_train_id() == ticket_id) {
            // 乘客数+1
            train_vector[i].add_train_passenger_now();
            // 生成车票
            ticket new_ticket(ticket_num, ticket_id, user_id, ticket_start, ticket_end, start, end, train_vector[i]);
            // 打印车票
            // new_ticket.print_ticket();

            ticket_vector.push_back(new_ticket);
            ticket_num++;
            break;
        }
    }
    return true;
}

// 退票
bool deleteTicket(int user_id, int ticket_id, std::vector<ticket>& ticket_vector, std::vector<train>& train_vector) {
    // 寻找到符合的车票
    for (int i = 0; i < ticket_vector.size(); i++) {
        if (ticket_vector[i].get_ticket_id() == ticket_id && ticket_vector[i].get_user_id() == user_id) {
            // 找到对应的车次
            for (int j = 0; j < train_vector.size(); j++) {
                if (train_vector[j].get_train_id() == ticket_vector[i].get_train_id()) {
                    // 乘客数-1
                    train_vector[j].sub_train_passenger_now();
                    break;
                }
            }
            // 删除车票
            ticket_vector.erase(ticket_vector.begin() + i);
            std::cout << "退票成功" << std::endl;
            return true;
        }
        // 若没有找到符合的车票
        if (i == ticket_vector.size() - 1) {
            std::cout << "没有找到符合的车票" << std::endl;
            return false;
        }
    }
    return false;
}

// 查看余票
void checkRestTicket (char* buffer,std::vector<train>& train_vector) {
    char temp[100] = "";
    for (int i = 0; i < train_vector.size(); i++) {
        if (train_vector[i].get_train_passenger_now() < train_vector[i].get_train_passenger_capcacity()) {
            std::cout << "车次" << train_vector[i].get_train_id() << "有余票" << train_vector[i].get_train_passenger_capcacity() - train_vector[i].get_train_passenger_now() << "张" << std::endl;
            sprintf(temp, "车次 %d 有余票 %d 张, 票价: %.2lf/单位距离\n", train_vector[i].get_train_id(), train_vector[i].get_train_passenger_capcacity() - train_vector[i].get_train_passenger_now(), train_vector[i].get_train_price());
            strcat(buffer, temp);
        }
        else {
            std::cout << "车次" << train_vector[i].get_train_id() << "无余票" << std::endl;
            sprintf(temp, "车次 %d 无余票\n", train_vector[i].get_train_id());
            strcat(buffer, temp);
        }
    }
}

// 查看自己购票
void checkBuyTicket(int user_id, char* buffer, std::vector<ticket>& ticket_vector) {
    char temp[100] = "";
    for (int i = 0; i < ticket_vector.size(); i++) {
        if (ticket_vector[i].get_user_id() == user_id) {
            printf("车票id:%d|车票车次id:%d|始发站id:%d|终点站id:%d|票价:%d\n", ticket_vector[i].get_ticket_id(), ticket_vector[i].get_train_id(), ticket_vector[i].get_ticket_start(), ticket_vector[i].get_ticket_end(), ticket_vector[i].get_ticket_price());

            sprintf(temp, "车票id:%d|车票车次id:%d|始发站id:%d|终点站id:%d|票价:%d\n", ticket_vector[i].get_ticket_id(), ticket_vector[i].get_train_id(), ticket_vector[i].get_ticket_start(), ticket_vector[i].get_ticket_end(), ticket_vector[i].get_ticket_price());
            strcat(buffer, temp);        
        }
    }
}