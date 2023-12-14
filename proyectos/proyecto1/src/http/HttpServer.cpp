// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Modificaciones 2023 <paula.camachogonzalez@ucr.ac.cr>
#include <cassert>
#include <stdexcept>
#include <string>

#include "HomeWebApp.hpp"
#include "HttpApp.hpp"
#include "HttpServer.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "HttpDispatcher.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n";

HttpServer::HttpServer() {
  this->socketsQueue = new Queue<Socket>();
}

HttpServer::~HttpServer() {
  // Controlando fugas de memoria
  delete this->socketsQueue;
  for (size_t index = 0; index < this->workersCount; index++) {
    delete this->connectionHandlers[index];
  }
}

HttpServer& HttpServer::getInstance() {
  static HttpServer httpserver;
  return httpserver;
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}

int HttpServer::run(int argc, char* argv[]) {
  bool stopApps = false;
  // Se utiliza para el Ctrl C y el kill(usando dos terminales)
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
     // std::cout<<"en run de server"<<std::endl;
      Log::getInstance().start();

      // Start all web applications
      this->startApps();
      stopApps = true;
       // TODO(you) dispatcher

      this->connectionHandlers.resize(this->workersCount);
      // Reservar espacio n para consumidores
      // creacion de los n consumidores como connection handlers
      for (size_t index = 0; index < this->workersCount; index++) {
        this->connectionHandlers[index] = new HttpConnectionHandler();
      }

      this->dispatcher = new HttpDispatcher();
      this->dispatcher->createOwnQueue();

      // establecer comunicacion
      // creacion de los n consumidores como connection handlers
      for (size_t index = 0; index < this->workersCount; index++) {
        this->connectionHandlers[index]->setConsumingQueue(this->socketsQueue);
        this->connectionHandlers[index]->setProducingQueue(
          this->dispatcher->getConsumingQueue());
      }


       for (size_t index = 0; index < this->applications.size(); ++index) {
      //  std::cout<<"llave es "<<this->applications[index]->key<<std::endl;
         std::string appKey = this->applications[index]->getKey();
         this->dispatcher->registerRedirect(this->applications[index]->getKey(),
         this->applications[index]->getEntranceQueue());
         if (appKey == "/") {
           HomeWebApp* homeWebApp = dynamic_cast<HomeWebApp*>(
            this->applications[index]);
           homeWebApp->homeConsumer->setProducingQueue(
            dispatcher->getConsumingQueue());
         }
       }



      for (size_t index = 0; index < this->workersCount; index++) {
        this->connectionHandlers[index]->startThread();
      }

      this->dispatcher->startThread();
     // std::cout<<"despues de start dispatcher de server"<<std::endl;
      // Start waiting for connections
      // TODO(you): Log the main thread id
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));

      // Accept all client connections. The main process will get blocked
      // running this method and will not return. When HttpServer::stop() is
      // called from another execution thread, an exception will be launched
      // that stops the acceptAllConnections() invocation and enters in the
      // catch below. Then, the main thread can continue stopping apps,
      // finishing the server and any further cleaning it requires.

      this->acceptAllConnections();
    // std::cout<<"despues de accept all connections de server"<<std::endl;
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
// std::cout<<"despues del catch de server"<<std::endl;
  this->sendEmpySockects();
  this->waitingFinish();

  // If applications were started
  if (stopApps) {
    this->stopApps();
  }

  // Stop the log service
  Log::getInstance().stop();
  return EXIT_SUCCESS;
}
// enio de paquetes vacios
void HttpServer::sendEmpySockects() {
  for (size_t index = 0; index < this->workersCount; index++) {
    this->socketsQueue->enqueue(Socket());
  }
}
// espera a finalizacion individual
void HttpServer::waitingFinish() {
  for (size_t index = 0; index < this->workersCount; index++) {
    this->connectionHandlers[index]->waitToFinish();
    std::cout << "Closing thread: subprocess "<< index << std::endl;
  }
  std::cout << "All closed" << std::endl;
}

void HttpServer::startApps() {
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->start();
  }
}

void HttpServer::stopApps() {
  // Stop web applications. Give them an opportunity to clean up
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->stop();
  }
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests. When stopListing()
  // method is called -maybe by a secondary thread-, the web server -running
  // by the main thread- will stop executing the acceptAllConnections() method.
  this->stopListening();
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  this->workersCount = std::thread::hardware_concurrency();

  if (argc >= 3) {  // se aumenta en uno por aumeto de
  // posibles parametros ingresados
    this->port = argv[1];
    this->workersCount = std::stoi(argv[2]);
  } else if (argc >= 2) {
    this->port = argv[1];
  }

  return true;
}

void HttpServer::handleClientConnection(Socket& client) {
  this->socketsQueue->enqueue(client);
}

// TODO(you): Move the following methods to your HttpConnectionHandler

bool HttpServer::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
    std::string("connection established with client ") + address.getIP()
    + " port " + std::to_string(address.getPort()));

  // Print HTTP request
  Log::append(Log::INFO, "request", httpRequest.getMethod()
    + ' ' + httpRequest.getURI()
    + ' ' + httpRequest.getHttpVersion());

  return this->route(httpRequest, httpResponse);
}

// TODO(you): Provide HttpConnectionHandler access to the array of web apps

bool HttpServer::route(HttpRequest& httpRequest, HttpResponse& httpResponse) {
  // Traverse the chain of applications
  for (size_t index = 0; index < this->applications.size(); ++index) {
    // If this application handles the request
    HttpApp* app = this->applications[index];
    if (app->handleHttpRequest(httpRequest, httpResponse)) {
      return true;
    }
  }

  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

bool HttpServer::serveNotFound(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <p>The requested resouce was not found on this server.</p>\n"
    << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
