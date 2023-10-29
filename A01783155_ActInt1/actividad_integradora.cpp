/*

Compilar: g++ -std=c++11 -o prueba_1 actividad_integradora.cpp
Ejecutar: ./prueba_1

    Autores>
        David Medina Domínguez (A01783155)
        Luis Rico Almada (A01252831)
        Arantza Parra Matrínez (A01782023)
    Fecha> 31/10/2023
    Abstract>

    Instrucciones>
            Los archivos contendran exclusivamente caracteres del 0 al 9, caracteres entre A y F y saltos de línea.
    Parte #1:
        El programa debe analizar si el contenido de los archivos mcode1.txt, mcode2.txt y mcode3.txt, están contenidos en
        los archivos transmission1.txt y transmission2.txt y desplegar un true o false si es que las secuencias de chars
        están contenidas o no. En caso de ser true, muestra true, seguido de exactamente un espacio, seguido de la posición
        en el archivo de transmissiónX.txt donde inicia el código de mcodeY.txt
    Parte #2:
        Suponiendo que el código malicioso tiene código "espejeado" (palíndromos de chars), buscar en las transmisiónes
        (palíndromo a nivel chars, no meterse a nivel bits). El programa muestra en una sola linea dos enteros separados por
        un espacio correspondientes a la posición (iniciando en 1) en donde inicia y termina el código "espejeado" más largo.
    Parte #3:
        Finalmente el programa analiza que tan similares son los archivos de transmisión, y debe mostrar la posición inicial
        y la posición final (iniciando en 1) del primer archivo en donde se encuentra el substring más largo común entre
        ambos archivos de transmisión

*/

// todo:

// Búsqueda de subsecuencias

// 1. Analizar si el contenido de los archivos mcode está presente en los archivos transmission. Se lee el contenido de los archivos, pero no hay implementación que verifique si una subsecuencia (mcode) está en las transmisiones.
// 2. Mostrar resultados. No se muestra ningún resultado relacionado con la búsqueda de subsecuencias.

// Palíndromos en las secuencias de transmisión

// 1. Mostrar en una sola línea dos enteros. Aunque el algoritmo de Manacher's está implementado, no hay código que muestre la posición donde comienza y termina el palíndromo más largo para cada archivo de transmisión.

// Substring más largo común

// 1. Encontrar el substring más largo común. No hay implementación que aborde la búsqueda del substring común más largo entre los dos archivos de transmisión.
// 2. Mostrar la posición inicial y final del substring común más largo. No hay implementación que aborde este requerimiento.

// Implementar propio sort para ordenar los sufijos.

// Agregar más comentarios al código.

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

std::string readTXT(std::string test)
{
    std::string line;
    std::string content;
    std::ifstream file(test);

    if (file.is_open())
    {
        while (getline(file, line)) // por cada linea
        {
            std::cout << line << std::endl;
            content += line + "\n"; // concatenar la line y una nueva (\n)
        }
        file.close(); // cerrar el archivo
    }
    else
        std::cout << "Unable to open file";

    return content;
}

// Knuth-Morris-Pratt (KMP)
std::vector<int> calcularTablaPrefijoSufijo(const std::string &patron)
{
    int longitud = patron.length();
    std::vector<int> lps(longitud, 0);
    int longitudActual = 0;
    int indice = 1;

    while (indice < longitud)
    {
        if (patron[indice] == patron[longitudActual])
        {
            longitudActual++;
            lps[indice] = longitudActual;
            indice++;
        }
        else
        {
            if (longitudActual != 0)
            {
                longitudActual = lps[longitudActual - 1];
            }
            else
            {
                lps[indice] = 0;
                indice++;
            }
        }
    }
    return lps;
}

int buscarSubsecuenciaKMP(const std::string &texto, const std::string &patron)
{
    int longitudTexto = texto.length();
    int longitudPatron = patron.length();

    if (longitudPatron > longitudTexto)
        return -1; // el patron no puede ser mas largo que el texto

    std::vector<int> lps = calcularTablaPrefijoSufijo(patron);
    int j = 0; // indice para el patrón

    for (int i = 0; i < longitudTexto; i++)
    {
        while (j > 0 && texto[i] != patron[j])
        {
            j = lps[j - 1];
        }

        if (texto[i] == patron[j])
        {
            j++;
        }

        if (j == longitudPatron)
        {
            return i - (longitudPatron - 1); // retorna la posicion inicial donde comienza el patron en el texto
        }
    }

    return -1; // no encontrado
}

