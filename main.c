/*****************************************************************//**
 * \file   main.c
 * \brief  
 * 
 * \author Diogo
 * \date   March 2023
 *********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Clients.h"

int main()
{
	Clients* clients_head = NULL;

	clients_head = read_clients_from_file();

	print_clients(clients_head);

	free_clients_list(clients_head);

	return 0;
}
