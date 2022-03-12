// Rewrite the temperature conversion program to use a function for conversion.

#include <stdio.h>
#include <stdlib.h>
// For string compare
#include <string.h>

// Maximum size of 10 characters to avoid buffer overruns
char unit[11];

float tempConverter(float temp, char *convertTo){

    // Selects between celsius or fahrenheit conversion, recalls the function if neither is selected properly
    if ((strcmp(convertTo, "celsius")) == 0){
        return (temp-32)/(1.8);
    }
    else if ((strcmp(convertTo, "fahrenheit")) == 0){
        return (temp*1.8)+32;
    }
    else {
        printf("That is not a valid unit, please enter either 'celsius' or 'fahrenheit': ");
        scanf("%11s", unit);
        return tempConverter(temp, unit);
    }

}

int main() {

    float temp;

    printf("Enter temperature value: ");
    scanf("%f", &temp);
    printf("\nEnter either 'celsius' or 'fahrenheit' as the unit to convert towards: ");

    scanf("%11s", &unit);

    printf("\n%f is equal to %.3f degrees %s", temp, tempConverter(temp, unit), unit);

    return 0;
}