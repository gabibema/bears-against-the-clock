#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>

#include "test_de_personalidad.h"
#include "osos_contra_reloj.h"
#include "graficos.h"
#include "utiles.h"

#define MAX_FILAS 20
#define MAX_COLUMNAS 30

const int FILA_MINIMA = 0;
const int COLUMNA_MINIMA = 0;


const char ARBOL= 'A';
const char PIEDRA= 'R';
const char KOALA= 'K';
const char LINTERNA= 'L';
#define VELA 'V'
#define BENGALA 'E'
#define PILA 'B'

const char POLAR= 'I';
const char PARDO= 'G';
const char PANDA= 'P';
const char CHLOE= 'C';

const int MAX_ARBOLES_INICIO = 350;
const int MAX_PIEDRAS_INICIO = 80;
const int MAX_KOALAS_INICIO = 1;

const int MAX_PILAS_INICIO = 30;
const int MAX_VELAS_INICIO = 30;
const int MAX_BENGALAS_INICIO = 10;

const int MOVIMIENTOS_PILAS =  5;

const int INDICE_LINTERNA = 0;
const int MOVIMIENTOS_LINTERNA_EXPERTO = 15;
const int MOVIMIENTOS_LINTERNA_NORMAL = 10;

const int CANTIDAD_VELAS_YOGA = 6;
const int CANTIDAD_VELAS_NORMAL = 4; 
const int MOVIMIENTOS_VELAS = 5;

const int CANTIDAD_BENGALAS_FIESTA = 2;
const int CANTIDAD_BENGALAS_NORMAL = 0;
const int DURACION_BENGALAS = 3;
const int MAX_RANGO_BENGALA = 2;
const int KOALAS_POR_LINTERNA = 1;

const char VACIO = '-';
const int COLUMNA_INICIAL = 0;

static const int JUEGO_CONTINUA = 0;
static const int JUEGO_TERMINADO = -1;

static const double TIEMPO_TOTAL = 120.0;

const double TIEMPO_PIEDRA = 2.0;
const double TIEMPO_EVADIR_PIEDRA = 0.0;
const double TIEMPO_TREPAR = 1.0;
const double TIEMPO_TREPAR_RAPIDO = 0.5;
const double TIEMPO_GPS = 30.0;

const bool VISIBILIDAD_DEFECTO = false;

const int SIN_ELEMENTOS_EN_USO = -1;
const int NO_HAY_ELEMENTO = -2;
const int MIN_MOVIMIENTOS = 0;

#define MOVERSE_ARRIBA 'W'
#define MOVERSE_IZQUIERDA 'A'
#define MOVERSE_DERECHA 'D'
#define MOVERSE_ABAJO 'S'
#define ENCENDER_LINTERNA 'L'
#define ENCENDER_VELA 'V'
#define ENCENDER_BENGALA 'E'
#define TIEMPO_RESTANTE 'T'

#define SEPARADOR_1_INICIO "\t\t\t╔══════════════════════════════════════════╗\n"
#define SEPARADOR_1_FIN "\t\t\t╚══════════════════════════════════════════╝\n"
#define SEPARADOR_MENSAJE "〔-▲-〕"


void inicializar_juego(juego_t* juego, char tipo_personaje);

void inicializar_personaje(personaje_t* personaje, char tipo_personaje);
coordenada_t posicion_inicial_personaje();
void obtener_kit_inicial_personaje(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos,char tipo_personaje);
void generar_kit_oso (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int movimientos_linterna, int cantidad_velas, int cantidad_bengalas);

void inicializar_chloe (bool* chloe_visible, coordenada_t* amiga_chloe, coordenada_t posicion_personaje);
coordenada_t posicion_aleatoria();
bool es_misma_posicion(coordenada_t posicion_1, coordenada_t posicion_2);

void agregar_obstaculos (juego_t* juego, int* cantidad_obstaculos , int cantidad, char tipo);
coordenada_t posicion_aleatoria_libre(juego_t juego);
bool esta_posicion_libre(juego_t juego, coordenada_t posicion);

void agregar_recolectables (juego_t* juego, int* cantidad_herramientas ,int cantidad, char tipo);

void mostrar_juego(juego_t juego);
void inicializar_matriz (char matriz[MAX_FILAS][MAX_COLUMNAS]);
void cargar_posiciones_visibles (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego);
bool puede_usar_gps(char tipo, double tiempo_perdido);
void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]);

void realizar_jugada(juego_t* juego, char jugada);

void mover_hacia(juego_t* juego, coordenada_t posicion, char direccion);
coordenada_t posicion_hacia(coordenada_t posicion, char direccion);
bool se_puede_mover(coordenada_t posicion);

void chocar_con(juego_t* juego, char tipo_chocado, coordenada_t posicion_personaje);

char tipo_elemento_chocado (juego_t juego, coordenada_t posicion);
int indice_herramienta (elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int cantidad_herramientas, coordenada_t posicion)
;
bool es_obstaculo (char tipo_elemento);
void aplicar_contratiempo (juego_t* juego, char contratiempo);
double tiempo_piedra(char tipo_personaje);
double tiempo_arbol(char tipo_personaje);
void tropezar_con_sekoalaz (juego_t* juego);
bool esta_columna_ocupada(juego_t juego, int columna);

bool es_herramienta(char tipo_elemento);
void agregar_en_mochila (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_herramientas , char recolectable);
void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice);

void intentar_iluminar_con(juego_t* juego, char herramienta, int indice_herramienta);
void ocultar_todo (juego_t* juego);

void iluminar_con (juego_t* juego, char herramienta);

void iluminar_hacia_arriba(juego_t* juego);
bool esta_arriba_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);

void iluminar_hacia_abajo(juego_t* juego);
bool esta_abajo_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);

