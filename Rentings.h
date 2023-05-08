#define DATE_SIZE 100

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
} Edge;typedef struct Renting {
	int idTransport;
	int idNode;
	char startDate[DATE_SIZE];
	char endDate[DATE_SIZE];
	int nifRenting;
	float totalPrice;
	struct Renting* next;
} Renting;


typedef struct Pickup {
	int idNode;
	struct Transports* next;
};



