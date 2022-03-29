// Write a program to print all input lines that are longer than 80 characters.
#define MAXLINE 1000 /* maximum input line length */
#include <stdio.h>
int getline(char line[], int maxline);
void add(char to[], char from[]);
/* print the longest input line */
int main()
{
    int len; /* current line length */
    int min = 8; /* minimum lenght*/
    // Have to initialize as empty strings to clear the allocatted memory of junk values
    char line[MAXLINE] = ""; /* current input line */
    char longLines[MAXLINE] = ""; /* all long lines saved here  */
    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (len > min) {
            add(longLines, line);
            // Clean the array
            int i = 0;
            while(i < MAXLINE){
                line[i] = '\0';
                i++;
            }
        }
    }
    if (min > 0)
    { /* Prints lines */
        printf("%s", longLines);
    }
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
    int i;
    i = 0;
    int v = 0;
    // Gets the current lenght of the longLines array to use as an offset when appending the next line
    while (to[v] != '\0'){
        v++;
    }
    // Appends the new line character by character with the offset
    while (from[i] != '\0')
    {
        to[i + v] = from[i];
        ++i;
    }
    // Add new line
    to[i + v] = '\n';
}