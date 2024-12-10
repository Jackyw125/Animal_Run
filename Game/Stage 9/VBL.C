#include "VBL.H"

int main_game_timer = 0;
int render_request = 0;
bool game_on = true;
UINT32 music_time = 0;

/***********************************************************************
* Name: do_vbl_isr
*
* Purpose:
*     Handles the vertical blanking interrupt service routine (VBL ISR),
*     managing time-based events and rendering updates during the game.
*
* Details:
*     - Checks if the game is currently active (game_on == true).
*     - Increments the main game timer to track time progression.
*     - Processes synchronous game events (e.g., collisions, score updates)
*       at a fixed interval when the main game timer equals 1.
*     - Increments the music_time variable to synchronize background music
*       with game progression.
*     - Sets the render_request flag to indicate that a new frame should
*       be rendered.
*     - Resets the main game timer to zero after processing events to 
*       ensure consistent timing intervals.
*
* Parameters:
*     None.
***********************************************************************/
void do_vbl_isr()
{
    if(game_on == true) {
        main_game_timer++;
        if(main_game_timer == 1){
            process_synchronous_events(&model, &endGame);
            music_time++;
            render_request = 1;
            main_game_timer = 0;
        }
    }
}
