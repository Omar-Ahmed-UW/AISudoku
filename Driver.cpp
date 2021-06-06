#include <Puzzle.h>
/*
 * Driver.cpp
 * CSS 342
 * Author: Omar Ahmed
 * 6/6/21
 * 
 * This is the Puzzle class header file that includes all
 * member declerations of the Puzzle class.
 * 
 * The Puzzle class creates a sudoku game that allows a user to complete
 * the sudoku puzzle following the three rules of the game:
 * A number cannot be repeated in the same row, column, or 3 by 3 grid.
 * 
 * The Puzzle class will create this game using 'Square' objects that 
 * hold a cell's value and state(a value from 1 to 9 and a variable or fixed state).
 * These Square objects are stored in a two-dimensional array to mimic the 
 * shape of a sudoku puzzle.
 * 
 * To create a puzzle the program takes in an input through the cin '>>' operator of 81 digits
 * where '0' counts as an variable empty cell to be filled.
 * To print a puzzle the program uses the cout '<<' operator and draws a table filled with the
 * corresponding values for each cell.
 * 
 * To access a cell's value, the get(x, y) function is called which returns the value associated
 * with the Square at the passed in coordinates as const.
 * While setting a cell's value is done using the set(x, y, value) function which sets the Square
 * object at the passed in coordinates to the passed in 'value'. This is ofcourse if the value is
 * is valid to be inserted at that location.
 * 
 * The Puzzle class also retreives the number of empty Squares before any insertion is done using
 * the size() function which returns the int value by value.
 * It can also retrieve the current number of empty Squares using the numEmpty() function which 
 * returns the int value by value. 
 * 
 * Additionally, the sudoku puzzle can be automatically solved by the solve() function which when
 * called uses a recurrsively backtracking algorithim to find the correct solution. This function
 * returns true if it a solvable puzzle and false if it is not.
 * 
 * Hope you enjoy!
 * 
 */

// Main function to run test of taking input and using recurssive backtracking alogrithm solve()
// solve it.
int main(){
    Puzzle p;
    cin >> p;
    cout << p << endl << endl;

    cout << p.solve(0,0) << endl;
    cout << p << endl << endl;
    return 0;
}