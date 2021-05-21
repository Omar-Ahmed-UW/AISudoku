/*
 * Puzzle.cpp
 * CSS 342
 * Author: Omar Ahmed
 * 5/20/21
 * 
 * This is the Puzzle class implementation file that includes all
 * code for class methods and nested classes.
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

#include "Puzzle.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Square constructor sets values to default of -1 and variable if not assigned using initializer list.
Puzzle::Square::Square(int value, bool flag): value_{value}, flag_{flag}
{}

// Accessor function returns value_ member of Square object by refrence.
int& Puzzle::Square::getValue()
{
    return value_;
}

// Modifier function sets value_ member to passed in value.
void Puzzle::Square::setValue(int value)
{
    value_ = value;
}

// Accessor function returns flag_ member of Square object by refrence.
bool& Puzzle::Square::getFlag()
{
    return flag_;
}

// Default constructor initializes all members of Puzzle class to default values of 0 and "" using initializer list.
Puzzle::Puzzle(): size_{0}, numEmpty_{0}, input_{""}
{}

// Default destructor deletes array.
Puzzle::~Puzzle()
{}

/*
* No return function called by >> istream operator to fill array using 'input_' string.
* Iterates through the string converting each char to an int and setting the Square object's
* value to that.
* If it encounters '0' sets the Square to be a variable status and sets its value to -1. 
*/
void Puzzle::filler()
{
    int count = 0;
    // Loop to iterate through rows. 
    for(int i = 0; i < 9; i++)
    {
        // Loop to iterate throuhg the columns.
        for(int j = 0; j < 9; j++)
        {
            // Takes each char from the string input_
            stringstream letter(string(1, input_[count]));
            int digit = 0;
            // Converts it from char to int.
            letter >> digit;
            // Checks if 0 increases size_ and calls default constructor.
            if(digit == 0){
                array[i][j] = Square();
                size_++;
            } else { // Else makes it a fixed Square object.
                array[i][j] = Square(digit, false);
            }
            count++;
        }
    }
    // Sets inital value of numEmpty_.
    numEmpty_ = size_;
}

/*
 * Private function that calls locateCompare() and checkSurroundings() functions
 * to check if value is repeated.
 * Returns bool by value whether the value is valid to be inserted.
 */
bool Puzzle::isValid(int x, int y, int value)
{
    if(checkSurroundings(x, y, value) == false && locateCompare(x, y, value) == false){
        return false;
    } else {
        return true;
    }
}

/*
 * Private function that takes x and y coordinates as well as a value from 1 to 9.
 * Finds which grid the cell at x and y belongs to then compares value passed in to
 * values in that grid and returns bool by value whether the value is repeated or not.
 */
bool Puzzle::locateCompare(int x, int y, int value)
{
    // If Square Object at given coordinates is fixed returns true.
    if(array[x][y].getFlag() == false){
        return true;
    } else {
        bool flag = false;
        int row = 0;
        int col = 0;
        // Find where x and y coordinates sit in the Puzzle by finding closest corner of a grid.
        for(int i = 2; i < 9; i += 3){
            if(x <= i && x >= (i - 2)){
                row = i;
            }
            if(y <= i && y >= (i - 2)){
                col = i;
            }
        }

        // Compare the value passed in with all values in its grid
        for(int i = row - 2; i <= row && flag == false; i++){
            for(int j = col - 2; j <= col && flag == false; j++){
                if(array[i][j].getValue() == value){
                    flag = true;
                } else {
                    flag = false;
                }
            }
        }
        return flag;
    }
}

/*
 * Private function that takes x and y coordinates as well as a value from 1 to 9.
 * compares value passed in to values in the same row and column and returns bool
 * by value whether the value is repeated or not.
 */
bool Puzzle::checkSurroundings(int x, int y, int value)
{    
    bool flag = false;
    // Compare passed in value with all values in its row and column to check if valid.
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(array[i][y].getValue() == value){
                flag = true;
            }
            if(array[x][i].getValue() == value){
                flag = true;
            }
        }
    }
    return flag;
}

/*
 * Public function to return the value of the Square object at passed in coordinates.
 * Takes x and y as parameters and returns getValue() of the Square object as a const. 
 */
