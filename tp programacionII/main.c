#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void mostrarDatosArchivo(const char *nombreArchivo) {
    FILE *archivo;
    practicasLaboratorio practica;

    // Abre el archivo en modo lectura binaria
    archivo = fopen(nombreArchivo, "rb");

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Lee y muestra los datos del archivo
    while (fread(&practica, sizeof(practicasLaboratorio), 1, archivo) == 1) {
        // Muestra los datos solo si no han sido marcados como eliminados
        if (!practica.eliminado) {
            printf("Número de Práctica: %d\n", practica.nroPractica);
            printf("Nombre de Práctica: %s\n", practica.nombreDePractica);
            printf("Eliminado: %d\n", practica.eliminado);
            printf("--------------------------\n");
        }
    }

    // Cierra el archivo
    fclose(archivo);
}
int main()
{
    char seguir;
    int ingreso;
    ingresos dato;
  nodoPracticasLaboratorio * listaPracticas=NULL;
     listaPracticas=ArchivoAListaPracticas("lasPracticas.bin",listaPracticas);

    int existe = mostrarPracticasQueComienzanCon(listaPracticas);
    if (existe==0)
    {
        printf("No se encontro una practica con ese comienzo.\n");
    }

     system("pause");
    nodoArbolPacientes* arbol= NULL;
    mostrarDatosArchivo("lasPracticas.bin");
    mostrarArchivoPacientes("pacientes.dat");
    arbol=archivoAArbolPacientes("pacientes.dat",arbol);
    mostrarArbolINORDERPaciente(arbol);
    mostrarPacienteDeDNI(arbol);
    system("pause");

    listaPracticas= ArchivoAListaPracticas("lasPracticas.bin",listaPracticas);
    listaPracticas=modificacion_de_practica(listaPracticas);
    system("pause");
    mostrarListaPracticas(listaPracticas);
    system("pause");
    listaPracticas=alta_de_practica(listaPracticas);
    printf("LLEGOOOO");
     mostrarListaPracticas(listaPracticas);
    arbol=archivoAArbolPacientes("pacientes.dat",arbol);
    do
    {
        mostrarArbolINORDERPaciente(arbol);
        ingreso = cargarUnIngreso(arbol,&dato);
        printf("dni %i",dato.dniPaciente);
        if(ingreso==1){
                printf("dni %i",dato.dniPaciente);
        arbol = alta_de_ingreso (arbol,dato,listaPracticas);

        printf("Desea dar de alta a otro ingreso (s/n)\n");
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
        else{
                seguir='n';
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

