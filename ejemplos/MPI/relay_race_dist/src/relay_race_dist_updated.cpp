// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <mpi.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#define fail(msg) throw std::runtime_error(msg)

void simulate_relay_race(int argc, char* argv[], int process_number
  , int process_count);
void run_stage1(int stage1_delay, int process_number, int team_count);
void run_stage2(int stage2_delay, int process_number, int team_count);
void referee(int team_count);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  // Inicializar el entorno MPI
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    try {
      int process_number = -1;
      // Obtener el número de proceso (o rango del host)
      MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
      // Obtener la cantidad de procesos en nuestro equipo o mundo
      int process_count = -1;
      MPI_Comm_size(MPI_COMM_WORLD, &process_count);

      char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
      int hostname_length = -1;\
      // Obtener el nombre del host
      MPI_Get_processor_name(process_hostname, &hostname_length);
      // Finalmente, hacemos lo que debemos hacer, en este caso,
      // simular la carrera de relevos
      simulate_relay_race(argc, argv, process_number, process_count);
    } catch (const std::runtime_error& exception) {
      std::cout << exception.what() << std::endl;
      error = EXIT_FAILURE;
    }
    MPI_Finalize();
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
    error = EXIT_FAILURE;
  }
  return error;
}
/**
 * @brief Simula una carrera de relevos
 * 
 * @param argc Cantidad de argumentos
 * @param argv Arreglo de argumentos
 * @param process_number Número del proceso
 * @param process_count Cantidad total de procesos
 *
 */
void simulate_relay_race(int argc, char* argv[], int process_number
  , int process_count) {
  if (argc == 3) {
    // Necesitamos que la cantidad de procesos sea mayor a 3 para tener al menos
    // 2 equipos y un árbitro, y necesitamos que la cantidad de procesos sea impar,
    // así siempre tenemos un árbitro y una cantidad par de equipos.
    if (process_count >= 3 && process_count % 2 == 1) {
      const int team_count = (process_count - 1) / 2;
      const int stage1_delay = atoi(argv[1]);
      const int stage2_delay = atoi(argv[2]);
      // Si somos el árbitro (proceso 0)
      if (process_number == 0) {
        referee(team_count);
      } else if (process_number <= team_count) {
        run_stage1(stage1_delay, process_number, team_count);
      } else {
        run_stage2(stage2_delay, process_number, team_count);
      }
    } else {
      fail("error: process count must be odd and greater than 3");
    }
  } else {
    fail("usage: relay_race_dist stage1_delay stage2_delay");
  }
}
/**
 * @brief Procedimiento para simular la etapa 1. Espera la barrera,
 * luego corre la etapa y envía el mensaje a su proceso compañero
 * para señalar que ha terminado la etapa (como en una carrera de relevos real)
 * 
 * @param stage1_delay 
 * @param process_number 
 * @param team_count
 */
void run_stage1(int stage1_delay, int process_number, int team_count) {
  // Esperar a la barrera
  if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could wait for barrier");
  }
  usleep(1000 * stage1_delay);
  // Enviar el mensaje al proceso compañero
  const int peer = process_number + team_count;
  // Crear un testigo booleano para el relevo
  bool baton = true;
  // send(&baton, 1, peer)
  if (MPI_Send(&baton, /*count*/ 1, MPI_C_BOOL, peer, /*tag*/ 0
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could not send baton");
  }
}
/**
 * @brief Procedimiento para simular la etapa 2. Espera la barrera,
 * luego espera el mensaje de su proceso compañero para señalar
 * el relevo y luego corre la etapa, finalmente señala al proceso árbitro
 * que ha terminado la etapa.
 * 
 * @param stage2_delay 
 * @param process_number 
 * @param team_count 
 */
void run_stage2(int stage2_delay, int process_number, int team_count) {
  // wait_barrier()
  if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could wait for barrier");
  }
  // Declarar el compañero
  int peer = process_number - team_count;
  // Declarar el testigo
  bool baton = false;
  // receive(&baton, 1, peer)
  if (MPI_Recv(&baton, /*capacity*/ 1, MPI_C_BOOL, /*source*/ peer
    , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    fail("could not receive baton");
  }
  // Correr la etapa
  usleep(1000 * stage2_delay);
  // send(&peer, 1, 0)
  // Enviar el mensaje al proceso árbitro (proceso 0)
  // para señalar que hemos terminado la etapa
  if (MPI_Send(&peer, /*count*/ 1, MPI_INT, /*target*/ 0, /*tag*/ 0
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could not send team number to referee");
  }
}
/**
 * @brief Procedimiento para simular al árbitro. Espera la barrera,
 * luego espera los mensajes de los procesos para señalar que
 * han terminado la etapa 2 y luego imprime los resultados.
 * 
 * @param team_count 
 */
void referee(int team_count) {
  // El tiempo del árbitro será el tiempo real
  // Aquí usamos la función mpi_wtime() para obtener el tiempo
  const double start_time = MPI_Wtime();
  // wait_barrier()
  if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("error: could wait for barrier");
  }
  int place = 0;
  for (int index = 0; index < team_count; ++index) {
    int team = 0;
    // receive(&team, 1, any_process)
    if (MPI_Recv(&team, /*capacity*/ 1, MPI_INT, MPI_ANY_SOURCE
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("error: could not receive team number");
    }
    const double elapsed = MPI_Wtime() - start_time;
    ++place;
    std::cout << "Place " << place << ": team " << team << " in " << elapsed
      << "s" << std::endl;
  }
}