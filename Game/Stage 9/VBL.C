#include "VBL.H"

int main_game_timer = 0;
int render_request = 0;
bool game_on = true;

void do_vbl_isr()
{
    if(game_on == true) {
        main_game_timer++;
        if(main_game_timer == 1){
            process_synchronous_events(&model, &endGame);
            render_request = 1;
            main_game_timer = 0;
        }
    }
}
