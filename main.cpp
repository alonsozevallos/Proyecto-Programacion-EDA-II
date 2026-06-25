#include "avl.h"
#include "hash Chaining.h"
#include "estudiante.h"

#include <iostream>

int main() {
    Estudiante estudiante;
    estudiante.mostrar_informacion();
    imprimir_avl();
    HashTable tabla_hash;
    tabla_hash.mostrar();
    std::cout << "" << std::endl;
    tabla_hash.buscar("CS1299");
    std::cout << "" << std::endl;
    tabla_hash.eliminar("CS1299");

    return 0;
}