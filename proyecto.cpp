#include <stdio.h>
#include <string.h>
#include <errno.h>

#define TAMTOKEN 100

// Función para cargar el diccionario
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int* iNumElementos) {
    FILE* fp = NULL;
    char buffer[300];
    *iNumElementos = 0;

    // Intentar abrir el archivo
    if ((fp = fopen(szNombre, "r")) == NULL) {
        printf("No se pudo abrir el archivo %s. Verifica la ruta o los permisos.\n", szNombre);
        return;
    }

    // Leer cada línea del archivo
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Obtener las palabras de la línea
        char* token = strtok(buffer, " \n\r");
        while (token != NULL) {
            // Asegurarse de que no se exceda el límite de palabras
            if (*iNumElementos >= TAMTOKEN) {
                printf("Se ha alcanzado el límite de palabras permitidas en el diccionario.\n");
                break;
            }

            // Guardar la palabra en el diccionario
            strcpy(szPalabras[*iNumElementos], token);
            iEstadisticas[*iNumElementos] = 1;  // Inicializamos la estadística
            (*iNumElementos)++;

            // Obtener la siguiente palabra
            token = strtok(NULL, " \n\r");
        }
    }

    fclose(fp);
    printf("Diccionario cargado con %d palabras.\n", *iNumElementos);
}

// Función para obtener una lista de palabras sugeridas
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN],
    int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int* iNumLista) {
    *iNumLista = 0;

    // Buscar las palabras sugeridas en el diccionario
    for (int i = 0; i < iNumSugeridas; i++) {
        for (int j = 0; j < iNumElementos; j++) {
            if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
                // Encontrar la palabra en el diccionario
                strcpy(szListaFinal[*iNumLista], szPalabras[j]);
                iPeso[*iNumLista] = iEstadisticas[j];
                (*iNumLista)++;
            }
        }
    }

    // Ordenar las palabras sugeridas por su peso (usando el método de burbuja)
    for (int i = 0; i < *iNumLista - 1; i++) {
        for (int j = i + 1; j < *iNumLista; j++) {
            if (iPeso[i] < iPeso[j]) {
                // Intercambiar las palabras
                char tempPalabra[TAMTOKEN];
                strcpy(tempPalabra, szListaFinal[i]);
                strcpy(szListaFinal[i], szListaFinal[j]);
                strcpy(szListaFinal[j], tempPalabra);

                // Intercambiar los pesos
                int tempPeso = iPeso[i];
                iPeso[i] = iPeso[j];
                iPeso[j] = tempPeso;
            }
        }
    }
}

// Función para generar variaciones de la palabra
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int* iNumSugeridas) {
    *iNumSugeridas = 0;
    int len = strlen(szPalabraLeida);

    // Generar variaciones de la palabra
    for (int i = 0; i < len; i++) {
        char palabraModificada[TAMTOKEN];
        strcpy(palabraModificada, szPalabraLeida);
        memmove(&palabraModificada[i], &palabraModificada[i + 1], len - i);
        strcpy(szPalabrasSugeridas[(*iNumSugeridas)++], palabraModificada);
    }
}

int main() {
    char szPalabras[100][TAMTOKEN];
    int iEstadisticas[100];
    int iNumElementos;

    // Cargar el diccionario
    Diccionario("diccionario.txt", szPalabras, iEstadisticas, &iNumElementos);

    char palabra[] = "casa";
    char szPalabrasSugeridas[100][TAMTOKEN];
    int iNumSugeridas;

    // Clonar la palabra
    ClonaPalabras(palabra, szPalabrasSugeridas, &iNumSugeridas);

    char szListaFinal[100][TAMTOKEN];
    int iPeso[100];
    int iNumLista;

    // Obtener las palabras sugeridas
    ListaCandidatas(szPalabrasSugeridas, iNumSugeridas, szPalabras, iEstadisticas, iNumElementos, szListaFinal, iPeso, &iNumLista);

    // Imprimir las sugerencias
    printf("Palabras sugeridas:\n");
    for (int i = 0; i < iNumLista; i++) {
        printf("%s (Peso: %d)\n", szListaFinal[i], iPeso[i]);
    }

    return 0;
}
