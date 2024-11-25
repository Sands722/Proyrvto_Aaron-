#include "stdafx.h"
#include <string.h>
#include "corrector.h"

// Prototipos de funciones auxiliares
void InicializarSugeridas(int& iNumSugeridas, char szPalabrasSugeridas[][TAMTOKEN]);
void ClonarPalabra(char* szPalabraLeida, char* szPalabraClonada, int indice);
void GenerarSugeridas(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas);

/***************************************
    CLONAPALABRAS: Esta funci�n genera las combinaciones y permutaciones necesarias
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

// Clona una palabra eliminando el car�cter en el �ndice indicado
void ClonarPalabra(char* szPalabraLeida, char* szPalabraClonada, int indice) {
    int len = strlen(szPalabraLeida);
    int j = 0;

    // Copiar los caracteres antes del �ndice
    for (int i = 0; i < len; i++) {
        if (i != indice) {
            szPalabraClonada[j++] = szPalabraLeida[i];
        }
    }
    szPalabraClonada[j] = '\0'; // Asegurar que la palabra clonada est� terminada correctamente
}

// Genera las palabras sugeridas a partir de la palabra le�da
void GenerarSugeridas(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
    // Recorrer cada �ndice de la palabra original y generar la clonaci�n
    for (int i = 0; i < strlen(szPalabraLeida); i++) {
        char palabraClonada[TAMTOKEN];
        ClonarPalabra(szPalabraLeida, palabraClonada, i);

        // Guardar la palabra clonada en el arreglo de sugeridas
        strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, palabraClonada);
        iNumSugeridas++; // Incrementar el n�mero de palabras sugeridas

        // Verificar si se alcanz� el l�mite de sugerencias
        if (iNumSugeridas >= TAMTOKEN) {
            printf("Se ha alcanzado el l�mite m�ximo de palabras sugeridas.\n");
            break;
        }
    }
}
