#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "skel.h"


int insert_in_hash(char *buff, hash_t *hashtable, int k)
{
   
    char newbuff[1000];
    char tempbuff[1000];
    static int key = 0;
    int length = 0;
    int wordcount = 0;
    int filecount = 0;
    char wc[100];
    char fc[100];
    int i = 0;
    int idx = 0;
    char *sptr;
    node_t *ptr = NULL;
    node_t *temp = NULL; 
    s_list *new = NULL;

    if (buff[0] == '$')
    {
    strcpy(newbuff, &buff[1]);
    key = find_key(newbuff[0]);
    length = strlen(newbuff);
    /***this will separate the file count***/
    for (i = 0; newbuff[i] != '\0'; i++)
    {
	if (newbuff[i] == '#')
	{
	    i++;
	    do
	    {
		fc[idx] = newbuff[i];
		i++;
		idx++;
	    }while(newbuff[i] != '@');
	    fc[idx] = '\0';
	    
	}

    }
    //puts(fc);
    filecount = atoi(fc);
    //puts(newbuff);

    /*****this will seperate the wordcount****/

    sptr = strchr(newbuff, '@');
    strcpy(tempbuff, sptr+1);
     wordcount = atoi(tempbuff);
     //puts(newbuff);


   /**************************************/    
    
    
    for (i = 0; newbuff[i] != '\0'; i++)
    {
	if (newbuff[i] == '#')
	{
	    newbuff[i] = '\0';
           break;

	}


    }
  
       
    /*****insert the node and connect to the hashtable****/

    if (hashtable[key].head == NULL)
    {
	ptr = malloc(sizeof(node_t));
	strcpy(ptr -> word, newbuff);
	ptr -> wordcount = wordcount;
	ptr -> filecount = filecount;
	ptr -> next = NULL;
	hashtable[key].head = (hash_t *)ptr;

    }

    else
    {
	ptr = malloc(sizeof(node_t));
	strcpy(ptr -> word, newbuff);
	ptr -> wordcount = wordcount;
	ptr -> filecount = filecount;
	ptr -> next = (node_t *)hashtable[key].head;
	hashtable[key].head = (hash_t *)ptr;
     }

    }
    else
    {
	sptr = strchr(buff, '#');

	strcpy(tempbuff, sptr + 1);

	wordcount = atoi(tempbuff);
	printf("wc is %d\n", wordcount);

	for (i = 0; buff[i] != '\0'; i++)
	{
	    if(buff[i] == '#')
	    {
		buff[i] = '\0';
		break;
	    }

	}

	if (hashtable[key].head != NULL)
	{
	    ptr = (node_t *)hashtable[key].head;
	    if (ptr -> head == NULL)
	    {
		new = malloc(sizeof (s_list));
		new -> wordc = wordcount;
	        strcpy(new -> file, buff);	
		new -> next = NULL;
		ptr -> head  = (node_t *)new;
	    }

	    else
	    {
		new = malloc(sizeof(s_list));
		new -> wordc = wordcount;
                strcpy(new -> file, buff);	
		new -> next = (s_list *)ptr -> head;
		ptr -> head = (node_t *)new;
	    }



	    
       }
     
    	


	
	

    }	
  
    
   

   
}
/****this function is to get word******/

int get_word(FILE *fp, hash_t *hashtable)
{
    char ch;
    char buff[100];
    int idx = 0;
    int k = 0;
    int i = 0;

    
    
    while ((ch = fgetc(fp)) != ';')
    {
	buff[idx] = ch;
	idx++;
    }

    buff[idx] = '\0';


    if (buff[0] == '$')
    {
    insert_in_hash(buff, hashtable, k);  
    }

    else
    {
	insert_in_hash(buff, hashtable, k);
    }

}






