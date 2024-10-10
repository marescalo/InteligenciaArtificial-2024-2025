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

#include "grafo.h"
#include <vector>

void grafo::crear_grafo(const std::string& file_name){
    std::ifstream file(file_name); // Abrir el archivo
    if (!file.is_open()) { // Verificar si el archivo se abrió correctamente
        std::cout << "Error: ¡No se pudo abrir el archivo!" << std::endl;
        exit(1);
    }

    file >> nodo_; // Leer el número de nodos
    int num = nodo_;
    matriz_.resize(num, std::vector<double>(num, -1.00)); // Redimensionar la matriz de adyacencia

    // Leer la matriz de adyacencia del archivo
    for (int i = 0; i < num; ++i) {
        for (int j = i+1; j < num; ++j) {
            if (i == j) {
                matriz_[i][j] = -1.00; // No hay arista entre un nodo y sí mismo
            } else {
                file >> matriz_[i][j]; // Leer el peso de la arista
                matriz_[j][i] = matriz_[i][j]; // La matriz es simétrica
            }
        }
    }
    file.close(); // Cerrar el archivo
}

void grafo::DFS(int inicio, int final, std::ostream& out){
    std::vector<bool> visited(nodo_, false);  // Para rastrear nodos visitados
    std::vector<int> parent(nodo_, -1);       // Para reconstruir el camino
    std::vector<int> toExplore;                // Nodos por explorar (no stack, sólo vector)
    std::vector<int> inspected;                // Nodos inspeccionados
    int numEdges = 0;                     // Contador de aristas

    // Imprimir el número de nodos y aristas del grafo
    for (int i = 0; i < nodo_; ++i) {
        for (int j = 0; j < nodo_; ++j) {
            if (matriz_[i][j] != -1.00) {
                numEdges++;
            }
        }
    }
    numEdges /= 2;  // Porque las aristas son bidireccionales y se cuentan doble
    out << "Número de nodos del grafo: " << nodo_ << std::endl;
    out << "Número de aristas del grafo: " << numEdges << std::endl;
    out << "Vértice origen: " << inicio + 1 << std::endl;
    out << "Vértice destino: " << final + 1 << std::endl;

    toExplore.push_back(inicio); // Agregar el nodo de inicio a la lista de exploración
    visited[inicio] = true; // Marcar el nodo de inicio como visitado
    int currentIndex = 0;
    bool found = false;
    int iteration = 1;
    std::vector<int> newGenerated;  // Para almacenar los nuevos nodos generados en esta iteración

    out << "--------------------------------" << std::endl;
    out << "Iteración 0" << std::endl;
    out << "Nodos generados: " << inicio + 1 << std::endl;
    out << "Nodos inspeccionados: -" << std::endl;

    // Bucle principal de DFS (iterativo utilizando vector)
    while (currentIndex >= 0) {
        int current = toExplore.back();
        inspected.push_back(current); // Agregar el nodo actual a la lista de inspeccionados
        toExplore.pop_back();  // Lo eliminamos del vector para simular el backtracking
        out << "--------------------------------" << std::endl;
        out << "Iteración " << iteration++ << std::endl;
        out << "Nodos generados: ";
        


        // Explorar nodos adyacentes
        for (int i = 0; i < nodo_; ++i) {
            if (matriz_[current][i] != -1.00 && !visited[i]) {
                visited[i] = true; // Marcar el nodo como visitado
                parent[i] = current; // Establecer el nodo actual como padre
                toExplore.push_back(i);  // DFS es LIFO, entonces agregamos al final para continuar profundizando
                newGenerated.push_back(i + 1);  // Convertir a 1-based index
                if (i == final) {
                    found = true; // Si encontramos el nodo de destino, marcar como encontrado
                    break;
                }
            }
        }

        // Imprimir los nodos generados y luego los nodos inspeccionados
        for (size_t i = 0; i < newGenerated.size(); ++i) {
            out << newGenerated[i];
            if (i != newGenerated.size() - 1) out << ", ";
        }
        out << std::endl;
        out << "Nodos inspeccionados: ";
        for (size_t i = 0; i < inspected.size(); ++i) {
            out << inspected[i] + 1;
            if (i != inspected.size() - 1) out << ", ";
        }
        out << std::endl;

        if (found) break;  // Si encontramos el vértice de destino, salimos del bucle
    }

    // Reconstruir el camino y calcular el costo total
    if (found) {
        std::vector<int> path;
        double totalCost = 0.0;  // Variable para almacenar el coste total del camino
        for (int v = final; v != -1; v = parent[v]) {
            path.push_back(v + 1);  // Convertimos a 1-based index
            if (parent[v] != -1) {
                totalCost += matriz_[parent[v]][v];  // Sumar el coste de la arista entre parent[v] y v
            }
        }
        reverse(path.begin(), path.end()); // Invertir el camino para obtener el orden correcto

        // Imprimir el camino y el coste total
        out << "--------------------------------" << std::endl;
        out << "Camino: ";
        for (size_t i = 0; i < path.size(); ++i) {
            out << path[i];
            if (i != path.size() - 1) out << " - ";
        }
        out << std::endl;
        out << "Costo: " << totalCost << std::endl;
    } else {
        out << "No se encontró un camino desde " << inicio + 1 << " hasta " << final + 1 << std::endl;
    }
}

