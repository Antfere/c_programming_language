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
#include <string.h>

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

                    else if ((c == '\t' || c == ' ') && (commentsEnable[i - 1] == ' ')){

                        buffer[i + extendedSpacesCounter] = c;
                        // It is likely costly to realloc every blank/tab character but it saves memory and unlike quotations shouldin't be too big of a deal
                        buffer = realloc(buffer, (extendedSpacesCounter + 22)*sizeof(char));

                        extendedSpacesCounter++;

                        // Keeps the directive counter the same if blanks/tabs are encountered while already on predefined blank
                        // Allows an infinite amount of blanks/tabs between words in the directive
                        // Although it would probably be a good thing to remove these extra spaces from the copy like a linter/compiler
                        // I would rather mess around with dynamically allocated memory
                        i--;
                    }
                    else if (c == commentsEnable[i]){
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
                    // Realoc forgets to add the null terminator?
                    // Or is it something else?
                    buffer[i + extendedSpacesCounter] = '\0';
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

                        // It is likely costly to realloc every blank/tab character but it saves memory and unlike quotations shouldin't be too big of a deal
                        buffer = realloc(buffer, (extendedSpacesCounter + 23)*sizeof(char));
                        buffer[i + extendedSpacesCounter] = c;
                        extendedSpacesCounter++;

                        // Keeps the directive counter the same if blanks/tabs are encountered while already on predefined blank
                        // Allows an infinite amount of blanks/tabs between words in the directive
                        i--;
                    }
                    else if (c == commentsDisable[i]){
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
                    // Realoc forgets to add the null terminator?
                    // Or is it something else?
                    buffer[i + extendedSpacesCounter] = '\0';
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
                    // This will create gaps in the program...
                    // Further motivation to make a whitespace removing program to pipe into
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
                if (c == EOF){
                    fputs(buffer, CProgramCleaned);
                    free(buffer);
                }
                else{
                    buffer[1] = c;
                    // Write buffer to file
                    fputs(buffer, CProgramCleaned);
                    // Free buffer
                    free(buffer);
                }
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