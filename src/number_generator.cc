#include "number_generator.h"

extern int number_generator_init(number_generator **ppNG, 
                                 int min,
                                 int max) 
{
    if (ppNG == nullptr) {
        return NUMBER_GENERATOR_INVALID;
    }

    // allocate number generator struct
    number_generator *ng = (number_generator *)malloc(sizeof(number_generator));
    if (ng == nullptr) {
        return NUMBER_GENERATOR_OUT_OF_MEMORY;
    }
    
    // initialize cpp obj
    NumberGenerator *num_gen;
    try {
        num_gen = new NumberGenerator(min, max);
    } catch (int err) {
        free(ng);
        return err;
    } catch (std::exception& e) {
        free(ng);
        return NUMBER_GENERATOR_UNKNOWN_ERROR;
    }

    // set opaque pointer to cpp obj
    ng->number_generator_obj = num_gen;

    // point to newly created number_generator struct
    *ppNG = ng;
    return NUMBER_GENERATOR_SUCCESS;
};

extern int number_generator_terminate(number_generator **ppNG) {
    if (ppNG == nullptr) {
        return NUMBER_GENERATOR_INVALID;
    }

    if (*ppNG == nullptr) {
        return NUMBER_GENERATOR_INVALID;
    }

    NumberGenerator *num_gen =
            static_cast<NumberGenerator *>((*ppNG)->number_generator_obj);

    delete num_gen;
    free(*ppNG);
    *ppNG = nullptr;
    return NUMBER_GENERATOR_SUCCESS;
};

extern int number_generator_get_random_number(number_generator *pNG, //
                             number_generator_response *response // OUT
) {
    if (pNG == nullptr) {
        return NUMBER_GENERATOR_INVALID;
    }

    if (response == nullptr) {
        return NUMBER_GENERATOR_RESPONSE_INVALID;
    }

    try {
        NumberGenerator *num_gen =
            static_cast<NumberGenerator *>(pNG->number_generator_obj);
        num_gen->GetRandomNumber(response);
    } catch (int err) {
        return err;
    } catch (std::exception &e) {
        return NUMBER_GENERATOR_UNKNOWN_ERROR;
    }
    return NUMBER_GENERATOR_SUCCESS;
};

// Date constructor
NumberGenerator::NumberGenerator(int minVal, int maxVal)
{
    if (minVal >= maxVal) {
        throw NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX;
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
