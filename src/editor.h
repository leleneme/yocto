#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)
#define VERSION "0.0.1"

// Editor Keys
enum editorKey {
    ARROW_LEFT = 1000, 
    ARROW_RIGHT, 
    ARROW_UP, 
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN,
};

// Editor Row
typedef struct erow {
    int size;
    char *chars;
} erow;

struct editorConfig {
    int cx, cy; // Cursor position
    int rowoff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
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
void editorScroll();
void editorDrawRows();

/* Row Operations */
void editorAppendRow(char *s, size_t len);

/* Editor file I/O */
void editorOpen(char *filename);

/* Editor Initialization */
void initEditor();

#endif