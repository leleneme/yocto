#include <unistd.h>
#include "editor.h"

int main() {
    enableRawMode();
    initEditor();

    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
