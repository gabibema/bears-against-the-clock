#include "test_de_personalidad.h"
#include <stdio.h>
#include <stdbool.h>
#include "graficos.h"
#include <stdlib.h>
#include <unistd.h>


static const char POLAR = 'I';
static const char PANDA = 'P';
static const char PARDO = 'G';

const char LIMPIEZA = 'L';
const char ANIME = 'A';
const char MUSICA_POP = 'M';

const char FOCAS = 'F';
const char BAMBU = 'B';
const char PESCADO = 'P';

const char BIENVENIDA = 'B';
const char DESPEDIDA = 'D';

const int PISO_MAS_BAJO = 1;
const int PISO_MAS_ALTO = 18;

const int GRITO_MINIMO = 1;
const int GRITO_MAXIMO = 18;

const int MULTIPLICADOR_LIMPIEZA=1;
const int MULTIPLICADOR_ANIME=2;
const int MULTIPLICADOR_MUSICA_POP=3;

const int PUNTAJE_FOCAS = 3;
const int PUNTAJE_BAMBU = 6;
const int PUNTAJE_PESCADO = 9;

const int PUNTAJE_MINIMO_POLAR = 5;
const int PUNTAJE_MAXIMO_POLAR = 24;
const int PUNTAJE_MINIMO_PANDA = 25;
const int PUNTAJE_MAXIMO_PANDA = 43;

void preguntar_canal_tv (char* canal_tv);
bool es_canal_valido (char canal_tv);

void preguntar_alimento (char* alimento);
bool es_canal_valido (char canal_tv);

void preguntar_alimento (char* alimento);
bool es_alimento_valido (char alimento);

void preguntar_piso_torre (int* piso_torre);
bool es_piso_torre_valido (int piso_torre);

void preguntar_fuerza_grito (int* fuerza_grito);
bool es_fuerza_grito_valida (int fuerza_grito);

int obtener_multiplicador_canal (char canal_elegido);
int obtener_puntaje_alimento (char alimento);
int calcular_puntaje_total (int piso_torre, int fuerza_grito, char canal, char  alimento);

bool es_polar (int puntaje);
bool es_panda (int puntaje);

void test_de_personalidad(char* personalidad_detectada);
void mostrar_personalidad_escandalosa (int puntaje_total);

/* 
 *PRE: -
 * POS: Muestra el título del test de personalidad
 */
void mostrar_titulo_test(){
	printf("\t\t\t\t\t\t\t\t"AMARILLO"╔══════════════════════╗\n");
    printf("\t\t\t\t\t\t\t\t║"NORMAL" TEST DE PERSONALIDAD "AMARILLO"║\n");
    printf("\t\t\t\t\t\t\t\t╚══════════════════════╝"NORMAL"\n\n\n");

}

/*
 * PRE: -
 * POS: La variable asociada se modificará a ANIME, MUSICA_POP o LIMPIEZA.
 */

void preguntar_canal_tv (char* canal_tv){

	printf("Vas a ver televisión un rato, pones el canal de Anime (%c), Musica Pop (%c) o Limpieza (%c): ", ANIME, MUSICA_POP, LIMPIEZA);
	scanf(" %c", canal_tv);
	
	while ( !(es_canal_valido(*canal_tv)) ){
		printf("ERROR!!! Polar está furioso, ingresa un canal válido o Polar no se calmará: ");
		scanf(" %c", canal_tv);
	}
}

/*
 * PRE: -
 * POS: Devuelve True si el canal_tv es ANIME, MUSICA_POP o LIMPIEZA. 
 * 		Devuelve False en caso contrario.
 */

bool es_canal_valido (char canal_tv){
	return ( (canal_tv == ANIME) || (canal_tv == MUSICA_POP) || (canal_tv == LIMPIEZA) );
}

/*
 * PRE: -
 * POS: Modifica la variable por FOCAS, BAMBU o PESCADO
 */

void preguntar_alimento (char* alimento){

	printf("\n\nSolo podes guardar un alimento en tu vianda: Bambú (%c), Pescado (%c), Focas (%c): ", BAMBU, PESCADO, FOCAS);
	scanf(" %c", alimento);
	
	while ( !(es_alimento_valido(*alimento)) ){
		printf("ERROR!!! Polar está furioso! Ingresa un alimento válido o Polar no se calmará: ");
		scanf(" %c", alimento);
	}
}

