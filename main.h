#define SUCCESS 1                   //MACRO DEFINITION
#define FAILURE 0                   //MACRO DEFINITION


typedef struct node                 //STRUCTURE FOR FILENAME LINKED LIST
{
    char File_Name[20];
    struct node *link;
}Filelist;

typedef struct main_node            //STRUCTURE FOR MAIN NODE
{
    int file_count;
    char word[20];
    struct main_node *link;
    struct sub_node  *sublink;

}Mainlist;

typedef struct sub_node             //STRUCTURE FOR SUB NODE
{  
    int word_count;
    char filename[20];
    struct sub_node *link;  

}Sublist;


int Valdate_Arguments(int argc,char *argv[],Filelist **head);    //FUNCTION DECLARATIONS
int Check_File_Extension( char * );
int Check_File( char * );

int Insert_at_Last( Filelist **,char * );

int Create_Database(Filelist **,Mainlist **);
int Extract_Words(char *,Mainlist **,Filelist **);
int Storing_Into_Database(char *word,int index,char *filename,Mainlist **,Filelist **);