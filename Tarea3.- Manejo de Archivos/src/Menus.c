/*
 ============================================================================
 Name        : NEW_TAREA.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct{
	int dia;
	int mes;
	int ano;
}fecha;

typedef struct{
	int id;
	char nombre[25];
	char paterno[25];
	char materno[25];
	fecha nacimiento;
}Cliente;

typedef struct{
	int id_cuenta;
	int id_cliente;
	int saldo;
	fecha apertura;
}Cuenta;

typedef struct{
	int id_transaccion;
	char operacion[15];
	int cuenta_origen;
	int cuenta_destino;
	int monto;
	fecha fch_transaccion;
}Transaccion;


enum MenuPrincipal {Cero, Clientes, Cuentas, Transacciones, Salir};

void submenuCliente();
void submenuCuentas();
void submenuTransacciones();

void altaCliente (Cliente clientes[MAX], int posicion, Cliente *arrApuntadores[]);
void buscarCliente (Cliente clientes[MAX], Cliente *arrApuntadores[]);
void eliminarCliente (Cliente clientes[MAX], Cliente *arrApuntadores[]);
void imprimirClientes(Cliente clientes[MAX], Cliente *arrApuntadores[]);

int altaCuenta (Cuenta cuentas[MAX], int posiCuentas, Cuenta *apCuentas[]);
void buscarCuenta (Cuenta cuentas[MAX], Cuenta *apCuentas[]);
void eliminarCuenta (Cuenta cuentas[MAX], Cuenta *apCuentas[], int valor);
void imprimirCuentas(Cuenta cuentas[MAX], Cuenta *apCuentas[]);

int deposito (Transaccion transacciones[MAX], int posTransa, Transaccion *apTransa[]);
int retiro (Transaccion transacciones[MAX], int posTransa, Transaccion *apTransa[]);
int transferencia (Transaccion transacciones[MAX], int posTransa, Transaccion *apTransa[]);


Cliente clientes[MAX];
int posicion = 0;
Cliente *arrApuntadores[MAX];


Cuenta cuentas[MAX];
int posiCuentas = 0;
Cuenta *apCuentas[MAX];

Transaccion transacciones[MAX];
int posTransa = 0;
Transaccion *apTransa[MAX];


//GLOBALES para funcion Crear o abrir Archivos Binarios
FILE *mydb_sys;	//Para guardar ruta de acceso de los otros 3 archivos binarios
FILE *clientes_dat = NULL, *cuentas_dat = NULL, *transacciones_dat = NULL;
char rutaClientes[35] = "";
char rutaCuentas[35] = "";
char rutaTransacciones[35] = "";
void leerArchivo (FILE *archivo, char arr[]);
void ArchivosBinarios ();

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	ArchivosBinarios ();	//Pide ruta y crea los archivos BINARIOS


	int i;
	for(i=0; i<MAX; i++){
		arrApuntadores[i] = NULL;	//Inicializar el Arreglo de apuntadores en posiciones NULL
	}

	for(i=0; i<MAX; i++){
		apCuentas[i] = NULL;	//Inicializar el Arreglo de apuntadores en posiciones NULL
	}

	for(i=0; i<MAX; i++){
		apTransa[i] = NULL;	//Inicializar arreglo de apuntadores
	}


	int opcion;
	    do{
	    	printf("\n \t _-_-_MENU PRINCIPAL_-_-_");
	        printf("\n1. Clientes");
	        printf("\n2. Cuentas");
	        printf("\n3. Transacciones");
	        printf("\n4. Salir");

	        printf("\nEscoja su opción (1-4) el número válido:");
	        scanf("%d", &opcion);

	        switch(opcion)
	           {
	               case Clientes: submenuCliente();
	                       break;

	               case Cuentas: submenuCuentas();
	                       break;

	               case Transacciones: submenuTransacciones();
	                       break;

	               default:
	            	   if(opcion != Salir)
	            		   printf( "\n-----Número NO válido, escoja de nuevo-----");
	           }

	    }while(opcion != Salir);


//Para leer su contenido CLIENTES.dat
	    clientes_dat = fopen(rutaClientes,"rb");
	    if (clientes_dat==NULL){
	    	printf("Error al abrir archivo clientes_dat\n");
	    }
	    else{
	    	printf("\nTodos los datos almacenados en el archivo clientes_dat.");
	    	Cliente arrLeerClientes[250];
	    	i = 0;
	    	fread(&arrLeerClientes[i], sizeof(Cliente), 1, clientes_dat);
	    	//Cliente *apunCliente = arrLeerClientes;
	    	while( !feof(clientes_dat) )
	    	{
	    		//if( (apunCliente + i)->id != -5 ){
	    		printf("\n****Cliente %d****", i+1);
	    		printf("\nEl ID es: %d", arrLeerClientes[i].id);
	    		printf("\nEl nombre del cliente es: %s",  arrLeerClientes[i].nombre);
	    		printf("\nEl apellido Paterno del cliente es: %s",  arrLeerClientes[i].paterno);
	    		printf("\nEl apellido Materno del cliente es: %s",  arrLeerClientes[i].materno);
	    		printf("\nSu fecha de Nacimiento es: %d / %d / %d \n",  arrLeerClientes[i].nacimiento.dia,  arrLeerClientes[i].nacimiento.mes,  arrLeerClientes[i].nacimiento.ano);
	    		i++;//Leer la siguiewnte
	    		fread(&arrLeerClientes[i], sizeof(Cliente), 1, clientes_dat);
	    		//}
	    	}
	    	fclose(clientes_dat);
	    }



//Para leer su contenido CUENTAS.dat
	    cuentas_dat = fopen(rutaCuentas,"rb");
	    if (cuentas_dat==NULL){
	    	printf("Error al abrir archivo cuentas_dat\n");
	    }
	    else{
	    	printf("\nTodos los datos almacenados en el archivo cuentas_dat.");
	    	Cuenta arrLeerCuentas[250];
	    	i = 0;
	    	fread(&arrLeerCuentas[i], sizeof(Cuenta), 1, cuentas_dat);
	    	//Cuenta *apunCuenta = arrLeerCuentas;
	    	while( !feof(cuentas_dat) )
	    	{
	    		//if( (apunCuenta + i)->id != -5 ){
	    		printf("\n****Cuenta %d****", i+1);
	    		printf("\nEl ID cuenta es: %d", arrLeerCuentas[i].id_cuenta);
	    		printf("\nEl ID del cliente es: %d",  arrLeerCuentas[i].id_cliente);
	    		printf("\nEl saldo en la ciuenta es: %d",  arrLeerCuentas[i].saldo);
	    		printf("\nSu fecha de Nacimiento es: %d / %d / %d \n",  arrLeerCuentas[i].apertura.dia,  arrLeerCuentas[i].apertura.mes,  arrLeerCuentas[i].apertura.ano);
	    		i++;//Leer la siguiewnte
	    		fread(&arrLeerCuentas[i], sizeof(Cuenta), 1, cuentas_dat);
	    		//}
	    	}
	    	fclose(cuentas_dat);
	    }



//Para leer su contenido TRANSACCIONES.dat
	    transacciones_dat = fopen(rutaTransacciones,"rb");
	    if (transacciones_dat==NULL){
	    	printf("Error al abrir archivo transacciones_dat\n");
	    }
	    else{
	    	printf("\nTodos los datos almacenados en el archivo transacciones_dat.");
	    	Transaccion arrLeerTransacciones[250];
	    	i = 0;
	    	fread(&arrLeerTransacciones[i], sizeof(Transaccion), 1, transacciones_dat);
	    	//Transaccion *apunTransaccion = arrLeerTransacciones;
	    	while( !feof(transacciones_dat) )
	    	{
	    		//if( (apunTransaccion + i)->id != -5 ){
	    		printf("\n****Transaccion %d****", i+1);
	    		printf("\nEl ID transaccion es: %d", arrLeerTransacciones[i].id_transaccion);
	    		printf("\nLa operación realizada es: %s",  arrLeerTransacciones[i].operacion);
	    		printf("\nLa cuenta de origen es: %d",  arrLeerTransacciones[i].cuenta_origen);
	    		printf("\nLa cuenta de origen es: %d",  arrLeerTransacciones[i].cuenta_destino);
	    		printf("\nEl monto fue de: %d", arrLeerTransacciones[i].monto);
	    		printf("\nSu fecha de Nacimiento es: %d / %d / %d \n",  arrLeerTransacciones[i].fch_transaccion.dia,  arrLeerTransacciones[i].fch_transaccion.mes,  arrLeerTransacciones[i].fch_transaccion.ano);
	    		i++;//Leer la siguiewnte
	    		fread(&arrLeerTransacciones[i], sizeof(Transaccion), 1, transacciones_dat);
	    		//}
	    	}
	    	fclose(transacciones_dat);
	    }



	return EXIT_SUCCESS;
}





int deposito (Transaccion transacciones[MAX], int posTransa, Transaccion *apTransa[]){
	Transaccion *arrTransa = transacciones;	//Declarar puntero local
	int auxID = posTransa + 1;
	char auxOperacion[15];
	int cuentaOrigen;
	//int cuentaDestino; Vale 0 no se utiliza
	int auxMonto;
	int dia, mes, ano;


	int i=0, bandera = 0;
	Cuenta *apunArr = cuentas;

	printf("\nPara hacer el depósito, introduzca su ID de cuenta: ");
	scanf("%d", &cuentaOrigen);
	for(i=0; i < MAX; i++){
		if( (apunArr + i)->id_cuenta == cuentaOrigen )
		{
			printf("Su ID de Transaccion es --- %d --- \n", auxID);

			printf("Dame el monto del depósito es:\n");
			scanf("%d", &auxMonto);

			(apunArr + i)->saldo = (apunArr + i)->saldo + auxMonto;	//DEPÓSITO

			setbuf(stdin, 0);
			printf("Dame la fecha de la transaccion dd/mm/aa:\n");
			scanf("%d %d %d", &dia, &mes, &ano);

			(arrTransa + posTransa)->id_transaccion = auxID;

			strcpy(((arrTransa + posTransa)->operacion),"");
			strcpy( auxOperacion , "Deposito");
			strcpy( ((arrTransa + posTransa)->operacion), auxOperacion );

			(arrTransa + posTransa)->cuenta_origen = cuentaOrigen;
			(arrTransa + posTransa)->cuenta_destino = 0;
			(arrTransa + posTransa)->monto = auxMonto;

			(arrTransa + posTransa)->fch_transaccion.dia = dia;
			(arrTransa + posTransa)->fch_transaccion.mes = mes;
			(arrTransa + posTransa)->fch_transaccion.ano = ano;
			apTransa[posTransa] = (arrTransa + posTransa);	//Ya no es NULL el Arreglo del main
			bandera = 1;

			//Escribir en Archivo nuevas transacciones
			transacciones_dat = fopen(rutaTransacciones, "a+b");
			fwrite(&arrTransa[posTransa], sizeof( Transaccion ), 1, transacciones_dat);
			fclose(transacciones_dat);

			//Actualizar el archivo Cuentas con lo mas nuevo
			cuentas_dat = fopen(rutaCuentas, "wb");//Borrar lo que habia antes en cuentas_dat
			fclose(cuentas_dat);

			cuentas_dat = fopen(rutaCuentas, "a+b");//Borrar lo que habia antes en cuentas_dat
			for(i=0; i<posiCuentas; i++)
				fwrite(&cuentas[i], sizeof( Cuenta ), 1, cuentas_dat);
			fclose(cuentas_dat);

			return 1;

		}
	}
	if(bandera == 0){
		printf("\nNo se pudo realizar el deposito, el ID de cuenta no existe\n");
		return 0;
	}
	return -8;//Seria un error el -8
}


int retiro (Transaccion transacciones[MAX], int posTransa, Transaccion *apTransa[]){
	Transaccion *arrTransa = transacciones;	//Declarar puntero local
	int auxID = posTransa + 1;
	char auxOperacion[15];
	int cuentaOrigen;
	//int cuentaDestino; Vale 0 no se utiliza
	int auxMonto;
	int dia, mes, ano;

	int i=0, bandera = 0;
	Cuenta *apunArr = cuentas;

	printf("\nPara hacer el RETIRO, introduzca su ID de cuenta: ");
	scanf("%d", &cuentaOrigen);
	for(i=0; i < MAX; i++){
		if( (apunArr + i)->id_cuenta == cuentaOrigen )
		{
			printf("Su ID de Transaccion es --- %d --- \n", auxID);

			printf("Dame el monto del retiro:\n");
			scanf("%d", &auxMonto);

			while((apunArr + i)->saldo < auxMonto){
				printf("El monto excede su Saldo, dame el monto del retiro:\n");
				scanf("%d", &auxMonto);
			}

			(apunArr + i)->saldo = (apunArr + i)->saldo - auxMonto;	//RETIRO

			setbuf(stdin, 0);
			printf("Dame la fecha de la transaccion dd/mm/aa:\n");
			scanf("%d %d %d", &dia, &mes, &ano);

			(arrTransa + posTransa)->id_transaccion = auxID;

			strcpy(((arrTransa + posTransa)->operacion),"");
			strcpy( auxOperacion , "Retiro");
			strcpy( ((arrTransa + posTransa)->operacion), auxOperacion );

			(arrTransa + posTransa)->cuenta_origen = cuentaOrigen;
			(arrTransa + posTransa)->cuenta_destino = 0;
			(arrTransa + posTransa)->monto = auxMonto;

			(arrTransa + posTransa)->fch_transaccion.dia = dia;
			(arrTransa + posTransa)->fch_transaccion.mes = mes;
			(arrTransa + posTransa)->fch_transaccion.ano = ano;
			apTransa[posTransa] = (arrTransa + posTransa);	//Ya no es NULL el Arreglo del main
			bandera = 1;

			//Escribir en Archivo nuevas transacciones
			transacciones_dat = fopen(rutaTransacciones, "a+b");
			fwrite(&arrTransa[posTransa], sizeof( Transaccion ), 1, transacciones_dat);
			fclose(transacciones_dat);

			//Actualizar el archivo Cuentas con lo mas nuevo
			cuentas_dat = fopen(rutaCuentas, "wb");//Borrar lo que habia antes en cuentas_dat
			fclose(cuentas_dat);

			cuentas_dat = fopen(rutaCuentas, "a+b");//Borrar lo que habia antes en cuentas_dat
			for(i=0; i<posiCuentas; i++)
				fwrite(&cuentas[i], sizeof( Cuenta ), 1, cuentas_dat);
			fclose(cuentas_dat);

			return 1;
		}
	}
	if(bandera == 0){
		printf("\nNo se pudo realizar el retiro, el ID de cuenta no existe\n");
		return 0;
	}
	return -8;//Seria un error el -8
}


int transferencia (Transaccion transacciones[MAX], int posTransa, Transaccion *apTransa[]){
	Transaccion *arrTransa = transacciones;	//Declarar puntero local
	int auxID = posTransa + 1;
	char auxOperacion[15];
	int cuentaOrigen;
	int cuentaDestino;
	int auxMonto;
	int dia, mes, ano;

	int i=0, bandera = 0;
	Cuenta *apunArr = cuentas;

	printf("\nPara hacer la transferencia, introduzca su ID de cuenta: ");
	scanf("%d", &cuentaOrigen);

	printf("\nPara hacer la transferencia, la cuenta de destino: ");
	scanf("%d", &cuentaDestino);
	int j;
	for(i=0; i < MAX; i++)
		for(j = 0; j < MAX; j++)
			if ( ((apunArr + i)->id_cuenta == cuentaOrigen) && (apunArr + j)->id_cuenta == cuentaDestino)
			{
				printf("Su ID de Transaccion es --- %d --- \n", auxID);

				printf("Dame el monto a transferir:\n");
				scanf("%d", &auxMonto);

				while((apunArr + i)->saldo < auxMonto){
					printf("No tiene fondos, dame el monto:\n");
					scanf("%d", &auxMonto);
				}

				(apunArr + i)->saldo = (apunArr + i)->saldo - auxMonto;	//TRANSFERENCIA
				(apunArr + j)->saldo = (apunArr + j)->saldo + auxMonto;

				setbuf(stdin, 0);
				printf("Dame la fecha de la transaccion dd/mm/aa:\n");
				scanf("%d %d %d", &dia, &mes, &ano);

				(arrTransa + posTransa)->id_transaccion = auxID;

				strcpy(((arrTransa + posTransa)->operacion),"");
				strcpy( auxOperacion , "Retiro");
				strcpy( ((arrTransa + posTransa)->operacion), auxOperacion );

				(arrTransa + posTransa)->cuenta_origen = cuentaOrigen;
				(arrTransa + posTransa)->cuenta_destino = 0;
				(arrTransa + posTransa)->monto = auxMonto;

				(arrTransa + posTransa)->fch_transaccion.dia = dia;
				(arrTransa + posTransa)->fch_transaccion.mes = mes;
				(arrTransa + posTransa)->fch_transaccion.ano = ano;
				apTransa[posTransa] = (arrTransa + posTransa);	//Ya no es NULL el Arreglo del main
				bandera = 1;

				//Escribir en Archivo nuevas transacciones
				transacciones_dat = fopen(rutaTransacciones, "a+b");
				fwrite(&arrTransa[posTransa], sizeof( Transaccion ), 1, transacciones_dat);
				fclose(transacciones_dat);

				//Actualizar el archivo Cuentas con lo mas nuevo
				cuentas_dat = fopen(rutaCuentas, "wb");//Borrar lo que habia antes en cuentas_dat
				fclose(cuentas_dat);

				cuentas_dat = fopen(rutaCuentas, "a+b");//Borrar lo que habia antes en cuentas_dat
				for(i=0; i<posiCuentas; i++)
					fwrite(&cuentas[i], sizeof( Cuenta ), 1, cuentas_dat);
				fclose(cuentas_dat);

				return 1;
			}
	if(bandera == 0){
		printf("\nNo se pudo realizar la transferencia, el ID de cuenta no existe\n");
		return 0;
	}
	return -8;//Seria un error el -8
}


void imprimirCuentas(Cuenta cuentas[MAX], Cuenta *apCuentas[]){
	Cuenta *apunArr = cuentas;
	printf("\nLas cuentas registradas al momento son:");
	for(int i=0; i < MAX; i++){
		if ( (apCuentas[i] != NULL) && ((apunArr + i)->id_cuenta != -5) )//IMPRIMIR SOLO LOS QUE NO APUNTEN A NULL
		{
			printf("\n****Cuenta %d****", i+1);
			printf("\nEl ID de cuenta es: %d", (apunArr + i)->id_cuenta);
			printf("\nEl ID de cliente es: %d", (apunArr + i)->id_cliente);
			printf("\nEl saldo de la cuenta es: %d", (apunArr + i)->saldo);
			printf("\nSu fecha de Apertura de la cuenta es: %d / %d / %d \n", (apunArr + i)->apertura.dia, (apunArr + i)->apertura.mes, (apunArr + i)->apertura.ano);
		}
	}

}

void eliminarCuenta (Cuenta cuentas[MAX], Cuenta *apCuentas[], int valor){
	Cuenta *apunArr = cuentas;
	int idBorrar;
	int bandera = 0;
	int i;
	Cliente *arrApuntadores = clientes;

	if(valor == 1){	//Llamado desde el MENU
		printf("\nDame el ID de la Cuenta que desea borrar:");
		scanf("%d", &idBorrar);

		for(i= 0; i < MAX; i++){
			if ( (apunArr + i)->id_cuenta == idBorrar )
			{
				apCuentas[i] = NULL;
				(apunArr + i)->id_cuenta = -5; //BORRADO LÓGICO al ID = -5
				printf("Cuenta eliminada\n");
				bandera = 1;
			}
		}
		if(bandera == 0)
			printf("No existe ese no. de ID de cuenta\n");
	}
	else if (valor == 2){	//Llamado desde eliminar Cliente
		for(i= 0; i < MAX; i++){
			if ((arrApuntadores + i)->id == -5)
			{
				apCuentas[i] = NULL;
				(apunArr + i)->id_cuenta = -5; //BORRADO LÓGICO al ID = -5
				printf("Cuenta eliminada\n");
				bandera = 1;
			}
		}
		if(bandera == 0)
			printf("No existe ese no. de ID de cuenta\n");
	}
}

int altaCuenta (Cuenta cuentas[MAX], int posiCuentas, Cuenta *apCuentas[]){
	Cuenta *arrCuenta = cuentas;	//Declarar puntero local
	int auxID_cuenta = posiCuentas + 1;
	int auxID_cliente;
	int auxSaldo;
	int dia, mes, ano;

	printf("\nPara crear su cuenta, introduzca su ID de cliente: ");
	scanf("%d", &auxID_cliente);

	Cliente *apunArr = clientes;
	int i, bandera = 0;
	for(i=0; i < MAX; i++){
		if( (apunArr + i)->id == auxID_cliente )
		{
			printf("Su ID_cuenta es --- %d ---\n", auxID_cuenta);

			(arrCuenta)->id_cliente = (apunArr + i)->id;

			printf("Dame el saldo inicial:\n");
			scanf("%d", &auxSaldo);

			setbuf(stdin, 0);
			printf("Dame la fecha de apertura de la cuenta dd/mm/aa:\n");
			scanf("%d %d %d", &dia, &mes, &ano);

			(arrCuenta + posiCuentas)->id_cuenta = auxID_cuenta;
			(arrCuenta + posiCuentas)->id_cliente = auxID_cliente;
			(arrCuenta + posiCuentas)->saldo = auxSaldo;

			(arrCuenta + posiCuentas)->apertura.dia = dia;
			(arrCuenta + posiCuentas)->apertura.mes = mes;
			(arrCuenta + posiCuentas)->apertura.ano = ano;

			apCuentas[posiCuentas] = (arrCuenta + posiCuentas); //Ya no es NULL el Arreglo del main
			bandera = 1;
			cuentas_dat = fopen(rutaCuentas, "a+b");
			fwrite(&arrCuenta[posiCuentas], sizeof( Cuenta ), 1, cuentas_dat);
			fclose(cuentas_dat);
			return 1;
		}
	}
	if(bandera == 0)
	{
		printf("\nNo se pudo crear la cuenta, el ID de cliente no existe\n");
		return 0;
	}
	return -8;//Seria un error el -8
}

void buscarCuenta (Cuenta cuentas[MAX], Cuenta *apCuentas[]){
	Cuenta *apunArr = cuentas;
	int ID_cuenta; //Para buscar por ID
	printf("\nBuscar por ID_Cuenta: \n");
	scanf("%d", &ID_cuenta);

	int bandera = 0;

	for(int i=0; i < MAX; i++){
		if( ((apunArr + i)->id_cuenta == ID_cuenta) && (apCuentas[i] != NULL) )
		{
			printf("\n****Cuenta %d****", i+1);
			printf("\nEl id_cuenta es: %d", (apunArr + i)->id_cuenta);
			printf("\nEl id_cliente es: %d", (apunArr + i)->id_cliente);
			printf("\nEl saldo de la cuenta es: %d", (apunArr + i)->saldo);
			printf("\nSu fecha de Apertura de la cuenta es: %d / %d / %d \n", (apunArr + i)->apertura.dia, (apunArr + i)->apertura.mes, (apunArr + i)->apertura.ano);
			bandera = 1;
		}
	}

	if(ID_cuenta != 0)
	{
		if(bandera == 0)
			printf("\nNo se encontro ningun cliente en su búsqueda\n");
	}
}


void buscarCliente (Cliente clientes[MAX], Cliente *arrApuntadores[]){
	Cliente *apunArr = clientes;
	int ID=0; //Para buscar por ID
	printf("\nBuscar por ID: \n");
	scanf("%d", &ID);

	int bandera = 0;

	for(int i=0; i < MAX; i++){
		if( ((apunArr + i)->id == ID) && (arrApuntadores[i] != NULL) )
		{
			printf("\n****Cliente %d****", i+1);
			printf("\nEl ID es: %d", (apunArr + i)->id);
			printf("\nEl nombre del cliente es: %s", (*(apunArr + i)).nombre);
			printf("\nEl apellido Paterno del cliente es: %s", (*(apunArr + i)).paterno);
			printf("\nEl apellido Materno del cliente es: %s", (*(apunArr + i)).materno);
			printf("\nSu fecha de Nacimiento es: %d / %d / %d \n", (apunArr + i)->nacimiento.dia, (apunArr + i)->nacimiento.mes, (apunArr + i)->nacimiento.ano);
			bandera = 1;
		}
	}

	if(ID != 0)
	{
		if(bandera == 0)
			printf("\nNo se encontro ningun cliente en su búsqueda\n");
	}


}

void altaCliente (Cliente clientes[MAX], int posicion, Cliente *arrApuntadores[]){
	Cliente *arrCliente = clientes;	//Declarar puntero local
	int auxID = posicion + 1;
	char auxNombre[20];
	char auxMaterno[25];
	char auxPaterno[25];
	int dia, mes, ano;

	printf("Su ID de cliente es --- %d --- \n", auxID);

	setbuf(stdin, 0);
	printf("Dame el nombre:\n");
	gets(auxNombre);

	setbuf(stdin, 0);
	printf("Dame el apellido paterno:\n");
	gets(auxPaterno);

	setbuf(stdin, 0);
	printf("Dame el apellido materno:\n");
	gets(auxMaterno);

	setbuf(stdin, 0);
	printf("Dame la fecha de nacimiento dd/mm/aa:\n");
	scanf("%d %d %d", &dia, &mes, &ano);


	(arrCliente + posicion)->id = auxID;
	strcpy(((arrCliente + posicion)->nombre),"");
	strcpy( ((arrCliente + posicion)->nombre), auxNombre );

	strcpy(((arrCliente + posicion)->paterno),"");
	strcpy( ((arrCliente + posicion)->paterno), auxPaterno );

	strcpy(((arrCliente + posicion)->materno),"");
	strcpy( ((arrCliente + posicion)->materno), auxMaterno );


	(arrCliente + posicion)->nacimiento.dia = dia;
	(arrCliente + posicion)->nacimiento.mes = mes;
	(arrCliente + posicion)->nacimiento.ano = ano;

	arrApuntadores[posicion] = (arrCliente + posicion);	//Ya no es NULL el Arreglo del main

	clientes_dat = fopen(rutaClientes, "a+b");
	fwrite(&arrCliente[posicion], sizeof( Cliente ), 1, clientes_dat);
	fclose(clientes_dat);

}

void eliminarCliente (Cliente clientes[MAX], Cliente *arrApuntadores[]){
	Cliente *apunArr = clientes;
	int idBorrar;
	int bandera = 0;
	printf("\nDame el ID del Cliente que desea borrar:");
	scanf("%d", &idBorrar);

	for(int i=0; i < MAX; i++){
		if ((apunArr + i)->id == idBorrar)
		{
			arrApuntadores[i] = NULL;	//Por que no lo pude poner:	 (arrApuntadores + i)  =  NULL;
			(apunArr + i)->id = -5; //BORRADO LÓGICO al ID = -5
			printf("Cliente eliminado\n");
			bandera = 1;
			eliminarCuenta (cuentas, apCuentas, 2);
		}
	}
	if(bandera == 0)
		printf("No existe ese no. de ID\n");



//	// A CONTINUACION PARA LEER UN ARCHIVO, modificar si es necesario
//	clientes_dat = fopen(rutaClientes,"r+b");
//	if (clientes_dat==NULL){
//		printf("Error al abrir archivo clientes_dat\n");
//	}
//	else{//Se abrió el archivo para leer y escribir
//		rewind(clientes_dat);
//		Cliente arrLeerClientes[250];
//		int i = 0;
//		int borradoLogico = -5;
//		fread(&arrLeerClientes[i], sizeof(Cliente), 1, clientes_dat);
////Cliente *apunCliente = arrLeerClientes;
//		while( ! feof(clientes_dat) )
//		{
//			if( (apunArr + i)->id == idBorrar){
//				int retorno = fseek(clientes_dat, 0, SEEK_CUR);
//
//				if(retorno == 0){
//					fwrite(&borradoLogico, sizeof( int ), 1, clientes_dat);
//					printf("El cursor se movió correctamente y ya borramos");
//				}
//				i++;//Leer la siguiente
//				fread(&arrLeerClientes[i], sizeof(Cliente), 1, clientes_dat);
//			}
//		}
//		fclose(clientes_dat);
//	}



}

void imprimirClientes(Cliente clientes[MAX], Cliente *arrApuntadores[]){
	Cliente *apunArr = clientes;
	printf("\nLos clientes registrados al momento son:");
	for(int i=0; i < MAX; i++){
		if ( (arrApuntadores[i] != NULL) && ((apunArr + i)->id != -5) )//IMPRIMIR SOLO LOS QUE NO APUNTEN A NULL
		{
			printf("\n****Cliente %d****", i+1);
			printf("\nEl ID es: %d", (apunArr + i)->id);
			printf("\nEl nombre del cliente es: %s", (*(apunArr + i)).nombre);
			printf("\nEl apellido Paterno del cliente es: %s", (*(apunArr + i)).paterno);
			printf("\nEl apellido Materno del cliente es: %s", (*(apunArr + i)).materno);
			printf("\nSu fecha de Nacimiento es: %d / %d / %d \n", (apunArr + i)->nacimiento.dia, (apunArr + i)->nacimiento.mes, (apunArr + i)->nacimiento.ano);
		}
	}

}



void submenuCliente(){
	int opcion;
	do{
		printf("\n\t\t  \t -> Submenu CLIENTES...");
		printf("\n\t\t1. Nuevo cliente");
		printf("\n\t\t2. Buscar cliente");
		printf("\n\t\t3. Eliminar cliente");
		printf("\n\t\t4. Imprimir clientes");
		printf("\n\t\t5. Salir");

		printf("\n\t\tOpción CLIENTES, escoja (1-5) un número válido:");
		scanf("%d", &opcion);

		switch(opcion)
			{
				case 1: altaCliente (clientes, posicion, arrApuntadores);
        	   	   	    posicion++;
        	   	   	    break;

				case 2: buscarCliente (clientes, arrApuntadores);
						break;

				case 3:	eliminarCliente (clientes, arrApuntadores);
						break;

				case 4: imprimirClientes (clientes, arrApuntadores);
						break;

				default:
					if(opcion != 5)
						printf( "\n\t\t  -------Número NO válido, escoja de nuevo\n");
			}

	}while(opcion != 5);
}

void submenuCuentas(){
	int valor, opcion;
	do{
		printf("\n\t\t  \t -> Submenu CUENTAS...");
		printf("\n\t\t1. Nueva cuenta");
		printf("\n\t\t2. Buscar cuenta");
		printf("\n\t\t3. Eliminar cuenta");
		printf("\n\t\t4. Imprimir cuentas");
		printf("\n\t\t5. Salir");

		printf("\n\t\tOpción CUENTAS, escoja (1-5) un número válido:");
		scanf("%d", &opcion);

		switch(opcion)
			{
				case 1: valor = altaCuenta (cuentas, posiCuentas, apCuentas);
						if(valor == 1){
							posiCuentas++;
						}
						break;

				case 2: buscarCuenta (cuentas , apCuentas);
						break;

				case 3: eliminarCuenta (cuentas, apCuentas, 1);
						break;

				case 4: imprimirCuentas(cuentas, apCuentas);
						break;

				default:
					if(opcion != 5)
						printf( "\n\t\t  -------Número NO válido, escoja de nuevo\n");
			}

	}while(opcion != 5);
}

void submenuTransacciones(){
	int opcion, valor;
	do{
		printf("\n\t\t  \t -> Submenu TRANSACCIONES...");
		printf("\n\t\t1. Depósito");
		printf("\n\t\t2. Retiro");
		printf("\n\t\t3. Transferencia");
		printf("\n\t\t4. Salir");

		printf("\n\t\tOpción TRANSACCIONES, escoja (1-4) un número válido:");
		scanf("%d", &opcion);

		switch(opcion)
			{
				case 1: valor = deposito (transacciones, posTransa, apTransa);
								if (valor == 1){
									posTransa++;
								}
								break;

				case 2: valor = retiro (transacciones, posTransa, apTransa);
								if(valor == 1){
									posTransa++;
								}
								break;
				case 3: valor = transferencia (transacciones, posTransa, apTransa);
								if(valor == 1){
									posTransa++;
								}
								break;
				default:
					if(opcion != 4)
						printf( "\n\t\t  -------Número NO válido, escoja de nuevo\n");
			}

	}while(opcion != 4);
}


void ArchivosBinarios (){
		char rutaAcceso[35], verificarRuta[35], rutaBase[35];
		strcpy(verificarRuta , "");
		mydb_sys = fopen("mydb.sys", "rt");//Validar: si no existe retorna NULL
		//clientes_dat = fopen("Carpeta1\\Yomero.dat", "w"); //Asi se crea correctamente en una carpeta dentro del directorio RAÍZ


		if(mydb_sys == NULL){ //Si no existe haz...
			printf("Introduce Ruta de acceso (Relativa)... Ejemplo: Carpeta1\\\\ \n");
			mydb_sys = fopen("mydb.sys", "wt");//modo "w" : abrir un archivo para escritura, se crea si no existe o se sobreescribe si existe.
			scanf("%s", rutaAcceso);
			fputs( rutaAcceso ,  mydb_sys);
			fclose(mydb_sys);
			mydb_sys = fopen("mydb.sys", "rt");
			leerArchivo(mydb_sys, verificarRuta);
			fclose(mydb_sys);
			printf("\nLinea del IF: %s", verificarRuta);

		}
		else{	//Si ya existe o NO entonces verificar que la ruta este bien...
			fclose(mydb_sys);//Cerrar el de lectura
			mydb_sys = fopen("mydb.sys", "rt");
			leerArchivo(mydb_sys, verificarRuta);
		    fclose(mydb_sys);
		    printf("\nLinea del ELSE: %s", verificarRuta);
		}

		int valor = strcmp(verificarRuta, "Carpeta1\\\\");
		printf("\n comparacion:%d", valor);

		while(valor != 0)
		{
			printf("\n\nError... (Ruta de acceso INCORRECTA)\n");
			printf("Introduce Ruta de acceso (Relativa)... Ejemplo: Carpeta1\\\\ \n");
			scanf("%s", rutaAcceso);
			mydb_sys = fopen("mydb.sys", "wt");//modo "w" : abrir un archivo para escritura, se crea si no existe o se sobreescribe si existe.
			fputs( rutaAcceso ,  mydb_sys);
			fclose(mydb_sys);
			mydb_sys = fopen("mydb.sys", "rt");
			leerArchivo(mydb_sys, verificarRuta);
			fclose(mydb_sys);
			printf("\nLinea del WHILE: %s", verificarRuta);
			valor = strcmp(verificarRuta, "Carpeta1\\\\");
		}
		//leer el archivo mydb.sys y recuperar la ruta de Acceso
		printf("\nverificarRuta: %s", verificarRuta);
		printf("\nrutaAcceso: %s", rutaAcceso);
		printf("\nrutaBase: %s", rutaBase);

		strcpy(rutaBase, verificarRuta);	//verificarRuta llega BIEN y la respaldamos

		strcpy(rutaClientes, rutaBase);
		strcat(rutaClientes, "clientes.dat"); //Nombre de Primer Archivo a crear
		clientes_dat = fopen(rutaClientes, "a+b"); //Validar que la ruta este correcta

		strcpy(rutaCuentas, rutaBase);
		strcat(rutaCuentas, "cuentas.dat"); //Nombre de 2do Archivo a crear
		cuentas_dat = fopen(rutaCuentas, "a+b");

		strcpy(rutaTransacciones, rutaBase);
		strcat(rutaTransacciones, "transacciones.dat"); //Nombre de 3er Archivo a crear
		transacciones_dat = fopen(rutaTransacciones, "a+b");

		fclose(clientes_dat);
		fclose(cuentas_dat);
		fclose(transacciones_dat);
}

void leerArchivo (FILE *archivo, char arr[35]){
	char letra;
	int i = 0;
	printf("Funcion leerArchivo: ");
	while ((letra = fgetc(archivo)) != EOF) {
		arr[i] = letra;
		printf( "%c",letra );
		i++;
	}
	arr[i] = '\0';
}




