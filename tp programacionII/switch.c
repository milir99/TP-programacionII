#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include "switch.h"
#include <windows.h>
#include <conio.h>

 char archivoEmpleado []="empleados.bin";
 char archivoPracticas[]="lasPracticas.bin";
 char archivoPXI []="PXI.bin";
 char archivoIngresos []="ingresos.bin";
 char archivoPacientes []= "paciente.bin";
//PASARLE A LOS SWITCH, EL ARBOL, Y LISTAS

void InicioDelPrograma()
{
    nodoPracticasLaboratorio* listaPracticasLaboratorio = inicListaPracticas();

    nodoArbolPacientes* arbolPacientes=iniciarArbol();

    nodoEmpleados* listaEmpleados= iniclistaEmpleados();

    listaEmpleados = pasarArchivoAlistaEmpleados(archivoEmpleado,listaEmpleados);

    listaPracticasLaboratorio = ArchivoAListaPracticas(archivoPracticas,listaPracticasLaboratorio);

    arbolPacientes = archivoAArbolPacientes(archivoPacientes,arbolPacientes);

    arbolPacientes = archivoAListaIngresos(archivoIngresos,arbolPacientes);

    arbolPacientes = archivoAListaPXI(archivoPXI,arbolPacientes);

    if(listaEmpleados == NULL)
    {
        printf(" _ ____  _                           _     _         __    _ \n");
    printf("(_) __ )(_) ___ _ ____   _____ _ __ (_) __| | ___   / /_ _| |\n");
    printf("| |  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\ / / _` | |\n");
    printf("| | |_) | |  __/ | | \\ V /  __/ | | | | (_| | (_) / / (_| |_|\n");
    printf("|_|____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/_/ \\__,_(_)\n");


    printf("Acontinuacion debe ingresar sus datos para generar el primer usuario del programa.\n");
        listaEmpleados=alta_de_empleados(listaEmpleados);

    }
    int perfil = usuarioYclavePrincipio(listaEmpleados);

    if(perfil==1)
    {
        switchAdmin(&arbolPacientes,&listaEmpleados,&listaPracticasLaboratorio);
    }
    else if(perfil==2)
    {
        switchProfesionales(&arbolPacientes,&listaEmpleados,&listaPracticasLaboratorio);
    }
    else if(perfil==3)
    {
        switchAdministrativo(&arbolPacientes,&listaEmpleados,&listaPracticasLaboratorio);;
    }

    FinDelPrograma(arbolPacientes,listaEmpleados,listaPracticasLaboratorio);



}
void FinDelPrograma(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas)
{
    listaPracticaAArchivo(archivoPracticas,listaPracticas);
    pasarListaEmpleadosAarchivo(listaEmpleados,archivoEmpleado);
    listaPXIsAArchivo(arbolPaciente,archivoPXI);
    listaIngresosAArchivo(arbolPaciente,archivoIngresos);
    cargarArchivoPaciente(archivoPacientes,arbolPaciente);
}