void grafo::BFS(int inicio, int final, std::ostream& out){
    std::vector<bool> visited(nodo_, false);  // Para rastrear nodos visitados
    std::vector<int> parent(nodo_, -1);       // Para reconstruir el camino
    std::vector<int> toExplore;                // Nodos por explorar
    std::vector<int> inspected;                // Nodos inspeccionados
    int numEdges = 0;                     // Contador de aristas

    // Imprimir el número de nodos y aristas del grafo
    for (int i = 0; i < nodo_; ++i) {
        for (int j = 0; j < nodo_; ++j) {
            if (matriz_[i][j] != -1.00) {
                numEdges++;
            }
        }
    }
    numEdges /= 2;  // Porque las aristas son bidireccionales y se cuentan doble
    out << "Número de nodos del grafo: " << nodo_ << std::endl;
    out << "Número de aristas del grafo: " << numEdges << std::endl;
    out << "Vértice origen: " << inicio + 1 << std::endl;
    out << "Vértice destino: " << final + 1 << std::endl;

    toExplore.push_back(inicio); // Agregar el nodo de inicio a la lista de exploración
    visited[inicio] = true; // Marcar el nodo de inicio como visitado
    int currentIndex = 0;
    bool found = false;
    int iteration = 1;
    std::vector<int> newGenerated;  // Para almacenar los nuevos nodos generados en esta iteración

    out << "--------------------------------" << std::endl;
    out << "Iteración 0" << std::endl;
    out << "Nodos generados: " << inicio + 1 << std::endl;
    out << "Nodos inspeccionados: -" << std::endl;

    // Bucle principal de BFS
    while (currentIndex < toExplore.size()) {
        int current = toExplore[currentIndex];
        inspected.push_back(current); // Agregar el nodo actual a la lista de inspeccionados
        out << "--------------------------------" << std::endl;
        out << "Iteración " << iteration++ << std::endl;
        out << "Nodos generados: ";

        // Explorar nodos adyacentes
        for (int i = 0; i < nodo_; ++i) {
            if (matriz_[current][i] != -1.00 && !visited[i]) {
                visited[i] = true; // Marcar el nodo como visitado
                parent[i] = current; // Establecer el nodo actual como padre
                toExplore.push_back(i); // Agregar el nodo a la lista de exploración
                newGenerated.push_back(i + 1);  // Convertir a 1-based index
                if (i == final) {
                    found = true; // Si encontramos el nodo de destino, marcar como encontrado
                }
            }
        }

        // Imprimir los nodos generados y luego los nodos inspeccionados
        for (size_t i = 0; i < newGenerated.size(); ++i) {
            out << newGenerated[i];
            if (i != newGenerated.size() - 1) out << ", ";
        }
        out << std::endl;
        out << "Nodos inspeccionados: ";
        for (size_t i = 0; i < inspected.size(); ++i) {
            out << inspected[i] + 1;
            if (i != inspected.size() - 1) out << ", ";
        }
        out << std::endl;

        currentIndex++;
        if (found) break;  // Si encontramos el vértice de destino, salimos del bucle
    }

    // Reconstruir el camino y calcular el costo total
    if (found) {
        std::vector<int> path;
        double totalCost = 0.0;  // Variable para almacenar el coste total del camino
        for (int v = final; v != -1; v = parent[v]) {
            path.push_back(v + 1);  // Convertimos a 1-based index
            if (parent[v] != -1) {
                totalCost += matriz_[parent[v]][v];  // Sumar el coste de la arista entre parent[v] y v
            }
        }
        reverse(path.begin(), path.end()); // Invertir el camino para obtener el orden correcto

        // Imprimir el camino y el coste total
        out << "--------------------------------" << std::endl;
        out << "Camino: ";
        for (size_t i = 0; i < path.size(); ++i) {
            out << path[i];
            if (i != path.size() - 1) out << " - ";
        }
        out << std::endl;
        out << "Costo: " << totalCost << std::endl;
    } else {
        out << "No se encontró un camino desde " << inicio + 1 << " hasta " << final + 1 << std::endl;
    }
}