void iluminar_hacia_izquierda(juego_t* juego);
bool esta_izquierda_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);

void iluminar_hacia_derecha(juego_t* juego);
bool esta_derecha_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);

void iluminar_alrededor(juego_t* juego);
bool esta_alrededor(coordenada_t posicion_personaje, coordenada_t posicion_elegida);

int distancia_mahattan (coordenada_t posicion1, coordenada_t posicion2);
bool estan_en_diagonal(coordenada_t posicion1, coordenada_t posicion2);

void iluminar_con_bengala(juego_t* juego);

void usar_herramienta(juego_t* juego, char herramienta);
bool hay_bengala_activa (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int elemento_en_uso);
int obtener_posicion_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char elemento, int cantidad_herramientas);
bool es_herramienta_buscada( elemento_mochila_t elemento, char buscado);
void encender_linterna(juego_t* juego, char ultimo_movimiento, int indice);
void encender_vela(juego_t* juego, int indice);
void encender_bengala(juego_t* juego, int indice);

int estado_juego(juego_t juego);
bool chloe_fue_encontrada(coordenada_t posicion_personaje, coordenada_t amiga_chloe);

bool es_jugada_valida (char jugada);


void inicializar_juego(juego_t* juego, char tipo_personaje){

	juego->cantidad_obstaculos = 0;
	juego->cantidad_herramientas = 0;
	
	inicializar_personaje(&(juego->personaje), tipo_personaje);
    inicializar_chloe(&(juego->chloe_visible), &(juego->amiga_chloe), juego->personaje.posicion);

	agregar_obstaculos(juego, &(juego->cantidad_obstaculos), MAX_ARBOLES_INICIO, ARBOL);
	agregar_obstaculos(juego, &(juego->cantidad_obstaculos), MAX_PIEDRAS_INICIO, PIEDRA);
	agregar_obstaculos(juego, &(juego->cantidad_obstaculos), MAX_KOALAS_INICIO, KOALA);


	agregar_recolectables(juego, &(juego->cantidad_herramientas), MAX_PILAS_INICIO, PILA);
	agregar_recolectables(juego, &(juego->cantidad_herramientas), MAX_VELAS_INICIO, VELA);
	agregar_recolectables(juego, &(juego->cantidad_herramientas), MAX_BENGALAS_INICIO, BENGALA);
}


/*
 * PRE: tipo_personaje sea PANDA, PARDO o POLAR
 * POS: Todos los campos del personaje serán válidos
 */ 
void inicializar_personaje(personaje_t* personaje, char tipo_personaje){

	personaje->tipo = tipo_personaje;

	personaje->posicion = posicion_inicial_personaje();
	personaje->ultimo_movimiento = MOVERSE_DERECHA;

	personaje->cantidad_elementos = 0;
	obtener_kit_inicial_personaje(personaje->mochila, &(personaje->cantidad_elementos), tipo_personaje);
	personaje->elemento_en_uso = SIN_ELEMENTOS_EN_USO;
	personaje->tiempo_perdido = 0.0;
}


/*
 * PRE: -
 * POS: Devuelve una coordenada aleatoria teniendo en cuenta la COLUMNA_INICIAL del personaje
 */ 
coordenada_t posicion_inicial_personaje(){
	
	coordenada_t posicion;

    posicion.col=COLUMNA_INICIAL;
    posicion.fil = rand()%MAX_FILAS;

	return posicion;
}


/*
 * PRE: cantidad de elementos por referencia sea 0 o mayor, tipo_personaje sea PARDO, PANDA o POLAR
 * POS: agrega en la mochila las herramientas correspondientes a cada oso
 */ 
void obtener_kit_inicial_personaje(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos,char tipo_personaje){

	if( tipo_personaje == PARDO){
		generar_kit_oso(mochila, cantidad_elementos, MOVIMIENTOS_LINTERNA_EXPERTO, CANTIDAD_VELAS_NORMAL, CANTIDAD_BENGALAS_NORMAL);

	} else if ( tipo_personaje == POLAR ){
		generar_kit_oso(mochila, cantidad_elementos, MOVIMIENTOS_LINTERNA_NORMAL, CANTIDAD_VELAS_YOGA, CANTIDAD_BENGALAS_NORMAL);

	} else {
		generar_kit_oso(mochila, cantidad_elementos, MOVIMIENTOS_LINTERNA_NORMAL, CANTIDAD_VELAS_NORMAL, CANTIDAD_BENGALAS_FIESTA);

	}
}  


/*
 * PRE: El tope sea 0 o mayor, movimientos linterna sea 0 o mayor, las cantidades sea 0 o mayor.
 * POS: Agrega las herramientas en la mochila
 */ 
void generar_kit_oso (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int movimientos_linterna, int cantidad_velas, int cantidad_bengalas){
	
	int i;

	mochila[INDICE_LINTERNA].tipo = LINTERNA;
	mochila[INDICE_LINTERNA].movimientos_restantes = movimientos_linterna;

	(*cantidad_elementos)++;


	for ( i =  0; i < cantidad_velas; i++ ){
		
		mochila[ (*cantidad_elementos) ].tipo = VELA;
		mochila[ (*cantidad_elementos) ].movimientos_restantes = MOVIMIENTOS_VELAS;	
		(*cantidad_elementos)++;	
	}


	for ( i =  0; i < cantidad_bengalas; i++ ){
		 
		mochila[ (*cantidad_elementos) ].tipo = BENGALA;	
		mochila[ (*cantidad_elementos) ].movimientos_restantes = DURACION_BENGALAS;
		(*cantidad_elementos)++;	
	}
}


/*
 * PRE: La posicion del personaje sea válida
 * POS: Chloe tendrá una posición válida en el mapa y tendrá la VISIBILIDAD_DEFECTO
 */ 
