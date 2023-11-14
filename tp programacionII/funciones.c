#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
//FUNCION ALTA DE PRACTICAS
void alta_de_practica(practica dato)
{
    //VER SI SE PUEDE MANEJAR DIRECTAMENTE DESDE EL ARCHIVO

}
//FUNCIONES DE INGRESO///
//FUNCION  DE MODIFICACION DE INGRESOS
// solo pueden modificarse las fechas y matricula del solicitante
nodoIngresos* modificacion_de_ingreso(nodoIngresos* lista, int nroIngreso)
{  //en el main tenemos que buscar el nodo arbol paciente con el dni de la persona
    int eleccion;
    char cambiarchar[40];
    int cambiarint;
    nodoIngresos*existe= buscarIngreso(lista,nroIngreso);
    if(existe!=NULL)
    {
        do
        {
            printf("Elija numero de lo que desea modificar del ingreso\n");
            printf("1.Fecha de ingreso\n");
            printf("2.Fecha de retiro\n");
            printf("3.Matricula de profesional\n");
            printf("4. Salir ");
            fflush(stdin);
            scanf("%i",&eleccion);
            switch(eleccion)
            {
            case 1:
                printf("Ingrese la nueva fecha de ingreso: \n");
                fflush(stdin);
                scanf("%s",cambiarchar);
                strcpy(existe->dato.fechaIngreso,cambiarchar);
                break;
            case 2:
                printf("Ingrese la nueva fecha de retiro: \n");
                fflush(stdin);
                scanf("%s",cambiarchar);
                strcpy(existe->dato.fechaRetiro,cambiarchar);
                break;
            case 3:
                printf("Ingrese la nueva fecha de ingreso: \n");
                fflush(stdin);
                scanf("%i",&cambiarint);
                existe->dato.matriculaProfesional=cambiarint;
                break;
            default:
                if(eleccion!=4)
                {
                    printf("La opcion ingresada no existe.");
                }

            }
        }
        while(eleccion==4);
        }
    else
    {
        printf("El numero de ingreso NO existe.");
    }
    return existe;
}
//FUNCION BUSCAR INGRESO
nodoIngresos* buscarIngreso(nodoIngresos* lista, int nroIngreso)
{
    if(lista!= NULL)
    {

        if (lista->dato.nroIngreso == nroIngreso)
        {
            return lista;
        }
        return buscarIngreso(lista->siguiente,nroIngreso);

    }
    return NULL;
}

//FUNCION DE ALTA DE INGRESO (A COMPLETAR)
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes * paciente,ingresos dato)
{

    nodoArbolPacientes * existencia = existePaciente(paciente,dato.dniPaciente);


    if(existencia==NULL)
    {
        printf("El Paciente NO existe.\n");
        printf("Debe darle de alta en el sistema ante de generar un ingreso.\n");
        return NULL;

    }
    else
    {
        int nroIngreso = buscarUltimoNroIngreso(existencia->listaIngresos);
       printf("numero de ingreso %i\n",nroIngreso);

        nodoIngresos*nuevoIngresoNodo=crearNodoIngreso(dato);


        nuevoIngresoNodo->listaDePracticas=alta_de_pxi(nuevoIngresoNodo->listaDePracticas ,nroIngreso);

        if(nuevoIngresoNodo->listaDePracticas== NULL)
        {
           printf("Error al agregar las practicas.\n");
            return NULL;
        }
        else
        {
          existencia->listaIngresos= agregarPpioIngreso(existencia->listaIngresos, nuevoIngresoNodo);
        }
    }
    printf("Ingreso cargado Exitosamente\n");
    return existencia;
}

