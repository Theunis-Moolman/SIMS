#include "utils.h"

void copyString(char *source, char *destination){
    while (*source != '\0'){
        *destination = *source;
        source++;
        destination++;
    }
    *destination = '\0';
}

void lowerString(char *source){
    while (*source != '\0'){
        if (*source >= 'A' && *source <= 'Z'){
            *source += 32;
        }
        source++;
    }
}
