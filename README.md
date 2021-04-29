# Extended Crossword Puzzle 
This project is implementation of a well-known Crossword Puzzle Game. The user will be asked to solve the crossword puzzle under a particular time period and the score will be generated afterwards. The difficulty of the game will be dependent on the level chosen by the user. Meanings of the word found will also be shown to the user.

# Methodology
The data structure used are Trees(non-linear data structure) and Stack(linear data structure) plus backtracking algorithm to find the specific word input by user in the puzzle. In
addition to this Filing is used and have implemented one of the OS concepts known as Multithreading.

## Trees
1) **AVL Tree:** For tracking that user do not re-enter the same word twice and get the points.
2) **Red-Black Tree:** For storing the dictionary and quick access to the meaning of the word found in the puzzle by the user.

## Backtracking
For finding the word in the puzzle enter by the user in all 8 directions (right, left, down, up, left-upper diagonal, leftlower diagonal, right-upper diagonal, right-lower diagonal).

## Filing
For storing dictionary and puzzles for each level.

## Multithreading
For Timer function to run in parallel with the program we have used the concept of Multithreading.

## Stack
For maintaining the position of Timer when timer function is run in parallel with the program.
