#include<stdio.h>   //HEADER FILES
#include<string.h>
#include<stdlib.h>
#include"main.h"

int Valdate_Arguments(int argc,char *argv[],Filelist **head) //FUNCTION TO VALIDATE ARGUMENTS
{
    if( argc < 2 )
   {
     printf("\033[1;31mInsufficient no.of arguments\n\033[0m");
     return 0;
   }
   int i=1,flag=0;
   for( i=1 ; i<argc ; i++ )
   {
        if( Check_File_Extension( argv[i] ) != SUCCESS )  //CHECKING FILE EXTENSION
            continue;
        if( Check_File( argv[i] ) != SUCCESS )            //CHECKING FILE STATUS
            continue;
        if( Insert_at_Last( head,argv[i] ) != SUCCESS )   //ADDING ELEMENT INTO LINKED LIST
            continue;
        flag = 1;
   }
   if(flag == 1)
    return SUCCESS;
   else
    return FAILURE;
}
int Check_File_Extension( char *File_name )                        //FUNCTION TO CHECK FILE EXTENSION
{  
    if( strstr( File_name,"." ) == NULL )                          //TO CHECK EXTENSION IS PRESENT OR NOT
    {
        printf("\033[1;31m(%s) No Extension in the Filename\033[0m\n",File_name);
        return FAILURE;
    }
    if( strcmp( strstr( File_name,"." ),".txt" )  == 0 )          //TO CHECK THE EXTENSION IS .TXT OR NOT
    {
        return SUCCESS;
    }
    else
    {
        printf("\033[1;31m%s Extension is not Valid\n\033[0m",File_name);
        return FAILURE;
    }
} 
int Check_File( char *File_name )                              //FUNCTION TO CHECK THE STSTUS OF THE FILE
{
    FILE *Fptr = fopen( File_name,"r" );              
    if( Fptr == NULL )                                         //CHECKING FILE EXISTS OR NOT
    {
        printf("\033[1;31m%s is not Exists\n\033[0m",File_name); 
        return FAILURE;
    }
    fseek( Fptr,0,SEEK_END );
    if( ftell(Fptr) == 0 || ftell(Fptr) == 1 )               //CHECKING FILE IS EMPTY OR NOT
    {
        printf("\033[1;31m%s is Empty\n\033[0m",File_name);
        return FAILURE;
    }
    return SUCCESS;
}

int Insert_at_Last( Filelist **head,char *File_name )   //FUNCTION TO INSERT AN ELEMENT AT LAST   
{
    Filelist *new = malloc( sizeof(Filelist) );         //DYNAMIC MEMMORY ALLOCATION
    if( new == NULL )
        return FAILURE;
    
    strcpy( new->File_Name,File_name );                 //NEW NODE CREATION
    new->link = NULL;

    Filelist *temp = *head;                             //STRUCTURE POINTER DECLARATION  

    if( temp == NULL )                                  //TO CHECK WHETHER THE LIST IS EMPTY OR NOT
    {
        *head = new;                                    //IF YES, ADDING NEW NODE ADDRESS IN 'HEAD'
        return SUCCESS; 
    }
    while( temp->link != NULL )                         //TO GET THE LAST ELEMENT
    {
        if( strcmp( temp->File_Name,File_name ) == 0 )
        {
            printf("\033[1;31m\nDuplicate files are present\n\033[0m");
            return FAILURE;
        }
           temp = temp->link;                           //UPDATING LINK VALUE
    }
    if( strcmp( temp->File_Name,File_name ) == 0 )
    {
        printf("\033[1;31m\nDuplicate files are present\n\033[0m");
        return FAILURE;
    }
        temp->link = new;                               //LINKING THE NEW NODE ADDRESS

    return SUCCESS;
}
int Create_Database(Filelist **head, Mainlist **hash)  //FUNCTION TO CREATE DATABASE
{
    long int size = 0;
    Filelist *temp = *head;
    while( temp != NULL )
    {
      Extract_Words(temp->File_Name,hash,head); 
      temp = temp->link;
    }
    return SUCCESS;
} 

