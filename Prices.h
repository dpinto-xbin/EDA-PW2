#pragma once
typedef struct Prices {

    int idTransport;
    float price;
    char date;

    struct Prices* next;
    struct Prices* prev;

} Prices;
