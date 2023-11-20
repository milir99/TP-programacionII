#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include "switch.h"
 char archivoEmpleado []="empleados.bin";
 char archivoPracticas[]="lasPracticas.bin";
 char archivoPXI []="PXI.bin";
 char archivoIngresos []="ingresos.bin";
 char archivoPacientes []= "paciente.bin";
//PASARLE A LOS SWITCH, EL ARBOL, Y LISTAS

void InicioDelPrograma()
{
    nodoPracticasLaboratorio* listaPracticasLaboratorio = inicListaPracticas();
    nodoArbolPacientes* arbolPacientes=iniciarArbol();
    nodoEmpleados* listaEmpleados= iniclistaEmpleados();
    FinDelPrograma(arbolPacientes,listaEmpleados,listaPracticasLaboratorio);

    pasarArchivoAlistaEmpleados(archivoEmpleado,listaEmpleados);

    ArchivoAListaPracticas(archivoPracticas,listaPracticasLaboratorio);

    archivoAArbolPacientes(archivoPacientes,arbolPacientes);

    archivoAListaIngresos(archivoIngresos,arbolPacientes);

    archivoAListaPXI(archivoPXI,arbolPacientes);

    mostrarArchivo(archivoEmpleado);
    int perfil=usuarioYclavePrincipio(listaEmpleados);

    FinDelPrograma(arbolPacientes,listaEmpleados,listaPracticasLaboratorio);


}
void FinDelPrograma(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas)
{    listaPracticaAArchivo(archivoPracticas,listaPracticas);
   pasarListaEmpleadosAarchivo(listaEmpleados,archivoEmpleado);
    listaPXIsAArchivo(arbolPaciente,archivoPXI);
    listaIngresosAArchivo(arbolPaciente,archivoIngresos);
    cargarArchivoPaciente(archivoPacientes,arbolPaciente);
    free(arbolPaciente);
    free(listaEmpleados);
    free(listaPracticas);

}
int usuarioYclavePrincipio(nodoEmpleados*listaEmpleados)
{
    char clave[20];
    char usuario[20];
    int intentos=0;
    int existe;

    printf(" _ ____  _                           _     _         __    _ \n");
    printf("(_) __ )(_) ___ _ ____   _____ _ __ (_) __| | ___   / /_ _| |\n");
    printf("| |  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\ / / _` | |\n");
    printf("| | |_) | |  __/ | | \\ V /  __/ | | | | (_| | (_) / / (_| |_|\n");
    printf("|_|____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/_/ \\__,_(_)\n");
    do
    {

        printf("Ingrese su nombre de usuario: ");
        fflush(stdin);
        fgets(usuario,sizeof(usuario),stdin);
         size_t longitud = strlen(usuario);
        if (usuario[longitud - 1] == '\n')
            {
            usuario[longitud - 1] = '\0';}

        printf("Ingrese su clave: ");
        fflush(stdin);
        fgets(clave,sizeof(clave),stdin);
         longitud = strlen(clave);
        if (clave[longitud - 1] == '\n')
            {
            clave[longitud - 1] = '\0';}

        existe=compararUsuario(clave,usuario,listaEmpleados);//ver que va en los parentesis

        if (existe!=0)
        {
            clearScreen();
            printf("Entrando al sistema");
            return existe;
        }

        else
        {
            printf("Usuario o contrase�a ingresado incorrectamente.Intentelo otra vez.\n");
            intentos++;
            if(intentos==3)
            {
                printf("Demasiados intentos fallidos.");
                printf("Comuniquese con un Administrador para generar cambio de contrase�a o usuario.");
                return 0;
            }
        }
    }
    while(1);
}

int compararUsuario(char clave[], char usuario[], nodoEmpleados *listaEmpleados) {
    int tipoperfil = 0;

    while (listaEmpleados != NULL) {
        printf("usuario %s   lista %s \n", usuario, listaEmpleados->empleado.usuario);

        if (strcmp(usuario, listaEmpleados->empleado.usuario) == 0 && strcmp(clave, listaEmpleados->empleado.clave) == 0) {
                printf("%s",listaEmpleados->empleado.perfil);
            if (strcmpi("administrador", listaEmpleados->empleado.perfil) == 0) {
                tipoperfil = 1; // Administrator
            } else if (strcmpi("profesional", listaEmpleados->empleado.perfil) == 0) {
                tipoperfil = 2; // Professional
            } else if (strcmpi("administrativo", listaEmpleados->empleado.perfil) == 0) {
                tipoperfil = 3; // Administrative
            }
            // Exit the loop early if a match is found
            break;
        }

        listaEmpleados = listaEmpleados->siguiente;
    }

    return tipoperfil;
}

