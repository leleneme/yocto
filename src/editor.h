#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)

#define VERSION "0.0.1"
#define TAB_STOP 4 //Tab size
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
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};

#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

struct editorSyntax {
    char *filetype;
    char **filematch;
    char **keywords;
    char *singleline_comment_start;
    char *multiline_comment_start;
    char *multiline_comment_end;
    int flags;
};

/* A struct that represents a single row of the file loaded */
typedef struct erow {
    int idx;  // Row index (stars at 0)

    int size;  // Size of the row, ignoring the null byte at the end
    int rsize; // Size of the rendered row, with tabs and stuff
    char *chars; // The actual content of the row, just chars
    char *render; // The row content rendered, with tabs and stuff
    unsigned char *hl; // Highlighting type for each chars in *render

    int hl_open_comment; // If the row had a not closed comment
} erow;

struct editorConfig {
    int cx, cy; // Cursor position
    int rx;     // Cursor position at the render

    int rowoff; // Row offset 
    int coloff; // Column offset

    int screenrows; // Number of rows in the terminal window
    int screencols; // Number of cols in the terminal window

    int numrows; // Number of rows
    erow *row; // Actual rows!
    int dirty; // Flag that checks if file is modified

    char *filename; // Filename of the current file opened
    char statusmsg[80];
    time_t statusmsg_time;

    struct editorSyntax *syntax; // Current syntax highlight used
    struct termios orig_termios;
};

/* The append buffer is a struct with a heap allocated string
 * that can be appended to (that's where the name comes from)
 * 
 * Used to write all escape sequences in a buffer to then
 * flush everything to the standart output at once, to
 * prevent flickering
 * learned that from the DOS experience :') */
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