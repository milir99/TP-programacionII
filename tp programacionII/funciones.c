#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>

// FUNCION DE ALTAS POR INGRESO
nodoPracticasXIngreso alta_de_pxi(int nroDeIngreso)
{
    //Pedir datos de la practica
    //Buscar si existe la practica
//    nodoPracticasXIngreso*nuevaPXI=crearNodoPXI(nroDeIngreso,nroPractica);
   //SI EXISTE LA PRACTIGA AGREGAR AL PRINCIPIO SI NO EXISTE IMPRIMIR CARTEL DE ERROR Y PEDIR QUE INGRESE LA PRACTICA NUEVAMENTE(HACER DO WHILE TAL VEZ PARA ESOY DEJAR QUE AGREGUE LA CANTIDAAD DE PRACTICAS QUE QUIERA),
}
//FUNCION CREAR NODO PRACTICAS X INGRESO
//nodoPracticasXIngreso*crearNodoPXI(int nroIngreso,int nroPractica)
//{
//    nodoPracticasXIngreso*aux=(nodoPracticasXIngreso*) malloc(sizeof(nodoPracticasXIngreso));
//    if(aux==NULL)
//    {
//        printf("Error al crear Nodo Practica x Ingreso");
//    }
//    aux.nroIngreso= nroIngreso;
//    aux.nroPractica= nroPractica;
//    aux.resultado=NULL;
//    aux.siguiente=NULL;
//}

//FUNCION DE ALTA DE PACIENTE(A COMPLETAR)
//nodoIngreso* alta_de_ingreso(nodoArPaciente *paciente,char fechaIngreso[],char fechaRetiro[],int dniPaciente,int matriculaProfesional, int eliminado)
//{
//    nodoPaciente*existencia=existePaciente(paciente,dniPaciente);
//
//    if(existencia==NULL)
//    {
//        printf("el Paciente NO existe.\n");
//        printf("Debe darle de alta en el sistema ante de generar un ingreso.\n");
//    }
//    else
//    {
//        int nroIngreso= buscarUltimoNroIngreso(existencia->listaIngresos);
//        nodoIngresos*nuevoIngresoNodo=crearNodoIngreso(nroIngreso,fechaIngreso,fechaRetiro,dniPaciente,matriculaProfesional, eliminado);
//        nuevoIngresoNodo->listaDePracticas=alta_de_pxi(nroIngreso,);
//        existencia->listaIngresos= agregarPpioIngreso(existencia->listaIngresos, nuevoIngresoNodo);
//    }
//}

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

//FUNCION DE EXISTENCIA DE PACIENTE(DONE)
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
//nodoIngresos*crearNodoIngreso(int nroIngreso,char fechaIngreso[],char fechaRetiro[],int dniPaciente,int matriculaProfesional, int eliminado)
//{
//    nodoIngresos* aux= (nodoIngresos*) malloc(sizeof(nodoIngresos));
//    aux.nroIngreso=nroIngreso;
//    aux.fechaIngreso=fechaIngreso;
//    aux.fechaRetiro=fechaRetiro;
//    aux.dniPaciente;
//    aux.matriculaProfesional=matriculaProfesional;
//    aux.eliminado=0;
//    aux.siguiente=NULL;
//    if(aux==NULL)
//    {
//        printf("ERROR al crear el NODO INGRESO\n")
//    }
//}


