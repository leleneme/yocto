#include <unistd.h>
#include "editor.h"

int main() {
    enableRawMode();

    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
