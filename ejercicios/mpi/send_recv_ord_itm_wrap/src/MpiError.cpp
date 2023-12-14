// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <string>
#include "MpiError.hpp"
#include "Mpi.hpp"
  MpiError::MpiError(const std::string& message, const Mpi& mpi):
    std::runtime_error(
      mpi.getHostname() + ": "+
      std::to_string(mpi.getProcessNumber()) + ": " + message) {}
  MpiError::MpiError(const std::string& message, const Mpi& mpi,
    const int threadNumber)
    : std::runtime_error(
      mpi.getHostname() + ": "+
      std::to_string(mpi.getProcessNumber()) + "." +
      std::to_string(threadNumber) + ": " + message) {}