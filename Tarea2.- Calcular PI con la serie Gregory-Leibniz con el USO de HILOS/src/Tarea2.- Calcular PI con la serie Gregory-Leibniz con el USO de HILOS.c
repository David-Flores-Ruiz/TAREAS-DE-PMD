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
#include <time.h>	//Para funcion clock() que regresa el tiempo en MILISEGUNDOS en que se ejecutó el programa

#include <windows.h>	// Para el uso y creación de hilos (en windows)

typedef struct {
	unsigned long long ini;
	unsigned long long fin;
	double sumatoriaParcial; //Genera mis 4 "n" acumuladores, para sumarlos al final
} RANGO;

DWORD WINAPI aproxPI(void *);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	clock_t inicial, final, total;
	int numHilos;
	printf("Hilos? \t");
	scanf("%d", &numHilos);
//	printf("%d \n", numHilos); //Ya lee la cantidad de hilos que usará!!!
	HANDLE hilo[16];
	int i;
	double SumatoriaFinal = 0, valorPI;
	RANGO arrRangos[16]; // EL nombre tiene la direccion inicial
	unsigned long long Razon;
	Razon = 50000000000 / numHilos;
//	printf("El valor de razon es: %I64u\n", Razon);

	for (i = 0; i < numHilos; i++) {	//Repartir los Rangos segun el numHilos
		arrRangos[i].ini = (Razon * (i + 1)) - Razon + 1; //Inicios del for
		arrRangos[i].fin = (Razon * (i + 1));//fin de los for
		arrRangos[i].sumatoriaParcial = 0;//Inicializar los acumuladores
	}

/*
	for (i = 0; i < numHilos; i++) {	//Comprobar en pantalla el valor de los rangos
		printf("Ini %I64u\n", arrRangos[i].ini);
		printf("Fin %I64u\n", arrRangos[i].fin);
		printf("Suma Parcial en0:  %lf\n", arrRangos[i].sumatoriaParcial);
	}
*/

	inicial = clock();
	printf("Going to scan a big loop, inicial = %ld\n", inicial);

	for (i = 0; i < numHilos; i++) { //Crear los hilos y ejecutar sus funciones
		hilo[i] = CreateThread(
		NULL,	//Seguridad por default
				0,	//tamaño de stack por default (memoria estática)
				aproxPI,	//dirección de la funcion que ejecuta el hilo
				(void *) &arrRangos[i],	//(direción) del parametro de la funcion tipo void
				0,	//ejecutar inmediatamente la función
				NULL	//sin ID para el Hilo
				);
	}

	WaitForMultipleObjects(numHilos, hilo, TRUE, INFINITE);

	RANGO *p = arrRangos;
	for (i = 0; i < numHilos; i++) {
		SumatoriaFinal = SumatoriaFinal + (p + i)->sumatoriaParcial;
	}

	valorPI = 4.0 * SumatoriaFinal; // Multiplicar 4 * sumatoriaFinal
	final = clock();
	printf("End of the big loop, final = %ld\n", final);
	total = (1000 * (final - inicial)) / CLOCKS_PER_SEC;

	printf("\nTiempo de ejecución:  %ld  ms", total);

	printf("\nPI:\t %.10lf", valorPI);
	return EXIT_SUCCESS;
}

DWORD WINAPI aproxPI(void *losRangos) {
	RANGO *p = (RANGO *) losRangos;
	double numerador, denominador; //PI
	unsigned long long n;
	for (n = p->ini; n <= p->fin; n++) { //Debe ser la prueba final con: 50_000_000_000
		numerador = ((n + 1) & 1) ? -1 : 1;
		denominador = (2 * n) - 1;
		p->sumatoriaParcial = p->sumatoriaParcial + (numerador / denominador);
	}
	return 0;
}

