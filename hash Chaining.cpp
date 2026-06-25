#include "hash Chaining.h"
#include "estudiante.h"

#include <iomanip>
#include <iostream>
#include <vector>

HashNode::HashNode(Estudiante* e) : estudiante(e), next(nullptr) {}

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        bins[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = bins[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            delete temp->estudiante;
            delete temp;
        }
    }
}

int HashTable::hashFunction(const std::string& codigo) const {
    int hash = 0;
    for (size_t i = 0; i < codigo.length(); ++i) {
        hash = (hash * 31 + codigo[i]) % TABLE_SIZE;
    }
    return hash;
}

bool HashTable::esta_vacia() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (bins[i] != nullptr) {
            return false;
        }
    }
    return true;
}

void HashTable::mostrar_bin(int index) const {
    std::cout << "Bin [" << std::setw(2) << index << "]: ";
    HashNode* current = bins[index];
    if (!current) {
        std::cout << "vacío";
    }
    while (current) {
        std::cout << "[" << current->estudiante->codigo
                  << " - " << current->estudiante->apellidos
                  << ", " << current->estudiante->primer_nombre << "]";
        if (current->next) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void HashTable::insertar(Estudiante* e, bool mostrar_bin_resultado) {
    int index = hashFunction(e->codigo);
    HashNode* nuevo = new HashNode(new Estudiante(*e));
    nuevo->next = bins[index];
    bins[index] = nuevo;

    if (mostrar_bin_resultado) {
        std::cout << "Estudiante agregado en:" << std::endl;
        mostrar_bin(index);
    }
}

void HashTable::llenar_hash() {
    if (!esta_vacia()) {
        return;
    }

    const std::string ruta_csv = "nombre_apellido.csv";
    std::vector<Estudiante*> alumnos;
    if (!Estudiante::cargar_estudiantes(ruta_csv, alumnos)) {
        std::cerr << "No se pudo abrir el archivo: " << ruta_csv << std::endl;
        return;
    }

    if (alumnos.empty()) {
        std::cerr << "No se cargaron alumnos para el HashTable." << std::endl;
        return;
    }

    for (Estudiante* e : alumnos) {
        insertar(e, false);
    }

    for (Estudiante* e : alumnos) {
        delete e;
    }
}

Estudiante* HashTable::buscar(const std::string& codigo) {
    llenar_hash();

    int index = hashFunction(codigo);
    HashNode* current = bins[index];
    while (current) {
        if (current->estudiante->codigo == codigo) {
            std::cout << "Estudiante " << current->estudiante->apellidos << " encontrado en:" << std::endl;
            mostrar_bin(index);
            return current->estudiante;
        }
        current = current->next;
    }

    std::cout << "No se encontro al estudiante con codigo: " << codigo << std::endl;
    return nullptr;
}

bool HashTable::eliminar(const std::string& codigo) {
    llenar_hash();

    int index = hashFunction(codigo);
    HashNode* current = bins[index];
    HashNode* prev = nullptr;
    while (current) {
        if (current->estudiante->codigo == codigo) {
            if (prev) {
                prev->next = current->next;
            } else {
                bins[index] = current->next;
            }
            delete current->estudiante;
            delete current;
            std::cout << "Estudiante eliminado: " << codigo << std::endl;
            std::cout << "Bin actualizado:" << std::endl;
            mostrar_bin(index);
            return true;
        }
        prev = current;
        current = current->next;
    }

    std::cout << "No se encontro al estudiante con codigo: " << codigo << std::endl;
    return false;
}

void HashTable::mostrar() {
    llenar_hash();

    std::cout << "\n=== Hash Table ===" << std::endl;
    std::cout << "Tamaño de tabla: " << TABLE_SIZE << std::endl;
    std::cout << "=========================================" << std::endl;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        std::cout << "Bin [" << std::setw(2) << i << "]: ";
        HashNode* current = bins[i];
        if (!current) {
            std::cout << "vacío";
        }
        while (current) {
            std::cout << "[" << current->estudiante->codigo
                      << " - " << current->estudiante->apellidos
                      << ", " << current->estudiante->primer_nombre << "]";
            if (current->next) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
}