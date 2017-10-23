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
#include "Abstract.h" // For the Position struct

Position INVALID_POS = {-1, -1};

class InputSource {
  public:
    /* Returns true if the InputSource has a nextPos ready.
     */
    virtual bool hasInput()=0;
    /* Returns nextPos.
     * If there hasn't been a nextPos, returns INVALID_POS.
     */
    virtual Position getNextPos() =0;
};

#endif

