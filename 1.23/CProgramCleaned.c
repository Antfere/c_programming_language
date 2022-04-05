









#define example 1 







int main(){
  
    int i = 0;
  
  char str[] = "//";
  char str2[] = "/*   */";
  char c = 'g';
}



#pragma comments enable// Do not delete
// I want this comment to stay
#pragma comments disable

#pragma comments enable/*
Do not delete

*/
/* 
This one should also stay
*/
#pragma comments disable








"
/* */
#pragma comments enable // Comment
#pragma comments disable // Delete
/* */
"






     #pragma      comments       enable // This is a directive

// This comment will stay
#pragma      comments     disable


#pragma comments enable
"// Comment"
#pragma comments disable
"// Comment"
 

 #pragma comments
 #pragma comments disabl
 #pragma comments

 #pragma com
 #pragma com"ents enable"
 #pragma "comments enable"
 #pragma 'comments enable'
"#pragma 'comments enable'"

 #pragma comments disable

"\" // "



















#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void entabAndPrint(char from[], char to[], int tabWidth, int outputLen){
    int i = 0;
    int c = 0;
    int spaces = 0;
    while (c < outputLen){
        if (from[i] == ' '){
            for(int s = 0; s < tabWidth; s++){
                if (from[i + s] == ' '){
                    spaces++;
                    if (spaces == tabWidth){
                        to[c] = '\t';
                        i = i + tabWidth - 1;
                        spaces = 0;
                    }
                }
                else {
                    spaces = 0;
                    to[c] = from[i];
                    break;
                }
            }
        }
        else {
            to[c] = from[i];
        }
        i++;
        c++;
    }
    printf("%s", to);
    printf("Len: %d", c);
}

int countChars(int tabWidth, char exitChar, char text[]){
    char c;
    int i = 0;
    int spaces = 0;
    int offset = 0;
    int escape = 0;

    while(((c=getchar()) != EOF)){
        if (c == exitChar && escape == 0){
            for (int s = 0; s < i; s++){
                if (text[s] == ' '){
                    spaces = spaces + 1;
                    if (spaces == tabWidth){
                        offset = offset + tabWidth - 1;
                        spaces = 0;
                    }
                }
                else{
                    spaces = 0;
                }
            }
            return (i-offset);
        }
        else if (escape == 1){
            if (c == exitChar){
                i--;
                text[i] = exitChar;
            }
            else if (c == '\\'){
                i--;
                text[i] = '\\';
            }
            else {
                text[i-1] = '\\';
                text[i] = c;
            }
            escape = 0;
        }
        else if (c == '\\'){
            escape = 1;
        }
        else {
            text[i] = c;
        }
        i++;
    }

    
    for (int s = 0; s < i; s++){
        if (text[s] == ' '){
            spaces = spaces + 1;
            if (spaces == tabWidth){
                offset = offset + tabWidth - 1;
            }
        }
        else{
            spaces = 0;
        }
    }
    return (i-offset);
}

int main(){
    unsigned int tabWidth = 4; 
    char exitChar = '~';

    
    
    printf("Enter tab width in spaces (Default: 4): ");
    scanf("%1u", &tabWidth);
    fseek(stdin, 1, SEEK_CUR);
    printf("Default exit character is '~', \n");
    printf("Enter custom exit character (Can be escaped with '\\' prefix): ");
    scanf("%1c", &exitChar);
    fseek(stdin, 1, SEEK_CUR);
    
    
    char *text = calloc(MAX, 1);
    
    
    int outputLen = countChars(tabWidth, exitChar, text) + 1;
    
    char *detabbed = calloc((outputLen), 1);
    entabAndPrint(text, detabbed, tabWidth, outputLen);
    return 0;
}





#pragma comments disable






























#include <stdio.h>
#include <stdlib.h>

