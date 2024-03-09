// Swarthmore College, CS 31
// Copyright (c) 2023 Swarthmore College Computer Science Department,
// Swarthmore PA


// System headers to be included.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local headers to be included.
#include "my_strings.h"

// TODO: test my_strlen
// Tests for my_strlen are implemented below to give you an idea of
// what is expected for the other functions. You are welcome to add a
// third strlen test if you would like.

// Compares my_strlen's output to that of strlen's on the string
// "Hello, world!"
void test_strlen_1() {
    char *test_string = "Hello, world!";

    printf("Given '%s':\n", test_string);
    printf("  The result of strlen() is %ld\n", strlen(test_string));
    printf("  The result of my_strlen() is %ld\n", my_strlen(test_string));
    printf("\n");
}

// Compares my_strlen's output to that of strlen's on the empty string ("")
void test_strlen_2() {
    char *test_string = "";

    printf("Given the empty string, '%s':\n", test_string);
    printf("  The result of strlen() is %ld\n", strlen(test_string));
    printf("  The result of my_strlen() is %ld\n", my_strlen(test_string));
    printf("\n");
}

// Compares my_strcat's output to that of strcat's on the two strings
// "Hello," " world!"
void test_strcat_1() {
    
    char test_string1[14];
    strcpy(test_string1, "Hello,"); 
    char *test_string2 = " world!";

    printf("Given '%s' and '%s':\n", test_string1, test_string2);
    printf("  The result of strcat() is %s\n",
        strcat(test_string1, test_string2));
    printf("  The result of my_strcat() is %s\n", 
        my_strcat(test_string1, test_string2));
    printf("\n");
}

// Compares my_strcat's output to that of strcats's on the two strings
// " a  b  c ," " d  e  f "
void test_strcat_2() {
    char test_string1[18];
    strcpy(test_string1, " a  b  c ");
    char *test_string2 = " d  e  f";

    printf("Given '%s' and '%s':\n", test_string1, test_string2);
    printf("  The result of strcat() is %s\n",
        strcat(test_string1, test_string2));
    printf("  The result of my_strcat() is %s\n", 
        my_strcat(test_string1, test_string2));
    printf("\n");
}

// Compares my_strchr's output to that of strchr's on the string
// "SWARTHMORE"
void test_my_strchr1() {
    char *test_string = "SWARTHMORE";
    int chr = 'O';

    printf("Given '%s':\n", test_string);
    printf("  The first occurence of %c in '%s' is '%s' using strchr()\n", 
        chr, test_string, strchr(test_string, chr));
    printf("  The first occurence of %c in '%s' is '%s' using my_strchr()\n", 
        chr, test_string, strchr(test_string, chr));    
        printf("\n");
}

// Compares my_strchr's output to that of strchr's on the string
// "cs rules!"
void test_my_strchr2() {
    char *test_string = "cs rules!";
    int chr = '!';

    printf("Given '%s':\n", test_string);
    printf("  The first occurence of %c in '%s' is '%s' using strchr()\n", 
        chr, test_string, strchr(test_string, chr));    
    printf("  The first occurence of %c in '%s' is '%s' using my_strchr()\n", 
        chr, test_string, strchr(test_string, chr));      printf("\n");
}

// Compares my_strcmp's output to that of strcmp's on the two strings
// "richard and charlie" and "nina and jimmy"
void test_strcmp_1() {
    char *test_string1 = "richard and charlie";
    char *test_string2 = "nina and jimmy";

    printf("Given '%s' and '%s':\n", test_string1, test_string2);
    printf("  The result of strcmp() is %d\n", 
        strcmp(test_string1, test_string2));
    printf("  The result of my_strcmp() is %d\n", 
        my_strcmp(test_string1, test_string2));
    printf("\n");
}

