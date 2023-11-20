#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED

int compararUsuario (char clave[], char usuario[], nodoEmpleados * listaEmpleados);
void switchAdmin();
void switchAdministrador();
void switchEmpleados(nodoArbolPacientes** arbolPacientes);
void InicioDelPrograma();
void FinDelPrograma(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas);
int usuarioYclavePrincipio(nodoEmpleados*listaEmpleados);
void mostrarArchivo (char nombreArchivo[]);
void mostrarUnaPersonaArchivo(empleadosDeLaboratorio aux);

#endif // SWITCH_H_INCLUDED
