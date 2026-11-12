# Tic-Tac-Toe vs. Computer

A console-based Tic-Tac-Toe game written in C where a human player (O) competes against a randomized computer opponent (X). Built as an individual project for COMP 120 at Capilano University.

## Features
- **Input Validation:** Safely handles invalid user inputs (letters, out-of-bound numbers, etc.) using `fgets` and `sscanf` without crashing or entering infinite loops.
- **Dynamic Display:** The board updates in real-time, replacing empty spaces with their corresponding numerical index (0-8) to clearly show available moves.
- **Randomized Opponent Moves:** The computer opponent uses `rand()` seeded with `time()` to ensure different gameplay every session.
- **Continuous Play:** Players can choose to play multiple rounds in a row without restarting the application.

## Prerequisites
- C compiler (GCC/Clang)
- JetBrains CLion

## How to Build and Run in CLion
1. Open CLion and select **File > Open**, then navigate to this project folder.
2. Ensure `main.c` is set up in your `CMakeLists.txt` 
3. Click the green **Run** triangle in the top right corner of the CLion window (or press `Shift + F10`).
4. Interact with the game directly in the CLion Run tool window at the bottom of the screen.

## How to Compile via Terminal
If you prefer running this from the command line outside of CLion:

```bash
gcc main.c -o tictactoe
./tictactoe
