#pragma once
typedef struct Transport {

    int idTransport;
    int type;
    float battery;
    float autonomy;
    float price; 
    int status; // 1 - Maintenance | 2 - MIA (Missing in Action) | 3 - Rented | 4 - Available |
    char geolocation[100];

} Transport;

typedef struct Transports {

    Transport t;

    struct Transports* next;
    struct Transports* prev;

} Transports;