int usuarioYclavePrincipio(nodoEmpleados* listaEmpleados)
{
    char clave[20];
    char usuario[20];
    int intentos = 0;
    int i;
    int existe;
    empleadosDeLaboratorio datosEmpleado;

    do
    {
        clearScreen();
        recuadro(30, 5, 80, 20);
        gotoxy(48, 8);
        printf("INICIO DE SESION");
        gotoxy(35, 10);
        printf("Usuario: ");
        fflush(stdin);
        fgets(usuario, sizeof(usuario), stdin);
        size_t longitud = strlen(usuario);

        if (usuario[longitud - 1] == '\n')
        {
            usuario[longitud - 1] = '\0';
        }

        gotoxy(35, 12);
        printf("Clave: ");

         i = 0;
        while (1)
        {
            char tecla = _getch();
            if (tecla == 13)
            {
                clave[i] = '\0';
                break;
            }
            else if (tecla == 8)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                clave[i] = tecla;
                printf("*");
                i++;
            }
        }
        longitud = strlen(clave);
        if (clave[longitud - 1] == '\n')
        {
            clave[longitud - 1] = '\0';
        }

        existe = compararUsuario(clave, usuario, listaEmpleados, &datosEmpleado);
        ocultarCursor();
        gotoxy(90,10);centrarTexto("C A R G A N D O...", 21);

        for (i = 20; i <= 90; i++) {
            gotoxy(i, 23);
            printf("%c", 177);
        }

        for (i = 20; i <= 90; i++) {
            gotoxy(i, 23);
            printf("%c", 219);
            Sleep(15);
        }

        gotoxy(10, 21);
        printf("                                                                    ");
        gotoxy(10, 23);
        printf("                                                                    ");

        activarCursor();

        if (existe != 0)
        {
            ocultarCursor();
            centrarTexto("C A R G A N D O...", 21);

            for (i = 4; i <= 76; i++)
            {
                gotoxy(i, 23);
                printf("%c", 170);
            }

            for (i = 3; i <= 76; i++)
            {
                gotoxy(i, 23);
                printf("%c", 219);
            }

            gotoxy(3, 21);
            printf("                                                                    ");
            gotoxy(3, 23);
            printf("                                                                    ");

            activarCursor();

            clearScreen();

            printf(" _ ____  _                           _     _         __    _ \n");
            printf("(_) __ )(_) ___ _ ____   _____ _ __ (_) __| | ___   / /_ _| |\n");
            printf("| |  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\ / / _` | |\n");
            printf("| | |_) | |  __/ | | \\ V /  __/ | | | | (_| | (_) / / (_| |_|\n");
            printf("|_|____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/_/ \\__,_(_)\n");

            gotoxy(25, 5);
            printf("%s\n", datosEmpleado.apellidoYnombre);
            system("pause");
            return existe;
        } else {
            gotoxy(23, 22);
            printf("Usuario o clave ingresado incorrectamente. Intentelo otra vez.\n");
            Sleep(5000);
            intentos++;

            if (intentos == 3)
            {
                clearScreen();
                printf("Demasiados intentos fallidos.\n");
                printf("Comuniquese con un Administrador para generar cambio de clave o usuario.\n");
                return 0;
            }
        }
    } while (1);
}

int compararUsuario(char clave[], char usuario[], nodoEmpleados *listaEmpleados,empleadosDeLaboratorio*datoUsuario)
{
    int tipoperfil = 0;

    while (listaEmpleados != NULL)
    {
        if (strcmp(usuario, listaEmpleados->empleado.usuario) == 0 && strcmp(clave, listaEmpleados->empleado.clave) == 0)
        {
                *datoUsuario = listaEmpleados->empleado;
            if (strcmpi("administrador", listaEmpleados->empleado.perfil) == 0)
            {
                tipoperfil = 1; // Administrator
            }
            else if (strcmpi("profesional", listaEmpleados->empleado.perfil) == 0)
            {
                tipoperfil = 2; // Professional
            }
            else if (strcmpi("administrativo", listaEmpleados->empleado.perfil) == 0)
            {
                tipoperfil = 3; // Administrative
            }
            // Exit the loop early if a match is found
            break;
        }
        listaEmpleados = listaEmpleados->siguiente;
    }
    return tipoperfil;
}

