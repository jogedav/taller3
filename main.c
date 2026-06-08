#include <stdio.h>
#include "funciones.h"

int main()
{
    Libro biblioteca[MAX_LIBROS];
    int total_libros = 0;
    int opcion= 0;

    do
    {
        opcion = menu();

        switch (opcion)
        {
        case 1:
            RegistrarLibro(biblioteca, &total_libros);
            break;
        case 2:
            MostrarLibros(biblioteca, total_libros);
            break;
        case 3:
            BuscarLibro(biblioteca, total_libros);
            break;
        case 4:
            EstadoLibro(biblioteca, total_libros);
            break;
        case 5:
            EliminarLibro(biblioteca, total_libros);
            break;
        case 6:
            printf("Finalizo el programa\n");
            break;
        }
    } while (opcion != 6);

    return 0;
}