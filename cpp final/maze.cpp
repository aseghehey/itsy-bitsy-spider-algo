#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <tuple>
#include <queue>

int totalsize = 0; // global variable which is necessary for the visited set on the bfs

struct Vertex {

    /*
        Each vertex will have 6 pointers which will be initialized to null.
        The graph will use this struct as vertices and the pointers are used to represent the edges.
    */

    Vertex* North;
    Vertex* South;
    Vertex* East;
    Vertex* West;
    Vertex* Up;
    Vertex* Down;
    int id; // to identify and to use on the visited set later

    Vertex() {
        // the default value for each pointer is null and they will be changed later as we build the edges
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
    
    /*
        Given data, this function will write the contents of data to the output file
    */

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
            // std::cout << &vertex << ' ' << &end << std::endl;
            // std::cout << vertex.id << ' ' << end.id << std::endl;
            writeToFile(cur_path);
            return; // end function
        }

        // adding the edges to the queue
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

std::vector<std::vector<std::vector<Vertex>>> Graph(std::tuple <int, int, int> size, std::ifstream& file){
    /*
        Given the size and file to be read from, this function will create and return a graph with vertices and pointers
        to other vertices, which corresponds to the binary string input from the file
    */
    std::vector<std::vector<std::vector<Vertex>>> graph;    // graph that will be returned
    std::vector<std::vector<std::vector<std::string>>> binaryGraph; // graph that will store the read bits from the textfile

    for (int z = 0; z < (std::get<0>(size)*std::get<1>(size)); z = z + std::get<1>(size)){ // traverses until the number of (rows * levels) is reached
        // helper vectors which are used later to build upper layers of graph
        std::vector<std::vector<Vertex>> buildNodeGraph; 
        std::vector<std::vector<std::string>> current_level; 

        for (int y = 0; y < std::get<1>(size); y++){ // loops until number of rows
            // helper vectors which are used later to build the layers of the graph
            std::vector<Vertex> buildNodes; 
            std::vector<std::string> current_row; 

            for (int x = 0; x < std::get<2>(size); x++){ // loops until number of columns
                std::string temp; // temporary to hold current string read from file
                file >> temp; 
                current_row.push_back(getDirections(temp));
                Vertex cur; // Vertex to be added
                cur.id = totalsize; // for identification used later
                totalsize += 1;
                buildNodes.push_back(cur); // start of building graph
            }
            // build levels
            buildNodeGraph.push_back(buildNodes);
            current_level.push_back(current_row);
        }
        // build upper layer
        graph.push_back(buildNodeGraph);
        binaryGraph.push_back(current_level);
    }

    // creating the edges for the graph
    for (int z = 0; z < binaryGraph.size(); z++){
        for (int y = 0; y < binaryGraph[z].size(); y++){
            for (int x = 0; x < binaryGraph[z][y].size(); x++){
                std::string current_string = binaryGraph[z][y][x]; // will go through each letter in the string and determine the dependencies (where to direct pointers)
            
                for (int w = 0; w < current_string.length(); w++){
                    switch(current_string[w]){
                        case 'N':
                            graph[z][y][x].North = &graph[z][y-1][x]; // north is above current row
                            break;
                        case 'S':
                            graph[z][y][x].South = &graph[z][y+1][x]; // south is below current row
                            break;
                        case 'W':
                            graph[z][y][x].West = &graph[z][y][x-1]; // west is in the previous column
                            break;
                        case 'E':
                            graph[z][y][x].East = &graph[z][y][x+1]; // east is in the next column
                            break;
                        case 'U':
                            graph[z][y][x].Up = &graph[z+1][y][x]; // up is in above level
                            break;
                        case 'D':
                            graph[z][y][x].Down = &graph[z-1][y][x]; // down is a level below
                            break;
                    }
                }
            }
        }
    }

    return graph;
}

int main(){
    
    std::ifstream file("/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt");

    if (!file.is_open()){
        std::cout << "cannot";
        throw std::runtime_error("cannot read file");
    }

    std::tuple <int, int, int> size; // levels, rows, columns
    std::tuple <int, int, int> start; // coordinates for the starting vertex
    std::tuple <int, int, int> end; // coordinates for the destination vertex

    // reading and storing first three lines to their respective tuples
    addToTuple(file, size);
    addToTuple(file, start);
    addToTuple(file, end);

    std::vector<std::vector<std::vector<Vertex>>> graph = Graph(size, file);
    bfs(graph[std::get<0>(start)][std::get<1>(start)][std::get<2>(start)], graph[std::get<0>(end)][std::get<1>(end)][std::get<2>(end)]);
    
    return 0;
}
