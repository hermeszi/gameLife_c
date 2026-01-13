#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void print_board(unsigned int width, unsigned int height, bool board[][width])
{
    for (unsigned int row = 0; row < height; row++) 
    {
        for (unsigned int col = 0; col < width; col++) 
        {
            putchar(board[row][col] ? 'O' : ' ');
        }
        putchar('\n');
    }
}

unsigned int count_neighbors(int width, int height, bool board[][width], unsigned int row, unsigned int col)
{
    unsigned int count = 0;
    for (int nrow = -1; nrow <= 1; nrow++) 
    {
        for (int ncol = -1; ncol <= 1; ncol++) 
        {
            if (nrow == 0 && ncol == 0) continue; // Skip the cell itself
            int nx = col + ncol;
            int ny = row + nrow;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && board[ny][nx]) 
            {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    // 1. validate argc
    if (argc != 4) 
    {
       //printf("Usage: %s <arg1> <arg2> <arg3>\n", argv[0]);
        return 1;
    }

    // 2. parse width, height, iterations
    unsigned int width = atoi(argv[1]);
    unsigned int height = atoi(argv[2]);
    unsigned int iter = atoi(argv[3]);
    //printf("Arguments received: %u, %u, %u\n", width, height, iter);

    // 3.declare boards and pointers
    bool board1[height][width];
    bool board2[height][width];
    bool (*current)[width]    = board1;
    bool (*next)[width]       = board2;

    // 4. initialize boards to zero
    memset(board1, 0, sizeof(board1));
    memset(board2, 0, sizeof(board2));

    // 5. drawing phase: read commands from standard input, update board
    char buffer[1];
    ssize_t bytesRead = 0;
    bool penDown = false;
    unsigned int x = 0, y = 0;
    while (bytesRead = read(STDIN_FILENO, buffer, 1), bytesRead > 0) 
    {
        if (penDown) 
        {
            current[y][x] = true; // Mark the cell as live
        }   

        char command = buffer[0];
        if (command == 'x' || command == 'X') 
        {
            penDown = !penDown;
        } 
        else if (command == 'W' || command == 'w')
        {  
            if (y > 0) y--;
        } 
        else if (command == 'S' || command == 's') 
        {
            if (y < height - 1) y++;
        } 
        else if (command == 'A' || command == 'a') 
        {
            if (x > 0) x--;
        } 
        else if (command == 'D' || command == 'd') 
        {
            if (x < width - 1) x++;
        } 
        else
        {
            ; // ignore unknown commands
        }
    }
    if (bytesRead < 0) 
    {
        //perror("Error reading from stdin");
        return 1;
    }

    // 6. conway's game of life iterations
    for (unsigned int i = 0; i < iter; i++) 
    {
        for (unsigned int row = 0; row < height; row++) 
        {
            for (unsigned int col = 0; col < width; col++) 
            {
                unsigned int neighbors = count_neighbors(width, height, current, row, col);
                if (current[row][col]) // Cell is alive
                {
                    // A live cell survives if it has 2 or 3 neighbors
                    // Otherwise, it dies
                    next[row][col] = (neighbors == 2 || neighbors == 3);
                } 
                else //Cell is dead
                {
                    // A dead cell becomes alive if it has exactly 3 neighbors
                    // Otherwise, it remains dead
                    next[row][col] = (neighbors == 3);
                }
            }
        }
        // Swap the boards
        bool (*temp)[width] = current;
        current = next;
        next = temp;
        memset(next, 0, sizeof(*next)); // Clear the next board for the next iteration
    }

    print_board(width, height, current);

    return 0;
}
