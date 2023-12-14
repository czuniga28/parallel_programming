#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <sys/random.h>
#include <stdlib.h>
#include <time.h>

void* shotPut(void* threadNumber);

int main(int argc, char* argv[]) {
  assert(argc == 2);

  size_t teamSize = 0;
  sscanf(argv[1], "%zu", &teamSize);
  if (teamSize % 2 == 0) {
    fprintf(stderr, "Error: could not execute the program\n");
  }

  size_t teamSize2 = teamSize * 2;

  double* distances[teamSize2];
  size_t points_t1 = 0;
  size_t points_t2 = 0;

  pthread_t thread[teamSize2];
  int threadCreation[teamSize2];

  for (size_t threadNum = 0; threadNum < teamSize2; threadNum++) {
    threadCreation[threadNum] = pthread_create(&thread[threadNum], /*attr*/ NULL, 
    shotPut, /*arg*/ (void*) threadNum);
    if (threadCreation[threadNum] != 0) {
          fprintf(stderr, "Error: could not create thread #%zu\n", threadNum);
        }
  } 

  for (size_t threadNum = 0; threadNum < teamSize2; threadNum++) {
    pthread_join(thread[threadNum], (void**)&distances[threadNum]);
  }

  for (size_t threadNum = 0; threadNum < teamSize2; threadNum++) {
    size_t biggerThreadNum = threadNum++;
    if (distances[threadNum] > distances[biggerThreadNum]) {
      points_t1++;
    } else {
      points_t2++;
    }
  }

  if (points_t1 > points_t2) {
    printf("result %zu:%zu, team 1 wins\n", points_t1, points_t2);
  } else {
    printf("result %zu:%zu, team 2 wins\n", points_t2, points_t1);
  }

  for (size_t i = 0; i < teamSize2; i++){
    free(distances[i]);
  }
}

void* shotPut(void* threadNumber) {
  const size_t rank = (size_t) threadNumber;
  double* maxDistance = (double*)calloc(1, sizeof(double));
  double* newDistanceFinal = (double*)calloc(1, sizeof(double));
  unsigned int seed = (unsigned int)time(NULL);

  for (size_t shot = 0; shot < 3; shot++) {
    size_t newDisPt1 = (size_t)rand_r(&seed) % 26;
    size_t newDisPt2 = (size_t)rand_r(&seed) % 26;
    *newDistanceFinal = (double)(newDisPt1 + (newDisPt2 / 31.0));
    if (*maxDistance < *newDistanceFinal) {
      *maxDistance = *newDistanceFinal;
    }
  }
  // size_t teamMemberNum = (rank / 2) + 1;
  if (rank % 2 == 0) {
    printf ("1.%zu: best shot put %lfm\n", rank, *maxDistance);
  } else {
    printf ("2.%zu: best shot put %lfm\n", rank, *maxDistance);
  }
  free(newDistanceFinal);
  return (void*)maxDistance;
}