#include <unistd.h>
#include "raw.h"

int main() {
    enableRawMode();

    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != "q") {
        if(iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
    }

    return 0;
}
