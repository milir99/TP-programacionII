#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "switch.h"
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

///FUNCIONES DE PRACTICAS///

///FUNCION MOSTRAR LA PRACTICA QUE COMIENCE CON
/*Esta función solicita al usuario ingresar las iniciales de una práctica de laboratorio. Luego, busca en una lista enlazada de
prácticas aquellas cuyos nombres coincidan con las iniciales ingresadas, mostrando información detallada de las prácticas encontradas y
devolviendo un indicador de existencia.*/
int mostrarPracticasQueComienzanCon(nodoPracticasLaboratorio *listaPracticas)
{
    int correcto;
    char comienzo[40];
    int existe=0;

    do
    {
        correcto = 0;

        printf("Ingrese las iniciales de la practica: ");
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
    }while (correcto == 1);

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
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Numero de Practica: %d\n", listaPracticas->datos.nroPractica);
                printf("Nombre de Practica: %s\n", listaPracticas->datos.nombreDePractica);
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                existe=1;
            }
        }
        listaPracticas = listaPracticas->siguiente;
    }
    return existe;
}

/// FUNCION PARA ORDENAR LA LISTA POR NOMBRE DE PRACTICA (USANDO EL ALGORITMO DE SELECCION)
/*Esta función ordena una lista enlazada de prácticas de laboratorio por nombre en orden ascendente. Utiliza el algoritmo de selección
para encontrar el menor elemento en cada iteración y realiza intercambios para lograr la ordenación.*/
void mostrarListaPorNombre(nodoPracticasLaboratorio *listaPracticas,int perfil)
{
    if (listaPracticas == NULL)
    {
        printf("La lista esta vacia.\n");
        return;
    }

    nodoPracticasLaboratorio *aux;

    printf("Lista de Practicas Ordenada por Nombre: ");

    for (aux = listaPracticas; aux != NULL; aux = aux->siguiente)
    {
        if((perfil== 1||perfil==2 )&& aux->datos.eliminado==1)
        {
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
            printf("Nombre de la Practica: %s\n", aux->datos.nombreDePractica);
             printf("Numero de la Practica: %i\n", aux->datos.nroPractica);
            printf("Eliminado=%i",aux->datos.eliminado);
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
        }
        else if(aux->datos.eliminado==0)
        {
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
            printf("Nombre de la Practica: %s\n", aux->datos.nombreDePractica);
            printf("Numero de la Practica: %i\n", aux->datos.nroPractica);

            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");

        }

    }
}
void ordenarListaPorNombreAuxYMostrar(nodoPracticasLaboratorio* listaPracticas,int perfil)
{
    if (listaPracticas == NULL || listaPracticas->siguiente == NULL)
    {
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
      printf("La lista esta vacia.\n");
      puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
    }

    nodoPracticasLaboratorio *listaAux = NULL;
    nodoPracticasLaboratorio *actual = listaPracticas;

    while (actual != NULL)
    {
        nodoPracticasLaboratorio *siguiente = actual->siguiente;

        listaAux = insertarNodo(listaAux, actual);

        actual = siguiente;
    }
     mostrarListaPorNombre(listaAux,perfil);

}

// Función para insertar un nodo en una lista enlazada ordenada
nodoPracticasLaboratorio* insertarNodo(nodoPracticasLaboratorio* listaOrdenada, nodoPracticasLaboratorio* nuevoNodo)
{
    if (listaOrdenada == NULL || strcmp(nuevoNodo->datos.nombreDePractica, listaOrdenada->datos.nombreDePractica) < 0)
    {
        nuevoNodo->siguiente = listaOrdenada;
        return nuevoNodo;
    }
    nodoPracticasLaboratorio* actual = listaOrdenada;
    while (actual->siguiente != NULL &&
           strcmp(nuevoNodo->datos.nombreDePractica, actual->siguiente->datos.nombreDePractica) > 0)
    {
        actual = actual->siguiente;
    }

    nuevoNodo->siguiente = actual->siguiente;
    actual->siguiente = nuevoNodo;

    return listaOrdenada;
}

///FUNCION DE LISTA PRACTICA A ARCHIVO(chequeada)
/*escribe los datos de una lista enlazada de practicas de laboratorio en un archivo binario.*/
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

        printf("Ingrese nombre de la practica a dar de baja: ");
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
        if(usada != 0)
        {
            nodoPractica->datos.eliminado = 1;
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
            printf("Practica dada de baja exitosamente.\n");
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        }
        else
        {
            printf("La practica se encuentra en un ingreso, no puede ser eliminada.\n");
        }
    }
    else
    {
        printf("La practica ingresada no existe.\n");
    }
    return listaPracticas;
}

///FUNCION PRACTICA EN INGRESO
/*Esta función busca la existencia de una práctica (identificada por nroPractica) en los ingresos
de pacientes almacenados en un árbol binario de búsqueda (arbolpaciente), actualizando un indicador de existencia.*/
void practicaEnIngreso(nodoArbolPacientes* arbolpaciente, int nroPractica,int * existencia)
{
    while(arbolpaciente!=NULL)
    {
        practicaEnIngreso(arbolpaciente->izq,nroPractica,existencia);
        *existencia= buscarPracticaEnIngreso(arbolpaciente->listaIngresos,nroPractica);
        practicaEnIngreso(arbolpaciente->der,nroPractica,existencia);
    }
}

///BUSCAR LA PRACTICA EN LOS INGRESOS
/*La función busca un número de práctica dentro de una estructura de listas enlazadas. Itera a través
de los nodos principales y sus sublistas, estableciendo "existe" en 1 si encuentra el número de práctica. Retorna el resultado de la búsqueda.*/
int buscarPracticaEnIngreso(nodoIngresos* listaIngreso,int nroPractica)
{
    int existe=0;
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

///FUNCION DE BUSCAR UNA PRACTICA EN LOS INGRESOS
/*Esta función busca la existencia de una práctica específica (nroPractica)
en una lista de ingresos, retornando 1 si existe y 0 si no se encuentra en la lista.*/
nodoPracticasLaboratorio* ArchivoAListaPracticas(char archivoPraticas[],nodoPracticasLaboratorio* lista)
{
    FILE *arch;
    practicasLaboratorio aux;
    arch = fopen(archivoPraticas,"rb");
    if(arch != NULL)
    {
        while(fread(&aux,sizeof(practicasLaboratorio),1,arch)==1)
        {
            lista = agregarFinPracticaLaboratorio(lista,CrearNodoPracticaLaboratorio(aux));
        }
        fclose(arch);

    }
    else
    {
         arch = fopen(archivoPraticas, "wb");
        if (arch != NULL)
        {
            fclose(arch);
        }
        else
        {
            printf("Error al abrir el archivo de practicas.\n");
        }
    }
    return lista;
}

///FUNCION MODIFICACION DE PRACTICAS (chequeada)
/*/ solicita el nombre de una practica a modificar. Luego, busca la practica en una lista enlazada.
Si encuentra la practica, solicita el nuevo nombre y realiza la modificacion.
 Retorna la lista de practicas actualizada. La entrada se valida para asegurar un nombre valido./*/
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista)
{
    char nombrePractica[30];
    char nuevoNombre[30];
    int correcto;

    do
    {
        correcto = 0;

        printf("Ingrese el nombre de la practica que desea modificar: ");
        fflush(stdin);
        if (fgets(nombrePractica, sizeof(nombrePractica),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }while(correcto==1);

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
            printf("Ingrese el nuevo nombre de la practica:");
            fflush(stdin);
            if (fgets(nuevoNombre, sizeof(nuevoNombre),stdin)==NULL)
            {
                printf("Entrada no valida. Por favor, reintentelo.\n");
                correcto = 1;
            }
        }while(correcto==1);

        for (int i = 0; i < strlen(nuevoNombre); i++)
        {
        nuevoNombre[i] = toupper(nuevoNombre[i]);
        }
        size_t longitud = strlen(nuevoNombre);
        if (nuevoNombre[longitud - 1] == '\n')
        {
            nuevoNombre[longitud - 1] = '\0';
        }

        strcpy(existe->datos.nombreDePractica, nuevoNombre);
        clearScreen();
         printf("Se modifico exitosamente la practica:\n");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("Numero de Practica: %d\n", existe->datos.nroPractica);
        printf("Nombre de Practica: %s\n", existe->datos.nombreDePractica);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");

    }
    else
    {
        printf("La practica no existe en la lista.\n");
    }
    return lista;
}

///FUNCION DE ALTA DE PRACTICAS(chequeada)
/*Esta función realiza el alta de una nueva práctica de laboratorio. Solicita al usuario el nombre de la práctica, verifica su
existencia en la lista, y la agrega al final si no existe o la restaura si fue eliminada previamente.*/
nodoPracticasLaboratorio* alta_de_practica(nodoPracticasLaboratorio* listaPracticas)
{
    int correcto;
    practicasLaboratorio nuevaPractica;
    do
    {
        correcto = 0;
        printf("Ingrese nombre de la practica:");
        fflush(stdin);
        if (fgets(nuevaPractica.nombreDePractica, sizeof(practicasLaboratorio),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }while(correcto==1);

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
        clearScreen();
        printf("Se agrego exitosamente la practica:\n");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("Numero de Practica: %d\n", nuevaPractica.nroPractica);
        printf("Nombre de Practica: %s\n", nuevaPractica.nombreDePractica);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        system("pause");
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
        clearScreen();
        printf("Se restauro exitosamente la practica:\n");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("Numero de Practica: %d\n", nodoPractica->datos.nroPractica);
        printf("Nombre de Practica: %s\n", nodoPractica->datos.nombreDePractica);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        system("pause");

        }
    }
    else
    {
        printf("La practica ya existe.\n");
    }
    return listaPracticas;
}

