#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <tuple>

struct Node {
    Node* North;
    Node* South;
    Node* East;
    Node* West;
    Node* Up;
    Node* Down;
};

std::string getDirections(const std::string& binaryString){    
    std::string result;
    for (int i = 0; i < binaryString.length(); i++){
        if (binaryString[i] == '1'){
            switch(i){
                case 0:
                    result += 'N';
                    break;
                case 1:
                    result += 'E';
                    break;
                case 2:
                    result += 'S';
                    break;
                case 3:
                    result += 'W';
                    break;
                case 4:
                    result += 'U';
                    break;
                case 5:
                    result += 'D';
                    break;
            }
        }
    }
    return result;
}

// auto readInput(const std::string& filename){
//     std::ifstream file(filename);
//     std::string results;

//     if (!file.is_open()){
//         throw std::runtime_error("cannot read file");
//     }

//     std::tuple <int, int, int> size;
//     std::tuple <int, int, int> start;
//     std::tuple <int, int, int> end;

// }

void addToTuple(std::ifstream& file, std::tuple<int, int, int>& tup){
    file >> std::get<0>(tup);
    file >> std::get<1>(tup);
    file >> std::get<2>(tup);
}

int main(){
    
    std::ifstream file("/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt");
    std::string results;

    if (!file.is_open()){
        std::cout << "cannot";
        throw std::runtime_error("cannot read file");
    }

    std::tuple <int, int, int> size; // l, r, c
    std::tuple <int, int, int> start;
    std::tuple <int, int, int> end;


    std::vector<std::vector<std::vector<Node>>> graph;    
    std::vector<std::vector<std::vector<std::string>>> binaryGraph;

    addToTuple(file, size);
    addToTuple(file, start);
    addToTuple(file, end);

    // creating both graphs, actual and helper
    for (int i = 0; i < (std::get<0>(size)*std::get<1>(size)); i=i + std::get<1>(size)){
        std::vector<std::vector<Node>> buildNodeGraph;
        std::vector<std::vector<std::string>> current_level;
        for (int j = 0; j < std::get<1>(size); j++){
            std::vector<Node> buildNodes;
            std::vector<std::string> current_row;
            for (int k = 0; k < std::get<2>(size); k++){
                std::string temp;
                file >> temp;
                current_row.push_back(getDirections(temp));
                Node cur;
                buildNodes.push_back(cur);
            }
            buildNodeGraph.push_back(buildNodes);
            current_level.push_back(current_row);
        }
        graph.push_back(buildNodeGraph);
        binaryGraph.push_back(current_level);
    }

    for (int i = 0; i < binaryGraph.size(); i++){
        for (int j = 0; j < binaryGraph.at(i).size(); j++){
            for (int k = 0; k < binaryGraph.at(i).at(j).size(); k++){
                // std::cout << binaryGraph.at(i).at(j).at(k) << std::endl; 
                // std::cout << graph.at(i).at(j).at(k).val << std::endl;
            }
        }
    }


    //level = 0
    // loop from third line to final, in increments of r
        // loop from i to i + c
        //add to cur level(index)
        // increment level





    return 0;
}