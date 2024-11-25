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
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#define TAMTOKEN 100 // Tamaño máximo de cada palabra

void Diccionario(const char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    std::ifstream archivo(szNombre); // Archivo de entrada
    std::string linea;               // Línea leída del archivo
    iNumElementos = 0;               // Inicializamos el contador de elementos

    // Verificar si se abrió correctamente el archivo
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << szNombre << ". Verifica la ruta o los permisos.\n";
        return;
    }

    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::istringstream stream(linea); // Crear un flujo para procesar las palabras en la línea
        std::string palabra;

        // Leer palabra por palabra en la línea
        while (stream >> palabra) {
            // Verificar que no exceda el tamaño máximo de elementos
            if (iNumElementos >= TAMTOKEN) {
                std::cerr << "Se ha alcanzado el límite de palabras permitidas en el diccionario.\n";
                archivo.close();
                return;
            }

            // Copiar la palabra al arreglo de palabras
            strncpy(szPalabras[iNumElementos], palabra.c_str(), TAMTOKEN - 1);
            szPalabras[iNumElementos][TAMTOKEN - 1] = '\0'; // Asegurar el fin de cadena

            // Inicializar la estadística de aparición
            iEstadisticas[iNumElementos] = 1;

            // Incrementar el contador de palabras
            iNumElementos++;
        }
    }

    // Cerrar el archivo
    archivo.close();

    // Informar del número de palabras leídas
    std::cout << "Diccionario cargado con " << iNumElementos << " palabras.\n";
}
