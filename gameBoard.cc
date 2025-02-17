#include "gameBoard.h"
#include "BlockFactory.h"
#include "block.h"
#include "displayStruct.h"
#include "piece.h"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// Constructor
gameBoard::gameBoard() {
  isGameOver_ = false;
  curBlock_ = nullptr;
  nextBlock_ = nullptr;
  displayStruct_ = new DisplayStruct;
  displayStruct_->score_ = 0;
  displayStruct_->hiScore_ = 0;
  displayStruct_->level_ = 0;

  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 11; j++) {
      displayStruct_->board_[i][j] = ' ';
    }
  }
}

//----------------------------------------------------------------------
// Destructor
gameBoard::~gameBoard() {
  delete nextBlock_;
  for (auto p : blocks_) {
    delete p;
  }
  blocks_.clear();
  delete displayStruct_;
}

//----------------------------------------------------------------------
// FUNCTIONS

bool gameBoard::gameOver_() { return isGameOver_; }

//----------------------------------------------------------------------
// Command-related Functions

// generates a block on the board
void gameBoard::newBlock_(char piece) {
  int xCor = -1;
  int yCor = -1;
  if (!isGameOver_) {
    // We can have a new block only if the game is still playable
    Block *genblock = BlockFactory::createBlock(piece);
    genblock->level_ = displayStruct_->level_;
    for (int i = 0; (unsigned)i < genblock->pieceList.size(); i++) {
      // Now we check if we have space to get the new block in
      xCor = genblock->pieceList.at(i).x;
      yCor = genblock->pieceList.at(i).y;
      if (displayStruct_->board_[yCor][xCor] != ' ') {
        // This means we have no space for the new block
        // this means the game is over
        delete genblock;
        isGameOver_ = true;
        return;
      }
    }

    // setting current and next blocks
    curBlock_ = nextBlock_;
    nextBlock_ = genblock;
    if (curBlock_ != nullptr) {
      blocks_.push_back(curBlock_);
    }
  }

  // once there are blocks on the board, update display
  if (blocks_.size() > 0) {
    generateBoardFromBlocks_();
    notifyObservers();
  }
}

// takes blocks vector and generates board from blocks played
void gameBoard::generateBoardFromBlocks_() {
  // init board with empty spaces
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 11; j++) {
      displayStruct_->board_[i][j] = ' ';
    }
  }

  // display blocks on board based on position of
  // individual pieces
  int xCor = -1;
  int yCor = -1;
  for (size_t i = 0; i < blocks_.size(); i++) {
    for (size_t j = 0; j < blocks_.at(i)->pieceList.size(); j++) {
      xCor = blocks_.at(i)->pieceList.at(j).x;
      yCor = blocks_.at(i)->pieceList.at(j).y;
      displayStruct_->board_[yCor][xCor] = blocks_.at(i)->pieceList.at(j).type;
    }
  }
}

// takes in directions and transforms block accordingly
void gameBoard::transformBlock_(vector<Direction> dirs) {
  for (int i = 0; (unsigned)i < dirs.size(); i++) {
    generateBoardFromBlocks_();
    curBlock_->translate(dirs.at(i), displayStruct_->board_);
  }

  generateBoardFromBlocks_();
  notifyObservers();
}

// drops current block onto the board
void gameBoard::drop_() {

  generateBoardFromBlocks_();
  bool status = curBlock_->translate(Direction::down, displayStruct_->board_);
  while (status == true) {
    generateBoardFromBlocks_();
    status = curBlock_->translate(Direction::down, displayStruct_->board_);
  }
  curBlock_ = nullptr;

  updateScore_();

  generateBoardFromBlocks_();
  notifyObservers();
}

// for testing purposes
// replaces current block with block of type given
void gameBoard::replace_(char piece) {
  blocks_.erase(std::remove(blocks_.begin(), blocks_.end(), curBlock_),
                blocks_.end());
  generateBoardFromBlocks_();

  // Now we generate a new block
  int xCor = -1;
  int yCor = -1;
  if (!isGameOver_) {
    // We can have a new block only if the game is still playable
    Block *genblock = BlockFactory::createBlock(piece);
    genblock->level_ = displayStruct_->level_;
    for (int i = 0; (unsigned)i < genblock->pieceList.size(); i++) {
      // Now we check if we have space to get the new block in
      xCor = genblock->pieceList.at(i).x;
      yCor = genblock->pieceList.at(i).y;
      if (displayStruct_->board_[yCor][xCor] != ' ') {
        // This means we have no space for new block
        // board is full and the game is over
        delete genblock;
        isGameOver_ = true;
        return;
      }
    }
    curBlock_ = genblock;
    blocks_.push_back(curBlock_);

    generateBoardFromBlocks_();
    notifyObservers();
  }
}