//FUNCION QUE DEVUELVE EL ULTIMO NUMERO DE INGRESO
int buscarUltimoNroIngreso(nodoIngresos* lista)
{
    int nroIngreso = 0;

    if (lista != NULL)
    {
        nodoIngresos* seg = lista;

        while (seg->siguiente != NULL)
        {
            nroIngreso = seg->dato.nroIngreso;
            seg = seg->siguiente;
        }
    }
   printf("dentro numero de ingreso %i",nroIngreso);
    return nroIngreso;
}
//FUNCION DE AGREGAR  INGRESO AL PRINCIPIO DE LA LISTA(DONE)
nodoIngresos*agregarPpioIngreso(nodoIngresos*lista,nodoIngresos* nuevoIngreso)
{
    if(lista==NULL)
    {
        lista=nuevoIngreso;
    }
    else
    {
        nuevoIngreso->siguiente=lista;
        lista=nuevoIngreso;
    }
    return lista;

}
//FUNCION DE EXISTENCIA DE PACIENTE(DONE)//PODRIA CAMBIARLE EL NOMBRE A BUSCAR
nodoArbolPacientes* existePaciente(nodoArbolPacientes* pacientes, int dniPaciente)
{
    if (pacientes == NULL)
    {
        return NULL;
    }

    if (dniPaciente == pacientes->dato.dni)
    {
        return pacientes;

    }
    else if (dniPaciente < pacientes->dato.dni)
    {
        return existePaciente(pacientes->izq, dniPaciente);
    }
    else
    {
        return existePaciente(pacientes->der,dniPaciente);
    }
}
//FUNCION CREA NODO TIPO INGRESO(done)
nodoIngresos*crearNodoIngreso(ingresos dato)
{
    nodoIngresos* aux= (nodoIngresos*) malloc(sizeof(nodoIngresos));
    aux->dato.nroIngreso=dato.nroIngreso;
    strcpy(aux->dato.fechaIngreso,dato.fechaIngreso);
    strcpy(aux->dato.fechaRetiro,dato.fechaRetiro);
    aux->dato.dniPaciente=dato.dniPaciente;
    aux->dato.matriculaProfesional=dato.matriculaProfesional;
    aux->dato.eliminado=0;
    aux->siguiente=NULL;
    if(aux==NULL)
    {
        printf("ERROR al crear el NODO INGRESO\n");
    }
    return aux;
}


//FUNCIONES DE PRACTICAS X INGRESO///
// FUNCION DE ALTA DE PREACTICAS POR INGRESO
nodoPracticasXIngreso *alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso)
{
    char eleccion;
    int nroPractica;


    do
    {
        printf("Ingrese codigo de la practica a realizar:\n");
        fflush(stdin);
        scanf("%i",&nroPractica);

        int existe= BuscarPractica("lasPracticas.bin",nroPractica);

        if(existe!= 0)
        {
            nodoPracticasXIngreso*nuevaPXI=crearNodoPXI(nroDeIngreso,nroPractica);

            lista= agregarPpioPXI(lista,nuevaPXI);

            printf("Desea ingresar otra practica a este ingreso? (s/n)\n");
            fflush(stdin);
            scanf("%c",&eleccion);
            eleccion = tolower(eleccion);

            while(eleccion!='s'&& eleccion!='n')
            {
                printf("Eleccion incorrecta, intentelo otra vez\n");
                printf("Desea ingresar otra practica a este ingreso? (s/n)");
                fflush(stdin);
                scanf("%c",&eleccion);
                eleccion= tolower(eleccion);
            }

        }
        else
        {
            printf("\n La practica Ingresada NO existe. \n");
            printf("Desea ingresar la practica otra vez? (s/n)\n");
            fflush(stdin);
            scanf("%c",&eleccion);
        }
        clearScreen();
    }
    while(eleccion=='s');
    if(lista==NULL)
    {
        return NULL;
    }
    else
    {
     printf("Lista de practicas X ingreso cargada Exitosamente\n");
    }

    return lista;
}
//FUNCION AGREGAR AL PRINCIPIO PRACTICAXINGRESO
nodoPracticasXIngreso*agregarPpioPXI (nodoPracticasXIngreso*lista,nodoPracticasXIngreso* nuevoIngreso)
{
    if(lista==NULL)
    {
        lista=nuevoIngreso;
    }
    else
    {
        nuevoIngreso->siguiente=lista;
        lista=nuevoIngreso;
    }
    return lista;

}
//FUNCION BUSCAR PRACTICA EN EL ARCHIVO.
int BuscarPractica(char archivo[], int nroPractica)
{
    practica aux;
    FILE* arch;
    arch = fopen(archivo, "rb");
    if (arch != NULL)
    {
        while (fread(&aux, sizeof(practica), 1, arch) == 1)
        {
            if (aux.nroPractica == nroPractica)
            {
                fclose(arch);
               return 1;
            }
        }

        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo de practicas");
    }
    return 0 ;
}

//FUNCION CREAR NODO PRACTICAS X INGRESO
nodoPracticasXIngreso*crearNodoPXI(int nroIngreso,int nroPractica)
{
    nodoPracticasXIngreso*aux=(nodoPracticasXIngreso*) malloc(sizeof(nodoPracticasXIngreso));
    if(aux==NULL)
    {
        printf("Error al crear Nodo Practica x Ingreso");
    }
    aux->dato.nroIngreso= nroIngreso;
    aux->dato.nroPractica= nroPractica;
    strcpy(aux->dato.resultado," ");
    aux->siguiente=NULL;
    return aux;

}

//FUNCION PARA BORRAR LO QUE HAY EN PANTALLA
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
