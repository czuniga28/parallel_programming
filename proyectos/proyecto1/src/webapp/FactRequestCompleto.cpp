// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#include <iostream>
#include "FactRequestCompleto.hpp"
#include "NumeroF.hpp"
#include "FactInfo.hpp"

FactRequestCompleto::FactRequestCompleto() {
}

int FactRequestCompleto::run() {
  // std::cout<<"empezo completo"<<std::endl;
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactRequestCompleto::consume(NumeroF numeroF) {
  // std::cout<<"encolando en completo"<<std::endl;
  if (numeroF.direccionRequest->hemosTerminado(numeroF)) {
    this->produce(numeroF.direccionRequest);
  }
}
