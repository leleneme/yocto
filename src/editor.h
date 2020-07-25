#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)
#define VERSION "0.0.1"

enum editorKey {
    ARROW_LEFT = 1000, 
    ARROW_RIGHT, 
    ARROW_UP, 
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN
};

struct editorConfig {
    int cx, cy; // Cursor position
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

/* Append buffer */
struct abuf {
    char *b;
    int len;
};
#define ABUF_INIT {NULL, 0}

/* Error handling */
void die(const char *err);

/* Raw mode stuff */
void enableRawMode();
void disableRawMode();

/* Editor functions*/
void abAppend(struct abuf *ab, const char *s, int len);

int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);

void editorMoveCursor(int key);
int editorReadKey();
void editorProcessKeypress();

void editorRefreshScreen();
void editorDrawRows();

void initEditor();

#endif