#define MAX_FILE 20

struct node{
    char content[MAX_FILE];
    struct node *next;
};

typedef struct{
    struct node *head;
    int size;  
} queue;

