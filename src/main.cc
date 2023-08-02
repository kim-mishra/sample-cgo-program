#include "number_generator.h"
#include <stdio.h>
#include <stdlib.h>

std::string toError(int status) {
#define NUMBER_GENERATOR_SUCCESS 0
#define NUMBER_GENERATOR_INVALID 1
#define NUMBER_GENERATOR_UNKNOWN_ERROR 2
#define NUMBER_GENERATOR_OUT_OF_MEMORY 3
#define NUMBER_GENERATOR_RESPONSE_INVALID 4
#define NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX 5
  switch (status) {
  case NUMBER_GENERATOR_INVALID:
    return "NUMBER_GENERATOR_INVALID";
  case NUMBER_GENERATOR_UNKNOWN_ERROR:
    return "NUMBER_GENERATOR_UNKNOWN_ERROR";
  case NUMBER_GENERATOR_OUT_OF_MEMORY:
    return "NUMBER_GENERATOR_OUT_OF_MEMORY";
  case NUMBER_GENERATOR_RESPONSE_INVALID:
    return "NUMBER_GENERATOR_RESPONSE_INVALID";
  case NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX:
    return "NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX";
  default:
    return "NUMBER_GENERATOR_UNCLASSIFIED_ERROR";
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "usage: " << argv[0] << " min max\n";
    exit(1);
  }

  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  number_generator *pNumGen;
  int status = number_generator_init(&pNumGen, min, max);
  if (status != NUMBER_GENERATOR_SUCCESS) {
    std::cerr << toError(status) << "\n";
    exit(status);
  }

  number_generator_response resp;
  status = get_random_number(pNumGen, &resp);
  if (status != NUMBER_GENERATOR_SUCCESS) {
    std::cerr << toError(status) << "\n";
    exit(status);
  }

  std::cout << resp.num << "\n";
}
