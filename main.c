#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>  
#include <stdbool.h>

// Function prototypes
int validateUserInt(int upperLimit, int lowerLimit);
char validateYesOrQuit(); 
void getVirtualMove(char board[]);
void getUserMove(char board[]);
void printCurrBoard(char board[]);
bool checkWin (char board[], char *winner);
void wipeBoard(char board[]);
void playGame();

/*
main:
Entry point of the program. Initializes the random number generator and 
runs the main game loop, prompting the user to play again or quit after each game.

Parameters:
None
Return:
0 upon successful execution
*/
int main(void) {
    bool keepPlaying = true;
    char userSelection;
    
    srand(time(NULL));

    printf("=====================================\n");
    printf("        TIC-TAC-TOE vs COMPUTER      \n");
    printf("=====================================\n");

    do {
        playGame();
        
        printf("Do you want to play again?\n");
        printf("Enter 'y' to play again or 'q' to quit: ");
        userSelection = validateYesOrQuit();
        
        if (userSelection == 'q' || userSelection == 'Q') {
            keepPlaying = false;
        }
    } while (keepPlaying == true);
    
    return 0;
}

/*
playGame:
Handles a single game from start to finish. Alternates turns between the user 
and the computer for a maximum of 9 turns. Checks for wins or draws and 
prints the final result.

Parameters:
None
Return:
None
*/
void playGame() {
    char board[9];
    bool win = false;
    char winner = ' ';
    
    wipeBoard(board);
    
    printf("You are O and you go first. The computer is X.\n");
    printf("On your turn, type the number of an empty square:\n");
    
    for (int turns = 0; turns < 9; turns++) {
        printCurrBoard(board);
        
        if (turns % 2 == 0) {
            getUserMove(board);
        } else {
            getVirtualMove(board);
        }
        
        win = checkWin(board, &winner);
        if (win == true) {
            break;
        }
    }
    
    printCurrBoard(board);
    
    if (win == true) {
        if (winner == 'O') {
            printf("You win!\n\n");
        }
        else if (winner == 'X') {
            printf("Computer wins. You lose!\n\n");
        }
    } else {
        printf("It's a draw!\n\n");
    }
}

/*
validateUserInt:
This function reads user input and checks that it meets the condition for it to be a valid
integer in the specified range. It gets rid of invalid input like letters, extra characters, mixed input, or
values outside the provided range.

Parameters:
int upperLimit --> Maximum input value
int lowerLimit --> Minimum input value
Return:
Valid integer provided by the user that is inside the accepted range and not of an unsupported kind
*/
int validateUserInt(int upperLimit, int lowerLimit) {
    char buffer[100];
    int userInt;
    int parseResult;
    char extra;
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error! Please enter a number between %d and %d inclusive\n", lowerLimit, upperLimit);
            continue;
        }
        
        parseResult = sscanf(buffer, "%d %c", &userInt, &extra);
        
        if (parseResult != 1 || userInt < lowerLimit || userInt > upperLimit) {
            printf("Invalid input! Please enter a number between %d and %d inclusive:\n", lowerLimit, upperLimit);
        } else {
            return userInt;
        }
    }
}

/*
validateYesOrQuit:
This function reads user input and ensures it is a valid 'y' (yes) or 'q' (quit) character.
It rejects invalid characters, numbers, and extra strings.

Parameters:
None
Return:
A valid character ('y', 'Y', 'q', or 'Q') indicating the user's choice to play again or quit
*/
char validateYesOrQuit() {
    char buffer[100];
    char choice;
    char extra;
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }
        
        int parseResult = sscanf(buffer, " %c %c", &choice, &extra);
        if (parseResult == 1 && (choice == 'y' || choice == 'Y' || choice == 'q' || choice == 'Q')) {
            return choice;
        }
        printf("Invalid input! Please enter 'y' to play again or 'q' to quit: ");
    }
}

/*
getVirtualMove:
This function generates a random integer from 0-8 and fills in the corresponding 
square on the board with an 'X', provided the square is currently empty.

Parameters:
char board[] --> Character array of index 0-8 that stores 'O', 'X', or empty space
Return:
None
*/
void getVirtualMove(char board[]) {
    int virtualMoves;
    
    printf("Computer (X) is thinking...\n");
    sleep(1);
    
    do { 
        virtualMoves = rand() % 9;
    } while (board[virtualMoves] != ' ');
    
    board[virtualMoves] = 'X';
    printf("Computer (X) chose square %d. Your move next!\n", virtualMoves);
}

/*
getUserMove:
This function prompts the user for a number 0-8 to select a specific square on the board.
It checks that the chosen square is empty before storing an 'O' in that position.

Parameters:
char board[] --> Character array of index 0-8 that stores 'O', 'X', or empty space
Return:
None
*/
void getUserMove(char board[]) {
    int userMove; 
    bool validMove = false;
    
    do {
        printf("Your turn (O). Enter a square number (0-8): ");
        userMove = validateUserInt(8, 0); 
        
        if (board[userMove] == ' ') {
            validMove = true;
        }
        else {
            printf("  That square is already taken. Choose an empty one.\n");
        }
    } while (validMove == false);
    
    board[userMove] = 'O'; 
}

/*
printCurrBoard:
This function prints the current state of the board. It uses a temporary array to 
replace empty spaces with their corresponding index number (0-8), helping the user 
identify available moves.

Parameters:
char board[] --> Character array of index 0-8 that stores 'O', 'X', or empty space
Return:
None
*/
void printCurrBoard(char board[]) {
    char c[9];
    int i;
    
    for (i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            c[i] = '0' + i; 
        } else {
            c[i] = board[i];
        }
    }

    printf("\n");
    printf("  %c  |  %c  |  %c\n", c[0], c[1], c[2]);
    printf("-----------------\n");
    printf("  %c  |  %c  |  %c\n", c[3], c[4], c[5]);
    printf("-----------------\n");
    printf("  %c  |  %c  |  %c\n\n", c[6], c[7], c[8]);
}

/*
checkWin:
This function checks if there is a win. It checks all the values in a determined row to check if there was a
horizontal win, all the values in a determined column to check if there was a vertical win, and all the
values in the diagonals of the board.

Parameters:
char board[] --> Character array of index 0-8 that stores 'O', 'X', or empty space
char *winner --> a pointer character used to store which player won ('X' or 'O')
Return:
Boolean variable that returns true if there is a win, and returns false if not
*/
bool checkWin (char board[], char *winner) {
    int i;
    
    for (i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i+1] && board[i+1] == board[i+2]) {
            *winner = board[i];
            return true;
        }
    }
    for (i = 0; i < 3; i++) {
        if (board[i] != ' ' && board[i] == board[i+3] && board[i+3] == board[i+6]) {
            *winner = board[i];
            return true;
        }
    }
    if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8]) {
        *winner = board[0];
        return true;
    }
    if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]) {
        *winner = board[2];
        return true;
    }
    
    return false;
}

/*
wipeBoard:
This function deletes all stored variables in the board array by setting them 
to empty spaces when a new game is started.

Parameters:
char board[] --> Character array of index 0-8 that stores 'O', 'X', or empty space
Return:
None
*/
void wipeBoard(char board[]) {
    int i;
    
    for (i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}