void inicializar_chloe (bool* chloe_visible, coordenada_t* amiga_chloe, coordenada_t posicion_personaje){

	do{ 
		(*amiga_chloe) = posicion_aleatoria();

	}  while (es_misma_posicion( (*amiga_chloe), posicion_personaje));

	(*chloe_visible) = VISIBILIDAD_DEFECTO;

}


/*
 * PRE: -
 * POS: Devuelve una posicion random dentro de los límites del mapa
 */ 
coordenada_t posicion_aleatoria(){
	coordenada_t posicion;
	
	posicion.fil= rand()%MAX_FILAS;
	posicion.col= rand()%MAX_COLUMNAS;

	return posicion;
}


/*
 * PRE: -
 * POS: Devuelve true si las dos coordenadas son iguales
 */ 
bool es_misma_posicion(coordenada_t posicion_1, coordenada_t posicion_2){
	
	return ((posicion_1.fil == posicion_2.fil) && (posicion_1.col == posicion_2.col));
	
}


/*
 * PRE: El tope sea 0 o mayor, la cantidad sea 0 o mayor, el tipo del obstáculo sea ARBOL, PIEDRA o KOALA
 * POS: Agrega la cantidad de obstaculos en el juego
 */ 
void agregar_obstaculos (juego_t* juego, int* cantidad_obstaculos , int cantidad, char tipo){
	
	coordenada_t posicion;
	int i;



	for ( i = 0; i <  cantidad; i++){

		juego->obstaculos[(*cantidad_obstaculos)].tipo = tipo; 

		posicion = posicion_aleatoria_libre(*juego);

		juego->obstaculos[(*cantidad_obstaculos)].posicion = posicion;
		juego->obstaculos[(*cantidad_obstaculos)].visible = VISIBILIDAD_DEFECTO;
		
		(*cantidad_obstaculos)++;	

	}
}


/*
 * PRE: Las coordenadas del personaje, Chloe, obstáculos y herramientas existentes sean válidas
 * POS: Devuelve una poisición válida que no se superpone con las existentes
 */ 
coordenada_t posicion_aleatoria_libre(juego_t juego){

	coordenada_t posicion;
	
	do{
		posicion = posicion_aleatoria();

	} while(!esta_posicion_libre(juego, posicion));

	return posicion;
}


/*
 * PRE: Las coordenadas del personaje, Chloe, obstáculos y herramientas existentes sean válidas
 * POS: Devuelve true si la posición no se superpone con ninguna del juego, false en caso contrario
 */ 
bool esta_posicion_libre(juego_t juego, coordenada_t posicion){

	bool esta_libre = true;
	int i = 0, j = 0;

	if (es_misma_posicion(juego.personaje.posicion, posicion)){
		esta_libre = false;

	} else if (es_misma_posicion( juego.amiga_chloe, posicion) ){
		esta_libre = false;

	} else {

		while(esta_libre && i < juego.cantidad_obstaculos){
			
			if(es_misma_posicion(juego.obstaculos[i].posicion, posicion)){
				esta_libre=false;
			}
			i++;
		}

		while(esta_libre && j < juego.cantidad_herramientas){

			if(es_misma_posicion(juego.herramientas[j].posicion, posicion)){
				esta_libre=false;
			}
			j++;
		}
	}

	return esta_libre;
}


/*
 * PRE: El tope sea 0 o mayor, la cantidad sea 0 o mayor, el tipo de recolectable sea VELA, PILA o BENGALA
 * POS: Agrega la cantidad de recolectables en el juego
 */ 
void agregar_recolectables (juego_t* juego, int* cantidad_herramientas ,int cantidad, char tipo){
	
	coordenada_t posicion;

	int i;

	for ( i = 0; i < cantidad; i++){

		posicion = posicion_aleatoria_libre(*juego);

		juego->herramientas[(*cantidad_herramientas)].visible = VISIBILIDAD_DEFECTO;
		juego->herramientas[(*cantidad_herramientas)].posicion = posicion;	
		juego->herramientas[(*cantidad_herramientas)].tipo = tipo; 

		(*cantidad_herramientas)++;
	}	
}


/*
 * Mostrará el juego por pantalla.
 * Se recomienda mostrar todo lo que sea de utilidad para el jugador.
 */
void mostrar_juego(juego_t juego){
	char tablero[MAX_FILAS][MAX_COLUMNAS];

	inicializar_matriz(tablero);
	cargar_posiciones_visibles(tablero, juego);

	mostrar_datos(juego.cantidad_obstaculos, juego.cantidad_herramientas, juego.personaje.cantidad_elementos);
	mostrar_matriz(tablero);

}


/*
 * PRE: -
 * POS: Llena toda la matriz de VACIO
 */ 
void inicializar_matriz (char matriz[MAX_FILAS][MAX_COLUMNAS]){
	int i, j;

	for ( i = 0; i < MAX_FILAS; i++){
		for ( j = 0; j < MAX_COLUMNAS; j++){
			matriz[i][j] = VACIO;
		}
	}
}


/*
 * PRE: Las posición del personaje, Chloe, obstáculos y herramientas estén inicializadas
 * POS: Carga en la matriz cada elemento en su respectiva posición si es visible y al personaje
 */ 
