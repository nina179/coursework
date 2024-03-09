/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

// TODO: add your top-level comment here

/*
 * To run:
 * ./gol file1.txt  0  # run with config file file1.txt, do not print board
 * ./gol file1.txt  1  # run with config file file1.txt, ascii animation
 * ./gol file1.txt  2  # run with config file file1.txt, ParaVis animation
 *
 */
#include <pthreadGridVisi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "colors.h"

/****************** Definitions **********************/
/* Three possible modes in which the GOL simulation can run */
#define OUTPUT_NONE   (0)   // with no animation
#define OUTPUT_ASCII  (1)   // with ascii animation
#define OUTPUT_VISI   (2)   // with ParaVis animation

/* Used to slow down animation run modes: usleep(SLEEP_USECS);
 * Change this value to make the animation run faster or slower
 */
//#define SLEEP_USECS  (1000000)
#define SLEEP_USECS    (200000)

/* A global variable to keep track of the number of live cells in the
 * world (this is the ONLY global variable you may use in your program)
 */
static int total_live = 0;

/* This struct represents all the data you need to keep track of your GOL
 * simulation.  Rather than passing individual arguments into each function,
 * we'll pass in everything in just one of these structs.
 * this is passed to play_gol, the main gol playing loop
 *
 * NOTE: You will need to use the provided fields here, but you'll also
 *       need to add additional fields. (note the nice field comments!)
 * NOTE: DO NOT CHANGE THE NAME OF THIS STRUCT!!!!
 */
struct gol_data {

    // NOTE: DO NOT CHANGE the names of these 4 fields (but USE them)
    int rows;  // the row dimension
    int cols;  // the column dimension
    int iters; // number of iterations to run the gol simulation
    int output_mode; // set to:  OUTPUT_NONE, OUTPUT_ASCII, or OUTPUT_VISI

    int* map; // array containing set of cells
    int* temp; // temp array containing set of dead cells

    int id; // thread id
    int num_threads; // degree of parallelism game is running on
    int partition; // flag specifying how to parallelize GOL program
    int print_partition; // flag specifying if partition should be printed
    
    int rowstart; // start row index
    int rowend; // end row index
    int colstart; // start col index
    int colend; // end col index

    /* fields used by ParaVis library (when run in OUTPUT_VISI mode). */
    // NOTE: DO NOT CHANGE their definitions BUT USE these fields
    visi_handle handle;
    color3 *image_buff;
};

static pthread_barrier_t my_barrier;
static pthread_mutex_t my_mutex;

/****************** Function Prototypes **********************/

/* the main gol game playing loop (prototype must match this) */
void *play_gol(void *args);

/* init gol data from the input file and run mode cmdline args */
int init_game_data_from_args(struct gol_data *data, char **argv);

// A mostly implemented function, but a bit more for you to add.
/* print board to the terminal (for OUTPUT_ASCII mode) */
void print_board(struct gol_data *data, int round);

/* returns number of live neighbors of cell */
int getVitals(struct gol_data *data, int cell, int x, int y);

/* main game loop updating number of live and dead cells */
void runGame(struct gol_data *data);

/* updates color of visii after every round */
void update_colors(struct gol_data *data);

/* paritition board for threading */
void partition(struct gol_data *data);

/* plays game of life with threads*/
void playThreads(struct gol_data *data, struct gol_data *threadArr, pthread_t *tids);


/************ Definitions for using ParVisi library ***********/
/* initialization for the ParaVisi library (DO NOT MODIFY) */
int setup_animation(struct gol_data* data);
/* register animation with ParaVisi library (DO NOT MODIFY) */
//int connect_animation(void (*applfunc)(struct gol_data *data), struct gol_data* data);
/* name for visi (you may change the string value if you'd like) */
static char visi_name[] = "GOL!";


