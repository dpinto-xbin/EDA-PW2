/*****************************************************************//**
 * \file   Clients.c
 * \brief  
 * 
 * \author Diogo
 * \date   March 2023
 *********************************************************************/
#pragma warning(disable:4996)

#pragma region INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Clients.h"
#pragma endregion

#pragma region ADD_CLIENT

Clients* add_client(Clients* clients_head, Client new_client)
{
    Clients* new_node;
    bool success = create_node(&new_node, new_client);
    if (!success)
    {
        //printf("Failed to create new node.\n");
        return clients_head;
    }

    success = add_node(&clients_head, new_node);
    if (!success)
    {
        //printf("Failed to add node to list.\n");
    }

    return clients_head;
}

bool create_node(Clients** new_node, Client new_client)
{
    *new_node = (Clients*)malloc(sizeof(Clients));
    if (*new_node == NULL)
    {
        //printf("Failed to allocate memory for new node.\n");
        return false;
    }

    (*new_node)->c = new_client;
    (*new_node)->next = NULL;
    (*new_node)->prev = NULL;
    return true;
}

bool add_node(Clients** clients_head, Clients* new_node)
{
    if (*clients_head == NULL)
    {
        *clients_head = new_node;
        return true;
    }
    else
    {
        Clients* current_node = *clients_head;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
        new_node->prev = current_node;
        return true;
    }
    return false;
}
#pragma endregion

#pragma region LIST_CLIENTS
void print_clients(Clients* clients_head)
{
    Clients* current_node = clients_head;
    while (current_node != NULL)
    {
        printf("Name: %s\n", current_node->c.name);
        printf("Balance: %.2f\n", current_node->c.balance);
        printf("NIF: %d\n", current_node->c.nif);
        printf("Address: %s\n", current_node->c.address);
        printf("Phone: %s\n", current_node->c.phone);
        printf("Email: %s\n\n", current_node->c.email);
        current_node = current_node->next;
    }
}
#pragma endregion

#pragma region FREE_CLIENTS
void free_clients_list(Clients* clients_head)
{
    Clients* current_node = clients_head;
    while (current_node != NULL)
    {
        Clients* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
}
#pragma endregion

#pragma region READ_FILE_CLIENTS
Clients* read_clients_from_file()
{
    Clients* clients_head = NULL;
    FILE* file = fopen("clients.txt", "r");
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
