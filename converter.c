
#include "converter.h"

bool perform_conversion(const configuration* config)
{
	bool success = false;

	printf("%d %d\n", config->direction, config->structure);

	if(config->direction == BINARY_TO_CSV)
	{
		switch(config->structure) 
		{
			case VISIBILITIES: 
				success = binary_to_csv_visibilities(config); break;
			case SOURCES:
				success = binary_to_csv_sources(config); break;
			// KERNELS: break;
			// MATRIX: break;
		}
	}
	else // assumes CSV_TO_BINARY
	{
		printf("Performing conversion from CSV to binary format...\n");
		switch(config->structure) 
		{
			case VISIBILITIES: 
				success = csv_to_binary_visibilities(config); break;
			case SOURCES:
				success = csv_to_binary_sources(config); break;
			// KERNELS: break;
			// MATRIX: break;
		}
	}

	printf("Status of conversion: %s...\n", (success) ? "success" : "failed");

	return success;
}

bool csv_to_binary_visibilities(const configuration *config)
{
	FILE *csv_file = fopen(config->visibilities_input_file, "r");
	if(!csv_file)
	{	
		printf("Unable to locate CSV based visibilities file...\n");
		return false;
	}

	int num_vis_from_file = 0;
	fscanf(csv_file, "%d", &num_vis_from_file);
	printf("%d -> %d\n", config->num_visibilities, num_vis_from_file);

	if(config->num_visibilities != num_vis_from_file)
	{
		fclose(csv_file);
		return false;
	}

	FILE *bin_file = fopen(config->visibilities_output_file, "wb");
	if(!bin_file)
	{	
		printf("Unable to create binary based visibilities file...\n");
		fclose(csv_file);
		return false;
	}

	fwrite(&num_vis_from_file, sizeof(int), 1, bin_file);

	// scan in one visibility at a time from csv, send to bin
	visibility temp;

	for(int processed = 0; processed < num_vis_from_file; ++processed)
	{
		fscanf(csv_file, "%f %f %f %f %f %f", &temp.coords.u, &temp.coords.v, 
			&temp.coords.w, &temp.real, &temp.imag, &temp.weight);

		fwrite(&temp, sizeof(temp), 1, bin_file);
	}

	fclose(csv_file);
	fclose(bin_file);

	return true;
}

bool binary_to_csv_visibilities(const configuration *config)
{
	FILE *bin_file = fopen(config->visibilities_input_file, "rb");
	if(!bin_file)
	{	
		printf("Unable to locate binary based visibilities file...\n");
		fclose(bin_file);
		return false;
	}

	int num_vis_from_file = 0;
	fread(&num_vis_from_file, sizeof(int), 1, bin_file);
	printf("%d -> %d\n", config->num_visibilities, num_vis_from_file);
	
	if(config->num_visibilities != num_vis_from_file)
	{
		fclose(bin_file);
		return false;
	}

	FILE *csv_file = fopen(config->visibilities_output_file, "w");
	if(!csv_file)
	{	
		printf("Unable to create CSV based visibilities file...\n");
		fclose(bin_file);
		return false;
	}

	fprintf(csv_file, "%d\n", num_vis_from_file);

	// scan in one visibility at a time from bin, send to csv
	visibility temp;

	for(int processed = 0; processed < num_vis_from_file; ++processed)
	{
		fread(&temp, sizeof(temp), 1, bin_file);

		fprintf(csv_file, "%f %f %f %f %f %f\n", temp.coords.u, temp.coords.v,
			temp.coords.w, temp.real, temp.imag, temp.weight);
	}

	fclose(csv_file);
	fclose(bin_file);

	return true;
}

bool csv_to_binary_sources(const configuration *config)
{
	FILE *csv_file = fopen(config->sources_input_file, "r");
	if(!csv_file)
	{	
		printf("Unable to locate CSV based sources file...\n");
		return false;
	}

	int num_source_from_file = 0;
	fscanf(csv_file, "%d", &num_source_from_file);
	printf("%d -> %d\n", config->num_sources, num_source_from_file);

	if(config->num_sources != num_source_from_file)
	{
		fclose(csv_file);
		return false;
	}

	FILE *bin_file = fopen(config->sources_output_file, "wb");
	if(!bin_file)
	{	
		printf("Unable to create binary based sources file...\n");
		fclose(csv_file);
		return false;
	}

	fwrite(&num_source_from_file, sizeof(int), 1, bin_file);

	// scan in one source at a time from csv, send to bin
	source temp;

	for(int processed = 0; processed < num_source_from_file; ++processed)
	{
		fscanf(csv_file, "%f %f %f", &temp.l, &temp.m, &temp.brightness);

		fwrite(&temp, sizeof(temp), 1, bin_file);
	}

	fclose(csv_file);
	fclose(bin_file);

	return true;
}

bool binary_to_csv_sources(const configuration *config)
{
	FILE *bin_file = fopen(config->sources_input_file, "rb");
	if(!bin_file)
	{	
		printf("Unable to locate binary based sources file...\n");
		fclose(bin_file);
		return false;
	}

	int num_source_from_file = 0;
	fread(&num_source_from_file, sizeof(int), 1, bin_file);
	printf("%d -> %d\n", config->num_sources, num_source_from_file);
	
	if(config->num_sources != num_source_from_file)
	{
		fclose(bin_file);
		return false;
	}

	FILE *csv_file = fopen(config->sources_output_file, "w");
	if(!csv_file)
	{	
		printf("Unable to create CSV based sources file...\n");
		fclose(bin_file);
		return false;
	}

	fprintf(csv_file, "%d\n", num_source_from_file);

	// scan in one source at a time from bin, send to csv
	source temp;

	for(int processed = 0; processed < num_source_from_file; ++processed)
	{
		fread(&temp, sizeof(temp), 1, bin_file);

		fprintf(csv_file, "%f %f %f\n", temp.l, temp.m, temp.brightness);
	}

	fclose(csv_file);
	fclose(bin_file);

	return true;
}

bool csv_to_binary_kernels()
{
	return true;
}

bool binary_to_csv_kernels()
{
	return true;
}

bool csv_to_binary_matrix()
{
	return true;
}

bool binary_to_csv_matrix()
{
	return true;
}

bool is_valid_direction(const int direction)
{
	return (direction >= 1 && direction <= 2);
}

bool is_valid_structure(const int structure)
{
	return (structure >= 1 && structure <= 4);
}