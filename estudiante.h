#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <vector>

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
    std::string generar_codigo() const;
    double generar_ppa() const;

    static bool cargar_estudiantes(const std::string& ruta,
                                   std::vector<Estudiante*>& alumnos);
};

#endif