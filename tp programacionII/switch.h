#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED

void InicioDelPrograma();
int compararUsuario(char clave[], char usuario[], nodoEmpleados *listaEmpleados,empleadosDeLaboratorio*datoUsuario);
void switchEmpleados(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas);
void switchAdministrativo(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas);
void switchAdmin(nodoEmpleados * listaEmpleados, nodoArbolPacientes * arbolPacientes, nodoPracticasLaboratorio * listaPracticasDeLaboratorio);

void FinDelPrograma(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas);
int usuarioYclavePrincipio(nodoEmpleados*listaEmpleados);
void mostrarArchivo (char nombreArchivo[]);
void mostrarUnaPersonaArchivo(empleadosDeLaboratorio aux);
void gotoxy(int x, int y);

#endif // SWITCH_H_INCLUDED
