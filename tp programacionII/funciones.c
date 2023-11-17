#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "switch.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
//FUNCIONES DE PRACTICAS
//FUNCION DE LISTA PRACTICA A ARCHIVO
//escribe los datos de una lista enlazada de pr�cticas de laboratorio en un archivo binario.
void listaPracticaAArchivo(char archivoPraticas[],nodoPracticasLaboratorio* lista)
{
    FILE *arch;
    arch=fopen(archivoPraticas,"wb");
    if(arch!=NULL)
    {
        while(lista!=NULL)
        {
            fwrite(&lista->datos,sizeof(practicasLaboratorio),1,arch);
            lista = lista->siguiente;
        }
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo de practicas\n");
    }
}
// FUNCION DE ARCHIVO A LISTA DE PRACTICAS
//lee datos de un archivo binario de pr�cticas de laboratorio y construye una lista enlazada a partir de ellos.
nodoPracticasLaboratorio* ArchivoAListaPracticas(char archivoPraticas[],nodoPracticasLaboratorio* lista)
{
    FILE *arch;
    practicasLaboratorio aux;
    arch=fopen(archivoPraticas,"rb");
    if(arch!=NULL)
    {
        while(fread(&aux,sizeof(practicasLaboratorio),1,arch)==1)
        {
            lista= agregarPpioPracticaLaboratorio(lista,CrearNodoPracticaLaboratorio(aux));
        }
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo de practicas");
    }
    return lista;
}
//FUNCION ALTA DE PRACTICAS
/*/ solicita el nombre de una pr�ctica a modificar. Luego, busca la pr�ctica en una lista enlazada.
Si encuentra la pr�ctica, solicita el nuevo nombre y realiza la modificaci�n.
 Retorna la lista de pr�cticas actualizada. La entrada se valida para asegurar un nombre v�lido./*/
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista)
{
    char nombrePractica[40];
    char nuevoNombre[40];

    // Solicitar el nombre de la pr�ctica a modificar
    do
    {
        printf("Ingrese el nombre de la practica que desea modificar: ");
        if (scanf("%39s", nombrePractica) == 1)
        {
            break;
        }
        else
        {
            printf("Entrada invalida. Debes ingresar un nombre valido.\n");
            while (getchar() != '\n');
        }
    }
    while (1);


    nodoPracticasLaboratorio* existe = BuscarPractica(lista, nombrePractica);

    if (existe != NULL)
    {

        do
        {
            printf("Ingrese el nuevo nombre de la Practica: ");
            if (scanf("%39s", nuevoNombre) == 1)
            {
                break;
            }
            else
            {
                printf("Entrada invalida. Debes ingresar un nombre valido.\n");
                while (getchar() != '\n');
            }
        }
        while (1);


        strcpy(existe->datos.nombreDePractica, nuevoNombre);

        printf("Practica modificada exitosamente.\n");
    }
    else
    {
        printf("La practica no existe en la lista.\n");
    }

    return lista;
}

//FUNCION DE ALTA DE PRACTICAS
// agrega una nueva pr�ctica al principio de la lista enlazada de pr�cticas de laboratorio si no existe previamente, verificando por nombre

nodoPracticasLaboratorio* alta_de_practica(practicasLaboratorio dato, nodoPracticasLaboratorio* lista)
{
    //Preguntar en main si el nro de practica no existe
    nodoPracticasLaboratorio* nodoPractica= BuscarPractica(lista,dato.nombreDePractica);
    if(nodoPractica!=NULL)
    {
        lista=agregarPpioPracticaLaboratorio(lista,CrearNodoPracticaLaboratorio(dato));

    }
    else
    {
        printf("La practica ya existe.\n");
    }
    return lista;
}

