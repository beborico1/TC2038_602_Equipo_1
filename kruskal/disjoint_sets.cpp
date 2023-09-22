#include <iostream>
#include <vector>

struct disjointSet{
    std::vector<int> parent; // vector of parent nodes
    std::vector<int> rank; // vector of rank of each node
    int n; // number of nodes

    //Construct 
    disjointSet(int a){
        n=a;
        for(int i=0;i<n;i++){
            parent.push_back(i);
            rank.push_back(0);
        }
    }
    //Find the parent of the node
    int find(int u){
        // If it is a root node -> if it is not its own father, keep looking for the parent
        if(parent[u]!=u){
            parent[u]=find(parent[u]);
        }
        //Return if the node is its own parent
        else{
            return parent[u];
        }
    }
    //Union of nodes
    void join(int source, int destinantion){
        int a=find(source);
        int b = find(destinantion);
        //Find the parent of each node
        if(rank[a]>rank[b]){
            parent[b]=a;
        }
        else{
            parent[a]=b;
            if(rank[a]==rank[b]){
                rank[b]++;
            }
        }
    }
};

int main(){
    return 0;
}