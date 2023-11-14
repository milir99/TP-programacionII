#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
//FUNCION ALTA DE PRACTICAS
void alta_de_practica(practica dato)
{
    //VER SI SE PUEDE MANEJAR DIRECTAMENTE DESDE EL ARCHIVO

}
//FUNCIONES DE INGRESO///
//FUNCION PARA COMPARAR FECHAS
/*/ompara dos fechas en formato "YYYY-MM-DD". Devuelve verdadero (1) si la primera fecha
 es anterior a la segunda, de lo contrario, devuelve falso (0)./*/
int esAnterior(const char *fecha1_str, const char *fecha2_str) {
    struct tm fecha1 = {0};
    struct tm fecha2 = {0};

    // Convierte las cadenas en estructuras tm
    if (sscanf(fecha1_str, "%d-%d-%d", &fecha1.tm_year, &fecha1.tm_mon, &fecha1.tm_mday) != 3 ||
        sscanf(fecha2_str, "%d-%d-%d", &fecha2.tm_year, &fecha2.tm_mon, &fecha2.tm_mday) != 3) {
        printf("Error al convertir las fechas.\n");
        return 0; // Error en la conversión
    }

    fecha1.tm_year -= 1900; // Ajusta el año según el formato tm
    fecha1.tm_mon -= 1;     // Ajusta el mes según el formato tm

    fecha2.tm_year -= 1900;
    fecha2.tm_mon -= 1;

    // Compara las fechas y devuelve true si fecha1 es anterior a fecha2
    return mktime(&fecha1) < mktime(&fecha2);
}
//FUNCION VERIFICAR FECHA
/*/verifica la validez de una fecha ingresada en formato "YYYY-MM-DD". Si es válida,devuelve 1;
 de lo contrario devulve 0 pero antes imprime fecha no valida./*/
int analizarFecha(const char *fechaIngresada) {
    int anio, mes, dia;
    int elementos_asignados = sscanf(fechaIngresada, "%d-%d-%d", &anio, &mes, &dia);

    if (elementos_asignados != 3) {
         printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }
    if (anio < 1900 || anio > 2100) {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    if (mes < 1 || mes > 12) {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Considera años bisiestos
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasEnMes[2] = 29; // Año bisiesto, febrero tiene 29 días
    }

    if (dia < 1 || dia > diasEnMes[mes]) {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    printf("Fecha valida: %s\n", fechaIngresada);
    return 1;
}
//FUNCION  DE MODIFICACION DE INGRESOS
// solo pueden modificarse las fechas y matricula del solicitante
nodoIngresos* modificacion_de_ingreso(nodoIngresos* lista, int nroIngreso)
{  //en el main tenemos que buscar el nodo arbol paciente con el dni de la persona
    int eleccion;
    char nuevaFecha[40];
    int nuevaMatricula;
    int volverIngresar;
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
                do
                {

                    printf("Ingresa una fecha nueva de ingreso (YYYY-MM-DD): ");
                    if (scanf("%19s", nuevaFecha) != 1)
                    {
                        printf("Entrada invalida\n.\n");
                        volverIngresar=1;
                    }
                     else if(!analizarFecha(nuevaFecha))
                    {
                        printf("La fecha ingresada es invalida\n");
                        volverIngresar=1;
                    }
                    else if(!esAnterior(nuevaFecha,existe->dato.fechaRetiro))
                    {
                        printf("La fecha de ingreso tiene que ser anterior a la de retiro\n");
                        volverIngresar=1;
                    }
                    else
                    {
                       volverIngresar=0;
                    }

                }
                while (volverIngresar==1);
                    strcpy(existe->dato.fechaIngreso,nuevaFecha);
                break;
            case 2:
                do
                {

                    printf("Ingresa una fecha nueva de retiro (YYYY-MM-DD): ");
                    if (scanf("%19s", nuevaFecha) != 1)
                    {
                        printf("Entrada invalida\n.\n");
                        volverIngresar=1;
                    }
                     else if(!analizarFecha(nuevaFecha))
                    {
                        printf("La fecha ingresada es invalida\n");
                        volverIngresar=1;
                    }
                    else if(!esAnterior(existe->dato.fechaIngreso,nuevaFecha))
                    {
                        printf("La fecha de ingreso tiene que ser posterior a la de ingreso\n");
                        volverIngresar=1;
                    }
                    else
                    {
                       volverIngresar=0;
                    }
                }
                while (volverIngresar==1);
                strcpy(existe->dato.fechaRetiro,nuevaFecha);
                break;
            case 3:
                do
                {
                    printf("Ingrese la nueva Matricula del profesional: \n");
                    if (scanf("%d", &nuevaMatricula) != 1)
                    {
                        printf("Entrada invalida. Debes ingresar un número entero.\n");

                        // Limpiar el búfer de entrada para evitar bucles infinitos
                        while (getchar() != '\n');
                    }
                    else
                    {
                        // La entrada es un entero, salir del bucle
                        break;
                    }
                }
                while (1);
                existe->dato.matriculaProfesional=nuevaMatricula;
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
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes * paciente, ingresos dato)
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
// FUNCION DE ALTA DE PRACTICAS POR INGRESO
nodoPracticasXIngreso *alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso)
{
    char eleccion;
    char  nombrePractica[40];


    do
    {
        printf("Ingrese codigo de la practica a realizar:\n");
        fflush(stdin);
        scanf("%c",nombrePractica);

        int nroPractica= BuscarPractica("lasPracticas.bin",nombrePractica);

        if(nroPractica!= -1)
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
int BuscarPractica(char archivo[], char nombrePractica[])
{
    practica aux;
    FILE* arch;
    arch = fopen(archivo, "rb");
    if (arch != NULL)
    {
        while (fread(&aux, sizeof(practica), 1, arch) == 1)
        {
            if (strcmpi(aux.nombrePractica, nombrePractica)==0)
            {
                fclose(arch);
               return aux.nroPractica;
            }
        }

        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo de practicas");
    }
    return -1 ;
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


//
//
//
///ARBOLES DE PACIENTES

    nodoArbolPacientes * iniciarArbol ()
{
    return NULL;
}
// CREAR NODO ARBOL PACIENTE
nodoArbolPacientes *crearNodoArbol (paciente datoP)
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
nodoArbolPacientes * insertarNodoArbolPaciente (nodoArbolPacientes *arbolPacientes, paciente dato)
{
    if(arbolPacientes==NULL)
    {
        arbolPacientes = crearNodoArbol (dato);
    }
    else
    {

        if(strcmp(arbolPacientes->dato.apellidoYnombre,dato.apellidoYnombre)>0)
        {   arbolPacientes->der= insertarNodoArbolPaciente(arbolPacientes->der,dato);
        }
        else
        {
            arbolPacientes->izq= insertarNodoArbolPaciente(arbolPacientes->izq,dato);
        }
    }
    return arbolPacientes;
}

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

    }while(respuesta =='s');
    return arbolPacientes;
}

//CARGAR PACIENTE
paciente cargarUnPaciente ()
{
    paciente nuevoPaciente;
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
    }else{
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
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

