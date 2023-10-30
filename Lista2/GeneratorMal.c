#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int n = atoi(argv[1]);
    printf("%d\n", n);
    for(int i = n; i > 0; i--) {
        printf("%d\n", i);
    }
}