int main(int argc, char **argv) {

    int ret, i;
    struct gol_data data;
    double secs;
    struct timeval start_time, stop_time;

    /* check number of command line arguments */
    if (argc != 6) {
        printf("usage: %s infile.txt output_mode[0|1|2] num_threads", argv[0]);
        printf(" partition[0,1] print_partition[0,1]\n");
        printf("(0: no visualization, 1: ASCII, 2: ParaVisi)\n");
        exit(1);
    }

    /* Initialize game state (all fields in data) from information
     * read from input file */
    ret = init_game_data_from_args(&data, argv);
    if (ret != 0) {
        printf("Initialization error: file %s, mode %s\n", argv[1], argv[2]);
        exit(1);
    }

    /* initialize ParaVisi animation (if applicable) */
    if (data.output_mode == OUTPUT_VISI) {setup_animation(&data);}

    /* ASCII output: clear screen & print the initial board */
    if (data.output_mode == OUTPUT_ASCII) {
        if (system("clear")) { perror("clear"); exit(1); }
        print_board(&data, 0);
    }

    // initializes array of threads
    pthread_t *tids;
    tids = malloc(sizeof(pthread_t) * data.num_threads);
    if(!tids) { perror("malloc: pthread_array"); exit(1);}

    // initializes array of structs storing information for each thread 
    struct gol_data* threadArr;
    threadArr = malloc(sizeof(struct gol_data)*data.num_threads);
    if (!threadArr) 
    {printf("ERROR: malloc for pthread array failed!\n"); exit(1);}

    // initialize barrier
    if (pthread_barrier_init(&my_barrier, NULL, data.num_threads)) 
    {printf("pthread_barrier_init error\n"); exit(1);}

    // initialize mutex
    if (pthread_mutex_init(&my_mutex, NULL)) 
    {printf("pthread_mutex_init error\n"); exit(1);}

    // starts clock to calculate total running time of gameplay
    ret = gettimeofday(&start_time, NULL);
    if (ret != 0) {printf("ERROR: unable to get time of day"); exit(1);}

    /* Invoke play_gol in different ways based on the run mode */
    if (data.output_mode == OUTPUT_NONE) {
        playThreads(&data, threadArr, tids);
    } else if (data.output_mode == OUTPUT_ASCII) { // run with ascii animation
        playThreads(&data, threadArr, tids);

        // clear the previous print_board output from the terminal:
        // (NOTE: you can comment out this line while debugging)
        if (system("clear")) { perror("clear"); exit(1); }

        // NOTE: DO NOT modify this call to print_board at the end
        //       (it's to help us with grading your output)
        print_board(&data, data.iters);
    } else {  // OUTPUT_VISI: run with ParaVisi animation
        playThreads(&data, threadArr, tids);
        
        // start ParaVisi animation
        //connect_animation(play_gol, &data);
        run_animation(data.handle, data.iters);
    }

    // joins threads
    for (i = 0; i < data.num_threads; i++) {
        pthread_join(tids[i], 0);
    }

    // stops clock to calculate total running time of gameplay
    ret = gettimeofday(&stop_time, NULL);

    // NOTE: you need to determine how and where to add timing code
    //       in your program to measure the total time to play the given
    //       number of rounds played.
    if (data.output_mode != OUTPUT_VISI) {
        secs = 0.0;

        secs = (stop_time.tv_sec + (stop_time.tv_usec * 0.000001 )) - 
            (start_time.tv_sec + (start_time.tv_usec * 0.000001));

        /* Print the total runtime, in seconds. */
        // NOTE: do not modify these calls to fprintf
        fprintf(stdout, "Total time: %0.3f seconds\n", secs);
        fprintf(stdout, "Number of live cells after %d rounds: %d\n\n",
                data.iters, total_live);
    }

    // clean up crew
    if (pthread_mutex_destroy(&my_mutex)) 
    {printf("pthread_mutex_destroy error\n"); exit(1);}

    if (pthread_barrier_destroy(&my_barrier)) 
    {printf("pthread_barrier_destroy error\n"); exit(1);}

    free(data.map);
    free(data.temp);

    free(tids);
    free(threadArr);

    return 0;
}

