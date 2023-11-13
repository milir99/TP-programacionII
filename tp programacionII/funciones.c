<<<<<<< Updated upstream
#include <stdio.h>
#include <stdlib.h>
#define "funciones.h"
// FUNCION DE ALTAS POR INGRESO
nodoPracticasXIngreso alta_de_pxi(int nroDeIngreso)
{
    //Pedir datos de la practica
    //Buscar si existe la practica
    nodoPracticasXIngreso*nuevaPXI=crearNodoPXI(nroDeIngreso,nroPractica)
    //SI EXISTE LA PRACTIGA AGREGAR AL PRINCIPIO SI NO EXISTE IMPRIMIR CARTEL DE ERROR Y PEDIR QUE INGRESE LA PRACTICA NUEVAMENTE(HACER DO WHILE TAL VEZ PARA ESOY DEJAR QUE AGREGUE LA CANTIDAAD DE PRACTICAS QUE QUIERA),

}
//FUNCION CREAR NODO PRACTICAS X INGRESO
nodoPracticasXIngreso*crearNodoPXI(int nroIngreso,int nroPractica)
{
    nodoPracticasXIngreso*aux=(nodoPracticasXIngreso*) malloc(sizeof(nodoPracticasXIngreso));
    if(aux==NULL)
    {
        printf("Error al crear Nodo Practica x Ingreso");
    }
     aux.nroIngreso= nroIngreso;
 aux.nroPractica= nroPractica;
 aux.resultado=NULL;
aux.siguiente=NULL;

}

//FUNCION DE ALTA DE PACIENTE(A COMPLETAR)
nodoPaciente* alta_de_ingreso(nodoPaciente *paciente,char fechaIngreso[] ,char fechaRetiro[],int dniPaciente,int matriculaProfesional, int eliminado)
{
    nodoPaciente*existencia=existePaciente(paciente,dniPaciente);

    if(existencia==NULL)
    {
        printf("el Paciente NO existe.\n");
        printf("Debe darle de alta en el sistema ante de generar un ingreso.\n");

    }
    else
    {
        int nroIngreso= buscarUltimoNroIngreso(existencia->listaIngresos);
        nodoIngresos*nuevoIngresoNodo=crearNodoIngreso(nroIngreso,fechaIngreso,fechaRetiro,dniPaciente,matriculaProfesional, eliminado);
        nuevoIngresoNodo->listaDePracticas=alta_de_pxi(nroIngreso,);
        existencia->listaIngresos= agregarPpioIngreso(existencia->listaIngresos, nuevoIngresoNodo);
    }
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
//FUNCION DE EXISTENCIA DE PACIENTE(DONE)
nodoPaciente* existePaciente(nodoPaciente* pacientes, int dniPaciente)
{
    if (paciente == NULL) {
        return NULL;
    }

    if (dniPaciente == paciente->dniPaciente) {
        return paciente;
    } else if (dniPaciente < paciente->dniPaciente) {
        return buscarPorLegajo(paciente->izquierda, dniPaciente);
    } else {
        return buscarPorLegajo(paciente->derecha,dniPaciente);
    }
}

}

//FUNCION CREA NODO TIPO INGRESO(done)
nodoIngresos*crearNodoIngreso(int nroIngreso,char fechaIngreso[] ,char fechaRetiro[],int dniPaciente,int matriculaProfesional, int eliminado)
{
    nodoIngresos* aux= (nodoIngresos*) malloc(sizeof(nodoIngresos));
    aux.nroIngreso=nroIngreso;
    aux.fechaIngreso=fechaIngreso;
    aux.fechaRetiro=fechaRetiro;
    aux.dniPaciente;
    aux.matriculaProfesional=matriculaProfesional;
    aux.eliminado=0;
    aux.siguiente=NULL;
    if(aux==NULL)
    {
        printf("ERROR al crear el NODO INGRESO\n")
    }
}
=======
///ESTRUCTURAS
typedef struct
{
    char apellidoYnombre [40];
    int edad;
    int dni;
    char direccion [30];
    char telefono [15];
} Paciente;

typedef struct nodoArbolPacientes
{
    Paciente dato;
    struct nodoArbolPacientes *izq;
    struct nodoArbolPacientes *der;
} nodoArbolPacientes;

///ARBOLES DE PACIENTES
nodoArbolPacientes * iniciarArbol ()
{
    return NULL;
}
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

nodoArbolPacientes * insertarNodoArbol (nodoArbolPacientes *arbol, Paciente dato)
{
    if(arbol==NULL)
    {
        arbol = crearNodoArbol (dato);
    }
    else
    {

        if(strcmp(arbol->dato.apellidoYnombre,dato.apellidoYnombre)>0)
        {
            arbol->der = insertarNodoArbol (arbol->der,dato);
        }
        else
        {
            arbol->izq = insertarNodoArbol (arbol->izq,dato);
        }
    }
    return arbol;
}
void mostrarArbolINORDER (nodoArbolPacientes * arbol)
{
    mostrarArbolINORDER (arbol->izq);
    printf("\n------------------------------------\n");
    printf("Apellido y nombre: %s\n",arbol->dato.apellidoYnombre);
    printf("Edad: %i\n",arbol->dato.edad);
    printf("DNI: %i\n",arbol->dato.dni);
    printf("Direccion: %s\n",arbol->dato.direccion);
    printf("Telefono: %s\n",arbol->dato.telefono);
    printf("------------------------------------\n");
    mostrarArbolINORDER (arbol->der);
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

void cargarArchivoPacientes (char nombreArcPacientes[])
{
    char respuesta[3];
    do
    {
        Paciente nuevoPaciente;
        FILE * archi = fopen(nombreArcPacientes,"ab");
        if (archi!=NULL)
        {
            nuevoPaciente = cargarUnPaciente ();
            fwrite(&nuevoPaciente,sizeof(Paciente),1,archi);
            printf("¿Desea cargar otro paciente? ");
            fflush(stdin);
            scanf("%s",respuesta);
            if(strcmp(respuesta,"si")!=0 && strcmp(respuesta,"no")!=0)
            {
                printf("Respuesta invalida, vuelva a ingresar!\n");
                fflush(stdin);
                scanf("%s",respuesta);
            }
            fclose(archi);
        }
    }while(strcmp(respuesta,"si")==0);

}

>>>>>>> Stashed changes
