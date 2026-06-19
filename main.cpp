#include "avl.h"
#include "estudiante.h"

int main() {
    // Crear un estudiante de ejemplo para mostrar su información
    Estudiante estudiante;
    estudiante.mostrar_informacion();
    
    // Imprimir el árbol AVL con los estudiantes cargados desde el CSV
    imprimir_avl();
}
