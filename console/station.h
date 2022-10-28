
/*
    station为站点类
    int 站点id
    double 站点在这条线路的什么位置
*/

class station
{
private:
    int id_station;
    double position;
public:
    station(int id, double position);
    ~station();
    station get_station_by_id(int id_station);
};


    