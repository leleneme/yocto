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

// Syntax Hightlighting
enum editorHighlight {
    HL_NORMAL = 0,
    HL_NUMBER,
    HL_MATCH
};

#define HL_HIGHLIGHT_NUMBERS (1<<0)

struct editorSyntax {
    char *filetype;
    char **filematch;
    int flags;
};

// Editor Row
typedef struct erow {
    int size;
    int rsize;
    char *chars;
    char *render;
    unsigned char *hl;
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

    struct editorSyntax *syntax;
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

/* Syntax highlighting */
int is_separator(int c);
void editorUpdateSyntax(erow *row);
int editorSyntaxToColor(int hl);
void editorSelectSyntaxHighlight();

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
int editorRowRxToCx(erow *row, int rx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);

/* Editor operations */
void editorInsertChar(int c);
void editorInsertNewLine();
void editorDelChar();

/* Editor file I/O */
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave();

/* Input */
char *editorPrompt(char *prompt, void (*callback)(char *, int));

/* Search */
void editorFindCallback(char *query, int key);
void editorFind();

/* Editor Initialization */
void initEditor();

#endif