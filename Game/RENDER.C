#include "RENDER.H"

/***********************************************************************
* Name: render
*
* Purpose:
*     Renders the game model's state using double buffering for smooth 
*     graphics rendering.
*
* Details:
*     - Clears the screen before rendering new positions.
*     - Updates the chicken's position and clears the previous bitmap 
*       to avoid visual artifacts.
*     - Checks for collisions between the chicken and coins; clears 
*       collected coins from the screen buffer.
*     - Renders all game elements (chicken, coins, monster, score, and 
*       ground).
*     - Respawns coins when collected.
*
* Parameters:
*     - model: Pointer to the game model structure containing game 
*              state information (player, coins, monsters, etc.).
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render(Model *model, UINT32 *base) {
    int i;
    clear_screen((UINT8 *)base);
    
    if (model->chicken.prev_x != model->chicken.x || model->chicken.prev_y != model->chicken.y) {
        clear_bitmap_32(base, model->chicken.prev_x, model->chicken.prev_y, clear_bitmap, CHICKEN_HEIGHT);
        model->chicken.prev_x = model->chicken.x;
        model->chicken.prev_y = model->chicken.y;
    }
    render_animal(&(model->chicken), base);

    for (i = 0; i < MAX_COINS; i++){
        if (check_collision_coin(&model->chicken, model->coins, i))
        {
            clear_bitmap_32(base, model->coins[i].x, model->coins[i].y, clear_bitmap, CHICKEN_HEIGHT);
        }
        else if (model->coins[i].active){
            render_coin((model->coins), (UINT16 *)base);
        }
    }
    respawn_render(model,base);

    render_monster(&model->monster, base);

    render_score(&(model->score), base);
    render_ground(&(model->ground), (UINT8 *)base);
}


/***********************************************************************
* Name: render_score
*
* Purpose: Renders the game score onto the screen buffer.
*
* Details: Renders the score onto the screen buffer using bitmap
*          plotting. Clears previous digits before rendering new ones.
*
* Parameters:
*     - score: Pointer to the game score structure.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_score(Score *score, UINT32 *base)
{
    int temp = score->total;
    int digitPosition = 0;
    int digits[10];  
    int i;

    if (temp == 0) {
        clear_bitmap_8((UINT16*)base, digitPosition << 4, 8, char_delete, FONT_HEIGHT);
        plot_bitmap_8((UINT16*)base, digitPosition << 4, 8, GLYPH_START('0'), FONT_HEIGHT);
        return;
    }

    while (temp > 0) {
        digits[digitPosition++] = temp % 10; 
        temp /= 10;  
    }

    for (i = digitPosition - 1; i >= 0; i--) {
        clear_bitmap_8((UINT16*)base, (digitPosition - 1 - i) << 4, 8, char_delete, FONT_HEIGHT);
        plot_bitmap_8((UINT16*)base, (digitPosition - 1 - i) << 4, 8, GLYPH_START(digits[i] + '0'), FONT_HEIGHT);
    }
}

/***********************************************************************
* Name: render_animal
*
* Purpose: Renders the animal onto the screen buffer.
*
* Details: Renders the animal onto the screen buffer based on its
*          position.
* Parameters:
*     - animal: Pointer to the animal object.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/

void render_animal(Animal *chicken, UINT32 *base)
{
    plot_bitmap_32(base, chicken->x, chicken->y, chicken_bitmap, CHICKEN_HEIGHT);
}

/***********************************************************************
* Name: render_monster
*
* Purpose: Renders the monster onto the screen buffer.
*
* Details: Renders the monster onto the screen buffer based on its
*          position using bitmap plotting.
*
* Parameters:
*     - monster: Pointer to the monster object.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_monster(Monster *monster, UINT32 *base)
{
        plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, MONSTER_HEIGHT);
}

/***********************************************************************
* Name: render_coin
*
* Purpose: Renders the score onto the screen buffer.
*
* Details: Renders the coin onto the screen buffer based on its
*          position using bitmap plotting.
*
* Parameters:
*     - coin: Pointer to the coin object.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_coin(Coin *coin, UINT16 *base){
    int i;
    for (i = 0; i < MAX_COINS; i++) {
        if (coin[i].active) {  
            plot_bitmap_16(base, coin[i].x, coin[i].y, coin_bitmap, COIN_HEIGHT);
        }
    }
}

/***********************************************************************
* Name: render_ground
*
* Purpose:
*     Renders the ground onto the screen buffer.
*
* Details:
*     Draws a horizontal line representing the ground using the y 
*     position provided in the ground structure.
*
* Parameters:
*     - ground: Pointer to the ground object containing position data.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_ground(Ground *ground, UINT8 *base) {
    plot_horizontal_line(base, ground->y);  
}

/***********************************************************************
* Name: respawn_render
*
* Purpose:
*     Handles the respawn and rendering of coins after collection.
*
* Details:
*     - Checks if any coins have been collected.
*     - If collected, initializes new coins and renders them.
*     - Ensures the updated state is reflected in the screen buffer.
*
* Parameters:
*     - model: Pointer to the game model structure containing game 
*              state information.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void respawn_render(Model *model, UINT32 *base)
{
    bool collected;
    collected = respawn_event(model);
    if (collected) {
        initialize_coins(model->coins, &(model->monster)); 
        render_coin((model->coins), (UINT16 *)base);
        collected = false;   
    } 
    else{
        render_coin((model->coins), (UINT16 *)base);
    }
}

/***********************************************************************
* Name: render_main_menu
*
* Purpose:
*     Displays the main menu screen.
*
* Details:
*     Renders the main menu bitmap onto the entire screen buffer.
*
* Parameters:
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_main_menu(UINT32 *base)
{
	plot_bitmap_screen(base, main_menu_bitmap);
}