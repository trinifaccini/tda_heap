#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "pa2m.h"

#define VACIO 0
#define ERROR -1
#define EXITO 0
#define FALSO 0

typedef struct gimanso
{
	size_t dificultad;
	
}gimnasio_t;


// Funcion que COMPARA los gimnasios segun su clave, la cual en este caso es la dif de los gimnasios
int comparar_gimnasios_por_dif(void* gimansio1, void* gimansio2){

    if(!gimansio1 || !gimansio2) return 0;

    if(((gimnasio_t*)gimansio1)->dificultad > ((gimnasio_t*)gimansio2)->dificultad) return 1;

    if(((gimnasio_t*)gimansio1)->dificultad < ((gimnasio_t*)gimansio2)->dificultad) return -1;

    return 0;
}

// Destructor 
void destructor(gimnasio_t* gimnasio_actual){

    free(gimnasio_actual);
}

// Funcion que invoca al destructor 
void invocador_de_destructor(void* elemento){
    if(!elemento)
        return;
    destructor((gimnasio_t*)elemento);
}

/* Funcion que crea los elementos que iran en el árbol */
gimnasio_t * crear_gimnasio(size_t dificultad){

    gimnasio_t * gimnasio = (gimnasio_t*)malloc(sizeof(gimnasio_t));
    if(gimnasio)
    	gimnasio->dificultad = dificultad;

    return gimnasio;
}


int comparador(void* elemento1, void* elemento2){

	if(!elemento1 || !elemento2) return 0;

    if( *(int*)elemento1 > *(int*)elemento2) return 1;

    if( *(int*)elemento1 < *(int*)elemento2) return -1;

    return 0;
}

