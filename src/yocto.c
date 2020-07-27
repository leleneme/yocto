#include <unistd.h>
#include "editor.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr,"Usage: yocto <filename>\n");
        exit(1);
    }

    enableRawMode();
    initEditor();
    editorOpen(argv[1]);

    editorSetStatusMessage("[HELP] Ctrl-Q: quit | Ctrl-S: save | Ctrl-F: find");

    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
