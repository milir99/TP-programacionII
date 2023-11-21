#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED

void InicioDelPrograma();
int compararUsuario(char clave[], char usuario[], nodoEmpleados *listaEmpleados,empleadosDeLaboratorio*datoUsuario);
void switchProfesionales(nodoArbolPacientes **arbolPaciente,nodoEmpleados**listaEmpleados,nodoPracticasLaboratorio**listaPracticas);
void switchAdministrativo(nodoArbolPacientes ** arbolPaciente,nodoEmpleados**listaEmpleados,nodoPracticasLaboratorio**listaPracticas);
void switchAdmin(nodoArbolPacientes ** arbolPacientes, nodoEmpleados ** listaEmpleados, nodoPracticasLaboratorio ** listaPracticas);

void FinDelPrograma(nodoArbolPacientes * arbolPaciente,nodoEmpleados*listaEmpleados,nodoPracticasLaboratorio*listaPracticas);
int usuarioYclavePrincipio(nodoEmpleados*listaEmpleados);
void mostrarArchivo (char nombreArchivo[]);
void mostrarUnaPersonaArchivo(empleadosDeLaboratorio aux);
void gotoxy(int x, int y);
void recuadro (int xs, int ys, int xi, int yi);
void mostrarLinea(int cantidad);
void marcoEsteticoSwitch(char texto[]);
void centrarTexto(char *texto, int y);

void activarCursor();
void ocultarCursor();
void recuadro (int xs, int ys, int xi, int yi);
#endif // SWITCH_H_INCLUDED
