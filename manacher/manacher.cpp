#include <iostream>
#include <vector>
#include <string>

std::string agregarSignosDeDolar(std::string str) {
    std::string str_con_signos = "$";
    std::cout << "$ ";
    for (short i = 0; i < str.length(); ++i) {
        str_con_signos += str[i];
        str_con_signos += "$";
        std::cout << str[i] << " $ ";
    }
    std::cout << std::endl;
    
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

void print_tabla_l(std::vector<int> tabla_l) {
    for (short i = 0; i < tabla_l.size(); ++i) {
        std::cout << tabla_l[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> tabla_l = manacher("abacaba");
    print_tabla_l(tabla_l);
    return 0;
}