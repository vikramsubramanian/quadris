#include "block.h"
#include "iostream"
#include <vector>
using namespace std;

Block::Block(){

}

void Block::shiftDown(char board[18][11]){
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
        if (!(newY <= 2 || newY > 17 ||
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


    switch (dir)
    {
        case Direction::left:
            //we check if move is valid for all sub pieces in the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                newX = pieceList.at(i).x - 1;
                newY = pieceList.at(i).y;
                if(newY <= 2 || newY > 17  ||
                newX < 0  || newX > 11  ||
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
                if (newY < 2 || newY > 17 ||
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
                if (newY <= 2 || newY > 17 ||
                    newX < 0 || newX > 11 ||
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
            for (int i = 0; i < pieceList.size(); i++)
            {   
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b)
                //Produces (y+a-b, a+b-x)
                newX = pieceList.at(i).y + rotateAroundPivot[0] - rotateAroundPivot[1];
                newY = (-1 * pieceList.at(i).x) + rotateAroundPivot[0] + rotateAroundPivot[1];
                cout << newX << "," << newY << endl;
                if (newY < 0 || newY > 17 ||
                    newX < 0 || newX > 11 ||
                    board[newY][newX] != '_')
                {
                    return false;
                }
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b) 
                //Produces (y+a-b, a+b-x)
                newX = pieceList.at(i).y + rotateAroundPivot[0] - rotateAroundPivot[1];
                newY = (-1 * pieceList.at(i).x) + rotateAroundPivot[0] + rotateAroundPivot[1];
                pieceList.at(i).y = newY;
                pieceList.at(i).x = newX;
            }
            cout << "PIVOT:" << rotateAroundPivot[0] << "," << rotateAroundPivot[1] << endl;
            break;

        case Direction::clockwise:

            vector<vector<int>> newPos;
            int lowestX =-1;
            int lowestY =-1;
            for (int i = 0; i < pieceList.size(); i++)
            {
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b)
                //Produces (-y+a+b, -a+b+x)
                newX = (-1 * pieceList.at(i).y) + rotateAroundPivot[0] + rotateAroundPivot[1];
                newY = (pieceList.at(i).x) - rotateAroundPivot[0] + rotateAroundPivot[1] ;
                vector<int> temp;
                temp.push_back(newX);
                temp.push_back(newY);
                newPos.push_back(temp);
                // cout << newX << "," << newY << endl;
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < pieceList.size(); i++)
            {
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b)
                //Produces (y+a-b, a+b-x)
                newX = (-1 * pieceList.at(i).y) + rotateAroundPivot[0] + rotateAroundPivot[1];
                newY = (pieceList.at(i).x) - rotateAroundPivot[0] + rotateAroundPivot[1];
                pieceList.at(i).y = newY;
                pieceList.at(i).x = newX;
            }
            cout << "PIVOT:" << rotateAroundPivot[0] << "," << rotateAroundPivot[1] << endl;
            break;

        default:
            break;
        
    }
    return true;
}