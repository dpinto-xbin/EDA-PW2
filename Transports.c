/*****************************************************************//**
 * \file   Transports.c
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
#include "Transports.h"
#define MAX_LINE_SIZE 100
#pragma endregion

#pragma region ADD_TRANSPORT

Transports* add_transport(Transports* transports_head, Transport new_transport)
{
    Transports* new_node = (Transports*)malloc(sizeof(Transports));
    if (new_node == NULL)
    {
        printf("Failed to allocate memory for new node.\n");
        return transports_head;
    }

    new_node->t = new_transport;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (transports_head == NULL)
    {
        transports_head = new_node;
    }
    else
    {
        Transports* current = transports_head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }

    return transports_head;
}

#pragma endregion

#pragma region READ_TRANSPORTS_FILE

Transports* read_transports_from_file()
{
    Transports* transports_head = NULL;
    FILE* file = fopen("transports.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return transports_head;
    }

    char line[MAX_LINE_SIZE];
    int i = 0;

    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        char* token = strtok(line, ",");
        Transport new_transport;
        new_transport.idTransport = atoi(token);

        token = strtok(NULL, ",");
        new_transport.type = atoi(token);

        token = strtok(NULL, ",");
        new_transport.battery = atof(token);

        token = strtok(NULL, ",");
        new_transport.autonomy = atof(token);

        token = strtok(NULL, ",");
        new_transport.status = atoi(token);

        token = strtok(NULL, ",");
        new_transport.location = atoi(token);

        transports_head = add_transport(transports_head, new_transport);

        i++;
    }

    fclose(file);

    return transports_head;
}


#pragma endregion

#pragma region LIST_TRANSPORTS

void print_transports(Transports* transports_head)
{
    if (transports_head == NULL)
    {
        printf("No transports available.\n");
        return;
    }

    Transports* current = transports_head;
    printf("Transports:\n");
    while (current != NULL)
    {
        printf("ID: %d\n", current->t.idTransport);
        printf("Type: %d\n", current->t.type);
        printf("Battery: %.2f\n", current->t.battery);
        printf("Autonomy: %.2f\n", current->t.autonomy);
        printf("Status: %d\n", current->t.status);
        printf("Location: %d\n", current->t.location);
        printf("-----------------------\n");

        current = current->next;
    }
}


#pragma endregion
