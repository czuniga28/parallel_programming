// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER

// TODO(you): mover estos includes a HttpServer.hpp
#include <csignal>
#include <iostream>
#include <thread>

#include "FactWebApp.hpp"
#include "GoldbachWebApp.hpp"
#include "HomeWebApp.hpp"
#include "HttpServer.hpp"

// TODO(you): Register a signal handler for Ctrl+C and kill, and stop the server
// TODO(you): Make your signal handler to print the thread id running it
void signalHandler(int signal) {
  std::cout << "Receiving signal from " << std::this_thread::get_id()<<
  " thread. Signal: " << signal << std::endl;
  // matar al programa (kill), haciendole stop a la unica instancia HttpServer
  // del programa (es lo que hace stop por debajo)
  HttpServer::getInstance().stop();
}


/// Start the web server
int main(int argc, char* argv[]) {
  // Create the web server
  // HttpServer httpServer; Aun no: primero signals, luego webApp y, por
  // ultimo, un HttpServer estatico:
  // registar manejo de señales para ctr+c y kill:
  // SIGINT se envia al proceso cuando se preciona ctr+c
  signal(SIGINT, signalHandler);
  // SIGTERM señal para pedir la terminacion de un programa
  signal(SIGTERM, signalHandler);
  // Create a factorization web application, and other apps if you want
  HttpServer& httpServer = HttpServer::getInstance();
  FactWebApp& factWebApp = FactWebApp::getInstance();
  GoldbachWebApp& goldbachWebApp = GoldbachWebApp::getInstance();
  HomeWebApp& homeWebApp = HomeWebApp::getInstance();

  // Register the web application(s) with the web server
  httpServer.chainWebApp(&goldbachWebApp);
  httpServer.chainWebApp(&factWebApp);
  httpServer.chainWebApp(&homeWebApp);

  // Run the web server
  return httpServer.run(argc, argv);
}

#endif  // WEBSERVER
