// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Inteligencia Artifial
// Curso: 2º
// Practica 1: Busqueda no informada
// Autor: Margarita Blanca Escobar Alonso
// Correo: alu0101567211@ull.edu.es
// Fecha: 26/09/2024
// Referencias:
//     Enlaces de interes
//
// Historial de revisiones
//     26/09/2024- Creacion (primera version) del codigo

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

class grafo{
    
    public:
        grafo(int nodo):nodo_(nodo) {matriz_.resize(nodo,std::vector<double>(nodo,0));};
        void crear_grafo(const std::string& file_name);
        void DFS(int inicio, int final, std::ostream& out);
        void BFS(int inicio, int final, std::ostream& out);
        void Modificacion(int inicio, int final, std::ostream& out);

    private:
        std::vector<std::vector<double>> matriz_; //cambiar nombre
        int nodo_{};
};