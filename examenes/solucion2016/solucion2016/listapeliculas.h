#include "reparto.h"
#include "pelicula.h"

const int MAX_PELICULAS = 50;
const string BD = "peliculas.txt";

// Puntero a pelicula
typedef tPelicula *tPunteroPelicula;

// Tipo array de punteros a peliculas
typedef tPunteroPelicula tArrayPunteros[MAX_PELICULAS];

// Lista de peliculas: array de punteros y contador
typedef struct {
    tArrayPunteros peliculas;
    int contador;
} tListaPeliculas;


// Carga la lista de peliculas
void cargar(tListaPeliculas &lista, bool &ok);

// Filtra una lista de peliculas por actor
void filtrarPorActor(const tListaPeliculas &lista, tListaPeliculas &nueva, tActor actor);

// Muestra la información de una lista de películas
void mostrar(const tListaPeliculas &lista);

// Ordena por genero una lista de peliculas
void ordenarPorGenero(tListaPeliculas &lista);

// Ordena por valoración una lista de peliculas
void ordenarPorValoracion(tListaPeliculas &lista);

// Libera la memoria dinámica utilizada
void destruir(tListaPeliculas &lista);
