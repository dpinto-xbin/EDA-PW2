/*****************************************************************//**
 * \file   Prices.h
 * \brief  
 * 
 * \author Diogo Pinto & Ricardo Cruz
 * \date   May 2023
 *********************************************************************/
#pragma once
typedef struct Prices {

    int type;
    float price;
    char date;

    struct Prices* next;
    struct Prices* prev;

} Prices;