//SWITCH PARAPROFESIONALES
void switchProfesionales(nodoArbolPacientes **arbolPaciente,nodoEmpleados**listaEmpleados,nodoPracticasLaboratorio**listaPracticas)
{
    int eleccion1;
    int eleccion2;
    int eleccion3;
    //int tipoPerfil = 3;
    int buscarPractica;
    int correcto;
    int dniPacienteAbuscar;
    nodoArbolPacientes * existe = iniciarArbol();

    do
    {
        clearScreen();
        printf("Ingresado como Profesional.\n");
        printf("Bienvenido/a!\n");
        printf("Ingrese la opcion que desee realizar o 0 para finalizar.\n");
        printf("1. Administrar practicas.\n");
        printf("2. Administrar pacientes. \n");
        fflush(stdin);
        scanf("%i", &eleccion1);

        switch(eleccion1)
        {
        case 1:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                clearScreen();
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Agregar una practica.\n");
                printf("2. Modificar una practica .\n");
                printf("3. Buscar una practica.\n");
                printf("4. Mostrar todas las practicas.\n");
                printf("5. Dar de baja una practica.\n");
                fflush(stdin);
                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:
                    *listaPracticas =  alta_de_practica(*listaPracticas);
                    break;

                case 2:
                    *listaPracticas = modificacion_de_practica(*listaPracticas);
                    break;

                case 3:
                    buscarPractica = mostrarPracticasQueComienzanCon(*listaPracticas);
                    if(buscarPractica == 0)
                    {
                        printf("La practica que desea buscar no existe.\n");
                    }
                    break;

                case 4:
                     do
                    {
                        printf("Mostrar las practicas organizadas por: \n");
                        printf("1. Nombre de Practica \n");
                        printf("2. Nro de Practica.\n");
                        printf("0. Volver.\n");
                        fflush(stdin);
                        scanf("%i", &eleccion1);
                        clearScreen();
                        switch(eleccion1)
                        {
                        case 1:
                            mostrarListaPorNombre(*listaPracticas);
                            break;
                        case 2:
                            mostrarListaPracticasadmin(*listaPracticas);
                            break;
                        default:
                            if(eleccion1!=0)
                            {
                                printf("Error, la opcion que ingreso es invalida.\n");
                            }
                            break;
                        }

                    }while(eleccion1!=0);
                    break;

                case 5:
                   * listaPracticas = baja_de_practicasLaboratorio(*listaPracticas, *arbolPaciente);
                    break;

                default:
                    if(eleccion2!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion2 != 0);

        case 2:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                clearScreen();
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Ver pacientes.\n");
                printf("2. Buscar un paciente.\n");
                printf("3. Ingresar resultados.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:
                    mostrarArbolINORDERPaciente(*arbolPaciente);
                    break;

                case 2:
                    do
                    {
                        correcto=0;
                        printf("Ingrese el DNI del paciente que desea buscar: ");
                        fflush(stdin);
                        if(scanf("%i", &dniPacienteAbuscar)!=1)
                        {
                            correcto = 1;
                            printf("Respuesta invalida. Intente nuevamente: \n");
                        }
                    }while(correcto == 1);
                    existe = existePaciente(*arbolPaciente,dniPacienteAbuscar);
                    mostrarUnPaciente(existe->dato);
                    break;
                    case 3:
                         modificar_PXI(*arbolPaciente,*listaPracticas);
                        break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion3 != 0);
            break;
        }
    }while(eleccion1!=0);
}

