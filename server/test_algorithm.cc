#include "include/ticketManage.h"

using namespace std;

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
    // int train_id, int train_start, int train_end, int train_passenger_capcacity, double train_price
    trains.push_back(train(1, 1, 10, 3, 1));
    trains.push_back(train(2, 1, 7, 3, 1));
    trains.push_back(train(3, 2, 5, 3, 1));
    trains.push_back(train(4, 5, 8, 3, 1));
    trains.push_back(train(5, 8, 10, 3, 1));

}


int main() {
    vector<station> stations;
    vector<train> trains;
    vector<train> trains_common;
    vector<ticket> tickets;
    vector<ticket> tickets_common;
    init_station(stations);
    init_train(trains, stations);
    init_train(trains_common, stations);
    int ticket_start_list[] = {8, 8, 8, 5, 5, 5, 2, 2, 2, 1, 1, 1, 1, 1, 1};
    int ticket_end_list[] = {10, 10, 10, 8, 8, 8, 5, 5, 5, 7, 7, 7, 10, 10, 10};

    int ticket_num = 1;
    int ticket_num_common = 1;
    int user_id = 1;

    int ticket_optimize_num = 0;
    int ticket_common_num = 0;
    
    // 放票15 张
    bool success = false;
    for (int i = 0; i < 15; i++) {
        
        int ticket_start = ticket_start_list[i];
        // ticket_end 不能等于 ticket_start
        int ticket_end = ticket_end_list[i];
        addTicketNoOptimized(user_id, ticket_num_common, ticket_start, ticket_end, trains, tickets_common, stations);
        addTicket(user_id, ticket_num, ticket_start, ticket_end, trains_common, tickets, stations);
        /* if (success) {
            cout << "start:" << ticket_start << "end: " << ticket_end << "add ticket success" << endl;
        }
        else {
            cout << "start:" << ticket_start << "end: " << ticket_end << "add ticket failed" << endl;
        } */
    }
    
    

    // 500次放票的上座率与500次成功放票次数
    // int success_num = tickets.size();
    // float success_rate = success_num / 100;
    float attendance_rate = float(tickets.size()) / 15;
    cout << "使用算法优化放票策略的上座率: " << attendance_rate << endl;
    attendance_rate = float(tickets_common.size()) / 15;
    cout << "不使用算法优化放票策略的上座率: " << attendance_rate << endl;

    return 0;
}