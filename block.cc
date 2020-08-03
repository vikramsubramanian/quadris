#include "block.h"
#include "iostream"
#include <vector>
using namespace std;

Block::Block(){

}

void Block::shiftDown(char board[18][11], int clearedRow){
    //Placeholder variables to store the location of the moved object
    int newX = -1;
    int newY = -1;

    // First we remove the block from this copy of the board

    for (int i = 0; i < pieceList.size(); i++)
    {
        newX = pieceList.at(i).x;
        newY = pieceList.at(i).y + 1;
        //FIX THIS!
        if (!(newY < 0 || newY > clearedRow ||
              newX < 0 || newX > 11 ||
              board[newY][newX] != ' '))
        {
            pieceList.at(i).y += 1;
        }
    }
}
void Block::_translate(bool positive, bool horizontal) {
    int j = (positive) ? 1 : -1;
    for (int i = 0; i < pieceList.size(); i++)
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
    for (int i = 0; i < pieceList.size(); i++)
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
    for (int i = 0; i < pieceList.size(); i++)
    {
        temp.clear();
        temp.push_back(-1 * pieceList.at(i).y);
        temp.push_back((pieceList.at(i).x));
        rotatedPos.push_back(temp);
    }

    for (int i = 0; i < rotatedPos.size(); i++)
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
    for (int i = 0; i < rotatedPos.size(); i++)
    {
        pieceList.at(i).x = rotatedPos.at(i).at(0) + translateX;
        pieceList.at(i).y = rotatedPos.at(i).at(1) + translateY;
    }
}

void Block::_transform(Direction dir)
{    
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
    int newX, newY;

    // First we remove the block from this copy of the board

    for (int i = 0; i < pieceList.size(); i++)
    {
        newX = pieceList.at(i).x;
        newY = pieceList.at(i).y;
        if (newY < 0 || newY > 17 ||
            newX < 0 || newX >= 11 ||
            board[newY][newX] != ' ')
        {
            return false;
        }
    }
    return true;
}

bool Block::translate(Direction dir, char board[18][11])
{    
    bool flag;

    _transform(dir);
    flag = _inBounds(board);
    
    if (!flag) {
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
        _transform(dir);
    }
    return flag;
}

/*
bool Block::translate(Direction dir, char board[18][11])
{
    //Placeholder variables to store the location of the moved object
    int newX = -1;
    int newY = -1;
    
    // First we remove the block from this copy of the board

    int currentX = 12;
    int currentY = -1;
    int newXPos = 12;
    int newYPos = -1;
    int translateX = 12;
    int translateY = -1;
    vector<vector<int>> rotatedPos;
    vector<int> temp;
    switch (dir)
    {
        case Direction::left:
            //we check if move is valid for all sub pieces in the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                newX = pieceList.at(i).x - 1;
                newY = pieceList.at(i).y;
                if(newY < 0 || newY > 17  ||
                newX < 0  || newX >= 11  ||
                board[newY][newX] != ' ')
                {

                    return false;
                }
            }
            //If move is valid, we actually move the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                pieceList.at(i).x -= 1;
            }
            rotateAroundPivot[0] -= 1;
            break;

        case Direction::right:

            for (int i = 0; i < pieceList.size(); i++)
            {
                newX = pieceList.at(i).x + 1;
                newY = pieceList.at(i).y;
                if (newY < 0 || newY > 17 ||
                    newX < 0 || newX >= 11 ||
                    board[newY][newX] != ' ')
                {
                    return false;
                }
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                pieceList.at(i).x += 1;
            }
            rotateAroundPivot[0] += 1;
            break;
        case Direction::down:
            for (int i = 0; i < pieceList.size(); i++)
            {
                newX = pieceList.at(i).x;
                newY = pieceList.at(i).y + 1;
                if (newY < 0 || newY > 17 ||
                    newX < 0 || newX >= 11 ||
                    board[newY][newX] != ' ')
                {
                    return false;
                }
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                pieceList.at(i).y += 1;
            }
            rotateAroundPivot[1] += 1;

            break;

        case Direction::counterclockwise:

            cout << "comng here" << endl;
            for (int i = 0; i < pieceList.size(); i++)
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
            for (int i = 0; i < pieceList.size(); i++)
            {
                temp.clear();
                temp.push_back(pieceList.at(i).y);
                temp.push_back((-1 * pieceList.at(i).x));
                rotatedPos.push_back(temp);
            }

            for (int i = 0; i < rotatedPos.size(); i++)
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
            cout << "current xy:" << currentX << "," << currentY << endl;
            cout << "new xy:" << newXPos << "," << newYPos << endl;
            for (int i = 0; i < rotatedPos.size(); i++)
            {
                newX = rotatedPos.at(i).at(0) + translateX;
                newY = rotatedPos.at(i).at(1) + translateY;
                if (newY < 0 || newY > 17 ||
                    newX < 0 || newX >= 11 ||
                    board[newY][newX] != ' ')
                {
                    return false;
                }
            }
            for (int i = 0; i < rotatedPos.size(); i++)
            {
                pieceList.at(i).x = rotatedPos.at(i).at(0) + translateX;
                pieceList.at(i).y = rotatedPos.at(i).at(1) + translateY;
                cout << "New position" << pieceList.at(i).x << "," << pieceList.at(i).y << endl;
            }

            break;

        case Direction::clockwise:
            cout << "comng here" << endl;
            for (int i = 0; i < pieceList.size(); i++)
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
            for (int i = 0; i < pieceList.size(); i++)
            {
                temp.clear();
                temp.push_back(-1 * pieceList.at(i).y);
                temp.push_back((pieceList.at(i).x));
                rotatedPos.push_back(temp);
            }

            for (int i = 0; i < rotatedPos.size(); i++)
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
            cout << "current xy:" << currentX << "," << currentY << endl;
            cout << "new xy:" << newXPos << "," << newYPos << endl;
            for (int i = 0; i < rotatedPos.size(); i++)
            {
                newX = rotatedPos.at(i).at(0) + translateX;
                newY = rotatedPos.at(i).at(1) + translateY;
                if (newY < 0 || newY > 17 ||
                    newX < 0 || newX >= 11 ||
                    board[newY][newX] != ' ')
                {
                    return false;
                }
            }
            for (int i = 0; i < rotatedPos.size(); i++)
            {
                pieceList.at(i).x = rotatedPos.at(i).at(0) + translateX;
                pieceList.at(i).y = rotatedPos.at(i).at(1) + translateY;
                cout << "New position" << pieceList.at(i).x << "," << pieceList.at(i).y << endl;
            }

            break;
        default:
            break;
        
    }
    return true;
}
*/