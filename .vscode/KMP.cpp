#include <iostream>
#include <vector>
#include <string>

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
void KMPSearch(const std::string text, const std::string pattern) {
    int text_length = text.length(); // longitud del texto
    int pattern_length = pattern.length(); // longitud del patrón
    // obtener la tabla 'pi' para el patrón
    std::vector<int> pi = getPi(pattern); 

    std::cout << "Tabla pi del patrón: " << std::endl;
    for (int pi_index = 0; pi_index < pi.size(); pi_index++) {
        std::cout << pi[pi_index] << " ";
    }
    std::cout << std::endl;

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
            std::cout << "Patrón encontrado en el índice " << text_index - pattern_index << std::endl;
            pattern_index = pi[pattern_index - 1];
        } else if (text_index < text_length && pattern[pattern_index] != text[text_index]) {
            // si no hay coincidencia y el índice del texto es menor que la longitud del texto
            if (pattern_index != 0) { // si el índice del patrón no es cero
                pattern_index = pi[pattern_index - 1]; // retrocede en la tabla 'pi'
            } else { // si el índice del patrón es cero
                text_index++; // incrementa el índice del texto
            }
        }
    }
}

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    std::cout << "Texto: " << text << std::endl;
    std::cout << "Patrón: " << pattern << std::endl;

    // buscar el patrón en el texto
    KMPSearch(text, pattern);

    return 0;
}
