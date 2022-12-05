#include "server/ticket.h"
#include "server/ticketManage.h"
#include <vector>
using namespace std;

int main() {
    vector<station> stations;

    // 初始化车站
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

    // 打印车站信息
    for (int i = 0; i < stations.size(); i++) {
        stations[i].print_station();
    }

    // 初始化车次
    vector<train> trains;
    trains.push_back(train(1, 1, 10, 10, 1, sizeof(stations)));
    trains.push_back(train(2, 3, 7, 5, 2, sizeof(stations)));
    trains.push_back(train(3, 1, 5, 3, 3, sizeof(stations)));
    trains.push_back(train(4, 5, 10, 3, 1, sizeof(stations)));
    trains.push_back(train(5, 10, 6, 3, 2, sizeof(stations)));
    trains.push_back(train(6, 7, 1, 10, 3, sizeof(stations)));
    trains.push_back(train(7, 10, 1, 5, 1, sizeof(stations)));

    // 打印车次信息
    for (int i = 0; i < trains.size(); i++) {
        trains[i].print_train();
    }
    
    int ticket_num = 1;

    vector<ticket> tickets;

    // 添加车票
    addTicket(ticket_num, 3,7, sizeof(stations), trains, tickets, stations);
    addTicket(ticket_num, 1,10, sizeof(stations), trains, tickets, stations);

}