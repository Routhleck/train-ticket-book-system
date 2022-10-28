class ticket
{
private:
    int id_ticket;
    int id_start;
    int id_end;
    int id_train;
    double price;
public:
    ticket(int id_ticket, int id_start, int id_end, int id_train);
    ~ticket();
    double price_cal(int id_start, int id_end, double price_per_km);
};

