#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <chrono>

int main(int argc, char **argv){
    std::mt19937 mt{ static_cast<unsigned int>(
    std::chrono::steady_clock::now().time_since_epoch().count()
    ) };
    
    int n = atoi(argv[1]);
    printf("%d\n", n);
    
    std::uniform_int_distribution<> randInt(0,(2*n -1));
    std::uniform_int_distribution<> randomPosition(1,n);
    
    printf("%d\n",randomPosition(mt));

    for (int i = 0; i < n; i++){
        printf("%d\n", randInt(mt));
    }

    return 0;
}