//SWITCH PARA ADMINISTRATIVOS
void switchAdministrativo(nodoArbolPacientes ** arbolPaciente,nodoEmpleados ** listaEmpleados,nodoPracticasLaboratorio ** listaPracticas)
{
    int eleccion1;
    int eleccion2;
    int eleccion3;
    int eleccion4;
    int dniPacienteAbuscar;
    int correcto;
    int buscarPractica;
    nodoArbolPacientes * existe = iniciarArbol();
    int nroIngreso;
     nodoIngresos* buscado;

    do
    {
        clearScreen();
        printf("Ingresado como administrativo\n");
        printf("\nBienvenido/a!\n");
        printf("Ingrese la opcion que desee realizar o 0 para finalizar.\n");
        printf("1. Administrar paciente.\n");
        printf("2. Ver practicas.\n");
        printf("3. Ingresos.\n");
        fflush(stdin);
        scanf("%i", &eleccion1);

        switch(eleccion1)
        {
        case 1:
            //modificar solo al paciente, agregar, dar de baja, buscar, mostrar
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un paciente.\n");
                printf("2. Modificar SOLO un paciente.\n");
                printf("3. Buscar un paciente.\n");
                printf("4. Mostrar todos los pacientes.\n");
                printf("5. Dar de baja un paciente.\n");
                fflush(stdin);
                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:
                   * arbolPaciente=altaArbolPacientes(*arbolPaciente);
                    break;

                case 2:
                    *arbolPaciente = modificacionPacientesArbol (*arbolPaciente);
                    break;

                case 3:
                    do
                    {
                        correcto=0;
                        printf("Ingrese el DNI del paciente que desea buscar: ");
                        fflush(stdin);
                        if(scanf("%i", &dniPacienteAbuscar)!=1)
                        {
                            correcto = 1;
                            printf("Respuesta invalida. Intente nuevamente: \n");
                        }
                    }while(correcto == 1);
                    existe = existePaciente(*arbolPaciente,dniPacienteAbuscar);
                    mostrarUnPaciente(existe->dato);
                    break;

                case 4:
                    mostrarArbolINORDERPaciente(*arbolPaciente);
                    break;

                case 5:
                    *arbolPaciente = darBajaPaciente(*arbolPaciente);
                    break;

                default:
                    if(eleccion2!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion2 != 0);
            break;
        case 2:
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Ver practicas.\n");
                printf("2. Buscar practica.\n");

                scanf("%i", &eleccion2);

                switch(eleccion2)
                {
                case 1:
                   do
                    {
                        printf("Mostrar las practicas organizadas por: \n");
                        printf("1. Nombre de Practica \n");
                        printf("2. Nro de Practica.\n");
                        printf("0. Volver.\n");
                        fflush(stdin);
                        scanf("%i", &eleccion4);
                        clearScreen();
                        switch(eleccion4)
                        {
                        case 1:
                            mostrarListaPorNombre(*listaPracticas);
                            break;
                        case 2:
                            mostrarListaPracticas(*listaPracticas);
                            break;
                        default:
                            if(eleccion3!=0)
                            {
                                printf("Error, la opcion que ingreso es invalida.\n");
                            }
                            break;
                        }

                    }while(eleccion4!=0);
                    break;

                case 2:
                    buscarPractica = mostrarPracticasQueComienzanCon(*listaPracticas);
                    if(buscarPractica == 0)
                    {
                        printf("La practica que desea buscar no existe.\n");
                    }
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion2 != 0);
            break;
        case 3:
            //dar de alta, buscar, mostrar, modificar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un ingreso.\n");
                printf("2. Modificar un ingreso.\n");
                printf("3. Buscar un ingreso.\n");
                printf("4. Mostrar todos los ingresos.\n");
                printf("5. Mostrar pacientes\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:

                    *arbolPaciente = alta_de_ingreso(*arbolPaciente, *listaPracticas);
                    break;

                case 2:
                    do
                    {
                        correcto = 0;
                        printf("\nIngrese el Nro de ingreso: ");
                        fflush(stdin);
                        if (scanf("%i",&nroIngreso) != 1)
                        {
                            printf("Entrada no valida. Por favor, ingrese el DNI del paciente.\n");
                            correcto = 1;
                        }

                    }while (correcto == 1);

                    *arbolPaciente = modificacion_de_ingreso(*arbolPaciente,nroIngreso);
                    break;

                case 3:
                    do
                    {
                        correcto = 0;
                        printf("\nIngrese el Nro de ingreso: ");
                        fflush(stdin);
                        if (scanf("%i",&nroIngreso) != 1)
                        {
                            printf("Entrada no valida. Por favor, ingrese el DNI del paciente.\n");
                            correcto = 1;
                        }
                    }while (correcto == 1);
                     buscado=buscarIngreso(*arbolPaciente,nroIngreso);
                     mostrarUnIngreso(buscado->dato);
                    break;

                case 4:
                    switchXingreso(*arbolPaciente);
                    mostrarIngresosConFiltro(*arbolPaciente);
                    break;
                case 5:
                    mostrarArbolINORDERPaciente(*arbolPaciente);
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion3 != 0);
            break;

        default:
            if(eleccion1!=0)
            {
                printf("Error, la opcion que ingreso es invalida.\n");
            }
        }
    }while(eleccion1!=0);
}