///FUNCION DE PROXIMO NUMERO DE PRACTICA(chequeada)
/*Esta función determina el próximo número de práctica disponible al recorrer una lista de prácticas de
laboratorio y devolver el valor más alto incrementado en uno.*/
int proximoNumeroPractica (nodoPracticasLaboratorio* listaPracticas)
{
    int nroPractica = 0;
    while(listaPracticas != NULL)
    {
        nroPractica = listaPracticas->datos.nroPractica;
        listaPracticas = listaPracticas->siguiente;
    }
    return nroPractica +1;
}

///FUNCION MOSTRAR LISTA (chequeada)
/*Esta función muestra en la consola un listado detallado de prácticas de laboratorio
no eliminadas, incluyendo el número y nombre de cada práctica en un formato estructurado.*/
void mostrarListaPracticas(nodoPracticasLaboratorio* listaPracticas ,int perfil)
{
    while (listaPracticas != NULL)
    {
        if((perfil== 1||perfil==2 )&& listaPracticas->datos.eliminado==1)
        {
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
            printf("Número de Práctica: %d\n", listaPracticas->datos.nroPractica);
            printf("Nombre de Práctica: %s\n", listaPracticas->datos.nombreDePractica);
            printf("Eliminado=%i",listaPracticas->datos.eliminado);
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
        }
        else if(listaPracticas->datos.eliminado==0)
        {
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
            printf("Número de Práctica: %d\n", listaPracticas->datos.nroPractica);
            printf("Nombre de Práctica: %s\n", listaPracticas->datos.nombreDePractica);
            puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");

        }

        listaPracticas = listaPracticas->siguiente;
    }
}



///FUNCION DE AGREGAR PRACTICA DE LABORATOTIO AL PRINCIPIO DE LA LISTA (chequeada)
/*/ Añade un nodo al final de la lista de prácticas de laboratorio.
Si la lista está vacía, establece el nuevo nodo como el primer elemento; de lo
contrario, recorre la lista hasta el último nodo y lo conecta al nuevo nodo/*/
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
/*Esta función crea y devuelve un nuevo nodo para una lista de prácticas de laboratorio, inicializando
sus datos con la información proporcionada y configurando el indicador de eliminación en 0.*/
nodoPracticasLaboratorio*CrearNodoPracticaLaboratorio(practicasLaboratorio dato)
{
    nodoPracticasLaboratorio*aux=(nodoPracticasLaboratorio*)malloc(sizeof(nodoPracticasLaboratorio));
    if(aux==NULL)
    {
        printf("Error al crear Nodo Practica x Ingreso.\n");
    }
    strcpy(aux->datos.nombreDePractica,dato.nombreDePractica);
    aux->datos.nroPractica=dato.nroPractica ;
    aux->datos.eliminado=0;
    aux->siguiente=NULL;
    return aux;
}


///FUNCION PASAR DE LA LISTA DE INGRESOS A ARCHIVO DE INGRESOS(chequeada)
/*Esta función guarda la información de los ingresos de pacientes almacenados en
un árbol binario de búsqueda (arbol) en un archivo binario (archivoIngresos).*/
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
        printf("Error al abrir el archivo de practicas.\n");
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
///FUNCIONES DE INGRESO///

///FUNCION FILTRAR INGRESO POR FECHA
/*Esta función solicita al usuario ingresar un rango de fechas (desde hasta hasta). Luego, utiliza un filtro
para mostrar los ingresos de pacientes en ese intervalo de tiempo almacenados en un árbol binario de búsqueda.*/
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
            printf("Entrada invalida.\n");
            volverIngresar = 1;
        }
        else if(!analizarFecha(desde))
        {
            printf("La fecha ingresada es invalida.\n");
            volverIngresar=1;
        }

    }while (volverIngresar == 1);

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
            printf("Entrada invalida.\n");
            volverIngresar = 1;
        }
        else if(!analizarFecha(hasta))
        {
            printf("La fecha ingresada es invalida.\n");
            volverIngresar=1;
        }

        else if(!esAnterior(desde,hasta))
        {
            printf("La fecha fin tiene que ser posterior a la de Comienzo.\n");
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
    nodoIngresos *listaAux= NULL;
   listaAux = acumularIngresosConFiltroRecursivo(arbol,desde,hasta,listaAux);
   mostrarListaIngresos(listaAux);
   free(listaAux);
}

///FUNCION MOSTRAR INGRESOS DE FORMA RECURSIVA
/*Esta función realiza una búsqueda recursiva en un árbol binario de pacientes, filtrando y mostrando
los ingresos cuyas fechas de ingreso están dentro del rango especificado (fechaDesde a fechaHasta).*/
nodoIngresos* acumularIngresosConFiltroRecursivo(nodoArbolPacientes* arbol, char fechaDesde[], char fechaHasta[], nodoIngresos* listaAux)
{
    if (arbol != NULL)
    {
        nodoIngresos* listaIngresos = arbol->listaIngresos;
        while (listaIngresos != NULL)
        {
            if (listaIngresos->dato.eliminado == 0 &&
                strcmp(listaIngresos->dato.fechaIngreso, fechaDesde) >= 0 &&
                strcmp(listaIngresos->dato.fechaRetiro, fechaHasta) <= 0)
            {
                listaAux = insertarIngresoOrdenado(listaAux, listaIngresos->dato);
            }
            listaIngresos = listaIngresos->siguiente;
        }


        listaAux = acumularIngresosConFiltroRecursivo(arbol->izq, fechaDesde, fechaHasta, listaAux);
        listaAux = acumularIngresosConFiltroRecursivo(arbol->der, fechaDesde, fechaHasta, listaAux);
    }

    return listaAux; // Devolver la lista auxiliar actualizada
}
//FUNCION PARA ORDENAR FILA POR FECHA
nodoIngresos* insertarIngresoOrdenado(nodoIngresos* lista, ingresos nuevoIngreso) {
    nodoIngresos* nuevoNodo = crearNodoIngreso(nuevoIngreso);

    if (lista == NULL || strcmp(nuevoNodo->dato.fechaIngreso, lista->dato.fechaIngreso) < 0) {
        nuevoNodo->siguiente = lista;
        return nuevoNodo;
    }

    nodoIngresos* actual = lista;
    while (actual->siguiente != NULL && strcmp(nuevoNodo->dato.fechaIngreso,actual->siguiente->dato.fechaIngreso) >= 0) {
        actual = actual->siguiente;
    }

    nuevoNodo->siguiente = actual->siguiente;
    actual->siguiente = nuevoNodo;

    return lista;
}

///FUNCION MOSTRAR UN INGRESO
/*Esta función muestra en la consola la información detallada de un
ingreso, incluyendo número, fechas, DNI del paciente y matrícula profesional en un formato estructurado.*/
void mostrarUnIngreso(ingresos dato)
{
    printf("\n<<>><<>><<>><INGRESO<<>><>><<>><<>><<>>\n");
    printf("Numero de Ingreso: %d\n", dato.nroIngreso);
    printf("Fecha de Ingreso: %s\n", dato.fechaIngreso);
    printf("Fecha de Retiro: %s\n", dato.fechaRetiro);
    printf("DNI del Paciente: %d\n", dato.dniPaciente);
    printf("Matricula Profesional: %d\n", dato.matriculaProfesional);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
}
///FUNCION RECURSIVA DE ESCRIBIR LOS INGRESOS EN EL ARCHIVO
/*/ recorre un arbol binario de pacientes, escribiendo la informacion de los ingresos en un archivo mediante un recorrido in-order.
La funcion utiliza una estructura recursiva para acceder a la lista de ingresos de cada paciente y escribir sus datos correspondientes en el archivo.*/
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

