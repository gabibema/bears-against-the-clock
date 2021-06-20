#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 

#include "test_de_personalidad.h"
#include "osos_contra_reloj.h"
#include "utiles.h"

const int JUEGO_TERMINADO = -1;
const double TIEMPO_TOTAL = 120.0;

#define MOVERSE_ARRIBA 'W'
#define MOVERSE_IZQUIERDA 'A'
#define MOVERSE_DERECHA 'D'
#define MOVERSE_ABAJO 'S'
#define ENCENDER_LINTERNA 'L'
#define ENCENDER_VELA 'V'
#define ENCENDER_BENGALA 'E'
#define TIEMPO_RESTANTE 'T'


bool es_jugada_valida (char jugada){
	return ( (jugada==MOVERSE_ARRIBA)|| (jugada==MOVERSE_ABAJO)||(jugada==MOVERSE_IZQUIERDA)||(jugada==MOVERSE_DERECHA)||(jugada==ENCENDER_LINTERNA)||(jugada==ENCENDER_VELA)||(jugada==ENCENDER_BENGALA)||(jugada==TIEMPO_RESTANTE));
}


void pedir_jugada(char* jugada){
	printf("Ingresa \n \t*-> W: Para moverte arriba.\n \t*-> A: Para moverte a la izquierda \n\t*-> S: Para moverte abajo. \n \t*-> D: Para moverte a la derecha. \n \t*-> L: Para encender una linterna. \n \t*-> V: Para encender una vela.  \n \t*-> E: Para encender la bengala. \n \t*-> T: Para ver el tiempo restante.  \n");
  	printf("Ingrese un carácter válido para realizar la jugada: ");
	scanf(" %c", jugada);

	while(!es_jugada_valida(*jugada)){
		printf("ERROR! Ingrese un carácter válido para realizar la jugada: ");
		scanf(" %c",jugada);
	}
}


bool chloe_fue_encontrada (juego_t juego){
	return ( (juego.personaje.posicion.col == juego.amiga_chloe.col) && ( juego.personaje.posicion.fil == juego.amiga_chloe.fil) );
}

int main(){
	juego_t juego;
	char personalidad_detectada = '0';
	char ultima_jugada = '0';

	srand ((unsigned)time(NULL));

    test_de_personalidad(&personalidad_detectada);
	//system("clear");
	
    inicializar_juego(&juego, personalidad_detectada);

	mostrar_juego(juego);
	iniciar_cronometro();

	do{
		pedir_jugada(&(ultima_jugada));
		
		//system("clear");
		realizar_jugada(&juego, ultima_jugada);
		printf("Cantidad de obstaculos: %i\n", juego.cantidad_obstaculos);

		mostrar_juego(juego);

	} while (estado_juego(juego)!=JUEGO_TERMINADO);

	system("clear");

	if ( (tiempo_actual() + juego.personaje.tiempo_perdido >= TIEMPO_TOTAL) && (chloe_fue_encontrada(juego)) ){
		printf("\tFELICIDADES GANASTE!!!");
	} else{
		printf("\tCHLOE SE QUEDÓ SIN SU INHALADOR :(");
	}
	return 0;
}