// Compares my_strcmp's output to that of strcmp's on the two strings
// "computer sciencE" and "computer science"
void test_strcmp_2() {
    char *test_string1 = "computer sciencE";
    char *test_string2 = "computer science";

    printf("Given '%s'and '%s':\n", test_string1, test_string2);
    printf("  The result of strcmp() is %d\n", 
        strcmp(test_string1, test_string2));
    printf("  The result of my_strcmp() is %d\n", 
        my_strcmp(test_string1, test_string2));
    printf("\n");
}

// Compares my_strcmp's output to that of strcmp's on the two identical strings
// "i love cs"
void test_strcmp_3() {
    char *test_string1 = "i love cs31!";
    char *test_string2 = "i love cs31!";

    printf("Given '%s'and '%s':\n", test_string1, test_string2);
    printf("  The result of strcmp() is %d\n", 
        strcmp(test_string1, test_string2));
    printf("  The result of my_strcmp() is %d\n", 
        my_strcmp(test_string1, test_string2));
    printf("\n");
}

// Compares my_strcpy's output to that of strcpy's on the string
// "This is working"
void test_strcpy_1() {    
    char test_string1[50];
    char *test_string2 = "This is working";

    printf("Given '%s':\n", test_string2);
    printf("  The result of strcpy() is %s\n",
        strcpy(test_string1, test_string2));
    printf("  The result of my_strcpy() is %s\n", 
        my_strcpy(test_string1, test_string2));
    printf("\n");
}

// Compares my_strcpy's output to that of strcpy's on the string
// "    !     "
void test_strcpy_2() {
    
    char test_string1[50];
    char *test_string2 = "    !    ";

    printf("Given '%s':\n", test_string2);
    printf("  The result of strcpy() is %s\n",
        strcpy(test_string1, test_string2));
    printf("  The result of my_strcpy() is %s\n", 
        my_strcpy(test_string1, test_string2));
    printf("\n");
}

// Compares my_strdup's output to that of strdup's on the string
// "Duplicate Me!"
void test_strdup_1() {
    
    char *test_string1 = "Duplicate Me!";

    char *result1 = strdup(test_string1);
    char *result2 = my_strdup(test_string1);

    printf("Given '%s':\n", test_string1);
    printf("  The result of strdup() is %s\n", result1);
    printf("  The result of my_strdup() is %s\n", result2);
    printf("\n");

    free (result1);
    free (result2);
}

// Compares my_strstr's output to that of strstr's on the string
// "I have so many layers." trying to find "layers"
void test_strstr_1() {
    
    char *haystack = "I have so many layers.";
    char *needle = "layers";

    char *result1 = strstr(haystack, needle);
    char *result2 = my_strstr(haystack, needle);

    printf("Given '%s' and '%s':\n", haystack, needle);
    printf("  The result of strstr() is %s\n", result1);
    printf("  The result of my_strstr() is %s\n", result2);
    printf("\n");
}

// Compares my_strstr's output to that of strstr's on the string
// "Yippie! Hooray!! Yayy!" trying to find "boo" 
void test_strstr_2() {
    
    char *haystack = "Yippie! Hooray!! Yayy!";
    char *needle = "boo";

    char *result1 = strstr(haystack, needle);
    char *result2 = my_strstr(haystack, needle);

    printf("Given '%s' and '%s':\n", haystack, needle);
    printf("  The result of strstr() is %s\n", result1);
    printf("  The result of my_strstr() is %s\n", result2);
    printf("\n");
}

int main(int argc, char **argv) {

    // test my_strcat
    test_strlen_1();
    test_strlen_2();

    // test my_strcat
    test_strcat_1();
    test_strcat_2();

    // test my_strchr
    test_my_strchr1();
    test_my_strchr2();

    // test my_strcmp
    test_strcmp_1();
    test_strcmp_2();
    test_strcmp_3();

    // test my_strcpy
    test_strcpy_1();
    test_strcpy_2();

    // test my_strdup
    test_strdup_1();
    
    // test my_strstr
    test_strstr_1();
    test_strstr_2();

    return 0;
}
