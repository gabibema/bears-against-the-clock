#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <time.h> 

#include "test_de_personalidad.h"
#include "osos_contra_reloj.h"
#include "utiles.h"

#define RESET_COLOR    "\x1b[0m"
#define NEGRO_T        "\x1b[30m"
#define NEGRO_F        "\x1b[40m"
#define ROJO_T     "\x1b[31m"
#define ROJO_F     "\x1b[41m"
#define VERDE_T        "\x1b[32m"
#define VERDE_F        "\x1b[42m"
#define AMARILLO_T "\x1b[33m"
#define    AMARILLO_F  "\x1b[43m"
#define AZUL_T     "\x1b[34m"
#define    AZUL_F      "\x1b[44m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define CYAN_T     "\x1b[36m"
#define CYAN_F     "\x1b[46m"
#define BLANCO_T   "\x1b[37m"
#define BLANCO_F   "\x1b[47m"

#define RESET_COLOR    "\x1b[0m"
#define NEGRO_T        "\x1b[30m"
#define NEGRO_F        "\x1b[40m"
#define ROJO_T     "\x1b[31m"
#define ROJO_F     "\x1b[41m"
#define VERDE_T        "\x1b[32m"
#define VERDE_F        "\x1b[42m"
#define AMARILLO_T "\x1b[33m"
#define    AMARILLO_F  "\x1b[43m"
#define AZUL_T     "\x1b[34m"
#define    AZUL_F      "\x1b[44m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define CYAN_T     "\x1b[36m"
#define CYAN_F     "\x1b[46m"
#define BLANCO_T   "\x1b[37m"
#define BLANCO_F   "\x1b[47m"

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

bool VISIBILIDAD_DEFECTO = false;

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

void inicializar_juego(juego_t* juego, char tipo_personaje);

void inicializar_personaje(juego_t* juego, char tipo_personaje);

coordenada_t posicion_inicial_personaje();
void obtener_kit_inicial_personaje(juego_t* juego,char tipo_personaje);
void generar_kit_oso (juego_t* juego, int movimientos_linterna, int cantidad_velas, int movimientos_vela, int cantidad_bengalas, int duracion_bengalas);

bool es_misma_posicion(coordenada_t posicion1, coordenada_t posicion2);

void inicializar_chloe (juego_t* juego);

coordenada_t posicion_aleatoria();
bool esta_posicion_libre(juego_t juego, coordenada_t posicion);

void agregar_obstaculos (juego_t* juego, int cantidad, char tipo);

void agregar_recolectables (juego_t* juego, int cantidad, char tipo);

void inicializar_matriz (char matriz[MAX_FILAS][MAX_COLUMNAS]);
void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]);

void cargar_posiciones_visibles (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego);
bool tiene_beneficio (char tipo, double tiempo_perdido);

void mostrar_juego(juego_t juego);

void pedir_jugada(char* jugada);
bool es_jugada_valida (char jugada);
void realizar_jugada(juego_t* juego, char jugada);

coordenada_t posicion_hacia(coordenada_t posicion, char direccion);
void moverse_hacia(juego_t* juego, coordenada_t nueva_posicion, char direccion);
bool se_puede_mover(coordenada_t posicion);

void intentar_iluminar_con(juego_t* juego, char herramienta, int indice_herramienta);

void usar_herramienta(juego_t* juego, char herramienta);

int indice_elemento (juego_t juego, coordenada_t posicion, char tipo_elemento);
int indice_obstaculo (juego_t juego, coordenada_t posicion);
int indice_herramienta (juego_t juego, coordenada_t posicion);

void aplicar_efecto_de(juego_t* juego, char tipo_chocado, coordenada_t posicion_personaje);

bool es_obstaculo (char tipo_elemento);
bool es_herramienta (char tipo_elemento);


char tipo_elemento_chocado (juego_t juego, coordenada_t posicion);

void aplicar_contratiempo (juego_t* juego, personaje_t* personaje, char contratiempo);

