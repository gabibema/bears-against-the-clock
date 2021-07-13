#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 

#include "test_de_personalidad.h"
#include "osos_contra_reloj.h"
#include "graficos.h"
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


/*
 * PRE: -
 * POS: Pide una jugada al usuario hasta que sea válida
 */ 
void pedir_jugada(char* jugada){

	mostrar_opciones();

  	printf("Ingrese un carácter válido para realizar la jugada: ");
	scanf(" %c", jugada);

	while(!es_jugada_valida(*jugada)){
		printf("ERROR! Ingrese un carácter válido para realizar la jugada: ");
		scanf(" %c",jugada);
	}
}


int main(){
	juego_t juego;
	char personalidad_detectada = '0';
	char ultima_jugada = '0';

	srand ((unsigned)time(NULL));

	mostrar_animacion_cargando();
    test_de_personalidad(&personalidad_detectada);
	system("clear");
	
    inicializar_juego(&juego, personalidad_detectada);
	iniciar_cronometro();

	do{
		mostrar_juego(juego);
		pedir_jugada(&(ultima_jugada));
		realizar_jugada(&juego, ultima_jugada);

	} while (estado_juego(juego)!=JUEGO_TERMINADO);

	system("clear");

	if ( (tiempo_actual() + juego.personaje.tiempo_perdido <= TIEMPO_TOTAL)){
		printf("\tFELICIDADES GANASTE!!!");
	} else{
		printf("\tCHLOE SE QUEDÓ SIN SU INHALADOR :(");
	}
	return 0;
}
