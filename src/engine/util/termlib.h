#ifndef PRINTLIB_H_
#define PRINTLIB_H_

#include "Geometry.h"

void termInit();

void termFinish();

void termClear();

void termRefresh();

void drawLine(char * line, void * vec);

const Vec2i * getTermSize();

#endif
