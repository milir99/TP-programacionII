#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
typedef struct nodoIngresos
{
int nroIngreso;
char fechaIngreso[10];
char fechaRetiro[10];
int dniPaciente;
int matriculaProfesional;
int eliminado;
struct nodoPracticasXIngreso*listaDePracticas;
struct nodoIngresos*siguiente;

}nodoIngresos;
typedef struct
{
     int nroPractica;
    char nombrePractica[30];
    int eliminado;
} Practica;
typedef struct nodoPracticasXIngreso{
 int nroIngreso;
 int nroPractica;
 char resultado[40];
struct nodoPracticasXIngreso* siguiente;
}nodoPracticasXIngreso;

typedef struct{
int nroPractica;
char nombreDePractica;
int eliminado;
}practicasLaboratorio;
typedef struct nodoPaciente
{ char apellidoYNombre[40];
  int edad;
  int dni;
  char direccion [30];
  char telefono[30];
  int eliminado;
  struct nodoIngresos* listaIngresos;
  struct nodoPaciente* izquierda;
  struct nodoPaciente * derecha;
} nodoPaciente;
typedef struct
{
    int dni;
    char apellidoYNombre[40];
    char usuario[20];
    char clave[20];
    char perfil[20];
}empleadosDeLaboratorio;



//Funciones INGRESOS
nodoPaciente * alta_de_ingreso(nodoPaciente *paciente,char fechaIngreso[] ,char fechaRetiro[],int dniPaciente,int matriculaProfesional, int eliminado);
nodoIngresos*agregarPpioIngreso(nodoIngresos*lista,nodoIngresos* nuevoIngreso);
nodoPaciente* existePaciente(nodoPaciente* pacientes, int dniPaciente);
nodoIngresos*crearNodoIngreso(int nroIngreso,char fechaIngreso[] ,char fechaRetiro[],int dniPaciente,int matriculaProfesional, int eliminado);
#endif // FUNCIONES_H_INCLUDED
