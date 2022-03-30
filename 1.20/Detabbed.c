// Write a program detab that replaces tabs in the input with the proper
// number of blanks to space to the next tab stop. Assume a fixed set of
// tab stops, say every n columns. Should n be a variable or a symbolic parameter?

// If I understood correctly, where n is the width of a tab space, n should be a variable
// So that the user may change it to suit their needs

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void detabAndPrint(char from[], char to[], unsigned int tabWidth, int outputLen){
    // i is the counter for the input length, c is the counter for the output length
    int i = 0;
    int c = 0;
    // Keeps track of the offset required to fit the added characters replacing tab
    // And also for the escape backslash
    int escape = 0;
    while(c < outputLen){
        if (escape == 1){
            if (from[i] == '\t'){
                c--;
                to[c] = '\t';
            }
            // Handles every other character, and keeps the backslash
            // Not really neccessary as you could just escape the backslash
            // But that would be cumbersome
            // Although this has the added of making '\\r' the same as '\r' for example
            else{
                to[c-1] = from[i-1];
                to[c] = from[i];
            }
            escape = 0;
        }
        else if (from[i] == '\\'){
            escape = 1;
        }
        else if (from[i] == '\t'){
            unsigned int o = 0;
            for(o = o; o < tabWidth; o++){
                to[c + o] = ' ';
            }
            c = c + tabWidth - 1;
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

int countChars(unsigned int tabWidth, char exitChar, char text[]){
    char c;
    int i = 0;
    int offset = 0;
    int escape = 0;
    // The char array text[] is a one to one copy of everything from the stdin stream
    // The variable i is the length of the final text with all the extra spaces added
    // Escape characters and behaviour is also handled, given the proper length and original text
    // Offset gives the amount of added lenght to the output from converting tabs to spaces 
    while(((c=getchar()) != EOF)){
        if (c == exitChar && escape == 0){
            return (i+offset);
        }
        else if (escape == 1){
            if (c == exitChar){
                i--;
                text[i] = exitChar;
            }
            else if (c == '\t'){
                i--;
                text[i] = '\\';
                i++;
                text[i] = '\t';
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
        else if (c == '\t'){
            text[i] = c;
            offset = offset + tabWidth;
        }
        else if (c == '\\'){
            escape = 1;
        }
        else {
            text[i] = c;
        }
        i++;
    }
    return (i+offset);
}

int main(){
    unsigned int tabWidth = 4; // Default 4 naturally, only positive values
    char exitChar = '~';

    // Fseek to move the stdin pointer away from the inputted values
    // Max 1 digit and 1 char for the two values
    printf("Enter tab width in spaces (Default: 4): ");
    scanf("%1u", &tabWidth);
    fseek(stdin, 1, SEEK_CUR);
    printf("Default exit character is '~', \n");
    printf("Enter custom exit character (Can be escaped with '\\' prefix): ");
    scanf("%1c", &exitChar);
    fseek(stdin, 1, SEEK_CUR);
    // Both seeks "clear" out the stdin stream
    
    char *text = calloc(MAX, 1);
    // Find the size of the new text while also setting up the old one properly to prepare for detabbing
    // Add one for good measure
    int outputLen = countChars(tabWidth, exitChar, text) + 1;
    // Allocate memory for the new text
    char *detabbed = calloc((outputLen), 1);
    detabAndPrint(text, detabbed, tabWidth, outputLen);
    return 0;
}