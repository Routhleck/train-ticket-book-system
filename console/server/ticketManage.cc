#include "ticketManage.h"

int getTrainId(int ticket_start, int ticket_end, int station_amount, std::vector<train>& train_vector) {

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
    // 判断该车票的等级
    int ticket_level = 0;
    int short_distance = station_amount / 3;
    int medium_distance = station_amount * 2 / 3;
    if (abs(ticket_end - ticket_start) <= short_distance) {
        ticket_level = 1;
    }
    else if (abs(ticket_end - ticket_start) <= medium_distance) {
        ticket_level = 2;
    }
    else {
        ticket_level = 3;
    }
    // 选择符合条件的车次
    int train_id = findTrainId(train_direction, ticket_start, ticket_end, ticket_level, train_vector);
    return train_id;
}

std::vector<train> sortByLevel(std::vector<train> train_vector, int target_level) {
    std::cout << target_level << std::endl;
    // 按照车次等级排序
    std::vector<train> train_vector_level;
    // 若level为1, 则按照车次level从1到3排序
    if (target_level == 1) {
        for (int i = 0; i < train_vector.size(); i++) {
            if (train_vector[i].get_train_level() == 1) {
                train_vector_level.push_back(train_vector[i]);
            }
        }
        for (int i = 0; i < train_vector.size(); i++) {
            if (train_vector[i].get_train_level() == 2) {
                train_vector_level.push_back(train_vector[i]);
            }
        }
        for (int i = 0; i < train_vector.size(); i++) {
            if (train_vector[i].get_train_level() == 3) {
                train_vector_level.push_back(train_vector[i]);
            }
        }
    }
    // 若level为2, 则按照车次level从2到3排序
    else if (target_level == 2) {
        for (int i = 0; i < train_vector.size(); i++) {
            if (train_vector[i].get_train_level() == 2) {
                train_vector_level.push_back(train_vector[i]);
            }
        }
        for (int i = 0; i < train_vector.size(); i++) {
            if (train_vector[i].get_train_level() == 3) {
                train_vector_level.push_back(train_vector[i]);
            }
        }
    }
    // 若level为3, 则选取车次level为3的车次
    else {
        for (int i = 0; i < train_vector.size(); i++) {
            if (train_vector[i].get_train_level() == 3) {
                train_vector_level.push_back(train_vector[i]);
            }
        }
    }
    return train_vector_level;
}

int findTrainId(int train_direction, int train_start, int train_end, int train_level, std::vector<train>& train_vector) {
    std::vector<train> temp_train;
    // 按照车次等级排序
    temp_train = sortByLevel(train_vector, train_level);
    // 找到符合条件的车次
    for (int i = 0; i < temp_train.size(); i++) {
        if (temp_train[i].get_train_direction() == train_direction) {
            if (train_direction == 1) {
                if (temp_train[i].get_train_start() <= train_start) {
                    if (temp_train[i].get_train_end() >= train_end) {
                        return temp_train[i].get_train_id();
                    }
                }
            }
            else {
                if (temp_train[i].get_train_start() >= train_start) {
                    if (temp_train[i].get_train_end() <= train_end) {
                        return temp_train[i].get_train_id();
                    }
                }
            }
        }
    }
    std::cout << "没有符合条件的车次" << std::endl;
    return -1;
}

void addTicket(int& ticket_num, int ticket_start, int ticket_end, int station_amount, std::vector<train>& train_vector, std::vector<ticket>& ticket_vector, std::vector<station>& station_vector) {
    int ticket_id = getTrainId(ticket_start, ticket_end, station_amount, train_vector);
    if (ticket_id == -1) {
        return;
    }
    station start = station_vector[ticket_start - 1];
    station end = station_vector[ticket_end - 1];

    // 找到id为ticket_id的train
    for (int i = 0; i < train_vector.size(); i++) {
        if (train_vector[i].get_train_id() == ticket_id) {
            // 乘客数+1
            train_vector[i].add_train_passenger_now();
            // 生成车票
            ticket new_ticket(ticket_num, ticket_id, ticket_start, ticket_end, start, end, train_vector[i]);
            // 打印车票
            new_ticket.print_ticket();

            ticket_vector.push_back(new_ticket);
            ticket_num++;
            break;
        }
    }
}