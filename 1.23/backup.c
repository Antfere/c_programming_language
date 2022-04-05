// Write a program to remove all comments from a C program.
// Don’t forget to handle quoted strings and character constants properly.
// C comments don’t nest.

// Inline comment

// // "Nested" comment

/* multi line comment */

#define example 1 // Comment after compiler directive

/*
int main(){

}

// Multi multi line comments
*/

/*

*/
/*

*/
/*

*/

int main(){
  //**********// 
    int i = 0;//
  //**********//
  char str[] = "//";
  char str2[] = "/*   */";
  char c = 'g';
}

// This is an example exception directive

#pragma comments enable// Do not delete
// I want this comment to stay
#pragma comments disable// Delete
/*
Delete
*/
#pragma comments enable/*
Do not delete

*/
/* 
This one should also stay
*/
#pragma comments disable/* Delete */

// #pragma comments enable
// #pragma comments disable

/*
#pragma comments enable
// Should be deleted
#pragma comments disable
*/

// Nested quotations/directives/comments:

"
/* */
#pragma comments enable // Comment
#pragma comments disable // Delete
/* */
"

// #pragma comments enable
// // Comment
// /* Comment */
// #pragma comments disable

     #pragma      comments       enable // This is a directive

// This comment will stay
#pragma      comments     disable


#pragma comments enable
"// Comment"
#pragma comments disable
"// Comment"
 // Delete

 #pragma comments
 #pragma comments disabl
 #pragma comments

 #pragma com//ents enable
 #pragma com"ents enable"
 #pragma "comments enable"
 #pragma 'comments enable'
"#pragma 'comments enable'"

 #pragma comments enable

"\" // "

// Past program as extra dummy input with comments kept
// *************************************************************************************************


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

// The comment program in here aswell:
// ****************************************************************

// Self referenced program:
#pragma comments disable

// Write a program to remove all comments from a C program.
// Don’t forget to handle quoted strings and character constants properly.
// C comments don’t nest.

// It needs to recognize double forward slashes
// And forward slashes with asterisks even after dummy text in the same line
// It can work similar to the look ahead system of the entab and detab
// Flip a bool when it hits a comment directive, flip it back depending on the situation
// And flip a quotation bool which negates the comment checks
// Directives can also disable both quotation and comments checks entirely
// However both comments and quotations must disable directives...
// Effectively all three need to disable the other two until the bool which controls them flips again

// For manipulating the actual text I won't go down the route of the entab and detab programs
// Instead of copying the full original and using it as a cached reference
// It will instead check if the current character is the start of a specific comment/quotation/directive syntax
// If it is it will continue, but it will have the sense to save every char that follows which conforms to the 
// Comment/quotation/directive syntax to a small buffer which it will only get rid of once the full syntax is read
// If it dosen't get the full pattern it will paste the buffer into the file
// I think this method will save memory and is particularly suitable for file reads/writes, would be much harder if messing with char arrays like in entab/detab

// Setup for recognition and buffering for relatively long directives is as follows:
// If character is equal to "#", then save to buffer, and start pulling new chars while simultaneously looping through a set char array
// Aslong as the characters in the array match up with the character being pulled at the same position, the buffer expands
// Once the end is reached bool is flipped, and buffer is flushed
// If mismatch occurs buffer is pasted and program continues
// This method is not really required for quotation and comments
// As they are relatively short identifiers

#include <stdio.h>
#include <stdlib.h>

