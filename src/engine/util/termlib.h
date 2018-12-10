#ifndef PRINTLIB_H_
#define PRINTLIB_H_

#include "Geometry.h"

Vec2i termSize;

void termInit();

void termFinish();

void termClear();

void termRefresh();

void drawLine(char * line, Vec2i * pos);

void drawLineAlpha(char * line, Vec2i * pos);

const Vec2i * getTermSize();

#endif
