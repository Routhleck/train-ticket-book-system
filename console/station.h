
/*
    station为站点类
    int 站点id
    double 站点在这条线路的什么位置
*/

class station
{
public:
    struct stationNode{
        int id_station;
        double position;
        stationNode *next;
        stationNode(int id_station, double position, stationNode *next = nullptr)
            :id_station(id_station), position(position), next(next){}
    };
    
    station();
    ~station();
    void set_station(int id, double position);
    station get_station_by_id(int id_station);
    
private:
    stationNode* _dummyHead;
    int station_num;

};


    