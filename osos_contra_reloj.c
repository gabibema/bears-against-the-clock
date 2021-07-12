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


//BREAKKKKKKKKKKKK
//BORRAR
void mostrar_todas_posiciones(juego_t juego){
	int i;
	
	printf("PJ: %c , FIL: %i COL: %i\n", juego.personaje.tipo, juego.personaje.posicion.fil, juego.personaje.posicion.col);

	printf("PJ: %c , FIL: %i COL: %i\n", CHLOE, juego.amiga_chloe.fil, juego.amiga_chloe.col);

	i = 0;

		while(i < juego.cantidad_obstaculos){
			
			printf("OBS: %c FIL: %i COL: %i \n", juego.obstaculos[i].tipo,juego.obstaculos[i].posicion.fil,juego.obstaculos[i].posicion.col);

			i++;
		}

	i = 0;

		while(i < juego.cantidad_herramientas){
			printf("OBS: %c FIL: %i COL: %i \n", juego.herramientas[i].tipo,juego.herramientas[i].posicion.fil,juego.herramientas[i].posicion.col);
			i++;
		}
}


/*
 * Inicializará el juego, cargando toda la información inicial
 * y los datos del personaje. 
 */
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

	//printf("Obstáculos %i\n", juego->cantidad_obstaculos);
	//printf("Herramientas %i\n", juego->cantidad_herramientas);
	//printf("Cantidad Mochila %i\n", juego->personaje.cantidad_elementos);

	//mostrar_todas_posiciones(*juego);
}


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
 * PRE:
 * POS: 
 */ 
coordenada_t posicion_inicial_personaje(){
	
	coordenada_t posicion;

    posicion.col=COLUMNA_INICIAL;
    posicion.fil = rand()%MAX_FILAS;

	return posicion;
}


/*
 * PRE:
 * POS: 
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


void inicializar_chloe (bool* chloe_visible, coordenada_t* amiga_chloe, coordenada_t posicion_personaje){

	do{ 
		(*amiga_chloe) = posicion_aleatoria();

	}  while (es_misma_posicion( (*amiga_chloe), posicion_personaje));

	(*chloe_visible) = VISIBILIDAD_DEFECTO;

}


coordenada_t posicion_aleatoria(){
	coordenada_t posicion;
	
	posicion.fil= rand()%MAX_FILAS;
	posicion.col= rand()%MAX_COLUMNAS;

	return posicion;
}


bool es_misma_posicion(coordenada_t posicion_1, coordenada_t posicion_2){
	
	return ((posicion_1.fil == posicion_2.fil) && (posicion_1.col == posicion_2.col));
	
}


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


coordenada_t posicion_aleatoria_libre(juego_t juego){

	coordenada_t posicion;
	
	do{
		posicion = posicion_aleatoria();

	} while(!esta_posicion_libre(juego, posicion));

	return posicion;
}


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



void cargar_posiciones_reales (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego){

	int i;

	tablero[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
	

	for (i = 0; i< juego.cantidad_obstaculos; i++){
		tablero[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].tipo;
	}	
	
	for (i = 0; i< juego.cantidad_herramientas; i++){
		tablero[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;

	}

	tablero[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

}


/*
 * Mostrará el juego por pantalla.
 * Se recomienda mostrar todo lo que sea de utilidad para el jugador.
 */
void mostrar_juego(juego_t juego){
	char tablero[MAX_FILAS][MAX_COLUMNAS];

	mostrar_datos(juego.cantidad_obstaculos, juego.cantidad_herramientas, juego.personaje.cantidad_elementos, juego.personaje.tipo, juego.personaje.posicion.fil, juego.personaje.posicion.col);


	inicializar_matriz(tablero);
	
	//cargar_posiciones_reales(tablero, juego);
	cargar_posiciones_visibles(tablero, juego);

	mostrar_matriz(tablero);

}


void inicializar_matriz (char matriz[MAX_FILAS][MAX_COLUMNAS]){
	int i, j;

	for ( i = 0; i < MAX_FILAS; i++){
		for ( j = 0; j < MAX_COLUMNAS; j++){
			matriz[i][j] = VACIO;
		}
	}
}


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


bool puede_usar_gps(char tipo, double tiempo_perdido){
	return ( (tipo == PANDA) && ( tiempo_perdido >= TIEMPO_GPS) );
}