void cargar_posiciones_visibles (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego){

	int i;

	
	if( (juego.chloe_visible)){
		tablero[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
	}

	for (i = 0; i< juego.cantidad_obstaculos; i++){
		if(juego.obstaculos[i].visible){
			tablero[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].tipo;
		}
	}	
	
	for (i = 0; i< juego.cantidad_herramientas; i++){
		if(juego.herramientas[i].visible){
			tablero[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;
		}
	}

	tablero[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

}


/*
 * PRE: -
 * POS: Devuelve true si el tipo es PANDA y tiempo perdido es mayor o igual a 30
 */ 
bool puede_usar_gps(char tipo, double tiempo_perdido){
	return ( (tipo == PANDA) && ( tiempo_perdido >= TIEMPO_GPS) );
}


void realizar_jugada(juego_t* juego, char jugada){
	
	double tiempo_sin_obstaculos = tiempo_actual();
	double tiempo = 0.0;


	switch (jugada){

		case MOVERSE_ARRIBA:

			mover_hacia(juego, juego->personaje.posicion, MOVERSE_ARRIBA);
			break;

		case MOVERSE_ABAJO:

			mover_hacia(juego, juego->personaje.posicion, MOVERSE_ABAJO);
			break;

		case MOVERSE_IZQUIERDA:

			mover_hacia(juego, juego->personaje.posicion, MOVERSE_IZQUIERDA);
			break;

		case MOVERSE_DERECHA:
		
			mover_hacia(juego, juego->personaje.posicion, MOVERSE_DERECHA);

			break;		

		case ENCENDER_LINTERNA:

			usar_herramienta(juego,LINTERNA);
			break;

		case ENCENDER_VELA:

			usar_herramienta(juego,VELA);
			break;

		case ENCENDER_BENGALA:

			usar_herramienta(juego, BENGALA);
			break;

		case TIEMPO_RESTANTE:

			tiempo = TIEMPO_TOTAL - (tiempo_sin_obstaculos + juego->personaje.tiempo_perdido);
			mostrar_tiempo(tiempo);
			break;
	
	}
}


/*
 * PRE: La dirección sea W,A,S,D
 * POS: Mueve al personaje si la posición está dentro de los límites del terreno y actualiza su último movimiento
 */ 
void mover_hacia(juego_t* juego, coordenada_t posicion, char direccion){

	int indice_en_uso = juego->personaje.elemento_en_uso;
	char tipo_chocado = '-';


	posicion = posicion_hacia(posicion, direccion);

	if(se_puede_mover(posicion)){ 
		
		juego->personaje.posicion = posicion;
		juego->personaje.ultimo_movimiento = direccion;

		if(!esta_posicion_libre(*juego, posicion)){
			
			tipo_chocado = tipo_elemento_chocado(*juego, posicion);

			printf("Tipo CHOCADO: %c", tipo_chocado);
			chocar_con(juego, tipo_chocado, posicion);	
		}
		

		if (tipo_chocado!=KOALA){
			juego->personaje.posicion = posicion;		
		}

		if (indice_en_uso != SIN_ELEMENTOS_EN_USO){
			intentar_iluminar_con(juego,juego->personaje.mochila[indice_en_uso].tipo, indice_en_uso);
		}
		mostrar_mensaje_usuario(MOVERSE, direccion);

	} else 
		mostrar_mensaje_usuario(MOVERSE,NADA);

	
}


/*
 * PRE: La direccion sea W, A, S, D
 * POS: Devuelve la nueva posición según la dirección
 */ 
coordenada_t posicion_hacia(coordenada_t posicion, char direccion){
	
	if (direccion == MOVERSE_ARRIBA){
		posicion.fil--;
	}else if (direccion == MOVERSE_ABAJO){
		posicion.fil++;
	}else if (direccion == MOVERSE_IZQUIERDA){
		posicion.col--;
	}else{
		posicion.col++;
	}

	return posicion;
}


/*
 * PRE: -
 * POS: Devuelve true si la posición está dentro de los límites del terreno, false en caso contrario
 */ 
bool se_puede_mover(coordenada_t posicion){
	return ( (( posicion.fil >= FILA_MINIMA )&&( posicion.fil < MAX_FILAS )) && (( posicion.col >= COLUMNA_MINIMA )&&( posicion.col < MAX_COLUMNAS )) );	
}


/*
 * PRE: Tipo chocado sea un obstáculo o una herramienta, la posicion del personaje sea válida y el juego esté inicializado
 * POS: Si el tipo es un obstáculo aplica su contratiempo, si es una herramienta la añade en la mochila
 */ 
void chocar_con(juego_t* juego, char tipo_chocado, coordenada_t posicion_personaje){

	int indice_chocado = 0;

	if (es_obstaculo(tipo_chocado)){
		aplicar_contratiempo(juego, tipo_chocado);

	} else if (es_herramienta(tipo_chocado)) {
		agregar_en_mochila(juego->personaje.mochila,&(juego->personaje.cantidad_elementos), tipo_chocado);
	
		indice_chocado = indice_herramienta(juego->herramientas, juego->cantidad_herramientas, posicion_personaje);

		//printf("Indice chocado: %i\n", indice_chocado);		
		//printf("Cantidad de obstaculos dps de chocado: %i\n", juego->cantidad_obstaculos);

		eliminar_herramienta(juego->herramientas, &(juego->cantidad_herramientas),indice_chocado);
		
		//printf("Cantidad de obstaculos dps de eliminar_herramienta: %i\n", juego->cantidad_obstaculos);		
	}
}


/*
 * PRE: El personaje esté encima de un elemento o Chloe
 * POS: Devuelve el tipo del elemento que coincide con la posición del personaje.
 */ 
char tipo_elemento_chocado (juego_t juego, coordenada_t posicion){

	bool chocado = false;
	
	int i = 0, j = 0;
	char tipo = '0';

	if (es_misma_posicion(juego.personaje.posicion, juego.amiga_chloe)){
		tipo = CHLOE;
		
	} else {

		while(!chocado && i<juego.cantidad_obstaculos){

			if(es_misma_posicion(juego.obstaculos[i].posicion, posicion)){

				tipo = juego.obstaculos[i].tipo;
				chocado = true;
			}
			i++;
		}

		while(!chocado && j<juego.cantidad_herramientas){

			if(es_misma_posicion(juego.herramientas[j].posicion, posicion)){

				tipo = juego.herramientas[j].tipo;
				chocado = true;
			}
			j++;
		}
	}


	return tipo;
}


/*
 * PRE: Cantidad herramientas sea 0 o mayor, herramientas esté inicializada
 * POS: Devuelve el índice de la herramienta que coincida con la posición dada, o -2 si no encuentra nada.
 */ 
int indice_herramienta (elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int cantidad_herramientas, coordenada_t posicion){

	bool chocado = false;
	int indice = NO_HAY_ELEMENTO;
	int i = 0;

	while(!chocado && i<cantidad_herramientas){

		if(es_misma_posicion(herramientas[i].posicion, posicion)){
			
			indice = i;
			chocado = true;
		}
		i++;
	}

	return indice;
}


/*
 * PRE: -
 * POS: Devuelve true si el tipo es PIEDRA, KOALA o ÁRBOL
 */ 
bool es_obstaculo (char tipo_elemento){
	return ((tipo_elemento == PIEDRA) || (tipo_elemento == KOALA) || (tipo_elemento == ARBOL) );
}


/*
 * PRE: El personaje haya chocado una PIEDRA, ÁRBOL o KOALA, y el contratiempo sea uno de los anteriores.
 * POS: Aplica el contratiempo correspondiente al personaje
 */ 
void aplicar_contratiempo (juego_t* juego, char contratiempo){

	if (contratiempo == PIEDRA){
		juego->personaje.tiempo_perdido += tiempo_piedra(juego->personaje.tipo);

		if(puede_usar_gps(juego->personaje.tipo, juego->personaje.tiempo_perdido)){
			juego->chloe_visible = true;
		}

    } else if (contratiempo == ARBOL){
		juego->personaje.tiempo_perdido += tiempo_arbol(juego->personaje.tipo);

		if(puede_usar_gps(juego->personaje.tipo, juego->personaje.tiempo_perdido)){
			juego->chloe_visible = true;
		}

	} else {
		tropezar_con_sekoalaz(juego);
	}
}


/*
 * PRE: -
 * POS: Devuelve 0.0 si el personaje es POLAR, 2.0 en caso contrario
 */ 
double tiempo_piedra(char tipo_personaje){
	double tiempo_retraso = 0.0;

	if(tipo_personaje!=POLAR){
		tiempo_retraso = TIEMPO_PIEDRA;

	} else {
		tiempo_retraso = TIEMPO_EVADIR_PIEDRA;	
	}

	return tiempo_retraso;
}


/*
 * PRE: -
 * POS: Devuelve 0.5 si el personaje es PARDO, 1.0 en caso contrario.
 */ 
double tiempo_arbol(char tipo_personaje){
	double tiempo_retraso = 0.0;

	if(tipo_personaje!=PARDO){
		tiempo_retraso = TIEMPO_TREPAR;

	} else {
		tiempo_retraso = TIEMPO_TREPAR_RAPIDO;
	}

	return tiempo_retraso;
}


/*
 * PRE: Las posiciones del personaje, Chloe, obstáculos y herramientas estén inicializadas.
 *      Los topes de obstáculos y herramientas sean válidos.
 * POS: Mueve al personaje a una posición aleatoria en la COLUMNA INICIAL si hay por lo menos una posición libre
 *		Sinó lo moverá a una posición aleatoria en el mapa libre.
 */ 

void tropezar_con_sekoalaz (juego_t* juego){
	coordenada_t posicion;

	mostrar_mensaje_usuario(KOALA,NADA);


	if(!esta_columna_ocupada(*juego, COLUMNA_INICIAL)){

		do{
			posicion = posicion_inicial_personaje();

		} while(!esta_posicion_libre(*juego, posicion));

	} else {

		posicion = posicion_aleatoria_libre(*juego);

	}

	juego->personaje.posicion = posicion;
}


/*
 * PRE: Las posiciones del personaje, Chloe, obstáculos y herramientas estén inicializadas.
 *      Los topes de obstáculos y herramientas sean válidos. La columna sea válida.
 * POS: Devuelve true si no hay alguna posición libre en la columna, false en caso contrario.
 */ 
bool esta_columna_ocupada(juego_t juego, int columna){
	
	bool ocupada = false;

	int cantidad_posiciones = 0;
	int i = 0, j = 0;

	if (juego.amiga_chloe.col == columna){
		cantidad_posiciones++;
	}

	while(!ocupada && i < juego.cantidad_obstaculos){
			
		if(juego.obstaculos[i].posicion.col == columna){
			cantidad_posiciones++;
		}

		if(cantidad_posiciones == MAX_FILAS){
			ocupada = true;
		}
		i++;
	}
	
	while(!ocupada && j < juego.cantidad_herramientas){
			
		if(juego.herramientas[j].posicion.col == columna){
			cantidad_posiciones++;
		}

		if(cantidad_posiciones == MAX_FILAS){
			ocupada = true;
		}
		j++;
	}

	return ocupada;
}


/*
 * PRE: -
 * POS: Devuelve true si el elemento es VELA, PILA o BENGALA; sinó devuelve false.
 */ 
bool es_herramienta(char tipo_elemento){
	return ( (tipo_elemento == VELA ) || (tipo_elemento == PILA) || (tipo_elemento == BENGALA) );
}


/*
 * PRE: El tope de herramientas sea mayor o igual a 0, el recolectable sea PILA, VELA o BENGALA
 * POS: Añade movimientos a la linterna si es pila, sinó agrega la herramienta correspondiente a la mochila.
 */ 
void agregar_en_mochila (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_herramientas , char recolectable){

	if (recolectable == PILA){
		mochila[INDICE_LINTERNA].movimientos_restantes += MOVIMIENTOS_PILAS;

	}else if (recolectable == VELA){

		mochila[(*cantidad_herramientas)].tipo = VELA;
		mochila[(*cantidad_herramientas)].movimientos_restantes = MOVIMIENTOS_VELAS;

		(*cantidad_herramientas)++;

	} else {

		mochila[(*cantidad_herramientas)].tipo = BENGALA;
		mochila[(*cantidad_herramientas)].movimientos_restantes= DURACION_BENGALAS;

		(*cantidad_herramientas)++;
	}

	printf("Herramienta agregada %c con %i movimientos", mochila[(*cantidad_herramientas)-1].tipo, mochila[(*cantidad_herramientas)-1].movimientos_restantes);
}


/*
 * PRE: La cantidad sea mayor o igual a 1, indice sea mayor o igual a 0
 * POS: Elimina físicamente la herramienta en la posición del índice
 */ 
void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice){
	int indice_ultima_herramienta = (*cantidad_herramientas) -1;

	herramientas[indice] = herramientas[indice_ultima_herramienta];
	(*cantidad_herramientas) --;
}


/*
 * PRE: La herramienta sea válida, el índice sea mayor o igual a 0
 * POS: Si el índice tiene por lo menos un movimiento activa la herramienta
 */ 
void intentar_iluminar_con(juego_t* juego, char herramienta, int indice_herramienta){

	if((juego->personaje.mochila[indice_herramienta].movimientos_restantes >MIN_MOVIMIENTOS) ){
		ocultar_todo(juego);
		iluminar_con(juego,herramienta);

		juego->personaje.mochila[indice_herramienta].movimientos_restantes--;
		//printf("Movimientos restantes de %c : %i indice en uso: %i \n", juego->personaje.mochila[indice_herramienta].tipo, juego->personaje.mochila[indice_herramienta].movimientos_restantes, indice_herramienta );
	
	} else{
		ocultar_todo(juego);
		juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;

	}
}


/*
 * PRE: La cantidad de herramientas y obstáculos sea mayor o igual a 0, el personaje esté inicializado
 * POS: Oculta las herramientas, obstáculos y a Chloe (teniendo en cuenta si puede o no usar el gps)
 */ 
void ocultar_todo (juego_t* juego){

	int i;

	if (!puede_usar_gps(juego->personaje.tipo, juego->personaje.tiempo_perdido)) {

		juego->chloe_visible = VISIBILIDAD_DEFECTO;
	}

	for (i = 0; i < juego->cantidad_obstaculos; i++){
		juego->obstaculos[i].visible = VISIBILIDAD_DEFECTO;
	}
	
	for (i = 0; i < juego->cantidad_herramientas; i++){

		juego->herramientas[i].visible = VISIBILIDAD_DEFECTO;
	}
}


/*
 * PRE: La herramienta sea VELA, LINTERNA o BENGALA
 * POS: Ilumina con las carácterísticas de la herramienta elegida
 */ 
void iluminar_con (juego_t* juego, char herramienta){
	char direccion = '0';

	if(herramienta == LINTERNA){
		direccion = juego->personaje.ultimo_movimiento;

		switch(direccion){
			case MOVERSE_ARRIBA:
		
				iluminar_hacia_arriba(juego);
				break;

			case MOVERSE_ABAJO:

				iluminar_hacia_abajo(juego);
				break;

			case MOVERSE_IZQUIERDA:

				iluminar_hacia_izquierda(juego);
				break;

			case MOVERSE_DERECHA:

				iluminar_hacia_derecha(juego);
				break;

		}

	} else if (herramienta == VELA){
		iluminar_alrededor(juego);

	}else{ 
		iluminar_con_bengala(juego);	
	}
}	


/*
 * POS: Las posiciones del personaje, Chloe y todos los elementos así como sus topes estén inicializados
 * PRE: Ilumina todos los elementos que están arriba del personaje
 */ 
void iluminar_hacia_arriba(juego_t* juego){
	int i;

	if (esta_arriba_de( juego->personaje.posicion, juego->amiga_chloe ) ){
		juego->chloe_visible = true;
	}
	for (i = 0; i < juego->cantidad_obstaculos; i++){
		if (esta_arriba_de(juego->personaje.posicion, juego->obstaculos[i].posicion )){
			juego->obstaculos[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->obstaculos[i].posicion.fil, juego-> obstaculos[i].posicion.col);
		}
	}
	
	for (i = 0; i < juego->cantidad_herramientas; i++){
		if (esta_arriba_de(juego->personaje.posicion, juego->herramientas[i].posicion )){
			juego->herramientas[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->herramientas[i].posicion.fil, juego-> herramientas[i].posicion.col);
		}
	}
}

/*
 * PRE: -
 * POS: Devuelve true si la posición elegida está arriba de la del personaje
 */ 
bool esta_arriba_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col == posicion_personaje.col) && (posicion_elegida.fil < posicion_personaje.fil));
}


