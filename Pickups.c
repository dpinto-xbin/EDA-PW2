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
#include <math.h>
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371.0 // Raio médio da Terra em quilômetros
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
void find_nodes_within_radius(Node* nodes_head, double target_latitude, double target_longitude)
{
    Node* current = nodes_head;

    while (current != NULL)
    {

        double distance = haversine_distance(target_latitude, target_longitude, current->latitude, current->longitude);


        if (distance <= 5.0) // Verificar se a distância está dentro do raio de 5 km
        {
            printf("Node ID: %d\n", current->idNode);
            printf("Latitude: %f\n", current->latitude);
            printf("Longitude: %f\n", current->longitude);
            printf("Distance: %f km\n\n", distance);
        }

        current = current->next;
    }
}


#pragma endregion


#pragma region TESTE


// Function to find the index of the node with the minimum distance
int findMinDistanceNode(int* dist, int* visited, int numNodes) {
    int minDistance = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i] && dist[i] < minDistance) {
            minDistance = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Function to print the shortest path
void printShortestPath(int parent[], int node) {
    if (parent[node] == -1) {
        printf("%d ", node);
        return;
    }

    printShortestPath(parent, parent[node]);
    printf("%d ", node);
}

// Function to execute the Dijkstra's algorithm
void dijkstra(Node* graph, int source) {
    int numNodes = 0;
    Node* temp = graph;
    while (temp != NULL) {
        numNodes++;
        temp = temp->next;
    }

    int* dist = malloc(numNodes * sizeof(int));
    int* visited = malloc(numNodes * sizeof(int));
    int* parent = malloc(numNodes * sizeof(int));

    for (int i = 0; i < numNodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = -1;
        int minDistance = INT_MAX;

        for (int i = 0; i < numNodes; i++) {
            if (!visited[i] && dist[i] < minDistance) {
                minDistance = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        temp = graph;
        while (temp != NULL && temp->idNode != u)
            temp = temp->next;

        if (temp != NULL) {
            Edge* edge = temp->Adj;
            while (edge != NULL) {
                int v = edge->destination;
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + edge->distance < dist[v]) {
                    dist[v] = dist[u] + edge->distance;
                    parent[v] = u;
                }
                edge = edge->next;
            }
        }
    }

    printf("Node\tDistance\tPath\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%d\t%d\t\t", i, dist[i]);
        int node = i;
        while (node != -1) {
            printf("%d ", node);
            node = parent[node];
        }
        printf("\n");
    }

    free(dist);
    free(visited);
    free(parent);
}


#pragma endregion
