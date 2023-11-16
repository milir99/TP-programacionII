#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
//FUNCIONES DE PRACTICAS
//FUNCION DE LISTA PRACTICA A ARCHIVO
//escribe los datos de una lista enlazada de prácticas de laboratorio en un archivo binario.
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
//lee datos de un archivo binario de prácticas de laboratorio y construye una lista enlazada a partir de ellos.
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
/*/ solicita el nombre de una práctica a modificar. Luego, busca la práctica en una lista enlazada.
Si encuentra la práctica, solicita el nuevo nombre y realiza la modificación.
 Retorna la lista de prácticas actualizada. La entrada se valida para asegurar un nombre válido./*/
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista)
{
    char nombrePractica[40];
    char nuevoNombre[40];

    // Solicitar el nombre de la práctica a modificar
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
// agrega una nueva práctica al principio de la lista enlazada de prácticas de laboratorio si no existe previamente, verificando por nombre

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
/*/ añade un nodo de práctica al principio de una lista enlazada de prácticas de laboratorio.
Si la lista está vacía, asigna la nueva práctica como el primer nodo; de lo contrario, enlaza la nueva práctica al principio y actualiza la cabeza de la lista.
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
//crea un archivo binario y escribe la información de los ingresos de un árbol binario de pacientes en él.
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
/*/ recorre un árbol binario de pacientes, escribiendo la información de los ingresos en un archivo mediante un recorrido in-order.
La función utiliza una estructura recursiva para acceder a la lista de ingresos de cada paciente y escribir sus datos correspondientes en el archivo./*/

void escribirIngresosEnArchivo(nodoArbolPacientes* arbol, FILE* archivo)
{
    if (arbol)
    {
        // Recorrer el subárbol izquierdo
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
/*/verifica la validez de una fecha ingresada en formato "YYYY-MM-DD". Si es válida,devuelve 1;
 de lo contrario devulve 0 pero antes imprime fecha no valida./*/
int analizarFecha(const char *fechaIngresada)
{
    int anio, mes, dia;
    int elementos_asignados = sscanf(fechaIngresada, "%d-%d-%d", &anio, &mes, &dia);

    if (elementos_asignados != 3)
    {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }
    if (anio < 1900 || anio > 2100)
    {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    if (mes < 1 || mes > 12)
    {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Considera años bisiestos
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
    {
        diasEnMes[2] = 29;
    }
    if (dia < 1 || dia > diasEnMes[mes])
    {
        printf("\nFecha no válida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    printf("Fecha valida: %s\n", fechaIngresada);
    return 1;
}
//FUNCION BAJA DE INGRESO
/*/marca como eliminado el ingreso con el número especificado y elimina en cascada la lista de prácticas asociadas.
Primero busca el ingreso en la lista y, si lo encuentra, establece el indicador "eliminado" en 1 y procede a eliminar la lista de prácticas en cascada.
 Retorna la lista de ingresos actualizada. Si el número de ingreso no coincide, muestra un mensaje de error./*/

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
/*/ elimina y libera en cascada la lista de nodos de prácticas por ingreso.
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
/*/Busca un ingreso en una lista por número de ingreso, permite al usuario modificar fecha de ingreso, fecha de retiro o matrícula profesional,
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
                        printf("Entrada invalida. Debes ingresar un número entero.\n");

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
cuyo número de ingreso coincida con el proporcionado, o devuelve NULL si no se encuentra./*/
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
/*/agrega un nuevo ingreso a un paciente existente en un árbol binario de pacientes.
Verifica la existencia del paciente, obtiene el número del último ingreso,
 crea un nuevo nodo de ingreso, y añade prácticas a dicho ingreso. Si tiene éxito,
  actualiza la lista de ingresos del paciente y retorna el árbol de pacientes.
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
/*/busca y retorna el número del último ingreso en una lista enlazada de ingresos.
 Recorre la lista hasta el final, actualizando el número de ingreso a medida que avanza.
 Retorna el número del último ingreso encontrado o 0 si la lista está vacía.
  La impresión dentro de la función no afecta el resultado y puede ser eliminada/*/
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
/*/añade un nodo al principio de una lista enlazada de ingresos. Si la lista está vacía, asigna el nuevo ingreso como el primer nodo;
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
/*/busca un paciente por su número de DNI en un árbol binario de búsqueda.
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
//crea un archivo binario y escribe la información de las prácticas por ingreso de un árbol binario de pacientes en él.
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
//recorre un árbol binario de pacientes y escribe la información de las prácticas por ingreso en un archivo mediante un recorrido in-order.
void escribirPXIEnArchivo(nodoArbolPacientes* arbol, FILE* archivo)
{
    if (arbol)
    {
        // Recorrer el subárbol izquierdo
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
/*/agrega prácticas a un ingreso, solicitando códigos de prácticas, verificando su existencia, y creando nodos en una lista enlazada. Retorna la lista actualizada/*/

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
//Añade un nodo al principio de una lista enlazada de prácticas por ingreso.
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
//Busca una práctica por nombre en una lista, retornando su número si se encuentra, y -1 si no.
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
        {
            arbolPacientes->der= insertarNodoArbolPaciente(arbolPacientes->der,dato);
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

    }
    while(respuesta =='s');
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