void tropezar_con_sekoalaz (juego_t* juego, personaje_t* personaje);
bool esta_columna_ocupada(juego_t juego, int columna);
double trepar_arbol(char tipo_personaje);
double tropezar_con_piedra(char tipo_personaje);

void agregar_en_mochila (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_herramientas , char herramienta);
void eliminar_elemento (juego_t* juego, int indice, char tipo_elemento);
void eliminar_obstaculo(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int* cantidad_obstaculos,int indice);
void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice);


void cargar_posiciones_reales (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego);

bool hay_bengala_activa (personaje_t personaje, int elemento_en_uso);

int obtener_posicion_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char elemento, int cantidad_herramientas);

void ocultar_todo (juego_t* juego);

void iluminar_con (juego_t* juego, char herramienta);

void encender_linterna(juego_t* juego, char ultimo_movimiento, int indice);

void iluminar_hacia_arriba(juego_t* juego);
bool esta_arriba_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);


void iluminar_hacia_abajo(juego_t* juego);
bool esta_abajo_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);


void iluminar_hacia_izquierda(juego_t* juego);
bool esta_izquierda_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);

void iluminar_hacia_derecha(juego_t* juego);
bool esta_derecha_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);


void encender_bengala(juego_t* juego, int indice);
void iluminar_con_bengala(juego_t* juego);
bool es_herramienta_buscada( elemento_mochila_t elemento, char buscado);

void encender_vela(juego_t* juego, int indice);


void iluminar_alrededor(juego_t* juego);

bool esta_alrededor(coordenada_t posicion_personaje, coordenada_t posicion_elegida);
int distancia_mahattan (coordenada_t posicion1, coordenada_t posicion2);
bool estan_en_diagonal(coordenada_t posicion1, coordenada_t posicion2);


int estado_juego(juego_t juego);
bool chloe_fue_encontrada (juego_t juego);


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
	
	inicializar_personaje(juego, tipo_personaje);
    inicializar_chloe(juego);

	agregar_obstaculos(juego, MAX_ARBOLES_INICIO, ARBOL);
	agregar_obstaculos(juego, MAX_PIEDRAS_INICIO, PIEDRA);
	agregar_obstaculos(juego, MAX_KOALAS_INICIO, KOALA);


	agregar_recolectables(juego, MAX_PILAS_INICIO, PILA);
	agregar_recolectables(juego, MAX_VELAS_INICIO, VELA);
	agregar_recolectables(juego, MAX_BENGALAS_INICIO, BENGALA);

	printf("Obstáculos %i\n", juego->cantidad_obstaculos);
	printf("Herramientas %i\n", juego->cantidad_herramientas);
	printf("Cantidad Mochila %i\n", juego->personaje.cantidad_elementos);

	//mostrar_todas_posiciones(*juego);
}


