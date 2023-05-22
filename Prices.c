/*****************************************************************//**
 * \file   Prices.c
 * \brief  
 * 
 * \author Diogo
 * \date   May 2023
 *********************************************************************/

#pragma warning(disable:4996)

#pragma region INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Prices.h"
#define MAX_LINE_SIZE 100
#pragma endregion

#pragma region READ_PRICES_FILE

Prices* read_prices_from_file()
{
    Prices* prices_head = NULL;
    FILE* file = fopen("prices.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return prices_head;
    }

    char line[MAX_LINE_SIZE];

    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        char* token = strtok(line, ",");
        Prices* new_price = (Prices*)malloc(sizeof(Prices));

        new_price->type = atoi(token);

        token = strtok(NULL, ",");
        new_price->price = atof(token);

        token = strtok(NULL, ",");
        new_price->date = *token;

        new_price->next = NULL;
        new_price->prev = NULL;

        if (prices_head == NULL)
        {
            prices_head = new_price;
        }
        else
        {
            Prices* current = prices_head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_price;
            new_price->prev = current;
        }
    }

    fclose(file);

    return prices_head;
}


#pragma endregion
