#ifndef EDITOR_C
#define EDITOR_C

#include "editor.h"

/* Error handling */
void die(const char *err) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(err);
    exit(1);
}

/* Raw mode stuff */
//struct termios orig_termios;

struct editorConfig E;

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
        die("tcgetattr");

    atexit(disableRawMode);

    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
}

/* Editor functions*/
int getCursorPosition(int *rows, int *cols) {
    char buffer[32];
    unsigned int i = 0;

    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return -1;

    while(i < sizeof buffer - 1) {
        if(read(STDIN_FILENO, &buffer[i], 1) != 1)
            break;
        if(buffer[i] == 'R')
            break;
        i++;
    }
    buffer[i] = '\0';

    if (buffer[0] != '\x1b' || buffer[i] != '[')
        return -1;
    if (sscanf(&buffer[2], "%d;%d", rows, cols) != 2)
        return -1;

    return 0;
}

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
            return -1;
        return getCursorPosition(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

char editorReadKey() {
    int nread;
    char c;

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }
    return c;
}

void editorProcessKeypress() {
    char c = editorReadKey();

    switch (c)
    {
    case CTRL_KEY('q'):
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
        exit(0);
        break;
    }
}

void editorDrawRows() {
    int y;
    for(y = 0; y < E.screenrows; y++) {
        write(STDIN_FILENO, "~", 3);

        if(y < E.screenrows - 1) {
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}

void editorRefreshScreen() {
    // \x1b -> escape character

    // clear the screen
    write(STDIN_FILENO, "\x1b[2J", 4);
    // put cursor at the top-left
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows();
    // put cursor at the top-left
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void initEditor() {
    if (getWindowSize(&E.screenrows, &E.screencols) == -1)
        die("getWindowSize");
}


#endif