void inicializar_personaje(juego_t* juego, char tipo_personaje){
	juego->personaje.tipo = tipo_personaje;
	juego->personaje.posicion = posicion_inicial_personaje();
	juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;
	juego->personaje.tiempo_perdido = 0;
	juego->personaje.ultimo_movimiento = MOVERSE_DERECHA;

	obtener_kit_inicial_personaje(juego, tipo_personaje);
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
void obtener_kit_inicial_personaje(juego_t* juego,char tipo_personaje){

	if( tipo_personaje == PARDO){
		generar_kit_oso(juego, MOVIMIENTOS_LINTERNA_EXPERTO, CANTIDAD_VELAS_NORMAL, MOVIMIENTOS_VELAS, CANTIDAD_BENGALAS_NORMAL, DURACION_BENGALAS);

	} else if ( tipo_personaje == POLAR ){
		generar_kit_oso(juego, MOVIMIENTOS_LINTERNA_NORMAL, CANTIDAD_VELAS_YOGA, MOVIMIENTOS_VELAS, CANTIDAD_BENGALAS_NORMAL, DURACION_BENGALAS);

	} else {
		generar_kit_oso(juego, MOVIMIENTOS_LINTERNA_NORMAL, CANTIDAD_VELAS_NORMAL, MOVIMIENTOS_VELAS, CANTIDAD_BENGALAS_FIESTA, DURACION_BENGALAS);

	}
}  


void generar_kit_oso (juego_t* juego, int movimientos_linterna, int cantidad_velas, int movimientos_vela, int cantidad_bengalas, int duracion_bengalas){
	
	int i;
	int cantidad;

	juego->personaje.cantidad_elementos = 0;

	juego->personaje.mochila[0].tipo=LINTERNA;
	juego->personaje.mochila[0].movimientos_restantes = movimientos_linterna;

	juego->personaje.cantidad_elementos++;

	cantidad = juego->personaje.cantidad_elementos;

	for ( i =  cantidad; i < cantidad_velas + cantidad; i++ ){
		
		juego->personaje.mochila[i].tipo=VELA;
		juego->personaje.mochila[i].movimientos_restantes= movimientos_vela;	
		juego->personaje.cantidad_elementos++;	
	}

	cantidad = juego->personaje.cantidad_elementos;

	for ( i =  cantidad; i < cantidad_bengalas + cantidad; i++ ){
		
		juego->personaje.mochila[i].tipo=BENGALA;	
		juego->personaje.mochila[i].movimientos_restantes= duracion_bengalas;
		juego->personaje.cantidad_elementos++;	
	}
}


void inicializar_chloe (juego_t* juego){

	do{ 
		juego->amiga_chloe = posicion_aleatoria();

	}  while (es_misma_posicion(juego->personaje.posicion, juego->amiga_chloe));

	juego->chloe_visible = VISIBILIDAD_DEFECTO;

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


void agregar_obstaculos (juego_t* juego, int cantidad, char tipo){
	
	coordenada_t posicion;

	int cantidad_inicial = juego->cantidad_obstaculos;
	int i;


	for ( i = cantidad_inicial; i < cantidad + cantidad_inicial; i++){
		juego->obstaculos[i].tipo = tipo; 

		do {
			posicion = posicion_aleatoria();
		} while(!esta_posicion_libre(*juego, posicion ));

		juego->obstaculos[i].posicion = posicion;
		juego->obstaculos[i].visible = VISIBILIDAD_DEFECTO;
		
		juego->cantidad_obstaculos++;	

	}
}


bool esta_posicion_libre(juego_t juego, coordenada_t posicion){
	int i = 0;
	bool esta_libre = true;

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

		i = 0;

		while(esta_libre && i < juego.cantidad_herramientas){

			if(es_misma_posicion(juego.herramientas[i].posicion, posicion)){
				esta_libre=false;
			}
			i++;
		}
	}

	return esta_libre;
}


void agregar_recolectables (juego_t* juego, int cantidad, char tipo){
	
	coordenada_t posicion;

	int cantidad_inicial = juego->cantidad_herramientas;
	int i;


	for ( i = cantidad_inicial; i < cantidad + cantidad_inicial; i++){

		do {
			posicion = posicion_aleatoria();
		} while(!esta_posicion_libre(*juego, posicion));

		juego->herramientas[i].visible = VISIBILIDAD_DEFECTO;
		juego->herramientas[i].posicion = posicion;	
		juego->herramientas[i].tipo = tipo; 
		juego->cantidad_herramientas++;
	}	
}


/*
 * Mostrará el juego por pantalla.
 * Se recomienda mostrar todo lo que sea de utilidad para el jugador.
 */
void mostrar_juego(juego_t juego){
	char tablero[MAX_FILAS][MAX_COLUMNAS];

	printf("Obstáculos %i\n", juego.cantidad_obstaculos);
	printf("Herramientas %i\n", juego.cantidad_herramientas);
	printf("Cantidad Mochila %i\n", juego.personaje.cantidad_elementos);
	printf("\n");

	printf("Personaje: (%c). Fil: %i. Col: %i\n", juego.personaje.tipo, juego.personaje.posicion.fil, juego.personaje.posicion.col); 
	printf("Personaje: (%c). Fil: %i. Col: %i\n", CHLOE, juego.amiga_chloe.fil, juego.amiga_chloe.col); 
	printf("Para ganar debes encontrar a Chloe (%s%s%c%s)",VERDE_T, MAGENTA_F,CHLOE,RESET_COLOR );
	inicializar_matriz(tablero);
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

	tablero[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

	if( (juego.chloe_visible) || (tiene_beneficio(juego.personaje.tipo, juego.personaje.tiempo_perdido) ) ){
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
}


bool tiene_beneficio (char tipo, double tiempo_perdido){
	return ( (tipo==PANDA)&& (tiempo_perdido>=30.0) );
}


void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]){
	int i,j;

	printf("\n"); 
	printf("   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n"); 
	for ( i = 0; i < MAX_FILAS; i++){
		
		printf("%2d ", i);
		
		for ( j = 0; j < MAX_COLUMNAS; j++){
			if(matriz[i][j] == PARDO){
				printf("%s%s%c%s ",ROJO_T,AZUL_F, matriz[i][j],RESET_COLOR );				
			}
			else if(matriz[i][j] == POLAR){
				printf("%s%s%c%s ",ROJO_T,AZUL_F, matriz[i][j] ,RESET_COLOR );				
			}
			else if(matriz[i][j] == PANDA){
				printf("%s%s%c%s ",ROJO_T,AZUL_F, matriz[i][j],RESET_COLOR );				
			}

			else if(matriz[i][j] == CHLOE){
				printf("%s%s%c%s ",VERDE_T, MAGENTA_F,matriz[i][j],RESET_COLOR );				
			}
			else {
				printf("%c ", matriz[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n"); 
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

	//mostrar_todas_posiciones(*juego);

	coordenada_t posicion = juego->personaje.posicion;
	
	double tiempo_sin_obstaculos = tiempo_actual();
	double tiempo_restante = 0.0;


	switch (jugada){

		case MOVERSE_ARRIBA:

			moverse_hacia(juego,posicion, MOVERSE_ARRIBA);
			break;

		case MOVERSE_ABAJO:

			moverse_hacia(juego,posicion, MOVERSE_ABAJO);
			break;

		case MOVERSE_IZQUIERDA:

			moverse_hacia(juego,posicion, MOVERSE_IZQUIERDA);
			break;

		case MOVERSE_DERECHA:
		
			moverse_hacia(juego,posicion, MOVERSE_DERECHA);

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

			tiempo_restante = TIEMPO_TOTAL - (tiempo_sin_obstaculos + juego->personaje.tiempo_perdido);
			printf("TIEMPO RESTANTE: %.2f\n", tiempo_restante);
			break;
	
		default:
			break;

	//mostrar_todas_posiciones(*juego);
	}
}


coordenada_t posicion_hacia(coordenada_t posicion, char direccion){
	
	if (direccion == MOVERSE_ARRIBA)
		posicion.fil--;
	else if (direccion == MOVERSE_ABAJO)
		posicion.fil++;
	else if (direccion == MOVERSE_IZQUIERDA)
		posicion.col--;
	else
		posicion.col++;

	return posicion;
}


void moverse_hacia(juego_t* juego, coordenada_t posicion_nueva, char direccion){
	int indice_en_uso = juego->personaje.elemento_en_uso;
	char tipo_chocado;

	posicion_nueva = posicion_hacia(posicion_nueva, direccion);

	if(se_puede_mover(posicion_nueva)){ 

		juego->personaje.ultimo_movimiento = direccion;
		juego->personaje.posicion = posicion_nueva;

		if(!esta_posicion_libre(*juego, juego->personaje.posicion)){

			tipo_chocado = tipo_elemento_chocado(*juego, juego->personaje.posicion);
			aplicar_efecto_de(juego, tipo_chocado, juego->personaje.posicion);	
		}
		
		if (indice_en_uso != SIN_ELEMENTOS_EN_USO){
			intentar_iluminar_con(juego,juego->personaje.mochila[indice_en_uso].tipo, indice_en_uso);
		}

	} else 
		printf("Movimiento no posible");
	
}


bool se_puede_mover(coordenada_t posicion){
	return ( ( (posicion.fil >= FILA_MINIMA)&&(posicion.fil < MAX_FILAS) ) &&( (posicion.col >= COLUMNA_MINIMA)&&(posicion.col < MAX_COLUMNAS) ) );	
}


void aplicar_efecto_de(juego_t* juego, char tipo_chocado, coordenada_t posicion_personaje){

	int indice_chocado = 0;

	if (es_obstaculo(tipo_chocado))
		aplicar_contratiempo(juego, &(juego->personaje), tipo_chocado);

	else {
		agregar_en_mochila(juego->personaje.mochila,&(juego->personaje.cantidad_elementos), tipo_chocado);


		printf("Cantidad de obstaculos: %i\n", juego->cantidad_obstaculos);		

		indice_chocado = indice_herramienta(*juego, juego->personaje.posicion);

		printf("Cantidad de obstaculos dps de chocado: %i\n", juego->cantidad_obstaculos);

		eliminar_herramienta(juego->herramientas, &(juego->cantidad_herramientas),indice_chocado);
		
		printf("Cantidad de obstaculos dps de eliminar_herramienta: %i\n", juego->cantidad_obstaculos);		
	}
}

char tipo_elemento_chocado (juego_t juego, coordenada_t posicion){

	bool chocado = false;
	char tipo;
	int i = 0;

	while(!chocado && i<juego.cantidad_obstaculos){

		if(es_misma_posicion(juego.obstaculos[i].posicion, posicion)){

			tipo = juego.obstaculos[i].tipo;
			chocado = true;

		} else {
			i++;
		}
	}

	while(!chocado && i<juego.cantidad_herramientas){

		if(es_misma_posicion(juego.herramientas[i].posicion, posicion)){

			tipo = juego.obstaculos[i].tipo;
			chocado = true;
		}

		i++;
	}

	return tipo;
}


int indice_herramienta (juego_t juego, coordenada_t posicion){

	bool chocado = false;
	int indice = NO_HAY_ELEMENTO;
	int i = 0;

	while(!chocado && i<juego.cantidad_herramientas){

		if(es_misma_posicion(juego.herramientas[i].posicion, posicion)){
			indice = i;
			chocado = true;
			
		} else {
			i++;
		}
	}

	return indice;
}


bool es_obstaculo (char tipo_elemento){
	return ((tipo_elemento == PIEDRA) || (tipo_elemento == KOALA) || (tipo_elemento == ARBOL) );
}


void aplicar_contratiempo (juego_t* juego, personaje_t* personaje, char contratiempo){

	if (contratiempo == PIEDRA){
		personaje->tiempo_perdido += tropezar_con_piedra(personaje->tipo);

    } else if (contratiempo == ARBOL){
		personaje->tiempo_perdido += trepar_arbol(personaje->tipo);

	} else {
		tropezar_con_sekoalaz(juego, personaje);
	}
}


double tropezar_con_piedra(char tipo_personaje){
	double tiempo_retraso = 0.0;

	if(tipo_personaje!=POLAR){
		tiempo_retraso = TIEMPO_PIEDRA;

	} else {
		tiempo_retraso = TIEMPO_EVADIR_PIEDRA;
	}

	return tiempo_retraso;
}


double trepar_arbol(char tipo_personaje){
	double tiempo_retraso = 0.0;

	if(tipo_personaje!=PARDO){
		tiempo_retraso = TIEMPO_TREPAR;

	} else {
		tiempo_retraso = TIEMPO_TREPAR_RAPIDO;
	}

	return tiempo_retraso;
}


void tropezar_con_sekoalaz (juego_t* juego,personaje_t* personaje){
	char tipo_chocado = '0';
	coordenada_t posicion;

	printf("Sekoalaz Chocado\n");

	if(!esta_columna_ocupada(*juego, COLUMNA_INICIAL)){

		do{
			posicion = posicion_inicial_personaje();

		} while(!esta_posicion_libre(*juego, posicion));

	} else {
		posicion = posicion_aleatoria();

	}

	personaje->posicion = posicion;
}


bool esta_columna_ocupada(juego_t juego, int columna){
	bool ocupada = false;

	int cantidad_posiciones = 0;
	int i = 0;

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

	i = 0;
	
	while(!ocupada && i < juego.cantidad_herramientas){
			
		if(juego.herramientas[i].posicion.col == columna){
			cantidad_posiciones++;
		}

		if(cantidad_posiciones == MAX_FILAS){
			ocupada = true;
		}
		i++;
	}

	return ocupada;
}


void agregar_en_mochila (elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_herramientas , char recolectable){

	if (recolectable == PILA){
		mochila[0].movimientos_restantes+=MOVIMIENTOS_PILAS;

	}else if (recolectable == VELA){

		mochila[*cantidad_herramientas].tipo = VELA;
		mochila[*cantidad_herramientas].movimientos_restantes = MOVIMIENTOS_VELAS;

		(*cantidad_herramientas)++;

	} else {

		mochila[*cantidad_herramientas].tipo = BENGALA;
		mochila[*cantidad_herramientas].movimientos_restantes= DURACION_BENGALAS;

		(*cantidad_herramientas)++;
	}
}


void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice){
	int indice_ultima_herramienta = (*cantidad_herramientas) -1;

	herramientas[indice] = herramientas[indice_ultima_herramienta];
	(*cantidad_herramientas) --;
}


void intentar_iluminar_con(juego_t* juego, char herramienta, int indice_herramienta){

	if((juego->personaje.mochila[indice_herramienta].movimientos_restantes >MIN_MOVIMIENTOS)){
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

			default:

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

	printf("Estoy iluminando hacia la derecha\n");

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

	if ( (distancia_mahattan(posicion_personaje, posicion_elegida))==1){
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
	int indice;

	if (!hay_bengala_activa(juego->personaje, juego->personaje.elemento_en_uso)){

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
	}
	

}


bool hay_bengala_activa (personaje_t personaje, int elemento_en_uso){
	bool bengala = false;

	if((personaje.mochila[elemento_en_uso].tipo==BENGALA)){
		printf("Bengala Activa!\n");
		bengala = true;
	}
	return bengala;
}


int obtener_posicion_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char elemento, int cantidad_herramientas){
	bool encontrado = false;
	int i = 0;
	int indice = NO_HAY_ELEMENTO;

	while(!encontrado){
		
		if((es_herramienta_buscada(mochila[i], elemento)) && (i<cantidad_herramientas) ){
			encontrado = true;
			indice = i;
		} else {
			i++;
		}
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

	if(indice==NO_HAY_ELEMENTO){
		printf("ERROR! Sin pilas.");

	} else{
		juego->personaje.elemento_en_uso = indice;

		agregar_obstaculos(juego, KOALAS_POR_LINTERNA ,KOALA);
		iluminar_con(juego, LINTERNA);

	}
}


void encender_vela(juego_t* juego, int indice){

	if (indice == NO_HAY_ELEMENTO){
		printf("No tienes velas");

	}else {
		juego->personaje.elemento_en_uso = indice;
		iluminar_con(juego,VELA);

	}
}


void encender_bengala(juego_t* juego, int indice){

	if (indice == NO_HAY_ELEMENTO){
		printf("ERROR! Sin bengalas!\n");

	} else{
		iluminar_con(juego,BENGALA);
		juego->personaje.elemento_en_uso = indice;
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

	if(chloe_fue_encontrada(juego) ){

		estado = JUEGO_TERMINADO;

	} else {

		estado = JUEGO_CONTINUA;
	}

	return estado;

}

