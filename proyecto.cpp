#include "stdafx.h"
#include <string.h>
#include "corrector.h"

// Prototipos de funciones auxiliares
int AbrirArchivo(const char* szNombre, FILE** fp);
void ProcesarLinea(char* linea, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos);

/***************************************
    DICCIONARIO: Esta función crea el diccionario completo
***************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    FILE* fp = NULL; // Puntero al archivo
    char buffer[300]; // Buffer temporal para leer cada línea del archivo

    // Inicializar el diccionario
    iNumElementos = 0;
    for (int i = 0; i < TAMTOKEN; i++) {
        szPalabras[i][0] = '\0'; // Vaciar cada entrada del arreglo de palabras
        iEstadisticas[i] = 0;   // Inicializar las estadísticas en cero
    }

    // Intentar abrir el archivo
    if (AbrirArchivo(szNombre, &fp) != 0) return; // Salir si no se puede abrir el archivo

    // Leer y procesar cada línea
    while (fgets(buffer, sizeof(buffer), fp)) {
        // Eliminar saltos de línea y tokenizar
        size_t len = strlen(buffer);
        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) buffer[--len] = '\0';
        char* token = strtok(buffer, " ");
        while (token != NULL) {
            if (iNumElementos >= TAMTOKEN) {
                printf("Límite del diccionario alcanzado.\n");
                fclose(fp);
                return;
            }
            strncpy(szPalabras[iNumElementos], token, TAMTOKEN - 1);
            szPalabras[iNumElementos][TAMTOKEN - 1] = '\0';
            iEstadisticas[iNumElementos] = 1;
            iNumElementos++;
            token = strtok(NULL, " ");
        }
    }

    // Cerrar archivo
    fclose(fp);

    // Mostrar estadísticas del diccionario
    printf("\n=== Estadísticas del Diccionario ===\n");
    for (int i = 0; i < iNumElementos; i++) {
        printf("Palabra: %-20s | Frecuencia: %d\n", szPalabras[i], iEstadisticas[i]);
    }
    printf("====================================\n");

    // Mensaje final
    printf("Diccionario cargado con éxito. Total de palabras: %d\n", iNumElementos);
}

/***************************************
    FUNCIONES AUXILIARES
***************************************/

// Intentar abrir un archivo y verificar errores
int AbrirArchivo(const char* szNombre, FILE** fp) {
    *fp = fopen(szNombre, "r");
    if (*fp == NULL) {
        perror("Error al abrir el archivo");
        return -1; // Retornar error
    }
    return 0; // Archivo abierto correctamente
}
