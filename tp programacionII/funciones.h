#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

///ESTRUCTURAS
typedef struct
{
    int nroIngreso;
    char fechaIngreso[10];
    char fechaRetiro[10];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
}ingresos;

typedef struct nodoIngresos
{
    ingresos dato;
    struct nodoPracticasXIngreso*listaDePracticas;
    struct nodoIngresos*siguiente;
}nodoIngresos;

typedef struct {
    int nroIngreso;
    int nroPractica;
    char resultado[40];
}practicasXIngreso;

typedef struct nodoPracticasXIngreso{
    practicasXIngreso dato;
    struct nodoPracticasXIngreso* siguiente;
}nodoPracticasXIngreso;

typedef struct{
int nroPractica;
char nombreDePractica[30];
int eliminado;
}practicasLaboratorio;

typedef struct nodoPracticasLaboratorio{
practicasLaboratorio datos;
struct nodoPracticasLaboratorio* siguiente;
}nodoPracticasLaboratorio;

typedef struct
{
    int dni;
    int telefono;
    char apellidoYNombre[40];
    char usuario[20];
    char clave[20];
    char perfil[20];
}empleadosDeLaboratorio;

typedef struct nodoEmpleados
{
    empleadosDeLaboratorio empleado;
    struct nodoEmpleados *siguiente;
    struct nodoEmpleados *anterior;
}nodoEmpleados;

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

//FUNCIONES DE PRATICA
nodoPracticasLaboratorio*CrearNodoPracticaLaboratorio(practicasLaboratorio dato);
nodoPracticasLaboratorio*agregarPpioPracticaLaboratorio(nodoPracticasLaboratorio*lista,nodoPracticasLaboratorio* nuevaPractica);
nodoPracticasLaboratorio* alta_de_practica(practicasLaboratorio dato , nodoPracticasLaboratorio* lista);
nodoPracticasLaboratorio* modificacion_de_practica(nodoPracticasLaboratorio* lista);
nodoPracticasLaboratorio* ArchivoAListaPracticas(char archivoPraticas[],nodoPracticasLaboratorio* lista);
void listaPracticaAArchivo(char archivoPraticas[],nodoPracticasLaboratorio* lista);
nodoPracticasLaboratorio* ArchivoAListaPracticas(char archivoPraticas[],nodoPracticasLaboratorio* lista);


//FUNCIONES DE INGRESO
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes *paciente,ingresos dato);
nodoIngresos*crearNodoIngreso(ingresos dato);
nodoIngresos*agregarPpioIngreso(nodoIngresos*lista,nodoIngresos* nuevoIngreso);
int buscarUltimoNroIngreso(nodoIngresos*lista);
nodoIngresos* buscarIngreso(nodoIngresos* lista, int nroIngreso);
nodoIngresos*modificacion_de_ingreso(nodoIngresos* lista, int nroIngreso);
nodoIngresos* baja_de_ingreso(nodoIngresos* lista, int nroIngreso);
void escribirIngresosEnArchivo(nodoArbolPacientes* arbol, FILE* archivo);



//FUNCIONES PRACTICAS X INGRESO
nodoPracticasXIngreso*crearNodoPXI(int nroIngreso,int nroPractica);
nodoPracticasLaboratorio* BuscarPractica(nodoPracticasLaboratorio*lista, char nombrePractica[]);
nodoPracticasXIngreso*agregarPpioPXI (nodoPracticasXIngreso*lista,nodoPracticasXIngreso* nuevoIngreso);
nodoPracticasXIngreso* alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso);
nodoPracticasXIngreso* baja_de_PXI_EnCascada(nodoPracticasXIngreso* lista);
void listaPXIsAArchivo(nodoArbolPacientes*arbol, char archivoIngresos[]);
void escribirPXIEnArchivo(nodoArbolPacientes* arbol, FILE* archivo);


nodoArbolPacientes* existePaciente(nodoArbolPacientes* pacientes, int dniPaciente);

//FUNCIONES DE PACIENTES
nodoArbolPacientes * iniciarArbol ();
nodoArbolPacientes *crearNodoArbol (paciente datoP);
nodoArbolPacientes * insertarNodoArbolPaciente (nodoArbolPacientes *arbolPacientes, paciente dato);
nodoArbolPacientes * altaArbolPacientes (nodoArbolPacientes *arbolPacientes);
paciente cargarUnPaciente ();
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes);
void cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes);
void cargarArchivoPaciente (char nombreArcPacientes[],nodoArbolPacientes * arbolPacientes);
void cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes);
nodoArbolPacientes * modificacionPacientesArbol (nodoArbolPacientes * arbolPaciente);
nodoArbolPacientes * darBajaPaciente (nodoArbolPacientes* arbolPaciente);
nodoArbolPacientes * borrarNodoPaciente(nodoArbolPacientes* arbolPaciente, char nombreYapellido[]);
nodoArbolPacientes * NMD(nodoArbolPacientes * arbolPaciente);
nodoArbolPacientes* NMI(nodoArbolPacientes* arbolPaciente);



//FUNCIONES EMPLEADOS
nodoEmpleados * crearNodoEmpleados(empleadosDeLaboratorio dato);
nodoEmpleados * existeEmpleado(nodoEmpleados* empleado, int dniEmpleado);
nodoEmpleados * agregarPpioEmpleados (nodoEmpleados * empleados, nodoEmpleados * nuevo);

nodoPracticasLaboratorio * listaPracticas;
#endif // FUNCIONES_H_INCLUDED
