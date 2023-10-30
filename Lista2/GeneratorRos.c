#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int n = atoi(argv[1]);
    printf("%d\n", n);
    for(int i = 0; i < n; i++) {
        printf("%d\n", i);
    }
}
