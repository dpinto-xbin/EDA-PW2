#define DATE_SIZE 100

#pragma region GRAPH_STRUCT
typedef struct Node {
	int idNode;
	double longitude;
	double latitude;
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
Edge* read_edges_from_file(Node* nodes_head);
Node* find_node_by_id(int node_id, Node* nodes_head);
void list_nodes_with_edges(Node* nodes_head);
void free_edges_list(Edge* edges_head);
void free_nodes_list(Node* nodes_head);
double haversine_distance(double lat1, double lon1, double lat2, double lon2);
void find_nodes_within_radius(Node* nodes_head, double target_latitude, double target_longitude);
