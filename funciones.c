#include <stdio.h>
#include <string.h>
#include "funciones.h"



int ValidarEnteroConRango(int a, int b){
    int n;
    int aux;
    do
    {
        aux = scanf("%d", &n);
        while((getchar())!='\n'); 
        if (aux != 1 || n < a || n > b)
        {
            printf("Error: El valor ingresado es incorrecto\n");
            printf("Vuelva a ingresarlo: ");
        }
        
    } while (aux != 1 || n < a || n > b);
    return n;
}

void leerCadena(char *cadena, int n){
    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    if(cadena[len] == '\n') { 
        cadena[len] = '\0';
    }
}



int menu(){
    printf("\n=== GESTION DE BIBLIOTECA ===\n");
    printf("Seleccione una opcion:\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar la lista completa de libros\n");
    printf("3. Buscar libro por ID o Titulo\n"); 
    printf("4. Actualizar el estado de un libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf(">> ");
    int opc = ValidarEnteroConRango(1, 6);
    return opc;
}



void RegistrarLibro(Libro *libros, int *n){
    if (*n >= MAX_LIBROS)
    {
        printf("Error. La biblioteca esta llena\n");
        return;
    }
    
    int repetido;
    do {
        repetido = 0; 
        
        printf("Ingrese el ID del libro %d: ", (*n) + 1);
        libros[*n].id = ValidarEnteroConRango(1, 999999);
        
        
        for (int i = 0; i < *n; i++) {
            if (libros[i].id == libros[*n].id && libros[i].estado1 == 1) {
                printf("Error: El ID ya existe. El codigo del libro debe ser unico.\n");
                repetido = 1;
                break;
            }
        }
    } while (repetido == 1);

    printf("Ingrese el titulo del libro %d: ", (*n) + 1);
    leerCadena(libros[*n].titulo, 100);
    
    printf("Ingrese el nombre del autor del libro %d: ", (*n) + 1);
    leerCadena(libros[*n].autor, 50);
    
    printf("Ingrese el año de publicacion del libro %d: ", (*n) + 1);
    libros[*n].anioPublicacion = ValidarEnteroConRango(1800, 2026);
    
    strcpy(libros[*n].estado, "Disponible");
    libros[*n].estado1 = 1; 
    
    printf("Libro Registrado!\n");
    (*n)++;
}

void MostrarLibros(Libro *libros, int n){
    int hayLibros = 0;
    printf("\n#\tID\tTitulo\t\t\tAutor\t\t\tAño\tDisponibilidad\n");
    printf("------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        if (libros[i].estado1 == 1) 
        {
            printf("%d\t%d\t%-20.20s\t%-20.20s\t%d\t%s\n", i+1,
                                                    libros[i].id,
                                                    libros[i].titulo,
                                                    libros[i].autor,
                                                    libros[i].anioPublicacion,
                                                    libros[i].estado);
            hayLibros = 1;
        }
    }
    if (!hayLibros) {
        printf("No hay libros registrados o activos en la biblioteca.\n");
    }
}

void BuscarLibro(Libro *libros, int n){
    printf("\nBuscar por:\n1. ID\n2. Titulo\n>> ");
    int opcion = ValidarEnteroConRango(1, 2);
    int encontrado = 0;

    if (opcion == 1) {
        printf("Ingrese el ID del libro a buscar: ");
        int idBuscado = ValidarEnteroConRango(1, 999999);
        for (int i = 0; i < n; i++) {
            if (libros[i].estado1 == 1 && libros[i].id == idBuscado) {
                printf("\nLibro encontrado: ID: %d, Titulo: %s, Autor: %s, Año: %d, Estado: %s\n", 
                       libros[i].id, libros[i].titulo, libros[i].autor, 
                       libros[i].anioPublicacion, libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    } else {
        char tituloBuscado[100];
        printf("Ingrese el titulo exacto: ");
        leerCadena(tituloBuscado, 100);
        for (int i = 0; i < n; i++) {
            if (libros[i].estado1 == 1 && strcmp(libros[i].titulo, tituloBuscado) == 0) {
                printf("\nLibro encontrado: ID: %d, Titulo: %s, Autor: %s, Año: %d, Estado: %s\n", 
                       libros[i].id, libros[i].titulo, libros[i].autor, 
                       libros[i].anioPublicacion, libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Error. No se encontro ningun libro con esos datos.\n");
    }
}

void EstadoLibro(Libro *libros, int n){
    int IDbuscar;
    int encontrado = 0;
    printf("\nIngrese el ID del libro: ");
    IDbuscar = ValidarEnteroConRango(1, 999999);
    for (int i = 0; i < n; i++)
    {
        if (libros[i].estado1 == 1 && libros[i].id == IDbuscar)
        {
            encontrado = 1;
            printf("Libro encontrado\n");
            printf("Estado actual: %s\n", libros[i].estado);
            if (strcmp(libros[i].estado, "Disponible") == 0)
            {
                strcpy(libros[i].estado, "Prestado");
                printf("El estado del libro ha cambiado a: Prestado\n");
            }else{
                strcpy(libros[i].estado, "Disponible");
                printf("El estado ha sido cambiado a: Disponible\n");
            }
            break;
        }
    }
    if (!encontrado)
    {
        printf("Error. No se encontro ningun libro activo con el ID %d \n", IDbuscar);
    }
}

void EliminarLibro (Libro *libros, int n){
    int IDbuscar;
    int encontrado = 0;
    MostrarLibros(libros, n);
    printf("Seleccione el ID del libro que desea eliminar: ");
    IDbuscar = ValidarEnteroConRango(1, 999999); 
    
    for (int i = 0; i < n; i++)
    {
        if (libros[i].id == IDbuscar && libros[i].estado1 == 1)
        {
            encontrado = 1;
            printf("Libro encontrado!\n");
            printf("Para eliminar ingrese 1, para cancelar ingrese 2: ");
            int confirmar = ValidarEnteroConRango(1, 2);
            if (confirmar == 1)
            {
                libros[i].estado1 = 0; 
                printf("Libro eliminado del sistema.\n");
            }else{
                printf("Operacion cancelada.\n");
            }
            break;
        }
    }
    if (!encontrado)
    {
        printf("Error. No se encontro ningun libro activo con el ID %d \n", IDbuscar);
    }
}