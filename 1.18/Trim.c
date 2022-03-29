// Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines
#define MAXLINE 1000 /* maximum input line length */

#include <stdio.h>
int getline(char line[], int maxline);
void add(char to[], char from[]);

int main(){
    char line[MAXLINE] = ""; /* current input line */
    char lines[MAXLINE] = ""; /* all lines saved here  */
    int len; /* current line length */
    while ((len = getline(line, MAXLINE)) > 0)
    {
        add(lines, line);
        int i = 0;
        // Clean the array
        while(i < MAXLINE){
            line[i] = '\0';
            i++;
        }
    }
    /* Prints lines */
    printf("%s", lines);
    return 0;
}
/* getline: read a line into s, return length */
int getline(char s[],int lim)
{
    int c, i;
    for (i=0; i+1 < lim && (c=getchar())!=EOF && c!='\n'; ++i)
    {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

/* add: add ’from’ to the end of ’to’; assume to is big enough */
void add(char to[], char from[])
{
    // Its somewhat poorly made, but "i" is the lenght of the trimmed string
    // "v" is the offset for the master char array which takes in added strings
    // "p" is the prefix offset, the amount of whitespace chars at the start which need trimming
    // "s" is the suffix offset, the amount of whitespace character before the final null character of a string
    int i = 0, v = 0, p = 0, s = 0;

    // Get the prefix trim offset
    while(from[p] == '\0' || from[p] == ' ' || from[p] == '\t'){
        p++;
    }

    // Get the suffix trim offset
    while(from[p + s] != '\0'){++s;}
    for (s = s; from[p + s] == ' ' || from[p + s] == '\t'; --s){

    }

    // Gets the current lenght of the lines array to use as an offset when appending the next line
    while (to[v] != '\0'){
        ++v;
    }
    // Appends the new line character by character with the offset
    while ((from[i + p] != '\0') && (i < s) && (p < MAXLINE)) 
    // p < 1000 is for edge case where p goes to 1000 and start reading wrong memory
    {
        to[i + v] = from[i + p];
        ++i;
    }
    // Add new line
    if (i > 0){
        to[i + v] = '\n';
    }
}