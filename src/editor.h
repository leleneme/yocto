#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)

struct editorConfig {
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

/* Error handling */
void die(const char *err);

/* Raw mode stuff */
void enableRawMode();
void disableRawMode();

/* Editor functions*/
int getWindowSize(int *rows, int *cols);

char editorReadKey();
void editorProcessKeypress();

void editorRefreshScreen();
void editorDrawRows();

void initEditor();

#endif