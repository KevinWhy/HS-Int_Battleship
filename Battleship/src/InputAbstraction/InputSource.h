/* Input Source
 *    By Kevin Yang
 * 
 * This abstraction seperates game logic from input.
 * Any input sources (keypads, replays) will extend
 *    from this class.
 * 
 ****************
 * Note: This does NOT do Inversion of Control.
 *    (aka: This does not read a config to tell
 *          game logic which devices to read from)
 * 
 * Reference:
 *  Abstract Class: https://msdn.microsoft.com/en-us/library/c8whxhf1.aspx
 *  Initializing Struct: https://stackoverflow.com/questions/11516657/c-structure-initialization#11516847
 */
#ifndef INPUT_SOURCE_H
#define INPUT_SOURCE_H

#include "../../Abstract.h" // For the Position struct

const Position INVALID_POS = {-1, -1};

class InputSource {
  private:
    Position changingPos; // Position that is changed by setX, setY
    Position nextPos; // Next position the program can read
    bool hasNextPos;
    void (*onChangeFunc)(Position currPos); // Function to call when input changes
    
  protected:
    // Should be called by child classes
    bool isPosValid(const int newXPos, const int newYPos); // Returns true if x, y is on the board
    void setX(const int newXPos); // Change the x position
    void setY(const int newYPos); // Change the y position
    void setPos(const int newXPos, const int newYPos); // Change both x & y position
    void finalizePos(); // Say that the position is ready to be read
    
    /* This is called whenever the input is changed.
     * ONLY CALL THIS IF setX, setY are NOT used!
     */
    void inputChanged(const Position currPos);
    
  public:
    InputSource();
    
    /* Child classes might require constant updating to poll for input.
     */
    virtual void loop() =0;
    
    /* Returns true if the InputSource has a nextPos ready.
     */
    virtual bool hasInput();
    /* Returns nextPos.
     * If there hasn't been a nextPos, returns INVALID_POS.
     */
    virtual Position getNextPos();
    
    /* Binds input changes to onChangeFunc.
     * So, while user is deciding what to send, onChangeFunc() is called.
     *     Use it to display the pending input to the player.
     */
    void onInputChange(void (*onChangeFunc)(Position currPos));
};

#endif

