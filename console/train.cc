#include"train.h"

train::train(int id_train, int id_start, int id_end, int passenger_capacity)
{
    this->id_train = id_train;
    this->id_start = id_start;
    this->id_end = id_end;
    this->passenger_capcacity = passenger_capacity;
    this->passenger_now = 0;
}

train::~train()
{
}