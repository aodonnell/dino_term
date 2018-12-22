#ifndef PRINTLIB_H_
#define PRINTLIB_H_

#include "Geometry.h"
#include "../things/Sprite.h"

Vec2i termSize;

void termInit();

void termFinish();

void termClear();

void termRefresh();

void drawLine(char * const line, const Vec2i * pos);

void drawLineAlpha(char * const line, const Vec2i * pos);

void drawSprite(const Sprite * sprite);

const Vec2i * getTermSize();

#endif
