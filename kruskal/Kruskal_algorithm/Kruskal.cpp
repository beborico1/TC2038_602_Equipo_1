/*
    Authors> 
        David Medina Domínguez (A01783155)
        Luis Rico Almada (A01252831)
        Arantza Parra Matrínez (A01782023) 
    Date> 21/08/2023
    Abstract>
        In this work you will find the implementation of Kruskal’s Algorithm, which is a Minimum Spanning Tree (MST), so it makes a
        locally optimal choice in each step in order to find the optimal solution, in doing so, making it a greedy algorithm.
        
        The data has to be provided throughout a TXT file with the weight of the connection, then the first conneciton, and then the final one. 
        Each one of them separated by blank spaces, and different connections on different lines. Example: 4 1 2 (This being that there is a
        connection between 1 and 2 with a weight of 4).
*/


#include <iostream>
#include <windows.h> //Not necesary, only for development (adds Sleep() function)
#include <fstream> //Library to read what is on a file (in/out)
#include <sstream> //Stringstream library 
#include <string>

struct links{
    short weight;
    short source;
    short destination;
    struct links *next;
    struct links *previous;
};

struct links *indice = NULL; //First in list

void add_sort(short weight_, short source_, short destination_){
    links *link_; link_ = new links;
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

    //If it is going to be the first link to be added
    if (indice == NULL){
        link_->next = NULL;
        link_->previous = NULL;
        indice =  link_;
        return;
    }

    while (indice_ != NULL){
        if(indice_->weight >= link_->weight){
            //Set up right order between links
            link_->previous = _indice;
            link_->next = indice_;
            indice_->previous = link_;
            
            //In case that it is has the lowest weight of the existing linked list
            if(_indice == NULL){
                indice = link_;
                return;
            }
            //In case that it is not the lowest weight on the list
            _indice->next = link_;
            return;
        }
        //Iterate over
        _indice = indice_;
        indice_ = indice_->next;
    }

    //If it is the link with the heaviest weight (last)
    link_->next = NULL;
    link_->previous = _indice;
    _indice->next = link_;
    return;
}

void print_links(){
    //Create an auxiliary index to print element on list
    struct links *indice_ = indice; 
    short index; index = 1;
    

    while (indice_ != NULL){
        std::cout<< "[" << index <<"] Weight: " << indice_->weight << ", Source: " << indice_->source << ", Destination: " << indice_->destination<<std::endl;
        indice_ = indice_->next;
        ++index;
    }
    return;
}


void delete_links(links* index = indice){
    if(index != NULL){
        // std::cout<<index->weight<<std::endl;
        delete_links(index->next);
        delete index;
    }
}

links* kruskal_algorithm(links* indece){
    // links* kruskal_list[];
}


void readTXT(std::string test = "test1.txt"){
    std::string line;
    std::ifstream file (test);

    if (file.is_open()){
        while (getline(file, line)){
            short weight_, source_, destination_;

            //Separate the string 'line' into the different values of weight, source and destination
            std::stringstream ssline(line);
            ssline >> weight_ >> source_ >> destination_;
            //Add to the existing list
            add_sort(weight_, source_, destination_);
        }
        //Close the file
        file.close();
    }
    //If the file was not found
    else std::cout << "Unable to open file"; 
}



int main(int argc, char* argv[]){
    // for (int i = 1; i <= argc; ++i){
    //     if(argv[i] != NULL){
    //         readTXT(argv[i]);
    //     }
    //     else{readTXT(); break;}
    // }
    readTXT("test2.txt");
    print_links();

    delete_links();
    return 0;
}