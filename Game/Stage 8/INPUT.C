#include "INPUT.H"

/***********************************************************************
* Name: input
*
* Purpose: Handles user input for the game.
*
* Details: Checks if keyboard input is available and reads the key.
*          If the pressed key is ' ' or 'q', it updates the
*          pressedKey variable accordingly.
*
* Parameters:
*     - model: Pointer to the game model.
*     - pressedKey: Pointer to the variable storing the pressed key.
***********************************************************************/
void input(Model *model, char *pressedKey)
{
    char key;
    if (Cconis()) /* Check if keyboard input is available */
    { 
        key = (char)Cnecin(); /* Read keyboard input */
        if (key == ' ' || key == 'q' || key == 'w' || key == 'W') {
            *pressedKey = key;
        }
    } 
    else {
        *pressedKey = 0; /* Reset pressedKey if no key is pressed */
    }
}
