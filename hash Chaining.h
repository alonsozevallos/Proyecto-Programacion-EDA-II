#ifndef HASH_CHAINING_H
#define HASH_CHAINING_H

#include "estudiante.h"

#include <string>

const int TABLE_SIZE = 11;

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

public:
    HashTable();
    ~HashTable();

    void insertar(Estudiante* e);
    Estudiante* buscar(const std::string& codigo) const;
    bool eliminar(const std::string& codigo);
    void mostrar();
};

#endif
