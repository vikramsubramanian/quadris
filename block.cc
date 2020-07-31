#include "block.h"
#include "iostream"
#include <vector>
using namespace std;

Block::Block(){
    rotateAroundPivot[0] = 1;
    rotateAroundPivot[1] = 4;
}



bool Block::translate(Direction dir, char board[18][11])
{
    //Placeholder variables to store the location of the moved object
    int newX = -1;
    int newY = -1;
    
    // First we remove the block from this copy of the board

    for (int i = 0; i < 4; i++)
    {
        board[pieceList.at(i).y][pieceList.at(i).x] = '_';
    }


    switch (dir)
    {
        case Direction::left:
            cout << "Translate called in the left direction" << endl;
            //we check if move is valid for all sub pieces in the object
            for (int i = 0; i < 4; i++)
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
            for(int i =0 ; i<4; i++){
                pieceList.at(i).x -= 1;
            }
            rotateAroundPivot[0] -= 1;
            break;

        case Direction::right:
            cout << "Translate called in the right direction" << endl;

            for (int i = 0; i < 4; i++)
            {
                newX = pieceList.at(i).x + 1;
                newY = pieceList.at(i).y;
                if (newY < 2 || newY > 17 ||
                    newX < 0 || newX > 11 ||
                    board[newY][newX] != '_')
                {
                    return false;
                }
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < 4; i++)
            {
                pieceList.at(i).x += 1;
            }
            rotateAroundPivot[0] += 1;
            break;
        case Direction::down:
            cout << "Translate called in the downwards direction" << endl;
            for (int i = 0; i < 4; i++)
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
            for (int i = 0; i < 4; i++)
            {
                pieceList.at(i).y += 1;
            }
            rotateAroundPivot[1] += 1;

            break;

        case Direction::clockwise:
            cout << "Translate called in the clkwise direction" << endl;
            for (int i = 0; i < 4; i++)
            {   
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b)
                //Produces (y+a-b, a+b-x)
                newX = pieceList.at(i).y + rotateAroundPivot[0] - rotateAroundPivot[1];
                newY = (-1 * pieceList.at(i).x) + rotateAroundPivot[0] + rotateAroundPivot[1];
                if (newY <= 2 || newY > 17 ||
                    newX < 0 || newX > 11 ||
                    board[newY][newX] != '_')
                {
                    return false;
                }
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < 4; i++)
            {
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b) 
                //Produces (y+a-b, a+b-x)
                newX = pieceList.at(i).y + rotateAroundPivot[0] - rotateAroundPivot[1];
                newY = (-1 * pieceList.at(i).x) + rotateAroundPivot[0] + rotateAroundPivot[1];
                pieceList.at(i).y = newY;
                pieceList.at(i).x = newX;
            }
            break;

        case Direction::counterclockwise:
            cout << "Translate called in the counterclkwise direction" << endl;
            for (int i = 0; i < 4; i++)
            {
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b)
                //Produces (-y+a+b, -a+b+x)
                newX = (-1 * pieceList.at(i).y) + rotateAroundPivot[0] + rotateAroundPivot[1];
                newY = (pieceList.at(i).x) - rotateAroundPivot[0] + rotateAroundPivot[1];
                if (newY <= 2 || newY > 17 ||
                    newX < 0 || newX > 11 ||
                    board[newY][newX] != '_')
                {
                    return false;
                }
            }

            //If move is valid, we actually move the object
            for (int i = 0; i < 4; i++)
            {
                //Matric multiplcation says rotating a coordinate (x,y) 90deg clockwise around a pivot (a,b)
                //Produces (y+a-b, a+b-x)
                newX = (-1 * pieceList.at(i).y) + rotateAroundPivot[0] + rotateAroundPivot[1];
                newY = (pieceList.at(i).x) - rotateAroundPivot[0] + rotateAroundPivot[1];
                pieceList.at(i).y = newY;
                pieceList.at(i).x = newX;
            }
            break;

        default:
            break;
        
    }
    return true;
}