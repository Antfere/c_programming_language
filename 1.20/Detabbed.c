// Write a program detab that replaces tabs in the input with the proper
// number of blanks to space to the next tab stop. Assume a fixed set of
// tab stops, say every n columns. Should n be a variable or a symbolic parameter?

// If I understood correctly, where n is the width of a tab space, n should be a variable
// So that the user may change it to suit their needs

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void detabAndPrint(char from[], char to[], unsigned int tabWidth, char exitChar, int charLen){
    int i = 0;
    // Keeps track of the offset required to fit the added characters replacing tab
    // And also for the escape backslash
    int offset = 0;
    int c = 0;
    int escape = 0;
    while(from[i] != exitChar){
        if (escape == 1){
            if (from[i] == exitChar){
                to[i + offset] = from[i];
            }
            else if (from[i] == '\\'){
                to[i + offset] = from[i];
            }
            // This else is not really neccessary, but somewhat more user friendly
            else{
                to[i + offset - 1] = from[i - 1];
                to[i + offset] = from[i];
            }
        }
        else if (from[i] == '\\'){
            escape = 1;
        }
        else if (from[i] == '\t'){
            for(unsigned int o = 0; o < tabWidth; o++){
                to[i + o + offset] = ' ';
            }
            offset = offset + tabWidth;
        }
        else {
            to[i + offset] = from[i];
        }
        i++;
    }
    while(c < charLen){
        printf("%c", to[c]);
        c++;
    }
}

int countChars(unsigned int tabWidth, char exitChar, char text[]){
    char c;
    int i = 0;
    int offset = 0;
    int escape = 0; 
    while(((c=getchar()) != EOF) && (c != exitChar)){
        if (escape == 1){
            if (c != exitChar || c != '\\'){
                text[i] = c;
                i++;
            }
            text[i] = c;
            escape = 0;
        }
        else if (c == '\t'){
            text[i] = c;
            offset = offset + tabWidth;
            i++;
        }
        else if (c == '\\'){
            escape = 1;
            i++;
        }
        else {
            text[i] = c;
            i++;
        }
    }
    text[i+1] = '!';
    return (i+offset+1);
}

int main(){
    unsigned int tabWidth = 4; // Default 4 naturally, only positive values
    char exitChar;
    printf("Enter tab width in spaces (Default: 4): ");
    scanf("%u", &tabWidth);
    fseek(stdin, 2, SEEK_CUR);
    printf("Enter exit character (Can be escaped with '\\' prefix): ");
    scanf("%c", &exitChar);
    fseek(stdin, 2, SEEK_CUR);
    char *text = calloc(MAX, 1);
    int charLen = countChars(tabWidth, exitChar, text);
    // Allocate memory, plus one for good measure 
    char *detabbed = calloc((charLen), 1);
    detabAndPrint(text, detabbed, tabWidth, exitChar, charLen);
    return 0;
}