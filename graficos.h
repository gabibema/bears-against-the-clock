#ifndef __GRAFICOS_H__
#define __GRAFICOS_H__

#include <stdio.h>

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


#define NEGRO_F "\e[40m"
#define ROJO_F "\e[41m"
#define VERDE_F "\e[42m"
#define AMARILLO_F "\e[43m"
#define AZUL_F "\e[44m"
#define MAGENTA_F "\e[45m"
#define CYAN_F "\e[46m"
#define BLANCO_F "\e[47m"

#define GRIS "\e[90m"
#define ROJO_CLARO "\e[91m"
#define VERDE_CLARO "\e[92m"
#define AMARILLO_CLARO "\e[93m"
#define AZUL_CLARO "\e[94m"
#define MAGENTA_CLARO "\e[95m"
#define CYAN_CLARO "\e[96m"
#define BLANCO_CLARO "\e[97m"

#define GRIS_F "\e[100m"
#define ROJO_CLARO_F "\e[01m"
#define VERDE_CLARO_F "\e[02m"
#define AMARILLO_CLARO_F "\e[03m"
#define AZUL_CLARO_F "\e[04m"
#define MAGENTA_CLARO_F "\e[05m"
#define CYAN_CLARO_F "\e[06m"
#define BLANCO_CLARO_F "\e[07m"

#define ENCENDIDO 'O'
#define MOVERSE 'M'
#define NADA '-'
#define BENGALA_EN_USO 'I'

#define MAX_FILAS 20
#define MAX_COLUMNAS 30


void mostrar_opciones();

void mostrar_mensaje_usuario(char evento, char comentario);

void mostrar_tiempo(double tiempo);

void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]);

void mostrar_datos(int cantidad_obstaculos, int cantidad_herramientas, int cantidad_elementos);

#endif /* __GRAFICOS_H__ */