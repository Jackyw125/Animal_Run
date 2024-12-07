#include "RENDER.H"

/***********************************************************************
 * Name: render
 *
 * Purpose:
 *   Renders the game model's current state onto the screen buffer.
 *
 * Details:
 *   The function handles rendering all visible components of the game, 
 *   including the player's character, monsters, coins, score, and ground. 
 *   It also ensures proper handling of object movement and collision:
 *     - Clears previous positions of the player and coins after movement.
 *     - Renders updated positions for the player, monsters, and coins.
 *     - Deactivates coins and clears their bitmap from the screen if 
 *       collected by the player.
 *     - Continuously updates and renders the game score and ground.
 *
 * Parameters:
 *   - model: Pointer to the game model structure containing game state 
 *            information (player, coins, monsters, score, ground, etc.).
 *   - base: Pointer to the base address of the screen buffer.
 ***********************************************************************/
void render(Model *model, UINT32 *base)
{
    render_animal(&(model->chicken), base);

    render_monster(&model->monster, base);
    render_coin((model->coins), (UINT16 *)base);

    render_score(&(model->score), base); 
    render_ground(&(model->ground), (UINT8 *)base);
}

void double_buffer_render(Model *model, UINT32 *base) {
    int i;
    clear_screen((UINT8*) base);

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

void render_ground(Ground *ground, UINT8 *base) {
    plot_horizontal_line(base, ground->y);  
}

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