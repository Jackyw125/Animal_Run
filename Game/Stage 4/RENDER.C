#include "RENDER.H"

void render(Model *model, UINT32 *base)
{

    render_animal(&(model->chicken), base);
    render_monster(model->monster, base);
    render_coin(model->coins, (UINT16 *)base);
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
    UINT8 i;
    int temp = score->total;
    int digitPosition = 0;

    if (temp == 0) {
        clear_bitmap_8((UINT16*)base, digitPosition << 4, 8, char_delete, FONT_HEIGHT);
        plot_bitmap_8((UINT16*)base, digitPosition << 4, 8, GLYPH_START('0'), FONT_HEIGHT);
        return;
    }

    while (temp > 0)
    {
        clear_bitmap_8((UINT16*)base, digitPosition << 4, 8, char_delete, FONT_HEIGHT);
        plot_bitmap_8((UINT16*)base, digitPosition << 4, 8, GLYPH_START(temp % 10 + '0'), FONT_HEIGHT);
        temp /= 10;
        digitPosition++;
    }
}


/***********************************************************************
* Name: render_animal
*
* Purpose: Renders the animal onto the screen buffer.
*
* Details: Renders the animal onto the screen buffer based on its
*          position and facing direction using bitmap plotting.
*
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
    int i;
    for (i = 0; i < MAX_MONSTER; i++) {
        if (!monster[i].off_screen) {  
            plot_bitmap_32(base, monster[i].x, monster[i].y, monster_bitmap, MONSTER_HEIGHT);
        }
    }
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
void render_coin(Coin *coin, UINT16 *base)
{
    int i;
    for (i = 0; i < MAX_COINS; i++) {
        if (coin[i].active) {  
            plot_bitmap_16(base, coin[i].x, coin[i].y, coin_bitmap, COIN_HEIGHT);
        }
    }}

void render_ground(Ground *ground, UINT8 *base) {
    plot_horizontal_line(base, ground->y);  
}