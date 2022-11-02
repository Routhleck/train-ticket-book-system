#include"station.h"

station::station() {
    stationNode* _dummyHead = new stationNode(0, 0);
    station_num = 0;
}

void station::set_station(int id, double position) {
    stationNode* p = _dummyHead;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = new stationNode(id, position);
    station_num++;
}

station station::get_station_by_id(int id_station){

}