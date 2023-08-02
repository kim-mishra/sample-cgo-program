package main

/*
  #cgo LDFLAGS: -Lbuild -lnumber_generator -lstdc++
	#include "src/number_generator.h"
*/
import "C"

/*
	the above line needs to be directly below the comment where
	C code is in order for it to be registered as C code
*/
import (
	"errors"
	"fmt"
	"os"
	"strconv"
)

func getRandomNumber(min int, max int) (int, error) {
	// initialize pointer to C number_generator
	var pNumGen *C.number_generator
	status := C.number_generator_init(&pNumGen, C.int(min), C.int(max))
	if status != C.NUMBER_GENERATOR_SUCCESS {
		return 0, toError(status)
	}

	// initialize outParam
	resp := C.number_generator_response{}
	status = C.number_generator_get_random_number(pNumGen, &resp)
	if status != C.NUMBER_GENERATOR_SUCCESS {
		return 0, toError(status)
	}

	// get useful information from outParam and cast to go types
	num := int(resp.num)

	// free number generator struct
	status = C.number_generator_terminate(&pNumGen)
	if status != C.NUMBER_GENERATOR_SUCCESS {
		return 0, toError(status)
	}

	return num, nil

}

func toError(status C.int) error {
	if status == 0 {
		return errors.New("NUMBER_GENERATOR_SUCCESS")
	}
	if status == 1 {
		return errors.New("NUMBER_GENERATOR_INVALID")
	}
	if status == 2 {
		return errors.New("NUMBER_GENERATOR_UNKNOWN_ERROR")
	}
	if status == 3 {
		return errors.New("NUMBER_GENERATOR_OUT_OF_MEMORY")
	}
	if status == 4 {
		return errors.New("NUMBER_GENERATOR_RESPONSE_INVALID")
	}
	if status == 5 {
		return errors.New("NUMBER_GENERATOR_MIN_NOT_LESS_THAN_MAX")
	}
	return errors.New("ERROR NOT RECOGNIZED")
}

func main() {
	if len(os.Args) != 3 {
		fmt.Printf("usage %s min max\n", os.Args[0])
		os.Exit(1)
	}

	min, err := strconv.ParseInt(os.Args[1], 10, 8)
	if err != nil {
		fmt.Printf("%s must be an integer\n", os.Args[1])
		os.Exit(1)
	}

	max, err := strconv.ParseInt(os.Args[2], 10, 8)
	if err != nil {
		fmt.Printf("%s must be an integer\n", os.Args[2])
		os.Exit(1)
	}

	num, err := getRandomNumber(int(min), int(max))

	if err == nil {
		fmt.Printf("%d\n", num)
	} else {
		fmt.Println(err)
		os.Exit(1)
	}
}
