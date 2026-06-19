#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <vector>
#include <random>

struct Estudiante {
    std::string codigo;
    std::string apellidos;
    std::string primer_nombre;
    double promedio_ponderado;

    Estudiante();
    Estudiante(const std::string& codigo,
               const std::string& apellidos,
               const std::string& primer_nombre,
               double promedio_ponderado);

    void mostrar_informacion() const;
    std::string generar_codigo_aleatorio() const;
    double generar_ppa() const;

    static bool cargar_nombres_y_apellidos_desde_csv(const std::string& ruta,
                                                     std::vector<std::string>& nombres,
                                                     std::vector<std::string>& apellidos);
    static std::mt19937& generador_random();
    static std::string seleccionar_al_azar(const std::vector<std::string>& lista);
    static bool generar_estudiantes_aleatorios(int cantidad,
                                               const std::vector<std::string>& nombres,
                                               const std::vector<std::string>& apellidos,
                                               std::vector<Estudiante*>& alumnos);
    static bool cargar_estudiantes_desde_csv(const std::string& ruta,
                                             std::vector<Estudiante*>& alumnos);

    bool imprimir_alumnos_desde_csv() const;
};

std::vector<Estudiante*> cargarAlumnos();

#endif