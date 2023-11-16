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


        nuevoIngresoNodo->listaDePracticas=alta_de_pxi(nuevoIngresoNodo->listaDePracticas,nroIngreso);

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
///CAMBIAR LUGAR A ARBOLES PACIENTE
nodoArbolPacientes* existePaciente(nodoArbolPacientes* pacientes, int dniPaciente)
{
    if (pacientes == NULL)
    {
        return NULL;
    }

    if (dniPaciente == pacientes->dato.dni && paciente.eliminado == 0)
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
    nodoIngresos* aux = (nodoIngresos*) malloc(sizeof(nodoIngresos));
    aux->dato.nroIngreso = dato.nroIngreso;
    strcpy(aux->dato.fechaIngreso,dato.fechaIngreso);
    strcpy(aux->dato.fechaRetiro,dato.fechaRetiro);
    aux->dato.dniPaciente = dato.dniPaciente;
    aux->dato.matriculaProfesional = dato.matriculaProfesional;
    aux->dato.eliminado = 0;
    aux->siguiente = NULL;
    if(aux == NULL)
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
nodoArbolPacientes * crearNodoArbol (paciente datoP)
{
    nodoArbolPacientes *aux=(nodoArbolPacientes*)malloc(sizeof(nodoArbolPacientes));
    strcpy(aux->dato.apellidoYnombre,datoP.apellidoYnombre);
    aux->dato.edad = aux->dato.dni;
    aux->dato.dni = datoP.dni;
    strcpy(aux->dato.direccion,datoP.direccion);
    strcpy(aux->dato.telefono,datoP.telefono);
    aux->der=NULL;
    aux->izq=NULL;
    aux->dato.eliminado = 0;
    return aux;
}

//INSERTAR NODO ARBOL PACIENTE
nodoArbolPacientes * insertarNodoArbolPaciente (nodoArbolPacientes *arbolPacientes, paciente dato)
{
    if(arbolPacientes == NULL)
    {
        arbolPacientes = crearNodoArbol (dato);
    }
    else
    {

        if(strcmp(arbolPacientes->dato.apellidoYnombre,dato.apellidoYnombre)>0)
        {
            arbolPacientes->der = insertarNodoArbolPaciente(arbolPacientes->der,dato);
        }
        else
        {
            arbolPacientes->izq = insertarNodoArbolPaciente(arbolPacientes->izq,dato);
        }
    }
    printf("Se insertaron los datos del archivo al arbol.\n");
    return arbolPacientes;
}


//MODIFICACION DEL PACIENTE EN EL ARBOL
/*Antes de usar esta funcion, se debe chequear que el arbol no este vacio, y que lo que devuelva no sea NULL*/
nodoArbolPacientes * modificacionPacientesArbol (nodoArbolPacientes * arbolPaciente)
{
    int eleccionModificar;
    int dniAbuscar;
    do
    {
        printf("Ingrese el DNI del paciente que quiere modificar: ");
        if (scanf("%i",&dniAbuscar)!=1)
        {
            while(getchar() != '\n');
            printf("La respuesta no es válida. Por favor, ingrese el DNI del paciente.\n");
        }
    }
    while(getchar() != '\n');

    nodoArbolPacientes * existeDNIpaciente = existePaciente(arbolPaciente,dniAbuscar);

    if(existeDNIpaciente!=NULL)
    {
        do
        {
            printf("Ingrese lo que desee modificar o 0 para finalzar.\n");
            printf("1. Nombre y apellido.\n");
            printf("2. Edad.\n");
            printf("3. DNI.\n");
            printf("4. Direccion.\n");
            printf("5. Telefono.\n");
            fflush(stdin);
            scanf("%i",&eleccionModificar);

            switch (eleccionModificar)
            {
            case 1:


                if(dniAbuscar != NULL)
                {
                    do
                    {
                        printf("Ingrese el nuevo nombre y apellido:");
                        fflush(stdin);
                        if(scanf("%s",existeDNIpaciente->dato.apellidoYnombre)!=1)
                        {
                            while(getchar() != '\n');
                            printf("La respuesta no es válida. Por favor, ingrese el nombre y apellido del paciente.\n");
                        }

                    }
                    while(getchar() != '\n');
                }
                break;
            case 2:
                do
                {
                    printf("Ingrese la nueva edad: ");
                    if(scanf("%i",&existeDNIpaciente->dato.edad)!=1);
                    {
                        while(getchar() != '\n');
                        printf("La respuesta no es válida. Por favor, ingrese la edad del paciente.\n");
                    }
                }
                while(getchar() != '\n');
                break;
            case 3:
                do
                {
                    printf("Ingrese el nuevo DNI: ");
                    if(scanf("%i",&existeDNIpaciente->dato.dni)!=1);
                    {
                        while(getchar() != '\n');
                        printf("La respuesta no es válida. Por favor, ingrese el DNI del paciente.\n");
                    }
                }
                while(getchar() != '\n');
                break;
            case 4:
                do
                {
                    printf("Ingrese la nueva direccion: ");
                    if(scanf("%i",&existeDNIpaciente->dato.direccion)!=1);
                    {
                        while(getchar() != '\n');
                        printf("La respuesta no es válida. Por favor, ingrese la direccion del paciente.\n");
                    }
                }
                while(getchar() != '\n');
                break;
            case 5:
                do
                {
                    printf("Ingrese el nuevo telefono: ");
                    if(scanf("%i",&existeDNIpaciente->dato.telefono)!=1);
                    {
                        while(getchar() != '\n');
                        printf("La respuesta no es válida. Por favor, ingrese el telefono del paciente.\n");
                    }
                }
                while(getchar() != '\n');
                break;
            default:
                if(eleccionModificar!=0)
                {
                    printf("Error, la opcion que ingreso es invalida.\n");
                }
            }
        }
        while(eleccionModificar!=0);
    }
    else
    {
        printf("El DNI ingresado es incorrecto, no se pueden hacer modificaciones.\n");
    }
    return existeDNIpaciente;
}

//ALTA PACIENTE EN EL ARBOL
nodoArbolPacientes * altaArbolPacientes (nodoArbolPacientes *arbolPacientes)
{
    paciente dato;
    char respuesta;
    do
    {
        dato = cargarUnPaciente ();
        nodoArbolPacientes * aux = existePaciente(arbolPacientes,dato.dni);
        if(aux==NULL)
        {
            arbolPacientes = crearNodoArbol(dato);
            printf("Desea ingresar paciente? ");
            fflush(stdin);
            scanf("%c",&respuesta);
            respuesta = tolower(respuesta);

            if(respuesta != 's'&& respuesta!= 'n')
            {
                printf("Respuesta invalida, ingrese devuelta. ");
                fflush(stdin);
                scanf("%c",&respuesta);
                respuesta = tolower(respuesta);
            }
        }
        else
        {
            printf("Este paciente ya existe, intentelo otra vez!\n");
            dato = cargarUnPaciente ();
        }
    }
    while(respuesta =='s');
    return arbolPacientes;
}

//DAR DE BAJA PACIENTE
nodoArbolPacientes * darBajaPaciente (nodoArbolPacientes* arbolPaciente)
{
    int dniAbuscar;
    do
    {
        printf("Ingrese el DNI del paciente que quiere modificar: ");
        if (scanf("%i",&dniAbuscar)!=1)
        {
            while(getchar() != '\n');
            printf("La respuesta no es válida. Por favor, ingrese el DNI del paciente.\n");
        }
    }
    while(getchar() != '\n');

    nodoArbolPacientes * existeDNIpaciente = existePaciente(arbolPaciente,dniAbuscar);

    if (existeDNIpaciente!=NULL)
    {
        existeDNIpaciente->dato.eliminado=1;
    }
    return existeDNIpaciente;
}



//CARGAR PACIENTE
paciente cargarUnPaciente ()
{
    paciente nuevoPaciente;
    do
    {
        printf("Ingrese nombre y apellido del paciente: ");
        fflush(stdin);
        if(scanf("%s",nuevoPaciente.apellidoYnombre)!=1)
        {
            while(getchar() != '\n');
            printf("Entrada no válida. Por favor, ingrese un nombre y apellido del paciente.\n");
        }
    }
    while(getchar() != '\n');

    do
    {
        printf("Ingrese edad del paciente: ");
        if((scanf("%i",&nuevoPaciente.edad)!=1))
        {
            while(getchar() != '\n');
            printf("Entrada no válida. Por favor, ingrese la edad del paciente.\n");
        }
    }
    while(getchar() != '\n');

    do
    {
        printf("Ingrese el DNI del paciente: ");
        if (scanf("%i",&nuevoPaciente.dni)!=1)
        {
            while(getchar() != '\n');
            printf("Entrada no válida. Por favor, ingrese el DNI del paciente.\n");
        }
    }
    while(getchar() != '\n');

    do
    {
        printf("Ingrese la direccion del paciente: ");
        fflush(stdin);
        if ((scanf("%s",nuevoPaciente.direccion)!=1))
        {
            while(getchar() != '\n');
            printf("Entrada no válida. Por favor, ingrese la direccion del paciente.\n");
        }
    }
    while(getchar() != '\n');

    do
    {
        printf("Ingrese el telefono del paciente: ");
        fflush(stdin);
        if ((scanf("%s",nuevoPaciente.telefono)!=1))
        {
            while(getchar() != '\n');
            printf("Entrada no válida. Por favor, ingrese el telefono del paciente.\n");
        }
    }
    while(getchar() != '\n');

    return nuevoPaciente;
}

//MOSTRAR EN ORDEN EL ARBOL
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes)
{
    mostrarArbolINORDERPaciente(arbolPacientes->izq);
    printf("\n------------------------------------\n");
    printf("Apellido y nombre: %s\n",arbolPacientes->dato.apellidoYnombre);
    printf("Edad: %i\n",arbolPacientes->dato.edad);
    printf("DNI: %i\n",arbolPacientes->dato.dni);
    printf("Direccion: %s\n",arbolPacientes->dato.direccion);
    printf("Telefono: %s\n",arbolPacientes->dato.telefono);
    printf("------------------------------------\n");
    mostrarArbolINORDERPaciente (arbolPacientes->der);
}

