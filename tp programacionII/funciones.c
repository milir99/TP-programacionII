#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>

// FUNCION DE ALTAS POR INGRESO
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

//
//
//
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
//
//
//

//FUNCION ALTA EMPLEADOS
nodoEmpleados * alta_de_empleados (nodoEmpleados * listaEmpleados, empleadosDeLaboratorio aux)
{
    nodoEmpleados * existe = existeEmpleado(listaEmpleados,aux.dni);
    if(existe == NULL)
    {
        nodoEmpleados * nuevo = crearNodoEmpleados(aux);
        listaEmpleados = agregarPpioEmpleados(listaEmpleados, nuevo);

        printf("El empleado fue agregado.\n");
    }else{
        printf("El empleado ya existe.\n");
    }
    return listaEmpleados;
}

//FUNCION PASAR DE LA LISTA AL ARCHIVO (a completar)
void pasarListaEmpleadosAarchivo(nodoEmpleados * listaEmpleados, char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo, "ab");


}

//FUNCION PASAR DE ARCHIVO A LISTA DOBLE EMPLEADOS
nodoEmpleados * pasarArchivoAlistaEmpleados(char nombreArchivo[], nodoEmpleados * listaEmpleados)
{
    FILE * archi = fopen(nombreArchivo, "rb");
    empleadosDeLaboratorio aux;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(empleadosDeLaboratorio), 1, archi)==1)
        {
            listaEmpleados = agregarPpioEmpleados(listaEmpleados,crearNodoEmpleados(aux));
        }
        fclose(archi);
    }else{
        printf("No se pudo abrir el archivo.\n");
    }
    printf("Se pasaron los datos del archivo a la lista doble.\n"); //BORRAR ANTES DE LA PRESENTACION
    return listaEmpleados;
}

//FUNCION AGREGAR AL PRINCIPIO LISTA DOBLE EMPLEADOS
nodoEmpleados * agregarPpioEmpleados (nodoEmpleados * empleados, nodoEmpleados * nuevo)
{
    nuevo->siguiente = empleados;
    if(empleados != NULL)
    {
        empleados->anterior = nuevo;
    }
    return empleados;
}

//FUNCION SI EXISTE UN EMPLEADO
nodoEmpleados * existeEmpleado(nodoEmpleados* empleado, int dniEmpleado)
{
    nodoEmpleados * actual = empleado;

    while(actual != NULL)
    {
        if (actual->empleado.dni == dniEmpleado)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

//FUNCION DE CREAR NODO TIPO EMPLEADO
nodoEmpleados * crearNodoEmpleados(empleadosDeLaboratorio dato)
{
    nodoEmpleados * aux = (nodoEmpleados*)malloc(sizeof(nodoEmpleados));
    if (aux == NULL)
    {
        printf("ERROR: No se pudo crear el nodo para el empleado.\n");
    }
    aux->empleado.DNI = dato.DNI;
    aux->empleado.telefono = dato.telefono;
    strcpy(aux->empleado.apellidoYnombre, dato.apellidoYnombre);
    strcpy(aux->empleado.contrasenia, dato.contrasenia);
    strcpy(aux->empleado.usuario, dato.usuario);
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

//INICIALIZAR LA LISTA DOBLE EMPLEADOS
nodoEmpleados * iniclistaEmpleados()
{
    return NULL;
}

//INICIALIZAR LA LISTA DOBLE PRACTICA POR INGRESO
nodoPracticasXIngreso * iniclistaPracticaXingreso()
{
    return NULL;
}
//FUNCION PARA BORRAR LO QUE HAY EN PANTALLA
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

