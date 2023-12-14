// Copyright 2023 <yeshua.ramirez@ucr.ac.cr>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

int initTest(char* argv[]);
int comparacion(std::vector<std::vector<double>>& placa1,
std::vector<std::vector<double>>& placa2, double epsilon, size_t R,
size_t C);
int lecturaBinarios(std::vector<std::vector<double>>& placa,
const std::string& nombreRuta, size_t& R, size_t& C);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Cantidad invalida de argumentos" << std::endl;
    return EXIT_FAILURE;
  }
  return initTest(argv);
}

// Compara dos placas considerando el epsilon
int comparacion(std::vector<std::vector<double>>& placa1,
std::vector<std::vector<double>>& placa2, double epsilon, size_t R,
size_t C) {
  try {
    for (size_t indexR = 1; indexR < (R - 2); indexR++) {
      for (size_t indexC = 1; indexC < (C - 2); indexC++) {
        if (std::abs(placa1[indexR][indexC] - placa2[indexR][indexC]) >
        epsilon) {
          std::cout << "ERROR! HA SOBREPASADO EPSILON!" << std::endl;
          return EXIT_FAILURE;
        }
      }
    }
  }
  catch(const std::exception& e) {  // catch para detectar segmentatios
    std::cerr << e.what() <<'\n';
    return EXIT_FAILURE;
  }
  std::cout << "TODO BIEN!" << std::endl;
  return EXIT_SUCCESS;
}

// Inicializa la prueba de comparación entre los archivos binarios
int initTest(char* argv[]) {
  std::string file1 = argv[1];
  std::string file2 = argv[2];
  double epsilon = std::stod(argv[3]);
  size_t rows1, cols1, rows2, cols2 = 0;
  std::vector<std::vector<double>> placaNuestra, placaOriginal;
  lecturaBinarios(placaNuestra, file1, rows1, cols1);
  lecturaBinarios(placaOriginal, file2, rows2, cols2);
  if ((rows1 != rows2) || (cols1 != cols2)) {
    std::cerr << "No se pueden comparar dos matrices de distinto tamaño "<<
    std::endl;
    return EXIT_FAILURE;
  }

  return comparacion(placaNuestra, placaOriginal, epsilon, rows1, cols1);
}

// Lee datos binarios desde el archivo y llena la matriz
int lecturaBinarios(std::vector<std::vector<double>>& placa,
const std::string& nombreRuta, size_t& R, size_t& C) {
  std::string ruta = nombreRuta;
  std::ifstream file;
  file.open(ruta, std::ios::binary);

  file.read(reinterpret_cast<char*>(&R), sizeof(size_t));
  file.read(reinterpret_cast<char*>(&C), sizeof(size_t));

  // nueva matriz para almacenar temporalmente los datos
  std::vector<std::vector<double>>* matrizDePaso1 =
    new std::vector<std::vector<double>>;

  // referencia para facilitar su uso
  std::vector<std::vector<double>>&  matrizDePaso2 = *matrizDePaso1;

  matrizDePaso1->resize(R);

  for (size_t r = 0; r < R; ++r) {
    matrizDePaso2[r].resize(C);
    for (size_t c = 0; c < C; ++c) {
      file.read(reinterpret_cast<char*>
          (&(matrizDePaso2[r][c])), sizeof(double));
    }
  }

  file.close();
  // Se redimensiona la matriz de la placa y guarda los datos obtenidos
  placa.resize(R,
    std::vector<double>(C));
    placa.resize(R,
    std::vector<double>(C));
  for (size_t r = 0; r < R; ++r) {
    for (size_t c = 0; c < C; ++c) {
      placa[r][c] = matrizDePaso2[r][c];
    }
  }
  // Limpiar la memoria asignada dinámicamente
  delete matrizDePaso1;
  return EXIT_SUCCESS;
}