///ARCHIVO DE PACIENTES
void mostrarUnPaciente (paciente nuevoPaciente)
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
    paciente nuevoPaciente;
    FILE *archi=fopen(nombreArcPacientes,"rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&nuevoPaciente,sizeof(paciente),1,archi);
            if(!feof(archi))
            {
                mostrarUnPaciente (nuevoPaciente);
            }
        }
        fclose(archi);
    }
}

///CARGAR DE ARBOL A ARCHIVO DE PACIENTES
void cargarArchivoPaciente (char nombreArcPacientes[],nodoArbolPacientes * arbolPacientes)
{
    FILE *archi=fopen(nombreArcPacientes,"wb");
    if(archi!=NULL)
    {
        cargarArchivoPacientesDelArbol (archi, arbolPacientes);
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    printf("Se cargaron los datos del arbol al archivo.\n");
}
void cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes)
{
    if(arbolPacientes)
    {
        cargarArchivoPacientesDelArbol (archi,arbolPacientes->izq);
        fwrite(&arbolPacientes->dato,sizeof(paciente),1,archi);
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
    }
    else
    {
        printf("El empleado ya existe.\n");
    }
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
    aux->empleado.dni = dato.dni;
    aux->empleado.telefono = dato.telefono;
    strcpy(aux->empleado.apellidoYNombre, dato.apellidoYNombre);
    strcpy(aux->empleado.clave, dato.clave);
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
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

