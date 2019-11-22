
#include "converter.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	// argv[0] = program name
	// argv[1] = direction of conversion (1 = binary to csv, 2 = csv to binary)
	// argv[2] = data being converted (ie; visibilities, kernels, sources, etc)
	// argv[3] = input file  (example: "../{bin|csv}/my_output_file.{csv|bin}")
	// argv[4] = output file (example: "../{bin|csv}/my_output_file.{csv|bin}")

	// const int required_args = 5;
	// if(argc < required_args)
	// {
	// 	printf("You have not provided the correct number of command line "
	// 		"arguments. Expected %d arguments, but only found %d\n", required_args, argc);
	// 	return EXIT_FAILURE;
	// }

	configuration config;
	config.num_visibilities = 31395840;
	config.num_sources = 1895;

	// Visibilities CSV to Binary
	// config.visibilities_input_file = "../csv/GLEAM_large_visibilities.csv";
	// config.visibilities_output_file = "../bin/GLEAM_large_visibilities.dat";
	// config.direction = CSV_TO_BINARY;
	// config.structure = VISIBILITIES;

	// Visibilities Binary to CSV
	// config.visibilities_input_file = "../bin/GLEAM_medium_visibilities.dat";
	// config.visibilities_output_file = "../csv/GLEAM_medium_visibilities_again.csv";
	// config.direction = BINARY_TO_CSV;
	// config.structure = VISIBILITIES;

	// Sources CSV to Binary
	// config.sources_input_file = "../csv/GLEAM_large_sources.csv";
	// config.sources_output_file = "../bin/GLEAM_large_sources.dat";
	// config.direction = CSV_TO_BINARY;
	// config.structure = SOURCES;

	// Sources Binary to CSV
	// config.sources_input_file = "../bin/GLEAM_medium_sources.dat";
	// config.sources_output_file = "../csv/GLEAM_medium_sources_again.csv";
	// config.direction = BINARY_TO_CSV;
	// config.structure = SOURCES;

	if(!is_valid_direction(config.direction))
	{
		printf("Invalid conversion direction specified. Unable to perform "
			"conversion, terminating...\n");
		return EXIT_FAILURE;
	}

	if(!is_valid_structure(config.structure))
	{
		printf("Invalid structure specified, unable to perform "
			"conversion, terminating...\n");
		return EXIT_FAILURE;
	}

	bool success = perform_conversion(&config);

	return success;
}