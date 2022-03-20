// Write a program to print all input lines that are longer than 80 characters.

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */
int lineCounter = 0;
int getline(char line[], int maxline);
void adding(char to[], char from[], int *lineCounter);
/* print the longest input line */
int main()
{
    int len; /* current line length */
    int min = 8; /* maximum length seen so far */
    char line[MAXLINE]; /* current input line */
    char longLines[MAXLINE]; /* longest line saved here */
    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (len > min) {
            adding(longLines, line, &lineCounter);
        }
    }
    if (min > 0)
    { /* there was a line */
        printf("%s", longLines);
    }
    return 0;
}
/* getline: read a line into s, return length */
int getline(char s[],int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    {
        s[i] = c;
        if (c == '\n') {
            s[i] = c;
            ++i;
        }
    }
    s[i] = '\0';
    return i;
}
/* copy: copy ’from’ into ’to’; assume to is big enough */
void adding(char to[], char from[], int *lineCounter)
{
    int i;
    i = 0;
    int v = 0;
    while (to[v] != '\0'){
        v++;
    }
    while (from[i] != '\0')
    {
        to[i + v] = from[i];
        ++i;
    }
    to[i + v] = '\n';
}

// Works ok sorta, except for the random symbols...