#include <unistd.h>
#include "raw.h"

int main() {
    enableRawMode();

    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != "q") {
        if(iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n", c, c);
        }
    }

    return 0;
}