// Manacher's
std::string encontrarPalindromoMasLargoManacher(const std::string &texto)
{
    if (texto.empty())
        return "";

    std::string transformado = "^#";
    for (int i = 0; i < texto.size(); i++)
    {
        transformado += texto[i];
        transformado += "#";
    }
    transformado += "$";

    int longitudTotal = transformado.length();
    std::vector<int> palindromos(longitudTotal, 0);

    int centro = 0, derecha = 0;
    for (int i = 1; i < longitudTotal - 1; i++)
    {
        int reflejo = 2 * centro - i; // eje de simetría

        if (i < derecha)
            palindromos[i] = std::min(derecha - i, palindromos[reflejo]);

        while (transformado[i + 1 + palindromos[i]] == transformado[i - 1 - palindromos[i]])
            palindromos[i]++;

        if (i + palindromos[i] > derecha)
        {
            centro = i;
            derecha = i + palindromos[i];
        }
    }

    int longitudMax = 0;
    int centroMax = 0;
    for (int i = 1; i < longitudTotal - 1; i++)
    {
        if (palindromos[i] > longitudMax)
        {
            longitudMax = palindromos[i];
            centroMax = i;
        }
    }

    return texto.substr((centroMax - 1 - longitudMax) / 2, longitudMax);
}

// Arreglo de Sufijos
std::vector<int> construirArregloSufijos(const std::string &texto)
{
    int longitud = texto.length();
    std::vector<std::pair<std::string, int>> sufijos(longitud);

    for (int i = 0; i < longitud; i++)
    {
        sufijos[i] = {texto.substr(i), i};
    }

    std::sort(sufijos.begin(), sufijos.end()); // todo: implementar propio sort

    std::vector<int> arregloSufijos(longitud);
    for (int i = 0; i < longitud; i++)
        arregloSufijos[i] = sufijos[i].second;

    return arregloSufijos;
}

int main(int argc, char const *argv[])
{
    std::string transmision1 = readTXT("transmission1.txt");
    std::string transmision2 = readTXT("transmission2.txt");
    std::string mcode1 = readTXT("mcode1.txt");
    std::string mcode2 = readTXT("mcode2.txt");
    std::string mcode3 = readTXT("mcode3.txt");

    // busqueda de mcode1 en las transmisiones
    int posicionMcode1EnTransmision1 = buscarSubsecuenciaKMP(transmision1, mcode1);
    int posicionMcode1EnTransmision2 = buscarSubsecuenciaKMP(transmision2, mcode1);

    std::cout << "¿Está mcode1 en transmisión 1? " << (posicionMcode1EnTransmision1 != -1 ? "Sí, comienza en la posición " + std::to_string(posicionMcode1EnTransmision1) : "No") << std::endl;
    std::cout << "¿Está mcode1 en transmisión 2? " << (posicionMcode1EnTransmision2 != -1 ? "Sí, comienza en la posición " + std::to_string(posicionMcode1EnTransmision2) : "No") << std::endl;

    // busqueda de mcode2 en las transmisiones
    int posicionMcode2EnTransmision1 = buscarSubsecuenciaKMP(transmision1, mcode2);
    int posicionMcode2EnTransmision2 = buscarSubsecuenciaKMP(transmision2, mcode2);

    std::cout << "¿Está mcode2 en transmisión 1? " << (posicionMcode2EnTransmision1 != -1 ? "Sí, comienza en la posición " + std::to_string(posicionMcode2EnTransmision1) : "No") << std::endl;
    std::cout << "¿Está mcode2 en transmisión 2? " << (posicionMcode2EnTransmision2 != -1 ? "Sí, comienza en la posición " + std::to_string(posicionMcode2EnTransmision2) : "No") << std::endl;

    // busqueda de mcode3 en las transmisiones
    int posicionMcode3EnTransmision1 = buscarSubsecuenciaKMP(transmision1, mcode3);
    int posicionMcode3EnTransmision2 = buscarSubsecuenciaKMP(transmision2, mcode3);

    std::cout << "¿Está mcode3 en transmisión 1? " << (posicionMcode3EnTransmision1 != -1 ? "Sí, comienza en la posición " + std::to_string(posicionMcode3EnTransmision1) : "No") << std::endl;
    std::cout << "¿Está mcode3 en transmisión 2? " << (posicionMcode3EnTransmision2 != -1 ? "Sí, comienza en la posición " + std::to_string(posicionMcode3EnTransmision2) : "No") << std::endl;

    return 0;
}