
#ifndef CONVERTER_H_
#define CONVERTER_H_

	#include <stdlib.h>
	#include <stdio.h>
	#include <stdbool.h>

	typedef enum conversion_direction {
		BINARY_TO_CSV = 1,
		CSV_TO_BINARY = 2
	} conversion_direction;

	typedef enum valid_structures {
		VISIBILITIES = 1,
		SOURCES      = 2,
		KERNELS      = 3,
		MATRIX       = 4
	} valid_structures;

	typedef struct configuration {

		int num_visibilities;
		int num_sources;
		int num_kernel_samples;
		int matrix_x_dimension;
		int matrix_y_dimension;

		conversion_direction direction;
		valid_structures structure;

		char* visibilities_input_file;
		char* visibilities_output_file;

		char* sources_input_file;
		char* sources_output_file;

		char* kernels_input_file;
		char* kernels_output_file;

		char* matrix_input_file;
		char* matrix_output_file;

	} configuration;

	typedef struct vis_uvw {
		float u;
		float v;
		float w;
	} vis_uvw;

	typedef struct visibility {
		float real;
		float imag;
		vis_uvw coords;
		float weight;
	} visibility;

	typedef struct source {
		float l;
		float m;
		float brightness;
	} source;

	bool perform_conversion(const configuration* config);

	bool csv_to_binary_visibilities(const configuration *config);

	bool binary_to_csv_visibilities(const configuration* config);

	bool csv_to_binary_sources(const configuration* config);

	bool binary_to_csv_sources(const configuration* config);

	bool csv_to_binary_kernels();

	bool binary_to_csv_kernels();

	bool csv_to_binary_matrix();

	bool binary_to_csv_matrix();

	bool is_valid_direction(const int direction);

	bool is_valid_structure(const int structure);

#endif /* CONVERTER_H_ */