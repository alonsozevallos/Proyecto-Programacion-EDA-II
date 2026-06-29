#ifndef HEAP_H
#define HEAP_H

#include "estudiante.h"
#include <vector>

std::vector<Estudiante*> obtener_top10_max(std::vector<Estudiante*>& alumnos);
void mostrar_top10_max(std::vector<Estudiante*>& alumnos);

std::vector<Estudiante*> obtener_top10_min(std::vector<Estudiante*>& alumnos);
void mostrar_top10_min(std::vector<Estudiante*>& alumnos);

#endif