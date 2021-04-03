#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stddef.h>

/* Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo */
typedef int (*heap_comparador)(void*, void*);

/* Destructor de elementos. */
typedef void (*heap_liberar_elemento)(void*);


typedef struct {
	size_t cantidad;
	void** vector;
	heap_comparador comparador;
	heap_liberar_elemento destructor;
	bool dinamico;

}heap_t;


/* 
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del heap,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);


/*
 * Devolvera la cantidad de elementos que contiene
 * el heap o 0 si este no existe. 
 */
size_t heap_elementos(heap_t* heap);


/*
 * Devolvera true si el heap está vacio o si
 * no existe. False en caso de contenes 1 o 
 * mas elementos.
 */
bool heap_vacio(heap_t* heap);


/* 
 * Inserta un elemento en el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */

int heap_insertar(heap_t * heap, void * elemento);


/*
 * Borra la raiz del heap, liverando la memoria
 * que se habia reservado para esta.
 */
int heap_borrar_raiz(heap_t * heap);


/* 
 * Devuelve el elemento almacenado como raiz o NULL si el 
 * heap está  vacio
 */
void * heap_elemento_raiz(heap_t * heap);


heap_t * heapify(int * vector[], size_t n);


void heapsort(int * vector[], size_t n);


void heapify_web(int vector[], int n, int i);


void heapsort_web(int vector[], int n);


/*
 * Destruye el heap liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el heap.
 */
void heap_destruir(heap_t * heap);

#endif /* __LISTA_H__ */




