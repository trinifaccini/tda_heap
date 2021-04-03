#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define MAX_ELEMENTOS 100
#define ERROR -1
#define EXITO 0
#define INICIO 0
#define VACIO 0

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){

	if(!comparador) return NULL; 

	heap_t * mi_heap = calloc(1, sizeof(heap_t));
	if(!mi_heap) return NULL;

	mi_heap->cantidad = 0;
	mi_heap->comparador = comparador;
	mi_heap->destructor = destructor;
	mi_heap->dinamico = true;

	return mi_heap;
}

size_t heap_elementos(heap_t* heap){

	if(!heap) return VACIO;
	return heap->cantidad;
}


bool heap_vacio(heap_t* heap){

	return (!heap || (heap_elementos(heap) == VACIO));
}

size_t posicion_padre(size_t n){
	
	return(n-1)/2;
}

size_t posicion_hijo_derecho(size_t n){

	return 2*n+2;
}

size_t posicion_hijo_izquierdo(size_t n){

	return 2*n+1;
}

void swap(void ** vector, size_t i, size_t j){

	if(!vector) return; 
	
	void * aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

void sift_up(heap_t * heap, size_t n){

	if(!heap || n == 0) return; //estoy en la raiz, no es posible subir mas

	size_t padre = posicion_padre(n);

	if(heap->comparador(heap->vector[n], heap->vector[padre]) < 0){

		swap(heap->vector, n, padre);
		sift_up(heap, padre);
	}
}

void sift_down(heap_t * heap, size_t n){

	size_t pos_der = posicion_hijo_derecho(n);
	size_t pos_izq = posicion_hijo_izquierdo(n);
	size_t pos_menor = pos_izq;

	if(pos_izq >= heap->cantidad) return; //sucede al llegar al final del arbol

	if(pos_der < heap->cantidad){
		if(heap->comparador(heap->vector[pos_der], heap->vector[pos_izq]) < 0)
			pos_menor = pos_der;
	}
		
	//en lo anterior busque al menor de sus hijos

	if(heap->comparador(heap->vector[n], heap->vector[pos_menor]) > 0){

		swap(heap->vector, n, pos_menor);
		sift_down(heap, pos_menor);
	}

}

int heap_insertar(heap_t * heap, void * elemento){

	if(!heap || !elemento) return ERROR; 

	void * aux = realloc(heap->vector, sizeof(void*)*(heap->cantidad+1));

	if(!aux) return ERROR;

	heap->cantidad++; 	 //significa que logre agrandar
	heap->vector = aux;  //igualo para que ahora este agrandado
	heap->vector[heap->cantidad-1] = elemento; //pongo el elemento que inserte como el ultimo

	sift_up(heap, heap->cantidad-1);

	return EXITO;

}


int heap_borrar_raiz(heap_t * heap){

	if(heap_vacio(heap)) return ERROR;

	void * aux = heap->vector[0];

	//swap(heap->vector, 0, heap->cantidad-1); 
	heap->vector[0] = heap->vector[heap->cantidad-1];
	heap->cantidad--; 

	if(heap->cantidad > 0){
		sift_down(heap, 0);
	}

	if(heap->destructor) 
		heap->destructor(aux);

	return EXITO;
	
}


void * heap_elemento_raiz(heap_t * heap){

	if(heap_vacio(heap)) return NULL;

	return heap->vector[0];

}


//de lucas

heap_t * heapify(int * vector[], size_t n){

	heap_t * mi_heap = calloc(1, sizeof(heap_t));
	if(!mi_heap) return NULL;

	mi_heap->vector = (void**)vector;
	mi_heap->cantidad = n;
	mi_heap->dinamico = false;

	while(n > 0){

		sift_down(mi_heap,n);
		n--;
	}

	return mi_heap;
}

void heapsort(int * vector[], size_t n){

	heap_t * heap = heapify(vector, n);
	
	heapify(vector, n);

	while(n > 0){
		heap_borrar_raiz(heap);
		n--;
	}

	heap_destruir(heap);
	
}



//de web

void swap_web(int * i, int * j){

	int aux = *i;
	*i = *j;
	*j = aux;
}


void heapify_web(int vector[], int n, int i){

	int max = i; //inicalizar mas grande como la raiz
	int pos_izq = (int)posicion_hijo_izquierdo((size_t)i);
	int pos_der = (int)posicion_hijo_derecho((size_t)i);

	//si el hijo izquiero es mas grande que la raiz
	if(pos_izq < n && vector[pos_izq] > vector[max])
		max = pos_izq;

	//si el hijo derecho es mas grande que el mas grande
	if(pos_der < n && vector[pos_der] > vector[max])
		max = pos_der;

	//si el mas grande NO ES la raiz
	if(max != i){
		swap_web(&vector[i] , &vector[max]);
		//llamada recursiva
		heapify_web(vector, n, max);
	}
}

void heapsort_web(int vector[], int n){

	//construir heap primero
	for(int i = n / 2 -1; i > 0; i--){
		heapify_web(vector, n, i);
	}

	printf("\n");
	printf("Vector luego de ser ordenado como heap\n");
	for(int i = 0; i < n; i++){
		printf("%i ", vector[i]);
	}

	//voy extrayendo uno por uno
	for(int i = n - 1; i > 0; i--){

		//move la raiz al final del vector
		swap_web(&vector[0], &vector[i]);
		heapify_web(vector, i, 0);
	}

	printf("\n");
	printf("Vector luego de ser ordenado\n");
	for(int i = 0; i < n; i++){
		printf("%i ", vector[i]);
	}
}


void heap_destruir(heap_t * heap){

	if(!heap) return;

	if(heap->dinamico){

		if(heap->destructor){
			for(int i = 0; i < heap->cantidad; i++){
				heap->destructor(heap->vector[i]);
			}
		}
	
	free(heap->vector);

	}

	free(heap);
}