///ARBOLES DE PACIENTES

    nodoArbolPacientes * iniciarArbol ()
{
    return NULL;
}
// CREAR NODO ARBOL PACIENTE
nodoArbolPacientes *crearNodoArbol (Paciente datoP)
{
    nodoArbolPacientes *aux=(nodoArbolPacientes*)malloc(sizeof(nodoArbolPacientes));
    strcpy(aux->dato.apellidoYnombre,datoP.apellidoYnombre);
    aux->dato.edad = aux->dato.dni;
    aux->dato.dni = datoP.dni;
    strcpy(aux->dato.direccion,datoP.direccion);
    strcpy(aux->dato.telefono,datoP.telefono);
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

//INSERTAR NODO ARBOL PACIENTE
nodoArbolPacientes * insertarNodoArbolPaciente (nodoArbolPacientes *arbolPacientes, Paciente dato)
{
    if(arbolPacientes==NULL)
    {
        arbolPacientes = crearNodoArbol (dato);
    }
    else
    {

        if(strcmp(arbolPacientes->dato.apellidoYnombre,dato.apellidoYnombre)>0)
        {
            arbolPacientes->der = insertarNodoArbol (arbolPacientes->der,dato);
        }
        else
        {
            arbolPacientes->izq = insertarNodoArbol (arbolPacientes->izq,dato);
        }
    }
    return arbolPacientes;
}

nodoArbolPacientes * altaArbolPacientes (nodoArbolPacientes *arbolPacientes)
{
    Paciente dato;
    char respuesta[3];
    do
    {
        dato = cargarUnPaciente ();
        nodoArbolPacientes * aux = existePaciente(arbolPacientes,dato.dni);
        if(arbolPacientes==NULL)
        {
            arbolPacientes = crearNodoArbol(dato);
            printf("Desea ingresar paciente? ");
            fflush(stdin);
            scanf("%c",respuesta);
            respuesta = tolower(respuesta);

            if(strcmp(strcmp(respuesta,"s")!=0) || strcmp(strcmp(respuesta,"n")!=0))
            {
                printf("Respuesta invalida, ingrese devuelta. ");
                fflush(stdin);
                scanf("%c",respuesta);
                respuesta = tolower(respuesta);
            }
        }
        else
        {
            printf("Este paciente ya existe, intentelo otra vez!\n");
            dato = cargarUnPaciente ();
        }

    }while(strcmp(respuesta,"s")==0);
}

//CARGAR PACIENTE
Paciente cargarUnPaciente ()
{
    Paciente nuevoPaciente;
    printf("Ingrese nombre y apellido del paciente: ");
    fflush(stdin);
    scanf("%s",nuevoPaciente.apellidoYnombre);

    printf("Ingrese edad del paciente: ");
    scanf("%i",&nuevoPaciente.edad);

    printf("Ingrese el DNI del paciente: ");
    scanf("%i",&nuevoPaciente.dni);

    printf("Ingrese la direccion del paciente: ");
    fflush(stdin);
    scanf("%s",nuevoPaciente.direccion);

    printf("Ingrese el telefono del paciente: ");
    fflush(stdin);
    scanf("%s",nuevoPaciente.telefono);
    return nuevoPaciente;
}

//MOSTRAR EN ORDEN EL ARBOL
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes)
{
    mostrarArbolINORDER (arbolPacientes->izq);
    printf("\n------------------------------------\n");
    printf("Apellido y nombre: %s\n",arbolPacientes->dato.apellidoYnombre);
    printf("Edad: %i\n",arbolPacientes->dato.edad);
    printf("DNI: %i\n",arbolPacientes->dato.dni);
    printf("Direccion: %s\n",arbolPacientes->dato.direccion);
    printf("Telefono: %s\n",arbolPacientes->dato.telefono);
    printf("------------------------------------\n");
    mostrarArbolINORDER (arbolPacientes->der);
}

///ARCHIVO DE PACIENTES
void mostrarUnPaciente (Paciente nuevoPaciente)
{
    printf("\n------------------------------------\n");
    printf("Apellido y nombre: %s\n",nuevoPaciente.apellidoYnombre);
    printf("Edad: %i\n",nuevoPaciente.edad);
    printf("DNI: %i\n",nuevoPaciente.dni);
    printf("Direccion: %s\n",nuevoPaciente.direccion);
    printf("Telefono: %s\n",nuevoPaciente.telefono);
    printf("------------------------------------\n");
}
void mostrarArchivoPacientes (char nombreArcPacientes[])
{
    Paciente nuevoPaciente;
    FILE *archi=fopen(nombreArcPacientes,"rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&nuevoPaciente,sizeof(Paciente),1,archi);
            if(!feof(archi))
            {
                mostrarUnPaciente (nuevoPaciente);
            }
        }
        fclose(archi);
    }
}

///CARGAR DE ARBOL A ARCHIVO DE PACIENTES
void cargarArchivoPaciente (char nombreArcPacientes,nodoArbolPacientes * arbolPacientes)
{
    Paciente nuevoPaciente;
    FILE *archi=fopen(nombreArcPacientes,"wb");
    if(archi!=NULL)
    {
        cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes);
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}
void cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes)
{
    if(arbolPacientes)
    {
        cargarArchivoPacientesDelArbol (archi,arbolPacientes->izq);
        fwrite(&arbolPacientes->dato,sizeof(Paciente),1,archi);
        cargarArchivoPacientesDelArbol (archi, arbolPacientes->der);
    }
}
