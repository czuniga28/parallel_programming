// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <iostream>
#include <string>
#include "GoldbachHtml.hpp"

GoldbachHtml::GoldbachHtml() {}

int GoldbachHtml::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachHtml::consume(GoldbachInfo *goldbachInfo) {
  goldbachInfo->impresionResultadosDefinitivos();
  delete(goldbachInfo);
}