/// FUNCION ARCHIVO DE INGRESOS A LISTA DE INGRESOS
/*Esta función lee un archivo binario de ingresos (archivo) y agrega la información al árbol
binario de pacientes (arbol), creando nodos de ingresos para cada registro del archivo.*/
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
        }
        fclose(arch);

    }
    else
    {
        arch = fopen(archivo, "wb");
        if (arch != NULL)
        {
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

    if (sscanf(fecha_ingreso, "%d-%d-%d", &fecha1.tm_year, &fecha1.tm_mon, &fecha1.tm_mday) != 3 || sscanf(fecha_retiro, "%d-%d-%d", &fecha2.tm_year, &fecha2.tm_mon, &fecha2.tm_mday) != 3)
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
        printf("EL nro de ingreso no coincide con los ingresos del paciente.\n");
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
        {  clearScreen();
            printf("Elija numero de lo que desea modificar del ingreso.\n");
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
                        printf("Entrada invalida.\n");
                        volverIngresar = 1;
                    }
                    else if(!analizarFecha(nuevaFecha))
                    {
                        printf("La fecha ingresada es invalida.\n");
                        volverIngresar=1;
                    }
                    else if(!esAnterior(nuevaFecha,existe->dato.fechaRetiro))
                    {
                        printf("La fecha de ingreso tiene que ser anterior a la de retiro.\n");
                        printf("Fecha de retiro: %s\n",existe->dato.fechaRetiro);
                        volverIngresar=1;
                    }
                    else
                    {
                        volverIngresar=0;
                    }
                }while (volverIngresar == 1);

                size_t longitud = strlen(nuevaFecha);
                if (nuevaFecha[longitud - 1] == '\n')
                {
                    nuevaFecha[longitud - 1] = '\0';
                }
                strcpy(existe->dato.fechaIngreso,nuevaFecha);
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Fecha modificada exitosamente.%s",existe->dato.fechaIngreso);
               puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
               system("pause");

                break;
            case 2:
                do
                {
                    volverIngresar=0;

                    printf("Ingresa una fecha nueva de retiro (YYYY-MM-DD): ");
                    if (fgets(nuevaFecha, sizeof(nuevaFecha), stdin) == NULL)
                    {
                        printf("Entrada invalida.\n");
                        volverIngresar=1;
                    }
                    else if(!analizarFecha(nuevaFecha))
                    {
                        printf("La fecha ingresada es invalida.\n");
                        volverIngresar=1;
                    }
                    else if(!esAnterior(existe->dato.fechaIngreso,nuevaFecha))
                    {
                        printf("La fecha de ingreso tiene que ser posterior a la de ingreso.\n");
                         printf("Fecha de ingreso: %s\n",existe->dato.fechaIngreso);
                        volverIngresar=1;
                    }
                    else
                    {
                        volverIngresar=0;
                    }
                }while (volverIngresar==1);

                longitud = strlen(nuevaFecha);
                if (nuevaFecha[longitud - 1] == '\n')
                {
                    nuevaFecha[longitud - 1] = '\0';
                }
                strcpy(existe->dato.fechaRetiro,nuevaFecha);
                 clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Fecha modificada exitosamente.%s",existe->dato.fechaRetiro);
               puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
               system("pause");

                break;
            case 3:
                do
                {
                    volverIngresar=0;
                    printf("Ingrese la nueva Matricula del profesional: ");
                    if (scanf("%d", &nuevaMatricula) != 1)
                    {
                        printf("Entrada invalida. Debes ingresar un numero entero.\n");

                        volverIngresar=1;
                    }

                }while (volverIngresar==1);
                existe->dato.matriculaProfesional=nuevaMatricula;
                 clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Matricula modificada exitosamente.%i",existe->dato.matriculaProfesional);
               puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
               system("pause");
                break;
            default:
                if(eleccion!=4)
                {
                    printf("La opcion ingresada no existe.\n");
                }
            }
        }while(eleccion==4);
    }
    else
    {
        printf("El numero de ingreso NO existe O fue eliminado.\n");
    }
    return arbol;
}

///FUNCION BUSCAR INGRESO
/*/recorre una lista de ingresos para encontrar y devolver el nodo
cuyo numerode ingreso coincida con el proporcionado, o devuelve NULL si no se encuentra./*/
nodoIngresos* buscarIngreso(nodoArbolPacientes* arbol, int nroIngreso)
{
    if (arbol != NULL)
    {
        nodoIngresos* ingresoEncontrado = buscarIngreso(arbol->izq, nroIngreso);

        if (ingresoEncontrado != NULL) {
            return ingresoEncontrado;
        }
        nodoIngresos* listaIngresos = arbol->listaIngresos;
        while (listaIngresos != NULL)
        {
            if (listaIngresos->dato.nroIngreso == nroIngreso && listaIngresos->dato.eliminado == 0)
            {
                return listaIngresos;
            }
            listaIngresos = listaIngresos->siguiente;
        }
        ingresoEncontrado = buscarIngreso(arbol->der, nroIngreso);

        if (ingresoEncontrado != NULL) {
            return ingresoEncontrado;
        }
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
{
    ingresos dato;
    int seguir=cargarUnIngreso(paciente,&dato);

    if(seguir!=0)
    {
        nodoArbolPacientes* existencia = existePaciente(paciente,dato.dniPaciente);

        if(existencia==NULL)
        {
            printf("El Paciente NO existe.\n");
            printf("Debe darle de alta en el sistema ante de generar un ingreso.\n");
        }
        else
        {
            int nroIngreso = buscarMaxNroIngresoEnArbol(paciente)+1;


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
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                printf("Nro Ingreso: %i\n",nuevoIngresoNodo->dato.nroIngreso);
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                printf("DNI: %i\n",nuevoIngresoNodo->dato.dniPaciente);
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                printf("Fecha De Ingreso: %s\n",nuevoIngresoNodo->dato.fechaIngreso);
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                printf("Fecha de Retiro: %s\n", nuevoIngresoNodo->dato.fechaRetiro);
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                printf("Matricula profesional: %i\n",nuevoIngresoNodo->dato.matriculaProfesional);
                puts("\n<<>><<>><<>><<>><<>><<>>\n");
                system("pause");
                clearScreen();
            }
        }
    }
    return paciente;
}

/// FUNCION CARGAR UN INGRESO (chequeada)
/*Esta función solicita al usuario ingresar información para un nuevo ingreso, como DNI del paciente, fechas de
ingreso y retiro, y matrícula del profesional. Verifica la validez de las entradas y actualiza datosIngreso. Retorna 1 si
la carga es exitosa, 0 si el usuario decide no ingresar el DNI nuevamente.*/
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
            printf("No existe un paciente con ese DNI.\n");
            printf("Si desea ingresar el DNI  nuevamente ingrese 's' de lo contrario ingrese 'n' y se volvera al menu anterior. \n");
            fflush(stdin);
            scanf("%c",&eleccion);
            eleccion = tolower(eleccion);

            while(eleccion!='s'&& eleccion!='n')
            {
                printf("Eleccion incorrecta, intentelo otra vez.\n");
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
    }while (correcto == 1);

    clearScreen();
    puts("\n<<>><<>><<>>\n");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("\n<<>><<>><<>>\n");
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
    }while (correcto == 1);

    clearScreen();
    puts("\n<<>><<>><<>><<>><<>>\n");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("\n<<>><<>><<>><<>><<>>\n");
    printf("Fecha De Ingreso: %s\n",nuevoIngreso.fechaIngreso);
    puts("\n<<>><<>><<>><<>><<>>\n");

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

    }while (correcto == 1);
    clearScreen();
    puts("\n<<>><<>><<>><<>><<>><<>>\n");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("\n<<>><<>><<>><<>><<>><<>>\n");
    printf("Fecha De Ingreso: %s\n",nuevoIngreso.fechaIngreso);
    puts("\n<<>><<>><<>><<>><<>><<>>\n");
    printf("Fecha de Retiro: %s\n", nuevoIngreso.fechaRetiro);
    puts("\n<<>><<>><<>><<>><<>><<>>\n");


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
    }while (correcto == 1);


    *datosIngreso= nuevoIngreso;
    clearScreen();
    puts("\n<<>><<>><<>><<>><<>><<>>");
    printf("DNI: %i\n",nuevoIngreso.dniPaciente);
    puts("\n<<>><<>><<>><<>><<>><<>>");
    printf("Fecha De Ingreso: %s\n",nuevoIngreso.fechaIngreso);
    puts("\n<<>><<>><<>><<>><<>><<>>");
    printf("Fecha de Retiro: %s\n", nuevoIngreso.fechaRetiro);
    puts("\n<<>><<>><<>><<>><<>><<>>");
    printf("Matricula profesional: %i\n",nuevoIngreso.matriculaProfesional);
    puts("\n<<>><<>><<>><<>><<>><<>>\n");

    return 1;
}

///FUNCION QUE DEVUELVE EL ULTIMO NUMERO DE INGRESO (chequeada)
/*/busca y retorna el numero del ultimo ingreso en una lista enlazada de ingresos.
 Recorre la lista hasta el final, actualizando el numero de ingreso a medida que avanza.
 Retorna el numero del ultimo ingreso encontrado o 0 si la lista esta vacia.
  La impresion dentro de la funcion no afecta el resultado y puede ser eliminada/*/

int buscarMaxNroIngresoEnArbol(nodoArbolPacientes* arbol) {
if (arbol == NULL) {
        return -1;
    }

    int maxNroIngreso = 0;


    if (arbol->izq != NULL) {
        maxNroIngreso = buscarMaxNroIngresoEnArbol(arbol->izq);
    }


    nodoIngresos* listaIngresos = arbol->listaIngresos;
    while (listaIngresos != NULL) {
        if (listaIngresos->dato.nroIngreso > maxNroIngreso) {
            maxNroIngreso = listaIngresos->dato.nroIngreso;
        }
        listaIngresos = listaIngresos->siguiente;
    }

    // Recorrer el árbol a la derecha
    if (arbol->der != NULL) {
        int maxNroIngresoDerecho = buscarMaxNroIngresoEnArbol(arbol->der);
        if (maxNroIngresoDerecho > maxNroIngreso) {
            maxNroIngreso = maxNroIngresoDerecho;
        }
    }

    return maxNroIngreso;
}


