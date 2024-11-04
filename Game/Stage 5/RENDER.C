#include "RENDER.H"
/***********************************************************************
* Name: render
*
* Purpose: Renders the game objects onto the screen buffer.
*
* Details: Renders the coins, animal, and monster onto the screen
*          buffer based on the provided game model. Clears previous
*          positions of moving objects before rendering new positions.
*
* Parameters:
*     - model: Pointer to the game model containing object positions.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render(const Model *model, UINT32 *base)
{
    /*render_coin(&(model->coins), base);*/
    
        /*render_monster(&(model->monster), base);*/
          /*Comparing so stationary objects are not redrawn*/

        render_animal(&(model->chicken), base);
    

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
***********************************************************************

void render_score(Score *score, UINT32 *base)
{
    UINT8 i;
    int temp;
    int currentDigits = score->total;
    
    temp = score->total;
    for(i=0; i < currentDigits; currentDigits-=1)
    {
        clear_bitmap_8((UINT16*)base, currentDigits<<4, 8, char_delete, FONT_HEIGHT);
        plot_bitmap_8((UINT16*)base, currentDigits<<4, 8, GLYPH_START(temp%10+'0'), FONT_HEIGHT);
        temp = temp/10;
    }
}
*/
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
void render_coin(Coin *coin, UINT16 *base)
{
    plot_bitmap_16(base, coin->x, coin->y, coin_bitmap, COIN_HEIGHT);
}


