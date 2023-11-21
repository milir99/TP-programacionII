#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

///ESTRUCTURAS
typedef struct
{
    int nroIngreso;
    char fechaIngreso[11];
    char fechaRetiro[11];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
} ingresos;

typedef struct nodoIngresos
{
    ingresos dato;
    struct nodoPracticasXIngreso*listaDePracticas;
    struct nodoIngresos*siguiente;
} nodoIngresos;

typedef struct
{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
} practicasXIngreso;

typedef struct nodoPracticasXIngreso
{
    practicasXIngreso dato;
    struct nodoPracticasXIngreso* siguiente;
} nodoPracticasXIngreso;

typedef struct
{
    int nroPractica;
    char nombreDePractica[30];
    int eliminado;
} practicasLaboratorio;

typedef struct nodoPracticasLaboratorio
{
    practicasLaboratorio datos;
    struct nodoPracticasLaboratorio* siguiente;
} nodoPracticasLaboratorio;

typedef struct
{
    int dni;
    char telefono[15];
    char apellidoYnombre[40];
    char usuario[20];
    char clave[20];
    char perfil[20];
} empleadosDeLaboratorio;

typedef struct nodoEmpleados
{
    empleadosDeLaboratorio empleado;
    struct nodoEmpleados *siguiente;
    struct nodoEmpleados *anterior;
} nodoEmpleados;

typedef struct
{
    char apellidoYnombre [40];
    int edad;
    int dni;
    char direccion [30];
    char telefono [15];
    int eliminado;
} paciente;

typedef struct nodoArbolPacientes
{
    paciente dato;
    struct nodoIngresos * listaIngresos;
    struct nodoArbolPacientes*izq;
    struct nodoArbolPacientes*der;
} nodoArbolPacientes;

///FUNCIONES GENERALES
void clearScreen();

//FUNCIONES DE PRACTICA
nodoPracticasLaboratorio*CrearNodoPracticaLaboratorio(practicasLaboratorio dato);
nodoPracticasLaboratorio* agregarFinPracticaLaboratorio(nodoPracticasLaboratorio* listaPractica, nodoPracticasLaboratorio* nuevaPractica);
nodoPracticasLaboratorio* alta_de_practica(nodoPracticasLaboratorio* listaPracticas);
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista);
nodoPracticasLaboratorio* ArchivoAListaPracticas(char archivoPraticas[],nodoPracticasLaboratorio* lista);
void listaPracticaAArchivo(char archivoPraticas[],nodoPracticasLaboratorio* lista);
int proximoNumeroPractica (nodoPracticasLaboratorio* listaPracticas);
void practicaEnIngreso(nodoArbolPacientes* arbolpaciente, int nroPractica,int * existencia);
nodoPracticasLaboratorio* baja_de_practicasLaboratorio(nodoPracticasLaboratorio*listaPracticas,nodoArbolPacientes* arbolPacientes);
int buscarPracticaEnIngreso(nodoIngresos* listaIngreso,int nroPractica);
void mostrarListaPracticas(nodoPracticasLaboratorio* listaPractica);
void mostrarListadoPracticas(nodoPracticasLaboratorio *listaPracticas);
int mostrarPracticasQueComienzanCon(nodoPracticasLaboratorio *listaPracticas);
void mostrarListadoPracticas(nodoPracticasLaboratorio *listaPracticas);

//FUNCIONES DE INGRESO
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes *paciente,ingresos dato,nodoPracticasLaboratorio* listaPracticas);
nodoIngresos*crearNodoIngreso(ingresos dato);
nodoIngresos*agregarPpioIngreso(nodoIngresos*lista,nodoIngresos* nuevoIngreso);
int buscarUltimoNroIngreso(nodoIngresos*lista);
nodoIngresos* buscarIngreso(nodoArbolPacientes* arbol, int nroIngreso);
nodoIngresos*modificacion_de_ingreso(nodoArbolPacientes * arbol, int nroIngreso);
nodoIngresos* baja_de_ingreso(nodoArbolPacientes * arbol, int nroIngreso);
void escribirIngresosEnArchivo(nodoArbolPacientes* arbol, FILE* archivo);
int cargarUnIngreso(nodoArbolPacientes* arbol,ingresos * nuevoIngreso);
void mostrarIngresosConFiltroRecursivo(nodoArbolPacientes* arbol, char fechaDesde[], char fechaHasta[]);
void mostrarUnIngreso(ingresos dato);
void mostrarIngresosConFiltro(nodoArbolPacientes*arbol);
int analizarFecha(char *fechaIngresada);
int esAnterior(const char *fecha_ingreso, const char *fecha_retiro);
nodoArbolPacientes* archivoAListaIngresos(char archivo[],nodoArbolPacientes* arbol);
void listaIngresosAArchivo(nodoArbolPacientes*arbol, char archivoIngresos[]);



