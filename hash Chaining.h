#ifndef HASH_CHAINING_H
#define HASH_CHAINING_H

#include "estudiante.h"

#include <string>

const int TABLE_SIZE = 50;

struct HashNode {
    Estudiante* estudiante;
    HashNode* next;

    explicit HashNode(Estudiante* e);
};

class HashTable {
private:
    HashNode* bins[TABLE_SIZE];

    int hashFunction(const std::string& codigo) const;
    bool esta_vacia() const;
    void llenar_hash();
    void mostrar_bin(int index) const;

public:
    HashTable();
    ~HashTable();

    void insertar(Estudiante* e, bool mostrar_bin = true);
    Estudiante* buscar(const std::string& codigo);
    bool eliminar(const std::string& codigo);
    void mostrar();
};

#endif
