#include "stdafx.h"
#include <string.h>
#include "corrector.h"

// Prototipos de funciones auxiliares
void InicializarDiccionario(int& iNumElementos, char szPalabras[][TAMTOKEN], int iEstadisticas[]);
int AbrirArchivo(const char* szNombre, FILE** fp);
void ProcesarLinea(char* linea, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos);
void MostrarEstadisticas(const char szPalabras[][TAMTOKEN], const int iEstadisticas[], int iNumElementos);

/***************************************
    DICCIONARIO: Esta función crea el diccionario completo
***************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    FILE* fp = NULL; // Puntero al archivo
    char buffer[300]; // Buffer temporal para leer cada línea del archivo

    // Inicializar el diccionario
    InicializarDiccionario(iNumElementos, szPalabras, iEstadisticas);

    // Intentar abrir el archivo
    if (AbrirArchivo(szNombre, &fp) != 0) {
        return; // Salir si no se puede abrir el archivo
    }

    // Leer línea por línea y procesarlas
    while (fgets(buffer, sizeof(buffer), fp)) {
        ProcesarLinea(buffer, szPalabras, iEstadisticas, iNumElementos);
    }

    // Cerrar el archivo
    fclose(fp);

    // Mostrar estadísticas del diccionario
    MostrarEstadisticas(szPalabras, iEstadisticas, iNumElementos);

    // Mensaje final
    printf("Diccionario cargado con éxito. Total de palabras: %d\n", iNumElementos);
}

/***************************************
    FUNCIONES AUXILIARES
***************************************/

// Inicializar el diccionario con valores por defecto
void InicializarDiccionario(int& iNumElementos, char szPalabras[][TAMTOKEN], int iEstadisticas[]) {
    iNumElementos = 0;
    for (int i = 0; i < TAMTOKEN; i++) {
        szPalabras[i][0] = '\0'; // Vaciar cada entrada del arreglo de palabras
        iEstadisticas[i] = 0;   // Inicializar las estadísticas en cero
    }
}

// Intentar abrir un archivo y verificar errores
int AbrirArchivo(const char* szNombre, FILE** fp) {
    *fp = fopen(szNombre, "r");
    if (*fp == NULL) {
        perror("Error al abrir el archivo");
        return -1; // Retornar error
    }
    printf("Archivo %s abierto con éxito.\n", szNombre);
    return 0; // Archivo abierto correctamente
}

// Procesar una línea y extraer palabras al diccionario
void ProcesarLinea(char* linea, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    // Eliminar saltos de línea y caracteres no deseados
    size_t longitud = strlen(linea);
    if (longitud > 0 && (linea[longitud - 1] == '\n' || linea[longitud - 1] == '\r')) {
        linea[--longitud] = '\0';
    }

    // Tokenizar la línea
    char* token = strtok(linea, " ");
    while (token != NULL) {
        // Verificar si se alcanzó el límite del diccionario
        if (iNumElementos >= TAMTOKEN) {
            printf("Límite del diccionario alcanzado. No se procesarán más palabras.\n");
            return;
        }

        // Agregar la palabra al diccionario
        strncpy(szPalabras[iNumElementos], token, TAMTOKEN - 1);
        szPalabras[iNumElementos][TAMTOKEN - 1] = '\0'; // Asegurar terminación

        // Inicializar estadística de la palabra
        iEstadisticas[iNumElementos] = 1;

        // Incrementar el contador
        iNumElementos++;

        // Continuar con el siguiente token
        token = strtok(NULL, " ");
    }
}

// Mostrar las estadísticas del diccionario cargado
void MostrarEstadisticas(const char szPalabras[][TAMTOKEN], const int iEstadisticas[], int iNumElementos) {
    printf("\n=== Estadísticas del Diccionario ===\n");
    for (int i = 0; i < iNumElementos; i++) {
        printf("Palabra: %-20s | Frecuencia: %d\n", szPalabras[i], iEstadisticas[i]);
    }
    printf("====================================\n");
}
