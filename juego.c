#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <time.h> 
#include "test_de_personalidad.h"
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

#define MAX_OBSTACULOS 600
#define MAX_HERRAMIENTAS 600
#define MAX_FILAS 20
#define MAX_COLUMNAS 30

const int FILA_MINIMA = 0;
const int COLUMNA_MINIMA = 0;


const char ARBOL= 'A';
const char PIEDRA= 'R';
const char KOALAS= 'K';
const char LINTERNA= 'L';
#define VELA 'V'
#define BENGALA 'E'
#define PILA 'B'

const char POLAR= 'I';
const char PARDO= 'G';
const char PANDA= 'P';
const char CHLOE= 'C';

const int MAX_ARBOLES_NORMAL = 350;
const int MAX_PIEDRAS_NORMAL = 80;

const int MAX_PILAS_NORMAL = 30;
const int MAX_VELAS_NORMAL = 30;
const int MAX_BENGALAS_NORMAL = 10;


const int MOVIMIENTOS_LINTERNA_EXPERTO = 15;
const int MOVIMIENTOS_LINTERNA_NORMAL = 10;

const int CANTIDAD_VELAS_YOGA = 6;
const int CANTIDAD_VELAS_NORMAL = 4; 
const int MOVIEMIENTOS_VELAS = 5;

const int CANTIDAD_BENGALAS_FIESTA = 2;
const int CANTIDAD_BENGALAS_NORMAL = 0;
const int DURACION_BENGALAS = 3;
const int MAX_RANGO_BENGALA = 2;
const int KOALAS_POR_LINTERNA = 1;

const char VACIO = '-';
const int COLUMNA_INICIAL = 0;

const int JUEGO_CONTINUA = 0;
const int JUEGO_TERMINADO = -1;

const double TIEMPO_TOTAL = 120.0;

bool VISIBILIDAD_DEFECTO = false;

const int SIN_ELEMENTOS_EN_USO = -1;
const int NO_HAY_ELEMENTO = -1;
const int MIN_MOVIMIENTOS = 0;

#define MOVERSE_ARRIBA 'W'
#define MOVERSE_IZQUIERDA 'A'
#define MOVERSE_DERECHA 'D'
#define MOVERSE_ABAJO 'S'
#define ENCENDER_LINTERNA 'L'
#define ENCENDER_VELA 'V'
#define ENCENDER_BENGALA 'E'
#define TIEMPO_RESTANTE 'T'


typedef struct coordenada { 
	int fil;
	int col; 
} coordenada_t;

typedef struct elemento_del_mapa { 
	char tipo;
	coordenada_t posicion; 
	bool visible;
} elemento_del_mapa_t;

typedef struct elemento_mochila {
	char tipo;
	int movimientos_restantes;
} elemento_mochila_t;

typedef struct personaje {
	char tipo;
	coordenada_t posicion; 
	elemento_mochila_t mochila[MAX_HERRAMIENTAS];
	int cantidad_elementos;
	int elemento_en_uso;
	double tiempo_perdido;
	char ultimo_movimiento;
} personaje_t;

typedef struct juego {
	elemento_del_mapa_t obstaculos[MAX_OBSTACULOS];
	int cantidad_obstaculos;
	elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS];
	int cantidad_herramientas;
	personaje_t personaje;
	coordenada_t amiga_chloe;
	bool chloe_visible;
} juego_t;

void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]);

void inicializar_juego(juego_t* juego, char tipo_personaje);
void inicializar_matriz (char matriz[MAX_FILAS][MAX_COLUMNAS]);
void inicializar_personaje(juego_t* juego, char tipo_personaje);
void inicializar_chloe (juego_t* juego);
bool esta_posicion_libre(juego_t juego, coordenada_t posicion);
bool es_misma_posicion(coordenada_t posicion1, coordenada_t posicion2);
void inicializar_obstaculos (juego_t* juego, int cantidad, char tipo);
void inicializar_recolectables (juego_t* juego, int cantidad, char tipo);

coordenada_t posicion_aleatoria();
coordenada_t posicion_inicial_personaje();

void obtener_kit_inicial_personaje(juego_t* juego,char tipo_personaje);
void generar_kit_oso (juego_t* juego, int movimientos_linterna, int cantidad_velas, int movimientos_vela, int cantidad_bengalas, int duracion_bengalas);
void mostrar_juego(juego_t juego);