// plays gol with threads
void playThreads(struct gol_data *data, struct gol_data *threadArr, pthread_t *tids) {
    int ret;
    for (int i = 0; i < data->num_threads; i++) {
        data->id = i;
        partition(data);
        threadArr[i] = *data;

        ret = pthread_create(&tids[i], 0, play_gol, &threadArr[i]);
        if(ret) {printf("ERROR: pthread creation failed"); exit(1);}
    }
}

/* initialize the gol game state from command line arguments
 *       argv[1]: name of file to read game config state from
 *       argv[2]: run mode value
 * data: pointer to gol_data struct to initialize
 * argv: command line args
 *       argv[1]: name of file to read game config state from
 *       argv[2]: run mode
 * returns: 0 on success, 1 on error
 */
int init_game_data_from_args(struct gol_data *data, char **argv) {

    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        printf("ERROR: cannot open file\n");
        exit(1);
    }

    int ret, num, x, y;
    
    // reads in and sets number of rows in struct
    ret = fscanf(infile, "%d", &num);
    if (ret == 0) {
        printf("ERROR: unable to read number of rows from file\n");
        exit(1);
    }
    data->rows = num;

    // reads in and sets number of columns in struct
    ret = fscanf(infile, "%d", &num);
    if (ret == 0) {
        printf("ERROR: unable to read number of columns from file\n");
        exit(1);
    }
    data->cols = num;

    // reads in and sets number of iterations in struct
    ret = fscanf(infile, "%d", &num);
    if (ret == 0) {
        printf("ERROR: unable to read number of iterations from file\n");
        exit(1);
    }
    data->iters = num;

    // sets output mode in struct
    ret = atoi(argv[2]);
    if (ret < 0 || ret > 2) {
        printf("ERROR: invalid output mode\n");
        exit(1);
    }
    data->output_mode = ret;

    // reads in and sets initial number of live cells in struct
    ret = fscanf(infile, "%d", &num);
    if (ret == 0) {
        printf("ERROR: unable to read number of live cells from file");
        exit(1);
    }
    total_live = num;

    // creates two array representing game of life board assuming all cells are dead
    data->map = NULL;
    data->temp = NULL;

    int m = data->rows;
    int n = data->cols;

    int* arr1 = malloc(m*n * sizeof(int));
    int* arr2 = malloc(m*n * sizeof(int));

    for (int i = 0; i < (m*n); i++) {
        arr1[i] = 0;
        arr2[i] = 0;
    }

    data->map = arr1;
    data->temp = arr2;

    // reads live cells into map
    int index;
    for (int i = 0; i < total_live; i++) {
        ret = fscanf(infile, "%d %d", &y, &x);
        if (ret == 0) {
            printf("ERROR: unable to read location of live cell from file");
            exit(1);
        }
        index = (y*n) + x;
        data->map[index] = 1;
    }

    fclose(infile);

    // determines how we will partition
    int temp = atoi(argv[4]);
    if (temp != 0 && temp != 1) 
    {printf("ERROR: partition flag must be set to 0 or 1\n"); exit(1);}
    data->partition = temp;

    // reads in number of threads
    temp = atoi(argv[3]);
    if (temp < 0)
    {printf("ERROR: number of threads cannot be negative\n"); exit(1);}

    if (data->partition == 0) {
        temp = atoi(argv[3]);
        if (temp > data->cols) 
        {printf("ERROR: number of threads cannot exceed number of columns\n"); exit(1);}
    } else {
        if (temp > data->rows) 
        {printf("ERROR: number of threads cannot exceed number of rows\n"); exit(1);}
    }
    data->num_threads = atoi(argv[3]);
    
    // determines if we print allocation information or not
    temp = atoi(argv[5]);
    if (temp != 0 && temp != 1)
    {printf("ERROR: print_partition flag must be set to 0 or 1 \n"); exit(1);}
    data->print_partition = temp;

    return 0;
}

/* Partitions for threading
 *     data: pointer to gol_data struct
 */