//FUNCION DE AGREGAR PRACTICA DE LABORATOTIO AL PRINCIPIO DE LA LISTA
/*/ a�ade un nodo de pr�ctica al principio de una lista enlazada de pr�cticas de laboratorio.
Si la lista est� vac�a, asigna la nueva pr�ctica como el primer nodo; de lo contrario, enlaza la nueva pr�ctica al principio y actualiza la cabeza de la lista.
 Retorna la lista actualizada/*/
nodoPracticasLaboratorio*agregarPpioPracticaLaboratorio(nodoPracticasLaboratorio*lista,nodoPracticasLaboratorio* nuevaPractica)
{
    if(lista==NULL)
    {
        lista=nuevaPractica;
    }
    else
    {
        nuevaPractica->siguiente=lista;
        lista=nuevaPractica;
    }
    return lista;

}
//FUNCION CREAR NODO PRACTICA LABORATORIO
//crea un nodo de practicas de laboratorio
nodoPracticasLaboratorio*CrearNodoPracticaLaboratorio(practicasLaboratorio dato)
{
    nodoPracticasLaboratorio*aux=(nodoPracticasLaboratorio*)malloc(sizeof(nodoPracticasLaboratorio));
    if(aux==NULL)
    {
        printf("Error al crear Nodo Practica x Ingreso");
    }
    strcpy(aux->datos.nombreDePractica,dato.nombreDePractica );
    aux->datos.nroPractica=dato.nroPractica ;
    aux->datos.eliminado=0;
    aux->siguiente=NULL;
    return aux;

}



//FUNCION PASAR DE LA LISTA DE INGRESOS A ARCHIVO DE INGRESOS
//crea un archivo binario y escribe la informaci�n de los ingresos de un �rbol binario de pacientes en �l.
void listaIngresosAArchivo(nodoArbolPacientes*arbol, char archivoIngresos[])
{
    FILE* arch;
    arch= fopen(archivoIngresos,"wb");
    if(arch!=NULL)
    {
        escribirIngresosEnArchivo(arbol,arch);
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo de practicas\n");

    }
}
//FUNCION RECURSIVA DE ESCRIBIR LOS INGRESOS EN EL ARCHIVO
/*/ recorre un �rbol binario de pacientes, escribiendo la informaci�n de los ingresos en un archivo mediante un recorrido in-order.
La funci�n utiliza una estructura recursiva para acceder a la lista de ingresos de cada paciente y escribir sus datos correspondientes en el archivo./*/

void escribirIngresosEnArchivo(nodoArbolPacientes* arbol, FILE* archivo)
{
    if (arbol)
    {
        // Recorrer el sub�rbol izquierdo
        escribirIngresosEnArchivo(arbol->izq, archivo);

        nodoIngresos* aux = arbol->listaIngresos;
        while (aux)
        {
            fwrite(&aux->dato, sizeof(ingresos), 1, archivo);
            aux = aux->siguiente;
        }

        escribirIngresosEnArchivo(arbol->der, archivo);
    }
}





//FUNCIONES DE INGRESO///
//FUNCION PARA COMPARAR FECHAS
/*/Compara dos fechas en formato "YYYY-MM-DD". Devuelve verdadero (1) si la primera fecha
 es anterior a la segunda, de lo contrario, devuelve falso (0)./*/
int esAnterior(const char *fecha1_str, const char *fecha2_str)
{
    struct tm fecha1 = {0};
    struct tm fecha2 = {0};


    if (sscanf(fecha1_str, "%d-%d-%d", &fecha1.tm_year, &fecha1.tm_mon, &fecha1.tm_mday) != 3 ||
            sscanf(fecha2_str, "%d-%d-%d", &fecha2.tm_year, &fecha2.tm_mon, &fecha2.tm_mday) != 3)
    {
        printf("Error al convertir las fechas.\n");
        return 0;
    }

    fecha1.tm_year -= 1900;
    fecha1.tm_mon -= 1;

    fecha2.tm_year -= 1900;
    fecha2.tm_mon -= 1;

    return mktime(&fecha1) < mktime(&fecha2);
}
//FUNCION VERIFICAR FECHA
/*/verifica la validez de una fecha ingresada en formato "YYYY-MM-DD". Si es v�lida,devuelve 1;
 de lo contrario devulve 0 pero antes imprime fecha no valida./*/
