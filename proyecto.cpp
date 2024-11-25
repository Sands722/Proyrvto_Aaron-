#include "stdafx.h"
#include <string.h>
#include "corrector.h"

/***************************************
    FUNCIONES AUXILIARES
***************************************/

// Función para leer y procesar una línea del archivo
void ProcesarLinea(char* linea, char szPalabras[][TAMTOKEN], int iEstadisticas[], int* iNumElementos) {
    char* token = strtok(linea, " \n\r"); // Tokeniza la línea por espacios o saltos de línea

    while (token != NULL) {
        // Verificar que no se exceda el tamaño máximo del diccionario
        if (*iNumElementos >= TAMTOKEN) {
            printf("El diccionario ha alcanzado su límite máximo de palabras (%d).\n", TAMTOKEN);
            return;
        }

        // Agregar la palabra al arreglo y establecer su estadística inicial
        strncpy(szPalabras[*iNumElementos], token, TAMTOKEN - 1);
        szPalabras[*iNumElementos][TAMTOKEN - 1] = '\0'; // Asegurar terminación
        iEstadisticas[*iNumElementos] = 1;

        // Incrementar el contador de elementos
        (*iNumElementos)++;

        // Continuar con el siguiente token
        token = strtok(NULL, " \n\r");
    }
}

// Función para abrir un archivo y verificar errores
FILE* AbrirArchivo(const char* szNombre) {
    FILE* fp = fopen(szNombre, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s. Verifica la ruta y los permisos.\n", szNombre);
    }
    return fp;
}

/***************************************
    DICCIONARIO: Función principal
***************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    char buffer[300]; // Buffer temporal para leer líneas
    iNumElementos = 0; // Inicializamos el contador

    // Abrir el archivo
    FILE* fp = AbrirArchivo(szNombre);
    if (fp == NULL) {
        return; // Salir si no se pudo abrir el archivo
    }

    // Leer línea por línea
    while (fgets(buffer, sizeof(buffer), fp)) {
        ProcesarLinea(buffer, szPalabras, iEstadisticas, &iNumElementos);
    }

    // Cerrar el archivo
    fclose(fp);

    // Mostrar el resultado final
    printf("Diccionario cargado con %d palabras.\n", iNumElementos);
}
