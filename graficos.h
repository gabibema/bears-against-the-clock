#ifndef __GRAFICOS_H__
#define __GRAFICOS_H__


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

#define VICTORIA 'V'
#define DERROTA 'D'

#define MAX_FILAS 20
#define MAX_COLUMNAS 30


/*
 * PRE: -
 * POS: Muestra una animación ASCII ART del juego cargando
 */ 
void mostrar_animacion_cargando();

/*
 * PRE: -
 * POS: Muestra todas las jugada válidas
 */ 
void mostrar_opciones();


/*
 * PRE: Evento sea válido, comentario sea ENCENDIDO, NADA o la direccion del movimiento
 * POS: Muestra al usuario un mensaje correspondiente al evento en el juego
 */ 
void mostrar_mensaje_usuario(char evento, char comentario);


/*
 * PRE: -
 * POS: Muestra al usuario el tiempo restante que tiene
 */ 
void mostrar_tiempo(double tiempo);


/*
 * PRE: -
 * POS: Muestra la matriz como un tablero
 */ 
void mostrar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]);


/*
 * PRE: -
 * POS: Muestra los datos actuales del personaje y el juego
 */ 
void mostrar_datos(int cantidad_obstaculos, int cantidad_herramientas, int cantidad_elementos);


/*
 * PRE: Estado sea VICTORIA o DERROTA
 * POS:  Muestra un ASCII ART de acuerdo al estado
 */ 
void mostrar_mensaje_final(char estado);


/*
 * PRE: Estado sea VICTORIA o DERROTA
 * POS: Muestra un ASCII ART de acuerdo al estado
 */ 
void mostrar_imagen_final (char estado);

#endif /* __GRAFICOS_H__ */