int analizarFecha(const char *fechaIngresada)
{
    int anio, mes, dia;
    int elementos_asignados = sscanf(fechaIngresada, "%d-%d-%d", &anio, &mes, &dia);

    if (elementos_asignados != 3)
    {
        printf("\nFecha no v�lida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }
    if (anio < 1900 || anio > 2100)
    {
        printf("\nFecha no v�lida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    if (mes < 1 || mes > 12)
    {
        printf("\nFecha no v�lida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Considera a�os bisiestos
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
    {
        diasEnMes[2] = 29;
    }
    if (dia < 1 || dia > diasEnMes[mes])
    {
        printf("\nFecha no v�lida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    printf("Fecha valida: %s\n", fechaIngresada);
    return 1;
}
//FUNCION BAJA DE INGRESO
/*/marca como eliminado el ingreso con el n�mero especificado y elimina en cascada la lista de pr�cticas asociadas.
Primero busca el ingreso en la lista y, si lo encuentra, establece el indicador "eliminado" en 1 y procede a eliminar la lista de pr�cticas en cascada.
 Retorna la lista de ingresos actualizada. Si el n�mero de ingreso no coincide, muestra un mensaje de error./*/

nodoIngresos* baja_de_ingreso(nodoIngresos* lista, int nroIngreso)
{
    //en el main tenemos que buscar el nodo arbol paciente con el dni de la persona
    nodoIngresos*existe= buscarIngreso(lista,nroIngreso);
    if(existe!=NULL)
    {
        existe->dato.eliminado=1;
        existe->listaDePracticas= baja_de_PXI_EnCascada(existe->listaDePracticas);
    }
    else
    {
        printf("EL nro de ingreso no cincide con los ingresos del paciente\n");
    }
    return lista;
}
//FUNCION BAJA DE PXI en cascada.
/*/ elimina y libera en cascada la lista de nodos de pr�cticas por ingreso.
Recorre la lista de manera recursiva, liberando cada nodo y finalmente retorna un puntero nulo./*/
nodoPracticasXIngreso* baja_de_PXI_EnCascada(nodoPracticasXIngreso* lista)
{
    // borra y libera la lista de practicas relacionadas a un ingreso
    if (lista!=NULL)
    {
        baja_de_PXI_EnCascada(lista->siguiente);
        free(lista);
    }
    return NULL;
}
//FUNCION  DE MODIFICACION DE INGRESOS
/*/Busca un ingreso en una lista por n�mero de ingreso, permite al usuario modificar fecha de ingreso, fecha de retiro o matr�cula profesional,
 validando entradas y relaciones temporales. Retorna la lista actualizada o muestra un mensaje si el ingreso no existe/*/
nodoIngresos*modificacion_de_ingreso(nodoIngresos* lista, int nroIngreso)
{
    //en el main tenemos que buscar el nodo arbol paciente con el dni de la persona
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
                        printf("Entrada invalida. Debes ingresar un n�mero entero.\n");

                        while (getchar() != '\n');
                    }
                    else
                    {
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
        printf("El numero de ingreso NO existe O fue eliminado.");
    }
    return lista;

}
//FUNCION BUSCAR INGRESO
/*/recorre una lista de ingresos para encontrar y devolver el nodo
cuyo n�mero de ingreso coincida con el proporcionado, o devuelve NULL si no se encuentra./*/
nodoIngresos* buscarIngreso(nodoIngresos* lista, int nroIngreso)
{
    if(lista!= NULL)
    {

        if (lista->dato.nroIngreso == nroIngreso)
        {
            if(lista->dato.eliminado == 0)
            {
                return lista;
            }

        }
        return buscarIngreso(lista->siguiente,nroIngreso);

    }
    return NULL;
}

//FUNCION DE ALTA DE INGRESO (A COMPLETAR)
/*/agrega un nuevo ingreso a un paciente existente en un �rbol binario de pacientes.
Verifica la existencia del paciente, obtiene el n�mero del �ltimo ingreso,
 crea un nuevo nodo de ingreso, y a�ade pr�cticas a dicho ingreso. Si tiene �xito,
  actualiza la lista de ingresos del paciente y retorna el �rbol de pacientes.
En caso de error, muestra un mensaje apropiado y retorna NULL. /*/
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
    return paciente;
}

//FUNCION QUE DEVUELVE EL ULTIMO NUMERO DE INGRESO
/*/busca y retorna el n�mero del �ltimo ingreso en una lista enlazada de ingresos.
 Recorre la lista hasta el final, actualizando el n�mero de ingreso a medida que avanza.
 Retorna el n�mero del �ltimo ingreso encontrado o 0 si la lista est� vac�a.
  La impresi�n dentro de la funci�n no afecta el resultado y puede ser eliminada/*/
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
/*/a�ade un nodo al principio de una lista enlazada de ingresos. Si la lista est� vac�a, asigna el nuevo ingreso como el primer nodo;
de lo contrario, enlaza el nuevo ingreso al principio y actualiza la cabeza de la lista. Retorna la lista actualizada/*/
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
/*/busca un paciente por su n�mero de DNI en un �rbol binario de b�squeda.
Retorna el nodo del paciente si existe, de lo contrario, devuelve NULL/*/
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
//Crea nodo de ingreso
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
// FUNCION PASAR DE LISTA DE PRACTICAS POR INGRESO A ARCHIVO DE PXI
//crea un archivo binario y escribe la informaci�n de las pr�cticas por ingreso de un �rbol binario de pacientes en �l.
void listaPXIsAArchivo(nodoArbolPacientes*arbol, char archivoIngresos[])
{
    FILE* arch;
    arch= fopen(archivoIngresos,"wb");
    if(arch!=NULL)
    {
        escribirPXIEnArchivo(arbol,arch);
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo de practicas\n");

    }
}

// FUNCION ESCRIBIR  LAS PRACTICAS POR INGRESO EN EL  ARCHIVO DE PXI
//recorre un �rbol binario de pacientes y escribe la informaci�n de las pr�cticas por ingreso en un archivo mediante un recorrido in-order.
void escribirPXIEnArchivo(nodoArbolPacientes* arbol, FILE* archivo)
{
    if (arbol)
    {
        // Recorrer el sub�rbol izquierdo
        escribirPXIEnArchivo(arbol->izq, archivo);

        nodoIngresos* aux = arbol->listaIngresos;
        while (aux)
        {
            nodoPracticasXIngreso* auxPXI= aux->listaDePracticas;
            while(auxPXI)
            {
             fwrite(&auxPXI->dato, sizeof(practicasXIngreso), 1, archivo);
             auxPXI=auxPXI->siguiente;
            }

            aux = aux->siguiente;
        }

        escribirPXIEnArchivo(arbol->der, archivo);
    }
}
// FUNCION DE ALTA DE PRACTICAS POR INGRESO
/*/agrega pr�cticas a un ingreso, solicitando c�digos de pr�cticas, verificando su existencia, y creando nodos en una lista enlazada. Retorna la lista actualizada/*/

nodoPracticasXIngreso *alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso)
{
    char eleccion;
    char  nombrePractica[40];


    do
    {
        printf("Ingrese nombre de la practica a realizar:\n");
        fflush(stdin);
        scanf("%c",nombrePractica);

        nodoPracticasLaboratorio* nodoPractica= BuscarPractica(listaPracticas,nombrePractica);
        int nroPractica= nodoPractica->datos.nroPractica;

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
        printf("No se han cargado practicas al ingreso");
        return NULL;
    }
    else
    {
        printf("Lista de practicas X ingreso cargada Exitosamente\n");

        return lista;

    }


}
//FUNCION AGREGAR AL PRINCIPIO PRACTICAXINGRESO
//A�ade un nodo al principio de una lista enlazada de pr�cticas por ingreso.
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
//Busca una pr�ctica por nombre en una lista, retornando su n�mero si se encuentra, y -1 si no.
nodoPracticasLaboratorio* BuscarPractica(nodoPracticasLaboratorio*lista, char nombrePractica[])
{
    if(lista!=NULL)
    {
        if(strcmpi(lista->datos.nombreDePractica,nombrePractica)==0)
        {
            return lista;
        }
        BuscarPractica(lista->siguiente,nombrePractica);
    }
    return NULL;
}


//FUNCION CREAR NODO PRACTICAS X INGRESO
//Crea un nodo de practicas por ingreso.
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
            arbolPacientes->der= insertarNodoArbolPaciente(arbolPacientes->der,dato);
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
            printf("La respuesta no es v�lida. Por favor, ingrese el DNI del paciente.\n");
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
                if(dniAbuscar != 0)
                {
                    do
                    {
                        printf("Ingrese el nuevo nombre y apellido:");
                        fflush(stdin);
                        if(scanf("%s",existeDNIpaciente->dato.apellidoYnombre)!=1)
                        {
                            while(getchar() != '\n');
                            printf("La respuesta no es v�lida. Por favor, ingrese el nombre y apellido del paciente.\n");
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
                        printf("La respuesta no es v�lida. Por favor, ingrese la edad del paciente.\n");
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
                        printf("La respuesta no es v�lida. Por favor, ingrese el DNI del paciente.\n");
                    }
                }
                while(getchar() != '\n');
                break;
            case 4:
                do
                {
                    printf("Ingrese la nueva direccion: ");
                    if(scanf("%s",existeDNIpaciente->dato.direccion)!=1);
                    {
                        while(getchar() != '\n');
                        printf("La respuesta no es v�lida. Por favor, ingrese la direccion del paciente.\n");
                    }
                }
                while(getchar() != '\n');
                break;
            case 5:
                do
                {
                    printf("Ingrese el nuevo telefono: ");
                    if(scanf("%s",existeDNIpaciente->dato.telefono)!=1);
                    {
                        while(getchar() != '\n');
                        printf("La respuesta no es v�lida. Por favor, ingrese el telefono del paciente.\n");
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
            printf("La respuesta no es v�lida. Por favor, ingrese el DNI del paciente.\n");
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
            printf("Entrada no v�lida. Por favor, ingrese un nombre y apellido del paciente.\n");
        }
    }
    while(getchar() != '\n');

    do
    {
        printf("Ingrese edad del paciente: ");
        if((scanf("%i",&nuevoPaciente.edad)!=1))
        {
            while(getchar() != '\n');
            printf("Entrada no v�lida. Por favor, ingrese la edad del paciente.\n");
        }
    }
    while(getchar() != '\n');

    do
    {
        printf("Ingrese el DNI del paciente: ");
        if (scanf("%i",&nuevoPaciente.dni)!=1)
        {
            while(getchar() != '\n');
            printf("Entrada no v�lida. Por favor, ingrese el DNI del paciente.\n");
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
            printf("Entrada no v�lida. Por favor, ingrese la direccion del paciente.\n");
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
            printf("Entrada no v�lida. Por favor, ingrese el telefono del paciente.\n");
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
//FUNCION PASAR DE LA LISTA DOBLE AL ARCHIVO
void pasarListaEmpleadosAarchivo(nodoEmpleados * listaEmpleados, char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo, "wb");

    if(archi != NULL)
    {
        if(lista != NULL)
        {
            fwrite(&listaEmpleados->empleado, sizeof(empleadosDeLaboratorio), 1, archi);
        }
    }
    fclose(archi);
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


