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
        board[pieceList.at(i).y][pieceList.at(i).x] = '_';
    }
    for (int i = 0; i < pieceList.size(); i++)
    {
        newX = pieceList.at(i).x;
        newY = pieceList.at(i).y + 1;
        //FIX THIS!
        if (!(newY < 0 || newY > clearedRow ||
              newX < 0 || newX > 11 ||
              board[newY][newX] != '_'))
        {
            pieceList.at(i).y += 1;
        }
    }
}

bool Block::translate(Direction dir, char board[18][11])
{
    //Placeholder variables to store the location of the moved object
    int newX = -1;
    int newY = -1;
    
    // First we remove the block from this copy of the board
    for (int i = 0; i < pieceList.size(); i++)
    {
        board[pieceList.at(i).y][pieceList.at(i).x] = '_';
    }

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
                board[newY][newX] != '_')
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
                    board[newY][newX] != '_')
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
                    board[newY][newX] != '_')
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
                    board[newY][newX] != '_')
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
                    board[newY][newX] != '_')
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