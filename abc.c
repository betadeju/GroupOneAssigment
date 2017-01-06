#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Read the un(decommented) code from a file
char * read(char name[20]){
    char *file_contents;
    long input_file_size;
    FILE *input_file = fopen(name, "rb");
    fseek(input_file, 0, SEEK_END);
    input_file_size = ftell(input_file);
    rewind(input_file);
    file_contents = malloc(input_file_size * (sizeof(char)));
    fread(file_contents, sizeof(char), input_file_size, input_file);
    fclose(input_file);
    return file_contents;
    }


char * removeComments(char *prgm)
{
    int n = strlen(prgm);
    char *res=malloc(n* (sizeof(char)));
    *res="\0";

    // Flags to indicate that single line and multpile line comments
    // have started or not.
    int s_cmt = 0;
    int m_cmt = 0;
    int str=0;
    int i;

    // Traverse the given program
    for (i=0; i<n; i++)
    {
        //Check if it is a string
        if((prgm[i]=='"'||prgm[i]=='\'')&&!m_cmt&&!s_cmt){
            if(str==1)
                str=0;
            else
                str=1;
            }
        // If single line comment flag is on, then check for end of it
        if (s_cmt == 1 && prgm[i] == '\n')
            s_cmt = 0;

        // If multiple line comment is on, then check for end of it
        else if  (m_cmt == 1 && prgm[i] == '*' && prgm[i+1] == '/')
            m_cmt = 0,  i++;

        // If this character is in a comment, ignore it
        else if (s_cmt || m_cmt)
            continue;

        // Check for beginning of comments and set the approproate flags
        else if (prgm[i] == '/' && prgm[i+1] == '/'&&!str)
            s_cmt = 1, i++;
        else if (prgm[i] == '/' && prgm[i+1] == '*'&&!str)
            m_cmt = 1,  i++;

        // If current character is a non-comment character, append it to res
        else  strncat(res,&prgm[i],1);
    }
    return res;
}



//Write the decommented code to a file

void write(char *prgm,char decom_name[20]){

    FILE *output_file = fopen(decom_name, "wb");
    fwrite(prgm, sizeof(char), strlen(prgm), output_file);
    fclose(output_file);

    }



int main(){
    char *decom;
    char name[20];
    char decom_name[20];
    printf("Enter file to be Decommented\n");
    scanf("%s",name);
    printf("Enter file to save the decommented code\n");
    scanf("%s",decom_name);
    decom=read(name);
    decom=removeComments(decom);
    write(decom,decom_name);
    return 0;
    }
