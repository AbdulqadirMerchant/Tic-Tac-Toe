#include <stdio.h>

/*
Making a tictactoe game by giving 2 lines per row and the 3rd line for the 
separator giving you a total play area space of 8 lines without the last row 
having the separator
It's currently a 2 player game where each player enters the row and column
where they want to place their token and the person who matches 3 in a row
horizontally, vertically or diagnolly wins. 
*/


struct Position{
    int row, column;
    char X_V;
};

void make_row(const struct Position positions[], int row)
{
    printf("\n");
    int bar = 0;
    //First for loop is for making the first line
    //Second for loop is for making the second line of the play area of the first row
    int startIndex = (row - 1) * 3;
    int endIndex = 2 + startIndex;

    for (int index = startIndex; index <= endIndex; index++){
        if (positions[index].X_V == 'X')
            printf("  \\/  ");
        else if (positions[index].X_V == 'V')
            printf(" \\  / ");
        else
            printf("      ");

        if (bar < 2) printf("|");
        bar++;

        }

        bar = 0;
        printf("\n");
        for (int index = startIndex; index <= endIndex; index++){
                if (positions[index].X_V == 'X')
                    printf("  /\\  ");
                else if (positions[index].X_V == 'V')
                    printf("  \\/  ");
                else
                    printf(" (%d,%d)", positions[index].row, positions[index].column);

                if (bar < 2) printf("|");
                bar++;
        }
}

void makePlayArea(const struct Position positions[])
{
    printf("\n");
    make_row(positions, 1);
    printf("\n------|------|------");
    make_row(positions, 2);
    printf("\n------|------|------");
    make_row(positions, 3);
    printf("\n\n");
}

//It returns a value so as to check whether a token already exists at the said position
int checkAndInsertX_V(struct Position positions[], int row, int column, char X_V)
{
    for (int index = 0; index < 9; index++){
            if (positions[index].row == row && positions[index].column == column){
                //Checks to see if a token already exists at a given position
                if (positions[index].X_V == '\0'){
                    positions[index].X_V = X_V;
                    return 1;
                }
                return 0;
            }
        }
}

char getWinner(const struct Position positions[])
{
    int winningPossibilities[8][3][2] = {{{1, 1}, {1, 2}, {1, 3}},//Horizontal
                                        {{2, 1}, {2, 2}, {2, 3}}, //Horizontal
                                        {{3, 1}, {3, 2}, {3, 3}}, //Horizontal
                                        {{1, 1}, {2, 1}, {3, 1}}, //Vertical
                                        {{1, 2}, {2, 2}, {3, 2}}, //Vertical
                                        {{1, 3}, {2, 3}, {3, 3}}, //Vertical
                                        {{1, 1}, {2, 2}, {3, 3}}, //Diagnol
                                        {{1, 3}, {2, 2}, {3, 1}}};//Diagnol
    
    //To count how many times the positions in winning possibilities match with the actual positions
    int X_count = 0, V_count = 0;
    //To check for a tie by going through positions to find if there is 
    //atleast one null character and still no win
    int nullCount = 0; 
        
    for (int outerIndex = 0; outerIndex < 8; outerIndex++){
        for (int innerIndex = 0; innerIndex < 3; innerIndex++){
            for (int index = 0; index < 9; index++){
                
                if (positions[index].X_V == '\0'){nullCount++;}
                /*
                Runs through each position of the tokens to see if, in any situation,
                all 3 arrays are identical to the ones in any of the winning possibilities for the same token
                */
                if (positions[index].row == winningPossibilities[outerIndex][innerIndex][0] &&
                    positions[index].column == winningPossibilities[outerIndex][innerIndex][1]){
                    if (positions[index].X_V == 'X'){X_count++;}
                    if (positions[index].X_V == 'V'){V_count++;}
                }
                if (X_count == 3) return 'X';
                if (V_count == 3) return 'V';
            }
            if (nullCount == 0) return 'T';
        }
        X_count = V_count = 0;
    }
    return ' ';
}

int main()
{
    struct Position positions[9];
    int row, column, cur_player;
    row = column = cur_player = 1;
    char winner;

    char X_V;
    //Initialising the tictactoe database
    for (int index = 0; index < 9; index++){
        if (column == 4){
            column = 1;
            row += 1;
        }
        positions[index].row = row;
        positions[index].column = column;
        positions[index].X_V = '\0';
        column += 1;
    }

    printf("Welcome to the Tic Tac Toe Game!\n");
    printf("Enter the row and column to play");
    makePlayArea(positions);
    
    while (1){
        printf("Player %d: \n", cur_player);
        printf("Enter the row: ");
        scanf("%d", &row);

        printf("Enter the column: ");
        scanf("%d", &column);

        X_V = cur_player == 1 ? 'X' : 'V';

        if (!checkAndInsertX_V(positions, row, column, X_V)){
            printf("\nA token is already present at this position! Please try again...\n\n");
            continue;
        }

        cur_player = cur_player == 1 ? 2 : 1;
        makePlayArea(positions);

        winner = getWinner(positions);
        if (winner == 'T'){
            printf("This game is a tie!! Try again next time...");
            break;
        }
        if (winner != ' '){
            printf("%c is the winner of this game", winner);
            break;
        } 
    }
    return 0;
}