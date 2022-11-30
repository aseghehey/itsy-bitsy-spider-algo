#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <tuple>
#include <queue>

int totalsize = 0;

struct Node {
    Node* North;
    Node* South;
    Node* East;
    Node* West;
    Node* Up;
    Node* Down;
    int id;

    Node() {
        North = nullptr;
        South = nullptr;
        East = nullptr;
        West = nullptr;
        Up = nullptr;
        Down = nullptr;
    }
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

void helper(Node v, std::vector<bool>& visited, std::vector<std::string> path, std::string direction, std::queue<std::pair<Node, std::vector<std::string>>>& q){

    if (visited[v.id] == false) {
        visited[v.id] = true;
        path.push_back(direction);
        std::pair<Node, std::vector<std::string>> addToQueue(v, path);
        q.push(addToQueue);
    }
}

std::string bfs(Node start, Node end){
    // create visit
    std::vector<bool> visited;
    visited.resize(totalsize, false);
    std::queue<std::tuple<Node, std::vector<std::string>>> queue;
    visited[start.id] = true;

    while(!queue.empty()){
        std::tuple<Node, std::vector<std::string>> nodeTuple = queue.front();
        queue.pop();
    }
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
                cur.id = totalsize;
                totalsize += 1;
                buildNodes.push_back(cur);
            }
            buildNodeGraph.push_back(buildNodes);
            current_level.push_back(current_row);
        }
        graph.push_back(buildNodeGraph);
        binaryGraph.push_back(current_level);
    }
    
    for (int i = 0; i < binaryGraph.size(); i++){
        for (int j = 0; j < binaryGraph[i].size(); j++){
            for (int k = 0; k < binaryGraph[i][j].size(); k++){
                std::string current_string = binaryGraph[i][j][k];
                for (int w = 0; w < current_string.length(); w++){
                    switch(current_string[w]){
                        case 'N':
                            graph[i][j][k].North = &graph[i][j-1][k];
                            break;
                        case 'S':
                            graph[i][j][k].South = &graph[i][j+1][k];
                            break;
                        case 'W':
                            graph[i][j][k].West = &graph[i][j][k-1];
                            break;
                        case 'E':
                            graph[i][j][k].East = &graph[i][j][k+1];
                            break;
                        case 'U':
                            graph[i][j][k].Up = &graph[i+1][j][k];
                            break;
                        case 'D':
                            graph[i][j][k].Down = &graph[i-1][j][k];
                            break;
                    }
                }
            }
        }
    }

    // test
    // for (int i = 0; i < binaryGraph.size(); i++){
    //     for (int j = 0; j < binaryGraph[i].size(); j++){
    //         for (int k = 0; k < binaryGraph[i][j].size(); k++){
    //             std::cout << graph[i][j][k].id << ' ';
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << graph[0][0][0].Up << std::endl;
    // std::cout << &graph[1][0][0] << std::endl;

    std::vector<bool> visited;
    visited.resize(totalsize, false);
    std::queue<std::pair<Node, std::vector<std::string>>> queue;
    std::vector<std::string> start_path;

    std::pair<Node, std::vector<std::string>> p(graph[0][0][0], start_path);
    queue.push(p);
    visited[graph[0][0][0].id] = true;

    while(!queue.empty()){

        std::pair<Node, std::vector<std::string>> current = queue.front();
        queue.pop();

        Node cur = current.first;
        std::vector<std::string> path = current.second;

        // test
        // for (int i = 0; i < path.size(); i ++){
        //         std::cout << path[i] << ' ';
        // }
        // std::cout << std::endl;

        if (cur.id == graph[2][2][2].id){
            for (int i = 0; i < path.size(); i ++){
                std::cout << path[i] << ' ';
            }
            // break;
        }

        if (cur.North != nullptr){
            helper(*cur.North, visited, path, "N", queue);
        }

        if (cur.South != nullptr){
            // come back
            helper(*cur.South, visited, path, "S", queue);
        }

        if (cur.East != nullptr){
            helper(*cur.East, visited, path, "E", queue);
        }

        if (cur.West != nullptr){
            helper(*cur.West, visited, path, "W", queue);
        }

        if (cur.Up != nullptr){
            helper(*cur.Up, visited, path, "U", queue);
        }

        if (cur.Down != nullptr){
            helper(*cur.Down, visited, path, "D", queue);
        }
    }

    return 0;
}
