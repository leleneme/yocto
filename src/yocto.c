#include <unistd.h>
#include "editor.h"

int main(int argc, char *argv[]) {
    enableRawMode();
    initEditor();
    if(argc >= 2) {
        editorOpen(argv[1]);
    }

    editorSetStatusMessage("[HELP] Ctrl-Q: quit | Ctrl-S: save | Ctrl-F: find");

    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
