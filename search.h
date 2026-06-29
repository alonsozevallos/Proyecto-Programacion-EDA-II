#ifndef SEARCH_H
#define SEARCH_H

#include "estudiante.h"
#include <vector>
#include <string>

void buscar_kmp(std::vector<Estudiante*>& alumnos, const std::string& patron);
void buscar_bm(std::vector<Estudiante*>& alumnos, const std::string& patron);

#endif