void pedir_jugada(char* jugada);
bool es_jugada_valida (char jugada);
void realizar_jugada(juego_t* juego, char jugada);
bool se_puede_mover(coordenada_t posicion);
void cargar_posiciones_visibles (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego);
void cargar_posiciones_reales (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego);

int estado_juego(juego_t juego);
bool chloe_fue_encontrada (juego_t juego);


void eliminar_elemento (juego_t* juego, int indice, char tipo_elemento);
void eliminar_obstaculo(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int* cantidad_obstaculos,int indice);
void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice);

int indice_elemento (juego_t juego, coordenada_t posicion, char tipo_elemento);
int indice_obstaculo (juego_t juego, coordenada_t posicion);
int indice_herramienta (juego_t juego, coordenada_t posicion);

bool es_obstaculo (char tipo_elemento);
bool es_herramienta (char tipo_elemento);

void encender_linterna(juego_t* juego, char ultimo_movimiento);
bool esta_arriba_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);
void iluminar_hacia_arriba(juego_t* juego);
bool esta_abajo_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);
void iluminar_hacia_abajo(juego_t* juego);
bool esta_izquierda_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);
void iluminar_hacia_izquierda(juego_t* juego);
bool esta_derecha_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida);
void iluminar_hacia_derecha(juego_t* juego);
void iluminar_con (juego_t* juego, char herramienta);
int obtener_posicion_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char elemento, int cantidad_herramientas);
bool hay_elemento_en_uso (personaje_t personaje);
bool hay_bengala_activa (personaje_t personaje, int elemento_en_uso);
void iluminar_con_bengala(juego_t* juego);
bool es_herramienta_buscada( elemento_mochila_t elemento, char buscado);
void encender_bengala(juego_t* juego);
void encender_vela(juego_t* juego);
bool esta_alrededor(coordenada_t posicion_personaje, coordenada_t posicion_elegida);
void iluminar_alrededor(juego_t* juego);

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


void ocultar_todo (juego_t* juego);