int main(){

	pa2m_nuevo_grupo("PRUEBAS CON ENTEROS: ");

	int elemento1 = 3;
	int elemento2 = 1;
	int elemento3 = 2;
	int elemento4 = 5;
	int elemento5 = 4;

	heap_t * heap_int = heap_crear(comparador, NULL);

	pa2m_afirmar(heap_vacio(heap_int), "El heap se creo y se encuentra vacio");
	pa2m_afirmar(heap_insertar(heap_int, &elemento1) == EXITO, "Es posible insertar un elemento en un heap que estaba vacio");
	pa2m_afirmar(!heap_vacio(heap_int), "El heap ya no se encuentra vacio");
	printf("\n");

	pa2m_afirmar(heap_elemento_raiz(heap_int) == &elemento1, "El elemento en la raiz es el correcto y coincide con el unico insertado");
	pa2m_afirmar(heap_elementos(heap_int) == 1, "La cantidad de elementos en el heap es 1 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap_int, &elemento2) == EXITO, "Es posible insertar un segundo elemento en el heap");
	pa2m_afirmar((heap_int->vector[0] == &elemento2) && (heap_int->vector[1] == &elemento1), "ORDEN CORRECTO (2)"); //aca estoy chequeando la raiz
	pa2m_afirmar(heap_elementos(heap_int) == 2, "La cantidad de elementos en el heap es 2 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap_int, &elemento3) == EXITO, "Es posible insertar un tercer elemento en el heap");
	pa2m_afirmar((heap_int->vector[0] == &elemento2) && (heap_int->vector[1] == &elemento1) && (heap_int->vector[2] == &elemento3), "ORDEN CORRECTO (3)");
	pa2m_afirmar(heap_elementos(heap_int) == 3, "La cantidad de elementos en el heap es 3 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap_int, &elemento4) == EXITO, "Es posible insertar un cuarto elemento en el heap");
	pa2m_afirmar((heap_int->vector[0] == &elemento2) && (heap_int->vector[1] == &elemento1) && (heap_int->vector[2] == &elemento3) && (heap_int->vector[3] == &elemento4), "ORDEN CORRECTO (4)");
	pa2m_afirmar(heap_elementos(heap_int) == 4, "La cantidad de elementos en el heap es 4 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap_int, &elemento5) == EXITO, "Es posible insertar un quinto elemento en el heap");
	pa2m_afirmar((heap_int->vector[0] == &elemento2) && (heap_int->vector[1] == &elemento1) && (heap_int->vector[2] == &elemento3) && (heap_int->vector[3] == &elemento4) && (heap_int->vector[4] == &elemento5), "ORDEN CORRECTO (5)");
	pa2m_afirmar(heap_elementos(heap_int) == 5, "La cantidad de elementos en el heap es 5 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap_int) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap_int) == 4, "La cantidad de elementos en el heap es 4 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap_int) == &elemento3, "El elemento en la raiz es el correcto luego de eliminar la raiz anterior (numero 2)");
	printf("\n");


	pa2m_afirmar(heap_borrar_raiz(heap_int) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap_int) == 3, "La cantidad de elementos en el heap es 3 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap_int) == &elemento1, "El elemento en la raiz es el correcto luego de eliminar la raiz anterior (numero 3)");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap_int) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap_int) == 2, "La cantidad de elementos en el heap es 2 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap_int) == &elemento5, "El elemento en la raiz es el correcto luego de eliminar la raiz anterior (numero 4)");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap_int) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap_int) == 1, "La cantidad de elementos en el heap es 1 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap_int) == &elemento4, "El elemento en la raiz es el correcto luego de eliminar la raiz anterior (numero 5)");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap_int) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_vacio(heap_int), "El heap se encuentra nuevamente vacio");
	printf("\n");

	heap_destruir(heap_int);

	pa2m_nuevo_grupo("PRUEBAS CON ''GIMNASIOS'': ");

	gimnasio_t * gimnasio1 = crear_gimnasio(3);
	gimnasio_t * gimnasio2 = crear_gimnasio(1);
	gimnasio_t * gimnasio3 = crear_gimnasio(2);
	gimnasio_t * gimnasio4 = crear_gimnasio(5);
	gimnasio_t * gimnasio5 = crear_gimnasio(4);

	heap_t * heap = heap_crear(comparar_gimnasios_por_dif, invocador_de_destructor);

	pa2m_afirmar(heap_vacio(heap), "El heap se creo y se encuentra vacio");
	pa2m_afirmar(heap_insertar(heap, gimnasio1) == EXITO, "Es posible insertar un gimnasio en un heap que estaba vacio");
	pa2m_afirmar(!heap_vacio(heap), "El heap ya no se encuentra vacio");
	printf("\n");

	pa2m_afirmar(heap_elemento_raiz(heap) == gimnasio1, "El gimnasio en la raiz es el correcto y coincide con el unico insertado");
	pa2m_afirmar(heap_elementos(heap) == 1, "La cantidad de gimnasios en el heap es 1 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap, gimnasio2) == EXITO, "Es posible insertar un segundo gimnasio en el heap");
	pa2m_afirmar((heap->vector[0] == gimnasio2) && (heap->vector[1] == gimnasio1), "ORDEN CORRECTO (2)"); //aca estoy chequeando la raiz
	pa2m_afirmar(heap_elementos(heap) == 2, "La cantidad de gimnasios en el heap es 2 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap, gimnasio3) == EXITO, "Es posible insertar un tercer gimnasio en el heap");
	pa2m_afirmar((heap->vector[0] == gimnasio2) && (heap->vector[1] == gimnasio1) && (heap->vector[2] == gimnasio3), "ORDEN CORRECTO (3)");
	pa2m_afirmar(heap_elementos(heap) == 3, "La cantidad de gimnasios en el heap es 3 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap, gimnasio4) == EXITO, "Es posible insertar un cuarto gimnasio en el heap");
	pa2m_afirmar((heap->vector[0] == gimnasio2) && (heap->vector[1] == gimnasio1) && (heap->vector[2] == gimnasio3) && (heap->vector[3] == gimnasio4), "ORDEN CORRECTO (4)");
	pa2m_afirmar(heap_elementos(heap) == 4, "La cantidad de gimnasios en el heap es 4 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_insertar(heap, gimnasio5) == EXITO, "Es posible insertar un quinto gimnasio en el heap");
	pa2m_afirmar((heap->vector[0] == gimnasio2) && (heap->vector[1] == gimnasio1) && (heap->vector[2] == gimnasio3) && (heap->vector[3] == gimnasio4) && (heap->vector[4] == gimnasio5), "ORDEN CORRECTO (5)");
	pa2m_afirmar(heap_elementos(heap) == 5, "La cantidad de gimnasios en el heap es 5 y es correcta");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap) == 4, "La cantidad de gimnasios en el heap es 4 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap) == gimnasio3, "El gimnasio en la raiz es el correcto luego de eliminar la raiz anterior (numero 2)");
	printf("\n");


	pa2m_afirmar(heap_borrar_raiz(heap) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap) == 3, "La cantidad de gimnasios en el heap es 3 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap) == gimnasio1, "El gimnasio en la raiz es el correcto luego de eliminar la raiz anterior (numero 3)");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap) == 2, "La cantidad de gimnasios en el heap es 2 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap) == gimnasio5, "El gimnasio en la raiz es el correcto luego de eliminar la raiz anterior (numero 4)");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_elementos(heap) == 1, "La cantidad de gimnasios en el heap es 1 y es correcta");
	pa2m_afirmar(heap_elemento_raiz(heap) == gimnasio4, "El gimnasio en la raiz es el correcto luego de eliminar la raiz anterior (numero 5)");
	printf("\n");

	pa2m_afirmar(heap_borrar_raiz(heap) == EXITO, "Se pudo quitar la raiz del heap correctamente");
	pa2m_afirmar(heap_vacio(heap), "El heap se encuentra nuevamente vacio");
	printf("\n");

	heap_destruir(heap);


	pa2m_nuevo_grupo("PRUEBAS HEAPIFY Y HEAPSORT WEB: ");

	int vector[] = {5,8,9,20,33,45,1,10};

	printf("Vector antes de ser ordenado como heap\n");
	for(int i = 0; i < n; i++){
		printf("%i ", vector[i]);
	}

	heapsort_web(vector, 8);


	pa2m_nuevo_grupo("PRUEBAS HEAPIFY Y HEAPSORT LUCAS: ");


	return 0;


}