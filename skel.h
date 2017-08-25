#include <stdio.h>
#define SUCCESS 1
#define FAILURE 0

/***this is the structure of the hash table*****/
typedef struct hashtable
{
    struct hashtable *head;
}hash_t;

/****this is the structure of linked list which is connected to the hashtable***/
typedef struct node 
{
    char word[100];
    char filename[100];
    int filecount;
    int wordcount;
    struct node *next;
    struct node *head;
}node_t;

/****this is the structure for filetable***/
typedef struct linkedlist
{
    char file[100];
    int wordc;
    struct linkedlist *next;
}s_list;

 s_list *insert_first(char *data, s_list **head,int wordcount);    

int find_key(char ch);