///FUNCION DE AGREGAR  INGRESO AL PRINCIPIO DE LA LISTA(DONE)(chequeada)
/*/añade un nodo al principio de una lista enlazada de ingresos. Si la lista esta vacia, asigna el nuevo ingreso como el primer nodo;
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

///SWITCH DE INGRESO
/*Esta función permite al usuario seleccionar un método para buscar y mostrar
información sobre ingresos en un árbol de pacientes. Ofrece opciones para
buscar por fecha de ingreso, número de ingreso o DNI del paciente.*/
void switchXingreso (nodoArbolPacientes * arbolPaciente,nodoPracticasLaboratorio* listaPracticas)
{
    int eleccion;
    int correcto;
    char fechaIngresada[11];
    int numeroIngreso;
    int dniIngresado;
    int existe;
    do
    {   clearScreen();
        printf("Como consultar el ingreso?  \n");
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
                else if(!analizarFecha(fechaIngresada))
                {
                    printf("No hay registros de un ingreso en esa fecha.\n");
                }
            }while(correcto == 1);
            clearScreen();
                mostrarIngresoXfechaIngreso (arbolPaciente, fechaIngresada,listaPracticas,&existe);
                if(existe==0)
                {
                    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                    printf("No hay registros de un ingreso en esa fecha.\n");
                     puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                }
                system("pause");

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
            }while(correcto == 1);
            clearScreen();
            mostrarIngresoXnumeroIngreso (arbolPaciente, numeroIngreso,listaPracticas,&existe);
            if(existe==0)
            {
                puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("No se encontro el Numero de ingreso");
                puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
            }
            system("pause");

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
            }while(correcto == 1);

            mostrarIngresoXdni (arbolPaciente,dniIngresado,listaPracticas,&existe);
            if(existe==0)
                {
                    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
                    printf("No hay registros de un ingreso para un paciente con ese DNI.\n");
                     puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
                }
                system("pause");

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
/*Esta función realiza una búsqueda recursiva en un árbol binario de pacientes, mostrando todos los
ingresos y prácticas asociadas cuya fecha de ingreso coincida con la fecha proporcionada (fechaIngresada).*/
void mostrarIngresoXfechaIngreso(nodoArbolPacientes* arbolPaciente, char fechaIngresada[],nodoPracticasLaboratorio*listaPracticas,int*existe)
{
    if (arbolPaciente != NULL)
    {
        mostrarIngresoXfechaIngreso(arbolPaciente->izq, fechaIngresada,listaPracticas,existe);

        nodoIngresos* listaIngresos = arbolPaciente->listaIngresos;

        while (listaIngresos != NULL)
        {
            if (listaIngresos->dato.eliminado != 1 && strcmp(listaIngresos->dato.fechaIngreso, fechaIngresada) == 0)
            {
                mostrarUnIngreso(listaIngresos->dato);
                 printf("\n<<>><<>><<>><<>>Practicas ingresadas<<>><<>><<>><<>>\n");
                mostrarListaPXIConNombre(listaIngresos->listaDePracticas,listaPracticas);
                 (*existe)++;
            }
            listaIngresos = listaIngresos->siguiente;
        }

        mostrarIngresoXfechaIngreso(arbolPaciente->der, fechaIngresada,listaPracticas,existe);
    }
}


///SWITCH INGRESO POR NUMERO DE INGRESO
/*Esta función busca un ingreso específico en un árbol binario de pacientes por su número (numeroIngreso). Si se
encuentra, muestra detalladamente la información de ese ingreso y las prácticas asociadas; de lo contrario, imprime
 un mensaje indicando la ausencia de registros.*/
void mostrarIngresoXnumeroIngreso(nodoArbolPacientes* arbolPaciente, int numeroIngreso,nodoPracticasLaboratorio*listaPracticas,int * existe)
{
    nodoIngresos* nodoIngreso = buscarIngreso(arbolPaciente, numeroIngreso);

    if (nodoIngreso != NULL && nodoIngreso->dato.eliminado ==0)
    {
        mostrarUnIngreso(nodoIngreso->dato);
        printf("\n<<>><<>><<>><<>>Practicas ingresadas<<>><<>><<>><<>>\n");
        mostrarListaPXIConNombre(nodoIngreso->listaDePracticas,listaPracticas);
         (*existe)++;
    }


}

///SWITCH INGRESO POR DNI PACIENTE
/*Esta función busca un paciente en un árbol binario por su DNI (dniIngresado). Si el paciente existe, muestra
detalladamente la información de su ingreso y las prácticas asociadas; de lo contrario, imprime un mensaje indicando la ausencia de registros.*/

  void mostrarIngresoXdni(nodoArbolPacientes* arbolPaciente, int dniIngresado,nodoPracticasLaboratorio*listaPracticas,int * existe)
{
    nodoArbolPacientes* nodoPaciente = existePaciente(arbolPaciente, dniIngresado);
    printf("paciente %i",nodoPaciente->dato.dni);

    if (nodoPaciente != NULL)
    {
        nodoIngresos* listaIngresos = nodoPaciente->listaIngresos;

        if (listaIngresos != NULL )
        {
            while (listaIngresos != NULL)
            {
                if (listaIngresos->dato.eliminado == 0)
                {
                    mostrarUnIngreso(listaIngresos->dato);
                     printf("\n<<>><<>><<>><<>>Practicas ingresadas<<>><<>><<>><<>>\n");
                    mostrarListaPXIConNombre(listaIngresos->listaDePracticas,listaPracticas);
                     (*existe)++;
                }
                listaIngresos = listaIngresos->siguiente;
            }

        }

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
        printf("ERROR al crear el NODO INGRESO.\n");
    }
    return aux;
}

///FUNCION MOSTRAR LISTA DE INGRESOS
/*Esta función muestra en la consola un listado detallado de ingresos, excluyendo aquellos
marcados como eliminados, incluyendo información como número de ingreso, fechas
y detalles asociados a cada ingreso en un formato estructurado.*/
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

/// inicializar lista practicas
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
///FUNCIONES DE PRACTICAS X INGRESO///

///FUNCION MODIFICAR PXI(corregir)
/*Esta función permite modificar información asociada a una práctica en un ingreso específico. Solicita al
usuario elegir entre modificar el número de práctica o el resultado de la misma, actualizando
los datos correspondientes si la práctica existe en la lista de ingresos.*/
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
        {   clearScreen();
            printf("Elija numero de lo que desea modificar del la practica del ingreso.\n");
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
                        printf("Entrada invalida.\n");
                        volverIngresar = 1;
                    }
                     if(BuscarPracticaXNro(listaPracticas,nuevoNro)==NULL)
                     {
                         printf("No existe una practica con ese ingreso.Por favor, intentelo otra vez.\n");
                         volverIngresar=1;
                     }
                }while (volverIngresar == 1);
                existe->dato.nroPractica=nuevoNro;
                clearScreen();
                 puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                 printf("NUMERO DE PRACTICA cambiado exitosamente.");
                  puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                  system("pause");
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

                }while (volverIngresar==1);

                strcpy(existe->dato.resultado,nuevoResultado);
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("RESULTADO cambiado exitosamente.");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                system("pause");
                break;

            default:
                if(eleccion!=0)
                {
                    printf("La opcion ingresada no existe.\n");
                }
            }
        }while(eleccion==0);
    }
    else
    {
        printf("El numero de ingreso NO existe O fue eliminado.\n");
    }
    return arbol;
}

///FUNCION buscar practica x ingreso que se desea modificar (corregir)
/*Esta función busca y devuelve el nodo de la lista de prácticas en un ingreso específico que coincide con el número de ingreso y el
nombre de la práctica proporcionados por el usuario, facilitando así la modificación de datos asociados a esa práctica.*/
nodoPracticasXIngreso*BuscarPXIparaModificar( nodoArbolPacientes*arbol,nodoPracticasLaboratorio*listaPracticas)
{
    int nroIngreso;
    char nombrePractica[30];
    int  correcto ;

    do
    {
        correcto = 0;

        printf("Ingrese el nro de ingreso: ");
        fflush(stdin);
        if (scanf("%i",&nroIngreso)!=1)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    } while(correcto==1);

    nodoIngresos* existeIngreso= buscarIngreso(arbol,nroIngreso);

    do
    {
        correcto = 0;

        printf("Ingrese nombre de la practica: ");
        fflush(stdin);
        if (fgets(nombrePractica, sizeof(practicasLaboratorio),stdin)==NULL)
        {
            printf("Entrada no valida. Por favor, reintentelo.\n");
            correcto = 1;
        }
    }while(correcto==1);
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

/// FUNCION PASAR DE LISTA DE PRACTICAS POR INGRESO A ARCHIVO DE PXI
/*Esta función guarda la información de las prácticas asociadas a los ingresos de
pacientes almacenados en un árbol binario de búsqueda (arbol) en un archivo binario (archivoIngresos).*/
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
        printf("Error al abrir el archivo de practicas.\n");
    }
}

/// FUNCION ESCRIBIR  LAS PRACTICAS POR INGRESO EN EL  ARCHIVO DE PXI
/*Esta función realiza una escritura recursiva en un archivo binario, guardando la información de las
prácticas asociadas a los ingresos de pacientes almacenados en un árbol binario de búsqueda (arbol).*/
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

///FUNCION ARCHIVO PXI A LISTA PXI
/*Esta función lee un archivo binario (archivo) que contiene información de
prácticas asociadas a ingresos y actualiza la estructura de datos de un árbol binario de pacientes (arbol) con esta información.*/
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
        }

        fclose(arch);
    }

    else
    {
       arch = fopen(archivo, "wb");
        if (arch != NULL)
        {
            fclose(arch);
        }
        else
        {
            printf("Error al abrir el archivo de ingresos.\n");
        }
    }
    return arbol;
}