//FUNCIONES PRACTICAS X INGRESO
nodoPracticasXIngreso*crearNodoPXI(int nroIngreso,int nroPractica);
nodoPracticasLaboratorio* BuscarPractica(nodoPracticasLaboratorio*lista, char nombrePractica[]);
nodoPracticasXIngreso*agregarPpioPXI (nodoPracticasXIngreso*lista,nodoPracticasXIngreso* nuevoIngreso);
nodoPracticasXIngreso *alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso,nodoPracticasLaboratorio* listaPracticas);
nodoPracticasXIngreso* baja_de_PXI_EnCascada(nodoPracticasXIngreso* lista);
void listaPXIsAArchivo(nodoArbolPacientes*arbol, char archivoIngresos[]);
void escribirPXIEnArchivo(nodoArbolPacientes* arbol, FILE* archivo);
void mostrarUnaPXI(practicasXIngreso dato);
void mostrarListaPXI(nodoPracticasXIngreso* listaPXI);
nodoPracticasXIngreso*BuscarPXIparaModificar( nodoArbolPacientes*arbol,nodoPracticasLaboratorio*listaPracticas);
nodoArbolPacientes* archivoAListaPXI (char archivo[],nodoArbolPacientes*arbol);

nodoArbolPacientes* existePaciente(nodoArbolPacientes* pacientes, int dniPaciente);

//FUNCIONES DE PACIENTES
nodoArbolPacientes * iniciarArbol ();
nodoArbolPacientes *crearNodoArbol (paciente datoP);
nodoArbolPacientes * insertarNodoArbolPaciente (nodoArbolPacientes *arbolPacientes, nodoArbolPacientes* dato);
nodoArbolPacientes * altaArbolPacientes (nodoArbolPacientes *arbolPacientes);
paciente cargarUnPaciente ();
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes);
void cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes);
void cargarArchivoPaciente (char nombreArcPacientes[],nodoArbolPacientes * arbolPacientes);
nodoArbolPacientes * modificacionPacientesArbol (nodoArbolPacientes * arbolPaciente);
nodoArbolPacientes * darBajaPaciente (nodoArbolPacientes* arbolPaciente);
void mostrarArchivoPacientes (char nombreArcPacientes[]);
nodoArbolPacientes* archivoAArbolPacientes(char archivo[],nodoArbolPacientes* arbol);
nodoArbolPacientes *removerNodoPacienteDelArbolPorNombre(nodoArbolPacientes *arbol,  char nombre[]);
nodoArbolPacientes *reubicarNodoEnArbol(nodoArbolPacientes *arbol, nodoArbolPacientes *nodoAReubicar);
void mostrarUnPaciente (paciente nuevoPaciente);
void mostrarListaIngresos(nodoIngresos* listaIngresos);
void mostrarPacienteEIngresos( nodoArbolPacientes*arbol);
void mostrarPacienteDeDNI(nodoArbolPacientes* arbol);
nodoPracticasLaboratorio * inicListaPracticas();


//FUNCIONES EMPLEADOS
nodoEmpleados * iniclistaEmpleados();
nodoEmpleados * crearNodoEmpleados(empleadosDeLaboratorio dato);
nodoEmpleados * existeEmpleado(nodoEmpleados* empleado, int dniEmpleado);
nodoEmpleados * agregarPpioEmpleados (nodoEmpleados * empleados, nodoEmpleados * nuevo);
nodoEmpleados * alta_de_empleados (nodoEmpleados * listaEmpleados);
nodoEmpleados * pasarArchivoAlistaEmpleados(char nombreArchivo[], nodoEmpleados * listaEmpleados);
void pasarListaEmpleadosAarchivo(nodoEmpleados * listaEmpleados, char nombreArchivo[]);
void mostrarUnEmpleado(empleadosDeLaboratorio aux, int tipoperfil);
void mostrarListaEmpleados(nodoEmpleados * listaEmpleados, int tipoperfil);
nodoEmpleados * modificarEmpleado(nodoEmpleados * listaEmpleados);
nodoEmpleados * darDeBajaEmpleado(nodoEmpleados * listaEmpleados);
nodoEmpleados * agregarEnOrdenEmpleados(nodoEmpleados * listaEmpleados, nodoEmpleados * nuevoNodo);
void buscarUnEmpleadoXdni (nodoEmpleados * listaEmpleados, int tipoperfil);
int cargarUnEmpleado(empleadosDeLaboratorio * datos, nodoEmpleados * listaEmpleados);


//SWITCH INGRESOS
void mostrarIngresoXfechaIngreso (nodoArbolPacientes * arbolPaciente, char fechaIngresada[]);
void mostrarIngresoXnumeroIngreso (nodoArbolPacientes * arbolPaciente, int numeroIngreso);
void mostrarIngresoXdni (nodoArbolPacientes * arbolPaciente, int dniIngresado);





#endif // FUNCIONES_H_INCLUDED
