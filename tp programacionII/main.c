#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <ctype.h>
#include <string.h>
#include <time.h>


int main()
{ /*/para cuando ingrese fechas
  char fechaIngresada[20];

    do {
        printf("Ingresa una fecha (YYYY-MM-DD): ");
        if (scanf("%19s", fechaIngresada) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }
    } while (!analizarFecha(fechaIngresada));/*/

    return 0;
}