int Extract_Words(char *filename,Mainlist **hash ,Filelist **head)  //FUNCTION EXTRACT WORDS FROM FILE
{
    FILE *Fptr = fopen( filename,"r" );
    char word[20] ;
    int index;
    
    while( fscanf(Fptr,"%s",word) != EOF )                         //EXTRACTING EACH STRINGS
    {
        if( word[0] >='A' && word[0] <= 'Z' )                      //TO FIND THE INDEX NUMBER
            index = word[0] - 65;
        else if( word[0] >= 'a' && word[0] <= 'z' )
            index = word[0] - 97;
        else
            index=26;

        Storing_Into_Database(word,index,filename,hash,head);      //FUNCTION CALL TO STORE INTO DATABASE
    }
    return SUCCESS;
}
int Storing_Into_Database(char *word,int index,char *filename,Mainlist **hash,Filelist **head) //FUNCTION TO STORE INTO DATABASE
{
    if(hash[index] == NULL)                                 //IF INDEX IS NULL
    {      
        Mainlist *main = malloc(sizeof(Mainlist));          //CREATING NEW MAIN NODE
        main->file_count = 1;
        strcpy(main->word,word);
        main->link = NULL;

        Sublist *sub = malloc(sizeof(Sublist));             //CREATING NEW SUB NODE
        sub->word_count = 1;
        strcpy(sub->filename,filename);
        sub->link = NULL;

        main->sublink = sub;                                //LINKING
        hash[index] = main;                                 //LINKING
    }
    else if(hash[index] != NULL )                           
    { 
        Mainlist *temp = hash[index];                       //CREATING TEMP POINTER
 
        while( temp->link != NULL )                         //TO GET THE LAST MAIN NODE IN AN INDEX
        {    
            if( strcmp(temp->word,word) == 0 )              //IF WORDS FOUND TO BE EQUAL
            {   
                Sublist *temp2  = temp->sublink;
                Sublist *prev   = temp->sublink;
                while(temp2 != NULL)                        //TO GET THE LAST SUB NODE 
                {
                    if( strcmp(filename,temp2->filename) == 0)    
                    {
                        (temp2->word_count)++;             //INCREMENTING WORD COUNT
                        return 0;
                    }
                    prev = temp2;
                    temp2 = temp2->link;
                 
                }
                Sublist *sub = malloc(sizeof(Sublist));   //CREATING ON SUB NODE
                sub->word_count = 1;
                strcpy(sub->filename,filename);
                sub->link = NULL;
                prev->link = sub;
                (temp->file_count)++;
                return 0;
            }
            temp = temp->link;
        }
        if( strcmp(temp->word,word) == 0 )
        {   
            Sublist *temp2  = temp->sublink;                    //CREATING TEMP POINTER
            Sublist *prev   = temp->sublink;                    //CREATING TEMP POINTER
            while(temp2 != NULL)
            {
                if( strcmp(filename,temp2->filename) == 0)
                {
                    
                    (temp2->word_count)++;                    //INCREMENTING WORD COUNT
                    return 0;
                }
                    prev = temp2;
                    temp2 = temp2->link;
            }
            Sublist *sub = malloc(sizeof(Sublist));         //CREATING ON SUB NODE
            sub->word_count = 1;
            strcpy(sub->filename,filename);
            sub->link = NULL;
            prev->link = sub;
            (temp->file_count)++;
            return 0;   
        }
        Mainlist *main = malloc(sizeof(Mainlist));          //CREATING NEW MAIN NODE
        main->file_count = 1;
        strcpy(main->word,word);
        main->link = NULL;
     
        Sublist *sub = malloc(sizeof(Sublist));             //CREATING ON SUB NODE
        sub->word_count = 1;
        strcpy(sub->filename,filename);
        sub->link = NULL;

        main->sublink = sub;                                //LINKING
        temp->link = main;                                  //LINKING
     
    }
    
}

     
