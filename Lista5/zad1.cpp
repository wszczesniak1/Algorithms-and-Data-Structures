#include <iostream>
#include <string.h>
#include <chrono>
int comparisions = 0;

void printLCS( int **backTrace_table, char *x, int m, int n ) {
  if ( n == -1 || m == -1 )
    return;
  if ( backTrace_table[m][n] == 3 ) {
    printLCS( backTrace_table, x, m - 1, n - 1 );
    std::cout << " " << x[m];
  } else if ( backTrace_table[m][n] == 1 ) {
    printLCS( backTrace_table, x, m - 1, n );
  } else if ( backTrace_table[m][n] == 2 ){
    printLCS( backTrace_table, x, m, n - 1 );
  } else if ( backTrace_table[m][n] == 5 ) {
    std::cout << " LCS: ";
    std::cout << x[m];
  } else {
    std::cout << " LCS: ";
  }
}


void LCS ( int **length_table, int **backTrace_table, char *y, char *x, int n , int m ) {//?
  for ( int j = 0; j < n; j++ ) {
    comparisions++;
    if ( x[0] == y[j] ) {
      length_table[0][j] = 1;
      backTrace_table[0][j] = 5;
    } else if ( j > 0){
      comparisions++;
      if ( length_table[0][j - 1] > length_table[0][j] ) {
        length_table[0][j] = length_table[0][j - 1];
        backTrace_table[0][j] = 2;
      }
    } 
  }
  for ( int i = 0; i < m; i++ ) {
      comparisions++;
    if ( x[i] == y[0] ) {
      length_table[i][0] = 1;
      backTrace_table[i][0] = 5;
    } else if ( i > 0) {
      comparisions++;
      if ( length_table[i - 1][0] > length_table[i][0] ) {
        length_table[i][0] = length_table[i - 1][0];
        backTrace_table[i][0] = 1;
      }
    }
  }

  for ( int i = 1; i < m; i++ ) {
    for ( int j = 1; j < n; j++ ) {
      comparisions++;
      if ( x[i] == y[j] ) {
        length_table[i][j] = length_table[i - 1][j - 1] + 1;
        backTrace_table[i][j] = 3;
      } else if ( length_table[i - 1][j] > length_table[i][j - 1] ) {
        comparisions++;
        length_table[i][j] = length_table[i - 1][j];
        backTrace_table[i][j] = 1;
      } else {
        comparisions++;
        length_table[i][j] = length_table[i][j - 1];
        backTrace_table[i][j] = 2;
      }
    }
  }

  std::cout << "lenght table" << std::endl;
  for ( int i = 0; i < m; i++ ) {
    // std::cout << "I= " << i << std::endl;
    for ( int j = 0; j < n; j++ ) {
      std::cout <<  " " << length_table[i][j];
    }
    std::cout << std::endl;
  }
  
  printLCS( backTrace_table, x, m - 1, n - 1 );
  std::cout << std::endl;
}

int main( int argc, char* argv[]) {
  auto start = std::chrono::high_resolution_clock::now();

  int k = atoi(argv[argc - 1]);
  
  int n = strlen(argv[1]);
  int m = strlen(argv[2]);

  std::cout << "n: " << n << " m: " << m << std::endl;
  std::cout << "y: " << argv[1] << " x: " << argv[2] << std::endl;

  int** length_table = new int*[m];
  int** backTrace_table = new int*[m];//3 - up & left, 2 - left, 1 - up
  for ( int i = 0; i < m; i++ ) {
    length_table[i] = new int[n];
    backTrace_table[i] = new int[n];
    for ( int j = 0; j < n; j++ ) {
      length_table[i][j] = 0;
      backTrace_table[i][j] = 0;
    }
  }
  LCS( length_table, backTrace_table, argv[1], argv[2], n, m);

  delete[] length_table;
  delete[] backTrace_table;
  
  return 0;
}
