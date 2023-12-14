// Copyright 2023 <paula.camachogonzalez@ucr.ac.cr>
#include <iostream>
#include <string>
#include  "FactHtml.hpp"

FactHtml::FactHtml() {
}

int FactHtml::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactHtml::consume(FactInfo *factInfo) {
  factInfo->impresionResultadosDefinitivos();
  delete(factInfo);
}
