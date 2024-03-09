/***************************************************************************
 * Parrish Hall Maze Program: CS31 Spring 2023
 ***************************************************************************/

#include "phases.h"
#include "support.h"
#include <stdio.h>
#include <stdlib.h>

FILE *infile;

int main(int argc, char *argv[]) {
  char *input;
  int answer, i;

  /* When run with no arguments, the maze reads its input lines
   * from standard input. */
  if (argc == 1) {
    infile = stdin;
  }

  /* When run with one argument <file>, the maze reads from <file>
   * until EOF, and then switches to standard input. Thus, as you
   * defuse each phase, you can add its defusing string to <file> and
   * avoid having to retype it. */
  else if (argc == 2) {
    if (!(infile = fopen(argv[1], "r"))) {
      printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
      exit(8);
    }
  }

  /* You can't call the maze with more than 1 command line argument. */
  else {
    printf("Usage: %s [<input_file>]\n", argv[0]);
    exit(8);
  }

  /* Do all sorts of secret stuff that makes the maze harder to solve. */
  initialize_maze();

  printf("You wake up on Parrish roof.  You need to get out of Parrish\n");
  printf("in time for your 9:30 class.  Due to construction, no single\n");
  printf("stairwell is connected to more than two floors, so you need to\n");
  printf("travel on each floor to find the open stairwell to the next.\n");
  printf("You have 5 floors to get through without getting caught along\n");
  printf("the way.  Good luck!\n\n");

  input = read_line(); /* Get input                   */
  phase_1(input);      /* Run the phase of the maze   */
  floor_escaped();     /* They got off that floor     */
                       /* Let me know how they did it. */
  printf("\nYou made it off the roof.  Now try the residential floors...\n");

  /* The second phase is harder.  */
  input = read_line();
  phase_2(input);
  floor_escaped();
  printf("\nYou made if off the residential floors without getting caught\n");
  printf("by an RA. See if you can sneak around to find an open stairwell\n");
  printf("on the President's floor.\n");

  /* The third phase is even harder than the last.  */
  input = read_line();
  phase_3(input);
  floor_escaped();
  printf("\nYou successfully snuck past Admissions. Try the main floor.\n");

  /* The fourth phase is more difficult yet  */
  input = read_line();
  phase_4(input);
  floor_escaped();
  printf("\nYou made made it past the Registrar's office.\n");

  printf("You could leave now and go to class, or do you\n");
  printf("want to try to exit through the basement?\n");
  printf("Enter 1 for yes, or 0 for no: ");
  input = read_line();
  i = sscanf(input, "%d", &answer);
  // i = scanf("%d", &answer);

  /* The fifth phase will really test them, will they try it??? */
  if ((i == 1) && (answer == 1)) {
    printf("Okay, try getting out of the basement then...\n");
    input = read_line();
    phase_5(input);
    floor_escaped();
  } else {
    printf("Yeah, skipping the basement for now and just going to class\n");
    printf("seems like a good idea.\n");
  }
  printf("\nGood work!  You made it out of Parrish in time for class");
  printf("...or did you?\n");
  /* They got out of Parrish!  But isn't something missing?
   * Perhaps something they overlooked?
   */
  return 0;
}
