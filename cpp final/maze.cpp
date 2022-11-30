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

int totalsize = 0; // global variable which is necessary for the visited set on the bfs

struct Vertex {

    /*
        Each vertex will have 6 pointers which will be initialized to null.
    */

    Vertex* North;
    Vertex* South;
    Vertex* East;
    Vertex* West;
    Vertex* Up;
    Vertex* Down;
    int id; // to identify and to use on the visited set later

    Vertex() {
        North = nullptr;
        South = nullptr;
        East = nullptr;
        West = nullptr;
        Up = nullptr;
        Down = nullptr;
    }
};

std::string getDirections(const std::string& binaryString){   

    /*
        Given the input binary string, this function computes and returns all the directions
        that a vertex can travel to. Which will be used when setting the pointers.
    */

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

/*
auto readInput(const std::string& filename){
    std::ifstream file(filename);
    std::string results;

    if (!file.is_open()){
        throw std::runtime_error("cannot read file");
    }

    std::tuple <int, int, int> size;
    std::tuple <int, int, int> start;
    std::tuple <int, int, int> end;

}
*/

// helper functions
void addToTuple(std::ifstream& file, std::tuple<int, int, int>& tup){

    /*
        The first three lines are l, r, c along with the coordinates for the start and end. To avoid having repeated code
        this function takes the file that is being read from and the tuple to pass the values (from the file) to.
    */

    file >> std::get<0>(tup);
    file >> std::get<1>(tup);
    file >> std::get<2>(tup);
}

void helper(Vertex v, std::vector<bool>& visited, std::vector<std::string> path, std::string direction, std::queue<std::pair<Vertex, std::vector<std::string>>>& q){

    /*
        Since you can check N, S, E, W, U, D and they were implemented with if-if's, this helper will reduce the need to repeat the following lines
        Taking the neighboring vertex, the visited set, the current path, destination, and queue this function will perform the
        necessary operations of bfs

        Check if we've seen vertex "v" before, mark it visited, add its destination to the path and add the pair to the queue
    */

    if (visited[v.id] == false) { // if we have not seen the vertex yet
        visited[v.id] = true; // mark it seen
        path.push_back(direction); // add the destination to path
        std::pair<Vertex, std::vector<std::string>> addToQueue(v, path); // make the pair
        q.push(addToQueue); // add to queue
    }
}

void writeToFile(std::vector<std::string> data){
    std::ofstream output("output.txt"); 
    for (int i = 0; i < data.size(); i++){
        output << data[i] << ' ';
    }
    output.close();
}

void bfs(Vertex start, Vertex end){

    /*
        This function represents an implementation of bfs. It takes the starting + ending nodes and writes the path
        once the "end" vertex is found
    */

    std::vector<bool> visited; // set
    visited.resize(totalsize, false); // give it sentinel value of False
    std::queue<std::pair<Vertex, std::vector<std::string>>> queue; // queue takes vertex and path leading up to it
    std::vector<std::string> start_path; // initial path, which contains nothing
    std::pair<Vertex, std::vector<std::string>> p(start, start_path); // starting pair which contains start vertex and initial path
    queue.push(p);
    visited[start.id] = true; // mark it seen since we know it

    while (!queue.empty()) {

        std::pair<Vertex, std::vector<std::string>> current_pair = queue.front(); // get the current vertex we are
        queue.pop();

        Vertex vertex = current_pair.first;
        std::vector<std::string> cur_path = current_pair.second;

        if (vertex.id == end.id) { // way to identify that we have reached the end
            writeToFile(cur_path);
            break;
        }

        if (vertex.North != nullptr){
            helper(*vertex.North, visited, cur_path, "N", queue);
        }

        if (vertex.South != nullptr){
            helper(*vertex.South, visited, cur_path, "S", queue);
        }

        if (vertex.East != nullptr){
            helper(*vertex.East, visited, cur_path, "E", queue);
        }

        if (vertex.West != nullptr){
            helper(*vertex.West, visited, cur_path, "W", queue);
        }

        if (vertex.Up != nullptr){
            helper(*vertex.Up, visited, cur_path, "U", queue);
        }

        if (vertex.Down != nullptr){
            helper(*vertex.Down, visited, cur_path, "D", queue);
        }
    }

}

std::vector<std::vector<std::vector<Vertex>>> Graph(std::tuple <int, int, int> size, std::tuple <int, int, int> start, std::tuple <int, int, int> end, std::ifstream& file){
    std::vector<std::vector<std::vector<Vertex>>> graph;    
    std::vector<std::vector<std::vector<std::string>>> binaryGraph;

    for (int i = 0; i < (std::get<0>(size)*std::get<1>(size)); i = i + std::get<1>(size)){
        std::vector<std::vector<Vertex>> buildNodeGraph;
        std::vector<std::vector<std::string>> current_level;
        for (int j = 0; j < std::get<1>(size); j++){
            std::vector<Vertex> buildNodes;
            std::vector<std::string> current_row;
            for (int k = 0; k < std::get<2>(size); k++){
                std::string temp;
                file >> temp;
                current_row.push_back(getDirections(temp));
                Vertex cur;
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

    return graph;
}

int main(){
    
    // std::ifstream file("/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt");
    //itsybitsy-maze.txt
    std::ifstream file("/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt");
    std::string results;

    if (!file.is_open()){
        std::cout << "cannot";
        throw std::runtime_error("cannot read file");
    }

    std::tuple <int, int, int> size; // l, r, c
    std::tuple <int, int, int> start; // coordinates for the starting vertex
    std::tuple <int, int, int> end; // coordinates for the destination vertex

    addToTuple(file, size);
    addToTuple(file, start);
    addToTuple(file, end);


    std::vector<std::vector<std::vector<Vertex>>> graph = Graph(size, start, end, file);
    bfs(graph[std::get<0>(start)][std::get<1>(start)][std::get<2>(start)], graph[std::get<0>(end)][std::get<1>(end)][std::get<2>(end)]);

    /*
    //test

    for (int i = 0; i < binaryGraph.size(); i++){
        for (int j = 0; j < binaryGraph[i].size(); j++){
            for (int k = 0; k < binaryGraph[i][j].size(); k++){
                std::cout << graph[i][j][k].id << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    */

    /*
    std::vector<bool> visited;
    visited.resize(totalsize, false);
    std::queue<std::pair<Vertex, std::vector<std::string>>> queue;
    std::vector<std::string> start_path;

    std::pair<Vertex, std::vector<std::string>> p(graph[0][3][3], start_path);
    queue.push(p);
    visited[graph[0][3][3].id] = true;

    while(!queue.empty()){

        std::pair<Vertex, std::vector<std::string>> current = queue.front();
        queue.pop();

        Vertex cur = current.first;
        std::vector<std::string> path = current.second;

        // test
        // for (int i = 0; i < path.size(); i ++){
        //         std::cout << path[i] << ' ';
        // }
        // std::cout << std::endl;

        if (cur.id == graph[4][0][0].id){
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
    */
    
    return 0;
}