int main(){
    int comment = 0; 
    int quotation = 0; 
    int directive = 0; 
    char c;
    char commentsEnable[22] = "pragma comments enable"; 
    char commentsDisable[23] = "pragma comments disable"; 

    FILE *CProgram = fopen("CProgram.c", "r+");
    FILE *CProgramCleaned = fopen("CProgramCleaned.c", "w+");
    c = fgetc(CProgram);
    while(c != EOF){
        
        if (c == '#'){
            
            if (directive == 0){
                char *buffer = calloc(22, sizeof(char)); 
                int extendedSpacesCounter = 0;
                int i = 0;
                fputc(c, CProgramCleaned);
                for (i = i; i < 22; i++){
                    c = fgetc(CProgram);
                    
                    if (c == '/' || c == '\'' || c == '\"'){
                        break;
                    }

                    if ((c == '\t' || c == ' ') && (commentsEnable[i - 1] == ' ')){
                        extendedSpacesCounter++;
                        
                        buffer = realloc(buffer, (extendedSpacesCounter + 22));
                        buffer[i + extendedSpacesCounter] = c;

                        
                        
                        
                        
                        i--;
                    }
                    else if (c == commentsEnable[i + extendedSpacesCounter]){
                        buffer[i + extendedSpacesCounter] = c;
                    }
                    
                    else {
                        
                        
                        
                        
                        fputs(buffer, CProgramCleaned);
                        fputc(c, CProgramCleaned);
                        break;
                    }
                }
                if (c == '/' || c == '\'' || c == '\"'){

                    fputs(buffer, CProgramCleaned);
                    free(buffer); 
                    
                    
                    continue;
                }
                
                
                if (i == 22){
                    fputs(buffer, CProgramCleaned);
                    directive = 1;
                }
                free(buffer); 
            }
            
            else{
                char *buffer = calloc(23, sizeof(char)); 
                int extendedSpacesCounter = 0;
                int i = 0;
                fputc(c, CProgramCleaned);
                for (i = i; i < 23; i++){
                    c = fgetc(CProgram);
                    
                    if ((c == '\t' || c == ' ') && (commentsDisable[i - 1] == ' ')){
                        extendedSpacesCounter++;
                        
                        buffer = realloc(buffer, (extendedSpacesCounter + 23));
                        buffer[i + extendedSpacesCounter] = c;


                        
                        
                        i--;
                    }
                    else if (c == commentsDisable[i + extendedSpacesCounter]){
                        buffer[i + extendedSpacesCounter] = c;
                    }
                    
                    else {
                        
                        
                        fputs(buffer, CProgramCleaned);
                        fputc(c, CProgramCleaned);
                        break;
                    }
                }
                
                if (i == 23){
                    fputs(buffer, CProgramCleaned);
                    directive = 0;
                }
                free(buffer); 
            }
        }
        else if (directive == 1){
            fputc(c, CProgramCleaned);
        }
        else if (c == '/'){
            char *buffer = malloc(3); 
            buffer[0] = '/';
            c = fgetc(CProgram);
            
            if ( c == '/'){
                
                
                while((c = fgetc(CProgram)) != '\n' && c != EOF){
                    
                }
                if (c == '\n'){
                    
                    fputc(c, CProgramCleaned);
                }
            }
            
            else if (c == '*'){
                
                comment = 1;
                while(comment == 1){
                    c = fgetc(CProgram);
                    if (c == EOF){
                        break;
                    }
                    
                    else if (c == '*' && ((c = fgetc(CProgram))) == '/') {
                        comment = 0;
                    }
                    else{
                        
                    }
                }
            }
            
            
            else{
                buffer[1] = c;
                
                fputs(buffer, CProgramCleaned);
                
                free(buffer);
            }
        }
        else if (c == '\''){
            quotation = 1;
            
            fputc(c, CProgramCleaned);
            while(quotation == 1){
                c = fgetc(CProgram);
                if (c == EOF){
                    break;
                }
                if (c == '\\'){
                    
                    fputc(c, CProgramCleaned);
                    
                    c = fgetc(CProgram);
                    fputc(c, CProgramCleaned);
                }
                else if (c == '\''){
                    
                    fputc(c, CProgramCleaned);
                    quotation = 0;
                }
                else {
                    
                    fputc(c, CProgramCleaned);
                }
            }
        }
        else if (c == '\"'){
            quotation = 1;
            
            fputc(c, CProgramCleaned);
            while(quotation == 1){
                c = fgetc(CProgram);
                if (c == EOF){
                    break;
                }
                if (c == '\\'){
                    
                    fputc(c, CProgramCleaned);
                    
                    c = fgetc(CProgram);
                    fputc(c, CProgramCleaned);
                }
                else if (c == '\"'){
                    
                    fputc(c, CProgramCleaned);
                    quotation = 0;
                }
                else {
                    
                    fputc(c, CProgramCleaned);
                }
            }
        }
        
        else if (c != '#' && c != '\'' && c != '\"'&& c != '#') {
            fputc(c, CProgramCleaned);
        }

        
        if (c == EOF){
            break;
        }

        c = fgetc(CProgram);

    }
    return 0;
}











#pragma comments dis/