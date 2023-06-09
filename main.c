/*****************************************************************//**
 * \file   main.c
 * \brief  
 * 
 * \author Diogo Pinto & Ricardo Cruz
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

	// Client current location
	double lat = 41.535610;
	double lon = -8.627301;

	
	clients_head = read_clients_from_file(); // Reads clients
	transports_head = read_transports_from_file(); // Reads transports
	nodes_head = read_nodes_from_file(); // Reads nodes
	edges_head = read_edges_from_file(nodes_head); // Reads edges and adds on nodes
	prices_head = read_prices_from_file(); // Reads prices

	//print_clients(clients_head);
	//print_nodes(nodes_head);
	//list_nodes_with_edges(nodes_head);
	//print_transports(transports_head);

	find_nodes_within_radius(nodes_head, lat, lon, transports_head);

	//find_transports_battery(transports_head);
	

	// Writes nodes to binary file
	writeNodeToFile(nodes_head);


	// Free memory
	free_clients_list(clients_head);
	free_edges_list(edges_head);
	free_nodes_list(nodes_head);


	return 0;
}