/*
 * POS: Las posiciones del personaje, Chloe y todos los elementos así como sus topes estén inicializados
 * PRE: Ilumina todos los elementos que están abajo del personaje
 */ 
void iluminar_hacia_abajo(juego_t* juego){

	int i;

	if (esta_abajo_de( juego->personaje.posicion, juego->amiga_chloe) ){
		juego->chloe_visible = true;
	}
	for (i = 0; i < juego->cantidad_obstaculos; i++){
		if (esta_abajo_de(juego->personaje.posicion, juego->obstaculos[i].posicion )){
			juego->obstaculos[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->obstaculos[i].posicion.fil, juego-> obstaculos[i].posicion.col);
		}
	}
	
	for (i = 0; i < juego->cantidad_herramientas; i++){
		if (esta_abajo_de(juego->personaje.posicion, juego->herramientas[i].posicion )){
			juego->herramientas[i].visible = true;
				//printf("Se ilumina fil: %i y col: %i\n",juego->herramientas[i].posicion.fil, juego-> herramientas[i].posicion.col);
		}
	}
}


/*
 * PRE: -
 * POS: Devuelve true si la posición elegida está abajo de la del personaje
 */ 
bool esta_abajo_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col == posicion_personaje.col) && (posicion_elegida.fil > posicion_personaje.fil));
}


