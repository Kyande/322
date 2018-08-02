// KYANDE MICHAEL JOHN.
// P15 / 34906 / 2014.
// do circulant matrix in C.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 7

struct do_circulant
{
    /* data */
    int vec[NUM];
    int matrix[NUM][NUM];

};

struct do_circulant shiftright(struct do_circulant x)
{
    struct do_circulant r = x;

    int temp = r.vec[NUM - 1];

    for (size_t i = 0; i < NUM - 1; i++)
    {
        // swap elements
        r.vec[i+1] = x.vec[i];
    }
    r.vec[0] = temp;

    return r;   
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    // variables.
    struct do_circulant dc;
    // generate values for number arrays.
    for(int i = 0; i < NUM; i++){
        dc.vec[i] = rand() % 10;
    } 
    // generate the matrix.
    for(size_t i = 0; i < NUM; i++)
    {   
        if(i > 0){
            // shift elements right.
            dc = shiftright(dc);
        }
        for(size_t j = 0; j < NUM; j++)
        {
            dc.matrix[i][j] = dc.vec[j];
        }
    }
    // print the matrix.
    for (size_t i = 0; i < NUM; i++)
    {
        for (size_t j = 0; j < NUM; j++)
        {
            printf("%d  ", dc.matrix[i][j]);
        }
        printf("\n");
    }
    // exit.
    return 0;
}
