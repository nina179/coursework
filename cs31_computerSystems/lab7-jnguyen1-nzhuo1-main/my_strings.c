// Swarthmore College, CS 31
// Copyright (c) 2023 Swarthmore College Computer Science Department,
// Swarthmore PA

// NOTE: your string library functions *must not* print anything in
// the code that you submit.  The standard I/O library is included
// here in case you wish to do any debug printing as you go.
#include <stdio.h>
#include <stdlib.h>

// NOTE: You *must not* include <string.h> or use any C-library string
// functions in this file!

// Header for your own implementation of the string library
#include "my_strings.h"

// Library functions for you to implement.

// Look at the manual page and/or the my_strings.h header file for a
// description of the arguments and return types.  The man pages will
// also give you a summary of the expected behavior.

/* Given a pointer to the beginning of a string, my_strlen computes
 * the length of the string by counting the number of characters it
 * encounters before finding a null-terminator.
 */
size_t my_strlen(const char *s) {

    size_t result = 0;
    int i = 0;

    // counts up number of characters in string before '\0'
    while (s[i] != '\0') {
        result ++;
        i++;
    }

    return result;
}

char *my_strcat(char *dest, const char *src) {

    int d_len = my_strlen(dest); // stores length of destination string
    int n = d_len; // saves index of string terminator in dest

    // iterates over length of dest string
    for(int i=0; i < d_len; i++) {

        // finds string terminator in dest
        if (dest[i] == '\0') {
            dest[i] = src[0]; 
            n = i; // saves index 

        // fills in rest of dest with characters in src after string terminator
        // has been replaced with the first character in src
        } else if (i > n) {
            dest[i] = src[i - n];
        }
    }

    // adds string terminator to end of modified dest
    dest[d_len] = '\0';

    return dest;
}

char *my_strchr(const char *str, int c) {
    
    int n = my_strlen(str); // stores length of str

    // iterates over length of str searching for c
    for (int i=0; i<n; i++) {
        // returns memory address of first c in str if c in str
        if (str[i] == c) {
            return (char*)&str[i];
        }
    }

    // returns NULL if c was not found in str
    return NULL;
}

int my_strcmp(const char *str1, const char *str2) {

    int a = my_strlen(str1); // stores length of str1
    int b = my_strlen(str2); // stores length of str2

    // initializes values of str1 and str2
    int aVal = 0; 
    int bVal = 0;

    // iterates over str1 to sum ASCII value
    for (int i = 0; i < a; i++) {
        aVal += str1[i];
    }

    // iterates over str2 to sum ASCII value
    for (int j = 0; j < b; j++) {
        bVal += str2[j];
    }

    // compares ASCII values of str1 and str2 and returns appropriate int value
    if (aVal < bVal) {
        return -1;
    } else if (aVal > bVal) {
        return 1;
    } else {
        return 0;
    }
}

char *my_strcpy(char *dest, const char *src) {

    int n = my_strlen(src); // stores length of src string

    // iterates over src and copies each character into dest
    for (int i=0; i<n; i++) {
        dest[i] = src[i];
    }
    
    dest[n+1] = '\0';   // adds string terminator after copied characters
    return dest;
}

char *my_strdup(const char *src) {

    char *str;
    char *copy;

    int len = my_strlen(src); // stores length of src

    // allocates memory for duplicates string accounting for terminator
    str = malloc(len + 1); 
    copy = str;

    // src has not reached the terminating bit set the mempory address of copy
    // equal to the memory address of src and increment
    while (*src) {
        *copy++ = *src++;
    }

    // set copy to the terminating bit and return string
    *copy = '\0';
    return str;
}

char *my_strstr(const char *haystack, const char *needle) {
    // set the lengths of needle and haystack and check
    int haylen = my_strlen(haystack);
    int needlen = my_strlen(needle);
    int check = -1;

    // iterates over haystack to find needle
    for (int i=0; i<haylen; i++) {
        // finds the first instance of a first letter of needle in haystack
        if (haystack[i] == needle[0]) {
            // iterates over needle and checks if the subsequent characters in 
            // haystack matches the subsequent characters in needle
            for (int j=0; j<needlen; j++) {
                if (j == needlen - 1 && check == 1) {
                    return (char*)&haystack[i];
                }
                else if (haystack[i+j] == needle[j]) {
                    check = 1;
                }
                else {
                    check = -1;
                    break;
                }
            }
        }
    }

    // returns NULL if needle not found in haystack
    return NULL;
}