//SWITCH PARA ADMINISTRADORES
void switchAdmin(nodoArbolPacientes ** arbolPacientes, nodoEmpleados * *listaEmpleados, nodoPracticasLaboratorio ** listaPracticas)
{
    int eleccion1;
    int eleccion2;
    int eleccion3;
    int eleccion4;
    int eleccion5;
    int correcto;
    int dniPacienteAbuscar;
    int buscarPractica;
    int tipoPerfil=1;
    nodoArbolPacientes * existe = iniciarArbol();

    do
    {
        clearScreen();
        printf("Ingresado como administrador\n");

        printf("\nBienvenido/a!\n");
        printf("Ingrese la opcion que desee realizar o 0 para finalizar.\n");
        printf("1. Administrar usuario/empleado. \n");
        printf("2. Adminnistrar practicas.\n");
        printf("3. Administrar paciente.\n");
        printf("4. Ingresar al sistema con otro perfil.\n");

        fflush(stdin);
        scanf("%i", &eleccion1);
        clearScreen();
        switch(eleccion1)
        {
        case 1:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Dar de alta un empleado.\n");
                printf("2. Modificar un empleado.\n");
                printf("3. Buscar un empleado.\n");
                printf("4. Mostrar todos los empleados.\n");
                printf("5. Dar de baja un empleado.\n");
                printf("0. Volver.\n");
                fflush(stdin);
                scanf("%i", &eleccion2);
                clearScreen();
                switch(eleccion2)
                {
                case 1:
                    *listaEmpleados = alta_de_empleados(*listaEmpleados);
                    break;

                case 2:
                    *listaEmpleados = modificarEmpleado(*listaEmpleados);
                    break;

                case 3:
                    printf("%i", tipoPerfil);
                    buscarUnEmpleadoXdni(*listaEmpleados,tipoPerfil);
                    break;

                case 4:
                    mostrarListaEmpleados(*listaEmpleados,tipoPerfil);
                    break;

                case 5:
                   * listaEmpleados = darDeBajaEmpleado(*listaEmpleados);
                    break;

                default:
                    if(eleccion2!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion2 != 0);
        break;

        case 2:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar o 0 para finalizar: \n");
                printf("1. Agregar una practica.\n");
                printf("2. Modificar una practica.\n");
                printf("3. Buscar una practica.(Puede ingresar iniciales)\n");
                printf("4. Mostrar todas las practicas.\n");
                printf("5. Dar de baja una practica.\n");
                printf("0. Volver.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);
                clearScreen();
                switch(eleccion3)
                {
                case 1:
                    *listaPracticas =  alta_de_practica(*listaPracticas);
                    break;

                case 2:
                    *listaPracticas = modificacion_de_practica(*listaPracticas);
                    break;

                case 3:
                    buscarPractica = mostrarPracticasQueComienzanCon(*listaPracticas);
                    if(buscarPractica == 0)
                    {
                        printf("La practica que desea buscar no existe.\n");
                    }
                    break;

                case 4:
                    do
                    {
                        printf("Mostrar las practicas organizadas por: \n");
                        printf("1. Nombre de Practica \n");
                        printf("2. Nro de Practica.\n");
                        printf("0. Volver.\n");
                        fflush(stdin);
                        scanf("%i", &eleccion4);
                        clearScreen();
                        switch(eleccion4)
                        {
                        case 1:
                            mostrarListaPorNombre(*listaPracticas);
                            break;
                        case 2:
                            mostrarListaPracticasadmin(*listaPracticas);
                            break;
                        default:
                            if(eleccion3!=0)
                            {
                                printf("Error, la opcion que ingreso es invalida.\n");
                            }
                        break;
                        }
                    }while(eleccion4!=0);
                    break;

                case 5:
                    *listaPracticas = baja_de_practicasLaboratorio(*listaPracticas, *arbolPacientes);
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion3 != 0);
            break;
        case 3:
            //Funciones para dar de alta, modificar, dar de baja, buscar y mostrar.
            do
            {
                printf("Ingrese la opcion que desee realizar: \n");
                printf("1. Dar de alta un paciente.\n");
                printf("2. Modificar un paciente.\n");
                printf("3. Buscar un paciente.\n");
                printf("4. Mostrar todos los pacientes.\n");
                printf("5. Dar de baja un paciente.\n");
                printf("0. Volver.\n");
                fflush(stdin);
                scanf("%i", &eleccion3);

                switch(eleccion3)
                {
                case 1:
                    * arbolPacientes = altaArbolPacientes(*arbolPacientes);
                    break;

                case 2:
                    *arbolPacientes = modificacionPacientesArbol(*arbolPacientes);
                    break;

                case 3:
                    do
                    {
                        correcto=0;
                        printf("Ingrese el DNI del paciente que desea buscar: ");
                        fflush(stdin);
                        if(scanf("%i", &dniPacienteAbuscar)!=1)
                        {
                            correcto = 1;
                            printf("Respuesta invalida. Intente nuevamente: \n");
                        }
                    }while(correcto == 1);
                    existe = existePaciente(*arbolPacientes,dniPacienteAbuscar);
                    mostrarUnPaciente(existe->dato);
                    break;

                case 4:
                    mostrarArbolINORDERPaciente(*arbolPacientes);
                    break;

                case 5:
                    *arbolPacientes = darBajaPaciente(*arbolPacientes);
                    break;

                default:
                    if(eleccion3!=0)
                    {
                        printf("Error, la opcion que ingreso es invalida.\n");
                    }
                }
            }while(eleccion3 != 0);
            break;
        case 4:
            do{
            printf("Con que perfil desea entrar al sistema?\n");
            printf("1. Profesional.\n");
            printf("2. Administrativo.\n");
            printf("0. Volver.\n");
            fflush(stdin);
            scanf("%i", &eleccion5);

            switch(eleccion5)
            {
            case 1:
                switchProfesionales(arbolPacientes,listaEmpleados,listaPracticas);
                break;

            case 2:
                switchAdministrativo(arbolPacientes,listaEmpleados,listaPracticas);
                break;
            default:
                if(eleccion5!=0)
                {
                    printf("Error, la opcion que ingreso es invalida.\n");
                }
                break;
            }
            }while(eleccion5!=0);

                break;
            default:
                if(eleccion1!=0)
                {
                    printf("Error, la opcion que ingreso es invalida.\n");
                }
    }
}while(eleccion1!=0);
}

void mostrarUnaPersonaArchivo(empleadosDeLaboratorio aux)
{
    printf("\n-----------------\n");
    printf("DNI: %i\n", aux.dni);
    printf("Apellido y nombre: %s\n",aux.apellidoYnombre);
    printf("Telefono: %s\n", aux.telefono);
    printf("Usuario: %s\n", aux.usuario);
    printf("Clave: %s\n", aux.clave);
    printf("perfil: %s\n", aux.perfil);
    printf("-------------------\n");
}

void mostrarArchivo(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    empleadosDeLaboratorio aux;

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(empleadosDeLaboratorio), 1, archi) == 1)
        {
            printf("\nRegistro en el archivo:\n");
            mostrarUnaPersonaArchivo(aux);
        }
        printf("\nFin del archivo.\n");
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
    }
}