/*
 * POS: Las posiciones del personaje, Chloe y todos los elementos así como sus topes estén inicializados
 * PRE: Ilumina todos los elementos que están a la izquierda del personaje
 */ 
void iluminar_hacia_izquierda(juego_t* juego){

	int i;

	if (esta_izquierda_de( juego->personaje.posicion, juego->amiga_chloe ) ){
		juego->chloe_visible = true;
	}

	for (i = 0; i < (juego->cantidad_obstaculos); i++){

		if (esta_izquierda_de(juego->personaje.posicion, juego->obstaculos[i].posicion)){
			juego->obstaculos[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",posicion_elemento.fil, posicion_elemento.col);
		}
	}
	
	for (i = 0; i < (juego->cantidad_herramientas); i++){
		
		if (esta_izquierda_de(juego->personaje.posicion, juego->herramientas[i].posicion)){
			juego->herramientas[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",posicion_elemento.fil, posicion_elemento.col);
		}
	}
}


/*
 * PRE: -
 * POS: Devuelve true si la posición elegida está a la izquierda de la del personaje
 */ 
bool esta_izquierda_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col < posicion_personaje.col) && (posicion_elegida.fil == posicion_personaje.fil));
}


/*
 * POS: Las posiciones del personaje, Chloe y todos los elementos así como sus topes estén inicializados
 * PRE: Ilumina todos los elementos que están a la derecha del personaje
 */ 
