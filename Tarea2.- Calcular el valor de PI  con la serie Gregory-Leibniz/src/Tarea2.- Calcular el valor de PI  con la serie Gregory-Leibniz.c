/*
 ============================================================================
 Name        : -.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <time.h>	//Para funcion clock() que regresa el tiempo en MILISEGUNDOS en que se ejecuto el programa

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	clock_t inicial, final, total;
	double numerador, denominador;
	double sumatoria = 0;
	double PI;
	unsigned long long n;
	//printf("Los numeros de la serie son:");
	inicial = clock();
	   printf("Going to scan a big loop, inicial = %ld\n", inicial);
	for(n=1; n<=500000000; n++){ //Debe ser la prueba final con: 50_000_000_000
		numerador =( (n+1) & 1 )? -1 : 1;	//		if ( (n+1) %2 == 0 )
											//			numerador = 1;
											//		else
											//			numerador = -1;
											//numerador = pow(-1,n+1);
		denominador = (2*n) - 1;
		  //printf("Going to scan a big loop, cambiando = %ld\n", clock());
		sumatoria = sumatoria + (numerador/denominador);
		//printf("\n %.15lf", sumatoria);
	}

	PI = 4.0*sumatoria; // Multiplicar 4 * sumatoriaFinal

	final = clock();
	printf("End of the big loop, final = %ld\n", final);
	total = (1000 *(final - inicial )) /CLOCKS_PER_SEC;

	printf("\nTiempo de ejecución:  %ld  ms", total);
	printf("\nPI:\t %.10lf", PI);

	return EXIT_SUCCESS;
}
