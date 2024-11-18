#ifndef RENDER_H
#define RENDER_H

#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"
#include "FONT.H"

void render(Model *model, UINT32 *base);
void render_animal(const Animal *chicken, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_score(Score *score, UINT32 *base);
void render_coin(Coin *coin, UINT16 *base);
void render_ground(Ground *ground, UINT8 *base);

#endif
