#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "switch.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

//FUNCIONES DE PRACTICAS
//FUNCION MOSTRAR PRACTICAS DE LABORATORIO ORGANIZADAS POR NOMBRE
//FUNCION mostrar las practicas que comiencen con
int mostrarPracticasQueComienzanCon(nodoPracticasLaboratorio *listaPracticas)
{
    int correcto;
    char comienzo[40];
    int existe=0;

    do
    {
        correcto = 0;

        printf("Ingrese las iniciales de la practica: \n");
        fflush(stdin);

        if (fgets(comienzo, sizeof(comienzo), stdin) == NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
        else
        {

            comienzo[strcspn(comienzo, "\n")] = '\0';
        }

    }
    while (correcto == 1);

    for (int i = 0; i < strlen(comienzo); i++)
    {
        comienzo[i] = toupper(comienzo[i]);
    }

    while (listaPracticas != NULL)
    {
        if (strstr(listaPracticas->datos.nombreDePractica, comienzo) == listaPracticas->datos.nombreDePractica)
        {
            if (listaPracticas->datos.eliminado == 0)
            {
                puts("----------------------------------------");
                printf("Numero de Practica: %d\n", listaPracticas->datos.nroPractica);
                printf("Nombre de Practica: %s\n", listaPracticas->datos.nombreDePractica);
                puts("----------------------------------------");
                existe=1;
            }
        }

        listaPracticas = listaPracticas->siguiente;
    }
    return existe;
}

// Función para ordenar la lista por nombre de práctica (usando el algoritmo de selección)
void mostrarListaPorNombre(nodoPracticasLaboratorio *listaPracticas)
{
    if (listaPracticas == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }

    nodoPracticasLaboratorio *aux;

    printf("Lista de Practicas Ordenada por Nombre:\n");
    for (aux = listaPracticas; aux != NULL; aux = aux->siguiente)
    {

        printf("Nombre de la Practica: %s\n", aux->datos.nombreDePractica);
        puts("-----------------------------------------------------------");
    }
}

// Función para mostrar la lista de prácticas
void mostrarListadoPracticas(nodoPracticasLaboratorio *listaPracticas)
{
    while (listaPracticas != NULL)
    {
        if(listaPracticas->datos.eliminado ==1)
        {
            puts("----------------------------------------");
            printf("Número de Práctica: %d\n", listaPracticas->datos.nroPractica);
            printf("Nombre de Práctica: %s\n", listaPracticas->datos.nombreDePractica);
            puts("----------------------------------------");

        }


        listaPracticas = listaPracticas->siguiente;
    }
}


///FUNCION DE LISTA PRACTICA A ARCHIVO(chequeada)
//escribe los datos de una lista enlazada de practicas de laboratorio en un archivo binario.
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
///FUNCION BAJA DE PRACTICA LABORATORIO (chequeada)
/* solicita y valida el nombre de una práctica de laboratorio. Luego, verifica si está en uso en ingresos de pacientes.
Si no está en uso, marca la práctica como eliminada; de lo contrario, emite un mensaje. Retorna la lista actualizada de prácticas*/
nodoPracticasLaboratorio* baja_de_practicasLaboratorio(nodoPracticasLaboratorio*listaPracticas,nodoArbolPacientes* arbolPacientes)
{
    int correcto;
    char practicaACambiar[30];
    do
    {
        correcto = 0;

        printf("Ingrese nombre de la practica a dar de baja:\n");
        fflush(stdin);
        if (fgets(practicaACambiar, sizeof(practicaACambiar),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }
    while(correcto==1);
    size_t longitud = strlen(practicaACambiar);
    if (practicaACambiar[longitud - 1] == '\n')
    {
        practicaACambiar[longitud - 1] = '\0';
    }

    nodoPracticasLaboratorio* nodoPractica= BuscarPractica(listaPracticas,practicaACambiar);
    if(nodoPractica!=NULL)
    {
        int usada;
        practicaEnIngreso(arbolPacientes,nodoPractica->datos.nroPractica,&usada);
        if(usada!=0)
        {
            nodoPractica->datos.eliminado =1;
            puts("----------------------------------------");

            printf("Practica dada de baja exitosamente.\n");
            puts("----------------------------------------");
        }
        else
        {
            printf("La practica se encuentra en un ingreso, no puede ser eliminada,\n");
        }
    }
    else
    {
        printf("La practica ingresada no existe.\n");
    }

    return listaPracticas;
}
//FUNCION PRACTICA EN INGRESO
void practicaEnIngreso(nodoArbolPacientes* arbolpaciente, int nroPractica,int * existencia)
{
    while(arbolpaciente!=NULL)
    {
        practicaEnIngreso(arbolpaciente->izq,nroPractica,existencia);
        *existencia= buscarPracticaEnIngreso(arbolpaciente->listaIngresos,nroPractica);
        practicaEnIngreso(arbolpaciente->der,nroPractica,existencia);
    }
}
//Busca la practica en los ingresos
/**/
int buscarPracticaEnIngreso(nodoIngresos* listaIngreso,int nroPractica)
{  int existe=0;
    while(listaIngreso!=NULL)
    {
        nodoPracticasXIngreso* seg= listaIngreso->listaDePracticas;
        while(seg!=NULL)
        {
            if(nroPractica== seg->dato.nroPractica)
            {
                existe=1;
            }

        seg=seg->siguiente;
    }
    }
return existe;
}
/// FUNCION DE ARCHIVO A LISTA DE PRACTICAS(chequeada)
//lee datos de un archivo binario de practicas de laboratorio y construye una lista enlazada a partir de ellos.
nodoPracticasLaboratorio* ArchivoAListaPracticas(char archivoPraticas[],nodoPracticasLaboratorio* lista)
{
    FILE *arch;
    practicasLaboratorio aux;
    arch=fopen(archivoPraticas,"rb");
    if(arch!=NULL)
    {
        while(fread(&aux,sizeof(practicasLaboratorio),1,arch)==1)
        {
            lista= agregarFinPracticaLaboratorio(lista,CrearNodoPracticaLaboratorio(aux));
        }
        fclose(arch);
        printf("lista practica pasada exitosamente.\n");
    }
    else
    {
         arch = fopen(archivoPraticas, "wb");
        if (arch != NULL)
        {
            printf("Se creo el archivode practicas.\n");
            fclose(arch);
        }
        else
        {
            printf("Error al abrir el archivo de practicas");
        }


    }
    return lista;
}
///FUNCION MODIFICACION DE PRACTICAS (chequeada)
/*/ solicita el nombre de una practica a modificar. Luego, busca la practica en una lista enlazada.
Si encuentra la practica, solicita el nuevo nombre y realiza la modificaci�n.
 Retorna la lista de practicas actualizada. La entrada se valida para asegurar un nombre v�lido./*/
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista)
{
    char nombrePractica[30];
    char nuevoNombre[30];

    int correcto;
    do
    {
        correcto = 0;

        printf("Ingrese el nombre de la practica que desea modificar: \n");
        fflush(stdin);
        if (fgets(nombrePractica, sizeof(nombrePractica),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }
    while(correcto==1);
    size_t longitud = strlen(nombrePractica);
    if (nombrePractica[longitud - 1] == '\n')
    {
        nombrePractica[longitud - 1] = '\0';
    }


    nodoPracticasLaboratorio* existe = BuscarPractica(lista, nombrePractica);

    if (existe != NULL)
    {

        do
        {
            correcto = 0;

            printf("Ingrese el  nuevo nombre de la practica: \n");
            fflush(stdin);
            if (fgets(nuevoNombre, sizeof(nuevoNombre),stdin)==NULL)
            {
                printf("Entrada no valida. Por favor, reintentelo.\n");
                correcto = 1;
            }
        }
        while(correcto==1);

        for (int i = 0; i < strlen(nuevoNombre); i++) {
        nuevoNombre[i] = toupper(nuevoNombre[i]);
    }
        size_t longitud = strlen(nuevoNombre);
        if (nuevoNombre[longitud - 1] == '\n')
        {
            nuevoNombre[longitud - 1] = '\0';
        }

        strcpy(existe->datos.nombreDePractica, nuevoNombre);

        printf("Practica modificada exitosamente.\n");
    }
    else
    {
        printf("La practica no existe en la lista.\n");
    }

    return lista;
}

///FUNCION DE ALTA DE PRACTICAS(chequeada)
// agrega una nueva practica al principio de la lista enlazada de practicas de laboratorio si no existe previamente, verificando por nombre

nodoPracticasLaboratorio* alta_de_practica(nodoPracticasLaboratorio* listaPracticas)
{
    int correcto;
    practicasLaboratorio nuevaPractica;
    do
    {
        correcto = 0;

        printf("Ingrese nombre de la practica a Ingresar:\n");
        fflush(stdin);
        if (fgets(nuevaPractica.nombreDePractica, sizeof(practicasLaboratorio),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }
    while(correcto==1);
    for (int i = 0; i < strlen(nuevaPractica.nombreDePractica); i++) {
       nuevaPractica.nombreDePractica[i] = toupper(nuevaPractica.nombreDePractica[i]);
    }
    size_t longitud = strlen(nuevaPractica.nombreDePractica);
    if (nuevaPractica.nombreDePractica[longitud - 1] == '\n')
    {
        nuevaPractica.nombreDePractica[longitud - 1] = '\0';
    }



    nodoPracticasLaboratorio* nodoPractica= BuscarPractica(listaPracticas,nuevaPractica.nombreDePractica);

    if(nodoPractica==NULL)
    {
        nuevaPractica.nroPractica= proximoNumeroPractica(listaPracticas);
        listaPracticas=agregarFinPracticaLaboratorio(listaPracticas,CrearNodoPracticaLaboratorio(nuevaPractica));

    }
    else if (nodoPractica->datos.eliminado==1)
    {
        char restaurar;

        printf("Esta practica habia sido eliminado del sistema anteriormente.\n Desea restaurarla? (s/n)");
        fflush(stdin);
        scanf("%c",&restaurar);
        restaurar = tolower(restaurar);
        while(restaurar!='s'&& restaurar!='n')
        {
            printf("Eleccion incorrecta, intentelo otra vez\n");
            printf("Esta practica habia sido eliminado del sistema anteriormente.\n Desea restaurarla? (s/n)");
            fflush(stdin);
            scanf("%c",&restaurar);
            restaurar = tolower(restaurar);
        }
        if (restaurar=='s')
        {
            nodoPractica->datos.eliminado=0;
        }
    }
    else
    {
        printf("La practica ya existe.\n");
    }
    return listaPracticas;
}
///FUNCION DE PROXIMO NUMERO DE PRACTICA(chequeada)
int proximoNumeroPractica (nodoPracticasLaboratorio* listaPracticas)
{
    int nroPractica=0;
    while(listaPracticas!=NULL)
    {
        nroPractica= listaPracticas->datos.nroPractica;
        listaPracticas= listaPracticas->siguiente;
    }
    return nroPractica +1;

}

///FUNCION MOSTRAR LISTA (chequeada)
void mostrarListaPracticas(nodoPracticasLaboratorio* listaPractica)
{
    while(listaPractica!=NULL)
    {
        if(listaPractica->datos.eliminado==0)
        {
            printf("Numero de Practica: %d\n", listaPractica->datos.nroPractica);
            printf("Nombre de Practica: %s\n", listaPractica->datos.nombreDePractica);
            printf("--------------------------\n");
        }

        listaPractica = listaPractica->siguiente;
    }
}
void mostrarListaPracticasadmin (nodoPracticasLaboratorio* listaPractica)
{
    while(listaPractica!=NULL)
    {

            printf("Numero de Practica: %d\n", listaPractica->datos.nroPractica);
            printf("Nombre de Practica: %s\n", listaPractica->datos.nombreDePractica);
            printf("Eliminada: %i\n", listaPractica->datos.eliminado);
            printf("--------------------------\n");


        listaPractica = listaPractica->siguiente;
    }
}

///FUNCION DE AGREGAR PRACTICA DE LABORATOTIO AL PRINCIPIO DE LA LISTA (chequeada)
/*/ Añade un nodo al final de la lista de prácticas de laboratorio.
Si la lista está vacía, establece el nuevo nodo como el primer elemento; de lo contrario, recorre la lista hasta el último nodo y lo conecta al nuevo nodo/*/
nodoPracticasLaboratorio* agregarFinPracticaLaboratorio(nodoPracticasLaboratorio* listaPractica, nodoPracticasLaboratorio* nuevaPractica)
{
    if (listaPractica == NULL)
    {
        listaPractica = nuevaPractica;
    }
    else
    {
        nodoPracticasLaboratorio* seg = listaPractica;

        while (seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }

        seg->siguiente = nuevaPractica;
    }

    return listaPractica;
}

///FUNCION CREAR NODO PRACTICA LABORATORIO (chequeada)
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



///FUNCION PASAR DE LA LISTA DE INGRESOS A ARCHIVO DE INGRESOS(chequeada)
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

//
//
//
//
//
//
//
//
//FUNCIONES DE INGRESO///
//FUNCION FILTRAR INGRESO POR FECHA
void mostrarIngresosConFiltro(nodoArbolPacientes*arbol)
{
    char desde[11];
    char hasta[11];
    int volverIngresar;

    do
    {
        volverIngresar = 0;
        printf("Ingrese fecha de inicio (AAAA-MM-DD): ");
        fflush(stdin);
        if (fgets(desde, sizeof(desde), stdin) == NULL)
        {
            printf("Entrada invalida\n.\n");
            volverIngresar = 1;
        }
        else if(!analizarFecha(desde))
        {
            printf("La fecha ingresada es invalida\n");
            volverIngresar=1;
        }

    }
    while (volverIngresar == 1);
    size_t longitud = strlen(desde);
    if (desde[longitud - 1] == '\n')
    {
        desde[longitud - 1] = '\0';
    }
    do
    {
        volverIngresar = 0;
        printf("Ingrese fecha de fin (AAAA-MM-DD): ");
        fflush(stdin);
        if (fgets(hasta, sizeof(hasta), stdin) == NULL)
        {
            printf("Entrada invalida\n.\n");
            volverIngresar = 1;
        }
        else if(!analizarFecha(hasta))
        {
            printf("La fecha ingresada es invalida\n");
            volverIngresar=1;
        }

        else if(!esAnterior(desde,hasta))
        {
            printf("La fecha fin tiene que ser posterior a la de Comienzo\n");
            volverIngresar=1;
        }
        else
        {
            volverIngresar=0;
        }


    }
    while (volverIngresar == 1);
    longitud = strlen(hasta);
    if (hasta[longitud - 1] == '\n')
    {
        hasta[longitud - 1] = '\0';
    }
    mostrarIngresosConFiltroRecursivo(arbol,desde,hasta);
}


void mostrarIngresosConFiltroRecursivo(nodoArbolPacientes* arbol, char fechaDesde[], char fechaHasta[])
{
    if (arbol != NULL)
    {
        nodoIngresos* listaIngreso= arbol->listaIngresos;
        while (listaIngreso != NULL)
        {

            if (listaIngreso->dato.eliminado == 0 &&
                    strcmp(listaIngreso->dato.fechaIngreso, fechaDesde) >= 0 &&
                    strcmp(listaIngreso->dato.fechaRetiro, fechaHasta) <= 0)
            {
                printf("\n\n------Ingresos del paciente-------\n");
                mostrarUnPaciente(arbol->dato);
                puts("-------------------------");
                mostrarUnIngreso(listaIngreso->dato);
                puts("---------fin-----------");
            }


            listaIngreso = listaIngreso->siguiente;
        }


        mostrarIngresosConFiltroRecursivo(arbol->izq, fechaDesde, fechaHasta);
        mostrarIngresosConFiltroRecursivo(arbol->der, fechaDesde, fechaHasta);
    }
}
//funcion mostrar un ingreso
void mostrarUnIngreso(ingresos dato)
{

    printf("Numero de Ingreso: %d\n", dato.nroIngreso);
    printf("Fecha de Ingreso: %s\n", dato.fechaIngreso);
    printf("Fecha de Retiro: %s\n", dato.fechaRetiro);
    printf("DNI del Paciente: %d\n", dato.dniPaciente);
    printf("Matricula Profesional: %d\n", dato.matriculaProfesional);
    printf("----------------------------------------\n");

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
// FUNCION ARCHIVO DE INGRESOS A LISTA DE INGRESOS
nodoArbolPacientes* archivoAListaIngresos(char archivo[], nodoArbolPacientes* arbol)
{
    FILE* arch;
    ingresos aux;

    arch = fopen(archivo, "rb");

    if (arch != NULL)
    {

        while (fread(&aux, sizeof(ingresos), 1, arch) == 1)
        {
            nodoArbolPacientes* existe = existePaciente(arbol, aux.dniPaciente);

            if (existe != NULL)
            {
                existe->listaIngresos = agregarPpioIngreso(existe->listaIngresos, crearNodoIngreso(aux));
            }
            else
            {
                printf("No se encontró el paciente con DNI %i en el árbol.\n", aux.dniPaciente);
            }
        }

        fclose(arch);
        printf("Datos del archivo de ingresos procesados exitosamente.\n");
    }
    else
    {

        arch = fopen(archivo, "wb");
        if (arch != NULL)
        {
            printf("Se creó el archivo: %s\n", archivo);
            fclose(arch);
        }
        else
        {
            printf("Error al abrir el archivo de ingresos.\n");
        }
    }

    return arbol;
}



///FUNCION PARA COMPARAR FECHAS (chequeada)
/*/Compara dos fechas en formato "YYYY-MM-DD". Devuelve verdadero (1) si la primera fecha
 es anterior a la segunda, de lo contrario, devuelve falso (0)./*/
int esAnterior(const char *fecha_ingreso, const char *fecha_retiro)
{
    struct tm fecha1 = {0};
    struct tm fecha2 = {0};

    if (sscanf(fecha_ingreso, "%d-%d-%d", &fecha1.tm_year, &fecha1.tm_mon, &fecha1.tm_mday) != 3 ||
            sscanf(fecha_retiro, "%d-%d-%d", &fecha2.tm_year, &fecha2.tm_mon, &fecha2.tm_mday) != 3)
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

///FUNCION VERIFICAR FECHA (chequeada)
/*/verifica la validez de una fecha ingresada en formato "YYYY-MM-DD". Si es valida,devuelve 1;
 de lo contrario devulve 0 pero antes imprime fecha no valida./*/
int analizarFecha(char *fechaIngresada)
{
    int anio, mes, dia;
    int elementos_asignados = sscanf(fechaIngresada, "%d-%d-%d", &anio, &mes, &dia);

    if (elementos_asignados != 3)
    {
        printf("\nFecha no valida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }
    if (anio < 1900 || anio > 2100)
    {
        printf("\nFecha no valida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }

    if (mes < 1 || mes > 12)
    {
        printf("\nFecha no valida. Asegurate de que los valores esten ingresados como se pide.\n");
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
        printf("\nFecha no valida. Asegurate de que los valores esten ingresados como se pide.\n");
        return 0;
    }
    return 1;
}
///FUNCION BAJA DE INGRESO (chequeada)
/*/marca como eliminado el ingreso con el numero especificado y elimina en cascada la lista de practicas asociadas.
Primero busca el ingreso en la lista y, si lo encuentra, establece el indicador "eliminado" en 1 y procede a eliminar la lista de practicas en cascada.
 Retorna la lista de ingresos actualizada. Si el numero de ingreso no coincide, muestra un mensaje de error./*/

nodoIngresos* baja_de_ingreso(nodoArbolPacientes*arbol, int nroIngreso)
{
    //en el main tenemos que buscar el nodo arbol paciente con el dni de la persona
    nodoIngresos*existe= buscarIngreso(arbol,nroIngreso);
    if(existe!=NULL)
    {
        existe->dato.eliminado=1;
        existe->listaDePracticas= baja_de_PXI_EnCascada(existe->listaDePracticas);
    }
    else
    {
        printf("EL nro de ingreso no coincide con los ingresos del paciente\n");
    }
    return arbol->listaIngresos;
}
///FUNCION BAJA DE PXI en cascada. (chequeada)
/*/ elimina y libera en cascada la lista de nodos de practicas por ingreso.
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
///FUNCION  DE MODIFICACION DE INGRESOS
/*/Busca un ingreso en una lista por numerode ingreso, permite al usuario modificar fecha de ingreso, fecha de retiro o matricula profesional,
 validando entradas y relaciones temporales. Retorna la lista actualizada o muestra un mensaje si el ingreso no existe/*/
nodoArbolPacientes*modificacion_de_ingreso(nodoArbolPacientes * arbol, int nroIngreso)
{

    int eleccion;
    char nuevaFecha[40];
    int nuevaMatricula;
    int volverIngresar;

    nodoIngresos*existe= buscarIngreso(arbol,nroIngreso);
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
                    volverIngresar = 0;
                    printf("Ingrese fecha de ingreso (AAAA-MM-DD): ");
                    fflush(stdin);
                    if (fgets(nuevaFecha, sizeof(nuevaFecha), stdin) == NULL)
                    {
                        printf("Entrada invalida\n.\n");
                        volverIngresar = 1;
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
                while (volverIngresar == 1);
                size_t longitud = strlen(nuevaFecha);
                if (nuevaFecha[longitud - 1] == '\n')
                {
                    nuevaFecha[longitud - 1] = '\0';
                }

                strcpy(existe->dato.fechaIngreso,nuevaFecha);
                break;
            case 2:
                do
                {
                    volverIngresar=0;

                    printf("Ingresa una fecha nueva de retiro (YYYY-MM-DD): ");
                    if (fgets(nuevaFecha, sizeof(nuevaFecha), stdin) == NULL)
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
                longitud = strlen(nuevaFecha);
                if (nuevaFecha[longitud - 1] == '\n')
                {
                    nuevaFecha[longitud - 1] = '\0';
                }
                strcpy(existe->dato.fechaRetiro,nuevaFecha);
                break;
            case 3:
                do
                {
                    volverIngresar=0;
                    printf("Ingrese la nueva Matricula del profesional: \n");
                    if (scanf("%d", &nuevaMatricula) != 1)
                    {
                        printf("Entrada invalida. Debes ingresar un numero entero.\n");

                        volverIngresar=1;
                    }

                }
                while (volverIngresar==1);
                existe->dato.matriculaProfesional=nuevaMatricula;
                break;
            default:
                if(eleccion!=4)
                {
                    printf("La opcion ingresada no existe.\n");
                }

            }


        }
        while(eleccion==4);
    }
    else
    {
        printf("El numero de ingreso NO existe O fue eliminado.");
    }
    return arbol;

}
///FUNCION BUSCAR INGRESO
/*/recorre una lista de ingresos para encontrar y devolver el nodo
cuyo numerode ingreso coincida con el proporcionado, o devuelve NULL si no se encuentra./*/
nodoIngresos* buscarIngreso(nodoArbolPacientes* arbol, int nroIngreso)
{
    if (arbol!=NULL)
    {
        buscarIngreso(arbol->izq, nroIngreso);
        while(arbol->listaIngresos!= NULL)
        {

            if (arbol->listaIngresos->dato.nroIngreso == nroIngreso)
            {
                if(arbol->listaIngresos->dato.eliminado == 0)
                {
                    return arbol->listaIngresos;
                }

            }

        }
        buscarIngreso(arbol->der, nroIngreso);
    }
    return NULL;
}

///FUNCION DE ALTA DE INGRESO (chequeada)
/*/agrega un nuevo ingreso a un paciente existente en un arbol binario de pacientes.(chequeada)
Verifica la existencia del paciente, obtiene el numero del ultimo ingreso,
 crea un nuevo nodo de ingreso, y añade practicas a dicho ingreso. Si tiene exito,
  actualiza la lista de ingresos del paciente y retorna el arbol de pacientes.
En caso de error, muestra un mensaje apropiado y retorna NULL. /*/
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes * paciente,nodoPracticasLaboratorio* listaPracticas)
{   ingresos dato;

    int seguir=cargarUnIngreso(paciente,&dato);

    if(seguir!=0)
    {

        nodoArbolPacientes* existencia = existePaciente(paciente,dato.dniPaciente);



        if(existencia==NULL)
        {
            printf("El Paciente NO existe.\n");
            printf("Debe darle de alta en el sistema ante de generar un ingreso.\n");
            return NULL;

        }
        else
        {

            int nroIngreso = buscarUltimoNroIngreso(existencia->listaIngresos);

            dato.nroIngreso = nroIngreso;
            nodoIngresos*nuevoIngresoNodo=crearNodoIngreso(dato);



            nuevoIngresoNodo->listaDePracticas=alta_de_pxi(nuevoIngresoNodo->listaDePracticas,nroIngreso,listaPracticas);


            if(nuevoIngresoNodo->listaDePracticas== NULL)
            {
                printf("Error al agregar las practicas.\n");

            }
            else
            {
                existencia->listaIngresos= agregarPpioIngreso(existencia->listaIngresos,nuevoIngresoNodo);
                 printf("Ingreso cargado Exitosamente\n");
            }
        }
    }

    return paciente;
}
/// FUNCION CARGAR UN INGRESO (chequeada)
/**/
int cargarUnIngreso(nodoArbolPacientes* arbol,ingresos * datosIngreso)
{
    ingresos nuevoIngreso;
    int correcto;
    char eleccion;

    do
    {
        correcto = 0;
        printf("\nIngrese el DNI del paciente: ");
        fflush(stdin);
        if (scanf("%i",&nuevoIngreso.dniPaciente) != 1)
        {
            printf("Entrada no valida. Por favor, ingrese el DNI del paciente.\n");
            correcto = 1;
        }
        else if(existePaciente(arbol,nuevoIngreso.dniPaciente)==NULL)
        {
            printf("No existe un paciente con ese DNI\n");
            printf("Si desea ingresar el DNI  nuevamente ingrese 's' de lo contrario ingrese 'n' y se volvera al menu anterior \n");
            fflush(stdin);
            scanf("%c",&eleccion);
            eleccion = tolower(eleccion);

            while(eleccion!='s'&& eleccion!='n')
            {
                printf("Eleccion incorrecta, intentelo otra vez\n");
                printf("Si desea ingresar el DNI  nuevamente ingrese 's' de lo contrario ingrese 'n' y se volvera al menu anterior.\n");
                fflush(stdin);
                scanf("%c",&eleccion);
                eleccion= tolower(eleccion);
            }
            if (eleccion=='n')
            {
                return 0;
            }
            else
            {
                correcto=1;
            }
        }
    }
    while (correcto == 1);
    clearScreen();
    puts("---------------------------");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("---------------------------\n");
    do
    {
        correcto = 0;
        printf("Ingrese fecha de ingreso (AAAA-MM-DD): ");
        fflush(stdin);
        if (fgets(nuevoIngreso.fechaIngreso, sizeof(nuevoIngreso.fechaIngreso), stdin) == NULL)
        {
            correcto = 1;
        }
        else if(analizarFecha(nuevoIngreso.fechaIngreso)!=1)
        {
            correcto = 1;
        }
    }
    while (correcto == 1);
    clearScreen();
    puts("---------------------------");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("---------------------------\n");
    printf("Fecha De Ingreso: %s\n",nuevoIngreso.fechaIngreso);
    puts("---------------------------\n");



    do
    {
        correcto=0;
        printf("Ingrese fecha de retiro (AAAA-MM-DD): ");
        fflush(stdin);
        if (fgets(nuevoIngreso.fechaRetiro, sizeof(nuevoIngreso.fechaRetiro), stdin) == NULL)
        {
            correcto = 1;
        }
        else if(analizarFecha(nuevoIngreso.fechaRetiro)!=1)
        {

            correcto = 1;
        }
        else if( esAnterior(nuevoIngreso.fechaIngreso,nuevoIngreso.fechaRetiro)!=1)
        {
            correcto = 1;
            printf("\n--La fecha de retiro debe ser posterior a la de ingreso.--\n\n");
        }

    }
    while (correcto == 1);
    clearScreen();
    puts("---------------------------");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("---------------------------\n");
    printf("Fecha De Ingreso: %s\n",nuevoIngreso.fechaIngreso);
    puts("---------------------------\n");
    printf("Fecha de Retiro: %s\n", nuevoIngreso.fechaRetiro);
    puts("---------------------------\n");



    do
    {
        correcto = 0;
        printf("\nIngrese la matricula del profesional: ");
        fflush(stdin);
        if (scanf("%i", &nuevoIngreso.matriculaProfesional) != 1)
        {
            printf("Entrada no valida. Por favor, ingrese la matricula del profesional.\n");
            correcto = 1;
        }
    }
    while (correcto == 1);
    clearScreen();
    puts("---------------------------");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("---------------------------\n");
    printf("Fecha De Ingreso: %s\n",nuevoIngreso.fechaIngreso);
    puts("---------------------------\n");
    printf("Fecha de Retiro: %s\n", nuevoIngreso.fechaRetiro);
    puts("---------------------------\n");
    printf("Matricula profesional: %i\n",nuevoIngreso.matriculaProfesional);
    puts("---------------------------\n");
    *datosIngreso= nuevoIngreso;

    return 1;
}
///FUNCION QUE DEVUELVE EL ULTIMO NUMERO DE INGRESO (chequeada)
/*/busca y retorna el numero del ultimo ingreso en una lista enlazada de ingresos.
 Recorre la lista hasta el final, actualizando el numero de ingreso a medida que avanza.
 Retorna el numero del ultimo ingreso encontrado o 0 si la lista esta vacia.
  La impresion dentro de la funcion no afecta el resultado y puede ser eliminada/*/
int buscarUltimoNroIngreso(nodoIngresos* lista)
{
    int nroIngreso = 0;

    if (lista != NULL)
    {
        ;
        nodoIngresos* seg = lista;

        while (seg != NULL)
        {
            nroIngreso = seg->dato.nroIngreso;
            seg = seg->siguiente;
        }
    }
    return nroIngreso;
}

///FUNCION DE AGREGAR  INGRESO AL PRINCIPIO DE LA LISTA(DONE)(chequeada)
/*/añade un nodo al principio de una lista enlazada de ingresos. Si la lista esta vacia, asigna el nuevo ingreso como el primer nodo;
de lo contrario, enlaza el nuevo ingreso al principio y actualiza la cabeza de la lista. Retorna la lista actualizada/*/
nodoIngresos*agregarPpioIngreso(nodoIngresos*lista,nodoIngresos* nuevoIngreso)
{
    //
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

//SWITCH DE INGRESO
/*
Esta función permite al usuario seleccionar un método para buscar y mostrar
información sobre ingresos en un árbol de pacientes. Ofrece opciones para
buscar por fecha de ingreso, número de ingreso o DNI del paciente.*/
void switchXingreso (nodoArbolPacientes * arbolPaciente)
{
    int eleccion;
    int correcto;
    char fechaIngresada[11];
    int numeroIngreso;
    int dniIngresado;
    do
    {
        printf("Como desea buscar el ingreso?  \n");
        printf("0. Para finalizar.\n ");
        printf("1. Por fecha de ingreso.\n");
        printf("2. Por Nro de ingreso.\n");
        printf("3. Por DNI del paciente.\n");

        fflush(stdin);
        scanf("%i",&eleccion);
        switch (eleccion)
        {
        case 1:
            do
            {
                correcto = 0;
                printf("Ingrese la fecha de ingreso: ");
                fflush(stdin);
                if (fgets(fechaIngresada, sizeof(fechaIngresada),stdin)==NULL)
                {
                    correcto = 1;
                    printf("La fecha no es valida. Por favor, ingrese la fecha de ingreso.\n");
                }
                else if(analizarFecha(fechaIngresada)!=1)
                {
                    printf("No hay registros de un ingreso en esa fecha.\n");
                }
            }

            while(correcto == 1);

                mostrarIngresoXfechaIngreso (arbolPaciente, fechaIngresada);


            break;
        case 2:
            do
            {
                correcto = 0;
                printf("Ingrese el nro de ingreso: ");
                if (scanf("%i",&numeroIngreso)!=1)
                {
                    correcto = 1;
                    printf("La respuesta no es valida. Por favor, ingrese el N° de ingreso.\n");
                }
            }
            while(correcto == 1);


            mostrarIngresoXnumeroIngreso (arbolPaciente, numeroIngreso);
            break;
        case 3:
            do
            {
                correcto = 0;
                printf("Ingrese el DNI: ");
                if (scanf("%i",&dniIngresado)!=1)
                {
                    correcto = 1;
                    printf("La respuesta no es valida. Por favor, ingrese el DNI.\n");
                }
            }
            while(correcto == 1);
            mostrarIngresoXdni (arbolPaciente,dniIngresado);
            break;
        default:
            if(eleccion != 0)
            {
                printf("Error, la opcion que ingreso es invalida, intentelo otra vez.\n");
            }
        }
    }while(eleccion!=0);
}

///SWITCH INGRESO POR FECHA
/*
Esta función realiza una búsqueda recursiva en un árbol binario de pacientes, mostrando todos los
ingresos y prácticas asociadas cuya fecha de ingreso coincida con la fecha proporcionada (fechaIngresada).*/
void mostrarIngresoXfechaIngreso (nodoArbolPacientes * arbolPaciente, char fechaIngresada[])
{
    while(arbolPaciente!=NULL)
    {
        mostrarIngresoXfechaIngreso (arbolPaciente->izq, fechaIngresada);
        if(strcmpi(arbolPaciente->listaIngresos->dato.fechaIngreso, fechaIngresada)==0)
        {
            mostrarUnIngreso(arbolPaciente->listaIngresos->dato); //muestra de forma inorder todos los ingresos dentro de esta fecha
            mostrarListaPXI(arbolPaciente->listaIngresos->listaDePracticas); //muestra todas las practicas
        }
        mostrarIngresoXfechaIngreso (arbolPaciente->der, fechaIngresada);
    }
}


///SWITCH INGRESO POR NUMERO DE INGRESO
/*Esta función busca un ingreso específico en un árbol binario de pacientes por su número (numeroIngreso). Si se
encuentra, muestra detalladamente la información de ese ingreso y las prácticas asociadas; de lo contrario, imprime
 un mensaje indicando la ausencia de registros.*/
void mostrarIngresoXnumeroIngreso (nodoArbolPacientes * arbolPaciente, int numeroIngreso)
{

    if (buscarIngreso(arbolPaciente, numeroIngreso) != NULL) //la funcion buscarIngreso retorna el nodo del numero ingresado o null
    {
        mostrarUnIngreso(arbolPaciente->listaIngresos->dato); //muestra solo el ingreso del numero ingresado
        mostrarListaPXI(arbolPaciente->listaIngresos->listaDePracticas); //muestra todas las practicas
    }
    else
    {
        printf("No hay registro del numero ingresado.\n");
    }
}

///SWITCH INGRESO POR DNI PACIENTE
/*
Esta función busca un paciente en un árbol binario por su DNI (dniIngresado). Si el paciente existe, muestra
detalladamente la información de su ingreso y las prácticas asociadas; de lo contrario, imprime un mensaje indicando la ausencia de registros.*/
void mostrarIngresoXdni (nodoArbolPacientes * arbolPaciente, int dniIngresado)
{
    if(existePaciente(arbolPaciente,dniIngresado)!=NULL) //busca el DNI en el arbol y retorta el nodo del paciente si existe, sino retorna NULL
    {
        mostrarUnIngreso(arbolPaciente->listaIngresos->dato); //muestra solo el ingreso de ese dni
        mostrarListaPXI(arbolPaciente->listaIngresos->listaDePracticas); //muestra todas las practicas
    }
    else
    {
        printf("No hay registros de DNI ingresado.\n");
    }
}



///FUNCION DE EXISTENCIA DE PACIENTE(DONE)/(chequeada)
/*/busca un paciente por su numero de DNI en un arbol binario de busqueda.
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

    nodoArbolPacientes* resultadoIzquierdo = existePaciente(pacientes->izq, dniPaciente);
    if (resultadoIzquierdo != NULL)
    {
        return resultadoIzquierdo;
    }

    nodoArbolPacientes* resultadoDerecho = existePaciente(pacientes->der, dniPaciente);
    if (resultadoDerecho != NULL)
    {
        return resultadoDerecho;
    }

    return NULL;


}

///FUNCION CREA NODO TIPO INGRESO(chequeada)
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
    aux->listaDePracticas=NULL;
    aux->siguiente=NULL;
    if(aux==NULL)
    {
        printf("ERROR al crear el NODO INGRESO\n");
    }
    return aux;
}
void mostrarListaIngresos(nodoIngresos* listaIngresos)
{
    while(listaIngresos!=NULL)
    {
        if(listaIngresos->dato.eliminado==0)
        {
            mostrarUnIngreso(listaIngresos->dato);
            listaIngresos=listaIngresos->siguiente;
        }

    }

}
// inicializar lista practicas
nodoPracticasLaboratorio * inicListaPracticas()
{
    return NULL;
}
//
//
//
//
//
//
//
//FUNCIONES DE PRACTICAS X INGRESO///

//FUNCION MODIFICAR PXI(corregir)
nodoArbolPacientes* modificar_PXI( nodoArbolPacientes*arbol,nodoPracticasLaboratorio*listaPracticas)
{
    nodoPracticasXIngreso* existe=BuscarPXIparaModificar(arbol,listaPracticas);
    int nuevoNro;
    int eleccion;
    int volverIngresar;
    char nuevoResultado[40];
    if(existe!= NULL)
    {


        do
        {
            printf("Elija numero de lo que desea modificar del la practica del ingreso:\n");
            printf("1.Numero de practica.\n");
            printf("2.Resultado.\n");
            printf("0.Volver al menu anterior.\n ");
            fflush(stdin);
            scanf("%i",&eleccion);
            switch(eleccion)
            {
            case 1:

                do
                {
                    volverIngresar = 0;
                    printf("Ingrese nuevo Nro de practica: ");
                    fflush(stdin);
                    if (scanf("%i",&nuevoNro)!=1)
                    {
                        printf("Entrada invalida\n.\n");
                        volverIngresar = 1;
                    }


                }
                while (volverIngresar == 1);
                existe->dato.nroPractica=nuevoNro;
                break;
            case 2:
                do
                {
                    volverIngresar=0;

                    printf("Ingrese el Resultado: ");
                    fflush(stdin);
                    if (fgets(nuevoResultado, sizeof(nuevoResultado), stdin) == NULL)
                    {
                        printf("Entrada invalida\n.Intentelo otra vez.\n");
                        volverIngresar=1;
                    }

                }
                while (volverIngresar==1);

                strcpy(existe->dato.resultado,nuevoResultado);
                break;

            default:
                if(eleccion!=0)
                {
                    printf("La opcion ingresada no existe.\n");
                }

            }


        }
        while(eleccion==0);
    }
    else
    {
        printf("El numero de ingreso NO existe O fue eliminado.");
    }
    return arbol;
}
//FUNCION buscar practica x ingreso que se desea modificar (corregir)
nodoPracticasXIngreso*BuscarPXIparaModificar( nodoArbolPacientes*arbol,nodoPracticasLaboratorio*listaPracticas)
{
    int nroIngreso;
    char nombrePractica[30];
    int  correcto ;

    do
    {
        correcto = 0;

        printf("Ingrese el nro de ingreso:\n");
        fflush(stdin);
        if (scanf("%i",&nroIngreso)!=1)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }
    while(correcto==1);

    nodoIngresos* existeIngreso= buscarIngreso(arbol,nroIngreso);

    do
    {
        correcto = 0;

        printf("Ingrese nombre de la practica:\n");
        fflush(stdin);
        if (fgets(nombrePractica, sizeof(practicasLaboratorio),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }
    while(correcto==1);
    size_t longitud = strlen(nombrePractica);
    if (nombrePractica[longitud - 1] == '\n')
    {
        nombrePractica[longitud - 1] = '\0';
    }
    nodoPracticasLaboratorio*practica= BuscarPractica(listaPracticas,nombrePractica);
    nodoPracticasXIngreso *seg=existeIngreso->listaDePracticas;
    while(seg!=NULL)
    {
        if(seg->dato.nroPractica==practica->datos.nroPractica)
        {
            break;
        }
        seg=seg->siguiente;
    }

    return seg;

}
// FUNCION PASAR DE LISTA DE PRACTICAS POR INGRESO A ARCHIVO DE PXI
//crea un archivo binario y escribe la informacion de las practicas por ingreso de un arbol binario de pacientes en el.
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
//recorre un arbol binario de pacientes y escribe la informacion de las practicas por ingreso en un archivo mediante un recorrido in-order.
void escribirPXIEnArchivo(nodoArbolPacientes* arbol, FILE* archivo)
{
    if (arbol)
    {
        // Recorrer el subarbol izquierdo
        escribirPXIEnArchivo(arbol->izq, archivo);

        nodoIngresos* aux = arbol->listaIngresos;
        while (aux!=NULL)
        {
            nodoPracticasXIngreso* auxPXI= aux->listaDePracticas;
            while(auxPXI!=NULL)
            {
                fwrite(&auxPXI->dato, sizeof(practicasXIngreso), 1, archivo);
                auxPXI=auxPXI->siguiente;
            }

            aux = aux->siguiente;
        }

        escribirPXIEnArchivo(arbol->der, archivo);
    }
}
//FUNCION ARCHIVO PXI A LISTA PXI
nodoArbolPacientes* archivoAListaPXI(char archivo[], nodoArbolPacientes* arbol)
{
    practicasXIngreso aux;
    FILE* arch;
    arch = fopen(archivo, "rb");

    if (arch != NULL)
    {
        while (fread(&aux, sizeof(practicasXIngreso), 1, arch) == 1)
        {

            nodoIngresos* ingreso = buscarIngreso(arbol, aux.nroIngreso);

            if (ingreso != NULL)
            {

                ingreso->listaDePracticas = agregarPpioPXI(ingreso->listaDePracticas, crearNodoPXI(aux.nroIngreso, aux.nroPractica));
            }
            else
            {
                printf("No se encontró el ingreso con número %i en el árbol.\n", aux.nroIngreso);
            }
        }

        fclose(arch);
        printf("Prácticas por ingreso cargadas exitosamente.\n");
    }
    else
    {
       arch = fopen(archivo, "wb");
        if (arch != NULL)
        {
            printf("Se creó el archivo: %s\n", archivo);
            fclose(arch);
        }
        else
        {
            printf("Error al abrir el archivo de ingresos.\n");
        }

    }

    return arbol;
}

/// FUNCION DE ALTA DE PRACTICAS POR INGRESO (chequeada)
/*/agrega practicas a un ingreso, solicitando codigos de practicas, verificando su existencia, y creando nodos en una lista enlazada. Retorna la lista actualizada/*/

nodoPracticasXIngreso *alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso,nodoPracticasLaboratorio* listaPracticas)
{
    char eleccion;
    char  nombrePractica[30];
    int correcto;


    do
    {
        do
        {
            correcto = 0;

            printf("Ingrese nombre de la practica a realizar:\n");
            fflush(stdin);
            if (fgets(nombrePractica, sizeof(practicasLaboratorio),stdin)==NULL)
            {
                printf("Entrada no valida. Por favor, reintentelo.\n");
                correcto = 1;
            }
        }
        while(correcto==1);
        size_t longitud = strlen(nombrePractica);
        if (nombrePractica[longitud - 1] == '\n')
        {
            nombrePractica[longitud - 1] = '\0';
        }


        nodoPracticasLaboratorio* nodoPractica= BuscarPractica(listaPracticas,nombrePractica);


        if(nodoPractica!=NULL)
        {
            int nroPractica= nodoPractica->datos.nroPractica;
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
        printf("No se han cargado practicas al ingreso\n");
        return NULL;
    }
    else
    {
        printf("Lista de practicas X ingreso cargada Exitosamente\n");

        return lista;

    }


}
///FUNCION AGREGAR AL PRINCIPIO PRACTICAXINGRESO(chequeada)
//Añade un nodo al principio de una lista enlazada de practicas por ingreso.
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
///FUNCION BUSCAR PRACTICA EN EL ARCHIVO.(chequeada)
//
nodoPracticasLaboratorio* BuscarPractica(nodoPracticasLaboratorio*lista, char nombrePractica[])
{
    while (lista!=NULL)
    {
        if(strcmpi(lista->datos.nombreDePractica,nombrePractica)==0)
        {


            return lista;


        }
        lista=lista->siguiente;
    }

    return NULL;
}


//FUNCION CREAR NODO PRACTICAS X INGRESO
///Crea un nodo de practicas por ingreso.(chequeada)
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
void mostrarListaPXI(nodoPracticasXIngreso* listaPXI)
{
    while(listaPXI!=NULL)
    {
        mostrarUnaPXI(listaPXI->dato);
        listaPXI=listaPXI->siguiente;
    }
}
void mostrarUnaPXI(practicasXIngreso dato)
{
    printf("Numero de Ingreso: %d\n", dato.nroIngreso);
    printf("Numero de practica: %d\n", dato.nroPractica);
    printf("Resultado: %s\n", dato.resultado);

    printf("----------------------------------------\n");
}
//
//
//
//
//
//
//
//
///ARBOLES DE PACIENTES(chequeada)
void mostrarPacienteEIngresos( nodoArbolPacientes*arbol)
{
    while(arbol)
    {
        mostrarPacienteEIngresos(arbol->izq);
        mostrarListaIngresos(arbol->listaIngresos);
        mostrarPacienteEIngresos(arbol->der);
    }
}
void mostrarPacienteDeDNI(nodoArbolPacientes* arbol)
{
    int dniAbuscar;
    int correcto;
    do
    {
        correcto = 0;
        printf("Ingrese el DNI del paciente que desea buscar: ");
        fflush(stdin);
        if (scanf("%d",&dniAbuscar)!=1)
        {
            correcto=1;
            printf("La respuesta no es valida. Por favor, ingrese el DNI del paciente.\n");
        }
    }
    while(correcto==1);

    nodoArbolPacientes * existeDNIpaciente = existePaciente(arbol,dniAbuscar);
    if(existeDNIpaciente!=NULL )
    {
        mostrarUnPaciente (existeDNIpaciente->dato);
        mostrarListaIngresos(existeDNIpaciente->listaIngresos);
        mostrarListaPXI(existeDNIpaciente->listaIngresos->listaDePracticas);


    }
    else
    {
        clearScreen();
        printf("El DNI ingresado no pertenece a un paciente.");
    }
}
nodoArbolPacientes * iniciarArbol ()
{
    return NULL;
}

/// CREAR NODO ARBOL PACIENTE(chequeada)
nodoArbolPacientes * crearNodoArbol (paciente datoP)
{
    nodoArbolPacientes *aux=(nodoArbolPacientes*)malloc(sizeof(nodoArbolPacientes));
    strcpy(aux->dato.apellidoYnombre,datoP.apellidoYnombre);
    aux->dato.edad = datoP.edad;
    aux->dato.dni = datoP.dni;
    strcpy(aux->dato.direccion,datoP.direccion);
    strcpy(aux->dato.telefono,datoP.telefono);
    aux->listaIngresos=NULL;
    aux->der=NULL;
    aux->izq=NULL;
    aux->dato.eliminado = 0;
    return aux;
}

///INSERTAR NODO ARBOL PACIENTE(chequeada)
nodoArbolPacientes * insertarNodoArbolPaciente (nodoArbolPacientes *arbolPacientes,nodoArbolPacientes* nuevoNodo)
{
    if(arbolPacientes == NULL)
    {
        arbolPacientes = nuevoNodo;

    }
    else
    {

        if(strcmp(arbolPacientes->dato.apellidoYnombre,nuevoNodo->dato.apellidoYnombre)<0)
        {
            arbolPacientes->der= insertarNodoArbolPaciente(arbolPacientes->der,nuevoNodo);
        }
        else
        {
            arbolPacientes->izq = insertarNodoArbolPaciente(arbolPacientes->izq,nuevoNodo);
        }
    }

    return arbolPacientes;
}

///MODIFICACION DEL PACIENTE EN EL ARBOL(chequeada)
/*Antes de usar esta funcion, se debe chequear que el arbol no este vacio, y que lo que devuelva no sea NULL*/
nodoArbolPacientes * modificacionPacientesArbol (nodoArbolPacientes * arbolPaciente)
{
    // RE INTRODUCIR EL NODO EN EL ARBOL YA QUE SI CAMBIA NOMBRE SE CAMBIA EL ORDEN

    int eleccionModificar;
    int dniAbuscar;
    int correcto;
    do
    {
        correcto = 0;
        printf("Ingrese el DNI del paciente que quiere modificar: ");
        fflush(stdin);
        if (scanf("%d",&dniAbuscar)!=1)
        {
            correcto=1;
            printf("La respuesta no es valida. Por favor, ingrese el DNI del paciente.\n");
        }
    }
    while(correcto==1);

    nodoArbolPacientes * existeDNIpaciente = existePaciente(arbolPaciente,dniAbuscar);


    if(existeDNIpaciente!=NULL)
    {
        do
        {
            printf("Ingrese el numero de la opcion que desea realizar.\n");
            printf("0. Volver al menu anterior.\n");
            printf("1. Modificar Nombre y apellido.\n");
            printf("2. Modificar Edad.\n");
            printf("3. Modificar DNI.\n");
            printf("4. Modificar Direccion.\n");
            printf("5. Modificar Telefono.\n");
            fflush(stdin);
            scanf("%i",&eleccionModificar);

            switch (eleccionModificar)
            {
            case 1:

                do
                {
                    correcto = 0;
                    printf("Ingrese nombre y apellido del paciente: ");
                    fflush(stdin);
                    if (fgets(existeDNIpaciente->dato.apellidoYnombre, sizeof(existeDNIpaciente->dato.apellidoYnombre), stdin) == NULL)
                    {
                        printf("Entrada no valida. Por favor, ingrese un nombre y apellido del paciente.\n");
                        correcto = 1;
                    }


                }
                while (correcto == 1);
                arbolPaciente= reubicarNodoEnArbol(arbolPaciente,existeDNIpaciente);
                puts("----------------------------------------\n");
                printf("Nombre y Apellido  cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 2:
                do
                {
                    correcto = 0;
                    printf("Ingrese la nueva edad: ");
                    fflush(stdin);
                    if(scanf("%i",&existeDNIpaciente->dato.edad)!=1)
                    {
                        correcto = 1;
                        printf("La respuesta no es valida. Por favor, ingrese la edad del paciente.\n");
                    }
                }
                while (correcto == 1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("Edad cambiada exitosamente.\n");
                puts("\n----------------------------------------\n");


                break;
            case 3:
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo DNI: ");
                    fflush(stdin);
                    if(scanf("%d",&existeDNIpaciente->dato.dni)!=1)
                    {
                        correcto =1;
                        printf("La respuesta no es valida. Por favor, ingrese el DNI del paciente.\n");
                    }
                }
                while (correcto == 1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("DNI cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 4:
                do
                {
                    correcto=0;
                    printf("Ingrese la nueva direccion: ");
                    fflush(stdin);
                    if (fgets(existeDNIpaciente->dato.direccion, sizeof(existeDNIpaciente->dato.direccion), stdin) == NULL)
                    {
                        correcto=1;
                        printf("La respuesta no es valida. Por favor, ingrese la direccion del paciente.\n");
                    }
                }
                while (correcto == 1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("Direccion cambiada exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 5:
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo telefono: ");
                    fflush(stdin);
                    if (fgets(existeDNIpaciente->dato.telefono, sizeof(existeDNIpaciente->dato.telefono), stdin) == NULL)
                    {
                        correcto=1;
                        printf("La respuesta no es valida. Por favor, ingrese el telefono del paciente.\n");
                    }
                }
                while (correcto == 1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("Telefono cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            default:
                if(eleccionModificar!=0)
                {
                    clearScreen();
                    puts("\n----------------------------------------\n");
                    printf("Error, la opcion que ingreso es invalida.\n");
                    puts("\n----------------------------------------\n");
                }
            }
        }
        while(eleccionModificar!=0);
    }
    else
    {
        printf("El DNI ingresado es incorrecto, no se pueden hacer modificaciones.\n");
    }
    return arbolPaciente;
}
///FUNCION PARA REUBICAR NODO QUE CAMBIA DE NOMBRE (chequeada)
//desvincula el nodo con el DNI especificado del árbol, luego lo inserta nuevamente, manteniendo la estructura del árbol binario de búsqueda.
nodoArbolPacientes *reubicarNodoEnArbol(nodoArbolPacientes *arbol,nodoArbolPacientes *nodoAReubicar)
{

    arbol = removerNodoPacienteDelArbolPorNombre(arbol, nodoAReubicar->dato.apellidoYnombre);

    arbol = insertarNodoArbolPaciente(arbol, nodoAReubicar);

    return arbol;
}

/// FUNCION REMOVER NODO DE UN ARBOL(chequeada)
/* desvincula un nodo con un DNI específico del árbol binario de pacientes, preservando la estructura del árbol sin liberar la memoria del nodo.*/
nodoArbolPacientes *removerNodoPacienteDelArbolPorNombre(nodoArbolPacientes *arbol,  char nombre[])
{
    if (arbol == NULL)
    {
        return arbol;
    }

    int comparacion = strcmp(nombre, arbol->dato.apellidoYnombre);

    if (comparacion < 0)
    {
        arbol->izq = removerNodoPacienteDelArbolPorNombre(arbol->izq, nombre);
    }
    else if (comparacion > 0)
    {
        arbol->der = removerNodoPacienteDelArbolPorNombre(arbol->der, nombre);
    }
    else
    {
        nodoArbolPacientes *nodoEliminado = arbol;

        if (arbol->izq == NULL)
        {
            arbol = arbol->der;
        }
        else if (arbol->der == NULL)
        {
            arbol = arbol->izq;
        }
        else
        {
            nodoArbolPacientes *aux = arbol->der;
            while (aux->izq != NULL)
            {
                aux = aux->izq;
            }

            arbol->dato = aux->dato;

            arbol->der = removerNodoPacienteDelArbolPorNombre(arbol->der, aux->dato.apellidoYnombre);
        }

        nodoEliminado->izq = nodoEliminado->der = NULL;



        return arbol;
    }

    return arbol;
}


///ALTA PACIENTE EN EL ARBOL(chequeada)
nodoArbolPacientes * altaArbolPacientes (nodoArbolPacientes *arbolPacientes)
{
    paciente dato;
    char restaurar;

    dato = cargarUnPaciente ();

    nodoArbolPacientes * aux = existePaciente(arbolPacientes,dato.dni);
    if(aux==NULL)
    {
        arbolPacientes = insertarNodoArbolPaciente( arbolPacientes,crearNodoArbol(dato));
        clearScreen();
        puts("----------------------------------------\n");
        printf("Paciente dado de alta exitosamente.\n");
        puts("\n----------------------------------------\n");



    }
    else if(aux->dato.eliminado==1)
    {
        printf("Este paciente habia sido eliminado del sistema anteriormente.\n Desea restauralo? (s/n)");
        fflush(stdin);
        scanf("%c",&restaurar);
        restaurar = tolower(restaurar);
        while(restaurar!='s'&& restaurar!='n')
        {
            printf("Eleccion incorrecta, intentelo otra vez\n");
            printf("Este paciente habia sido eliminado del sistema anteriormente.\n Desea restauralo? (s/n)");
            fflush(stdin);
            scanf("%c",&restaurar);
            restaurar = tolower(restaurar);
        }
        if (restaurar=='s')
        {
            aux->dato.eliminado=1;
        }
    }

    else
    {
        printf("Este paciente ya existe, intentelo otra vez!\n");
    }

    return arbolPacientes;
}

///DAR DE BAJA PACIENTEchequeada)
nodoArbolPacientes * darBajaPaciente (nodoArbolPacientes* arbolPaciente)
{
    int dniAbuscar;
    do
    {
        printf("Ingrese el DNI del paciente que quiere modificar: ");
        if (scanf("%i",&dniAbuscar)!=1)
        {
            while(getchar() != '\n');
            printf("La respuesta no es valida. Por favor, ingrese el DNI del paciente.\n");
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
///CARGAR PACIENTE(chequeada)
paciente cargarUnPaciente()
{
    paciente nuevoPaciente;
    int correcto;


    do
    {
        correcto = 0;
        printf("Ingrese nombre y apellido del paciente: ");
        fflush(stdin);
        if (fgets(nuevoPaciente.apellidoYnombre, sizeof(nuevoPaciente.apellidoYnombre), stdin) == NULL)
        {
            printf("Entrada no valida. Por favor, ingrese un nombre y apellido del paciente.\n");
            correcto = 1;
        }
    }
    while (correcto == 1);


    do
    {
        correcto = 0;
        printf("\nIngrese edad del paciente: ");
        fflush(stdin);
        if ((scanf("%i", &nuevoPaciente.edad) != 1) || (nuevoPaciente.edad < 0) || (nuevoPaciente.edad>200))
        {
            printf("Entrada no valida. Por favor, ingrese una edad valida del paciente.\n");
            correcto = 1;
        }

    }
    while (correcto == 1);

    do
    {
        correcto = 0;
        printf("\nIngrese el DNI del paciente: ");
        fflush(stdin);
        if (scanf("%i", &nuevoPaciente.dni) != 1)
        {
            printf("Entrada no valida. Por favor, ingrese el DNI del paciente.\n");
            correcto = 1;
        }
    }
    while (correcto == 1);

    // Ingreso de Dirección
    do
    {
        correcto = 0;
        printf("\nIngrese la direccion del paciente: ");
        fflush(stdin);
        if (fgets(nuevoPaciente.direccion, sizeof(nuevoPaciente.direccion), stdin) == NULL)
        {
            printf("Entrada no valida. Por favor, ingrese la direccion del paciente.\n");
            correcto = 1;
        }
    }
    while (correcto == 1);

    do
    {
        correcto = 0;
        printf("\nIngrese el telefono del paciente: ");
        fflush(stdin);
        if (scanf("%s", nuevoPaciente.telefono) != 1)
        {
            printf("Entrada no valida. Por favor, ingrese el telefono del paciente.\n");
            correcto = 1;
        }
    }
    while (correcto == 1);

    return nuevoPaciente;
}
///MOSTRAR EN ORDEN EL ARBOL(chequeada)
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes)
{
    if(arbolPacientes!= NULL)
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
}

///ARCHIVO DE PACIENTES(chequeada)
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
///FUNCION DE MOSTRAR EL ARCHIVO DE PACIENTES (chequeada)
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

///CARGAR DE ARBOL A ARCHIVO DE PACIENTES(chequeada)
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
///FUNCION ESCRIBIR EN EL ARCHIVO LO DEL ARBOL (chequeada)
void cargarArchivoPacientesDelArbol (FILE * archi,nodoArbolPacientes * arbolPacientes)
{
    if(arbolPacientes)
    {
        cargarArchivoPacientesDelArbol (archi,arbolPacientes->izq);
        fwrite(&arbolPacientes->dato,sizeof(paciente),1,archi);
        cargarArchivoPacientesDelArbol (archi, arbolPacientes->der);
    }
}
///FUNCION PARA  DATOS DE ARCHIVO AL ARBOL DE PACIENTE(chequeada)
/*   carga datos de un archivo binario de pacientes en una estructura de árbol binario de búsqueda,
 utilizando la función insertarNodoArbolPaciente para añadir cada paciente al árbol. */
nodoArbolPacientes* archivoAArbolPacientes  ( char archivo[],nodoArbolPacientes* arbol)
{
    paciente aux;
    FILE *archi=fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(paciente),1,archi)==1)
        {
            arbol = insertarNodoArbolPaciente(arbol, crearNodoArbol(aux));
        }

        fclose(archi);
        printf("Se cargaron los datos del Archivo al arbol.\n");
    }
    else
    {
        archi = fopen(archivo, "wb");
        if (archi != NULL)
        {
            printf("Se creó el archivo: %s\n", archivo);
            fclose(archi);
        }
        else
        {
            printf("Error al abrir el archivo de ingresos.\n");
        }

    }

    return arbol;
}
//
//
//
//
//FUNCION DAR DE BAJA A UN EMPLEADO
nodoEmpleados * darDeBajaEmpleado(nodoEmpleados * listaEmpleados)
{
    int dniEmpleado;
    int correcto;

    do
    {
        correcto = 0;
        printf("Ingrese el DNI del empleado que quiere eliminar: ");
        if(scanf("%i", &dniEmpleado) != 1)
        {
            printf("La respuesta es inválida. Ingrese nuevamente el DNI del empleado: ");
            correcto = 1;
            while (getchar() != '\n'); // Limpia el búfer del teclado en caso de entrada no válida
        }
    }
    while(correcto == 1);

    // Buscar el nodo a eliminar
    nodoEmpleados *actual = listaEmpleados;
    nodoEmpleados *anterior = NULL;

    while (actual != NULL && actual->empleado.dni != dniEmpleado)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != NULL)
    {
        // Ajustar los punteros del nodo anterior y siguiente
        if (anterior != NULL)
        {
            anterior->siguiente = actual->siguiente;
        }
        else
        {
            // El nodo a eliminar es el primero de la lista
            listaEmpleados = actual->siguiente;
        }

        // Liberar la memoria del nodo
        free(actual);
    }
    else
    {
        printf("No se encontró ningún empleado con el DNI proporcionado.\n");
    }
    return listaEmpleados;
}
//FUNCION MODIFICAR EMPLEADO
nodoEmpleados * modificarEmpleado(nodoEmpleados * listaEmpleados)
{
    int eleccionModificar;
    int dniAbuscar;
    int correcto;
    int perfil;
    do
    {
        correcto=0;
        printf("\nIngrese el DNI del paciente que quiere modificar: ");
        if (scanf("%i",&dniAbuscar)!=1)
        {
            correcto=1;
            printf("La respuesta no es valida. Por favor, ingrese el DNI del empleado.\n");
        }
    }
    while(correcto==1);

    nodoEmpleados* existeDNI= existeEmpleado(listaEmpleados,dniAbuscar);
    if(existeDNI!=NULL)
    {
        do
        {
            printf("Ingrese lo que desee modificar o 0 para finalzar.\n");
            printf("1. Nombre y apellido.\n");
            printf("2. Usuario.\n");
            printf("3. DNI.\n");
            printf("4. Clave.\n");
            printf("5. Telefono.\n");
            printf("6. perfil.\n");
            fflush(stdin);
            scanf("%i",&eleccionModificar);

            switch (eleccionModificar)
            {
            case 1:

            {
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo NOMBRE Y APELLIDO: ");
                    fflush(stdin);
                    if (fgets(existeDNI->empleado.apellidoYnombre, sizeof(existeDNI->empleado.apellidoYnombre), stdin) == NULL)
                    {
                        printf("Entrada no valida. Por favor, ingrese un DNI correcto.\n");
                        correcto=1;
                    }
                }
                while(correcto==1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("NOMBRE Y APELLIDO cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");

            }
            break;
            case 2:
                do
                {
                    correcto = 0;
                    printf("Ingrese el nuevo usuario: ");
                    fflush(stdin);
                    if(fgets(existeDNI->empleado.usuario, sizeof(existeDNI->empleado.usuario), stdin) == NULL)
                    {
                        correcto = 1;
                        printf("La respuesta no es valida. Por favor, ingrese el usuario del empleado.\n");
                    }
                }
                while (correcto == 1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("USUARIO cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 3:
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo DNI: ");
                    fflush(stdin);
                    if(scanf("%i",&existeDNI->empleado.dni)!=1)
                    {
                        correcto =1;
                        printf("La respuesta no es valida. Por favor, ingrese el DNI del empleado.\n");
                    }
                }
                while (correcto == 1);
                clearScreen();
                puts("----------------------------------------\n");
                printf("DNI cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 4:
                do
                {
                    correcto=0;
                    printf("Ingrese la nueva clave: ");
                    fflush(stdin);
                    if (fgets(existeDNI->empleado.clave, sizeof(existeDNI->empleado.clave), stdin) == NULL)
                    {
                        correcto=1;
                        printf("La respuesta no es valida. Por favor, ingrese la clave del empleado.\n");
                    }
                }
                while (correcto == 1);
                puts("----------------------------------------\n");
                printf("CLAVE cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 5:
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo telefono: ");
                    fflush(stdin);
                    if (fgets(existeDNI->empleado.telefono, sizeof(existeDNI->empleado.telefono), stdin) == NULL)
                    {
                        correcto=1;
                        printf("La respuesta no es valida. Por favor, ingrese el telefono del empleado.\n");
                    }
                }
                while (correcto == 1);
                puts("----------------------------------------\n");
                printf("Telefono cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
                break;
            case 6:
                 do
        {
            correcto=0;
            printf("Ingrese el perfil (1=administrador, 2=profesional, 3=administrativo): ");
            fflush(stdin);
            if (scanf("%i",&perfil)!=1)
            {
                correcto=1;
                printf("Respuesta invalida. Vuelva a intentarlo.\n");
            }
        }
        while(correcto==1);
        if (perfil==1)
        {
            strcpy(existeDNI->empleado.perfil,"administrador");
        }else if(perfil==2)
        {
           strcpy(existeDNI->empleado.perfil,"profesional");
        }
        else if(perfil==3)
        {
           strcpy(existeDNI->empleado.perfil,"administrativo");
        }


                puts("----------------------------------------\n");
                printf("perfil cambiado exitosamente.\n");
                puts("\n----------------------------------------\n");
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
    return listaEmpleados;
}

//FUNCION DE BUSCAR Y MOSTRAR UN EMPLEADO EN ESPECIFICO
void buscarUnEmpleadoXdni (nodoEmpleados * listaEmpleados, int tipoperfil)
{
    int dniAbuscar;
    int correcto;
    do
    {
        correcto=0;
        printf("Ingrese el DNI del empleado que quiera buscar: ");
        fflush(stdin);
        if (scanf("%i",&dniAbuscar)!=1)
        {
            correcto=1;
            printf("La respuesta no es valida. Por favor, ingrese el DNI del empleado.\n");
        }
    }while(correcto==1);
    nodoEmpleados * existeDni = existeEmpleado(listaEmpleados, dniAbuscar);
    if(existeDni != NULL)
    {
        mostrarUnEmpleado(existeDni->empleado,tipoperfil);
    }
    else
    {
        printf("No se encontro el empleado con el DNI solicitado.\n");
    }
}

//FUNCION MOSTRAR LISTA DOBLE EMPLEADOS
void mostrarListaEmpleados(nodoEmpleados * listaEmpleados, int tipoperfil)
{
    if(listaEmpleados != NULL)
    {
        mostrarUnEmpleado(listaEmpleados->empleado,tipoperfil);
        mostrarListaEmpleados(listaEmpleados->siguiente, tipoperfil);
    }
}

void mostrarUnEmpleado(empleadosDeLaboratorio aux, int tipoperfil)
{
    printf("\n-------------------\n");
    printf("DNI: %i\n", aux.dni);
    printf("Telefono: %s\n", aux.telefono);
    printf("Apellido y nombre: %s\n", aux.apellidoYnombre);
    printf("Usuario: %s\n", aux.usuario);
    if(tipoperfil == 1)
    {
        printf("Clave: %s\n", aux.clave);
    }
    else
    {
        printf("*****\n");
    }
    printf("perfil: %s\n", aux.perfil);
    printf("-------------------\n");
}

//FUNCION PASAR DE LA LISTA DOBLE AL ARCHIVO
void pasarListaEmpleadosAarchivo(nodoEmpleados * listaEmpleados, char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo, "wb");

    if (archi != NULL)
    {
        while (listaEmpleados != NULL)
        {
            fwrite(&listaEmpleados->empleado, sizeof(empleadosDeLaboratorio), 1, archi);
            listaEmpleados = listaEmpleados->siguiente;
        }
        fclose(archi);
        printf("Se pasaron los datos de la lista de empleados al archivo.\n");
    }
    else
    {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}


///FUNCION PASAR DE ARCHIVO A LISTA DOBLE EMPLEADOS
nodoEmpleados * pasarArchivoAlistaEmpleados(char nombreArchivo[], nodoEmpleados * listaEmpleados)
{
    FILE * archi = fopen(nombreArchivo, "rb");
    empleadosDeLaboratorio aux;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(empleadosDeLaboratorio),1, archi)==1)
        {
            nodoEmpleados * nuevoEmpleado = crearNodoEmpleados(aux);

            listaEmpleados=agregarEnOrdenEmpleados(listaEmpleados,nuevoEmpleado);

        }

        fclose(archi);
        printf("Se pasaron los datos del archivo a la lista doble.\n"); //BORRAR ANTES DE LA PRESENTACION
    }
    else
    {
        archi = fopen(nombreArchivo, "wb");
        if (archi != NULL)
        {
            printf("Se creo el archivo: %s\n", nombreArchivo);
            fclose(archi);
        }
        else
        {
            printf("Error al abrir el archivo de empleados.\n");
        }

    }

    return listaEmpleados;
}

//
//
//
///FUNCION ALTA EMPLEADOS
nodoEmpleados * alta_de_empleados (nodoEmpleados * listaEmpleados)
{
    empleadosDeLaboratorio nuevoEmpleado;
    char nombre[40];
    char clave [20];
    char usuario[20];
    int perfil;

    int correcto;
    do
    {
        correcto=0;
        printf("Ingrese el DNI: ");
        fflush(stdin);
        if(scanf("%i", &nuevoEmpleado.dni)!=1)
        {
            correcto = 1;
            printf("Respuesta invalida. Intente nuevamente: \n");
        }
    }
    while(correcto == 1);

    nodoEmpleados * existeUnEmpleado = existeEmpleado(listaEmpleados, nuevoEmpleado.dni);

    if(existeUnEmpleado==NULL)
    {
        do
        {
            correcto = 0;
            printf("Ingrese el telefono: ");
            fflush(stdin);
            if (fgets(nuevoEmpleado.telefono, sizeof(nuevoEmpleado.telefono), stdin) == NULL)
            {
                correcto = 1;
                printf("La respuesta no es valida. Por favor, ingrese el telefono del empleado.\n");
            }
            else
            {

                nuevoEmpleado.telefono[strcspn(nuevoEmpleado.telefono, "\n")] = '\0';

            }

              } while (correcto==1);


        do
        {
            correcto=0;
            printf("Ingrese el apellido y nombre: ");
            fflush(stdin);
            if (fgets(nombre, sizeof(nombre), stdin) == NULL)
            {
                printf("Respuesta invalida. Vuelva a intentarlo.\n");
                correcto=1;
            }


        }
        while(correcto==1);
             nombre[strcspn(nombre, "\n")] = '\0';
             strcpy(nuevoEmpleado.apellidoYnombre,nombre);

        do
        {
            correcto = 0;
            printf("Ingrese el nuevo usuario: ");
            fflush(stdin);
            if(fgets(usuario, sizeof(usuario), stdin) == NULL)
            {
                correcto = 1;
                printf("Respuesta invalida. Vuelva a intentarlo.\n");
            }
        }
        while(correcto==1);
        usuario[strcspn(usuario, "\n")] = '\0';
        strcpy(nuevoEmpleado.usuario,usuario);
      if(listaEmpleados==NULL)
      {
          strcpy(nuevoEmpleado.perfil,"administrador");
      }
      else
      {
        do
        {
            correcto=0;
            printf("Ingrese el perfil (1=administrador, 2=profesional, 3=administrativo): ");
            fflush(stdin);
            if (scanf("%i",&perfil)!=1)
            {
                correcto=1;
                printf("Respuesta invalida. Vuelva a intentarlo.\n");
            }
        }
        while(correcto==1);
        if (perfil==1)
        {
            strcpy(nuevoEmpleado.perfil,"administrador");
        }else if(perfil==2)
        {
           strcpy(nuevoEmpleado.perfil,"profesional");
        }
        else if(perfil==3)
        {
           strcpy(nuevoEmpleado.perfil,"administrativo");
        }
    }

            correcto=0;
            printf("Ingrese la clave: ");
             int i = 0;
        while (1) {
            char tecla = _getch();
            if (tecla == 13) {
                clave[i] = '\0';
                break;
            } else if (tecla == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                clave[i] = tecla;
                printf("*");
                i++;
            }
        }
        clave[strcspn(clave, "\n")] = '\0';
        strcpy(nuevoEmpleado.clave,clave);


        nodoEmpleados * nuevo = crearNodoEmpleados(nuevoEmpleado);

        listaEmpleados = agregarEnOrdenEmpleados(listaEmpleados, nuevo);

        printf("El empleado fue agregado.\n");

    }
    else
    {
        printf("Ya existe un empleado con ese DNI.\n");
    }
    return listaEmpleados;
}


//FUNCION AGREGAR A LA LISTA ORDENADO POS APELLIDO Y NOMBRE
nodoEmpleados * agregarEnOrdenEmpleados(nodoEmpleados * listaEmpleados, nodoEmpleados * nuevoNodo)
{
    // Caso base: lista vacía o el nuevo nodo va antes del primer nodo
    if (listaEmpleados == NULL || strcmpi(nuevoNodo->empleado.apellidoYnombre, listaEmpleados->empleado.apellidoYnombre) < 0)
    {
        nuevoNodo->siguiente = listaEmpleados;
        if (listaEmpleados != NULL)
        {
            listaEmpleados->anterior = nuevoNodo;
        }
        printf("Se ha agregado a %s a la lista.\n", nuevoNodo->empleado.apellidoYnombre);
        return nuevoNodo;
    }

    // Buscar la posición adecuada en la lista
    nodoEmpleados * actual = listaEmpleados;
    while (actual->siguiente != NULL && strcmpi(nuevoNodo->empleado.apellidoYnombre, actual->siguiente->empleado.apellidoYnombre) > 0)
    {
        actual = actual->siguiente;
    }

    // Insertar el nuevo nodo en la posición encontrada
    nuevoNodo->siguiente = actual->siguiente;
    nuevoNodo->anterior = actual;
    if (actual->siguiente != NULL)
    {
        actual->siguiente->anterior = nuevoNodo;
    }
    actual->siguiente = nuevoNodo;
    clearScreen();
    puts("---------------------------");
    printf("Se ha agregado a %s a la lista.\n", nuevoNodo->empleado.apellidoYnombre);
    puts("---------------------------\n");


    return listaEmpleados;
}


///FUNCION SI EXISTE UN EMPLEADO
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

///FUNCION DE CREAR NODO TIPO EMPLEADO
nodoEmpleados * crearNodoEmpleados(empleadosDeLaboratorio dato)
{
    nodoEmpleados * aux = (nodoEmpleados*)malloc(sizeof(nodoEmpleados));
    if (aux == NULL)
    {
        printf("ERROR: No se pudo crear el nodo para el empleado.\n");
    }
    aux->empleado.dni = dato.dni;
    strcpy(aux->empleado.telefono , dato.telefono);
    strcpy(aux->empleado.apellidoYnombre, dato.apellidoYnombre);
    strcpy(aux->empleado.clave, dato.clave);
    strcpy(aux->empleado.usuario, dato.usuario);
    strcpy(aux->empleado.perfil,dato.perfil);
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

///INICIALIZAR LA LISTA DOBLE EMPLEADOS
nodoEmpleados * iniclistaEmpleados()
{
    return NULL;
}

///INICIALIZAR LA LISTA DOBLE PRACTICA POR INGRESO
nodoPracticasXIngreso * iniclistaPracticaXingreso()
{
    return NULL;
}
///FUNCION PARA BORRAR LO QUE HAY EN PANTALLA (chequeada)
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