// FUNCION DE ALTA DE PRACTICAS POR INGRESO (chequeada)
/*Esta función permite agregar prácticas asociadas a un ingreso en una lista (lista) de prácticas por ingreso.
Solicita el nombre de la práctica a realizar, verifica su existencia en otra lista de prácticas (listaPracticas), y en
caso de existir, crea un nodo con la información del ingreso y la práctica y lo agrega al principio de la lista.
Luego, pregunta al usuario si desea ingresar otra práctica y repite el proceso. Finalmente, muestra
un mensaje indicando si la lista se ha cargado exitosamente o está vacía.*/
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

            printf("Ingrese nombre de la practica a realizar: ");
            fflush(stdin);
            if (fgets(nombrePractica, sizeof(practicasLaboratorio),stdin)==NULL)
            {
                printf("Entrada no valida. Por favor, reintentelo.\n");
                correcto = 1;
            }
        }while(correcto==1);

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
                printf("Eleccion incorrecta, intentelo otra vez.\n");
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
    }while(eleccion=='s');
    if(lista==NULL)
    {
        printf("No se han cargado practicas al ingreso.\n");
        return NULL;
    }
    else
    {
        printf("Lista de practicas X ingreso cargada Exitosamente.\n");
        return lista;
    }
}

///FUNCION AGREGAR AL PRINCIPIO PRACTICAXINGRESO(chequeada)
/*Esta función agrega un nuevo nodo al principio de la lista de prácticas por ingreso (lista). Si la
lista está vacía, asigna el nuevo nodo como el primero. En caso contrario, enlaza el nuevo nodo con la
lista existente y actualiza la cabeza de la lista. Finalmente, devuelve la lista actualizada.*/
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
/*La función busca una práctica de laboratorio por nombre en una lista enlazada, utilizando
comparación de cadenas. Retorna el nodo correspondiente si encuentra la práctica, de lo contrario, retorna NULL.*/
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
//FUNCION BUSCAR PRACTICA POR NRO
nodoPracticasLaboratorio* BuscarPracticaXNro(nodoPracticasLaboratorio*lista, int nroPractica)
{
    while (lista!=NULL)
    {
        if(lista->datos.nroPractica==nroPractica)
        {
            return lista;
        }
        lista=lista->siguiente;
    }
    return NULL;
}


///FUNCION BUSCAR PRACTICA EN EL ARCHIVO.(chequeada)
/*Esta función busca una práctica en una lista enlazada por su nombre. Recorre la lista y devuelve
el nodo de la práctica si encuentra una coincidencia de nombre, de lo contrario, devuelve NULL.*/
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

///FUNCION CREAR NODO PRACTICAS X INGRESO
/*Crea un nodo de tipo pxi*/
void mostrarListaPXI(nodoPracticasXIngreso* listaPXI)
{
    while(listaPXI!=NULL)
    {
        mostrarUnaPXI(listaPXI->dato);
        listaPXI=listaPXI->siguiente;
    }
}

///FUNCION DE MOSTRAR UNA PRACTICA X INGRESO
/*Muestra una practica por ingreso*/
void mostrarUnaPXI(practicasXIngreso dato)
{  printf("<<>><<>><<>PRACTICA X INGRESO ><<>><<>><<>><<>>\n");
    printf("Numero de Ingreso: %d\n", dato.nroIngreso);
    printf("Numero de practica: %d\n", dato.nroPractica);
    printf("Resultado: %s\n", dato.resultado);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><>><<>><<>>");
}
void mostrarListaPXIConNombre(nodoPracticasXIngreso* listaPXI,nodoPracticasLaboratorio* listaPractica)
{
    while(listaPXI!=NULL)
    {   nodoPracticasLaboratorio* nombre= BuscarPracticaXNro(listaPractica,listaPXI->dato.nroPractica);
    if(nombre!=NULL){
    printf("<<>><<>><<>PRACTICA X INGRESO ><<>><<>><<>><<>>\n");
    printf("Numero de Ingreso: %d\n", listaPXI->dato.nroIngreso);
    printf("Numero de practica: %d\n", listaPXI->dato.nroPractica);
    printf("Nombre Practica: %s\n",nombre->datos.nombreDePractica);
    printf("Resultado: %s\n", listaPXI->dato.resultado);
    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><>><<>><<>>\n");

    }
        listaPXI=listaPXI->siguiente;
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
///FUNCIONES DE ARBOLES DE PACIENTES///
///MOSTRAR PACIENTE POR DNI
/*Esta función solicita al usuario ingresar un DNI y luego busca y
muestra información sobre el paciente correspondiente en un árbol, incluyendo
sus ingresos y las prácticas asociadas a esos ingresos.*/
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
///INICIAR ARBOL
nodoArbolPacientes * iniciarArbol ()
{
    return NULL;
}

/// CREAR NODO ARBOL PACIENTE(chequeada)
nodoArbolPacientes * crearNodoArbol (paciente datoP)
{
    nodoArbolPacientes *aux=(nodoArbolPacientes*)malloc(sizeof(nodoArbolPacientes));


    aux->dato=datoP;
    aux->listaIngresos=NULL;
    aux->der=NULL;
    aux->izq=NULL;
    aux->dato.eliminado = 0;

    return aux;
}

///INSERTAR NODO ARBOL PACIENTE(chequeada)
/*Esta función inserta un nuevo nodo en un árbol binario de búsqueda de pacientes. Compara el
apellido y nombre del nuevo nodo con el nodo actual y lo inserta en la rama izquierda o
derecha según sea necesario, manteniendo la propiedad de orden del ABB.*/
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
/*Antes de usar esta funcion, se debe chequear que el arbol no este vacio, y que lo que devuelva no sea NULL
Esta función permite modificar los datos de un paciente en el árbol. Solicita al usuario el
DNI del paciente a modificar, luego ofrece opciones para modificar nombre y apellido, edad, DNI, dirección
y teléfono. Se reintroduce el nodo en el árbol ya que cambiar el nombre podría alterar su posición en el orden del árbol.*/
nodoArbolPacientes * modificacionPacientesArbol (nodoArbolPacientes * arbolPaciente)
{
    // RE INTRODUCIR EL NODO EN EL ARBOL YA QUE SI CAMBIA NOMBRE SE CAMBIA EL ORDEN
    int eleccionModificar;
    int dniAbuscar;
    int correcto;
    int nuevoDNI;
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
        {  clearScreen();
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
                }while (correcto == 1);

                arbolPaciente= reubicarNodoEnArbol(arbolPaciente,existeDNIpaciente);

                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Nombre y Apellido  cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                system("pause");


                break;
            case 2:
                do
                {
                    correcto = 0;
                    printf("Ingrese la nueva edad: ");
                    fflush(stdin);
                    if(scanf("%i",&existeDNIpaciente->dato.edad)!=1 || (existeDNIpaciente->dato.edad< 0) || (existeDNIpaciente->dato.edad>200))
                    {
                        correcto = 1;
                        printf("La respuesta no es valida. Por favor, ingrese la edad del paciente.\n");
                    }


                }while (correcto == 1);
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Edad cambiada exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                system("pause");


                break;
            case 3:
                do
                {
                   correcto=0;
                    printf("Ingrese el nuevo DNI: ");
                    fflush(stdin);
                    if(scanf("%d",&nuevoDNI)!=1)
                    {
                        correcto =1;
                        printf("La respuesta no es valida. Por favor, ingrese el DNI del paciente.\n");
                    }else if(existePaciente(arbolPaciente,nuevoDNI)!=NULL)
                    {
                        printf("Ya existe un paciente con ese DNI. Por favor, ingrese otro DNI.");
                        correcto=1;
                    }
                    int aux=nuevoDNI;
                    int contador=0;
                    while (aux!= 0)
                    {
                        aux/= 10;
                        contador++;
                    }

                    if (contador != 8&& correcto==0)
                    {
                        correcto = 1;
                        printf("El DNI debe tener exactamente 8 digitos. Intente nuevamente.\n");
                    }


                }while (correcto == 1);
                while(existeDNIpaciente->listaIngresos!=NULL)
                {
                    existeDNIpaciente->listaIngresos->dato.dniPaciente=nuevoDNI;
                }
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("DNI cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                system("pause");

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
                    size_t len = strlen(existeDNIpaciente->dato.direccion);
                    if (len > 0 && existeDNIpaciente->dato.direccion[len - 1] == '\n')
                    {
                        existeDNIpaciente->dato.direccion[len - 1] = '\0';
                    }

                    if (strlen(existeDNIpaciente->dato.direccion) > 30)
                    {
                        printf("La direccion no puede superar los 30 caracteres. Intente nuevamente.\n");
                        correcto = 1;
            }
                }while (correcto == 1);
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Direccion cambiada exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                system("pause");

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
                    else
                    {
                        size_t longitud = strlen(existeDNIpaciente->dato.telefono);

                        if (existeDNIpaciente->dato.telefono[longitud - 1] == '\n')
                        {
                            existeDNIpaciente->dato.telefono[longitud - 1] = '\0';
                        }
                        else
                        {
                            correcto = 1;
                            printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
                            continue;
                        }

                        for (size_t i = 0; i < longitud - 1; i++)
                        {
                            if (!isdigit(existeDNIpaciente->dato.telefono[i]))
                            {
                                correcto = 1;
                                printf("El telefono solo puede contener numeros. Intente nuevamente.\n");
                                break;
                            }
                        }
                        if (longitud - 1 >= 15)
                        {
                            correcto = 1;
                            printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
                        }
                    }
                }while (correcto == 1);
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Telefono cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                system("pause");

                break;
            default:
                if(eleccionModificar!=0)
                {
                    clearScreen();
                    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                    printf("Error, la opcion que ingreso es invalida.\n");
                    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                }
            }
        }while(eleccionModificar!=0);
    }
    else
    {
        printf("El DNI ingresado es incorrecto, no se pueden hacer modificaciones.\n");
    }
    return arbolPaciente;
}

