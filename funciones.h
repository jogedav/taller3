#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_LIBROS 10

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anioPublicacion;
    char estado[20];
    int estado1; 
} Libro;

// Prototipos actualizados
int ValidarEnteroConRango(int a, int b);
void leerCadena(char *cadena, int n);
int menu();
void RegistrarLibro(Libro *libros, int *n);
void MostrarLibros(Libro *libros, int n);
void BuscarLibro(Libro *libros, int n);
void EstadoLibro(Libro *libros, int n);
void EliminarLibro(Libro *libros, int n);

#endif