void iluminar_hacia_derecha(juego_t* juego){

	int i;

	if (esta_derecha_de( juego->personaje.posicion, juego->amiga_chloe ) ){
		juego->chloe_visible = true;
	}
	for (i = 0; i < (juego->cantidad_obstaculos); i++){
		if (esta_derecha_de(juego->personaje.posicion, juego->obstaculos[i].posicion )){
			juego->obstaculos[i].visible = true;
				//printf("Se ilumina fil: %i y col: %i\n",juego->obstaculos[i].posicion.fil, juego-> obstaculos[i].posicion.col);
		}
	}
	
	for (i = 0; i < (juego->cantidad_herramientas); i++){
		if (esta_derecha_de(juego->personaje.posicion, juego->herramientas[i].posicion )){
			juego->herramientas[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->herramientas[i].posicion.fil, juego-> herramientas[i].posicion.col);
		}
	}
}


/*
 * PRE: -
 * POS: Devuelve true si la posición elegida está a la derecha de la del personaje
 */ 
bool esta_derecha_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col > posicion_personaje.col) && (posicion_elegida.fil == posicion_personaje.fil));
}


/*
 * POS: Las posiciones del personaje, Chloe y todos los elementos así como sus topes estén inicializados
 * PRE: Ilumina todos los elementos que están alrededor del personaje
 */ 
void iluminar_alrededor(juego_t* juego){
	int i;

	if (esta_alrededor( juego->personaje.posicion, juego->amiga_chloe ) ){
		juego->chloe_visible = true;
	}

	for (i = 0; i < juego->cantidad_obstaculos; i++){
		if (esta_alrededor(juego->personaje.posicion, juego->obstaculos[i].posicion )){
			juego->obstaculos[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->obstaculos[i].posicion.fil, juego-> obstaculos[i].posicion.col);
		}
	}
	
	for (i = 0; i < juego->cantidad_herramientas; i++){
		if (esta_alrededor(juego->personaje.posicion, juego->herramientas[i].posicion )){
			juego->herramientas[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->herramientas[i].posicion.fil, juego-> herramientas[i].posicion.col);
		}
	}
}


/*
 * PRE: -
 * POS: Devuelve true si la posición elegida está alrededor de la del personaje
 */ 
bool esta_alrededor(coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	bool alrededor = false;

	if ( (distancia_mahattan(posicion_personaje, posicion_elegida))<=1){
		alrededor = true;
	} else if ( ( (distancia_mahattan(posicion_personaje, posicion_elegida))==2) && (estan_en_diagonal(posicion_personaje,posicion_elegida)) ){
		alrededor = true;
	}

	return alrededor;
}


/*
 * PRE: -
 * POS: Devuelve la distancia Manhattan entre las dos coordenadas
 */ 
int distancia_mahattan (coordenada_t posicion1, coordenada_t posicion2){
	return (( abs(posicion2.col-posicion1.col) + abs(posicion2.fil-posicion1.fil) ));
}


/*
 * PRE: -
 * POS: Devuelve true si las posiciones están en diagonal
 */ 
bool estan_en_diagonal(coordenada_t posicion1, coordenada_t posicion2){
	bool diagonal = false;

	if ((posicion1.col!=posicion2.col)&&(posicion1.fil!=posicion2.fil)){
		if((abs(posicion1.fil - posicion2.fil)%abs(posicion1.col - posicion2.col))==0){
			diagonal = true;
		}
	}

	return diagonal;
}


/*
 * POS: Las posiciones del personaje, Chloe y todos los elementos así como sus topes estén inicializados
 * PRE: Enciende una bengala en una posición aleatoria del mapa e ilumina todos los elementos que están dentro de su rango
 */ 
