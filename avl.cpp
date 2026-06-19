#include "avl.h"
#include "estudiante.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    string apellido;
    vector<Estudiante*> alumnos;
    Node* left;
    Node* right;
    int height;

    Node(const string& apellidos) : apellido(apellidos), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insertNode(Node* node, Estudiante* estudiante) {
    if (!node) {
        Node* newNode = new Node(estudiante->apellidos);
        newNode->alumnos.push_back(estudiante);
        return newNode;
    }

    if (estudiante->apellidos < node->apellido) {
        node->left = insertNode(node->left, estudiante);
    } else if (estudiante->apellidos > node->apellido) {
        node->right = insertNode(node->right, estudiante);
    } else {
        node->alumnos.push_back(estudiante);
        return node;
    }

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && estudiante->apellidos < node->left->apellido)
        return rightRotate(node);
    if (balance < -1 && estudiante->apellidos > node->right->apellido)
        return leftRotate(node);
    if (balance > 1 && estudiante->apellidos > node->left->apellido) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && estudiante->apellidos < node->right->apellido) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* node, int& indice_alumno) {
    if (!node) return;
    inorder(node->left, indice_alumno);
    cout << "Apellido: " << node->apellido << " (" << node->alumnos.size() << ")" << endl;
    cout << "------------------------------" << endl;

    unordered_set<string> seen;
    for (Estudiante* e : node->alumnos) {
        string key = e->primer_nombre + "|" + e->apellidos;
        if (seen.insert(key).second) {
            cout << "Alumno #" << indice_alumno++ << endl;
            e->mostrar_informacion();
            cout << "------------------------------" << endl;
        }
    }
    cout << endl;

    inorder(node->right, indice_alumno);
}

int altura_arbol(Node* node) {
    if (!node) {
        return 0;
    }
    return 1 + max(altura_arbol(node->left), altura_arbol(node->right));
}

void imprimir_formato_arbol(Node* root) {
    if (!root) {
        cout << "(arbol vacio)" << endl;
        return;
    }

    const int h = altura_arbol(root);
    const int ancho_celda = 8;

    auto etiqueta = [](const string& apellido) {
        if (apellido.size() <= 8) {
            return apellido;
        }
        return apellido.substr(0, 8);
    };

    queue<Node*> q;
    q.push(root);

    for (int nivel = 1; nivel <= h; ++nivel) {
        int nodos_nivel = static_cast<int>(pow(2, nivel - 1));
        int bloques_inicio = static_cast<int>(pow(2, h - nivel)) - 1;
        int bloques_intermedios = static_cast<int>(pow(2, h - nivel + 1)) - 1;
        int factor_espacio = max(1, ancho_celda / 2);

        cout << string(bloques_inicio * factor_espacio, ' ');

        for (int i = 0; i < nodos_nivel; ++i) {
            Node* actual = q.front();
            q.pop();

            if (actual) {
                cout << left << setw(ancho_celda) << etiqueta(actual->apellido);
                q.push(actual->left);
                q.push(actual->right);
            } else {
                cout << left << setw(ancho_celda) << " ";
                q.push(nullptr);
                q.push(nullptr);
            }

            if (i != nodos_nivel - 1) {
                cout << string(bloques_intermedios * factor_espacio, ' ');
            }
        }
        cout << "\n\n";
    }
}

void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    for (Estudiante* e : node->alumnos) {
        delete e;
    }
    delete node;
}

void imprimir_avl() {
    vector<Estudiante*> alumnos;
    const string ruta_csv = "nombre_apellido.csv";

    if (!Estudiante::cargar_estudiantes_desde_csv(ruta_csv, alumnos)) {
        cerr << "No se pudo abrir el archivo CSV: " << ruta_csv << endl;
        return;
    }

    Node* root = nullptr;
    for (Estudiante* e : alumnos) {
        root = insertNode(root, e);
    }

    cout << "\n=== AVL por apellido ===" << endl;
    cout << "Total: " << alumnos.size() << endl;
    cout << "==============================" << endl;
    int indice_alumno = 1;
    inorder(root, indice_alumno);

    deleteTree(root);
}
