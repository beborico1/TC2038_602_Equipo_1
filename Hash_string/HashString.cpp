/*
    Authors> 
        David Medina Domínguez (A01783155)
        Luis Rico Almada (A01252831)
        Arantza Parra Matrínez (A01782023) 
    Date> 21/09/2023
    Abstract>
        in this work we implement the Polynomial rolling hash function to compare two strings and discover if they are the same  :)
*/


#include <iostream>
#include <vector>
#include <string>
#include <cmath>


// Como convertirlo: static_cast<int>("A");


void print_vector(std::vector<int> mi_vec) {
    for (short i = 0; i < mi_vec.size(); ++i) {
        std::cout << mi_vec[i] << " ";
    }
    std::cout << std::endl;
}

int get_value(std::string str){
    int p; p = 31; //Numero primo mas grande que el abecedario a usar
    int m; m = pow(10, 9) + 9;
    std::vector<int> ascii_vec;
    for(short i = 0; i < str.length(); ++i){
        // std::cout<<static_cast<int>(str[i])<<std::endl;
        ascii_vec.push_back(static_cast<int>(str[i]));
    }
    print_vector(ascii_vec);

    long sum; sum = ascii_vec[0];
    for(int i = 1; i < ascii_vec.size(); ++i){
        int dividend = ascii_vec[i] + pow(p,i);
        std::cout<<dividend<<std::endl;
        sum =+ dividend % m;
        std::cout<<sum<<std::endl;

    }
    std::cout<<sum<<std::endl;
    return sum;
}


int main(){
    get_value("xcbcc");
    return 0;
}