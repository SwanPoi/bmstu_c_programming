#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "../inc/constants.h"
#include "../inc/struct.h"
#include "../inc/list_functions.h"
#include "../inc/struct_IO.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
	
    if (argc == 3 || argc == 4)
    {
        FILE *first_in_file = fopen(argv[1], "r");
        
        if (first_in_file)
        {
            node_t *first_films = NULL;

            rc = init_struct_list(first_in_file, &first_films);

            fclose(first_in_file);

            if (rc == ERR_OK && argc == 4)
            {
                FILE *second_in_file = fopen(argv[2], "r");

                if (second_in_file)
		            {
		                node_t *second_films = NULL;

		                rc = init_struct_list(second_in_file, &second_films);

		                fclose(second_in_file);

		                if (rc == ERR_OK)
		                    append(&first_films, &second_films);
		            }
		        }

		        if (rc == ERR_OK)
		        {
		            first_films = sort(first_films, films_comparator);

		            film_t *cheap_film = pop_front(&first_films);
		            free_film(cheap_film);

		            film_t *expensive_film = pop_back(&first_films);
		            free_film(expensive_film);

		            FILE *dest = fopen(argv[argc - 1], "w");

		            if (dest)
		            {
                    rc = print_all(dest, first_films);
                    fclose(dest);
		            }	
		            else
                    rc = ERR_OPEN_DEST;
		        } 

            free_list(first_films); 
        }
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_INVALID_ARGS;
    
    return rc;
}