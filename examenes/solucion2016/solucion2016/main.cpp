#include <iostream>
#include "reparto.h"
#include "pelicula.h"
#include "listapeliculas.h"
#include "checkML.h"


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    tListaPeliculas lista;
    tListaPeliculas nueva;
	tPunteroPelicula p;
	tArrayPunteros a;
    bool ok = false;
    tActor actor;
    cargar(lista, ok);
    if (ok) {
        cout << "Introduce actor: ";
        cin.sync();
        getline(cin, actor.nombre);
        cout << endl;
        nueva.contador = 0;
        filtrarPorActor(lista, nueva, actor);
		ordenarPorValoracion(nueva);
		ordenarPorGenero(nueva);
        mostrar(nueva);
        destruir(lista);
    }
    else {
        cout << "Error al cargar la lista de peliculas." << endl;
    }
    system("pause");
    return 0;
} // main
