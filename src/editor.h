#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)

#define VERSION "0.0.1"
#define TAB_STOP 8 //Tab size
#define QUIT_TIMES 2 // Times you need to press ^Q to confirm exit

// Editor Keys
enum editorKey {
    BACKSPACE = 127,
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
    int dirty;

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
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);

/* Editor operations */
void editorInsertChar(int c);
void editorDelChar();

/* Editor file I/O */
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave();

/* Editor Initialization */
void initEditor();

#endif