/*****************************************************************//**
 * \file   Pickups.c
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
#include "Rentings.h"
#define MAX_LINE_SIZE 100
#pragma endregion


#pragma region READ_FILE_NODES
Node* read_nodes_from_file()
{
    Node* node_head = NULL;
    FILE* file = fopen("node.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return clients_head;
    }

    char line[MAX_LINE_SIZE];
    int i = 0;

    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        char* token = strtok(line, ",");
        Client new_client;
        strncpy(new_client.name, token, sizeof(new_client.name));

        token = strtok(NULL, ",");
        new_client.balance = atof(token);

        token = strtok(NULL, ",");
        new_client.nif = atoi(token);

        token = strtok(NULL, ",");
        strncpy(new_client.address, token, sizeof(new_client.address));

        token = strtok(NULL, ",");
        strncpy(new_client.phone, token, sizeof(new_client.phone));

        token = strtok(NULL, ",");
        strncpy(new_client.email, token, sizeof(new_client.email));


        clients_head = add_client(clients_head, new_client);


        i++;
    }

    fclose(file);

    return clients_head;
}
#pragma endregion