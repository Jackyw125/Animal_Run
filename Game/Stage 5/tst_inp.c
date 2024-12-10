#include <stdio.h>
#include <osbind.h>
#include "MODEL.H"
#include "INPUT.H"
#include "TYPES.H"

int main() {
    char pressedKey = 0;
    Model testModel;

    printf("Testing input function. Press SPACE, W, or Q to see the output. Press Q to quit.\n");

    while (1) {
        input(&testModel, &pressedKey);

        if (pressedKey == 'q' || pressedKey == 'Q') {
            printf("Quit key pressed. Exiting test.\n");
            break;
        } else if (pressedKey) {
            printf("Key pressed: %c\n", pressedKey);  
        }
    }

    return 0;
}
