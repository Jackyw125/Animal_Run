#include <osbind.h>
#include "RENDER.H"
#include "MODEL.H"
#include "stdio.h"

int main()
{
    int i;
    int j;
    int loop;
    UINT32 *base = Physbase();
    UINT16 *base2 = Physbase();
    Model initialModel;
    Model *model = &initialModel;

    clear_screen((UINT8*)base);

    initialize_animal(model);
    initialize_monster(model);
    initialize_coins(model);

    render_animal(&(model->chicken), base);
    render_monster(&(model->monster), base);
    /*render_score(&(model->score), base2);*/
    render_coin(&(model->coins), base2);
    
    loop = 0;

    /*render(model, base);*/
 
    return 0;
}