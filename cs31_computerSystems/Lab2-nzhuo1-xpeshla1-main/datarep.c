/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

/* CS31 Data Representation and Arithmetic Operations lab: Part 2
 * This program answers and proves arithmetic operations on binary numbers.
 *
*/
#include <stdio.h>

/*
 * Helper functions for left and right shifting
 */
 void helper(unsigned val, int x, int s);
 void helperR(unsigned val, int x, int s);

/****************************************************/
/*
 * This functions answers Q1: how many different representations
 * can printf display the value 97?
 */
void question1() {
  int val;
  val = 97;

  printf("\n**** Question 1 ****\n");
  printf("How many different representations can printf display the value 97?\n");
  printf("   printf can display the value 97 as 3 different representations:\n");
  printf("     as a decimal  = %d \n", val);
  printf("     as a hexadecimal = %x \n", val);
  printf("     as a character = %c \n", val);
}
/****************************************************/
/*
 * This function answers Q2: what is the maximum value that can be stored in 
 * a C unsigned int variable (unsigned)?
 */
void question2() {
  printf("\n**** Question 2 ****\n");
  printf("What is the maximum value that can be stored in a C unsigned int variable (unsigned)?\n");
  
  printf("     We know that an unsigned int has 32 bits, so we set n to be a maxed out\n");
  printf("     32-bit binary number where every digit is one. This is the same as a maxed\n");
  printf("     out 32-bit hexadecimal where every digit is f.\n");
 
  unsigned n = 0b11111111111111111111111111111111;
  printf("     n = %x = %u\n", n, n);
 
  printf("     To further prove that this is the maximum value that can be stored in a C\n");
  printf("     unsigned int, we add one to n, which should result in overflow, resetting n\n");
  printf("     to be 0:\n");

  printf("     n + 1 = %x = %u\n", (n+1), n+1 );
}
/****************************************************/

/****************************************************/
/*
 * This function answers Q3: what is the maximum positive value that can be 
 * stored in a C int variable (signed)?
 */
void question3() {
  printf("\n**** Question 3 ****\n");
  printf("The maximum positive value that can be stored in a C int variable (signed) is:\n");
 
  printf("     We know that a signed int has 32 bits where the first digit has a decimal value\n");
  printf("     of -2^(i-1). So, we set n to be a maxed out signed 32-bit binary number where the\n");
  printf("     first digit is zero and every digit is one.\n");
 
  int n = 0b01111111111111111111111111111111;
  printf("     n = %x = %d\n", n, n);
  
  printf("     We know this is the maximum value that can be stored in a C signed int\n"); 
  printf("     variable because adding one will result in overflow, setting n to be -(n-1):\n");
 
  printf("     n + 1 = %x = %d\n", (n+1), n+1 );
}
/****************************************************/

/****************************************************/
/*
 * This function answers Q4: what arithmetic operation is equivalent to left 
 * shifting an unsigned int value by 1?
 */
void question4() {
  printf("\n**** Question 4 ****\n");
  printf("The arithmetic operation n*(2^1) is equivalent to left shifting an unsigned int value by 1:\n");
 
  int x = 2;
  int s = 1;
 
  unsigned val = 0b00000000000000000000000000000010;
  helper(val, x, s);
  printf("\n");
 
  unsigned val2 = 0b00000000000000000000000000000110; 
  helper(val2, x, s);
  printf("\n");
 
  unsigned val3 = 0b00000000000000000000000000001110; 
  helper(val3, x, s);
}
/****************************************************/

/****************************************************/
/*
 * This is a helper function that shifts val left by s and multiplies val by x
 */
void helper(unsigned val, int x, int s) {
  printf("     We set n equal to %d in decimal\n",val);
  unsigned shiftedVal = val << s ;
 
  printf("     We perform n << %d to get: %d\n",x, shiftedVal);
  unsigned mathVal = val*x;
 
  printf("     This is the same as n*%d which gives us: %d\n",x ,mathVal);

}
/****************************************************/

/****************************************************/
/*
 * This function answers Q5: what arithmetic operation is equivalent to left 
 * shifting an unsigned int value by 2?
 */
void question5() {
  printf("\n**** Question 5 ****\n");
  printf("The arithmetic operation n*(2^2) is equivalent to left shifting an unsigned int value by 2:\n");
 
  int x = 2*2;
  int s = 2;
 
  unsigned val = 0b00000000000000000000000000000010;
  helper(val, x, s);
  printf("\n");
 
  unsigned val2 = 0b00000000000000000000000000000110; 
  helper(val2, x, s);
  printf("\n");
 
  unsigned val3 = 0b00000000000000000000000000001110; 
  helper(val3, x, s);
}
/****************************************************/

/****************************************************/
/*
 * This function answers Q5: what arithmetic operation is equivalent to 
 * right shifting an unsigned int value by 1?
 */
void question6() {
  printf("\n**** Question 6 ****\n");
  printf("The arithmetic operation n/2 is equivalent to right shifting an unsigned int value by 1:\n");
 
  int x = 2;
  int s = 1;
 
  unsigned val = 0b00000000000000000000000000000010;
  helperR(val, x, s);
  printf("\n");
 
  unsigned val2 = 0b00000000000000000000000000000110; 
  helperR(val2, x, s);
  printf("\n");
 
  unsigned val3 = 0b00000000000000000000000000001110; 
  helperR(val3, x, s);
}
/****************************************************/

/****************************************************/
/*
 * This is a helper function that shifts val right by s and divides val by x
 */
void helperR(unsigned val, int x, int s) {
  printf("     We set n equal to %d in decimal\n",val);
  unsigned shiftedVal = val >> s ;
 
  printf("     We perform n >> %d to get: %d\n",x, shiftedVal);
  unsigned mathVal = val/x;
 
  printf("     This is the same as n/%d which gives us: %d\n",x ,mathVal);
}
/****************************************************/

int main() {

  question1();
  question2();
  question3();
  question4();
  question5();
  question6();
 
  printf("\n");
 
  return 0;
}
