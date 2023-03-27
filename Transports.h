/*****************************************************************//**
 * \file   Transports.h
 * \brief  
 * 
 * \author Diogo
 * \date   March 2023
 *********************************************************************/

#pragma region CONSTANTS
#define GEOLOCATION_SIZE 100
#pragma endregion

#pragma region TRANSPORT_STRUCT
typedef struct Transport {

    int idTransport;
    int type;
    float battery;
    float autonomy;
    int status; // 1 - Maintenance | 2 - MIA (Missing in Action) | 3 - Rented | 4 - Available |
    char geolocation[GEOLOCATION_SIZE];

} Transport;
#pragma endregion

#pragma region TRANSPORTS_STRUCT
typedef struct Transports {

    Transport t;

    struct Transports* next;
    struct Transports* prev;

} Transports;
#pragma endregion