//SWITCH PARA PROFESIONALES DE LABORATORIO
void switchAdministrador()
{
    int eleccion1;
    int eleccion2;
    int eleccion3;

    do
    {
        printf("Bienvenido/a!\n");
        printf("Ingrese la opcion que desee realizar o 0 para finalizar.\n");
        printf("1. Adminnistrar practicas.\n");
        printf("1. Ver pacientes. \n");
        fflush(stdin);
        scanf("%i", &eleccion1);

        switch(eleccion1)
        {
        case 1:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Agregar una practica.\n");
                printf("2. Modificar una practica.\n");
                printf("3. Buscar una practica.\n");
                printf("4. Mostrar todas las practicas.\n");
                printf("5. Dar de baja una practica.\n");
                fflush(stdin);
                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                default:
                    if(eleccion2!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion2 != 0);

        case 2:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Ver pacientes.\n");
                printf("2. Buscar un paciente.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:
                    break;

                case 2:
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion3 != 0);
            break;
        }
    }
    while(eleccion1!=0);
}

//SWITCH PARA EMPLEADOS
void switchEmpleados(nodoArbolPacientes** arbolPacientes)
{
    int eleccion1;
    int eleccion2;
    int eleccion3;
    char seguir;

    do
    {
        printf("Bienvenido/a!\n");
        printf("Ingrese la opcion que desee realizar o 0 para finalizar.\n");
        printf("1. Administrar paciente.\n");
        printf("2. Ver practicas.\n");
        printf("3. Ingresos.\n");
        fflush(stdin);
        scanf("%i", &eleccion1);

        switch(eleccion1)
        {
        case 1:
            //modificar solo al paciente, agregar, dar de baja, buscar, mostrar
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un paciente.\n");
                printf("2. Modificar SOLO un paciente.\n");
                printf("3. Buscar un paciente.\n");
                printf("4. Mostrar todos los pacientes.\n");
                printf("5. Dar de baja un paciente.\n");
                fflush(stdin);
                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:
                    do
                    {
                        *arbolPacientes=altaArbolPacientes(*arbolPacientes);
                        puts("----------------------------------------");
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
                    while(seguir!='s');
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                default:
                    if(eleccion2!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion2 != 0);
            break;
        case 2:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Ver practicas.\n");
                printf("2. Buscar practica.\n");

                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:
                    break;

                case 2:
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion3 != 0);
            break;
        case 3:
            //dar de alta, buscar, mostrar, modificar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un ingreso.\n");
                printf("2. Modificar un ingreso.\n");
                printf("3. Buscar un ingreso.\n");
                printf("4. Mostrar todos los ingresos.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion3 != 0);
            break;

        default:
            if(eleccion1!=0)
            {
                printf("Error, la opcion que ingreso es invalida.\n");
            }
        }
    }
    while(eleccion1!=0);
}

//SWITCH PARA ADMINISTRADORES
void switchAdmin()
{
    int eleccion1;
    int eleccion2;
    int eleccion3;

    do
    {
        printf("Bienvenido/a!\n");
        printf("Ingrese la opcion que desee realizar o 0 para finalizar.\n");
        printf("1. Administrar usuario/empleado. \n");
        printf("2. Adminnistrar practicas.\n");
        printf("3. Administrar paciente.\n");
        fflush(stdin);
        scanf("%i", &eleccion1);

        switch(eleccion1)
        {
        case 1:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un empleado.\n");
                printf("2. Modificar un empleado.\n");
                printf("3. Buscar un empleado.\n");
                printf("4. Mostrar todos los empleados.\n");
                printf("5. Dar de baja un empleado.\n");
                fflush(stdin);
                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:

                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                default:
                    if(eleccion2!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion2 != 0);

        case 2:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Agregar una practica.\n");
                printf("2. Modificar una practica.\n");
                printf("3. Buscar una practica.\n");
                printf("4. Mostrar todas las practicas.\n");
                printf("5. Dar de baja una practica.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion3 != 0);
            break;
        case 3:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un paciente.\n");
                printf("2. Modificar un paciente.\n");
                printf("3. Buscar un paciente.\n");
                printf("4. Mostrar todos los pacientes.\n");
                printf("5. Dar de baja un paciente.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }
            while(eleccion3 != 0);
            break;

        default:
            if(eleccion1!=0)
            {
                printf("Error, la opcion que ingreso es invalida.\n");
            }
        }
    }
    while(eleccion1!=0);
}
void mostrarUnaPersonaArchivo(empleadosDeLaboratorio aux)
{
    printf("\n-----------------\n");
    printf("DNI: %i\n", aux.dni);
    printf("Apellido y nombre: %s\n", aux.apellidoYNombre);
    printf("Telefono: %s\n", aux.telefono);
    printf("Usuario: %s\n", aux.usuario);
    printf("Clave: %s\n", aux.clave);
    printf("perfil: %s\n", aux.perfil);
    printf("-------------------\n");
}
void mostrarArchivo (char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo,"rb");
    empleadosDeLaboratorio aux;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(empleadosDeLaboratorio), 1, archi)==1)
        {
            mostrarUnaPersonaArchivo(aux);
        }
    }
    fclose(archi);
}
