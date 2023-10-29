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
#include <fstream> //Stringstream library
#include <string>

void readTXT(std::string test /*std::string test = "mcode1.txt"*/){
    std::string line;
    std::ifstream file(test);

    if (file.is_open()){
        while(getline(file, line)){
            // Separate the string 'line' into the different values of weight, source and destination
            // std::stringstream ssline(line);
            std::cout<<line<<std::endl;
        }
        // Close the file
        file.close();
    }
    // If the file was not found
    else
        std::cout << "Unable to open file";
}

int main(int argc, char const *argv[]){
    std::cout<<"Hello world"<<std::endl;
    readTXT("mcode1.txt");
    return 0;
}
