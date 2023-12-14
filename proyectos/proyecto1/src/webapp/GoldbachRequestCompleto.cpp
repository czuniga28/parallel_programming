// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <iostream>
#include "GoldbachRequestCompleto.hpp"
#include "NumeroG.hpp"
#include "GoldbachInfo.hpp"

GoldbachRequestCompleto::GoldbachRequestCompleto() {}

int GoldbachRequestCompleto::run() {
  // std::cout << "empezo completo" << std::endl;
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachRequestCompleto::consume(NumeroG numeroG) {
  // std::cout << "encolado completo" << std::endl;
  if (numeroG.direccionRequest->hemosTerminado(numeroG)) {
    this->produce(numeroG.direccionRequest);
  }
}
