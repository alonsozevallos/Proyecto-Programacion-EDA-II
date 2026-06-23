#include "avl.h"
#include "hash Chaining.h"
#include "estudiante.h"

#include <iostream>

int main() {
    Estudiante estudiante;
    estudiante.mostrar_informacion();

    HashTable tabla_hash;
    tabla_hash.mostrar();

    Estudiante alumno_nuevo("CS1001", "Perez", "Juan", 15.5);
    tabla_hash.insertar(&alumno_nuevo);
    tabla_hash.mostrar();

    imprimir_avl_apellido();
    imprimir_avl_arbol();

    return 0;
}
