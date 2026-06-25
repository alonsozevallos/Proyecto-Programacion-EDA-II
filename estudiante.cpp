#include "estudiante.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <unordered_set>
#include <vector>

namespace {
int g_contador_codigo = 1000;
std::mt19937 g_gen_codigo;
std::mt19937 g_gen_ppa;
constexpr unsigned int g_seed_base = 20260624u;
constexpr unsigned int g_seed_combinaciones = 0xA5A5A5A5u;

void reiniciar_generacion() {
    g_contador_codigo = 1000;
    g_gen_codigo.seed(g_seed_base);
    g_gen_ppa.seed(g_seed_base ^ 0x9e3779b9u);
}
}

Estudiante::Estudiante() {
    this->codigo = "";
    this->apellidos = "";
    this->primer_nombre = "";
    this->promedio_ponderado = 0.0;
}

Estudiante::Estudiante(const std::string& codigo,
                       const std::string& apellidos,
                       const std::string& primer_nombre,
                       double promedio_ponderado)
    : codigo(codigo), apellidos(apellidos), primer_nombre(primer_nombre), promedio_ponderado(promedio_ponderado) {}

void Estudiante::mostrar_informacion() const {
    if (codigo.empty() && apellidos.empty() && primer_nombre.empty() && promedio_ponderado == 0.0) {
        const std::string ruta_csv = "nombre_apellido.csv";
        std::vector<Estudiante*> alumnos;

        if (!Estudiante::cargar_estudiantes(ruta_csv, alumnos)) {
            std::cerr << "No se pudo abrir el archivo: " << ruta_csv << std::endl;
            return;
        }

        if (alumnos.empty()) {
            std::cerr << "No se cargaron alumnos." << std::endl;
            return;
        }

        std::cout << "\n=== Lista de Alumnos ===" << std::endl;
        std::cout << "==============================" << std::endl;

        int indice = 1;
        for (Estudiante* estudiante : alumnos) {
            std::cout << "Alumno #" << indice++ << std::endl;
            estudiante->mostrar_informacion();
            std::cout << "------------------------------" << std::endl;
        }

        for (Estudiante* estudiante : alumnos) {
            delete estudiante;
        }
        return;
    }

    std::cout << std::left << std::setw(20) << "Codigo:" << codigo << std::endl;
    std::cout << std::left << std::setw(20) << "Apellidos:" << apellidos << std::endl;
    std::cout << std::left << std::setw(20) << "Primer Nombre:" << primer_nombre << std::endl;
    std::cout << std::left << std::setw(20) << "Promedio Ponderado:" << std::fixed << std::setprecision(2) << promedio_ponderado << std::endl;
}

std::string Estudiante::generar_codigo() const {
    std::uniform_int_distribution<int> dist_carrera(0, 3);

    std::string carreras[] = {"CS", "SI", "CE", "TI"};
    std::string sigla = carreras[dist_carrera(g_gen_codigo)];

    std::string codigo_resultado = sigla + std::to_string(g_contador_codigo);
    g_contador_codigo++;
    return codigo_resultado;
}

double Estudiante::generar_ppa() const {
    std::uniform_real_distribution<double> dist(1.0, 20.0);

    double valor = dist(g_gen_ppa);
    return std::round(valor * 100.0) / 100.0;
}

bool Estudiante::cargar_estudiantes(const std::string& ruta,
                                              std::vector<Estudiante*>& alumnos) {
    reiniciar_generacion();

    const std::size_t total_objetivo = 300;
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    alumnos.clear();

    std::vector<std::string> nombres;
    std::vector<std::string> apellidos;
    std::unordered_set<std::string> pares_existentes;

    auto agregar_estudiante = [&](const std::string& nombre, const std::string& apellido) {
        Estudiante* estudiante = new Estudiante();
        estudiante->primer_nombre = nombre;
        estudiante->apellidos = apellido;
        estudiante->codigo = estudiante->generar_codigo();
        estudiante->promedio_ponderado = estudiante->generar_ppa();
        alumnos.push_back(estudiante);
    };

    std::string linea;
    if (!std::getline(archivo, linea)) {
        return true;
    }

    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        std::stringstream ss(linea);
        std::string nombre;
        std::string apellido;

        if (!std::getline(ss, nombre, ',') || !std::getline(ss, apellido)) {
            continue;
        }

        nombres.push_back(nombre);
        apellidos.push_back(apellido);
        pares_existentes.insert(nombre + "|" + apellido);

        agregar_estudiante(nombre, apellido);

        if (alumnos.size() >= total_objetivo) {
            return true;
        }
    }

    if (nombres.empty() || apellidos.empty()) {
        return true;
    }

    std::vector<std::pair<std::size_t, std::size_t>> combinaciones;
    combinaciones.reserve(nombres.size() * apellidos.size());
    for (std::size_t ai = 0; ai < apellidos.size(); ++ai) {
        for (std::size_t ni = 0; ni < nombres.size(); ++ni) {
            combinaciones.push_back({ni, ai});
        }
    }

    std::mt19937 gen(g_seed_combinaciones);
    std::shuffle(combinaciones.begin(), combinaciones.end(), gen);

    for (const auto& par : combinaciones) {
        if (alumnos.size() >= total_objetivo) {
            break;
        }

        const std::string& nombre = nombres[par.first];
        const std::string& apellido = apellidos[par.second];
        std::string clave = nombre + "|" + apellido;

        if (pares_existentes.find(clave) != pares_existentes.end()) {
            continue;
        }

        agregar_estudiante(nombre, apellido);
        pares_existentes.insert(clave);
    }

    std::uniform_int_distribution<std::size_t> dist_nombre(0, nombres.size() - 1);
    std::uniform_int_distribution<std::size_t> dist_apellido(0, apellidos.size() - 1);
    while (alumnos.size() < total_objetivo) {
        const std::string& nombre = nombres[dist_nombre(gen)];
        const std::string& apellido = apellidos[dist_apellido(gen)];

        agregar_estudiante(nombre, apellido);
    }

    return true;
}