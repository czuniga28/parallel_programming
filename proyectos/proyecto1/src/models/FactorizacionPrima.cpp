// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#include "FactorizacionPrima.hpp"
#include "FactInfo.hpp"

void FactorizacionPrima::factorizar(std::vector<int64_t> numeros) {
  this->factorizados = numeros;
  std::vector<std::vector<std::tuple<int64_t, int64_t>>> resultados;

  for (int64_t i = 0; i < static_cast<int64_t>(numeros.size()); i++) {
    int64_t numActual = numeros[i];
    std::vector<std::tuple<int64_t, int64_t>> factores;

    if (numActual == 0 || numActual < 0) {
      factores.push_back(std::make_tuple(-2, -2));
    } else if (numActual == 1) {
      factores.push_back(std::make_tuple(-1, -1));
    } else {
      CribaEratostenes criba = CribaEratostenes();
      criba.calcularPrimos(numActual);
      // std::vector<int64_t> primos = cribaDeEratostenes(numActual);

      for (int64_t j = 0; j < static_cast<int64_t>
          (criba.getNumerosPrimos().size()); j++) {
        int64_t primo = criba.getNumerosPrimos()[j];
        int64_t exponente = 0;
        while (numActual % primo == 0) {
          exponente++;
          numActual /= primo;
        }
        if (exponente > 0) {
          factores.push_back(std::make_tuple(primo, exponente));
        }
      }
      if (numActual > 1) {
        factores.push_back(std::make_tuple(numActual, 1));
      }
    }

    resultados.push_back(factores);
  }

  this->factorizaciones = resultados;
}

// Solo usar en casos de debugging! No para web
void FactorizacionPrima::imprimirFactorizacionPrima() {
    for (size_t i = 0; i < this->factorizados.size(); i++) {
        std::cout << "Número " << this->factorizados[i] << ": ";
        for (size_t j = 0; j < this->factorizaciones[i].size(); j++) {
            int64_t primo = std::get<0>(this->factorizaciones[i][j]);
            int64_t exponente = std::get<1>(this->factorizaciones[i][j]);
            std::cout << "(" << primo << "," << exponente << ")";
        }
        std::cout << std::endl;
    }
}

  int FactorizacionPrima::run() {
    this->consumeForever();
    return EXIT_SUCCESS;
  }

  void FactorizacionPrima::consume(NumeroF numeroF) {
    std::vector<int64_t> trabajo;
    trabajo.push_back(numeroF.numero);
    this->factorizar(trabajo);
    //! NO SE SI ESTA LINEA PUEDE DAR PROBLEMAS, PORQUE
    //! NO DA TOTAL DE BASES COMO TAL
    numeroF.totalBases = this->factorizaciones.size();
    std::vector<std::tuple<int64_t, int64_t>> prueba =
    this->factorizaciones.back();
    numeroF.direccionRequest->
    setFactorizacion(prueba, numeroF.posicion);

    this->produce(numeroF);
  }