void gameBoard::hint_(bool playTurn) {
  // Note: If playTurn == True, we have the computer
  // play the hint piece. This is an extra feature.
  Block *hintBlock = nullptr;
  char piece = curBlock_->pieceList.at(0).type;
  if (playTurn) {
    blocks_.pop_back();
  }
  if (!isGameOver_ && curBlock_ != nullptr) {
    Block *genblock = nullptr;
    int lowest = -1;
    bool status = true;
    int possibleLowest = -1;

    // We create all possible positions- both in terms of
    // orientation and position and check to find the one
    // lowest on the board
    // That is our hint position
    for (int i = 0; i < 11; i++) {
      for (int rotateCount = 0; rotateCount < 3; rotateCount++) {
        genblock = BlockFactory::createBlock(piece);
        blocks_.push_back(genblock);

        for (int coun = 0; coun < rotateCount; coun++) {
          removeCurrentBlockFromDisplayBoard_();
          genblock->translate(Direction::clockwise, displayStruct_->board_);
        }

        // We check all possible columns through this loop.
        for (int j = 0; j < i; j++) {
          removeCurrentBlockFromDisplayBoard_();
          genblock->translate(Direction::right, displayStruct_->board_);
        }

        // We check all 4 orientations through this loop.
        removeCurrentBlockFromDisplayBoard_();
        status = genblock->translate(Direction::down, displayStruct_->board_);

        // We go as far down as possible
        while (status == true) {
          removeCurrentBlockFromDisplayBoard_();
          status = genblock->translate(Direction::down, displayStruct_->board_);
        }

        possibleLowest = genblock->pieceList.at(0).y;

        // find the lowest piece in this block
        // Lower the piece, higher its index in our board(a 2D array).
        for (int pieceCount = 0;
             (unsigned)pieceCount < genblock->pieceList.size(); pieceCount++) {
          if (possibleLowest < genblock->pieceList.at(pieceCount).y) {
            possibleLowest = genblock->pieceList.at(pieceCount).y;
          }
        }
        // Lower the piece, higher its index in our board(a 2D array).
        // We check if the current iteration of the hint block is the lowest
        if (possibleLowest > lowest) {
          lowest = possibleLowest;
          hintBlock = genblock;
          genblock = nullptr;
        }
        delete genblock;
        blocks_.pop_back();
        genblock = nullptr;
      }
    }
  }

  if (!playTurn) {
    for (size_t jj = 0; jj < hintBlock->pieceList.size(); jj++) {
      // We replace the char that each piece is represented by in our block
      // In order to display the hint block with '?'s
      hintBlock->pieceList.at(jj).type = '?';
    }
  }
  // Push the block with the '?'s and update display
  blocks_.push_back(hintBlock);
  updateScore_();
  generateBoardFromBlocks_();
  notifyObservers();

  // Remove the block with the '?'s for next command
  if (!playTurn) {
    blocks_.pop_back();
    delete hintBlock;
  }

  updateScore_();
}

// generates and drops our special blocks
// for level 4: generates * block and drops it
// in the centre of the board
void gameBoard::constructiveForce_(char piece) {
  int xCor = -1;
  int yCor = -1;

  // Creating the block
  // We can have a new block only if the game is still playable
  Block *genblock = BlockFactory::createBlock(piece);
  genblock->level_ = displayStruct_->level_;
  // type = genblock->pieceList.at(0).type;
  genblock->transform(Direction::right);
  genblock->transform(Direction::right);
  genblock->transform(Direction::right);

  for (int i = 0; (unsigned)i < genblock->pieceList.size(); i++) {
    // Now we check if we have space to get the new block in
    xCor = genblock->pieceList.at(i).x;
    yCor = genblock->pieceList.at(i).y;
    if (displayStruct_->board_[yCor][xCor] != ' ') {
      // This means we have no space for the new block
      // this means the game is over
      delete genblock;
      isGameOver_ = true;
      return;
    }
  }

  blocks_.push_back(genblock);

  // Dropping the block
  generateBoardFromBlocks_();
  bool status = genblock->translate(Direction::down, displayStruct_->board_);
  while (status == true) {
    generateBoardFromBlocks_();
    status = genblock->translate(Direction::down, displayStruct_->board_);
  }
  genblock = nullptr;

  // check if newly dropped block clears a row
  updateScore_();

  generateBoardFromBlocks_();
  notifyObservers();
}