/*
 * PRE: -
 * POS: Devuelve True si el alimento es BAMBU, PESCADO o FOCAS. 
 * 		Devuelve False en caso contrario.
 */

bool es_alimento_valido (char alimento){
	return ( (alimento == BAMBU) || (alimento == PESCADO) || (alimento == FOCAS) );
}

/*
 * PRE: - 
 * POS: Modifica variable asociada por un valor entre PISO_MAS_BAJO y PISO_MAS_ALTO.
 */

void preguntar_piso_torre (int* piso_torre){

	printf ("\n\nTe compras una torre con tus dos hermanos de %i pisos. ¿En que piso te gustaría vivir? ", PISO_MAS_ALTO);
	scanf(" %i", piso_torre);
	
	while ( !(es_piso_torre_valido(*piso_torre)) ){
		printf("ERROR!!! Polar está furioso! Ingresa un piso válido (%i a %i) o Polar no se calmará: ", PISO_MAS_BAJO, PISO_MAS_ALTO);
		scanf(" %i", piso_torre);
	}

}

/*
 * PRE: -
 * POS: Devuelve True si piso_torre está entre PISO_MAS_BAJO y PISO_MAS_ALTO.
 * 		Devuelve False en caso contrario.
 */

bool es_piso_torre_valido (int piso_torre){
	return ( (piso_torre>=PISO_MAS_BAJO) && (piso_torre<=PISO_MAS_ALTO) );
}

/*
 * PRE: -
 * POS: La variable asociada tendrá un valor entre GRITO_MINIMO y GRITO_MAXIMO.
 */

void preguntar_fuerza_grito (int* fuerza_grito){

	printf("\n\n¡Oh, una rata! ¿Qué tan fuerte gritas del %i al %i? Siendo 1 no gritar y 18 desgarrarse la garganta: ", GRITO_MINIMO, GRITO_MAXIMO);
	scanf(" %i", fuerza_grito);

	while ( !(es_fuerza_grito_valida(*fuerza_grito)) ){
		printf("ERROR!!! Ningún escandaloso puede descifrar lo que hiciste, el grito debe ser entre %i a %i: ", GRITO_MINIMO, GRITO_MAXIMO);
		scanf(" %i", fuerza_grito);
	}
}

/*
 * PRE: -
 * POS: Devuelve True si fuerza_grito está entre GRITO_MINIMO y GRITO_MAXIMO.
 * 		Devuelve False en caso contrario.
 */

bool es_fuerza_grito_valida (int fuerza_grito){
	return ( (fuerza_grito>=GRITO_MINIMO) && (fuerza_grito<=GRITO_MAXIMO) );
}

/*
 * PRE: Canal_elegido sea LIMPIEZA, ANIME o MUSICA_POP
 * POS: Devuelve un entero correspondiente al multiplicador del canal_elegido
 */

int obtener_multiplicador_canal (char canal_elegido){

	int multiplicador_canal = 0;

	if ( (canal_elegido==LIMPIEZA) ){
		multiplicador_canal = MULTIPLICADOR_LIMPIEZA;
	} else if ( (canal_elegido==ANIME) ){
		multiplicador_canal = MULTIPLICADOR_ANIME;
	} else {
		multiplicador_canal = MULTIPLICADOR_MUSICA_POP;
	}

	return multiplicador_canal;
}

/*
 * PRE: Alimento sea FOCAS, BAMBU o PESCADO
 * POS: Devuelve el puntaje correspondiente a cada alimento
 */

int obtener_puntaje_alimento (char alimento){
	
	int puntaje_alimento = 0;

	if ( (alimento == FOCAS) ){
		puntaje_alimento = PUNTAJE_FOCAS;
	} else if ( (alimento == BAMBU) ){
		puntaje_alimento = PUNTAJE_BAMBU;
	} else {
		puntaje_alimento = PUNTAJE_PESCADO;
	}

	return puntaje_alimento;

}

