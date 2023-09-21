#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Count from 1 to 2^32
    unsigned int count = 1;
    while (count != 4294967296) {
        count++;
    }
    return 0;
}
