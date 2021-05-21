#pragma once

/*
 * Puzzle.h
 * CSS 342
 * Author: Omar Ahmed
 * 5/20/21
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

#include <iostream>
#include <string>

using namespace std;

// Puzzle class declaration.
class Puzzle
{
    // Private member declarations. 
private:

    /*
     * Private nested Square class that holds the 'value_' and 'flag_'
     * which hold value and status associated with each cell.
     * 
     * value_ holds values from 1 to 9 as well as -1 and flag holds true for 'variable'
     * and false for 'fixed'.
     * 
     * Contains constructor as well accessors and modifiers for both members.
     */ 
    class Square
    {
    private:
        int value_;
        bool flag_;
    public:
        // Square constructor sets values to default of -1 and variable if not assigned.
        Square(int value = -1, bool flag = true);
        // Accessor function returns value_ member of Square object by refrence.
        int& getValue();
        // Modifier function sets value_ member to passed in value.
        void setValue(int value);
        // Accessor function returns flag_ member of Square object by refrence.
        bool& getFlag();
    };

    // 'size_' value set in filler() function. Refers to the size of empty Square objects after Puzzle is constructed.
    int size_;
    // 'numEmpty_' value refers to the current number of unmodified squares.
    int numEmpty_;

    // Square array declaration to hold 9 rows and 9 columns.
    Square array[9][9];
    
    /*
     * Private function that takes x and y coordinates as well as a value from 1 to 9.
     * Finds which grid the cell at x and y belongs to then compares value passed in to
     * values in that grid and returns bool by value whether the value is repeated or not.
     */
    bool locateCompare(int x, int y, int value);

    /*
     * Private function that takes x and y coordinates as well as a value from 1 to 9.
     * compares value passed in to values in the same row and column and returns bool
     * by value whether the value is repeated or not.
     */
    bool checkSurroundings(int x, int y, int value);

    /*
     * Private function that calls locateCompare() and checkSurroundings() functions
     * to check if value is repeated.
     * Returns bool by value whether the value is valid to be inserted.
     */
    bool isValid(int x, int y, int value);

public:
    
    // 'input_' string value set by >> istream operator and used by filler() to build Puzzle object.
    string input_;
    
    // Default constructor initializes all members of Puzzle class to default values of 0 and "" using initializer list.
    Puzzle();
    // Default destructor deletes array.
    ~Puzzle();

    /*
     * No return function called by >> istream operator to fill array using 'input_' string.
     * Iterates through the string converting each char to an int and setting the Square object's
     * value to that.
     * If it encounters '0' sets the Square to be a variable status and sets its value to -1. 
     */
    void filler();

    /*
     * Public function to return the value of the Square object at passed in coordinates.
     * Takes x and y as parameters and returns getValue() of the Square object as a const. 
     */
    const int get(int x, int y);

    /*
     * Public function takes x and y coordinates as well as value as input.
     * Sets value to sepcified Square object if valid, increments numEmpty_, and returns true.
     * Returns false if value cannot be set and outputs error.
     */
    bool set(int x, int y, int value);

    // Function returns 'numEmpty_' member by value. 
    int numEmpty();
    // Function returns 'size_' member by value.
    int size();

    /*
     * Recursive function that contains a backtracking algorithm used to solve the Puzzle object it is called in.
     * Takes x and y coordinates for input and returns a bool for whether the Puzzle can be solved or not.
     * A puzzle is unsolvable if it is invalid from the beginning or it cannot complete a specific Square object. 
     */
    bool solve(int x, int y);
    
    /*
     * istream >> operator that takes in cin input and sets the 'input_' member to it.
     * Declared as a friend and is implemented as an ordinary function. 
     */
    friend std::istream& operator>>(std::istream& is, Puzzle& puzzle);

    /*
     * ostream << operator that outputs the Puzzle object by iterating through elements in the array
     * and printing their value in specified format.
     * Declared as a friend and is implemented as an ordinary function. 
     */
    friend std::ostream& operator<<(std::ostream& os, Puzzle& puzzle);
};