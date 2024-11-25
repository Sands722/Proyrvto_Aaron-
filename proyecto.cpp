#include "stdafx.h"
#include <string.h>
#include "corrector.h"

/***************************************
    CLONAPALABRAS: Esta funci�n genera las combinaciones y permutaciones necesarias
***************************************/
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
    iNumSugeridas = 0;
    int len = strlen(szPalabraLeida);

    // Generar las palabras sugeridas
    for (int i = 0; i < len; i++) {
        char palabraModificada[TAMTOKEN];

        // Eliminar el car�cter en la posici�n i
        for (int j = 0, k = 0; j < len; j++) {
            if (j != i) {
                palabraModificada[k++] = szPalabraLeida[j];
            }
        }
        palabraModificada[len - 1] = '\0'; // Asegurar terminaci�n

        // Guardar la palabra clonada
        strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, palabraModificada);
        iNumSugeridas++;

        // Verificar si se ha alcanzado el l�mite de sugerencias
        if (iNumSugeridas >= TAMTOKEN) {
            printf("Se ha alcanzado el l�mite m�ximo de palabras sugeridas.\n");
            break;
        }
    }

    // Mensaje final
    printf("Se han generado %d palabras sugeridas.\n", iNumSugeridas);
}
