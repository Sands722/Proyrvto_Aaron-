#include "stdafx.h"
#include <string.h>
#include "corrector.h"

/***************************************
    CLONAPALABRAS: Esta función genera las combinaciones y permutaciones necesarias
***************************************/
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
    iNumSugeridas = 0;
    int len = strlen(szPalabraLeida);

    // Generar las palabras sugeridas
    for (int i = 0; i < len; i++) {
        char palabraModificada[TAMTOKEN];

        // Eliminar el carácter en la posición i
        for (int j = 0, k = 0; j < len; j++) {
            if (j != i) {
                palabraModificada[k++] = szPalabraLeida[j];
            }
        }
        palabraModificada[len - 1] = '\0'; // Asegurar terminación

        // Guardar la palabra clonada
        strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, palabraModificada);
        iNumSugeridas++;

        // Verificar si se ha alcanzado el límite de sugerencias
        if (iNumSugeridas >= TAMTOKEN) {
            printf("Se ha alcanzado el límite máximo de palabras sugeridas.\n");
            break;
        }
    }

    // Mensaje final
    printf("Se han generado %d palabras sugeridas.\n", iNumSugeridas);
}
