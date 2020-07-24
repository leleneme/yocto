#include <unistd.h>
#include "editor.h"

int main() {
    enableRawMode();

    while(1) {
        editorProcessKeypress();
    }

    return 0;
}
