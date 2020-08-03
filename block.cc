#include "block.h"
#include "iostream"
#include <vector>
using namespace std;

Block::Block(){}

void Block::shiftDown(char board[18][11], int clearedRow){
    //This method is used to drop pieces when a row is cleared for the board.

    //Placeholder variables to store the location of the moved object
    int newX = -1;
    int newY = -1;

    // First we remove the block from this copy of the board
    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        board[pieceList.at(i).y][pieceList.at(i).x] = ' ';
    }

    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        newX = pieceList.at(i).x;
        newY = pieceList.at(i).y + 1;

        if ((newY < 0 || newY > clearedRow ||
             newX < 0 || newX > 11         ||
             board[newY][newX] != ' '))
        {
            
        }
        else
        {
            pieceList.at(i).y += 1;
        }
        
    }
}
void Block::_translate(bool positive, bool horizontal) {
    int j = (positive) ? 1 : -1;
    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        if (horizontal) {
            pieceList.at(i).x += j;
        } else {
            pieceList.at(i).y += j;
        }
    }
}

void Block::_clockwise() {
    int currentX = 12;
    int currentY = -1;
    int newXPos = 12;
    int newYPos = -1;
    int translateX = 12;
    int translateY = -1;
    vector<vector<int>> rotatedPos;
    vector<int> temp;
    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        if (pieceList.at(i).x < currentX)
        {
            currentX = pieceList.at(i).x;
        }
        if (pieceList.at(i).y > currentY)
        {
            currentY = pieceList.at(i).y;
        }
    }
    rotatedPos.clear();
    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        temp.clear();
        temp.push_back(-1 * pieceList.at(i).y);
        temp.push_back((pieceList.at(i).x));
        rotatedPos.push_back(temp);
    }

    for (int i = 0; (unsigned)i < rotatedPos.size(); i++)
    {
        if (rotatedPos.at(i).at(0) < newXPos)
        {
            newXPos = rotatedPos.at(i).at(0);
        }
        if (rotatedPos.at(i).at(1) > newYPos)
        {
            newYPos = rotatedPos.at(i).at(1);
        }
    }
    translateX = currentX - newXPos;
    translateY = currentY - newYPos;
    for (int i = 0; (unsigned)i < rotatedPos.size(); i++)
    {
        pieceList.at(i).x = rotatedPos.at(i).at(0) + translateX;
        pieceList.at(i).y = rotatedPos.at(i).at(1) + translateY;
    }
}

void Block::_transform(Direction dir)
{
    //Method to transform block's location without bounds checking
    //We investigate the results of this method to see if the transform is valid
    switch (dir)
    {
        case Direction::left:
            _translate(false, true);
            break;

        case Direction::right:
            _translate(true, true);
            break;

        case Direction::up:
            _translate(false, false);
            break;

        case Direction::down:
            _translate(true, false);
            break;

        case Direction::counterclockwise:
            // Counterclockwise is equivalent to calling clockwise 3 times
            _clockwise();
            _clockwise();
            _clockwise();
            break;

        case Direction::clockwise:
            _clockwise();
            break;

        default:
            break;
    }
}

bool Block::_inBounds(char board[18][11])
{
    //This method checks if the block's location is valid/inbound
    //Placeholder vars
    int newX, newY;
    //We check every piece in the block.
    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        newX = pieceList.at(i).x;
        newY = pieceList.at(i).y;
        //We check for 2 things-
        //  1. If the piece lies within the playing area (within 0-11 columns and 0-17 rows )
        //  2. If the piece occupies a position that is already occupied.

        if (newY < 0 || newY > 17 ||
            newX < 0 || newX >= 11 ||
            board[newY][newX] != ' ')
        {
            //If even one piece fails the checks, the block cant be transformed
            return false;
        }
    }
    return true;
}

bool Block::translate(Direction dir, char board[18][11])
{    
    bool flag;
    // First we remove the block from this copy of the board
    // One piece of a block, after transformation, could occupy another pieces location
    //Therefore we, initially, remove the entire block we are trying to rotate.
    for (int i = 0; (unsigned)i < pieceList.size(); i++)
    {
        board[pieceList.at(i).y][pieceList.at(i).x] = ' ';
    }
    //We do the transform and then check if it is valid in _inBounds()
    //If the translate is not valid, flag turns false and the switch
    // statement below runs
    _transform(dir);
    flag = _inBounds(board);
    
    if (!flag) {
        //If this code runs, it means boundsChecking failed for transform 
        //and we cant succesfully make the transformation
        //So we undo our action by runnning translate in the
        // opposite direction
        //This switch calculates what that opposite direction is
        switch (dir) {
            case Direction::left:
                dir = Direction::right;
                break;

            case Direction::right:
                dir = Direction::left;
                break;

            case Direction::up:
                dir = Direction::down;
                break;

            case Direction::down:
                dir = Direction::up;
                break;

            case Direction::counterclockwise:
                dir = Direction::clockwise;
                break;

            case Direction::clockwise:
                dir = Direction::counterclockwise;
                break;

            default:
                break; 
        }
        //We perform translate in the opposite direction
        _transform(dir);
    }

    return flag;
}

