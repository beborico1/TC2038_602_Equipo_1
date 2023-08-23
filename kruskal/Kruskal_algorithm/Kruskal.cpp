/*
    Authors> 
        David Medina Domínguez (A01783155)
        Luis
        Atantza
    Date> 28/08/2023
    Abstract>
        In this work you will find the implementation of Kruskal’s Algorithm, which is a Minimum Spanning Tree (MST), so it makes a
        locally optimal choice in each step in order to find the optimal solution, in doing so, making it a greedy algorithm.
        
        The data has to be provided throughout a TXT file with the weight of the connection, then the first conneciton, and then the final one. 
        Each one of them separated by blank spaces, and different connections on different lines. Example: 4 1 2 (This being that there is a
        connection between 1 and 2 with a weight of 4).
*/


#include <iostream>
#include <fstream> //Library to read what is on a file (in/out)
#include <cctype> // Provides functions to classify and manipulate individual characters, (adds isspace() function)
#include <string>
#include <windows.h> //Not necesary, only for development (adds Sleep() function)

struct links{
    short weight;
    short source;
    short destination;
    struct links *next;
    struct links *previous;
};

struct links *indice = NULL; //Inicio de la lista

void add_sort(short weight_, short source_, short destination_){
    links *link_; link_ = new links;//-----------------------------------------------capaz es links()
    if (link_ == NULL){ // Check if the new "link" memory space did in fact was created
		std::cout<<"Couldn't create new link"<<std::endl;
		return;
	}

    //Give the corresponding values to the new link
    link_->weight = weight_;
    link_->source = source_;
    link_->destination = destination_;

    struct links *indice_ = indice; //Create an auxiliary index (leading) to iterate through the double linked list
    struct links *_indice = NULL; //Create another auxiliary index (following)

    if (indice == NULL){//If it is going to be the first link ot be added
        link_->next = NULL;
        link_->previous = NULL;
        indice =  link_;
        return;
    }

    while (indice_ != NULL){
        if(indice_->weight >= link_->weight){
            link_->previous = _indice;
            link_->next = indice_;
            indice_->previous = link_;
            if(_indice == NULL){//In case that it is has the lowest weight of the existing linked list
                indice = link_;
                return;
            }
            _indice->next = link_;
            return;
        }
        _indice = indice_;//Iterate over
        indice_ = indice_->next;
    }
    //If it is the link with the heaviest weight
    link_->next = NULL;
    link_->previous = _indice;
    _indice->next = link_;
    return;
}

void print_links(){
    struct links *indice_ = indice; //Create an auxiliary index to iterate through the double linked list
    
    while (indice_ != NULL){
        std::cout<<"Weight: " << indice_->weight << ", Source: " << indice_->source << ", Destination: " << indice_->destination<<std::endl;
        indice_ = indice_->next;
    }
    return;
}




void readTXT(std::string test = "test1.txt"){
    std::string line;
    std::ifstream file (test);

    if (file.is_open()){
        while (getline(file, line)){
            std::cout << line<<std::endl;
            add_sort();
            break;
            // Sleep(1000);
        }

    file.close();
    }
    else std::cout << "Unable to open file"; 
}



int main(int argc, char* argv[]){
    // for (int i = 1; i <= argc; ++i){
    //     if(argv[i] != NULL){
    //         readTXT(argv[i]);
    //     }
    //     else{readTXT(); break;}
    // }
    readTXT();
    std::cout<<indice->weight<<std::endl;
    print_links();


    return 0;
}