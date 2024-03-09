/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsecmd.h"

char **parse_cmd_dynamic(const char *cmdline, int *bg) {
  
  char **argv = NULL;
  *bg = 0; // assumes cmdline does not contain '&'
  
  int i = 0;  // keeps track of index in cmdline
  int m = 0; // keeps track of # tokens 
  char current = cmdline[i]; // character at current index
  int check = 0; // checks if current is part of a token

  // counts up number of tokens 
  while (current != '&' && current != '\n') {
    if (!check && !isspace(current)) {
      check = 1;
      m++;
    } else if (check && isspace(current)){
      check = 0;
    }
    current = cmdline[i++];
  }

  // sets bg correctly if '&' is found
  if (current == '&') {
    *bg = 1; 
  } 

  // allocates memory for m number of tokens + null
  argv = (char**)malloc((m+1) * sizeof(char*));
  if (argv == NULL) {
    perror("ERROR: failed to allocate memory\n");
    exit(1);
  }

  int start, k, j, n = 0;
  i = 0;

  // save m number of tokens into argv 
  for (k = 0; k < m; k++) {
    // accounts for excess whitespace
    while (isspace(cmdline[i])) {
      i++;
    }
    start = i;
    // finds length of current token n
    while (!isspace(cmdline[i])) {
      if (cmdline[i] == '&') {
        break;
      }
      i++;
      n++;
    }
    
    // allocates memory in argv for current token
    argv[k] = (char*)malloc((n+1)*sizeof(char));

    // copies each character in current token over into argv[k]
    for (j = 0; j < n; j++) {
        argv[k][j] = cmdline[start + j];
    }
    argv[k][j] = '\0';

    n = 0; 
    j = 0;
    i++;
  }

  argv[k] = NULL;

  return argv;
}