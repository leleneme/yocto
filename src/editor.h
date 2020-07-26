#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)
#define VERSION "0.0.1"
#define TAB_STOP 8 //Tab size

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
    int rsize;
    char *chars;
    char *render;
} erow;

struct editorConfig {
    int cx, cy; // Cursor position
    int rx;

    int rowoff;
    int coloff;

    int screenrows;
    int screencols;

    int numrows;
    erow *row;

    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;

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
void editorSetStatusMessage(const char *fmt, ...);
void editorScroll();
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);

/* Row Operations */
int editorRowCxToRx(erow *row, int cx);
void editorUpdateRow(erow *row);
void editorAppendRow(char *s, size_t len);
void editorRowInsertChar(erow *row, int at, int c);

/* Editor operations */
void editorInsertChar(int c);

/* Editor file I/O */
void editorOpen(char *filename);

/* Editor Initialization */
void initEditor();

#endif