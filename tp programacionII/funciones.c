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