/*
 * Mueve el personaje en la dirección indicada por el usuario o habilita 
 * cualquiera de las herramientas y actualiza el juego según los elementos 
 * que haya en el camino del personaje.
 * El juego quedará en un estado válido al terminar el movimiento. 
 * El movimiento será:
 * -> W: Si el personaje debe moverse para la arriba. 
 * -> A: Si el personaje debe moverse para la izquierda.
 * -> S: Si el personaje debe moverse para la abajo.
 * -> D: Si el personaje debe moverse para la derecha.
 * -> L: Si el personaje quiere encender una linterna.
 * -> V: Si el personaje quiere encender una vela. 
 * -> E: Si el personaje quiere encender la bengala.
 * -> T: Si el personaje quiere ver el tiempo restante.
 * En caso de que querer activar una herramienta, y no tenga mas movimientos, no deberá 
 * activarse ninguna ventaja. 
 * Si se aprieta una tecla de iluminación y esta ya está siendo usada, se desactivará colocando
 * el int elemento_en_uso en -1.
 */
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


bool se_puede_mover(coordenada_t posicion){
	return ( (( posicion.fil >= FILA_MINIMA )&&( posicion.fil < MAX_FILAS )) && (( posicion.col >= COLUMNA_MINIMA )&&( posicion.col < MAX_COLUMNAS )) );	
}


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


bool es_obstaculo (char tipo_elemento){
	return ((tipo_elemento == PIEDRA) || (tipo_elemento == KOALA) || (tipo_elemento == ARBOL) );
}


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


double tiempo_piedra(char tipo_personaje){
	double tiempo_retraso = 0.0;

	if(tipo_personaje!=POLAR){
		tiempo_retraso = TIEMPO_PIEDRA;

	} else {
		tiempo_retraso = TIEMPO_EVADIR_PIEDRA;	
	}

	return tiempo_retraso;
}


double tiempo_arbol(char tipo_personaje){
	double tiempo_retraso = 0.0;

	if(tipo_personaje!=PARDO){
		tiempo_retraso = TIEMPO_TREPAR;

	} else {
		tiempo_retraso = TIEMPO_TREPAR_RAPIDO;
	}

	return tiempo_retraso;
}


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


bool es_herramienta(char tipo_elemento){
	return ( (tipo_elemento == VELA ) || (tipo_elemento == PILA) || (tipo_elemento == BENGALA) );
}

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


void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice){
	int indice_ultima_herramienta = (*cantidad_herramientas) -1;

	herramientas[indice] = herramientas[indice_ultima_herramienta];
	(*cantidad_herramientas) --;
}


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


void ocultar_todo (juego_t* juego){
	int i;

	juego->chloe_visible = VISIBILIDAD_DEFECTO;

	for (i = 0; i < juego->cantidad_obstaculos; i++){
		juego->obstaculos[i].visible = VISIBILIDAD_DEFECTO;
	}
	
	for (i = 0; i < juego->cantidad_herramientas; i++){

		juego->herramientas[i].visible = VISIBILIDAD_DEFECTO;
	}
}


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


bool esta_arriba_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col == posicion_personaje.col) && (posicion_elegida.fil < posicion_personaje.fil));
}


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

bool esta_abajo_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col == posicion_personaje.col) && (posicion_elegida.fil > posicion_personaje.fil));
}


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


bool esta_izquierda_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col < posicion_personaje.col) && (posicion_elegida.fil == posicion_personaje.fil));
}


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


bool esta_derecha_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col > posicion_personaje.col) && (posicion_elegida.fil == posicion_personaje.fil));
}


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


bool esta_alrededor(coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	bool alrededor = false;

	if ( (distancia_mahattan(posicion_personaje, posicion_elegida))<=1){
		alrededor = true;
	} else if ( ( (distancia_mahattan(posicion_personaje, posicion_elegida))==2) && (estan_en_diagonal(posicion_personaje,posicion_elegida)) ){
		alrededor = true;
	}

	return alrededor;
}


int distancia_mahattan (coordenada_t posicion1, coordenada_t posicion2){
	return (( abs(posicion2.col-posicion1.col) + abs(posicion2.fil-posicion1.fil) ));
}


bool estan_en_diagonal(coordenada_t posicion1, coordenada_t posicion2){
	bool diagonal = false;

	if ((posicion1.col!=posicion2.col)&&(posicion1.fil!=posicion2.fil)){
		if((abs(posicion1.fil - posicion2.fil)%abs(posicion1.col - posicion2.col))==0){
			diagonal = true;
		}
	}

	return diagonal;
}


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

		printf(" %s\t\t\t%s ¡Hay una bengala activa! %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
		
		intentar_iluminar_con(juego, BENGALA, juego->personaje.elemento_en_uso);
	}
}


bool hay_bengala_activa (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int elemento_en_uso){
	return ( (elemento_en_uso!= SIN_ELEMENTOS_EN_USO) && (  mochila[elemento_en_uso].tipo == BENGALA ));
}


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
