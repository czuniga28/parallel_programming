// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include "CribaEratostenes.hpp"

  void CribaEratostenes::calcularPrimos(int64_t numMax) {
    // se guardan los primos en
    std::vector<int64_t> cribaResumen;
    std::vector<bool> primo(numMax + 1, true);

    for (int64_t i = 2; i * i <= numMax; i++) {  // identifica
        if (primo[i] == true) {
            for (int64_t j = i * i; j <= numMax; j += i)
                primo[j] = false;
        }
    }

    for (int64_t i = 2; i <= numMax; i++)  // resume
        if (primo[i])
            cribaResumen.push_back(i);

    this->numerosPrimos = cribaResumen;  // guarda en this
  }

  std::vector<int64_t> CribaEratostenes::getNumerosPrimos() {
    return this->numerosPrimos;
  }

  void CribaEratostenes::imprimirNumerosPrimos() {
    std::cout << std::endl;
        for (int64_t primo : this->numerosPrimos) {
            std::cout << primo << "\t";
        }
    std::cout << std::endl;
  }
