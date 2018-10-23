#ifndef reparto_h
#define reparto_h
#include <string>
#include <fstream>
#include <fstream>
using namespace std;

const int MAX_ACTORES = 10;

// Estructura de un actor
typedef struct {
    string nombre;
} tActor;

// Tipo array de actores
typedef tActor tArrayActores[MAX_ACTORES];

// Lista de actores: array y contador
typedef struct {
    tArrayActores actores;
    int contador;
} tReparto;


// Carga un reparto
void cargar(tReparto &reparto, ifstream &archivo);

// Localiza un actor en un reparto a partir de una posición
void aparece(const tReparto &reparto, bool &existe, tActor actor, int pos);

#endif
