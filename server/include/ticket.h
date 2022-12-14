#ifndef TICKET_H_H
#define TICKET_H_H
#include "station.h"
#include "train.h"
#include <iostream>
#include <math.h>
#include <vector>

class ticket {
public:
    ticket(int ticket_id, int train_id, int user_id, int ticket_start, int ticket_end, double ticket_price):
    ticket_id(ticket_id), train_id(train_id), user_id(user_id), ticket_start(ticket_start), ticket_end(ticket_end), ticket_price(ticket_price) {}

    ticket(int ticket_id, int train_id, int user_id, int ticket_start, int ticket_end, station& start, station& end, train& train):
    ticket_id(ticket_id), train_id(train_id), user_id(user_id), ticket_start(ticket_start), ticket_end(ticket_end) 
    {
        this->ticket_price = this->calculate_price(start, end, train);
    }
    // 通过始发站与终点站计算票价
    double calculate_price(station& start, station& end, train& train) {
        return (train.get_train_price() * start.distance_cal(end));
    }

    void print_ticket() const {
        std::cout << "车票id:" << ticket_id << std::endl;
        std::cout << "车次id:" << train_id << std::endl;
        std::cout << "始发站：" << ticket_start << std::endl;
        std::cout << "终点站：" << ticket_end << std::endl;
        std::cout << "车票价格：" << ticket_price << std::endl;
    }
    int get_ticket_id() const { return ticket_id; }
    int get_train_id() const { return train_id; }
    int get_user_id() const { return user_id; }
    int get_ticket_start() const { return ticket_start; }
    int get_ticket_end() const { return ticket_end; }
    int get_ticket_price() const { return ticket_price; }

private:
    int ticket_id; // 车票id
    int train_id; // 车次id
    int user_id; //用户id
    int ticket_start; // 车票始发站id
    int ticket_end; // 车票终点站id
    int ticket_price; // 车票价格
};

#endif