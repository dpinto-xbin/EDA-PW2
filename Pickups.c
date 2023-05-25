/*****************************************************************//**
 * \file   Pickups.c
 * \brief  
 * 
 * \author Diogo Pinto & Ricardo Cruz
 * \date   May 2023
 *********************************************************************/

#pragma warning(disable:4996)

#pragma region INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Transports.h"
#include "Rentings.h"
#define MAX_LINE_SIZE 100
#include <math.h>
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371.0 // Value obtained in Google - Unit: km
#define MAX_NODES 10
#pragma endregion

#pragma region READ_NODES
/**
 * \brief Read graph nodes from file
 * 
 * \return 
 */
Node* read_nodes_from_file()
{
    Node* nodes_head = NULL;
    FILE* file = fopen("nodes.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return nodes_head;
    }

    char line[MAX_LINE_SIZE];

    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        char* token = strtok(line, ",");
        Node* new_node = (Node*)malloc(sizeof(Node));

        new_node->idNode = atoi(token);

        token = strtok(NULL, ",");
        new_node->latitude = atof(token);

        token = strtok(NULL, ",");
        new_node->longitude = atof(token);

        new_node->next = NULL;
        new_node->Adj = NULL;

        if (nodes_head == NULL)
        {
            nodes_head = new_node;
        }
        else
        {
            Node* current = nodes_head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    fclose(file);

    return nodes_head;
}

#pragma endregion

#pragma region READ_EDGES

/**
 * \brief Reads graph edges and with nodes_head inserts them onto the graph
 * 
 * \param nodes_head
 * \return 
 */

Edge* read_edges_from_file(Node* nodes_head)
{
    Edge* edges_head = NULL;
    FILE* file = fopen("edges.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return edges_head;
    }

    char line[MAX_LINE_SIZE];

    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        char* token = strtok(line, ",");
        int source_node_id = atoi(token);

        token = strtok(NULL, ",");
        int destination_node_id = atoi(token);

        token = strtok(NULL, ",");
        double distance = atof(token);

        // Find the corresponding source node
        Node* source_node = find_node_by_id(source_node_id, nodes_head);
        if (source_node == NULL)
        {
            printf("Error: Source node with ID %d not found.\n", source_node_id);
            continue;  // Skip this edge and proceed to the next line
        }

        // Find the corresponding destination node
        Node* destination_node = find_node_by_id(destination_node_id, nodes_head);
        if (destination_node == NULL)
        {
            printf("Error: Destination node with ID %d not found.\n", destination_node_id);
            continue;  // Skip this edge and proceed to the next line
        }

        // Create new edges for both directions
        Edge* new_edge_source = (Edge*)malloc(sizeof(Edge));
        new_edge_source->distance = distance;
        new_edge_source->destination = destination_node_id;
        new_edge_source->next = NULL;

        Edge* new_edge_destination = (Edge*)malloc(sizeof(Edge));
        new_edge_destination->distance = distance;
        new_edge_destination->destination = source_node_id;
        new_edge_destination->next = NULL;

        // Attach the new edges to the respective nodes
        if (source_node->Adj == NULL)
        {
            source_node->Adj = new_edge_source;
        }
        else
        {
            Edge* current = source_node->Adj;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_edge_source;
        }

        if (destination_node->Adj == NULL)
        {
            destination_node->Adj = new_edge_destination;
        }
        else
        {
            Edge* current = destination_node->Adj;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_edge_destination;
        }
    }

    fclose(file);

    return edges_head;
}

#pragma endregion

#pragma region FIND_NODE_ID

/**
 * \brief Finds the nodeID inside the graph
 * 
 * \param node_id
 * \param nodes_head
 * \return 
 */

Node* find_node_by_id(int node_id, Node* nodes_head)
{
    Node* current = nodes_head;  // Assuming the linked list of nodes is accessible as "nodes_head"

    while (current != NULL)
    {
        if (current->idNode == node_id)
        {
            return current;  // Found the node with the specified ID
        }
        current = current->next;
    }

    return NULL;  // Node with the specified ID not found
}


#pragma endregion

#pragma region LIST_NODES
/**
 * \brief Lists all the nodes
 * 
 * \param nodes_head
 */
void print_nodes(Node* nodes_head)
{
    Node* current_node = nodes_head;
    while (current_node != NULL)
    {
        printf("ID: %d\n", current_node->idNode);
        printf("Longitude: %f\n", current_node->longitude);
        printf("Latitude: %f\n", current_node->latitude);
        current_node = current_node->next;
    }
}
#pragma endregion

