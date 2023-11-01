/*
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

#include <iostream>
#include <sstream>
#include <fstream> // Stringstream library
#include <string>
#include <vector>
#include <algorithm>


std::string readTXT(std::string test /*std::string test = "mcode1.txt"*/)
{
    std::string line;
    std::string content;
    std::ifstream file(test);
    std::ostringstream wholeFile; 

    if (file.is_open())
    {
        while (getline(file, line)) // por cada linea
        {
            wholeFile << line;
        }
        file.close(); // Close the file
    }
    else std::cout << "Unable to open file";

    return wholeFile.str();

}

// Parte #1: Códigos maliciosos (KMP)
// Función para construir la tabla 'pi' para el algoritmo KMP.
std::vector <int> getPi (std::string pattern) {
    int pattern_length = pattern.length();
    std::vector<int> pi(pattern_length, 0); // Inicializar el vector 'pis' con ceros.
    int prefix_length = 0; // longitud del prefijo mas largo
    int pattern_index = 1; // índice para recorrer el patrón

    // construir la tabla 'pi'
    while (pattern_index < pattern_length) {
        // si los caracteres coinciden, se incrementa 1 la longitud del prefijo.
        if (pattern[prefix_length] == pattern[pattern_index]) {
            prefix_length++;
            pi[pattern_index] = prefix_length;
            pattern_index++;
        } else { // si no coinciden los caracteres
            // si la longitud del prefijo es cero se incrementa el índice del patrón.
            if (prefix_length == 0) {
                pi[pattern_index] = prefix_length;
                pattern_index++;
            } else {
                // si no hay coincidencia, retrocede en la tabla 'pi' 
                prefix_length = pi[prefix_length - 1];
            }
        }
    }
    return pi;
}

