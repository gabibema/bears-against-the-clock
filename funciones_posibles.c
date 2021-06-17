#include <stdbool.h>

/*void eliminar_elemento (juego_t* juego, int indice, char tipo_elemento){
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
}*/


/*int indice_elemento (juego_t juego, coordenada_t posicion, char tipo_elemento){
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
}*/


bool es_herramienta (char tipo_elemento){
	return ((tipo_elemento == PILA) || (tipo_elemento==VELA) || (tipo_elemento ==BENGALA) );
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
