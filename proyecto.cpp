#include "stdafx.h"
#include <string.h>
#include "corrector.h"

/***************************************
    FUNCIONES AUXILIARES
***************************************/

// Funci�n para leer y procesar una l�nea del archivo
void ProcesarLinea(char* linea, char szPalabras[][TAMTOKEN], int iEstadisticas[], int* iNumElementos) {
    char* token = strtok(linea, " \n\r"); // Tokeniza la l�nea por espacios o saltos de l�nea

    while (token != NULL) {
        // Verificar que no se exceda el tama�o m�ximo del diccionario
        if (*iNumElementos >= TAMTOKEN) {
            printf("El diccionario ha alcanzado su l�mite m�ximo de palabras (%d).\n", TAMTOKEN);
            return;
        }

        // Agregar la palabra al arreglo y establecer su estad�stica inicial
        strncpy(szPalabras[*iNumElementos], token, TAMTOKEN - 1);
        szPalabras[*iNumElementos][TAMTOKEN - 1] = '\0'; // Asegurar terminaci�n
        iEstadisticas[*iNumElementos] = 1;

        // Incrementar el contador de elementos
        (*iNumElementos)++;

        // Continuar con el siguiente token
        token = strtok(NULL, " \n\r");
    }
}

// Funci�n para abrir un archivo y verificar errores
FILE* AbrirArchivo(const char* szNombre) {
    FILE* fp = fopen(szNombre, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s. Verifica la ruta y los permisos.\n", szNombre);
    }
    return fp;
}

/***************************************
    DICCIONARIO: Funci�n principal
***************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    char buffer[300]; // Buffer temporal para leer l�neas
    iNumElementos = 0; // Inicializamos el contador

    // Abrir el archivo
    FILE* fp = AbrirArchivo(szNombre);
    if (fp == NULL) {
        return; // Salir si no se pudo abrir el archivo
    }

    // Leer l�nea por l�nea
    while (fgets(buffer, sizeof(buffer), fp)) {
        ProcesarLinea(buffer, szPalabras, iEstadisticas, &iNumElementos);
    }

    // Cerrar el archivo
    fclose(fp);

    // Mostrar el resultado final
    printf("Diccionario cargado con %d palabras.\n", iNumElementos);
}
