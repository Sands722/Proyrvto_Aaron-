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
