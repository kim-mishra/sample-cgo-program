#include "number_generator.h"

extern int number_generator_init(number_generator **ppNG, 
                                 int min,
                                 int max) 
{
    if (ppNG == nullptr) {
        return NUMBER_GENERATOR_INVALID;
    }

    // allocate date struct
    number_generator *ng = (number_generator *)malloc(sizeof(number_generator));
    if (ng == nullptr) {
        return NUMBER_GENERATOR_OUT_OF_MEMORY;
    }
    
    // initialize cpp obj
    NumberGenerator *num_gen;
    try {
        num_gen = new NumberGenerator(min, max);
    } catch (std::exception& e) {
        free(ng);
        return NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX;
    }

    // set opaque pointer to cpp obj
    ng->number_generator_obj = num_gen;

    // point to newly created viam_carto struct
    *ppNG = ng;
    return NUMBER_GENERATOR_SUCCESS;
};

extern int get_random_number(number_generator *n, //
                             number_generator_response *response // OUT
) {
    if (n == nullptr) {
        return NUMBER_GENERATOR_INVALID;
    }

    if (response == nullptr) {
        return NUMBER_GENERATOR_RESPONSE_INVALID;
    }

    try {
        NumberGenerator *num_gen =
            static_cast<NumberGenerator *>(n->number_generator_obj);
        num_gen->GetRandomNumber(response);
    } catch (std::exception &e) {
        return NUMBER_GENERATOR_UNKNOWN_ERROR;
    }
    return NUMBER_GENERATOR_SUCCESS;
};




// Date constructor
NumberGenerator::NumberGenerator(int minVal, int maxVal)
{
    if (minVal >= maxVal) {
        throw std::runtime_error("min must be less than max");
    }
    min = minVal;
    max = maxVal;
}

// GetRandomNumber member function
void NumberGenerator::GetRandomNumber(number_generator_response *r) 
{
    srand(time(NULL));
    int range = static_cast<int>(max - min + 1);
    r->num = min + rand() % range;
}
