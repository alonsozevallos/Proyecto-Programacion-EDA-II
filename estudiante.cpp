#include "estudiante.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

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
    static int contador = 1000;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_carrera(0, 3);

    std::string carreras[] = {"CS", "SI", "CE", "TI"};
    std::string sigla = carreras[dist_carrera(gen)];

    std::string codigo_resultado = sigla + std::to_string(contador);
    contador++;
    return codigo_resultado;
}

double Estudiante::generar_ppa() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(1.0, 20.0);

    double valor = dist(gen);
    return std::round(valor * 100.0) / 100.0;
}

bool Estudiante::cargar_estudiantes(const std::string& ruta,
                                              std::vector<Estudiante*>& alumnos) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    alumnos.clear();

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

        Estudiante* estudiante = new Estudiante();
        estudiante->primer_nombre = nombre;
        estudiante->apellidos = apellido;
        estudiante->codigo = estudiante->generar_codigo();
        estudiante->promedio_ponderado = estudiante->generar_ppa();
        alumnos.push_back(estudiante);
    }

    return true;
}