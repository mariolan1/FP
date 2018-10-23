#include <fstream>
#include <iostream>
#include "listapeliculas.h"
#include "checkML.h"


void cargar(tListaPeliculas &lista, bool &ok) {
    ok = true;
    ifstream archivo;
    int num, i = 0;
    string intro;
    tPelicula pelicula;
    lista.contador = 0;
    archivo.open(BD);
    if (!archivo.is_open()) {
        ok = false; 
    }
    else {
        archivo >> num;
        if (num < MAX_PELICULAS) {
            getline(archivo, intro);
            while (i < num) {
                cargar(pelicula, archivo);
                lista.peliculas[i] = new tPelicula(pelicula);
                lista.contador++;
                i++;
            }
        }
    }
} // cargar


void filtrarPorActor(const tListaPeliculas &lista, tListaPeliculas &nueva, tActor actor) {
    tPelicula pelicula;
    for (int i = 0; i < lista.contador; i++) {
        pelicula = *(lista.peliculas[i]);
        if (interviene(pelicula, actor)) {
            nueva.peliculas[nueva.contador] = lista.peliculas[i];
            nueva.contador++;
        }
    }
} // filtrarPorActor


void mostrar(const tListaPeliculas &lista) {
    tPelicula pelicula;
    for (int i = 0; i < lista.contador; i++) {
        pelicula = *(lista.peliculas[i]);
        mostrar(pelicula);
        cout << "---" << endl;
    }
} // mostrar


void ordenarPorGenero(tListaPeliculas &lista) {
    // Ordenación de menor a mayor por selección directa
    for (int i = 0; i < lista.contador - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < lista.contador; j++) {
            if (lista.peliculas[j]->genero < lista.peliculas[menor]->genero) {
                menor = j;
            }
        }
        if (menor > i) {
            tPunteroPelicula tmp;
            tmp = lista.peliculas[i];
            lista.peliculas[i] = lista.peliculas[menor];
            lista.peliculas[menor] = tmp;
        }
    }
} // ordenarPorGenero


void ordenarPorValoracion(tListaPeliculas &lista) {
    // Ordenación de mayor a menor por inserción
    tPunteroPelicula nuevo;
    int pos;
    for (int i = 1; i < lista.contador; i++) {
        nuevo = lista.peliculas[i];
        pos = 0;
        while ((pos < i) && !(lista.peliculas[pos]->valoracion < nuevo->valoracion)) {
            pos++;
        }
        for (int j = i; j > pos; j--) {
            lista.peliculas[j] = lista.peliculas[j - 1];
        }
        lista.peliculas[pos] = nuevo;
    }
} // ordenarPorValoracion


void destruir(tListaPeliculas &lista) {
    for (int i = 0; i < lista.contador; i++) {
        delete lista.peliculas[i];		
    }
    lista.contador = 0;	
} // destruir

