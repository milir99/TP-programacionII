#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "switch.h"
#include <ctype.h>
#include <string.h>
#include <time.h>

//FUNCIONES DE PRACTICAS
//FUNCION DE LISTA PRACTICA A ARCHIVO
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
// FUNCION DE ARCHIVO A LISTA DE PRACTICAS
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
/*/ solicita el nombre de una practica a modificar. Luego, busca la practica en una lista enlazada.
Si encuentra la practica, solicita el nuevo nombre y realiza la modificaci�n.
 Retorna la lista de practicas actualizada. La entrada se valida para asegurar un nombre v�lido./*/
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista)
{
    char nombrePractica[40];
    char nuevoNombre[40];

    // Solicitar el nombre de la practica a modificar
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
// agrega una nueva practica al principio de la lista enlazada de practicas de laboratorio si no existe previamente, verificando por nombre

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
/*/ Añade un nodo de practica al principio de una lista enlazada de practicas de laboratorio.
Si la lista est� vac�a, asigna la nueva practica como el primer nodo; de lo contrario, enlaza la nueva practica al principio y actualiza la cabeza de la lista.
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

//FUNCION VERIFICAR FECHA
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
//FUNCION BAJA DE INGRESO
/*/marca como eliminado el ingreso con el numero especificado y elimina en cascada la lista de practicas asociadas.
Primero busca el ingreso en la lista y, si lo encuentra, establece el indicador "eliminado" en 1 y procede a eliminar la lista de practicas en cascada.
 Retorna la lista de ingresos actualizada. Si el numero de ingreso no coincide, muestra un mensaje de error./*/

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
        printf("EL nro de ingreso no coincide con los ingresos del paciente\n");
    }
    return lista;
}
//FUNCION BAJA DE PXI en cascada.
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
//FUNCION  DE MODIFICACION DE INGRESOS
/*/Busca un ingreso en una lista por numerode ingreso, permite al usuario modificar fecha de ingreso, fecha de retiro o matricula profesional,
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
                        printf("Entrada invalida. Debes ingresar un numeroentero.\n");

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
cuyo numerode ingreso coincida con el proporcionado, o devuelve NULL si no se encuentra./*/
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
/*/agrega un nuevo ingreso a un paciente existente en un arbol binario de pacientes.
Verifica la existencia del paciente, obtiene el numero del ultimo ingreso,
 crea un nuevo nodo de ingreso, y añade practicas a dicho ingreso. Si tiene exito,
  actualiza la lista de ingresos del paciente y retorna el arbol de pacientes.
En caso de error, muestra un mensaje apropiado y retorna NULL. /*/
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes * paciente, ingresos dato)
{
   printf("in %i \n",dato.dniPaciente);
   nodoArbolPacientes * existencia = existePaciente(paciente,dato.dniPaciente);
   printf("out %i \n",existencia->dato.edad);


    if(existencia==NULL)
    {
        printf("El Paciente NO existe.\n");
        printf("Debe darle de alta en el sistema ante de generar un ingreso.\n");
        return NULL;

    }
    else
    {

        int nroIngreso = buscarUltimoNroIngreso(existencia->listaIngresos);
        printf("\npaso %i\n",nroIngreso);

        nodoIngresos*nuevoIngresoNodo=crearNodoIngreso(dato);


       nuevoIngresoNodo->listaDePracticas=alta_de_pxi(nuevoIngresoNodo->listaDePracticas,nroIngreso);

        if(nuevoIngresoNodo->listaDePracticas== NULL)
        {
            printf("Error al agregar las practicas.\n");
            return NULL;
        }
        else
        {
            existencia->listaIngresos= agregarPpioIngreso(existencia->listaIngresos,nuevoIngresoNodo);
        }
    }
    printf("Ingreso cargado Exitosamente\n");
    return paciente;
}
// FUNCION CARGAR UN INGRESO
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
//FUNCION QUE DEVUELVE EL ULTIMO NUMERO DE INGRESO
/*/busca y retorna el numero del ultimo ingreso en una lista enlazada de ingresos.
 Recorre la lista hasta el final, actualizando el numero de ingreso a medida que avanza.
 Retorna el numero del ultimo ingreso encontrado o 0 si la lista esta vacia.
  La impresion dentro de la funcion no afecta el resultado y puede ser eliminada/*/
int buscarUltimoNroIngreso(nodoIngresos* lista)
{
    int nroIngreso = 0;

    if (lista != NULL)
    {;
        nodoIngresos* seg = lista;

        while (seg != NULL)
        {
            nroIngreso = seg->dato.nroIngreso;
            seg = seg->siguiente;
        }
    }
    return nroIngreso;
}

//FUNCION DE AGREGAR  INGRESO AL PRINCIPIO DE LA LISTA(DONE)
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
//FUNCION DE EXISTENCIA DE PACIENTE(DONE)//PODRIA CAMBIARLE EL NOMBRE A BUSCAR
/*/busca un paciente por su numero de DNI en un arbol binario de busqueda.
Retorna el nodo del paciente si existe, de lo contrario, devuelve NULL/*/
nodoArbolPacientes* existePaciente(nodoArbolPacientes* pacientes, int dniPaciente)
{if (pacientes == NULL) {

        return NULL;
}

    if (dniPaciente == pacientes->dato.dni) {

        return pacientes;
    }

   nodoArbolPacientes* resultadoIzquierdo = existePaciente(pacientes->izq, dniPaciente);
    if (resultadoIzquierdo != NULL) {
        return resultadoIzquierdo;
    }

   nodoArbolPacientes* resultadoDerecho = existePaciente(pacientes->der, dniPaciente);
    if (resultadoDerecho != NULL) {
        return resultadoDerecho;
    }

    printf("\n.%i no encontrado. \n", pacientes->dato.dni);
    return NULL;


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
/*/agrega practicas a un ingreso, solicitando codigos de practicas, verificando su existencia, y creando nodos en una lista enlazada. Retorna la lista actualizada/*/

nodoPracticasXIngreso *alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso)
{
    char eleccion;
    char  nombrePractica[40];


    do
    {
        printf("Ingrese nombre de la practica a realizar:\n");
        fflush(stdin);
        scanf("%s",nombrePractica);

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
//FUNCION BUSCAR PRACTICA EN EL ARCHIVO.
//Busca una practica por nombre en una lista, retornando su numerosi se encuentra, y -1 si no.
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
//
//
//
//
///ARBOLES DE PACIENTES(chequeada)

nodoArbolPacientes * iniciarArbol ()
{
    return NULL;
}

// CREAR NODO ARBOL PACIENTE(chequeada)
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

//INSERTAR NODO ARBOL PACIENTE(chequeada)
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

//MODIFICACION DEL PACIENTE EN EL ARBOL(chequeada)
/*Antes de usar esta funcion, se debe chequear que el arbol no este vacio, y que lo que devuelva no sea NULL*/
nodoArbolPacientes * modificacionPacientesArbol (nodoArbolPacientes * arbolPaciente)
{
    // RE INTRODUCIR EL NODO EN EL ARBOL YA QUE SI CAMBIA NOMBRE SE CAMBIA EL ORDEN

    int eleccionModificar;
    int dniAbuscar;
    int correcto;
    do
    {  correcto = 0;
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
                {   correcto=0;
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
                {   correcto=0;
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
                {   correcto=0;
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
                {   clearScreen();
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
//FUNCION PARA REUBICAR NODO QUE CAMBIA DE NOMBRE (chequeada)
//desvincula el nodo con el DNI especificado del árbol, luego lo inserta nuevamente, manteniendo la estructura del árbol binario de búsqueda.
nodoArbolPacientes *reubicarNodoEnArbol(nodoArbolPacientes *arbol,nodoArbolPacientes *nodoAReubicar)
{

    arbol = removerNodoPacienteDelArbolPorNombre(arbol, nodoAReubicar->dato.apellidoYnombre);

    arbol = insertarNodoArbolPaciente(arbol, nodoAReubicar);

    return arbol;
}

// FUNCION REMOVER NODO DE UN ARBOL(chequeada)
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

        // No liberar la memoria del nodo eliminado

        return arbol;
    }

    return arbol;
}


//ALTA PACIENTE EN EL ARBOL(chequeada)
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

//DAR DE BAJA PACIENTEchequeada)
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
//CARGAR PACIENTE(chequeada)
paciente cargarUnPaciente() {
    paciente nuevoPaciente;
    int correcto;


    do {
        correcto = 0;
        printf("Ingrese nombre y apellido del paciente: ");
        fflush(stdin);
        if (fgets(nuevoPaciente.apellidoYnombre, sizeof(nuevoPaciente.apellidoYnombre), stdin) == NULL) {
            printf("Entrada no valida. Por favor, ingrese un nombre y apellido del paciente.\n");
            correcto = 1;
        }
    } while (correcto == 1);


    do {
        correcto = 0;
        printf("\nIngrese edad del paciente: ");
        fflush(stdin);
        if ((scanf("%i", &nuevoPaciente.edad) != 1) || (nuevoPaciente.edad < 0) || (nuevoPaciente.edad>200)) {
            printf("Entrada no valida. Por favor, ingrese una edad valida del paciente.\n");
            correcto = 1;
        }

    } while (correcto == 1);

    do {
        correcto = 0;
        printf("\nIngrese el DNI del paciente: ");
        fflush(stdin);
        if (scanf("%i", &nuevoPaciente.dni) != 1) {
            printf("Entrada no valida. Por favor, ingrese el DNI del paciente.\n");
            correcto = 1;
        }
    } while (correcto == 1);

    // Ingreso de Dirección
    do {
        correcto = 0;
        printf("\nIngrese la direccion del paciente: ");
        fflush(stdin);
        if (fgets(nuevoPaciente.direccion, sizeof(nuevoPaciente.direccion), stdin) == NULL) {
            printf("Entrada no valida. Por favor, ingrese la direccion del paciente.\n");
            correcto = 1;
        }
    } while (correcto == 1);

    do {
        correcto = 0;
        printf("\nIngrese el telefono del paciente: ");
        fflush(stdin);
        if (scanf("%s", nuevoPaciente.telefono) != 1) {
            printf("Entrada no valida. Por favor, ingrese el telefono del paciente.\n");
            correcto = 1;
        }
    } while (correcto == 1);

    return nuevoPaciente;
}
//MOSTRAR EN ORDEN EL ARBOL(chequeada)
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes)
{  if(arbolPacientes!= NULL)
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
//FUNCION DE MOSTRAR EL ARCHIVO DE PACIENTES (chequeada)
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
//FUNCION ESCRIBIR EN EL ARCHIVO LO DEL ARBOL (chequeada)
void cargarArchivoPacientesDelArbol (FILE * archi,nodoArbolPacientes * arbolPacientes)
{
    if(arbolPacientes)
    {
        cargarArchivoPacientesDelArbol (archi,arbolPacientes->izq);
        fwrite(&arbolPacientes->dato,sizeof(paciente),1,archi);
        cargarArchivoPacientesDelArbol (archi, arbolPacientes->der);
    }
}
//FUNCION PARA  DATOS DE ARCHIVO AL ARBOL DE PACIENTE(CHEQUEADA)
/*   carga datos de un archivo binario de pacientes en una estructura de árbol binario de búsqueda,
 utilizando la función insertarNodoArbolPaciente para añadir cada paciente al árbol. */
nodoArbolPacientes* archivoAArbolPacientes  ( char archivo[],nodoArbolPacientes* arbol)
{   paciente aux;
    FILE *archi=fopen(archivo,"rb");
    if(archi!=NULL)
    {  while(fread(&aux,sizeof(paciente),1,archi)==1)
    {
      arbol = insertarNodoArbolPaciente(arbol, crearNodoArbol(aux));
    }

        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    printf("Se cargaron los datos del Archivo al arbol.\n");
 return arbol;
}
//
//
//
//
//FUNCION PASAR DE LA LISTA DOBLE AL ARCHIVO
void pasarListaEmpleadosAarchivo(nodoEmpleados * listaEmpleados, char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo, "wb");

    if(archi != NULL)
    {
        if(listaEmpleados!= NULL)
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


