/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms

  Sums up the number read from imported file
*/

#include <iostream>
#include <fstream>
using namespace std;

int big_num(int array[], int n);
int ten_count(int array[], int n);
float num_avg(int array[], int n);

int main() {

  //prompts user for name of a file
  cout << "Please enter the name of your file: ";
  string numbers_file;
  cin >> numbers_file;

  // reads contents of file into a new dynamic array
  ifstream myfile;
  myfile.open(numbers_file);

  int n;
  myfile >> n;
  int *num_array = new int[n];

  for (int i=0; i<n; i++) {
    myfile >> num_array[i];
  }

  // prints out summaries of functions performed
  cout << "The last number is " << num_array[n-1] << "." << endl;
  cout << "The largest number is " << big_num(num_array, n) << "." << endl;
  cout << "There are " << ten_count(num_array, n) << " numbers less than 10 in this sequence." << endl;
  cout << "The average is " << num_avg(num_array, n) << endl;

  delete[] num_array;
  return 0;
}

int big_num(int array[], int n) {
  // assumes the biggest number in the array is the first one
  int big_num = array[0];

  // compares each element in the array to big_num to find the actual big_num
  for(int i=1; i<n-1; i++) {
    // sets biggest number as array[i] if its value is bigger than big_num
    if (array[i] > big_num) {
      big_num = array[i];
    }
  }
  return big_num;
}

int ten_count(int array[], int n) {
  // initializes count for number of elements in array that are less than 10
  int count = 0;
  for (int i=0; i<n; i++) {
    // adds 1 to count if array[i] is less than 10
    if (array[i] < 10) {
      count += 1;
    }
  }
  return count;
}

float num_avg(int array[], int n) {
  // initializes the sum of all integers in array[] to 0
  float num_sum;
  num_sum = 0;

  // iterates over length of array and adds value of array[i] to num_sum 
  for (int i=0; i<n; i++) {
    num_sum += array[i];
  }

  // creates float avg and divides it by lenth of array (n)
  float avg;
  avg = (num_sum/n);

  return avg;
}