const int Puzzle::get(int x, int y)
{
    // Outputs error if passed in coordinate values are invalid.
    if(x > 8 || y > 8 || x < 0 || y < 0){
        cerr << "Passed in coordinates are out of bounds!" << endl;
    } else {
        return array[x][y].getValue();
    }
    return -1;
}

/*
 * Public function takes x and y coordinates as well as value as input.
 * Sets value to sepcified Square object if valid, increments numEmpty_, and returns true.
 * Returns false if value cannot be set and outputs error.
 */
bool Puzzle::set(int x, int y, int value)
{
    // Outputs error if passed in coordinate values are invalid.
    if(x > 8 || y > 8 || x < 0 || y < 0){
        cerr << "Passed in coordinates are out of bounds!" << endl;
    } else {
        // Checks if value is valid to be inserted and if it is a variable Square object.
        if(isValid(x, y, value) == false && array[x][y].getFlag() == true){
            array[x][y].setValue(value);
            numEmpty_--;
            return true;
        } else { // else outputs error.
            cerr << "Passed in value is invalid!";
        }
    }
    return false;
}

// Function returns 'numEmpty_' member by value. 
int Puzzle::numEmpty()
{
    return numEmpty_;
}

// Function returns 'size_' member by value.
int Puzzle::size()
{
    return size_;
}

/*
 * Recursive function that contains a backtracking algorithm used to solve the Puzzle object it is called in.
 * Takes x and y coordinates for input and returns a bool for whether the Puzzle can be solved or not.
 * A puzzle is unsolvable if it is invalid from the beginning or it cannot complete a specific Square object. 
 */
bool Puzzle::solve(int x, int y)
{
    // Base condition checks if counter is at the end of the list.
    if(x == 9 && y == 0){
        return true;
    } 

    // Finds next empty Square and goes to it ignoring the current Square
    // with each recurssive call.
    if(array[x][y].getValue() != -1){
        y++;
        if(y == 9){
            y = 0;
            x++;
        }
        return solve(x, y);
    }

    // Iterates through all possible values to determine which one fits.
    for(int num = 1; num <= 9; num++){
        // Checks if value is valid.
        if(isValid(x, y, num) == false){
            // Sets value.
            set(x, y, num);
            int row = x;
            int col = y + 1;
            // Increments element to pass in to recurssive call. 
            if(col == 9){
                col = 0;
                row++;
            }

            // Recurssive call checks if this element fits with later elements.
            if(solve(row, col) == true){ // Backtracking functionality.
                return true;
            } 
            // If it does not fit then goes back and revaluates it.
            array[x][y].setValue(-1);
        }
    }
    return false;
}

/*
 * istream >> operator that takes in cin input and sets the 'input_' member to it.
 * Declared as a friend and is implemented as an ordinary function.  
 */
std::istream& operator>>(std::istream& is, Puzzle& puzzle)
{
    is >> puzzle.input_;
    puzzle.filler();
    return is;
}

/*
 * ostream << operator that outputs the Puzzle object by iterating through elements in the array
 * and printing their value in specified format.
 * Declared as a friend and is implemented as an ordinary function. 
 */
std::ostream& operator<<(std::ostream& os, Puzzle& puzzle)
{
    int count1 = 0;
    int count2 = 0;
    // Adds grid for readabilty.
    os << "\n" << "   0 1 2 3 4 5 6 7 8 \n \n";
    for(int i = 0; i < 9; i++)
    {
        count1 = 0;
        // Adds side grid for readabilty.
        os << i << "  ";
        // Iterates through all of array and prints each element.
        for(int j = 0; j < 9; j++)
        {
            if(puzzle.get(i, j) == -1){
                os << " ";
            } else {
                os << puzzle.get(i, j);
            }
            count1++;
            // adds dividers.
            if(count1 % 3 == 0 && count1 != 9){
                os << "|";
            } else{
                os << " ";
            }
        }
        os << "\n";
        count2++;
        // adds dividers.
        if(count2 % 3  == 0 && count2 != 9){
            os << "  ------+-----+------" << endl;
        }
    } 
    return os;
}


int main(){
    Puzzle p;

    cin >> p;
    cout << p << endl << endl;
    // int x, y, value = 0;
    // while(p.numEmpty() > 0){
    //     cin >> x >> y >> value;
    //     p.set(x, y, value);
    //     cout << p << endl << endl;
    // }
    cout << p.solve(0,0) << endl;
    cout << p << endl << endl;
    return 0;
}