///funciones de vista de datos
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void recuadro (int xs, int ys, int xi, int yi)
{
    int i;
    for(i=xs; i<=xi; i++)
    {
        gotoxy(i,ys); printf("%c", 196);
        gotoxy(i,yi); printf("%c", 196);
    }

    for(i=ys; i<=yi; i++)
    {
        gotoxy(xs,i); printf("%c", 179);
        gotoxy(xi,i); printf("%c", 179);
    }
    gotoxy(xs,ys); printf("%c", 218);
    gotoxy(xi,yi); printf("%c", 217);
    gotoxy(xi,ys); printf("%c", 191);
    gotoxy(xs,yi); printf("%c", 192);
}

void ocultarCursor()
{
    printf("\e[?25l");
}

void activarCursor()
{
    printf("\e[?25h");
}

void centrarTexto(char *texto, int y)
{
    int longitud = strlen(texto);
    gotoxy(56-(longitud/2),y); printf(texto);
}

void marcoEsteticoSwitch(char texto[])
{
    clearScreen();
    mostrarLinea(25);
    printf("%s\n", texto);
    mostrarLinea(25);
}

void mostrarLinea(int cantidad)
{
    for(int i = 0; i < cantidad; i++)
    {
        printf("-");
    }
    printf("\n");
}
