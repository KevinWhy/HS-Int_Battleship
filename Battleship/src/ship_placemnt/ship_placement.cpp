//
//  ship_placement.cpp
//  
//
//  Created by Ritesh Sood on 11/19/17.
//

#include <stdio.h>
#include "Board.h"

void shipPlacement(int ship, Board a_board)              // ship is the size of the ship we wanna place
{
    //lc.clearDisplay(0);                                                 // allPos is a pointer to our array which holds all of this players ship positions.
    bool check = false;
    int a_size = a_board.numberOfPos;
    
      char key = ' ';
      int col = 0;
      int row = 0;
    
    while(check == false)             // this loop gets the head position of the ship from the user
    {
      col = 0;
      row = 0;
      Position pos = playerIn->getNextPos();
      
      
      col = pos.x*10+(key-'0');
      col = col - 1;                    // subtract by 1 because the user enters between '1..8', the program accepts '0..7'
      //Serial.println(col);
      
      
      row = pos.y*10+(key-'0');
      row = row - 1;
      //Serial.println(row);
      
      int count = 0;
      //Serial.println(col+1);
      //Serial.println(row+1);
      if(a_size > 0)                                                    // if the position array is not empty then make sure the
      {                                                                 // user entered position is not already taken
        for(int i = 0; i < a_size; ++i)
        {
          if(row != allPos[i].y || col != allPos[i].x)
            ++count;
        }
      }
 
      if(count == a_size )
        check = true;
    }

    
    
    int pos1 = col - (ship - 1);
    int pos2 = col + (ship - 1);                  // these are the four optional end positions for the ship
    int pos3 = row - (ship - 1);
    int pos4 = row + (ship - 1);
   
    //ask the user for row and col
    
    lc.setLed(0, col, row, true);
    lc.setLed(0, pos1, row, true);                                    //I light all of the positions up and then check to see which ones are invalid
    lc.setLed(0, pos2, row, true);
    lc.setLed(0, col, pos3, true);
    lc.setLed(0, col, pos4, true);

    if(a_size > 0)                                                  //Here i step through the allPos array and compare
    {
      Serial.println(a_size);                                       // all of the positions that could be taken up by any of those orientations
      for(int b = 0; b < ship; ++b)                                 // if any position gets taken that consequent end position is turned off.
      {
        for(int j = 0; j < a_size; ++j)
        {
          if(allPos[j].x == (col - b) && allPos[j].y == row)
            lc.setLed(0, pos1, row, false);

          if(allPos[j].x == (col + b) && allPos[j].y == row)
            lc.setLed(0, pos2, row, false);

          if(allPos[j].x == col && allPos[j].y == (row - b))
            lc.setLed(0, col, pos3, false);

          if(allPos[j].x == col && allPos[j].y == (row + b))
            lc.setLed(0, col, pos4, false);

          //Serial.println(allPos[b].col);
          //Serial.println(allPos[b].row);
          //Serial.println("________");
        }
      }
    }
    

      //tuan light up function


    int e_col = 0;
    int e_row = 0;
    bool a_check = true;
    while(!playerIn->hasInput())
    {
        playerIn->loop();
    }                                        //Here we read the second position from the user
    
   if(playerIn->hasInput())
   {
    do{
        e_col = 0;
        e_row = 0;

        Position pos_2 = playerIn->getNextPos();
        

        e_col = e_col*10+(pos_2.x -'0');
        if(e_col != 0)
        {
          e_col = e_col - 1;
        }
        

        e_row = e_row*10+(pos_2.y-'0');
        if(e_row != 0)
        {
          e_row = e_row - 1;
        }

          int count = 0;
        if(a_size > 0)
        {
          if(e_col == col)
          {
              if(e_row > row)
              {
                for(int b = 0; b < ship; ++k)
                {
                    for(int k = 0; k < a_size; ++b)
                    {
                    if(allPos[b].x == e_col && allPos[b].y == e_row)    //check to see if the input is valid
                        count++;
                    else if(allPos[b].x == e_col && allPos[b].y == row + k)
                        count++;
                    }
                }
              }
              else if(e_row < row)
              {
                  for(int b = 0; b < ship; ++k)
                {
                    for(int k = 0; k < a_size; ++b)
                    {
                    if(allPos[b].x == e_col && allPos[b].y == e_row)    //check to see if the input is valid
                        count++;
                    else if(allPos[b].x == e_col && allPos[b].y == row - k)
                        count++;
                    }
                }
              }
              
          }
          else if(e_row == row)
          {
            if(e_col > col)
              {
                for(int b = 0; b < ship; ++k)
                {
                    for(int k = 0; k < a_size; ++b)
                    {
                    if(allPos[b].x == e_col && allPos[b].y == e_row)    //check to see if the input is valid
                        count++;
                    else if(allPos[b].x == e_col + k && allPos[b].y ==)
                        count++;
                    }
                }
              }
              else if(e_col < col)
              {
                  for(int b = 0; b < ship; ++k)
                {
                    for(int k = 0; k < a_size; ++b)
                    {
                    if(allPos[b].x == e_col && allPos[b].y == e_row)    //check to see if the input is valid
                        count++;
                    else if(allPos[b].x == e_col - k && allPos[b].y == row)
                        count++;
                    }
                }
              }
          }
        }
        else
            a_check = false;
        
        if(count != 0)
          a_check = false;
        
      }while(((e_col != pos1 || e_row != row) && (e_col != pos2 || e_row != row) && (e_row != pos3 || e_col != col) && (e_row != pos4 || e_col != col)) && a_check != true);
    }
    //lc.clearDisplay(0);
    Position a_ship[ship];
    if(e_row == row)                                                // if the row position is the same for the head and end position
    {                                                               // then only the col changes and we only need to step through that
      if(e_col == pos1)
      {
          lc.setLed(0, pos2, row, false);

          lc.setLed(0, col, pos3, false);

          lc.setLed(0, col, pos4, false);
          
        for(int i = 0; i < ship; ++i)
        {
          a_ship[i].col = (col-i);
          a_ship[i].row = row;
          lc.setLed(0, a_ship[i].col, a_ship[i].row, true);               //this for loop is where the full ship is turned on
          allPos[a_size].row = row;                                       //turns on one pos at a time and stores the pos into the allPos array
          allPos[a_size].col = (col-i);
          ++a_size;                                                       //the same is done from here on down for rest of the position options that were available
          ++posSize;
        }
      }
      else if(e_col == pos2)
      {
          lc.setLed(0, pos1, row, false);

          lc.setLed(0, col, pos3, false);

          lc.setLed(0, col, pos4, false);

        for(int i = 0; i < ship; ++i)
        {
          a_ship[i].col = (col+i);
          a_ship[i].row = row;
          lc.setLed(0, a_ship[i].col, a_ship[i].row, true);
          allPos[a_size].row = row;
          allPos[a_size].col = (col+i);
          ++a_size;
          ++posSize;
        }
      }
    }
    else if(e_col == col)
    {
          lc.setLed(0, pos2, row, false);
      
          lc.setLed(0, pos1, row, false);

          lc.setLed(0, col, pos4, false);
     
        for(int i = 0; i < ship; ++i)
        {
          a_ship[i].row = (row-i);
          a_ship[i].col = col;
          lc.setLed(0, a_ship[i].col, a_ship[i].row, true);
          allPos[a_size].row = (row - i);
          allPos[a_size].col = col;
          ++a_size;
          ++posSize;
        }
      }
      else if(e_row == pos4)
      {
        lc.setLed(0, pos2, row, false);
        
        lc.setLed(0, pos1, row, false);
        
        lc.setLed(0, col, pos3, false);

        for(int i = 0; i < ship; ++i)
        {
          a_ship[i].row = (row+i);
          a_ship[i].col = col;
          lc.setLed(0, a_ship[i].col, a_ship[i].row, true);
          allPos[a_size].row = (row + i);
          allPos[a_size].col = col;
          ++a_size;
          ++posSize;
        }
      }
    }
    //delay(10000);
}
