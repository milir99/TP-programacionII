#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream
#include "funciones.h"
=======
#include <string.h>
#include "funciones.c"

>>>>>>> Stashed changes

int main()
{
//nodoArbolPacientes *arbol=iniciarArbol ();

int eleccion;
do
{
    printf("\nMENU\n");
    printf("Cargar pacientes.\n");
    fflush(stdin);
    scanf("%i",&eleccion);
    switch (eleccion)
    {
    case 1:
        cargarArchivoPacientes ("paciente.dat");
        mostrarArchivoPacientes ("paciente.dat");
        break;
    }
}while(eleccion!=0);

}

