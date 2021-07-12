
#define NORMAL "\e[0m"
#define SUBRAYADO "\e[4m"

#define NEGRO "\e[30m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define AZUL "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define BLANCO "\e[37m"

#define SEPARADOR_1_INICIO "\t\t\t"AMARILLO"╔══════════════════════════════════════════╗"AMARILLO"\n"
#define SEPARADOR_1_FIN "\t\t\t"AMARILLO"╚══════════════════════════════════════════╝"AMARILLO"\n"
#define SEPARADOR_MENSAJE "〔═▲═〕"

#define MAX_MENSAJE 256

#define VACIO '-'
#define POLAR 'I'
#define PARDO 'G'
#define PANDA 'P'
#define CHLOE 'C'

#define KOALA 'K'
#define LINTERNA 'L'
#define VELA  'V'
#define BENGALA  'E'



#include <stdio.h>
#include <string.h>
#include "graficos.h"


void mostrar_opciones(){
    
	printf(AMARILLO "┏┳┳┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┓\n");
    printf("┋┋┋                I N G R E S A\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┛\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┓\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" W: Para moverte arriba"AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" A: Para moverte a la izquierda"AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" S: Para moverte abajo"AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" D: Para moverte a la derecha"AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" L: Para encender una linterna "AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" V: Para encender una vela  "AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" E: Para encender la bengala"AMARILLO"\n");
    printf("┋┋┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅"AMARILLO"\n");
    printf("┋┋┋    ◉ᐅ"NORMAL" T: Para ver el tiempo restante"AMARILLO"\n");
    printf("┗┻┻┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┛\n" NORMAL);

}

void mostrar_mensaje_usuario(char evento, char comentario){


    if (comentario == ENCENDIDO){

        if (evento == LINTERNA){

            printf(" %s\t\t\t%s ¡Linterna ENCENDIDA! %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);

        } else if (evento == VELA){

            printf(" %s\t\t\t%s ¡Vela Encendida! %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);

        } else{

            printf(" %s\t\t\t%s ¡Bengala Encendida! %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
        }

    } else if (comentario == NADA){

        if (evento == KOALA){

            printf(" %s\t\t\t     %s ¡Sekoalaz chocado! %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);

        } else if (evento == LINTERNA){    
            
            printf(" %s\t\t\t%s ¡ERROR! No te quedan pilas %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
            
        } else if (evento == VELA){    
            
            printf(" %s\t\t\t%s ¡ERROR! No tienes velas %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
            
        } else if (evento == BENGALA){   

            printf(" %s\t\t\t%s ¡ERROR! No tienes bengalas %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
        } else {

            printf(" %s\t\t\t%s ¡ERROR! Movimiento no posible%s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);

        }

    } else {
        printf(" %s\t\t\t%s Movimiento realizado: [%c] %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE, comentario, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
    }

}


void mostrar_tiempo(double tiempo){
    
    printf(" %s\t\t\t%s TIEMPO RESTANTE: %.2f %s\n %s\n", SEPARADOR_1_INICIO, SEPARADOR_MENSAJE,tiempo, SEPARADOR_MENSAJE, SEPARADOR_1_FIN);
}

void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]){
	int i, j;

	printf("\t\t\t\t\t%s╔═════════════════════════════════════════════════════════════════╗%s\n",CYAN,NORMAL);
	printf("\t\t\t\t\t%s║                                                                 ║%s\n",CYAN,NORMAL);
	//printf("\t\t\t\t║     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9  ║\n"); 
	for ( i = 0; i < MAX_FILAS; i++){
		printf("\t\t\t\t\t%s║   %s",CYAN,NORMAL);
		
		for ( j = 0; j < MAX_COLUMNAS; j++){
			if (matriz[i][j] == VACIO){
				printf("· ");
			}else if(matriz[i][j] == PARDO){
				printf("%s%s%c%s ",ROJO_CLARO, CYAN_F, matriz[i][j],NORMAL );				
			}
			else if(matriz[i][j] == POLAR){
				printf("%s%s%c%s ",ROJO_CLARO, CYAN_F, matriz[i][j] ,NORMAL );				
			}
			else if(matriz[i][j] == PANDA){
				printf("%s%s%c%s ",ROJO_CLARO, CYAN_F, matriz[i][j],NORMAL );				
			}

			else if(matriz[i][j] == CHLOE){
				printf("%s%s%c%s ",VERDE_CLARO, MAGENTA_F,matriz[i][j],NORMAL );				
			}
			else {
				printf("%c ", matriz[i][j]);
			}
		}
		printf("%s  ║ %s\n",CYAN,NORMAL);

	} 
	printf("\t\t\t\t\t%s║                                                                 ║%s\n",CYAN,NORMAL);
	printf("\t\t\t\t\t%s╚═════════════════════════════════════════════════════════════════╝%s\n",CYAN,NORMAL);
}


//╗ ═ ╝║ ╔  ╚
void mostrar_datos(int cantidad_obstaculos, int cantidad_herramientas, int cantidad_elementos, char tipo, int fil, int col){

    printf("\t\t\t\t\t\t\t\t╔═══════════════════╗\n");
    printf("\t\t\t\t\t\t\t\t║ OSOS CONTRA RELOJ ║\n");
    printf("\t\t\t\t\t\t\t\t╚═══════════════════╝\n");

    printf("\t\t\t\t\t\t    ╔════════════════════════════════════════╗\n");
	printf("\t\t\t\t\t\t    ║ Para ganar debes encontrar a Chloe (%s%s%c%s) ║\n",VERDE_CLARO, MAGENTA_F,CHLOE,NORMAL );
    printf("\t\t\t\t\t\t    ╚════════════════════════════════════════╝\n");
    printf(VERDE_CLARO" >>>>>"NORMAL" Cantidad de Obstáculos:  "ROJO"%i"VERDE_CLARO" <<<<<\n"NORMAL, cantidad_obstaculos);
	printf(VERDE_CLARO" >>>>>"NORMAL" Cantidad de Herramientas: "ROJO"%i"VERDE_CLARO" <<<<<\n"NORMAL, cantidad_herramientas);
	printf(VERDE_CLARO" >>>>>"NORMAL" Herramientas en Mochila:   "ROJO"%i"VERDE_CLARO" <<<<<\n"NORMAL, cantidad_elementos);


}