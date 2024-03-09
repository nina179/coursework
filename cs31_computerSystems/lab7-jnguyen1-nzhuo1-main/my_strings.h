// Swarthmore College, CS 31
// Copyright (c) 2023 Swarthmore College Computer Science Department,
// Swarthmore PA

#ifndef _MYSTRINGS_
#define _MYSTRINGS_

// This header file defines the function prototypes for all of the
// functions in our library.  By including this, any program that
// wants to use the library knows what it needs to about the parameter
// types and return types of our library's functions.  In a header
// file like this, you can optionally name the function parameters or
// specify just the type, as shown below.

// NOTE: You *must not* change these function prototypes!  These
// functions should have the same parameter types and return types as
// their C-library counterparts!

size_t my_strlen(const char *s);

/* concatonates two strings
 * @param dest character pointer with extra memory to store concatonated string
 * @param src unchangable character pointer representing a string
 * @returns memory address of dest now containing concatonated string
 */
char *my_strcat(char *dest, const char *src);

/* finds first instance of a given character in given string
 * @param str unchangable character pointer containing multiple characters
 * @param c character being searched for in str
 * @returns memory address of first instance of c in str
 * @returns NULL in the case that c not in str
 */
char *my_strchr(const char *str, int c);

/* compares ASCII values of two strings
 * @param str1 unchangable character pointer
 * @param str2 unchangable character pointer being compared to str1
 * @returns -1 when ASCII value of str1 is less than str2
 * @returns 0 when str1 and str2 have the same ASCII value
 * @returns 1 when ASCII value of str1 is greater than str2
 */
int my_strcmp(const char *str1, const char *str2);

/* copies characters of one string into another
 * @param dest character pointer to empty string of characters
 * @param src unchangable character point being copied into dest
 * @returns memory address of dest now containing copy of src
 */
char *my_strcpy(char *dest, const char *src);

/* duplicates given string
 * @param str unchangable character pointer to be duplicated
 * @return memory address of duplicated string
 */
char *my_strdup(const char *str);

/* finds a substring within given string
 * @param haystack unchangable character pointer to search through
 * @param needle unchangable character pointer containing substring
 * @returns memory address of first instance of needle in haystack
 * @returns NULL in the case that needle not in haystack
 */
char *my_strstr(const char *haystack, const char *needle);

#endif
