#ifndef TRAIN_H_H
#define TRAIN_H_H
#include <math.h>
#include <iostream>
class train {
public:
    train(int train_id, int train_start, int train_end, int train_passenger_capcacity, double train_price):
    train_id(train_id), train_start(train_start), train_end(train_end), train_passenger_capcacity(train_passenger_capcacity), train_price(train_price) 
    {
        // 判断车次的方向
        if (train_start < train_end) {
            train_direction = 1;
        } else {
            train_direction = 0;
        }
        this->train_passenger_now = 0;
        // 通过train_end与train_start判断该车次距离
        this->train_distance = abs(train_end - train_start);
    }
    int get_train_id() const { return train_id; }
    int get_train_direction() const { return train_direction; }
    int get_train_start() const { return train_start; }
    int get_train_end() const { return train_end; }
    int get_train_passenger_capcacity() const { return train_passenger_capcacity; }
    int get_train_passenger_now() const { return train_passenger_now; }
    double get_train_price() const { return train_price; }
    int get_train_distance() const { return train_distance; }
    // 若有乘客购票，乘客数+1
    void add_train_passenger_now() { train_passenger_now++; }
    // 若有乘客退票，乘客数-1
    void sub_train_passenger_now() { train_passenger_now--; }
    void print_train() const {
        std::cout << "车次：" << train_id << std::endl;
        std::cout << "始发站：" << train_start << std::endl;
        std::cout << "终点站：" << train_end << std::endl;
        std::cout << "车次价格：" << train_price << std::endl;
        std::cout << "车次距离：" << train_distance << std::endl;
        std::cout << "车次方向：" << train_direction << std::endl;
        std::cout << "车次容量：" << train_passenger_capcacity << std::endl;
        std::cout << "当前乘客数：" << train_passenger_now << std::endl;
    }
private:
    int train_id; // 车次id
    int train_direction; // 车次方向 1为正向 0为反向
    int train_start; // 车次始发站id
    int train_end; // 车次终点站id
    int train_passenger_capcacity; // 乘客容量
    int train_passenger_now; // 当前乘客数
    double train_price; // 车次单位价格
    int train_distance; // 车次距离
};

#endif
