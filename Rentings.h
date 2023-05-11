#define DATE_SIZE 100

#pragma region GRAPH_STRUCT
typedef struct Node {
	int idNode;
	float longitude;
	float latitude;
	struct Node* next;
	struct Edge* Adj;
} Node;


typedef struct Edge {
	float distance;
	int destination;
	struct Edge* next;
} Edge;

#pragma endregion

#pragma region RENTING_STRUCT


typedef struct Renting {
	int idTransport;
	int idNode;
	char startDate[DATE_SIZE];
	char endDate[DATE_SIZE];
	int nifRenting;
	float totalPrice;
	struct Renting* next;
} Renting;

#pragma endregion

#pragma region PICKUP_STRUCT
typedef struct Pickup {
	int idNode;
	struct Transports* next;
};

#pragma endregion



Node* read_nodes_from_file();
Edge* read_edges_from_file();
void print_nodes(Node* nodes_head);
