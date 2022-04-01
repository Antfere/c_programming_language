// Write a program entab that replaces strings of blanks by
// the minimum number of tabs and blanks to achieve the same spacing. Use
// the same tab stops as for detab. When either a tab or a single blank would
// suffice to reach a tab stop, which should be given preference?

// In the case of multiple tab stops worth of blanks, the program should first convert from left to right
// The applicable amount of tabs, then finish up with spaces, to properly emulate a conversion between the two
// Assuming the user was trying to emulate tabs with spaces before running it through this program to finalize the process

// Same tab width selection as detab
// Same exit character setup
// Same split counters between old and new, except now the new text will shrink is bytes
// Similar setup by generating original text first, then counting, then processing and printing

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

    // Just in case
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
    entabAndPrint(text, detabbed, tabWidth, outputLen);
    return 0;
}