#pragma region LIST_NODES_WITH_EDGES

/**
 * \brief Lists all the nodes with edges included
 * 
 * \param nodes_head
 */

void list_nodes_with_edges(Node* nodes_head)
{
    Node* current = nodes_head;

    while (current != NULL)
    {
        printf("Node ID: %d\n", current->idNode);
        printf("Latitude: %f\n", current->latitude);
        printf("Longitude: %f\n", current->longitude);
        printf("Edges:\n");

        Edge* edge = current->Adj;
        while (edge != NULL)
        {
            printf("    Destination: %d, Distance: %.2f\n", edge->destination, edge->distance);
            edge = edge->next;
        }

        printf("\n");

        current = current->next;
    }
}


#pragma endregion

#pragma region FREE_NODES
/**
 * \brief Clear memory of nodes
 * 
 * \param nodes_head
 */
void free_nodes_list(Node* nodes_head)
{
    Node* current_node = nodes_head;
    while (current_node != NULL)
    {
        Node* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
}
#pragma endregion

#pragma region FREE_EDGES
/**
 * \brief Clear memory of edges
 * 
 * \param edges_head
 */
void free_edges_list(Edge* edges_head)
{
    Node* current_edge = edges_head;
    while (current_edge != NULL)
    {
        Node* next_edge = current_edge->next;
        free(current_edge);
        current_edge = next_edge;
    }
}
#pragma endregion

#pragma region SEARCH_TRANSPORT_BY_LOCATION
/**
 * \brief Uses locationID to list all transports with status 4
 * 
 * \param transports_head
 * \param locationID
 */
void listTransportsByLocation(Transports* transports_head, int locationID) {

    Transports* current = transports_head;
    int sum = 0;
    printf("\nTransports available:\n");
    while (current != NULL)
    {
        if (current->t.location == locationID && current->t.status == 4) {

            printf("Transport ID: %d\n", current->t.idTransport);
            printf("Type: %d\n", current->t.type);
            printf("Battery: %.2f\n", current->t.battery);
            printf("Autonomy: %.2f\n", current->t.autonomy);
            printf("\n");
            sum++;
        }
        current = current->next;
    }

    if (sum == 0) {
        printf("No available transports!\n");
    }
}

#pragma endregion

#pragma region SEARCH_PICKUP_POINTS


/**
 * \brief Haversine function that measures distance between two points
 * 
 * \param lat1
 * \param lon1
 * \param lat2
 * \param lon2
 * \return 
 */
double haversine_distance(double lat1, double lon1, double lat2, double lon2)
{
    double dlat = (lat2 - lat1) * PI / 180.0;
    double dlon = (lon2 - lon1) * PI / 180.0;

    double a = sin(dlat / 2) * sin(dlat / 2) +
        cos(lat1 * PI / 180.0) * cos(lat2 * PI / 180.0) *
        sin(dlon / 2) * sin(dlon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = EARTH_RADIUS * c;
    return distance;
}
/**
 * \brief When user gives location, searches through the graph for all the nodes within the range of 5km
 * 
 * \param nodes_head
 * \param target_latitude
 * \param target_longitude
 */
void find_nodes_within_radius(Node* nodes_head, double target_latitude, double target_longitude, Transports* transports_head)
{
    Node* current = nodes_head;

    while (current != NULL)
    {

        double distance = haversine_distance(target_latitude, target_longitude, current->latitude, current->longitude);


        if (distance <= 5.0) // Check if distance is equal or lower than 5km
        {
            printf("------------------------------------------------------\n");
            printf("Node ID: %d\n", current->idNode);
            //printf("Latitude: %f\n", current->latitude);
            //printf("Longitude: %f\n", current->longitude);
            printf("Distance: %f km\n\n", distance);

            listTransportsByLocation(transports_head, current->idNode);

            printf("------------------------------------------------------\n");

        }

        current = current->next;
    }
}


#pragma endregion


#pragma region SAVE_TO_BINARY_FILE

/**
 * \brief Saves graph to binary file
 * 
 * \param nodes_head
 */

void writeNodeToFile(Node* nodes_head) {
    FILE* file = fopen("nodes.bin", "wb");

    Node* current = nodes_head;
    while (current != NULL) {
        fwrite(current, sizeof(Node), 1, file);
        current = current->next;
    }

    fclose(file);
}

#pragma endregion
