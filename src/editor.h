#ifndef EDITOR_H
#define EDITOR_H

#include "headers.h"

#define CTRL_KEY(k) ((k) & 0x1f)

struct editorConfig {
    struct termios orig_termios;
};

/* Error handling */
void die(const char *err);

/* Raw mode stuff */
void enableRawMode();
void disableRawMode();

/* Editor functions*/
/* Input */
char editorReadKey();
void editorProcessKeypress();

/* Output */
void editorRefreshScreen();
void editorDrawRows();

#endif