void iluminar_con_bengala(juego_t* juego){
	
	coordenada_t posicion_bengala;
	int i;

	posicion_bengala = posicion_aleatoria();

	if (distancia_mahattan( posicion_bengala, juego->amiga_chloe ) <= MAX_RANGO_BENGALA){
		juego->chloe_visible = true;
	}

	for (i = 0; i < juego->cantidad_obstaculos; i++){
		if (distancia_mahattan(posicion_bengala, juego->obstaculos[i].posicion ) <= MAX_RANGO_BENGALA){
			juego->obstaculos[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->obstaculos[i].posicion.fil, juego-> obstaculos[i].posicion.col);
		}
	}
	
	for (i = 0; i < juego->cantidad_herramientas; i++){
		if (distancia_mahattan(posicion_bengala, juego->herramientas[i].posicion ) <=MAX_RANGO_BENGALA){
			juego->herramientas[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",juego->herramientas[i].posicion.fil, juego-> herramientas[i].posicion.col);
		}
	}
}


/*
 * PRE: La herramienta sea válida, la mochila esté inicializada así como su tope
 * POS: Si hay una bengala activa, intenta ilumina con la bengala.
 *		Sinó intenta encender la herramienta elegida
 */ 
void usar_herramienta(juego_t* juego, char herramienta){
	
	int indice = 0;

	if (!hay_bengala_activa(juego->personaje.mochila, juego->personaje.elemento_en_uso)){

		indice = obtener_posicion_mochila(juego->personaje.mochila, herramienta, juego->personaje.cantidad_elementos);
		if((indice == juego->personaje.elemento_en_uso)){

			juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;
			ocultar_todo(juego);

		} else {

			if( herramienta == LINTERNA ){
				encender_linterna(juego, juego->personaje.ultimo_movimiento, indice);
			} else if ( herramienta == VELA){
				encender_vela(juego,indice);
			} else{
				encender_bengala(juego,indice);
			}

		}

	} else {

		mostrar_mensaje_usuario(BENGALA_EN_USO, NADA);
		intentar_iluminar_con(juego, BENGALA, juego->personaje.elemento_en_uso);
	}
}


/*
 * PRE: elemento en uso mayor o igual a 0 , o -1 
 * POS: Devuelve true si el elemento en uso no es -1 y la herramienta en uso es BENGALA, false en caso de que no se cumpla
 */ 
bool hay_bengala_activa (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int elemento_en_uso){
	return ( (elemento_en_uso!= SIN_ELEMENTOS_EN_USO) && (  mochila[elemento_en_uso].tipo == BENGALA ));
}


/*
 * PRE: 
 * POS: 
 */ 
int obtener_posicion_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char elemento, int cantidad_herramientas){
	bool encontrado = false;

	int indice = NO_HAY_ELEMENTO;
	int i = 0;

	while(!encontrado && (i<cantidad_herramientas) ){
		
		if( es_herramienta_buscada(mochila[i], elemento) ){
			encontrado = true;
			indice = i;
		} 

		i++;
	}

	return indice;
}


bool es_herramienta_buscada( elemento_mochila_t elemento, char buscado){
	bool herramienta = false;

	if ((elemento.tipo == buscado) && (elemento.movimientos_restantes > MIN_MOVIMIENTOS)){
		herramienta = true;
	}

	return herramienta;
}


void encender_linterna(juego_t* juego, char ultimo_movimiento, int indice){

	if(indice != NO_HAY_ELEMENTO){
		
		juego->personaje.elemento_en_uso = indice;
		juego->personaje.mochila[indice].movimientos_restantes--;

		agregar_obstaculos(juego, &(juego->cantidad_obstaculos), KOALAS_POR_LINTERNA ,KOALA);
		iluminar_con(juego, LINTERNA);

		mostrar_mensaje_usuario(LINTERNA,ENCENDIDO);

	} else{
		ocultar_todo(juego);
		mostrar_mensaje_usuario(LINTERNA, NADA);
	}
}


void encender_vela(juego_t* juego, int indice){

	if (indice != NO_HAY_ELEMENTO){

		juego->personaje.elemento_en_uso = indice;
		juego->personaje.mochila[indice].movimientos_restantes--;

		iluminar_con(juego,VELA);
		
		mostrar_mensaje_usuario(VELA, ENCENDIDO);
	}else {
		ocultar_todo(juego);
		mostrar_mensaje_usuario(VELA, NADA);
	}
}


void encender_bengala(juego_t* juego, int indice){

	if (indice != NO_HAY_ELEMENTO){

		juego->personaje.elemento_en_uso = indice;
		juego->personaje.mochila[indice].movimientos_restantes--;

		iluminar_con(juego,BENGALA);
		
		mostrar_mensaje_usuario(BENGALA, ENCENDIDO);
	} else{

		ocultar_todo(juego);
		mostrar_mensaje_usuario(BENGALA, NADA);
	}
}


/*
 * Recibe un juego con todas sus estructuras válidas.
 *
 * El juego se dará por terminado, si el personaje encontró a Chloe. 
 * Devolverá:
 * -> 0 si el estado es jugando. 
 * -> -1 si el estado es terminado.
 */

int estado_juego(juego_t juego){
	int estado = 0;

	if(chloe_fue_encontrada(juego.personaje.posicion, juego.amiga_chloe) ){

		estado = JUEGO_TERMINADO;

	} else {

		estado = JUEGO_CONTINUA;
	}

	return estado;

}

bool chloe_fue_encontrada(coordenada_t posicion_personaje, coordenada_t amiga_chloe){

	return ((posicion_personaje.col == amiga_chloe.col) && (posicion_personaje.fil == amiga_chloe.fil));

}

bool es_jugada_valida (char jugada){
	return ( (jugada==MOVERSE_ARRIBA) || (jugada==MOVERSE_ABAJO)||(jugada==MOVERSE_IZQUIERDA)||(jugada==MOVERSE_DERECHA)||(jugada==ENCENDER_LINTERNA)||(jugada==ENCENDER_VELA)||(jugada==ENCENDER_BENGALA)||(jugada==TIEMPO_RESTANTE));
}
