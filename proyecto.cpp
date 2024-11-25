ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
**************************************/
// Función ClonaPalabras
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
	iNumSugeridas = 0;
	for (int i = 0; i < strlen(szPalabraLeida); i++) {
		char palabraModificada[TAMTOKEN];
		strcpy_s(palabraModificada, TAMTOKEN, szPalabraLeida);
		memmove(&palabraModificada[i], &palabraModificada[i + 1], strlen(szPalabraLeida) - i);
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, palabraModificada);
	}
}