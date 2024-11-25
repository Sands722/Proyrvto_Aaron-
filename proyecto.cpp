ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
Regresa las palabras ordenadas por su peso
char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
int		iNumSugeridas,						//Lista de palabras clonadas
char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
int		iEstadisticas[],					//Lista de las frecuencias de las palabras
int		iNumElementos,						//Numero de elementos en el diccionario
char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
int		iPeso[],							//Peso de las palabras en la lista final
int& iNumLista)							//Numero de elementos en la szListaFinal
************************************** /
void ListaCandidatas(
char szPalabrasSugeridas[][TAMTOKEN],
int iNumSugeridas,
char szPalabras[][TAMTOKEN],
int iEstadisticas[],
int iNumElementos,
char szListaFinal[][TAMTOKEN],
int iPeso[],
int& iNumLista)
{
	iNumLista = 0; // Inicializamos el contador de la lista final

	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				// Palabra encontrada en el diccionario
				strcpy_s(szListaFinal[iNumLista], szPalabras[j]);
				iPeso[iNumLista] = iEstadisticas[j];
				iNumLista++;
			}
		}
	}

	// Ordenar szListaFinal por peso (burbuja por simplicidad)
	for (int i = 0; i < iNumLista - 1; i++) {
		for (int j = i + 1; j < iNumLista; j++) {
			if (iPeso[i] < iPeso[j]) {
				// Intercambiar palabras
				char tempPalabra[TAMTOKEN];
				strcpy_s(tempPalabra, szListaFinal[i]);
				strcpy_s(szListaFinal[i], szListaFinal[j]);
				strcpy_s(szListaFinal[j], tempPalabra);

				// Intercambiar pesos
				int tempPeso = iPeso[i];
				iPeso[i] = iPeso[j];
				iPeso[j] = tempPeso;
			}
		}
	}
}