/****this function is to about update database****/
int update_database(hash_t *hashtable)
{

    /****file operation*****/
    FILE *fp;

    fp = fopen("backup.txt", "r");

    /*****no file*****/
    if (fp == NULL)
    {
	printf("there is no backup\n");
    }

    char line[1000];
    char buff[100];
    char ch;
    int idx = 0;
    int i = 0;

    fseek(fp , 0L, SEEK_SET);

    while ((ch = fgetc(fp)) != EOF)
    {
	if (ch == ';')
	{
	    idx = idx + 1;
	}
    }

    fseek(fp , 0L, SEEK_SET);

    for (i = 0; i < idx; i++)
    {
	get_word(fp, hashtable);
    }



    
    
}




/****this function to search in the database*****/
node_t *search_data(hash_t *hashtable, char *string)
{
    int key = 0;
    key = find_key(string[0]);

    /******if the hashtable is not created****/
    if (hashtable[key].head == NULL)
    {
	return NULL;
    }

    /******this is temporary pointer***/
    node_t *temp = (node_t *)hashtable[key].head;

    /******this is moving inside the file****/
    while (temp != NULL)
    {

	if (strcmp(temp -> word, string) == 0)
	{
	    return temp ;
	}
	temp = temp -> next;


    }

    return NULL;




}




/****to create filetable******/
s_list *insert_list(char *filename, node_t *head)
{
    s_list *ptr = (s_list *)head;

    if (head == NULL)
    {
	s_list *new = malloc(sizeof(s_list));
	strcpy(new -> file, filename);
	new -> wordc = 1;
	new -> next = NULL;
	return new;
    }

    else
    {
        while (ptr -> next != NULL)
	{
	    ptr = ptr -> next;
	}
	
	if (strcmp(ptr -> file , filename) == 0)
	{
	    ptr -> wordc = ptr -> wordc + 1;

        }

	else
	{
	while (ptr -> next != NULL)
	{
	    ptr = ptr -> next;
	}
	s_list *new1 = malloc(sizeof(s_list));
	strcpy(new1 -> file, filename);

	new1 -> wordc = 1;
	new1 -> next = NULL;
	ptr -> next = new1;
	}
	



    }

}





/***open the files and insert to the database****/
int open_file(int no, char **argv, hash_t *hashtable)
{
    int i;
    /***include file pointers****/
    FILE *fp;
    for (i = 1; i <= (no - 1); i++)
    {
	fp = fopen(argv[i] , "r");

	create_database(fp, hashtable, argv[i]);
    }
    

}

/****this function is about create the database*****/
int create_database(FILE *fp, hash_t *hashtable, char *filename)
{
    fseek(fp , 0L, SEEK_SET);
    char buff[100];
    char ch;
    int k = 0;
    int word_flag = 0;
    int idx = 0;

    /***clear the buffer*****/
    memset(buff, '\0', sizeof(buff));

    /****move the file pointer to the end of document****/
    while ((ch = fgetc(fp)) != EOF)
    {

	/***if it is character***/
	if ((ch >= 65 && ch <=  90) || (ch >= 97 && ch <= 122))
	{
          
	  /***set the wordflag*****/
	  if (word_flag == 0)
	  {
	      /***findkey*****/
	      k = find_key(ch);
	      word_flag = 1;

	  }
	  buff[idx] = ch;
	  idx++;


	}
	else
	{
	   
	    word_flag = 0;
	    idx = '\0';
	    hash_insert(buff,k, hashtable, filename);
	    //printf("key is %d\n", k);
	    /***reset the iteration****/
	    idx = 0;
	    /****clear the buffer***/
	    memset(buff , '\0', sizeof(buff));
	    
	}

	
      //printf("%c\n", ch);
    }

    fclose(fp);

}

