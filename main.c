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
#include "Rentings.h"
#include "Transports.h"
#include "Prices.h"



int main()
{
	Clients* clients_head = NULL;
	Node* nodes_head = NULL;
	Edge* edges_head = NULL;
	Transports* transports_head = NULL;
	Prices* prices_head = NULL;

	
	clients_head = read_clients_from_file(); // Reads clients
	transports_head = read_transports_from_file(); // Reads transports
	nodes_head = read_nodes_from_file(); // Reads nodes
	edges_head = read_edges_from_file(nodes_head); // Reads edges and adds on nodes
	prices_head = read_prices_from_file();

	//print_clients(clients_head);
	print_nodes(nodes_head);
	//list_nodes_with_edges(nodes_head);
	//print_transports(transports_head);

	find_nodes_within_radius(nodes_head, 41.535610, -8.628196);


	// FREE DLL
	free_clients_list(clients_head);
	free_edges_list(edges_head);
	free_nodes_list(nodes_head);


	return 0;
}
