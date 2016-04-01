#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int crout (size_t alto, size_t ancho, real A[alto][ancho]) {
  if (ancho != alto) return 1;
  
  //definimos las variables necesarias
  int n = ancho;
  real l[n][n], u[n][n], d[n];  //descomposicion matricial
  int k,i,j; //variables contador
  real sum;  //variable sumatorio

  //bucle K
  /* k = 0 */
  l[0][0] = u[0][0] = 1;
  d[0] = 1;
  /* k = 1 -> n*/
  for(k = 1; k < n; k++){
    //U
    for(i = 0; i < k; i++) {
      for(j = 0, suma = 0; j < i; j++)
	suma += l[i][j] * u[j][k]; 
      u[i][k] = (A[i][k] - suma)/d[i];
    }

    //L
    for(i = 0; i < k; i++) {
      for(j = 0, suma = 0; j < i; j++)
	suma += u[j][i] * l[k][j];
      l[k][i] = (A[k][i] - suma)/d[i];
    }
    
    //Siguientes elementos
    l[k][k] = u[k][k] = 1;
    
    for(j = 0, suma = 0; j < k)
      suma += l[k][j] * d[j] * u[j][k];
    d[k] = A[k][k] - suma;
  }

  //Modificamos la matriz
  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      if (i<j)
	A[i][j] = u[i][j];
      else if (i==j)
	A[i][j] = d[i];
      else
	A[i][j] = l[i][j];
    }
  }
  return 0;
}

int main (int argc, char* argv[]) {
  printf("\n Crout descomposition in C\n");
  // a test
  real A[4][4];
  A[0][0] = 1;
  A[0][1] = -0.6875;
  A[0][2] = 0;
  A[1][0] = -0.3125;
  A[1][1] = 1;
  A[1][2] = -0.6875;
  A[2][0] = 0;
  A[2][1] = -0.3125;
  A[2][2] = 1;

  printf("\nMatrix A:");
  printMatrix(A);
  printf("\nDecomposited matrix:");
  printMatrix(A);

}

void printMatrix (size_t alto, size_t ancho, real A[alto][ancho]) {
  int i,j;
  printf("\n");
  for(i=0;i<alto;i++) {
    for(j=0;j<ancho;j++) 
      printf("%.5f ",A[i][j]);
    printf("\n");
  }
}
