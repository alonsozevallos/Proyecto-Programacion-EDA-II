#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;
string a_minusculas(const string& s) {
    string resultado = s;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

vector<int> construir_tabla_kmp(const string& patron) {
    int m = patron.size();
    vector<int> tabla(m, 0);
    int j = 0;

    for (int i = 1; i < m; i++) {
        while (j > 0 && patron[i] != patron[j]) {
            j = tabla[j - 1];
        }
        if (patron[i] == patron[j]) {
            j++;
        }
        tabla[i] = j;
    }
    return tabla;
}

bool kmp_contiene(const string& texto, const string& patron) {
    if (patron.empty()) return true;

    string t = a_minusculas(texto);
    string p = a_minusculas(patron);

    int n = t.size();
    int m = p.size();
    vector<int> tabla = construir_tabla_kmp(p);

    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j]) {
            j = tabla[j - 1];
        }
        if (t[i] == p[j]) {
            j++;
        }
        if (j == m) {
            return true;
        }
    }
    return false;
}

void buscar_kmp(vector<Estudiante*>& alumnos, const string& patron) {
    cout << "\n=== Búsqueda KMP: \"" << patron << "\" ===" << endl;
    cout << "===========================================" << endl;

    int encontrados = 0;
    for (Estudiante* e : alumnos) {
        if (kmp_contiene(e->apellidos, patron)) {
            e->mostrar_informacion();
            cout << "-------------------------------------------" << endl;
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron alumnos con ese patrón." << endl;
    } else {
        cout << "Total encontrados: " << encontrados << endl;
    }
}
unordered_map<char, int> construir_tabla_bm(const string& patron) {
    unordered_map<char, int> tabla;
    int m = patron.size();

    for (int i = 0; i < m; i++) {
        tabla[patron[i]] = i;
    }
    return tabla;
}
bool bm_contiene(const string& texto, const string& patron) {
    if (patron.empty()) return true;

    string t = a_minusculas(texto);
    string p = a_minusculas(patron);

    int n = t.size();
    int m = p.size();

    unordered_map<char, int> tabla = construir_tabla_bm(p);

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && p[j] == t[i + j]) {
            j--;
        }
        if (j < 0) {
            return true;
        }
        char c = t[i + j];
        int salto = tabla.count(c) ? j - tabla[c] : j + 1;
        i += max(1, salto);
    }
    return false;
}

void buscar_bm(vector<Estudiante*>& alumnos, const string& patron) {
    cout << "\n=== Busqueda Boyer Moore: \"" << patron << "\" ===" << endl;
    cout << "===================================================" << endl;

    int encontrados = 0;
    for (Estudiante* e : alumnos) {
        if (bm_contiene(e->apellidos, patron)) {
            e->mostrar_informacion();
            cout << "---------------------------------------------------" << endl;
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron alumnos con ese patron" << endl;
    } else {
        cout << "Total encontrados: " << encontrados << endl;
    }
}