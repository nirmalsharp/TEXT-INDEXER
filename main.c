#include <stdio.h>
#include <stdlib.h>
#include "skel.h"

/***main driver program which is for text indexing*****/
int main(int argc, char *argv[])
{

    /*****menu option******/
    int option;
    char string[100];


    /***hashtable creation***/
    hash_t *hashtable[26] = {NULL};
    node_t *check = NULL;
    s_list *trav = NULL;
    int backup = 0;
    int create_flag = 0;

    if (argc < 2)
    {
	printf("GIVE THE FILE ARGUMENTS\n");
	return FAILURE;
    }

    while (1)
    {
    printf("********menu*******\n");
    printf("1.CREATE DATABASE\n");
    printf("2.SEARCH DATABASE\n");
    printf("3.DISPLAY DATABASE\n");
    printf("4.SAVE DATABASE\n");
    printf("5.UPDATE DATABASE\n");
    printf("6.EXIT\n");

    printf("enter an option\n");
    scanf("%d", &option);

    switch(option)
    {
	case 1:
	    if (backup == 0)
	    {
	    open_file(argc, argv, hashtable);
	    create_flag = 1;

	    
	    }
	    else
	    {
		printf("database already created\n");
	    }
	    break;

	case 2:
	    printf("enter the string:");
	    scanf("%s", string);
            check = (node_t *)search_data(hashtable, string);
	    if (check == NULL)
	    {
		printf("NO SEARCH FOUND\n");

	    }

	    else
	    {
		printf("******word found********\n");
		printf("word found at %d files\n", check -> filecount);
		printf("count of words %d\n", check -> wordcount);
		trav = (s_list *)check -> head;
		while (trav != NULL)
		{
		    printf("filenames are %s\n", trav -> file);
		    trav = trav -> next;
		}


	    }
	    break;

	
	
	case 3:
	    print_hash(hashtable, 26);
	    break;

	case 4:
	    print_inside(hashtable, 26);
	    break;


	case 5:
	     if (create_flag == 0)
	     {
	     update_database(hashtable);
	     backup = 1;
	     }
	     else
	     {
		 printf("database is already created\n");
	     }
	     break;
	     
	
	case 6:
	    system("clear");
	    exit(0);
	    break;


         default:
	    printf("give valid option\n");
	    break;


    }



    }



}

