/*****************************************************************//**
 * \file   Clients.h
 * \brief 
 * 
 * \author Diogo Pinto & Ricardo Cruz
 * \date   March 2023
 *********************************************************************/
#include <stdbool.h>

#pragma region CONSTANTS
#define NAME_SIZE 50
#define ADDRESS_SIZE 50
#define PHONE_SIZE 12
#define EMAIL_SIZE 50
#define MAX_LINE_SIZE 100
#pragma endregion

#pragma region CLIENT_STRUCT
typedef struct Client
{
    char name[NAME_SIZE];
    float balance;
    int nif;
    char address[ADDRESS_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];

} Client;
#pragma endregion

#pragma region CLIENTS_STRUCT
typedef struct Clients
{
    Client c;

    struct Clients* next;
    struct Clients* prev;

} Clients;

#pragma endregion

#pragma region INSERT_CLIENT
Clients* add_client(Clients* clients_head, Client new_client);
bool create_node(Clients** new_node, Client new_client);
bool add_node(Clients** clients_head, Clients* new_node);
#pragma endregion

#pragma region LIST_CLIENTS
void print_clients(Clients* clients_head);
#pragma endregion

#pragma region READ_CLIENTS
Clients* read_clients_from_file();
#pragma endregion

#pragma region FREE_DLL
void free_clients_list(Clients* clients_head);
#pragma endregion

