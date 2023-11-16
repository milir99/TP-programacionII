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

typedef struct
{
     int nroPractica;
    char nombrePractica[30];
    int eliminado;
} practica;

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
char nombreDePractica;
int eliminado;
}practicasLaboratorio;

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

//FUNCIONES DE INGRESOS
nodoArbolPacientes* alta_de_ingreso(nodoArbolPacientes *paciente,ingresos dato);
nodoIngresos*crearNodoIngreso(ingresos dato);
nodoIngresos*agregarPpioIngreso(nodoIngresos*lista,nodoIngresos* nuevoIngreso);
int buscarUltimoNroIngreso(nodoIngresos*lista);
//FUNCIONES DE PRACTICAS X INGRESO
nodoPracticasXIngreso*crearNodoPXI(int nroIngreso,int nroPractica);
int BuscarPractica(char archivo[], int nroPractica);
nodoPracticasXIngreso*agregarPpioPXI (nodoPracticasXIngreso*lista,nodoPracticasXIngreso* nuevoIngreso);
nodoPracticasXIngreso* alta_de_pxi(nodoPracticasXIngreso*lista,int nroDeIngreso);

nodoArbolPacientes* existePaciente(nodoArbolPacientes* pacientes, int dniPaciente);
//FUNCIONES DE PACIENTES
paciente cargarUnPaciente ();
void mostrarArbolINORDERPaciente (nodoArbolPacientes * arbolPacientes);
void cargarArchivoPacientesDelArbol (FILE * archi, nodoArbolPacientes * arbolPacientes);
nodoEmpleados * crearNodoEmpleados(empleadosDeLaboratorio dato);
nodoEmpleados * existeEmpleado(nodoEmpleados* empleado, int dniEmpleado);
nodoEmpleados * agregarPpioEmpleados (nodoEmpleados * empleados, nodoEmpleados * nuevo);
#endif // FUNCIONES_H_INCLUDED