/*
 * PRE: Piso_torre esté entre PISO_MAS_BAJO y PISO_MAS_ALTO .
 *		Fuerza_grito esté entre GRITO_MINIMO y GRITO_MAXIMO.
 *		Multiplicador de canal sea MULTIPLICADOR_LIMPIEZA, MULTIPLICADOR_MUSICA_POP o MULTIPLICADOR_ANIME.
 *		Puntaje_alimento sea PUNTAJE_FOCAS, PUNTAJE_BAMBU o PUNTAJE_PESCADO.
 * POS:	Devuelve un puntaje entre 5 y 63.
 */

int calcular_puntaje_total (int piso_torre, int fuerza_grito, char canal, char alimento){

	int multiplicador_canal_tv = obtener_multiplicador_canal(canal);
	int puntaje_alimento = obtener_puntaje_alimento(alimento);

	int puntaje_total = (puntaje_alimento * multiplicador_canal_tv) + piso_torre + fuerza_grito;

	return puntaje_total;

}

bool es_polar (int puntaje_total){
	return ( (puntaje_total >= PUNTAJE_MINIMO_POLAR ) && (puntaje_total <= PUNTAJE_MAXIMO_POLAR) );
}

bool es_panda (int puntaje_total){
	return ( (puntaje_total >= PUNTAJE_MINIMO_PANDA ) && (puntaje_total <= PUNTAJE_MAXIMO_PANDA ) );
}

/*
 * PRE: Puntaje total sea mayoro o igual a 0 y menor o igual a 63
 * POS: Imprime por pantalla el personaje coincidente con el usuario.
 */

void mostrar_personalidad_escandalosa (int puntaje_total) {


	printf("\n ---------- Después de un arduo análisis con un puntaje de %i , se determinó que la personalidad más adecuada para definirte es ------------ \n\n", puntaje_total);

	if ( es_polar(puntaje_total) ){

		printf("- Polar (%c) -  Alonzo Corazón de tigre\n\n\tSos el menor de los tres hermanos, casi siempre estás en tu mundo y no decís una palabra. Pero aunque seas un oso de pocas palabras, no hay que subestimarte. \n\tPosees un montón de talentos ocultos y sueles hacer todo el trabajo sucio de los osos. \n\tTe dan miedo los pepinos.\n\n", POLAR);
		
	} else if ( es_panda(puntaje_total) ){

		printf (" - Panda (%c) - \n\n\tSos el hermano del medio y no te parecés en nada a tus hermanos. A ellos les gusta bailar, vos te quedas contra la pared. \n\tEllos comen carne, vos sos vegetariano. Participas voluntariamente en casi todas las ideas de Pardo, aunque seas un poco más inteligente. \n\tY como dice Pardo, sos el vínculo que une a tus hermanos.\n\n", PANDA);

	} else {

		printf(" - Pardo (%c) - \n\n\tSos el mayor de los hermanos, un líder carismático, alegre y muy motivado. \n\tA lo mejor comiste pintura siendo osezno, nadie lo sabe. \n\tTe encanta divertirte y no tomarte nunca la vida demasiado en serio.\n\n", PARDO);
	}

}


/*
 * PRE: -
 * POS: Pide un carácter al usuario
 */
void pedir_caracter_continuar(char* caracter){
	printf("Ingrea cualquier carácter para continuar: ");
	scanf(" %c", caracter);
}
void test_de_personalidad(char* personalidad_detectada){

	char canal = '0';
	char alimento = '0';
	char continuar;

	int piso_torre = 0;
	int fuerza_grito = 0;

	system("clear");

	mostrar_titulo_test();

	preguntar_canal_tv(&canal);
	preguntar_alimento(&alimento);
	preguntar_piso_torre(&piso_torre);
	preguntar_fuerza_grito(&fuerza_grito);


	int puntaje_total = calcular_puntaje_total (piso_torre,fuerza_grito, canal ,alimento);

	if ( es_polar(puntaje_total) ){
		(* personalidad_detectada) = POLAR;
		
	} else if ( es_panda(puntaje_total) ){
		(*personalidad_detectada) = PANDA;

	} else {
		(* personalidad_detectada) = PARDO;
	}

	mostrar_personalidad_escandalosa(puntaje_total);

	pedir_caracter_continuar(&continuar);
}