/*
NAME          : SAJITH P
DATE          : 12-03-2023
DESCRIPTION   : Inverted Search
SAMPLE INPUT  : ./a.out file1.txt file2.txt
SAMPLE OUTPUT : Read and validation successfull
                
                1.Create Datbase
		2.Display Database
		3.Search Database
		4.Save Database
		5.Upadate Database

		Enter your Choice :
	        (..etc)
*/
#include<stdio.h>                                         //HEADER FILES
#include<string.h>
#include<stdlib.h>
#include "main.h"

int main( int argc , char *argv[] )                      //MAIN FUNCTION
{
   
   Filelist *head = NULL;                                //DECLARING ONE HEAD POINTER
   Mainlist *hash[27];                                   //DECLARING ARRAY OF STRUCTURE POINTER
   int flag=0;
  
   for(int i=0;i<27;i++)                                 //TO MAKE THE HASH TABLE INDEX AS NULL
       hash[i] = NULL;
   if( Valdate_Arguments(argc,argv,&head) != SUCCESS)    //VALIDATING EACH ARGUMENTS
       return FAILURE;
   printf("\033[1;32m\nRead and validation successfull\n\033[0m\n");

   int Choice;
   char ch='y';
while(ch == 'y' || ch == 'Y')                           //LOOP FOR CONTINUED EXECUTION
{
   printf("\n1.Create Database\n2.Display Database\n");
   printf("3.Search Database\n4.Save Database\n");
   printf("5.Update Database\n\nEnter your Choice : ");
   scanf("%d",&Choice);

   switch(Choice)
   {
      case 1 :                                                          //CREATING DATABASE
               if(flag==0)                       
               {
                  if( Create_Database(&head,hash) != SUCCESS)
                      return 0;  
                  printf("\033[1;32m\ncreate database successfull\033[0m\n");
                  flag = 1;
                  break;
               }
               else
               {
                  printf("\n\033[1;31mDatabase is already Created!!\033[0m\n");
               }
               break;
      case 2 :                                                         //TO DISPLAY THE DATABASE                                       
               printf("\n  Index    Word    Filecount      Filename     wordcount\n");
              
               for(int i=0 ; i<27 ; i++)                               //LOOP TO DISPLAY HASH TABLE
               {
                  if(hash[i] != NULL)
                  {
                     Mainlist *temp = hash[i]; 
                     while( temp != NULL)                              //LOOP TO GET MAIN NODES
                     {   
                        int flag=0;
                        printf("%5d",i);
                        printf("%9s",temp->word);
                  
                        Sublist *temp2 = temp->sublink;
                        printf("%7d files  ",temp->file_count);

                        temp2 = temp->sublink;
                        while(temp2 != NULL)                           //LOOP TO GET SUB NODES
                        {  
                           flag++;
                           if(flag>1)
                              printf("\n\t\t\t     ");
                           printf("%13s",temp2->filename);
                           printf("%10d",temp2->word_count);
                           temp2=temp2->link;                          //UPDATING TEMP2  
                        }

                     printf("\n");
                     temp=temp->link;                                  //UPDATING TEMP          
                     }
                  }
               }
               break;
      case 3 :                                                         //TO SEARCH AN ELEMENT
               printf("\nEnter a word to be searched in the database : ");
               char word[20];
               int index,Flag=0;
               scanf("%s",word);
               
               if( word[0] >='A' && word[0] <= 'Z' )                   //TO FIND THE INDEX
                   index = word[0] - 65;
               else if( word[0] >= 'a' && word[0] <= 'z' )
                   index = word[0] - 97;
               else
                   index=26;

               if(hash[index] == NULL)                                 //TO CHECK THE INDEX IS NULL OR NOT
               {
                  printf("\n\033[1;31mSearch word is not available in the database\033[0m\n");
                  break;
               }

               Mainlist *temp = hash[index];
               while( temp != NULL)                                    //TO TRAVERESE THROUGH MAIN NODES
               {
                  if( strcmp(temp->word,word) == 0 )
                  {
                     printf("\nthe word %s is present in %d files\n",word,temp->file_count);
                     Sublist *temp2 = temp->sublink;
                     while(temp2 != NULL)                             //TO TRAVERSE THROUGH SUB NODES
                     {
                        printf("In file : %s %d times\n",temp2->filename,temp2->word_count);
                        temp2 = temp2->link;                          //UPDATING TEMP2
                     }
                     Flag=1;
                     break;
                  }
                  temp = temp->link;                                  //UPDATING TEMP
               }
               if(Flag == 0 )
               printf("\n\033[1;31mSearch word is not available in the database\033[0m\n");
               break;
       case 4 :                                                       //TO SAVE THE DATABASE INTO A FILE
               printf("Enter the filename to save database : ");
               char backup[20];
               scanf("%s",backup); 
               if( strstr( backup,"." ) == NULL )                     //VALIDATING THE FILENAME
                   strcpy(backup,strcat(backup,".txt"));
               else
                   strcpy(backup,strcat(strtok( backup,"." ),".txt")); 
                  
               FILE *Fptr = fopen(backup,"w");

               for(int i=0 ; i<27 ; i++)                              //TO TRAVERSE THROUGH ALL INDEXES
               { 
                  if(hash[i] != NULL)
                  {
                     Mainlist *temp = hash[i];
                     while( temp != NULL)                             //TO TRAVERSE THROUGH MAIN NODES
                     {  
                        fprintf(Fptr,"# %d;\n",i);
                        fprintf(Fptr,"%s;",temp->word);
                        fprintf(Fptr,"%d;",temp->file_count);
                  
                        Sublist *temp2 = temp->sublink;
                        while(temp2 != NULL)                          //TO TRAVERSE THROUGH SUB NODES
                        {  
                           fprintf(Fptr,"%s;",temp2->filename);
                           fprintf(Fptr,"%d;",temp2->word_count);
                           temp2=temp2->link;       
                        }
                     fprintf(Fptr,"#\n");
                     temp=temp->link;                  
                     }
                  }
               }
               fclose(Fptr);
               printf("\033[1;32m\nFile saved successfully\033[0m\n");
               break; 
       case 5 :                                                       //TO UPDATE THE DATABASE
               printf("Enter the back up file name : ");
               char saved[20];
               int flag=0,flag2=0;
               int ind;
               scanf("%s",saved);
               if( Check_File_Extension( saved ) != SUCCESS )        //TO VALIDATE THE GIVEN FILENAME
                   break;
               if( Check_File( saved ) != SUCCESS )
                   break;

                 char string[50];
               FILE *Fp = fopen(saved,"r");
                while( fscanf(Fp,"%s",string) != EOF )              //TO GET EACH STRING FROM BACKUP FILE
               {
                  if(string[0] == '#')                              //VALIDATING THE BACKUP FILE
                  {  
                     flag=1;
                     flag2=1;
                     continue;
                  }
                  if(flag2==0)
                  {
                     printf("\n\033[1;31mThe backup file is cannot be used\033[0m\n");
                     break;
                  }
                  if(flag == 1)
                  {  
                     ind =atoi(string);
                     flag = 0;
                     continue; 
                  }
                  
                  char* token;
                  char* rest = string;
                  int filecount,i=0,j=0;
                  token = strtok_r(rest, ";,\n", &rest);                 //GETTING EACH ELEMENTS FROM STRING
                  filecount = atoi(strtok_r(rest, ";", &rest));          //GETTING FILECOUNT
                  char *filename[filecount];
                  while(i<filecount)
                  {
                       filename[i] = malloc(20);                         //DYNAMIC MEMMORY ALLOACTION
                       i++;
                  }
                  i=0;
                  int wordcount[filecount];                       
                 
                  while(i<filecount)                                
                  {
                     filename[i] = strtok_r(rest, ";,\n", &rest);         //GETTING FILENMAES
                     wordcount[i] = atoi(strtok_r(rest, ";,\n", &rest));  //GETITNG WORDCOUNTS
                     i++;
                  }
                  i=0;
                  while( i<filecount )
                  {
                   j=0;
                   while(j<wordcount[i])
                   {
                     Storing_Into_Database(token,ind,filename[i],hash,&head);  //UPDATING DATABASE
                     j++;
                   }
                   i++;
                  }  
               }
               printf("\033[1;32m\nFile Backedup successfully\033[0m\n");
               break;    
   }
   printf("\nDo you want to continue(y/Y) : ");
   scanf(" %c",&ch);
}
return 0;
}

