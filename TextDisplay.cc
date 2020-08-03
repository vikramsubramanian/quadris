#include "TextDisplay.h"

using namespace std;

//--------------------------------------------------------------------------------------------
// Constructor
TextDisplay::TextDisplay(std::ostream &out, gameBoard *b): subject_{b}, out{out}{}

//--------------------------------------------------------------------------------------------
// Destructor
TextDisplay::~TextDisplay()
{
    subject_->detach(this);
}

//--------------------------------------------------------------------------------------------
// Update
// pulls current data from Library (subject) to output messages about changes to listener
void TextDisplay::notify_()
{
    DisplayStruct* display = subject_->getState_();

    // print header info
    out << "    Level:     " << display->level_ << endl;
    out << "    Score:     " << display->score_ << endl;
    out << "    Hi Score:  " << display->hiScore_ << endl;
    out << "    ___________ " << endl;

    // print board
    for (int i = 0; i < 18; i++)
    {
        if (i+1 < 10)
        {
            out << i+1 << "   ";
        }
        else
        {
            out << i+1<< "  ";
        }
        for (int j = 0; j < 11; j++)
        {
            //We use underscores for testing purposes. TODO: Final code should have " "
            out << display->board_[i][j];
        }
        out << endl;
    }
    out << "    ___________ " << endl;

    // print next block
    out << "    Next:" << endl;
    string nextBlock = subject_->getNextBlock_();
    for (int i = 0; i < 2; i++)
    {
        out << "    ";
        for(int j = 0; j < 4; j++)
            out << nextBlock[i*4+j];
        out << endl;
    }

}