/***this function is about insert the hash node******/
int hash_insert(char *buff, int key, hash_t *hashtable, char *filename)
{


         

    int present = 0;

    /***first to check if there is no node is present***/
    node_t *new  = NULL;

    s_list *head = NULL;

    /***there is no node in the hashtable****/
    if (hashtable[key].head == NULL)
    {
	new = malloc(sizeof(node_t));
	new -> filecount = 1;
	new -> wordcount = 1;
	strcpy(new -> word, buff);
	strcpy(new -> filename, filename); 
        new -> head = (node_t *)insert_list(filename, new -> head); 
	new -> next = NULL;
	 

	hashtable[key].head = (hash_t *)new;
	return SUCCESS;
    }

    
    
	node_t *ptr = (node_t *)hashtable[key].head;
	s_list *temp;

	/****search the list*****/
	while (ptr  != NULL)
	{
	    
	

	if (strcmp(ptr -> word, buff) == 0)
	
	{
	   
	    /***reset the filename ***/
	    if (strcmp(ptr -> filename, filename) != 0)
	    {
		
		ptr -> wordcount = ptr -> wordcount + 1;

		strcpy(ptr -> filename, filename);
		ptr -> filecount = ptr -> filecount + 1;
                  
                  insert_list(filename, ptr -> head);
   	     

              present = 1;
	     //head =  (s_list *)ptr -> head;

	    }

	    else
	    {
		 ptr -> wordcount = ptr -> wordcount + 1;
		 insert_list(filename, ptr -> head);
		 present = 1;
               
	//ptr -> head = (node_t *)insert_first(filename, &head, ptr -> wordcount);

	    //head =  (s_list *)ptr -> head;
           }

 
	 }

	ptr = ptr -> next;

	}

	if (present == 0)
	{

	new = malloc(sizeof(node_t));
	new -> filecount = 1;
	new -> wordcount = 1;
	strcpy(new -> word, buff);
	strcpy(new -> filename, filename); 
	new -> next = (node_t *)hashtable[key].head;
	new -> head = (node_t *)insert_list(filename, new -> head); 

	hashtable[key].head = (hash_t *)new;

        

	}



}

/****this will returns the key of word****/
int find_key(char ch)
{
    int key;
    /**to find the key****/
    if(isupper(ch))
    {
	key = ch - 65;
	//printf("%d", key);
    }

    else if (islower(ch))
    {
	key = ch - 97;
	//printf("%d", key);
    }
  return key;
}

/****printing the hashtable****/
int print_hash(hash_t *hashtable, int size)
{
    int i = 0;
    int idx = 0;
    node_t *ptr;
    s_list *temp;

    /***if the hashtable is null means****/
    if (hashtable == NULL)
	printf("hashtable is not created\n");

    else
    {
	/***print all the nodes which is presented inside the table***/
	for (idx = 0; idx < size; idx++)
	{

	    if (hashtable[idx].head != NULL)
	    {
		ptr = (node_t *)hashtable[idx].head;

		while (ptr != NULL)
		{
		    printf("%s;files:%d;wordcount:%d;", ptr -> word, ptr -> filecount, ptr -> wordcount);
		    if (ptr -> head != NULL)
		    {
		
			
			temp = (s_list *)ptr -> head;
			while(temp != NULL)
			{
			
			    printf("filename:%s;count:%d;", temp -> file, temp -> wordc);

			    temp = temp -> next;
			}
		    }

                   printf("\n");

		    ptr = ptr -> next;
		}
	    }
	}

	
    }

}




/****printing the hashtable****/
int print_inside(hash_t *hashtable, int size)
{
    int i = 0;
    int idx = 0;
    node_t *ptr;
    s_list *temp;

    FILE *fp;
    fp = fopen("backup.txt", "w");

    /***if the hashtable is null means****/
    if (hashtable == NULL)
	printf("hashtable is not created\n");

    else
    {
	/***print all the nodes which is presented inside the table***/
	for (idx = 0; idx < size; idx++)
	{

	    if (hashtable[idx].head != NULL)
	    {
		ptr = (node_t *)hashtable[idx].head;

		while (ptr != NULL)
		{
		    fprintf(fp ,"$%s#%d@%d;", ptr -> word, ptr -> filecount, ptr -> wordcount);
		    if (ptr -> head != NULL)
		    {
		
			
			temp = (s_list *)ptr -> head;
			while(temp != NULL)
			{
			
			    fprintf(fp ,"%s#%d;", temp -> file, temp -> wordc);

			    temp = temp -> next;
			}
		    }

                   
		    

		    ptr = ptr -> next;
		}
	    }
	}

	
    }

    fclose(fp);

}


