#ifndef NUMBER_GENERATOR_H
#define NUMBER_GENERATOR_H


// BEGIN C API
#ifdef __cplusplus
#include <cstdlib>
#include <exception>
#include <ctime>
#include <iostream>
extern "C" {
#endif

#include <stdlib.h>

#define NUMBER_GENERATOR_SUCCESS 0
#define NUMBER_GENERATOR_INVALID 1
#define NUMBER_GENERATOR_UNKNOWN_ERROR 2
#define NUMBER_GENERATOR_OUT_OF_MEMORY 3
#define NUMBER_GENERATOR_RESPONSE_INVALID 4
#define NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX 5

typedef struct number_generator {
    void *number_generator_obj;
} number_generator;

typedef struct number_generator_response {
    int num;
} number_generator_response;

extern int number_generator_init(number_generator **ppNG, //OUT
                                 int min,
                                 int max
);

extern int number_generator_terminate(number_generator **ppNG  // OUT
);

extern int get_random_number(number_generator *n, //
                             number_generator_response *response // OUT
);

#ifdef __cplusplus
}
#endif
// END C API

// BEGIN C++ API
#ifdef __cplusplus
class NumberGenerator
{
public:
    NumberGenerator(int min, int max);

    void GetRandomNumber(number_generator_response *r);
    int max;
    int min;
};

#endif
// END C++ API

#endif // DATE_H