void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]){
	int i,j;

	printf("\n"); 
	printf("   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n"); 
	for ( i = 0; i < MAX_FILAS; i++){
		if (i<=9){
			printf("%i  ", i);
		} else{
			printf("%i ", i);
		}
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
 * Inicializará el juego, cargando toda la información inicial
 * y los datos del personaje. 
 */
void inicializar_juego(juego_t* juego, char tipo_personaje){

	juego->cantidad_obstaculos = 0;
	juego->cantidad_herramientas = 0;
	
	inicializar_personaje(juego, tipo_personaje);
    inicializar_chloe(juego);

	inicializar_obstaculos(juego, MAX_ARBOLES_NORMAL, ARBOL);
	inicializar_obstaculos(juego, MAX_PIEDRAS_NORMAL, PIEDRA);


	inicializar_recolectables(juego, MAX_PILAS_NORMAL, PILA);
	inicializar_recolectables(juego, MAX_VELAS_NORMAL, VELA);
	inicializar_recolectables(juego, MAX_BENGALAS_NORMAL, BENGALA);

	printf("Obstáculos %i\n", juego->cantidad_obstaculos);
	printf("Herramientas %i\n", juego->cantidad_herramientas);
	printf("Cantidad Mochila %i\n", juego->personaje.cantidad_elementos);

	//mostrar_todas_posiciones(*juego);

 
}

/*
 * PRE:
 * POS: 
 */ 
void obtener_kit_inicial_personaje(juego_t* juego,char tipo_personaje){

	if( tipo_personaje == PARDO){
		generar_kit_oso(juego, MOVIMIENTOS_LINTERNA_EXPERTO, CANTIDAD_VELAS_NORMAL, MOVIEMIENTOS_VELAS, CANTIDAD_BENGALAS_NORMAL, DURACION_BENGALAS);

	} else if ( tipo_personaje == POLAR ){
		generar_kit_oso(juego, MOVIMIENTOS_LINTERNA_NORMAL, CANTIDAD_VELAS_YOGA, MOVIEMIENTOS_VELAS, CANTIDAD_BENGALAS_NORMAL, DURACION_BENGALAS);

	} else {
		generar_kit_oso(juego, MOVIMIENTOS_LINTERNA_NORMAL, CANTIDAD_VELAS_NORMAL, MOVIEMIENTOS_VELAS, CANTIDAD_BENGALAS_FIESTA, DURACION_BENGALAS);

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

bool es_misma_posicion(coordenada_t posicion1, coordenada_t posicion2){
	
	return ((posicion1.fil == posicion2.fil) && (posicion1.col == posicion2.col));
	
}

bool esta_posicion_libre(juego_t juego, coordenada_t posicion){
	int i;
	bool esta_libre = true;

	if (es_misma_posicion(juego.personaje.posicion, posicion)){
		esta_libre = false;

	} else if (es_misma_posicion( juego.amiga_chloe, posicion) ){
		esta_libre = false;

	} else {
		i = 0;

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

void inicializar_personaje(juego_t* juego, char tipo_personaje){
	
	juego->personaje.tipo = tipo_personaje;
	juego->personaje.posicion = posicion_inicial_personaje();
	juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;
	juego->personaje.ultimo_movimiento = MOVERSE_DERECHA;

	obtener_kit_inicial_personaje(juego, tipo_personaje);
}

void inicializar_chloe (juego_t* juego){
	do{ 
		juego->amiga_chloe = posicion_aleatoria();

	}  while (es_misma_posicion(juego->personaje.posicion, juego->amiga_chloe));

	juego->chloe_visible = VISIBILIDAD_DEFECTO;

}

void inicializar_obstaculos (juego_t* juego, int cantidad, char tipo){
	int i;
	int cantidad_inicial = juego->cantidad_obstaculos;

	coordenada_t posicion;

	for ( i = cantidad_inicial; i < cantidad + cantidad_inicial; i++){
		juego->obstaculos[i].tipo = tipo; 

		do {
			posicion = posicion_aleatoria();
		} while(!esta_posicion_libre(*juego, posicion ));

		juego->cantidad_obstaculos++;	

		juego->obstaculos[i].posicion = posicion;
		juego->obstaculos[i].visible = VISIBILIDAD_DEFECTO;

	}
}

void inicializar_recolectables (juego_t* juego, int cantidad, char tipo){
	int i;
	int cantidad_inicial = juego->cantidad_herramientas;

	coordenada_t posicion;

	for ( i = cantidad_inicial; i < cantidad + cantidad_inicial; i++){
		juego->herramientas[i].tipo = tipo; 
		juego->cantidad_herramientas++;

		do {
			posicion = posicion_aleatoria();
		} while(!esta_posicion_libre(*juego, posicion));

		juego->herramientas[i].posicion = posicion;	
		juego->herramientas[i].visible = VISIBILIDAD_DEFECTO;


	}	
}

void inicializar_matriz (char matriz[MAX_FILAS][MAX_COLUMNAS]){
	int i, j;

	for ( i = 0; i < MAX_FILAS; i++){
		for ( j = 0; j < MAX_COLUMNAS; j++){
			matriz[i][j] = VACIO;
		}
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
	int estado = 1;

	if( (tiempo_actual()<=0) || chloe_fue_encontrada(juego) ){

		juego.personaje.tiempo_perdido = detener_cronometro();
		estado = JUEGO_TERMINADO;

	} else {

		estado = JUEGO_CONTINUA;
	}

	return estado;


}

bool chloe_fue_encontrada (juego_t juego){
	return ( (juego.personaje.posicion.col == juego.amiga_chloe.col) && ( juego.personaje.posicion.fil == juego.amiga_chloe.fil) );
}

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
	int indice_objeto_chocado = 0;
	int indice_en_uso = juego->personaje.elemento_en_uso;

	char matriz_temporal[MAX_FILAS][MAX_COLUMNAS];
	char elemento_chocado = '0';

	coordenada_t posicion = juego->personaje.posicion;

	inicializar_matriz(matriz_temporal);
	cargar_posiciones_reales(matriz_temporal, *juego);

	switch (jugada){
		case MOVERSE_ARRIBA:
			posicion.fil--;
			if(se_puede_mover(posicion)){ 

				if(esta_posicion_libre(*juego, posicion)){
					juego->personaje.posicion = posicion;
				}

				else {
					juego->personaje.posicion = posicion;
					elemento_chocado = matriz_temporal[posicion.fil][posicion.col];
					indice_objeto_chocado = indice_elemento(*juego, posicion, elemento_chocado);
					eliminar_elemento(juego, indice_objeto_chocado,elemento_chocado);
					
				}

				if (indice_en_uso != SIN_ELEMENTOS_EN_USO){

					if((juego->personaje.mochila[indice_en_uso].movimientos_restantes >MIN_MOVIMIENTOS)){
						ocultar_todo(juego);
						iluminar_con(juego,juego->personaje.mochila[indice_en_uso].tipo);

						juego->personaje.mochila[indice_en_uso].movimientos_restantes--;
						printf("Movimientos restantes de %c : %i indice en uso: %i \n", juego->personaje.mochila[indice_en_uso].tipo, juego->personaje.mochila[indice_en_uso].movimientos_restantes, indice_en_uso );
					} else{
						ocultar_todo(juego);
						juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;

					}

				}

				juego->personaje.ultimo_movimiento = jugada;

			} else {
				printf("Movimiento no posible");
			}
			break;
		case MOVERSE_ABAJO:
			posicion.fil++;
			if(se_puede_mover(posicion)){
				
				if(esta_posicion_libre(*juego, posicion)){
					juego->personaje.posicion = posicion;
				}

				else {
					juego->personaje.posicion = posicion;
					elemento_chocado = matriz_temporal[posicion.fil][posicion.col];
					indice_objeto_chocado = indice_elemento(*juego, posicion, elemento_chocado);
					eliminar_elemento(juego, indice_objeto_chocado,elemento_chocado);
					
				}
				if (indice_en_uso != SIN_ELEMENTOS_EN_USO){

					if((juego->personaje.mochila[indice_en_uso].movimientos_restantes >MIN_MOVIMIENTOS)){
						ocultar_todo(juego);
						iluminar_con(juego,juego->personaje.mochila[indice_en_uso].tipo);

						juego->personaje.mochila[indice_en_uso].movimientos_restantes--;
						printf("Movimientos restantes de %c : %i indice en uso: %i \n", juego->personaje.mochila[indice_en_uso].tipo, juego->personaje.mochila[indice_en_uso].movimientos_restantes, indice_en_uso );
					} else{
						ocultar_todo(juego);
						juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;

				}

			}

				juego->personaje.ultimo_movimiento = jugada;

			} else {
				printf("Movimiento no posible");
			}



			break;

		case MOVERSE_IZQUIERDA:
			posicion.col--;
			if(se_puede_mover(posicion)){ 

				if(esta_posicion_libre(*juego, posicion)){
					juego->personaje.posicion = posicion;
				}

				else {
					juego->personaje.posicion = posicion;
					elemento_chocado = matriz_temporal[posicion.fil][posicion.col];
					indice_objeto_chocado = indice_elemento(*juego, posicion, elemento_chocado);
					eliminar_elemento(juego, indice_objeto_chocado,elemento_chocado);
					
				}

				if (indice_en_uso != SIN_ELEMENTOS_EN_USO){

				
					if((juego->personaje.mochila[indice_en_uso].movimientos_restantes >MIN_MOVIMIENTOS)){
						ocultar_todo(juego);
						iluminar_con(juego,juego->personaje.mochila[indice_en_uso].tipo);

						juego->personaje.mochila[indice_en_uso].movimientos_restantes--;
						printf("Movimientos restantes de %c : %i indice en uso: %i \n", juego->personaje.mochila[indice_en_uso].tipo, juego->personaje.mochila[indice_en_uso].movimientos_restantes, indice_en_uso );
					} else{
						ocultar_todo(juego);
						juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;

					}

				}

				juego->personaje.ultimo_movimiento = jugada;

			} else {
				printf("Movimiento no posible");
			}
			break;

		case MOVERSE_DERECHA:
			posicion.col++;
			if(se_puede_mover(posicion)){ 
				
				if(esta_posicion_libre(*juego, posicion)){
					juego->personaje.posicion = posicion;
				}

				else {
					juego->personaje.posicion = posicion;
					elemento_chocado = matriz_temporal[posicion.fil][posicion.col];
					indice_objeto_chocado = indice_elemento(*juego, posicion, elemento_chocado);
					eliminar_elemento(juego, indice_objeto_chocado,elemento_chocado);
					
				}

				juego->personaje.ultimo_movimiento = jugada;

				if (indice_en_uso != SIN_ELEMENTOS_EN_USO){

					if((juego->personaje.mochila[indice_en_uso].movimientos_restantes >MIN_MOVIMIENTOS)){
						ocultar_todo(juego);
						iluminar_con(juego,juego->personaje.mochila[indice_en_uso].tipo);

						juego->personaje.mochila[indice_en_uso].movimientos_restantes--;
						printf("Movimientos restantes de %c : %i indice en uso: %i \n", juego->personaje.mochila[indice_en_uso].tipo, juego->personaje.mochila[indice_en_uso].movimientos_restantes, indice_en_uso );
					} else{
						ocultar_todo(juego);
						juego->personaje.elemento_en_uso = SIN_ELEMENTOS_EN_USO;
					}
				}
			} else {
				printf("Movimiento no posible");
			}
			break;
		case ENCENDER_LINTERNA:
			if (!hay_bengala_activa(juego->personaje, juego->personaje.elemento_en_uso)){
				if( !hay_elemento_en_uso((juego->personaje)) ){
					inicializar_obstaculos(juego, KOALAS_POR_LINTERNA ,KOALAS);
					encender_linterna(juego, juego->personaje.ultimo_movimiento);
				}	
			}
			break;

		case ENCENDER_VELA:

			if (!hay_bengala_activa(juego->personaje, juego->personaje.elemento_en_uso)){
				if( !hay_elemento_en_uso((juego->personaje)) ){

					encender_vela(juego);
				}	
			}
			break;

		case ENCENDER_BENGALA:

			if (!hay_bengala_activa(juego->personaje, juego->personaje.elemento_en_uso)){
				if( !hay_elemento_en_uso((juego->personaje)) ){

					encender_bengala(juego);
				}	
			}
			break;

		default:
			break;
	}
	
}

void encender_vela(juego_t* juego){
	int indice = obtener_posicion_mochila(juego->personaje.mochila,VELA, juego->personaje.cantidad_elementos);

	if (indice == NO_HAY_ELEMENTO){
		printf("No tienes velas");
	} else {
		iluminar_con(juego,VELA);
		juego->personaje.elemento_en_uso = indice;	
	}
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
bool esta_alrededor(coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	bool alrededor = false;

	if ( (distancia_mahattan(posicion_personaje, posicion_elegida))==1){
		alrededor = true;
	} else if ( ( (distancia_mahattan(posicion_personaje, posicion_elegida))==2) && (estan_en_diagonal(posicion_personaje,posicion_elegida)) ){
		alrededor = true;
	}

	return alrededor;
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

void iluminar_con (juego_t* juego, char herramienta){
	char direccion = '0';

	if(herramienta == LINTERNA){
		direccion = juego->personaje.ultimo_movimiento;

		switch(direccion){
			case MOVERSE_ARRIBA:
		
				iluminar_hacia_arriba(juego);
				break;

			case MOVERSE_ABAJO:
				printf("Iluminar abajo\n");
				iluminar_hacia_abajo(juego);
				break;

			case MOVERSE_IZQUIERDA:
				printf("Iluminar izquierda\n");
				iluminar_hacia_izquierda(juego);
				break;

			case MOVERSE_DERECHA:
				printf("Iluminar derecha\n");
				iluminar_hacia_derecha(juego);

				break;

			default:
				printf("Movimiento default\n");
				iluminar_hacia_derecha(juego);
				break;
		}

	} else if (herramienta == VELA){
		iluminar_alrededor(juego);
	} else {
		iluminar_con_bengala(juego);
	}
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

void encender_bengala(juego_t* juego){
	int indice = obtener_posicion_mochila(juego->personaje.mochila, BENGALA, juego->personaje.cantidad_elementos);

	if (indice == NO_HAY_ELEMENTO){
		printf("ERROR! Sin bengalas!\n");
	} else{
		iluminar_con(juego,BENGALA);
		juego->personaje.elemento_en_uso = indice;
	}
}

void encender_linterna(juego_t* juego, char ultimo_movimiento){
	int indice = obtener_posicion_mochila(juego->personaje.mochila, LINTERNA, juego->personaje.cantidad_elementos);

	if(indice==NO_HAY_ELEMENTO){
		printf("ERROR! Sin pilas.");

	} else{
		iluminar_con(juego, LINTERNA);
		juego->personaje.elemento_en_uso = indice;

	}
}

bool esta_arriba_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col == posicion_personaje.col) && (posicion_elegida.fil < posicion_personaje.fil));
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

bool esta_abajo_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col == posicion_personaje.col) && (posicion_elegida.fil > posicion_personaje.fil));
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

bool esta_derecha_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col > posicion_personaje.col) && (posicion_elegida.fil == posicion_personaje.fil));
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

bool esta_izquierda_de (coordenada_t posicion_personaje, coordenada_t posicion_elegida){
	return ((posicion_elegida.col < posicion_personaje.col) && (posicion_elegida.fil == posicion_personaje.fil));
}

void iluminar_hacia_izquierda(juego_t* juego){
	coordenada_t posicion_personaje = juego->personaje.posicion;
	coordenada_t posicion_chloe = juego->amiga_chloe;
	coordenada_t posicion_elemento;
	int i;

	if (esta_izquierda_de( posicion_personaje, posicion_chloe ) ){
		juego->chloe_visible = true;
	}
	for (i = 0; i < (juego->cantidad_obstaculos); i++){
		posicion_elemento = juego->obstaculos[i].posicion;



		if (esta_izquierda_de(posicion_personaje, posicion_elemento )){
			juego->obstaculos[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",posicion_elemento.fil, posicion_elemento.col);
		}
	
	}
	
	for (i = 0; i < (juego->cantidad_herramientas); i++){
		posicion_elemento = juego->herramientas[i].posicion;
		
		if (esta_izquierda_de(juego->personaje.posicion, posicion_elemento)){
			juego->herramientas[i].visible = true;
			//printf("Se ilumina fil: %i y col: %i\n",posicion_elemento.fil, posicion_elemento.col);
		}
	
	}
}
bool es_herramienta_buscada( elemento_mochila_t elemento, char buscado){
	bool herramienta = false;

	if ((elemento.tipo == buscado) && (elemento.movimientos_restantes > MIN_MOVIMIENTOS)){
		herramienta = true;
	}

	return herramienta;
}

int obtener_posicion_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char elemento, int cantidad_herramientas){
	int i = 0;
	int indice = NO_HAY_ELEMENTO;
	while((!es_herramienta_buscada(mochila[i], elemento)) && (i<cantidad_herramientas) ){
		i++;
	}

	if (mochila[i].tipo == elemento){
		indice = i;
	}

	return indice;
}

bool hay_elemento_en_uso (personaje_t personaje){
	return (personaje.elemento_en_uso!=SIN_ELEMENTOS_EN_USO);
}

bool hay_bengala_activa (personaje_t personaje, int elemento_en_uso){
	bool bengala = false;

	if((personaje.mochila[elemento_en_uso].tipo==BENGALA)&&(personaje.mochila[elemento_en_uso].movimientos_restantes >MIN_MOVIMIENTOS)){
		printf("Bengala Activa!\n");
		bengala = true;
	}
	printf("%d", bengala);
	return bengala;
}
bool se_puede_mover(coordenada_t posicion){
	return ( ( (posicion.fil >= FILA_MINIMA)&&(posicion.fil < MAX_FILAS) ) &&( (posicion.col >= COLUMNA_MINIMA)&&(posicion.col < MAX_COLUMNAS) ) );	
}

void eliminar_elemento (juego_t* juego, int indice, char tipo_elemento){
	if ( es_obstaculo(tipo_elemento) ){
		printf("SE eliminó fil:%i col:%i ", juego->obstaculos[indice].posicion.col,juego->obstaculos[indice].posicion.fil );
		eliminar_obstaculo(juego->obstaculos,&(juego->cantidad_obstaculos), indice);

	} else if ( es_herramienta (tipo_elemento) ){
	
		printf("SE eliminó fil:%i col:%i ", juego->obstaculos[indice].posicion.col,juego->obstaculos[indice].posicion.fil );
		eliminar_herramienta(juego->herramientas ,&(juego->cantidad_herramientas), indice);
	}
}

void eliminar_obstaculo(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int* cantidad_obstaculos,int indice){
	int indice_ultimo_obstaculo = (*cantidad_obstaculos) -1;

	obstaculos[indice] = obstaculos[indice_ultimo_obstaculo];
	(*cantidad_obstaculos) --;
}

void eliminar_herramienta(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas,int indice){
	int indice_ultima_herramienta = (*cantidad_herramientas) -1;

	herramientas[indice] = herramientas[indice_ultima_herramienta];
	(*cantidad_herramientas) --;
}

int indice_elemento (juego_t juego, coordenada_t posicion, char tipo_elemento){
	int indice = 0;


	if (es_obstaculo(tipo_elemento)){

		indice = indice_obstaculo(juego, posicion);

	} else if (es_herramienta(tipo_elemento)){
		indice = indice_herramienta(juego, posicion);
	}

	return indice;


}

int indice_obstaculo (juego_t juego, coordenada_t posicion){
	int indice = 0;
	int i;

	for(i = 0; i < juego.cantidad_obstaculos; i++){
		if ( (juego.obstaculos[i].posicion.fil == posicion.fil) && (juego.obstaculos[i].posicion.col == posicion.col) ){
			indice = i;
		}
	}
	return indice;
}

int indice_herramienta (juego_t juego, coordenada_t posicion){
	int indice = 0;
	int i;

	for(i = 0; i < juego.cantidad_herramientas; i++){
		if ( (juego.herramientas[i].posicion.fil == posicion.fil) && (juego.herramientas[i].posicion.col == posicion.col) ){
			indice = i;
		}
	}	

	return indice;
}


bool es_obstaculo (char tipo_elemento){
	return ((tipo_elemento == PIEDRA) || (tipo_elemento==KOALAS) || (tipo_elemento ==ARBOL) );
}

bool es_herramienta (char tipo_elemento){
	return ((tipo_elemento == PILA) || (tipo_elemento==VELA) || (tipo_elemento ==BENGALA) );
}


void cargar_posiciones_visibles (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego){

	int i;

	tablero[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;
	if(juego.chloe_visible!=VISIBILIDAD_DEFECTO){
		tablero[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
	}

	for (i = 0; i< juego.cantidad_obstaculos; i++){
		if(juego.obstaculos[i].visible!=VISIBILIDAD_DEFECTO){
			tablero[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].tipo;
		}
	}	
	
	for (i = 0; i< juego.cantidad_herramientas; i++){
		if(juego.herramientas[i].visible!=VISIBILIDAD_DEFECTO){
			tablero[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;
		}
	}
}

void cargar_posiciones_reales (char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego){

	int i;

	tablero[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

	tablero[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
	

	for (i = 0; i< juego.cantidad_obstaculos; i++){
		tablero[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].tipo;
	}	
	
	for (i = 0; i< juego.cantidad_herramientas; i++){
		tablero[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;

	}
}

/*

 * Mostrará el juego por pantalla.
 * Se recomienda mostrar todo lo que sea de utilidad para el jugador.
 */
void mostrar_juego(juego_t juego){
	double tiempo = 0;
	char tablero[MAX_FILAS][MAX_COLUMNAS];

	system("clear");

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


	if(juego.personaje.ultimo_movimiento == TIEMPO_RESTANTE){
		tiempo = TIEMPO_TOTAL - juego.personaje.tiempo_perdido;

		printf("TIEMPO RESTANTE: %.2f\n", tiempo);
	}
}

coordenada_t posicion_aleatoria(){
	coordenada_t posicion;
	
	posicion.fil= rand()%MAX_FILAS;
	posicion.col= rand()%MAX_COLUMNAS;

	return posicion;
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




int main(){
	srand ((unsigned)time(NULL));
	char ultima_jugada;
    juego_t juego;
	char personalidad_detectada = PANDA;

    test_de_personalidad(&personalidad_detectada);
    printf("%c\n", personalidad_detectada); 
	
    inicializar_juego(&juego, personalidad_detectada);
	mostrar_juego(juego);
	iniciar_cronometro();

	do{
		juego.personaje.tiempo_perdido = tiempo_actual();
		pedir_jugada(&(ultima_jugada));
		realizar_jugada(&juego, ultima_jugada);
		mostrar_juego(juego);

	} while (estado_juego(juego)!=JUEGO_TERMINADO);

	return 0;
}
