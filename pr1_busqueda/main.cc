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
#include "grafo.h"

void error_opcion(){
    std::cout  << "ERROR: se ha introducido una opcion incorrecta o no se introdujo ninguna \n cierre de programa" << std::endl;
}

int main(){

  grafo grafo_clase(0);
  std::string input;
  std::cout << "introduzca al nombre del archivo que quiere utilizar" << std::endl;
  std::cin >> input;
  grafo_clase.crear_grafo(input);

  int inicio{};
  int final{};
  std::cout << "intruduzca el nodo inicial y el nodo final del recorrido" << std::endl;
  std::cin >> inicio >> final;

  int recorrido{};    
  std::cout << "Elija un recorrido para hacer: BFS(1) o DFS(2)" << std::endl;
  std::cin >> recorrido;

  std::ofstream out{"output.txt"};

  if ( recorrido == 1){
    grafo_clase.BFS(inicio-1, final-1, out);
  }
  else if(recorrido == 2){
    grafo_clase.DFS(inicio-1, final-1, out);
  }
  else{
    std::cout  << "ERROR: se ha introducido una opcion incorrecta o no se introdujo ninguna \ncierre de programa" << std::endl;
    exit(1);
  }

  out.close();
  return 0;

}