int main(){
    int comment = 0; // Buffer gets cleared and bit is flipped when encountered
    int quotation = 0; // Buffer is kept and bit is flipped when encountered
    int directive = 0; // Buffer is kept and bit is flipped when encountered
    char c;
    char commentsEnable[22] = "pragma comments enable"; // 23 lenght for pound sign + terminator
    char commentsDisable[23] = "pragma comments disable"; // 24 lenght for pound sign + terminator

    FILE *CProgram = fopen("CProgram.c", "r+");
    FILE *CProgramCleaned = fopen("CProgramCleaned.c", "w+");
    c = fgetc(CProgram);
    while(c != EOF){
        // Beginning of look ahead section
        if (c == '#'){
            // Directive is off
            if (directive == 0){
                char *buffer = calloc(22, sizeof(char)); // Minimum buffer needs to be 22
                int extendedSpacesCounter = 0;
                int i = 0;
                fputc(c, CProgramCleaned);
                for (i = i; i < 22; i++){
                    c = fgetc(CProgram);
                    // If at any moment it detects a special character, it should go to the appropriate section
                    if (c == '/' || c == '\'' || c == '\"'){
                        break;
                    }

                    if ((c == '\t' || c == ' ') && (commentsEnable[i - 1] == ' ')){
                        extendedSpacesCounter++;
                        // It is likely costly to realloc every blank/tab character but it saves memory and unlike quotations shouldin't be too big of a deal
                        buffer = realloc(buffer, (extendedSpacesCounter + 22));
                        buffer[i + extendedSpacesCounter] = c;

                        // Keeps the directive counter the same if blanks/tabs are encountered while already on predefined blank
                        // Allows an infinite amount of blanks/tabs between words in the directive
                        // Although it would probably be a good thing to remove these extra spaces from the copy like a linter/compiler
                        // I would rather mess around with dynamically allocated memory
                        i--;
                    }
                    else if (c == commentsEnable[i + extendedSpacesCounter]){
                        buffer[i + extendedSpacesCounter] = c;
                    }
                    // Mismatch case
                    else {
                        // Write pound sign
                        // Write rest of buffer to file
                        // The buffer isin't even neccessary, you could just print each character when they occur
                        // But this is a nice proof of concept for a buffer
                        fputs(buffer, CProgramCleaned);
                        fputc(c, CProgramCleaned);
                        break;
                    }
                }
                if (c == '/' || c == '\'' || c == '\"'){

                    fputs(buffer, CProgramCleaned);
                    free(buffer); // Free the buffer
                    // This is meant to chain with the break statement inside the for loop above
                    // Pushes next iteration of the while loop to get this special character
                    continue;
                }
                // If the increment reaches its end it means the directive bool is flipped
                // And buffer is copied
                if (i == 22){
                    fputs(buffer, CProgramCleaned);
                    directive = 1;
                }
                free(buffer); // Free the buffer
            }
            // Directive is on
            else{
                char *buffer = calloc(23, sizeof(char)); // Minimum buffer needs to be 23
                int extendedSpacesCounter = 0;
                int i = 0;
                fputc(c, CProgramCleaned);
                for (i = i; i < 23; i++){
                    c = fgetc(CProgram);
                    
                    if ((c == '\t' || c == ' ') && (commentsDisable[i - 1] == ' ')){
                        extendedSpacesCounter++;
                        // It is likely costly to realloc every blank/tab character but it saves memory and unlike quotations shouldin't be too big of a deal
                        buffer = realloc(buffer, (extendedSpacesCounter + 23));
                        buffer[i + extendedSpacesCounter] = c;


                        // Keeps the directive counter the same if blanks/tabs are encountered while already on predefined blank
                        // Allows an infinite amount of blanks/tabs between words in the directive
                        i--;
                    }
                    else if (c == commentsDisable[i + extendedSpacesCounter]){
                        buffer[i + extendedSpacesCounter] = c;
                    }
                    // Mismatch case
                    else {
                        // Write pound sign
                        // Write buffer to file
                        fputs(buffer, CProgramCleaned);
                        fputc(c, CProgramCleaned);
                        break;
                    }
                }
                // If the increment reaches its end it means the directive bool is flipped
                if (i == 23){
                    fputs(buffer, CProgramCleaned);
                    directive = 0;
                }
                free(buffer); // Free the buffer
            }
        }
        else if (directive == 1){
            fputc(c, CProgramCleaned);
        }
        else if (c == '/'){
            char *buffer = malloc(3); // No need for initialization to zero this time
            buffer[0] = '/';
            c = fgetc(CProgram);
            // Inline quotation
            if ( c == '/'){
                // At this point no need to add anything to the buffer, just check for ending
                // Ending in this case is \n
                while((c = fgetc(CProgram)) != '\n' && c != EOF){
                    // Do nothing
                }
                if (c == '\n'){
                    // Puts the newline
                    fputc(c, CProgramCleaned);
                }
            }
            // Multi line quotation
            else if (c == '*'){
                // At this point no need to add anything to the buffer, just check for ending
                comment = 1;
                while(comment == 1){
                    c = fgetc(CProgram);
                    if (c == EOF){
                        break;
                    }
                    // && should evaluate left side first
                    else if (c == '*' && ((c = fgetc(CProgram))) == '/') {
                        comment = 0;
                    }
                    else{
                        // Do nothing
                    }
                }
            }
            // Case where it isin't an actual comment
            // Buffer is unnescessary as shown in quotation example below as it is only two characters
            else{
                buffer[1] = c;
                // Write buffer to file
                fputs(buffer, CProgramCleaned);
                // Free buffer
                free(buffer);
            }
        }
        else if (c == '\''){
            quotation = 1;
            // Write char to file
            fputc(c, CProgramCleaned);
            while(quotation == 1){
                c = fgetc(CProgram);
                if (c == EOF){
                    break;
                }
                if (c == '\\'){
                    // Write char to file
                    fputc(c, CProgramCleaned);
                    // Dosen't matter what next character is, just write it
                    c = fgetc(CProgram);
                    fputc(c, CProgramCleaned);
                }
                else if (c == '\''){
                    // Write to file
                    fputc(c, CProgramCleaned);
                    quotation = 0;
                }
                else {
                    // Write to file
                    fputc(c, CProgramCleaned);
                }
            }
        }
        else if (c == '\"'){
            quotation = 1;
            // Write char to file
            fputc(c, CProgramCleaned);
            while(quotation == 1){
                c = fgetc(CProgram);
                if (c == EOF){
                    break;
                }
                if (c == '\\'){
                    // Write char to file
                    fputc(c, CProgramCleaned);
                    // Dosen't matter what next character is, just write it
                    c = fgetc(CProgram);
                    fputc(c, CProgramCleaned);
                }
                else if (c == '\"'){
                    // Write to file
                    fputc(c, CProgramCleaned);
                    quotation = 0;
                }
                else {
                    // Write to file
                    fputc(c, CProgramCleaned);
                }
            }
        }
        // Case where none of the special chars are active, just copies to file
        else if (c != '#' && c != '\'' && c != '\"'&& c != '#') {
            fputc(c, CProgramCleaned);
        }

        // Global check
        if (c == EOF){
            break;
        }

        c = fgetc(CProgram);

    }
    return 0;
}

"