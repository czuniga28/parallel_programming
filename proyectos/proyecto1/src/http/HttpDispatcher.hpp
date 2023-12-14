// Copyright Modificaciones Taller 2023 <paula.camachogonzalez@ucr.ac.cr>
#ifndef HTTPDISPATCHER_HPP_
#define HTTPDISPATCHER_HPP_

#include <cassert>
#include <stdexcept>
#include <string>
#include "Dispatcher.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "Structs.hpp"
#include "Queue.hpp"

class HttpDispatcher : public Dispatcher<std::string, reqRes_t> {
 public:
  int run() override;
  std::string extractKey(const reqRes_t& data) const override;
  void consume(reqRes_t data);
  void stop();
};


#endif  // HTTPDISPATCHER_HPP_
