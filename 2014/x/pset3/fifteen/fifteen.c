/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;
// board width (dimension is d x d so we need a second variable)
int bwidth;

//count variable for winning function
int count = 0;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX){
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        //clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("You win!!! :D \n");
            break;
        }
        
        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }
         
        // sleep for animation's sake
        usleep(500000);
       
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}
/**
 * Greets player.
 */
void greet(void)
{
    //clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    //init boardwidth with d (need a second variable that we will not multiply)
    bwidth = d;
    //Multiply d by d to have the board dimension
    d *= d;
    //Substract 1 because there is one empty space
    d -= 1;
     
    //Check if boardwidth is odd
    bool even;
    if((bwidth%2) != 0){
        even = false;
    }else {
        even = true;
    }
    //Populate board[i][j] with all the numbers
    for(int i = 0; i < bwidth; i++){
        for(int j = 0; j < bwidth; j++){
            board[i][j] = d;
            d--;
        }
    }
    //Change position of number 1 and 2 if board is even
    if(even){
        board[bwidth-1][bwidth-2] = 2;
        board[bwidth-1][bwidth-3] = 1;   
    };
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    // Draw the numbers
    for(int i = 0; i < bwidth; i++){
        for(int j = 0; j < bwidth; j++){
            printf("%5d", board[i][j]);
        }
        // When i reach board width, print new line
        if(i < bwidth){
                printf("\n");
        }
    }   
}
/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    // search for user input. If found return true 
    bool inputUserFound;
    int positionI;
    int positionJ;
    int positionIzero;
    int positionJzero;

    for(int i = 0; i < bwidth; i++){
        for(int j = 0; j < bwidth; j++){
            if(tile == board[i][j]){
                positionI = i;
                positionJ = j;
                inputUserFound = true;
            }
            if(0 == board[i][j]){
                positionIzero = i;
                positionJzero = j;
            }
        }
    }
    //If inputUser is found, look if the tile can be legaly moved
    // look also for the zero
    if(inputUserFound){
        // check position of the user's input with the zero position (can it be legaly moved ?)
        if(positionIzero == positionI && positionJzero == positionJ-1 ){
            board[positionIzero][positionJzero] = tile;
            board[positionI][positionJ] = 0;  
            return true;
        }
        else if(positionIzero == positionI+1 && positionJzero == positionJ){
            board[positionIzero][positionJzero] = tile;
            board[positionI][positionJ] = 0;
            return true;
        }
        else if(positionIzero == positionI && positionJzero == positionJ+1){
            board[positionIzero][positionJzero] = tile;
            board[positionI][positionJ] = 0;  
            return true;
        }
        else if(positionIzero == positionI-1 && positionJzero == positionJ){
            board[positionIzero][positionJzero] = tile;
            board[positionI][positionJ] = 0; 
            return true;
        }
    }

    //if illegal move return false
    return false;
}



/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.

 */
bool won(void)
{
    for(int i = 0; i < bwidth; i++){
        for(int j = 0; j < bwidth; j++){
            if(board[i][j] == count){
                count++;
            }else{
                count = 0;
            }
            if(count == bwidth*2){
                return true;
            }
        }
    }
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
