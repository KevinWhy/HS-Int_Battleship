//
//  ship_placement.cpp
//  
//
//  Created by Ritesh Sood on 11/19/17.
//

#include <stdio.h>
void shipPlacement(int ship, Board a_board)              // ship is the size of the ship we wanna place
{
    //lc.clearDisplay(0);                                                 // allPos is a pointer to our array which holds all of this players ship positions.
    bool check = false;
    int a_size = PosSize;
    
      char key = ' ';
      int col = 0;
      int row = 0;
    
    while(check == false)             // this loop gets the head position of the ship from the user
    {
      col = 0;
      row = 0;
      Position pos = playerIn->getNextPos();
      
      
      col = pos.col*10+(key-'0');
      col = col - 1;                    // subtract by 1 because the user enters between '1..8', the program accepts '0..7'
      //Serial.println(col);
      
      
      row = pos.row*10+(key-'0');
      row = row - 1;
      //Serial.println(row);
      
      int count = 0;
      //Serial.println(col+1);
      //Serial.println(row+1);
      if(a_size > 0)                                                    // if the position array is not empty then make sure the
      {                                                                 // user entered position is not already taken
        for(int i = 0; i < a_size; ++i)
        {
          if(row != allPos[i].row || col != allPos[i].col)
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
          if(allPos[j].col == (col - b) && allPos[j].row == row)
            lc.setLed(0, pos1, row, false);

          if(allPos[j].col == (col + b) && allPos[j].row == row)
            lc.setLed(0, pos2, row, false);

          if(allPos[j].col == col && allPos[j].row == (row - b))
            lc.setLed(0, col, pos3, false);

          if(allPos[j].col == col && allPos[j].row == (row + b))
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
    bool a_check = true;                                        //Here we read the second position from the user
    
    do{
        e_col = 0;
        e_row = 0;

        Position pos_2 = playerIn->getNextPos();
        

        e_col = e_col*10+(pos_2.col -'0');
        if(e_col != 0)
        {
          e_col = e_col - 1;
        }
        

        e_row = e_row*10+(pos_2.row-'0');
        if(e_row != 0)
        {
          e_row = e_row - 1;
        }

          int count = 0;
        if(a_size > 0)
        {
          for(int k = 0; k < ship; ++k)
          {
            for(int b = 0; b < a_size; ++b)
            {
              if(allPos[b].col == e_col && allPos[b].row == e_row)    //check to see if the input is valid
                count++;
              else if(allPos[b].col == e_col - k && allPos[b].row == e_row)
                count++;
              else if(allPos[b].col == e_col
              Serial.println("asdfasdf");                            //rather than just the end position
              Serial.println(count);
            }
          }
        }
        
        if(count != 0)
          a_check = false;
        
    }while(((e_col != pos1 || e_row != row) && (e_col != pos2 || e_row != row) && (e_row != pos3 || e_col != col) && (e_row != pos4 || e_col != col)) && a_check != true);
    
    //lc.clearDisplay(0);
    Position a_ship[ship];
    if(e_row == row)                                                // if the row position is the same for the head and end position
    {                                                               // then only the col changes and we only need to step through that
      if(e_col == pos1)
      {
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        for(int b = 0; b < a_size; ++b)
        {
          if(allPos[b].col != pos2 || allPos[b].row != row)               // this loop and the following if statements are to
            ++index1;                                                     // turn on any leds that were turned off two loops ago.
          if(allPos[b].col != col || allPos[b].row != pos3)               // any leds that have a pos in the allPos array but were turned off.
            ++index2;
          if(allPos[b].col != pos2 || allPos[b].row != pos4)
            ++index3;
        }

        if(index1 == a_size)
          lc.setLed(0, pos2, row, false);
        else
          lc.setLed(0, pos2, row, true);
          
        if(index2 == a_size)
          lc.setLed(0, col, pos3, false);
        else
          lc.setLed(0, col, pos3, true);
          
        if(index3 == a_size)
          lc.setLed(0, col, pos4, false);
        else
          lc.setLed(0, col, pos4, true);
          
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
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        for(int b = 0; b < a_size; ++b)
        {
          if(allPos[b].col != pos1 || allPos[b].row != row)
            ++index1;
          if(allPos[b].col != col || allPos[b].row != pos3)
            ++index2;
          if(allPos[b].col != pos2 || allPos[b].row != pos4)
            ++index3;
        }

        if(index1 == a_size)
          lc.setLed(0, pos1, row, false);
        else
          lc.setLed(0, pos1, row, true);
          
        if(index2 == a_size)
          lc.setLed(0, col, pos3, false);
        else
          lc.setLed(0, col, pos3, true);
          
        if(index3 == a_size)
          lc.setLed(0, col, pos4, false);
        else
          lc.setLed(0, col, pos4, true);
        
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
      if(e_row == pos3)
      {
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        for(int b = 0; b < a_size; ++b)
        {
          if(allPos[b].col != pos2 || allPos[b].row != row)
            ++index1;
          if(allPos[b].col != pos1 || allPos[b].row != row)
            ++index2;
          if(allPos[b].col != pos2 || allPos[b].row != pos4)
            ++index3;
        }

        if(index1 == a_size)
          lc.setLed(0, pos2, row, false);
        else
          lc.setLed(0, pos2, row, true);
          
        if(index2 == a_size)
          lc.setLed(0, pos1, row, false);
        else
          lc.setLed(0, pos1, row, true);
          
        if(index3 == a_size)
          lc.setLed(0, col, pos4, false);
        else
          lc.setLed(0, col, pos4, true);
          
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
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        for(int b = 0; b < a_size; ++b)
        {
          if(allPos[b].col != pos2 || allPos[b].row != row)
            ++index1;
          if(allPos[b].col != pos1 || allPos[b].row != row)
            ++index2;
          if(allPos[b].col != pos2 || allPos[b].row != pos3)
            ++index3;
        }

        if(index1 == a_size)
          lc.setLed(0, pos2, row, false);
        else
          lc.setLed(0, pos2, row, true);
          
        if(index2 == a_size)
          lc.setLed(0, pos1, row, false);
        else
          lc.setLed(0, pos1, row, true);
          
        if(index3 == a_size)
          lc.setLed(0, col, pos3, false);
        else
          lc.setLed(0, col, pos3, true);
        
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