// algoritmo KMP para buscar un patrón en un texto
int  KMPSearch(const std::string text, const std::string pattern) {
    int text_length = text.length(); // longitud del texto
    int pattern_length = pattern.length(); // longitud del patrón
    // obtener la tabla 'pi' para el patrón
    std::vector<int> pi = getPi(pattern); 

    int text_index = 0; // índice para el texto
    int pattern_index = 0; // índice para el patrón

    while (text_index < text_length) {
        // si hay una coincidencia, incrementa ambos índices
        if (pattern[pattern_index] == text[text_index]) {
            text_index++;
            pattern_index++;
        }

        // si el índice del patrón es igual a la longitud del patrón, se encontró el patrón
        if (pattern_index == pattern_length) {
            return text_index - pattern_index; 
        } else if (text_index < text_length && pattern[pattern_index] != text[text_index]) {
            // si no hay coincidencia y el índice del texto es menor que la longitud del texto
            if (pattern_index != 0) { // si el índice del patrón no es cero
                pattern_index = pi[pattern_index - 1]; // retrocede en la tabla 'pi'
            } else { // si el índice del patrón es cero
                text_index++; // incrementa el índice del texto
            }
        }
    }
    return -1;
}
// Busca secuencia de mcode en fragmento de transmission y regresa la posición donde se encuentra
void FindSequence(const std::string transmission, const std::string mcode1, const std::string mcode2, const std::string mcode3) {
    int position;

    position = KMPSearch(transmission, mcode1);
    if (position != -1) {
        std::cout << "true " << position + 1 << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    position = KMPSearch(transmission, mcode2);
    if (position != -1) {
        std::cout << "true " << position + 1 << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    position = KMPSearch(transmission, mcode3);
    if (position != -1) {
        std::cout << "true " << position + 1 << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
}

// Parte #2: Códigos Espejeados (Manacher)
std::string agregarSignosDeDolar(std::string str) {
    std::string str_con_signos = "$";
    for (short i = 0; i < str.length(); ++i) {
        str_con_signos += str[i];
        str_con_signos += "$";
    }
    return str_con_signos;
}

std::vector<int> manacher(std::string str) {
    std::string str_con_signos = agregarSignosDeDolar(str);
    std::vector<int> tabla_l(str_con_signos.length(), 0);
    int l, r = 0;
    for (short c = 1; c < str_con_signos.length(); c++) {
        l = c - 1; r = c + 1;
        while (l > 1 && r < str_con_signos.length() && str_con_signos[l] == str_con_signos[r]) {
            l--; r++;
        }
        tabla_l[c] = r - c - 1;
    }
    return tabla_l;
}
void FindLargeMirrorCode(std::string transmission) {
    std::vector<int> tabla_l = manacher(transmission);
    int max_len = 0;
    int max_index = 0;
    for (int i = 0; i < tabla_l.size(); i++) {
        if (tabla_l[i] > max_len) {
            max_len = tabla_l[i];
            max_index = i;
        }
    }
    int startP = (max_index - max_len) / 2;
    int endP = startP + max_len - 1;
    std::cout << startP + 1 << " " << endP + 1 << std::endl;
}

void print_vec(std::vector <int> mi_vec){
    for(short i = 0; i < mi_vec.size(); ++i){
        std::cout<< mi_vec[i];
        if(i != mi_vec.size()-1){
            std::cout<<",";
        }
    }
    std::cout<<std::endl;
}

// Función para construir el Suffix Array (una versión simplificada del algoritmo de Manber y Myers)
std::vector<int> constructSA(const std::string& s) {
    int n = s.size();
    std::vector<int> sa(n), rank(n), tempRank(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }
    
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        
        tempRank[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tempRank[sa[i]] = tempRank[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
        }
        rank = tempRank;
    }
    // std::cout<<"SA: ";
    // print_vec(sa);
    // std::cout<<"rank: ";
    // print_vec(rank);
    return sa;
}

// Función para construir el array LCP
std::vector<int> constructLCP(const std::string& s, const std::vector<int>& sa) {
    int n = s.size();
    std::vector<int> rank(n), lcp(n-1);
    for (int i = 0; i < n; i++) {
        rank[sa[i]] = i;
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }

    // Encontrar el LCP mas grande
    int maxLCP = 0;
    int maxLCPIndex = 0;
    for (int i = 0; i < lcp.size(); i++) {
        if (lcp[i] > maxLCP) {
            maxLCP = lcp[i];
            maxLCPIndex = i;
        }
    }

    // Calcula el indice del inicio y el final del LCP mas grande 
    int startLCP = sa[maxLCPIndex] + 1; //Arreglar el que indice inicial sea 1
    int endLCP = startLCP + maxLCP - 1; //Arreglar el que indice inicial sea 1

    std::cout << startLCP << " " << endLCP << std::endl;
    return lcp;
}


int main(int argc, char const *argv[])
{
    //Lectura de archivos
    std::string transmission = readTXT("transmission1.txt");
    std::string transmission2 = readTXT("transmission2.txt");
    std::string mcode1 = readTXT("mcode1.txt");
    std::string mcode2 = readTXT("mcode2.txt");
    std::string mcode3 = readTXT("mcode3.txt");


    //Pruebas parte #1
    std::cout << "----- Parte #1: Códigos maliciosos -----" << std::endl;
    std::cout << "Transmisión #1" << std::endl;
    FindSequence(transmission, mcode1, mcode2, mcode3);
    std::cout << "Transmisión #2" << std::endl;
    FindSequence(transmission2, mcode1, mcode2, mcode3);


    //Pruebas parte #2
    std::cout << "----- Parte #2: Códigos Espejeados -----" << std::endl;
    std::cout << "Transmisión #1" << std::endl;
    FindLargeMirrorCode(transmission);
    std::cout << "Transmisión #2" << std::endl;
    FindLargeMirrorCode(transmission2);

    
    //Pruebas parte #3
    std::cout << "----- Parte #3: Códigos Semejantes -----" << std::endl;
    std::string s = transmission + "#"+ transmission2 + "$";
    // std::cout << s << std::endl;
    std::vector<int> sa = constructSA(s);
    std::vector<int> lcp = constructLCP(s, sa);

    return 0;
}