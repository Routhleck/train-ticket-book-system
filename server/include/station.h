#ifndef STATION_H_H
#define STATION_H_H
#include <string>
#include <iostream>

class station {
public:
    station(int station_id, std::string station_name, int station_position): 
    station_id(station_id), station_name(station_name), station_position(station_position) {}
    int get_station_id() const { return station_id; }
    double get_station_position() const { return station_position; }
    std::string get_station_name() const { return station_name; }
    // 通过id重载比较运算符来为vector排序
    bool operator<(const station& other) const { return station_id < other.station_id; }
    // 通过两个车站的位置计算两个车站之间的距离
    double distance_cal(station& other) { return abs(station_position - other.station_position); };
    void print_station() const { std::cout << "station_id: " << station_id << " station_name: " << station_name << " station_position: " << station_position << std::endl; }


private:
    int station_id; // 车站id
    std::string station_name; // 车站名
    double station_position; // 车站位置(以第一站为0)
};
#endif