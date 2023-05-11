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


#pragma region READ_FILES
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
        new_node->longitude = atof(token);

        token = strtok(NULL, ",");
        new_node->latitude = atof(token);

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

Edge* read_edges_from_file()
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
        Edge* new_edge = (Edge*)malloc(sizeof(Edge));

        new_edge->distance = atof(token);

        token = strtok(NULL, ",");
        new_edge->destination = atoi(token);

        new_edge->next = NULL;

        if (edges_head == NULL)
        {
            edges_head = new_edge;
        }
        else
        {
            Edge* current = edges_head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_edge;
        }
    }

    fclose(file);

    return edges_head;
}
#pragma endregion

#pragma region LIST_NODES
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
