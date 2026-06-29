#include "avl.h"
#include "hash Chaining.h"
#include "estudiante.h"
#include "heap.h"
#include "search.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void mostrar_menu() {
    cout << "\n=========================================" << endl;
    cout << "   SISTEMA DE CONTROL DE ESTUDIANTES    " << endl;
    cout << "=========================================" << endl;
    cout << "1. Mostrar lista de alumnos" << endl;
    cout << "2. Mostrar arbol AVL (por apellido)" << endl;
    cout << "3. Mostrar tabla hash" << endl;
    cout << "4. Buscar alumno por codigo (Hash)" << endl;
    cout << "5. Eliminar alumno por codigo (Hash)" << endl;
    cout << "6. Top 10 mejores alumnos (Max-Heap)" << endl;
    cout << "7. Top 10 peores alumnos (Min-Heap)" << endl;
    cout << "8. Buscar por apellido - KMP" << endl;
    cout << "9. Buscar por apellido - Boyer-Moore" << endl;
    cout << "0. Salir" << endl;
    cout << "=========================================" << endl;
    cout << "Opcion: ";
}

int main() {
    vector<Estudiante*> alumnos;
    if (!Estudiante::cargar_estudiantes("nombre_apellido.csv", alumnos)) {
        cerr << "Error: no se pudo cargar el archivo CSV." << endl;
        return 1;
    }

    HashTable tabla_hash;

    int opcion = -1;

    while (opcion != 0) {
        mostrar_menu();
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida, intenta de nuevo." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                cout << "\n=== Lista de Alumnos ===" << endl;
                cout << "==============================" << endl;
                int i = 1;
                for (Estudiante* e : alumnos) {
                    cout << "Alumno #" << i++ << endl;
                    e->mostrar_informacion();
                    cout << "------------------------------" << endl;
                }
                break;
            }
            case 2: {
                imprimir_avl();
                break;
            }
            case 3: {
                tabla_hash.mostrar();
                break;
            }
            case 4: {
                string codigo;
                cout << "Ingresa el codigo del alumno: ";
                getline(cin, codigo);
                Estudiante* encontrado = tabla_hash.buscar(codigo);
                if (encontrado) {
                    cout << "\nDatos del alumno encontrado:" << endl;
                    encontrado->mostrar_informacion();
                }
                break;
            }
            case 5: {
                string codigo;
                cout << "Ingresa el codigo del alumno a eliminar: ";
                getline(cin, codigo);
                tabla_hash.eliminar(codigo);
                break;
            }
            case 6: {
                mostrar_top10_max(alumnos);
                break;
            }
            case 7: {
                mostrar_top10_min(alumnos);
                break;
            }
            case 8: {
                string patron;
                cout << "Ingresa el patron a buscar (KMP): ";
                getline(cin, patron);
                buscar_kmp(alumnos, patron);
                break;
            }
            case 9: {
                string patron;
                cout << "Ingresa el patron a buscar (Boyer-Moore): ";
                getline(cin, patron);
                buscar_bm(alumnos, patron);
                break;
            }
            case 0: {
                cout << "\nSaliendo del sistema." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida, intenta de nuevo." << endl;
                break;
            }
        }
    }

    for (Estudiante* e : alumnos) {
        delete e;
    }

    return 0;
}