//----------------------------------------------------------------------
// ACCESSORS AND MUTATORS
int gameBoard::getScore_() { return displayStruct_->score_; }

int gameBoard::getHiScore_() { return displayStruct_->hiScore_; }

void gameBoard::setHiScore_(int hiScore_) {
  displayStruct_->hiScore_ = hiScore_;
}

void gameBoard::updateScore_() {
  bool isFullFlag = true;
  int numberOfLines = 0;
  for (int counter = 0; counter < 18; counter++) {
    generateBoardFromBlocks_();

    // if row has an empty space, it is not full
    for (int j = 0; j < 11; j++) {
      if (displayStruct_->board_[counter][j] == ' ') {
        isFullFlag = false;
      }
    }

    // if row is full, it needs to be cleared
    if (isFullFlag == true) {
      numberOfLines++;
      for (int j = 0; j < 11; j++) {
        for (size_t l = 0; l < blocks_.size(); l++) {
          Block *temp = blocks_.at(l);
          for (size_t ll = 0; ll < temp->pieceList.size(); ll++) {
            if (temp->pieceList.at(ll).x == j &&
                temp->pieceList.at(ll).y == counter && temp != curBlock_) {
              temp->pieceList.erase(temp->pieceList.begin() + ll);
            }
            if (blocks_.at(l)->pieceList.size() == 0) {
              displayStruct_->score_ += (1 + temp->level_) * (1 + temp->level_);
              blocks_.erase(blocks_.begin() + l);
              delete temp;
            }
          }
        }
      }

      // shift all rows above cleared row down by one
      for (size_t l = 0; l < blocks_.size(); l++) {
        if (blocks_.at(l) != curBlock_) {
          generateBoardFromBlocks_();
          blocks_.at(l)->shiftDown(displayStruct_->board_, counter);
        }
      }
    }
    isFullFlag = true;
  }

  // We update score only if rows have been deleted
  if (numberOfLines > 0) {
    int lineLevel = numberOfLines + displayStruct_->level_;
    displayStruct_->score_ += lineLevel * lineLevel;
  }
  if (displayStruct_->score_ > displayStruct_->hiScore_) {
    displayStruct_->hiScore_ = displayStruct_->score_;
  }
}

void gameBoard::setLevel_(int lvl) {
  if (nextBlock_ != nullptr) {
    nextBlock_->level_ = lvl;
  }
  displayStruct_->level_ = lvl;
}

//----------------------------------------------------------------------
// Accessors for Observer DP

// returns board and game information for display
DisplayStruct *gameBoard::getState_() { return displayStruct_; }

void gameBoard::removeCurrentBlockFromDisplayBoard_() {
  // We sometimes need our board with the current piece removed.
  // This method produces that
  // For instance, if the block was being rotated, one piece of the
  // block could take the position of another piece.
  // To know that it is a valid rotate, we need to remove all the
  // current pieces in curBlock and then compare.
  generateBoardFromBlocks_();
  int curX, curY;
  for (int i = 0; (unsigned)i < curBlock_->pieceList.size(); i++) {
    curX = curBlock_->pieceList.at(i).x;
    curY = curBlock_->pieceList.at(i).y;
    displayStruct_->board_[curY][curX] = ' ';
  }
}

// returns block to be displayed as next block
string gameBoard::getNextBlock_() {
  string nextBlockRepr;
  char type = nextBlock_->pieceList.at(0).type;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      nextBlockRepr[i * 4 + j] = ' ';
    }
  }
  for (int i = 0; (unsigned)i < nextBlock_->pieceList.size(); i++) {
    int index =
        (nextBlock_->pieceList.at(i).y - 3) * 4 + nextBlock_->pieceList.at(i).x;
    nextBlockRepr[index] = type;
  }
  return nextBlockRepr;
}