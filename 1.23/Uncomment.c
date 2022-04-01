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
    int quotation = 0; // Buffer is kept and bit is flipped when encoutered
    int directive = 0; // Buffer gets cleared and bit is flipped
    char c;

    FILE *CProgram = fopen("/CProgram.c", "r+");
    FILE *CProgramCleaned = fopen("/CProgramCleaned.c", "w+");
    while((c = fgetc(CProgram)) != EOF){
        // Beginning of look ahead section
        if (comment == 0 && quotation == 0 && directive == 0){
            if (c == '/'){

            }
        }
    }

    return 0;
}