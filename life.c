#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO:
// - Make array variable sizes
// - Improve readability

enum{ MAX = 10 , ALIVE = '#', DEAD = '.' };

// A colony is a 2D array of characters.  Each row is a null-terminated string,
// and the rows are terminated by an empty string.
typedef char colony[MAX][MAX];

// State contains the colony and the current position being checked
// on the board.
struct Game{
    colony col;
    int row, column;
};
typedef struct Game game;

// Counts number of live cells around the current one
int countLive(game *g){
    int liveCells = 0;
    int startRow = (g->row - 1 == -1) ? g->row : g->row - 1;
    int startColumn = (g->column -1 == -1) ? g->column : g->column - 1;
    int endRow = (g->row + 1 == MAX) ? g->row : g->row+1;
    int endColumn = (g->column + 1 == MAX) ? g->column : g->column + 1;
    for(int i = startRow; i <= endRow ; i++){
        for(int j = startColumn; j <= endColumn; j++){
            if(g->col[i][j] == ALIVE) liveCells++;
        }
    }
    if(g->col[g->row][g->column] == ALIVE) liveCells--;
    return liveCells;
}

// Read a line of text from the standard input into the given character array.
// Make sure that any pending text on the standard output has been printed
// first.  Remove the newline (\r or \n or both).
void readline(int n, char line[n]) {
    fflush(stdout);
    fgets(line, n, stdin);
    line[strcspn(line, "\r\n")] = '\0';
}

// Read a colony from the standard input into the given matrix, with the rows
// terminated by an empty string.
void readColony(colony col) {
    for (int i=0; ! feof(stdin); i++) {
        readline(MAX, col[i]);
        if (feof(stdin)) strcpy(col[i], "");
    }
}

// Print out a colony.
void print(colony col) {
    for (int i=0; strlen(col[i]) != 0; i++) {
        printf("%s\n", col[i]);
    }
}

// Creates pointer to game of life board.
game *newGame(){
    game *g = malloc(sizeof(game));
    readColony(g->col);
    g->row = 0, g->column = 0;
    return g;
}

// Updates the state of the current game to a new state
game *newState(game *g){
    game *n = newGame();
    for(g->row = 0; g->row < MAX; g->row++){
        for(g->column = 0; g->column < MAX; g->column++){
            if(g->col[g->row][g->column] == '#' || g->col[g->row][g->column] == '.'){
                if(g->col[g->row][g->column] == ALIVE && !(countLive(g) == 2 || countLive(g) == 3)){
                    n->col[g->row][g->column] = DEAD;
                }
                else if(g->col[g->row][g->column] == DEAD && countLive(g) == 3){
                    n->col[g->row][g->column] = ALIVE;
                }
                else{
                    n->col[g->row][g->column] = g->col[g->row][g->column];
                }
            }
        }
    }
    free (g);
    return n;
}

void run(){
    game *g = newGame();
    g = newState(g);
    print(g->col);
}

int main(int n, char *args[n]) {
    if(n > 0){
        run();
    }
    else{
        exit(1);
    }
}
