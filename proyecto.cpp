/***************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) Ponga su nombre y numero de cuenta aqui.

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

**************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/***************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
**************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fp = nullptr; // Puntero al archivo
	char buffer[300];   // Buffer temporal para leer l�neas del archivo
	iNumElementos = 0;  // Inicializamos el contador de elementos

	// Abrir el archivo en modo lectura
	errno_t err = fopen_s(&fp, szNombre, "r");
	if (err != 0 || fp == nullptr) {
		printf("No se pudo abrir el archivo %s. Verifica la ruta o los permisos.\n", szNombre);
		return;
	}

	// Leer el archivo l�nea por l�nea
	while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
		// Procesar cada palabra en la l�nea
		char* token = strtok(buffer, " \n\r"); // Separar palabras por espacios o saltos de l�nea
		while (token != nullptr) {
			// Verificar que no exceda el tama�o m�ximo de elementos
			if (iNumElementos >= TAMTOKEN) {
				printf("Se ha alcanzado el l�mite de palabras permitidas en el diccionario.\n");
				break;
			}

			// Copiar la palabra al arreglo de palabras
			strcpy_s(szPalabras[iNumElementos], TAMTOKEN, token);

			// Inicializar la estad�stica de aparici�n
			iEstadisticas[iNumElementos] = 1;

			// Incrementar el contador de palabras
			iNumElementos++;

			// Obtener el siguiente token
			token = strtok(nullptr, " \n\r");
		}
	}

	// Cerrar el archivo
	fclose(fp);

	// Informar del n�mero de palabras le�das
	printf("Diccionario cargado con %d palabras.\n", iNumElementos);
}