// Write a function reverse that reverses the character string s.
// Use it to write a program that reverses its input a line at a time.
#define MAXLINE 1000 // maximum input line length
#include <stdio.h>

void reverseAndAdd(char to[], char from[]) {

    int i = 0;
    int v = 0;
    int c = 0;
    while(to[v] != '\0'){
        v++;
    }
    while(from[i] != '\0'){
        i++;
    }
    to[i + v] = '\n';
    while(i > 0){
        to[i + v - 1] = from[c];
        i--;
        c++;
    }
}
int getline(char line[], int maxline){
    int i = 0;
    char c;
    while((i+1 < (maxline)) && (((c = getchar())!=EOF) && (c != '\n'))){
        line[i] = c;
        i++;
    }
    return i;
}

char line[MAXLINE] = ""; /* current input line */
char lines[MAXLINE] = ""; /* all lines saved here  */

int main(){

    while (getline(line, MAXLINE) > 0)
    {
        reverseAndAdd(lines, line);
        // Clean the array
        int i = 0;
        while(i < MAXLINE){
            line[i] = '\0';
            i++;
        }
    }

    /* Prints lines */
    printf("%s", lines);

    return 0;
}