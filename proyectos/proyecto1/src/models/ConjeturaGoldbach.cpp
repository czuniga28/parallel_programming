// Copyright 2023 <yeashua.ramirez@ucr.ac.cr>
#include <unordered_map>
#include "ConjeturaGoldbach.hpp"
#include "GoldbachInfo.hpp"

void ConjeturaGoldbach::trabajarConjeturaGoldbach(std::vector<int64_t> sumas) {
  std::vector<std::vector<std::vector<int64_t>>> resultados;
  // this->sumandos.reserve(sumas.size());
  // para cada uno de los elementos buscados
  for (auto suma : sumas) {
    // si es negativo y aun asi en positivo se puede trabajar, es que
    // el usuario quiere ver cuantas posibles soluciones hay
    if (suma < 0) {
      if ((suma * -1) > 5) {
        suma = suma * -1;
      } else {
        // cuando es negativo e invalido, no intersa el numero que sea, porque
        // de todas formas no se procesara
        suma = 1;
      }
    }
    // si es par
    if (suma % 2 == 0) {
      resultados.push_back(this->sumaPrimosPares(suma));
    } else {  // si es impar
      resultados.push_back(this->sumaPrimosImpares(suma));
    }
  }

  this->sumas = sumas;
  this->sumandos = resultados;
}

std::vector<std::vector<int64_t>> ConjeturaGoldbach::sumaPrimosImpares
    (int64_t suma) {
  CribaEratostenes hastaN = CribaEratostenes();
  hastaN.calcularPrimos(suma);
  // hastaN.imprimirNumerosPrimos();
  std::vector<std::vector<int64_t>> resultado;

  if (suma <= 5) {
    // Significa que no hay resultado posible
    //! Tomar en cuenta para impresion en webApp
    resultado.push_back({0, 0});
    return resultado;
  }


  const std::vector<int64_t>& numerosPrimos = hastaN.getNumerosPrimos();
  int64_t n = static_cast<int64_t>(numerosPrimos.size());

  std::unordered_map<int64_t, int64_t> numMap;

  for (int64_t i = 0; i < n; i++) {
      numMap[numerosPrimos[i]] = i;
  }

  for (int64_t a = 0; a < n; a++) {
      for (int64_t b = a; b < n; b++) {
          int64_t target = suma - (numerosPrimos[a] + numerosPrimos[b]);
          auto it = numMap.find(target);

          if (it != numMap.end() && it->second >= b) {
              resultado.push_back({numerosPrimos[a], numerosPrimos[b],
                it->first});
              this->sumasEncontradas += 1;
          }
      }
  }

  return resultado;
}

std::vector<std::vector<int64_t>> ConjeturaGoldbach::sumaPrimosPares
    (int64_t suma) {
  CribaEratostenes hastaN = CribaEratostenes();
  hastaN.calcularPrimos(suma);
  // hastaN.imprimirNumerosPrimos();
  std::vector<std::vector<int64_t>> resultado;

  if (suma <= 5) {
    // Significa que no hay resultado posible
    //! Tomar en cuenta para impresion en webApp
    resultado.push_back({0, 0});
    return resultado;
  }

  const std::vector<int64_t>& numerosPrimos = hastaN.getNumerosPrimos();
  int64_t n = static_cast<int64_t>(numerosPrimos.size());
  std::unordered_map<int64_t, int> numMap;

  for (int64_t a = 0; a < n; a++) {
      int64_t currentA = numerosPrimos[a];
      int64_t target = suma - currentA;

      if (numMap.find(target) != numMap.end()) {
          resultado.push_back({currentA, target});
          this->sumasEncontradas += 1;
      }

      numMap[currentA] = a;
  }

  return resultado;
}

// Solo para debuggin! Probar antes de subir definitivamente
void ConjeturaGoldbach::imprimirConjeturaGoldbach() {
  for (int64_t suma = 0; suma < static_cast<int64_t>(this->getSumas().size());
      suma++) {
    std::cout << this->getSumas()[suma] << ": ";
    if (this->getSumas()[suma] <= 5) {
      int64_t verificacion = this->getSumas()[suma];
      if ((verificacion * -1) > 5) {
        this->ImprimirSumaPrimos(this->getSumandos()[suma], true);
      } else {
        std::cout << "NA" << std::endl;
      }
    } else {
      this->ImprimirSumaPrimos(this->getSumandos()[suma], false);
    }
  }
}

void ConjeturaGoldbach::ImprimirSumaPrimos(std::vector<std::vector<int64_t>>
    sumaPrimos, bool imprimir) {
  std::cout << sumaPrimos.size() << " sums" << std::endl;
  if (imprimir) {
    for (auto it = sumaPrimos.begin(); it != sumaPrimos.end(); it++) {
      const std::vector<int64_t>& int64_terno = *it;
      for (auto it2 = int64_terno.begin(); it2 != int64_terno.end(); it2++) {
        std::cout << *it2;
        if (it2 != int64_terno.end() - 1) {
          std::cout << "+";
        }
      }
      std::cout << ", ";
    }
    std::cout << std::endl;
  }
}

int64_t ConjeturaGoldbach::getSumasEncontradas() {
  return this->sumasEncontradas;
}

void ConjeturaGoldbach::consume(NumeroG numeroG) {
  // std::cout << "trabajando" << std::endl;
  std::vector<int64_t> trabajo;
  trabajo.push_back(numeroG.numero);
  this->trabajarConjeturaGoldbach(trabajo);
  numeroG.totalSumas = this->sumasEncontradas;
  //! VERIFICAR SI CUANDO EL NUMERO ES NEGATIVO, PERO INVALIDO
  //! POR EJEMPLO, -2, SUCEDE ALGUN PROBLEMA EN ESTA SECCION!!!
  // std::vector<std::vector<int64_t>> prueba = this->sumandos.back();
  if (numeroG.numero < 0) {
//!    numeroG.direccionRequest->setSuma(this->sumandos[0],
  //!  numeroG.posicion);
    std::vector<std::vector<int64_t>> prueba =
    this->sumandos.back();
    numeroG.direccionRequest->setSuma(prueba, numeroG.posicion);
  }
  this->produce(numeroG);
}

int ConjeturaGoldbach::run() {
  this->consumeForever();
  return EXIT_FAILURE;
}
