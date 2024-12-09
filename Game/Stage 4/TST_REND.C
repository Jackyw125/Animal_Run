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
    
    initialize_model(model);

    clear_screen((UINT8*)base);

    render(model, base); 

    loop = 0;
 
    return 0;
}