#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

//结构体
typedef struct Node
{
    int date;
    struct Node* next;
}node;

struct headnode
{
    int size;
    node h_node;
}


void producer(void*arg)
{
    while(1)
    {
        node* newnode=(node*)malloc(sizeof(node))
            newnode->date=rand()%1000;

        newnode->next=head->h_ndoe.next
        
        sleep(rand()%3);
    }
    return NULL;
}

void customer(void *arg)
{

    while(1)
    {
        node *del=NULL;
        
    }
    return NULL;

}

int main(int argc, const char* argv[])
{
    pthread_t pid1,pid2;

    headnode *head=(headnode*)malloc(sizeof(headnode));
    head->h_node=NULL;
    head->size=0;
    
    pthread_create(&pid1,NULL,producer,NULL);
    pthread_create(&pid2,NULL,customer,NULL);

    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    return 0;
}