///FUNCION PARA REUBICAR NODO QUE CAMBIA DE NOMBRE (chequeada)
/*Esta función reubica un nodo en el árbol de pacientes. Primero, remueve el nodo del árbol por su nombre. Luego, inserta el
mismo nodo en la posición correcta según su nuevo nombre, manteniendo la estructura ordenada del árbol.*/
nodoArbolPacientes *reubicarNodoEnArbol(nodoArbolPacientes *arbol,nodoArbolPacientes *nodoAReubicar)
{
    arbol = removerNodoPacienteDelArbolPorNombre(arbol, nodoAReubicar->dato.apellidoYnombre);
    arbol = insertarNodoArbolPaciente(arbol, nodoAReubicar);

    return arbol;
}

/// FUNCION REMOVER NODO DE UN ARBOL(chequeada)
/*Esta función elimina un nodo del árbol de pacientes según su
nombre. Si el nombre coincide, elimina el nodo manteniendo la estructura
ordenada del árbol, considerando los casos en que el nodo a eliminar tiene 0, 1 o 2 hijos.*/
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
/*Esta función agrega un nuevo paciente al árbol de pacientes si el DNI no existe o si el paciente
 fue eliminado anteriormente. Si el paciente fue eliminado, da la opción de restaurarlo.*/
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
        puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        printf("Nombre y apellido:%s\n",dato.apellidoYnombre);
        puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        printf("Edad:%i\n",dato.edad);
        puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        printf("DNI:%i\n",dato.dni);
        puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        printf("Direccion:%s\n",dato.direccion);
        puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        printf("Telefono:%s\n",dato.telefono);
        puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("Paciente dado de alta exitosamente.\n");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");

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

///DAR DE BAJA PACIENTE (chequeada)
/*Esta función marca a un paciente con el DNI proporcionado como
eliminado en el árbol de pacientes, estableciendo el estado "eliminado" en 1.*/
nodoArbolPacientes * darBajaPaciente (nodoArbolPacientes* arbolPaciente)
{
    int dniAbuscar;
    do
    {
        printf("Ingrese el DNI del paciente que quiere eliminar: ");
        if (scanf("%i",&dniAbuscar)!=1)
        {
            while(getchar() != '\n');
            printf("La respuesta no es valida. Por favor, ingrese el DNI del paciente.\n");
        }
    }while(getchar() != '\n');

    nodoArbolPacientes * existeDNIpaciente = existePaciente(arbolPaciente,dniAbuscar);

    if (existeDNIpaciente!=NULL)
    {
        existeDNIpaciente->dato.eliminado=1;
    clearScreen();
    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
    printf("Paciente dado de baja exitosamente.\n");
    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
    }

    return arbolPaciente;
}

///CARGAR PACIENTE(chequeada)
/*Esta función solicita al usuario ingresar información sobre un
paciente, incluyendo nombre, edad, DNI, dirección y teléfono. Realiza
validaciones para asegurar la entrada correcta de datos y devuelve la estructura de paciente con la información ingresada.*/
paciente cargarUnPaciente(nodoArbolPacientes* arbol)
{
    paciente nuevoPaciente;
    int correcto;
    char telefono[15];
    clearScreen();
    do
    {

    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Cargando un Paciente");
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
        correcto = 0;
        printf("Ingrese nombre y apellido del paciente: ");
        fflush(stdin);
        if (fgets(nuevoPaciente.apellidoYnombre, sizeof(nuevoPaciente.apellidoYnombre), stdin) == NULL)
        {
            printf("Entrada no valida. Por favor, ingrese un nombre y apellido del paciente.\n");
            correcto = 1;
        }
    }while (correcto == 1);
    clearScreen();
     puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Nombre y apellido:%s",nuevoPaciente.apellidoYnombre);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
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
    }while (correcto == 1);
    clearScreen();
     puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Nombre y apellido:%s",nuevoPaciente.apellidoYnombre);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Edad:%i\n",nuevoPaciente.edad);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");

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
        else if(existePaciente(arbol,nuevoPaciente.dni)!=NULL)
        {
            printf("Ya existe un paciente con ese DNI.\n");
        }
        int contador=0;
        int nuevoDNI = nuevoPaciente.dni;
        while (nuevoDNI != 0) {

                nuevoDNI /= 10;
                contador++;
            }

            if (contador != 8&& correcto==0) {
                correcto = 1;
                printf("El DNI debe tener exactamente 8 digitos. Intente nuevamente.\n");
            }

    }while (correcto == 1);
    clearScreen();
 puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Nombre y apellido:%s",nuevoPaciente.apellidoYnombre);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Edad:%i\n",nuevoPaciente.edad);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("DNI:%i\n",nuevoPaciente.dni);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");

    do
    {
        correcto = 0;
        printf("\nIngrese la direccion del paciente: ");
        fflush(stdin);
        if (fgets(nuevoPaciente.direccion, sizeof(nuevoPaciente.direccion), stdin) == NULL)
        {

            printf("Entrada no valida. Por favor, ingrese la direccion del paciente.\n");
            correcto = 1;
        }else {

            size_t len = strlen(nuevoPaciente.direccion);
            if (len > 0 && nuevoPaciente.direccion[len - 1] == '\n') {
                nuevoPaciente.direccion[len - 1] = '\0';
            }

            if (strlen(nuevoPaciente.direccion) > 30) {
                printf("La direccion no puede superar los 30 caracteres. Intente nuevamente.\n");
                correcto = 1;
            }
        }
    } while (correcto == 1);
    clearScreen();
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Nombre y apellido:%s",nuevoPaciente.apellidoYnombre);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Edad:%i\n",nuevoPaciente.edad);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("DNI:%i\n",nuevoPaciente.dni);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Direccion:%s\n",nuevoPaciente.direccion);
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");

 do
    {
        correcto = 0;

        printf("Ingrese el telefono: ");
        fflush(stdin);

        if (fgets(telefono, sizeof(telefono), stdin) == NULL) {
            printf("Ingreso invalido. Intente nuevamente: \n");
            correcto = 1;
        } else {
            size_t longitud = strlen(telefono);

            if (telefono[longitud - 1] == '\n') {
                telefono[longitud - 1] = '\0';
            } else {
                correcto = 1;
                printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
                continue;
            }

            for (size_t i = 0; i < longitud - 1; i++) {
                if (!isdigit(telefono[i])) {
                    correcto = 1;
                    printf("El telefono solo puede contener numeros. Intente nuevamente.\n");
                    break;
                }
            }
            if (longitud - 1 >= 15) {
                correcto = 1;
                printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
            }

        }
    }while (correcto == 1);
     strcpy(nuevoPaciente.telefono,telefono);
     clearScreen();

    return nuevoPaciente;
}

///MOSTRAR EN ORDEN EL ARBOL(chequeada)
/*Esta función realiza un recorrido inorden en un árbol de pacientes, mostrando
la información de cada paciente, incluyendo apellido y nombre, edad, DNI, dirección y teléfono, en un formato estructurado.*/
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes)
{
    if(arbolPacientes!= NULL)
    {
        mostrarArbolINORDERPaciente(arbolPacientes->izq);
        if(arbolPacientes->dato.eliminado==0){
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("Apellido y nombre: %s\n",arbolPacientes->dato.apellidoYnombre);
        printf("Edad: %i\n",arbolPacientes->dato.edad);
        printf("DNI: %i\n",arbolPacientes->dato.dni);
        printf("Direccion: %s",arbolPacientes->dato.direccion);
        printf("Telefono: %s\n",arbolPacientes->dato.telefono);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        }
        mostrarArbolINORDERPaciente (arbolPacientes->der);
    }
}
///ARCHIVO DE PACIENTES(chequeada)
/*Esta función imprime la información de un paciente, incluyendo
apellido y nombre, edad, DNI, dirección y teléfono, en un formato estructurado.*/
void mostrarUnPaciente (paciente nuevoPaciente)
{
    printf("\n<<>><<>><<>><<>PACIENTE<<>><<>><<>><<>>\n");
    printf("Apellido y nombre: %s\n",nuevoPaciente.apellidoYnombre);
    printf("Edad: %i\n",nuevoPaciente.edad);
    printf("DNI: %i\n",nuevoPaciente.dni);
    printf("Direccion: %s\n",nuevoPaciente.direccion);
    printf("Telefono: %s\n",nuevoPaciente.telefono);
    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
}

///FUNCION DE MOSTRAR EL ARCHIVO DE PACIENTES (chequeada)
/*Esta función lee un archivo binario de pacientes, muestra la información
de cada paciente en un formato estructurado y luego cierra el archivo.*/
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
/*Esta función crea o sobrescribe un archivo binario de pacientes, carga la información de
pacientes desde un árbol y luego cierra el archivo. Imprime un mensaje indicando que los
datos del árbol se cargaron en el archivo.*/
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

