/*
[SZÁMÍTÓGÉPI GRAFIKA BEADANDÓ FELADAT]
[----------LOW-BUDGET SIMCITY-------]
[-------------Kozma János-----------]
[---------------SVOXGH--------------]
*/

#include "model.h"
#ifndef INCLUDE_DRAW_H_
#define INCLUDE_DRAW_H_
#ifndef GL_EXT_texture_edge_clamp
#define GL_CLAMP_TO_EDGE                 0x812F
#endif

void draw_content(World* world);

void draw_ground(City city);

void draw_walls(City city);

void draw_model(const struct Model* model);

void draw_help(int texture);

#endif
