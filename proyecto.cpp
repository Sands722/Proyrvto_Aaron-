/***************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) Ponga su nombre y numero de cuenta aqui.

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

**************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/***************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
#include "stdafx.h"
#include <string.h>
#include "corrector.h"

/***************************************
    DICCIONARIO: Esta función crea el diccionario completo
    char *	szNombre				:	Nombre del archivo de donde se sacarán las palabras del diccionario
    char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
    int		iEstadisticas[]			:	Arreglo con el número de veces que aparecen las palabras en el diccionario
    int &	iNumElementos			:	Número de elementos en el diccionario
**************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    FILE* fp = NULL; // Puntero al archivo
    char buffer[300]; // Buffer temporal para leer líneas
    iNumElementos = 0; // Inicializamos el contador

    // Intentar abrir el archivo
    fp = fopen(szNombre, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s. Verifica que el archivo existe y tiene los permisos correctos.\n", szNombre);
        return;
    }

    // Leer línea por línea
    while (fgets(buffer, sizeof(buffer), fp)) {
        // Tokenizar el contenido de la línea
        char* token = strtok(buffer, " \n\r");
        while (token != NULL) {
            // Evitar exceder el límite del diccionario
            if (iNumElementos >= TAMTOKEN) {
                printf("El diccionario ha alcanzado el límite de %d palabras.\n", TAMTOKEN);
                break;
            }

            // Guardar la palabra en el arreglo
            strncpy(szPalabras[iNumElementos], token, TAMTOKEN - 1);
            szPalabras[iNumElementos][TAMTOKEN - 1] = '\0'; // Asegurar terminación

            // Inicializar el contador de estadísticas
            iEstadisticas[iNumElementos] = 1;

            // Incrementar el contador
            iNumElementos++;

            // Continuar con el siguiente token
            token = strtok(NULL, " \n\r");
        }
    }

    // Cerrar el archivo
    fclose(fp);

    // Reportar resultados
    printf("Diccionario cargado con %d palabras.\n", iNumElementos);
}