///FUNCION ESCRIBIR EN EL ARCHIVO LO DEL ARBOL (chequeada)
/*Esta función realiza un recorrido inorden en un árbol de pacientes, escribiendo cada paciente
en un archivo binario proporcionado. Se utiliza para cargar datos de pacientes desde un árbol a un archivo.*/
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
/*carga datos de un archivo binario de pacientes en una estructura de árbol binario de búsqueda,
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
    }
    else
    {
        archi = fopen(archivo, "wb");
        if (archi != NULL)
        {

            fclose(archi);
        }
        else
        {
            printf("Error al abrir el archivo de ingresos.\n");
        }
    }
    return arbol;
}

///FUNCION DAR DE BAJA A UN EMPLEADO
/*Esta función elimina un empleado de una lista enlazada según el DNI
proporcionado. Busca el nodo con ese DNI, ajusta los punteros del nodo anterior
y siguiente, y luego libera la memoria del nodo eliminado. Si no se encuentra
ningún empleado con el DNI proporcionado, muestra un mensaje de error.*/
nodoEmpleados * darDeBajaEmpleado(nodoEmpleados * listaEmpleados)
{
    int dniEmpleado;
    int correcto;

    do
    {
        correcto = 0;
        printf("\nIngrese el DNI del empleado que quiere eliminar: ");
        if(scanf("%i", &dniEmpleado) != 1)
        {
            printf("La respuesta es invalida. Ingrese nuevamente el DNI del empleado: ");
            correcto = 1;
            while (getchar() != '\n'); // Limpia el búfer del teclado en caso de entrada no válida
        }
    }while(correcto == 1);

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

        if (anterior != NULL)
        {
            anterior->siguiente = actual->siguiente;
        }
        else
        {

            listaEmpleados = actual->siguiente;
        }
        free(actual);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>");
        printf("Empleado dado de baja exitosamente.");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
    }
    else
    {
        printf("\nNo se encontro ningun empleado con el DNI proporcionado.\n");
    }
    return listaEmpleados;
}

///FUNCION MODIFICAR EMPLEADO
/*Esta función permite modificar información de un empleado, identificado por su DNI. Solicita
la opción de modificación (nombre, usuario, DNI, clave, teléfono, perfil) y realiza los cambios
correspondientes. Si el DNI ingresado es incorrecto, muestra un mensaje de error.*/
nodoEmpleados * modificarEmpleado(nodoEmpleados * listaEmpleados)
{

    int eleccionModificar;
    int dniAbuscar;
    int correcto;
    char usuario[20];
    int nuevoDNI;
    int perfil;
    char telefono [15];
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
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("NOMBRE Y APELLIDO cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");

            }
            break;
            case 2:
                do
                {
                    correcto = 0;
                    printf("Ingrese el nuevo usuario: ");
                    fflush(stdin);
                    if(fgets(usuario, sizeof(usuario), stdin) == NULL)
                    {
                        correcto = 1;
                        printf("La respuesta no es valida. Por favor, ingrese el usuario del empleado.\n");
                    }
                    size_t longitud = strlen(usuario);
                    if (usuario[longitud - 1] == '\n')
                    {
                        usuario[longitud - 1] = '\0';
                    }
                    if (existeUsuario(listaEmpleados,usuario)!=NULL)
                    {
                        printf("El usuario ingresado ya existe. Por favor,intentelo otra vez.\n");
                        correcto = 1;
                    }
                }
                while (correcto == 1);
                strcpy(existeDNI->empleado.usuario,usuario);

                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("USUARIO cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                break;
            case 3:
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo DNI: ");
                    fflush(stdin);
                    if(scanf("%i",&nuevoDNI)!=1)
                    {
                        correcto =1;
                        printf("La respuesta no es valida. Por favor, ingrese el DNI del empleado.\n");
                    }
                    else if (existeEmpleado(listaEmpleados,nuevoDNI)!=NULL)
                    {
                        correcto =1;
                        printf("El DNI ingresado ya existe. Por favor,intentelo otra vez.\n");
                    }
                    int contador=0;
                    while (nuevoDNI != 0)
                    {
                        int aux= nuevoDNI;
                        aux /= 10;
                        contador++;
                    }

                    if (contador != 8&& correcto==0)
                    {
                        correcto = 1;
                        printf("El DNI debe tener exactamente 8 digitos. Intente nuevamente.\n");
                    }



                }
                while (correcto == 1);
                 existeDNI->empleado.dni= nuevoDNI;
                clearScreen();
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("DNI cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
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
                }while (correcto == 1);
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("CLAVE cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");

                break;
            case 5:
                do
                {
                    correcto=0;
                    printf("Ingrese el nuevo telefono: ");
                    fflush(stdin);
                    if (fgets(telefono, sizeof(telefono), stdin) == NULL)
                    {
                        correcto=1;
                        printf("La respuesta no es valida. Por favor, ingrese el telefono del empleado.\n");
                    }
                    else
                    {
                        size_t longitud = strlen(telefono);

                        if (telefono[longitud - 1] == '\n')
                        {
                            telefono[longitud - 1] = '\0';
                        }
                        else
                        {
                            correcto = 1;
                            printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
                            continue;
                        }

                        for (size_t i = 0; i < longitud - 1; i++)
                        {
                            if (!isdigit(telefono[i]))
                            {
                    correcto = 1;
                    printf("El telefono solo puede contener numeros. Intente nuevamente.\n");
                    break;
                }
            }
            if (longitud - 1 >= 15) {
                correcto = 1;
                printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
            }
        }

                 strcpy(existeDNI->empleado.telefono,telefono);

                }while (correcto == 1);
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("Telefono cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                break;
            case 6:
                do
                {
                    correcto=0;
                    printf("Ingrese el perfil (1=administrador, 2=profesional, 3=administrativo): ");
                    fflush(stdin);
                     if (scanf("%i", &perfil) != 1 || (perfil < 1 || perfil > 3))
                    {
                        correcto=1;
                        printf("\nRespuesta invalida. Vuelva a intentarlo.\n");
                    }
                }while(correcto==1);
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
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
                printf("PERFIL cambiado exitosamente.\n");
                puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");



            break;


            default:
                if(eleccionModificar!=0)
                {
                    printf("Error, la opcion que ingreso es invalida.\n");
                }
            }
        }while(eleccionModificar!=0);

    }else
    {
        printf("El DNI ingresado es incorrecto, no se pueden hacer modificaciones.\n");
    }
return listaEmpleados;
}

//FUNCION SI EXISTE UN USUARIO
nodoEmpleados * existeUsuario(nodoEmpleados* empleado,char usuario [])
{
    nodoEmpleados * actual = empleado;

    while(actual != NULL)
    {
        if (strcmp(actual->empleado.usuario,usuario)==0)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

///FUNCION BUSCAR Y MOSTRAR EMPLEADO MEDIANTE UN DNI
/*Esta función busca y muestra la información de un empleado por su DNI en una lista de empleados. Verifica la validez de la entrada y, si
encuentra el empleado, muestra sus detalles según un tipo de perfil especificado. Si no encuentra al empleado, emite un
mensaje de no coincidencia.*/
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
            printf("\nLa respuesta no es valida. Por favor, ingrese el DNI del empleado.\n");
        }
    }while(correcto==1);

    nodoEmpleados * existeDni = existeEmpleado(listaEmpleados, dniAbuscar);

    if(existeDni != NULL)
    {
        clearScreen();
        mostrarUnEmpleado(existeDni->empleado,tipoperfil);
    }
    else
    {
        printf("\nNo se encontro el empleado con el DNI solicitado.\n");
    }
}

///FUNCION MOSTRAR LISTA DOBLE EMPLEADOS
/*Esta función muestra la información de los empleados en una lista, considerando
un tipo de perfil específico. Recorre la lista y utiliza otra función para mostrar los detalles de cada empleado.*/
void mostrarListaEmpleados(nodoEmpleados * listaEmpleados, int tipoperfil)
{
    if(listaEmpleados != NULL)
    {
        mostrarUnEmpleado(listaEmpleados->empleado,tipoperfil);
        mostrarListaEmpleados(listaEmpleados->siguiente, tipoperfil);
    }
}

///FUNCION DE MOSTRAR UN EMPLEADO
/*Esta función imprime la información de un empleado de laboratorio, considerando un tipo de perfil específico.
Muestra el DNI, teléfono, apellido y nombre, usuario, y, si es un perfil específico, la clave; finalmente, muestra el perfil.*/
void mostrarUnEmpleado(empleadosDeLaboratorio aux, int tipoperfil)
{
    puts("\n<<>><<>><<>EMPLEADO<>><<>><<>><<>>\n");
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
        for (size_t i = 0; i < strlen(aux.clave); i++)
        {
            printf("*");
        }
        printf("\n");
    }
    printf("perfil: %s\n", aux.perfil);
    puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
}

///FUNCION PASAR DE LA LISTA DOBLE AL ARCHIVO
/*Esta función guarda en un archivo binario la información del primer empleado de
laboratorio en una lista, proporcionando el nombre del archivo. La escritura se realiza
en modo binario ("wb"), y se cierra el archivo después de la operación.*/
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
    }
    else
    {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}


