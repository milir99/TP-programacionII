#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main()
{
    char seguir;
    nodoArbolPacientes* arbol= NULL;

    arbol=archivoAArbolPacientes("pacientes.dat",arbol);
    do
    {
        mostrarArbolINORDERPaciente(arbol);
        arbol= modificacionPacientesArbol(arbol);
        printf("Desea dar de alta a otro Paciente? (s/n)\n");
        fflush(stdin);
        scanf("%c",&seguir);
        seguir = tolower(seguir);
        while(seguir!='s'&& seguir!='n')
        {
            printf("Eleccion incorrecta, intentelo otra vez\n");
            printf("Desea dar de alta a otro Paciente? (s/n)\n");
            fflush(stdin);
            scanf("%c",&seguir);
            seguir = tolower(seguir);
        }

    }
    while(seguir=='s');

    cargarArchivoPaciente("pacientes.dat",arbol);
    mostrarArchivoPacientes("pacientes.dat");

    system("color 5");
    /*/para cuando ingrese fechas
  char fechaIngresada[20];

    do {
        printf("Ingresa una fecha (YYYY-MM-DD): ");
        if (scanf("%19s", fechaIngresada) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }
    } while (!analizarFecha(fechaIngresada));/*/

    return 0;
}

