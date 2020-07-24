#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)

void die(const char *err);
void enableRawMode();
void disableRawMode();

#endif