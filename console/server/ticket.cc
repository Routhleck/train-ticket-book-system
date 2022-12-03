#include"ticket.h"

ticket::ticket(int id_ticket, int id_start, int id_end, int id_train)
{
    this->id_ticket = id_ticket;
    this->id_start = id_start;
    this->id_end = id_end;
    this->id_train = id_train;
}

ticket::~ticket()
{
}

double ticket::price_cal(int id_start, int id_end, double price_per_km)
{
    

}