///FUNCION PASAR DE ARCHIVO A LISTA DOBLE EMPLEADOS
/*Esta función lee un archivo binario de empleados de laboratorio, comparando el apellido y nombre
de cada empleado con los existentes en una lista doble enlazada. Si encuentra un empleado en el archivo
con un apellido y nombre mayores en orden lexicográfico, lo agrega al principio de la lista. La función imprime
un mensaje informativo y devuelve la lista actualizada.*/
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
    }
    else
    {
        archi = fopen(nombreArchivo, "wb");
        if (archi != NULL)
        {
            fclose(archi);
        }
        else
        {
            printf("Error al abrir el archivo de empleados.\n");
        }
}
return listaEmpleados;
}
///FUNCION ALTA EMPLEADOS
/*Esta función recibe una lista de empleados y un nuevo empleado. Verifica si ya existe un
empleado con el mismo DNI en la lista. Si no existe, crea un nuevo nodo con el empleado y lo
agrega a la lista en orden, imprimiendo un mensaje de éxito. Si ya existe, imprime un mensaje
indicando que el empleado ya está en la lista y no realiza ninguna acción. La función devuelve la lista actualizada.*/
nodoEmpleados * alta_de_empleados (nodoEmpleados * listaEmpleados)
{
    empleadosDeLaboratorio nuevoEmpleado;
    char nombre[40];
    char clave [20];
    char usuario[20];
    int perfil;
    char telefono[15];


    int correcto;
     puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
    printf("Cargando un Empleado");
    puts("<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>>");
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


        }while(correcto==1);
        nombre[strcspn(nombre, "\n")] = '\0';
        strcpy(nuevoEmpleado.apellidoYnombre,nombre);
         puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" APELLIDO Y NOMBRE:%s.\n",nuevoEmpleado.apellidoYnombre);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
    do
    {
        correcto=0;
        printf("Ingrese el DNI: ");
        fflush(stdin);
        if(scanf("%i", &nuevoEmpleado.dni)!=1)
        {
            correcto = 1;
            printf("Ingreso invalido. Intente nuevamente: \n");
        } else if(existeEmpleado(listaEmpleados,nuevoEmpleado.dni)!=NULL)
        {
            printf("El DNI ingresado ya existe. Por favor,intentelo otra vez.\n");
        }
        {
            int contador = 0;
            int nuevoDNI= nuevoEmpleado.dni;

            while (nuevoDNI != 0) {
                nuevoDNI /= 10;
                contador++;
            }

            if (contador != 8) {
                correcto = 1;
                printf("El DNI debe tener exactamente 8 digitos. Intente nuevamente.\n");
            }
        }
    }
    while(correcto == 1);


    nodoEmpleados * existeUnEmpleado = existeEmpleado(listaEmpleados, nuevoEmpleado.dni);

    if(existeUnEmpleado==NULL)
    {
        clearScreen();
         puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" APELLIDO Y NOMBRE:%s.\n",nuevoEmpleado.apellidoYnombre);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" DNI:%i.\n",nuevoEmpleado.dni);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
       do {
        correcto = 0;

        printf("Ingrese el telefono: ");
        fflush(stdin);

        if (fgets(telefono, sizeof(telefono), stdin) == NULL) {
            printf("Ingreso invalido. Intente nuevamente: \n");
            correcto = 1;
        } else {
            size_t longitud = strlen(telefono);

            if (telefono[longitud - 1] == '\n') {
                telefono[longitud - 1] = '\0';
            } else {
                correcto = 1;
                printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
                continue;
            }

            for (size_t i = 0; i < longitud - 1; i++) {
                if (!isdigit(telefono[i])) {
                    correcto = 1;
                    printf("El telefono solo puede contener numeros. Intente nuevamente.\n");
                    break;
                }
            }
            if (longitud - 1 >= 15) {
                correcto = 1;
                printf("El telefono debe tener menos de 15 digitos. Intente nuevamente.\n");
            }
        }
    } while (correcto == 1);
        strcpy(nuevoEmpleado.telefono,telefono);
        clearScreen();
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" APELLIDO Y NOMBRE:%s.\n",nuevoEmpleado.apellidoYnombre);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" DNI:%i.\n",nuevoEmpleado.dni);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("TELEFONO:%s.\n",nuevoEmpleado.telefono);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");


        do
        {
            correcto = 0;
            printf("Ingrese el usuario: ");
            fflush(stdin);
            if(fgets(usuario, sizeof(usuario), stdin) == NULL)
            {
                correcto = 1;
                printf("Respuesta invalida. Vuelva a intentarlo.\n");
            }
            size_t longitud = strlen(usuario);
            if (usuario[longitud - 1] == '\n')
            {
                usuario[longitud - 1] = '\0';
            }
            if (existeUsuario(listaEmpleados,usuario)!=NULL)
            {
                printf("El usuario ingresado ya existe. Por favor,intentelo otra vez.\n");
                correcto = 1;
            }
        }
        while(correcto==1);
        usuario[strcspn(usuario, "\n")] = '\0';
        strcpy(nuevoEmpleado.usuario,usuario);
        clearScreen();
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" APELLIDO Y NOMBRE:%s.\n",nuevoEmpleado.apellidoYnombre);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" DNI:%i.\n",nuevoEmpleado.dni);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("TELEFONO:%s.\n",nuevoEmpleado.telefono);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" USUARIO:%s.\n",nuevoEmpleado.usuario);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");

        do
        {
            correcto=0;
            printf("Ingrese el perfil (1=administrador, 2=profesional, 3=administrativo): ");
            fflush(stdin);
            if (scanf("%i", &perfil) != 1 || (perfil < 1 || perfil > 3))
            {
                correcto=1;
                printf("Respuesta invalida. Vuelva a intentarlo.\n");
            }
        }
        while(correcto==1);
        if (perfil==1)
        {
            strcpy(nuevoEmpleado.perfil,"administrador");
        }
        else if(perfil==2)
        {
            strcpy(nuevoEmpleado.perfil,"profesional");
        }
        else if(perfil==3)
        {
            strcpy(nuevoEmpleado.perfil,"administrativo");
        }
        clearScreen();
         puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" APELLIDO Y NOMBRE:%s.\n",nuevoEmpleado.apellidoYnombre);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" DNI:%i.\n",nuevoEmpleado.dni);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("TELEFONO:%s.\n",nuevoEmpleado.telefono);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" USUARIO:%s.\n",nuevoEmpleado.usuario);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" PERFIL:%s.\n",nuevoEmpleado.perfil);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");

            correcto=0;
            printf("Ingrese la clave: ");
             int i = 0;
        while (1)
            {
            char tecla = _getch();
            if (tecla == 13)
            {
                clave[i] = '\0';
                break;
            } else if (tecla == 8)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            } else
            {
                clave[i] = tecla;
                printf("*");
                i++;
            }
        }

        clave[strcspn(clave, "\n")] = '\0';
        strcpy(nuevoEmpleado.clave,clave);
        clearScreen();
       puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" APELLIDO Y NOMBRE:%s.\n",nuevoEmpleado.apellidoYnombre);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" DNI:%i.\n",nuevoEmpleado.dni);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("TELEFONO:%s.\n",nuevoEmpleado.telefono);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" USUARIO:%s.\n",nuevoEmpleado.usuario);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf(" PERFIL:%s.\n",nuevoEmpleado.perfil);
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("CLAVE ingresada exitosamente.\n");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        nodoEmpleados * nuevo = crearNodoEmpleados(nuevoEmpleado);

        listaEmpleados = agregarEnOrdenEmpleados(listaEmpleados, nuevo);
        clearScreen();
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        printf("El empleado fue agregado.\n");
        puts("\n<<>><<>><<>><<>><<>><<>><<>><<>><<>>\n");
        system("pause");
    }
    else
    {
        printf("Ya existe un empleado con ese DNI.\n");
    }
    return listaEmpleados;
}

///FUNCION AGREGAR A LA LISTA ORDENADO POS APELLIDO Y NOMBRE
/*Esta función recibe una lista de empleados y un nuevo nodo de empleado. Inserta el
nuevo nodo en orden alfabético por apellido y nombre en la lista doblemente
enlazada, ajustando los punteros de manera adecuada. La función devuelve la lista actualizada.*/
nodoEmpleados * agregarEnOrdenEmpleados(nodoEmpleados * listaEmpleados, nodoEmpleados * nuevoNodo)
{
    if (listaEmpleados == NULL || strcmpi(nuevoNodo->empleado.apellidoYnombre, listaEmpleados->empleado.apellidoYnombre) < 0)
    {
        nuevoNodo->siguiente = listaEmpleados;
        if (listaEmpleados != NULL)
        {
            listaEmpleados->anterior = nuevoNodo;
        }
        return nuevoNodo;
    }

    nodoEmpleados * actual = listaEmpleados;
    while (actual->siguiente != NULL && strcmpi(nuevoNodo->empleado.apellidoYnombre, actual->siguiente->empleado.apellidoYnombre) > 0)
    {
        actual = actual->siguiente;
    }

    nuevoNodo->siguiente = actual->siguiente;
    nuevoNodo->anterior = actual;
    if (actual->siguiente != NULL)
    {
        actual->siguiente->anterior = nuevoNodo;
    }
    actual->siguiente = nuevoNodo;
    clearScreen();

    return listaEmpleados;
}

///FUNCION SI EXISTE UN EMPLEADO
/*Esta función busca un empleado por su número de DNI en una lista doblemente enlazada.
Devuelve un puntero al nodo del empleado si se encuentra, de lo contrario, devuelve NULL.*/
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
/*Esta función crea un nuevo nodo para la lista doblemente enlazada de empleados, asignando
los datos proporcionados al nodo y estableciendo los punteros en NULL. Retorna el nodo recién creado.*/
nodoEmpleados * crearNodoEmpleados(empleadosDeLaboratorio dato)
{
    nodoEmpleados * aux = (nodoEmpleados*)malloc(sizeof(nodoEmpleados));
    if (aux == NULL)
    {
        printf("ERROR: No se pudo crear el nodo para el empleado.\n");
    }
    aux->empleado.dni = dato.dni;
    strcpy(aux->empleado.telefono, dato.telefono);
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


