#pragma once
typedef struct Prices {

    int type;
    float price;
    char date;

    struct Prices* next;
    struct Prices* prev;

} Prices;
