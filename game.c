#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        //printf("Usage: %s <arg1> <arg2> <arg3>\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iter = atoi(argv[3]);

    //printf("Arguments received: %d, %d, %d\n", width, height, iter);

    int board1[height][width];
    int board2[height][width];

    memset(board1, 0, sizeof(board1));
    memset(board2, 0, sizeof(board2));

    int *current    = NULL;
    int *next       = NULL;

    return 0;
}
