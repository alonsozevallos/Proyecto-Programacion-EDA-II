#include "heap.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

struct CmpMin {
    bool operator()(Estudiante* a, Estudiante* b) {
        return a->promedio_ponderado > b->promedio_ponderado;
    }
};

vector<Estudiante*> obtener_top10_max(vector<Estudiante*>& alumnos) {
    priority_queue<Estudiante*, vector<Estudiante*>, CmpMin> pq;

    for (Estudiante* e : alumnos) {
        pq.push(e);
        if ((int)pq.size() > 10) {
            pq.pop();
        }
    }

    vector<Estudiante*> resultado;
    while (!pq.empty()) {
        resultado.push_back(pq.top());
        pq.pop();
    }
    
    reverse(resultado.begin(), resultado.end());
    return resultado;
}

void mostrar_top10_max(vector<Estudiante*>& alumnos) {
    cout << "\n=== TOP 10 - MAYOR PPA (Candidatos a Beca) ===" << endl;
    cout << "================================================" << endl;

    vector<Estudiante*> top = obtener_top10_max(alumnos);
    int puesto = 1;
    for (Estudiante* e : top) {
        cout << "Puesto #" << puesto++ << endl;
        e->mostrar_informacion();
        cout << "------------------------------------------------" << endl;
    }
}


struct CmpMax {
    bool operator()(Estudiante* a, Estudiante* b) {
        return a->promedio_ponderado < b->promedio_ponderado;
    }
};

vector<Estudiante*> obtener_top10_min(vector<Estudiante*>& alumnos) {
    priority_queue<Estudiante*, vector<Estudiante*>, CmpMax> pq;

    for (Estudiante* e : alumnos) {
        pq.push(e);
        if ((int)pq.size() > 10) {
            pq.pop();
        }
    }

    vector<Estudiante*> resultado;
    while (!pq.empty()) {
        resultado.push_back(pq.top());
        pq.pop();
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}

void mostrar_top10_min(vector<Estudiante*>& alumnos) {
    cout << "\n=== TOP 10 - MENOR PPA (Clases de Reforzamiento) ===" << endl;
    cout << "=====================================================" << endl;

    vector<Estudiante*> bottom = obtener_top10_min(alumnos);
    int puesto = 1;
    for (Estudiante* e : bottom) {
        cout << "Puesto #" << puesto++ << endl;
        e->mostrar_informacion();
        cout << "-----------------------------------------------------" << endl;
    }
}