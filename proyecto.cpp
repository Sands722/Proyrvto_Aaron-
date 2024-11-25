#include "stdafx.h"
#include <string.h>
#include "corrector.h"

// Prototipos de funciones auxiliares
void InicializarSugeridas(int& iNumSugeridas, char szPalabrasSugeridas[][TAMTOKEN]);
void ClonarPalabra(char* szPalabraLeida, char* szPalabraClonada, int indice);
void GenerarSugeridas(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas);

/***************************************
    CLONAPALABRAS: Esta función genera las combinaciones y permutaciones necesarias
***************************************/
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
    // Inicializar la lista de palabras sugeridas
    InicializarSugeridas(iNumSugeridas, szPalabrasSugeridas);

    // Generar las combinaciones de palabras sugeridas
    GenerarSugeridas(szPalabraLeida, szPalabrasSugeridas, iNumSugeridas);

    // Mensaje final
    printf("Se han generado %d palabras sugeridas.\n", iNumSugeridas);
}

/***************************************
    FUNCIONES AUXILIARES
***************************************/

// Inicializa el contador de palabras sugeridas
void InicializarSugeridas(int& iNumSugeridas, char szPalabrasSugeridas[][TAMTOKEN]) {
    iNumSugeridas = 0; // No hay palabras sugeridas inicialmente
}

// Clona una palabra eliminando el carácter en el índice indicado
void ClonarPalabra(char* szPalabraLeida, char* szPalabraClonada, int indice) {
    int len = strlen(szPalabraLeida);
    int j = 0;

    // Copiar los caracteres antes del índice
    for (int i = 0; i < len; i++) {
        if (i != indice) {
            szPalabraClonada[j++] = szPalabraLeida[i];
        }
    }
    szPalabraClonada[j] = '\0'; // Asegurar que la palabra clonada esté terminada correctamente
}

// Genera las palabras sugeridas a partir de la palabra leída
void GenerarSugeridas(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
    // Recorrer cada índice de la palabra original y generar la clonación
    for (int i = 0; i < strlen(szPalabraLeida); i++) {
        char palabraClonada[TAMTOKEN];
        ClonarPalabra(szPalabraLeida, palabraClonada, i);

        // Guardar la palabra clonada en el arreglo de sugeridas
        strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, palabraClonada);
        iNumSugeridas++; // Incrementar el número de palabras sugeridas

        // Verificar si se alcanzó el límite de sugerencias
        if (iNumSugeridas >= TAMTOKEN) {
            printf("Se ha alcanzado el límite máximo de palabras sugeridas.\n");
            break;
        }
    }
}