void partition(struct gol_data *data) {

    int div; // min num rows or cols each thread is responsible for
    int rem; // additional rows or cols to account for

    // sets div and rem according to mode of parallelization
    int mode = data->partition;
    if (mode == 0) {
        div = data->rows / data->num_threads;
        rem = data->rows % data->num_threads;
    } else {
        div = data->cols / data->num_threads;
        rem = data->cols % data->num_threads;
    }

    // determines if thread will be responsible for a rem cols or rows
    int part, mini;
    if (data->id < rem) { 
        part = div + 1;
        mini = data->id;
    } else { 
        part = div;
        mini = rem;
    }

    mini = mini * (div+1);
    for (int i = rem; i < data->id; i++) {
        mini += div;
    }

    // updates start and end at each thread
    if (mode == 0) {
        data->rowstart = mini;
        data->rowend = data->rowstart + part;
        data->colstart = 0;
        data->colend = data->cols;
    } else {
        data->rowstart = 0;
        data->rowend = data->rows;
        data->colstart = mini;
        data->colend = data->colstart + part;
    }
}

 /* checks to see if the surrounding vitals of a certain cell and returns the amount
  * of live cells around it.
  *     data: pointer to gol_data struct
  *     cell: current index in map we're checking nieghbors of
  *     x: data->rows
  *     y: data->cols
  * returns: the number of live surrounding cells
  */
int getVitals(struct gol_data *data, int cell, int y, int x){

    int num = 0; // tallies up number of live neighbors
    int c_index = y*data->cols + x; // index of cell in data->map

    int neighbor, index;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            
            // x and y values of neighboring cell
            int modx = x + i;
            int mody = y + j;

            // accounts for edge cases of x
            if ((x+i) < 0) {
                modx = data->cols - 1;
            } else if ((x+i) >= data->cols) {
                modx = 0;
            } 

            // accounts for edge cases of y
            if ((y+j) < 0) {
                mody = data->rows - 1;
            } else if ((y+j) >= data->rows) {
                mody = 0;
            }

            // gets neighbor accounting for edge cases
            index = (mody*data->cols) + modx; 
            neighbor = data->map[index];

            // increments num accounting for cell
            if (index != c_index) {
                if (neighbor == 1) {
                    //pthread_mutex_lock(&my_mutex);
                    num++;
                    //pthread_mutex_unlock(&my_mutex);
                }
            }
        }
    }

    return num;
}

/* the for loop that runs game of life.
 *     data: pointer to gol_data struct
 */
void runGame (struct gol_data *data) {

    int c1 = data->colstart;
    int c2 = data->colend;
    int r1 = data->rowstart;
    int r2 = data->rowend;

    int local_live = 0;

    // checks every cell in current partition
    for(int i = r1; i < r2; i++){
        for(int j = c1; j < c2; j++) {
            int index = i*data->cols + j;
            int cell = data->map[index];

            // gets number of live neighbors of current cell
            int check = getVitals(data, cell, i, j);

            data->temp[i*data->cols + j] = cell;

            // updates cell according to number of live neighbors
            if (cell == 1) {
                if (check <= 1 || check >= 4) {
                    data->temp[index] = 0;
                    local_live--;
                } 
            } else if (cell == 0) {
                if (check == 3) {
                    data->temp[index] = 1;
                    local_live++;
                }
            }
        }
    }

    // updates total_live
    pthread_mutex_lock(&my_mutex);
    total_live += local_live;
    pthread_mutex_unlock(&my_mutex);
    
    // updates map and temp
    int* hold = data->map;
    data->map = data->temp;
    data->temp = hold;
}



/* the gol application main loop function:
 *  runs rounds of GOL,
 *    * updates program state for next round (world and total_live)
 *    * performs any animation step based on the output/run mode
 *
 *   data: pointer to a struct gol_data  initialized with
 *         all GOL game playing state
 */
