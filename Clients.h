typedef struct Client
{
    char name[50];
    float balance;
    int nif;
    char address[50];
    char phone[12];
    char email[50];

} Client;

typedef struct Clients
{
    Client c;

    struct Clients* next;
    struct Clients* prev;

} Clients;
