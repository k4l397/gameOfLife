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
};
typedef struct Game game;

// Counts number of live cells around the current one (at position (i, j))
int countLive(colony col, int i, int j){
    int liveCells = 0;
    int startRow = (i - 1 == -1) ? i : i - 1;
    int startColumn = (j - 1 == -1) ? j : j - 1;
    int endRow = (i + 1 == MAX) ? i : i + 1;
    int endColumn = (j + 1 == MAX) ? j : j + 1;
    for(int a = startRow; a <= endRow ; a++){
        for(int b = startColumn; b <= endColumn; b++){
            if(col[a][b] == ALIVE) liveCells++;
        }
    }
    if(col[i][j] == ALIVE) liveCells--;
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
    return g;
}

// Updates the state of the current game to a new state
game *newState(game *g){
    game *n = newGame();
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            if(g->col[i][j] == '#' || g->col[i][j] == '.'){
                if(g->col[i][j] == ALIVE && !(countLive(g->col, i, j) == 2 || countLive(g->col, i, j) == 3)){
                    n->col[i][j] = DEAD;
                }
                else if(g->col[i][j] == DEAD && countLive(g->col, i, j) == 3){
                    n->col[i][j] = ALIVE;
                }
                else{
                    n->col[i][j] = g->col[i][j];
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