void *play_gol(void *args) {

    //  at the end of each round of GOL, determine if there is an
    //  animation step to take based on the output_mode,
    //   if ascii animation:
    //     (a) call system("clear") to clear previous world state from terminal
    //     (b) call print_board function to print current world state
    //     (c) call usleep(SLEEP_USECS) to slow down the animation
    //   if ParaVis animation:
    //     (a) call your function to update the color3 buffer
    //     (b) call draw_ready(data->handle)
    //     (c) call usleep(SLEEP_USECS) to slow down the animation

    struct gol_data *data;
    data = (struct gol_data *)args;

    // prints partition information if needed
    if (data->print_partition == 1) {
        printf("tid %d: rows: %d:%d (%d) cols: %d:%d (%d)\n", 
            data->id, data->rowstart, data->rowend - 1, data->rowend - data->rowstart,
            data->colstart, data->colend - 1, data->colend - data->colstart);
    }

    // runs game of life according to data->iters
    for (int i = 0; i < data->iters; i++) {
        runGame(data);
        pthread_barrier_wait(&my_barrier);

        // runs ascii if needed
        if (data->id == 0) {
            if (data->output_mode == OUTPUT_ASCII) {
                system("clear");
                print_board(data, i+1);
                usleep(SLEEP_USECS);
            }
        }
        // runs visi if needed
        if (data->output_mode == OUTPUT_VISI) {
            update_colors(data);
            draw_ready(data->handle);
            usleep(SLEEP_USECS);
        }
        pthread_barrier_wait(&my_barrier);
    }
    return NULL;
}

/* helper function for running visi code that updates color
 * of each cell for each iteration 
 * data: gol game specific data
 * returns: nothing
 */
void update_colors(struct gol_data *data) {
    int i, j, index, buffer;

    int c1 = data->colstart;
    int c2 = data->colend;
    int r1 = data->rowstart;
    int r2 = data->rowend;

    for(i = r1; i < r2; i++){
        for(j = c1; j < c2; j++) {
            index = i * data->cols + j;
            buffer = (data->rows - (i+1))* data->cols + j;

            if (data->map[index] == 1) {
                data->image_buff[buffer] = c3_black;
            } else {
                data->image_buff[buffer] = colors[((data->id)%8)];
            }
        }
    }
}

/* Print the board to the terminal.
 *     data: gol game specific data
 *     round: the current round number
 */
void print_board(struct gol_data *data, int round) {

    int i, j;

    /* Print the round number. */
    fprintf(stderr, "Round: %d\n", round);

    for (i = 0; i < data->rows; i++) {
        for (j = 0; j < data->cols; j++) {
            if (data->map[i*data->cols + j] == 1) {
                fprintf(stderr, " @");
            } else {
                fprintf(stderr, " .");
            }
        }
        fprintf(stderr, "\n");
    }

    /* Print the total number of live cells. */
    fprintf(stderr, "Live cells: %d\n\n", total_live);
}

/**********************************************************/
/***** START: DO NOT MODIFY THIS CODE *****/
/* initialize ParaVisi animation */
int setup_animation(struct gol_data* data) {
    /* connect handle to the animation */
    int num_threads = data->num_threads;
    data->handle = init_pthread_animation(num_threads, data->rows, data->cols, visi_name);
    if (data->handle == NULL) {
        printf("ERROR init_pthread_animation\n");
        exit(1);
    }
    // get the animation buffer
    data->image_buff = get_animation_buffer(data->handle);
    if(data->image_buff == NULL) {
        printf("ERROR get_animation_buffer returned NULL\n");
        exit(1);
    }
    return 0;
}

/* sequential wrapper functions around ParaVis library functions */
void (*mainloop)(struct gol_data *data);

void* seq_do_something(void * args){
    mainloop((struct gol_data *)args);
    return 0;
}

/*
int connect_animation(void (*applfunc)(struct gol_data *data),
        struct gol_data* data)
{
    pthread_t pid;

    mainloop = applfunc;
    if( pthread_create(&pid, NULL, seq_do_something, (void *)data) ) {
        printf("pthread_created failed\n");
        return 1;
    }
    return 0;
}

*/

/***** END: DO NOT MODIFY THIS CODE *****/
/******************************************************/
