#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <tuple>
#include <queue>

int cell_number = 0; // global variable which is necessary for the visited set on the bfs

struct Vertex {

    /*
        Each vertex will have 6 pointers which will be initialized to null.
        The graph will use this struct as vertices and the pointers are used to represent the edges.
    */

    Vertex* N;
    Vertex* S;
    Vertex* E;
    Vertex* W;
    Vertex* U;
    Vertex* D;
    int cell; // to identify and to use on the visited set later

    Vertex() {
        // the default value for each pointer is null and they will be changed later as we build the edges
        N = nullptr;
        S = nullptr;
        E = nullptr;
        W = nullptr;
        U = nullptr;
        D = nullptr;
    }
};

std::string get_directions(const std::string& binary_string){   

    /*
        Given the input binary string, this function computes and returns all the directions
        that a vertex can travel to. Which will be used when setting the pointers.
    */

    std::string directions;
    for (int i = 0; i < binary_string.length(); i++){
        if (binary_string[i] == '1'){
            switch(i){
                case 0:
                    directions += 'N';
                    break;
                case 1:
                    directions += 'E';
                    break;
                case 2:
                    directions += 'S';
                    break;
                case 3:
                    directions += 'W';
                    break;
                case 4:
                    directions += 'U';
                    break;
                case 5:
                    directions += 'D';
                    break;
            }
        }
    }
    return directions;
}

// helper functions
void write_to_tuple(std::ifstream& file, std::tuple<int, int, int>& tuple_to_add){

    /*
        The first three lines are l, r, c along with the coordinates for the start and end. To avoid having repeated code
        this function takes the file that is being read from and the tuple to pass the values (from the file) to.
    */

    file >> std::get<0>(tuple_to_add);
    file >> std::get<1>(tuple_to_add);
    file >> std::get<2>(tuple_to_add);
}

void find_path_bfs_helper(Vertex current_vertex, std::vector<bool>& set_visited, std::vector<std::string> current_path, std::string destination, std::queue<std::pair<Vertex, std::vector<std::string>>>& queue){

    /*
        Since you can check N, S, E, W, U, D and they were implemented with if-if's, this helper will reduce the need to repeat the following lines
        Taking the neighboring vertex, the visited set, the current path, destination, and queue this function will perform the
        necessary operations of bfs

        Check if we've seen vertex "current_vertex" before, mark it visited, add its destination to the path and add the pair to the queue
    */

    if (set_visited[current_vertex.cell] == false) { // if we have not seen the vertex yet
        set_visited[current_vertex.cell] = true; // mark it seen
        current_path.push_back(destination); // add the destination to current_path
        std::pair<Vertex, std::vector<std::string>> addToQueue(current_vertex, current_path); // make the pair
        queue.push(addToQueue); // add to queue
    }
}

void write_to_file(std::vector<std::string> data){
    
    /*
        Given data, this function will write the contents of data to the output file
    */

    std::ofstream output("output.txt"); 
    for (int i = 0; i < data.size(); i++){
        output << data[i] << ' ';
    }
    output.close();
    std::cout << "successfully written to file" << std::endl;
}

std::vector<std::string> find_path_bfs(Vertex start, Vertex end){

    /*
        This function represents an implementation of bfs. It takes the starting + ending nodes and writes the path
        once the "end" vertex is found
    */

    std::vector<bool> visitedSet; // set
    visitedSet.resize(cell_number, false); // give it sentinel value of False
    visitedSet[start.cell] = true; // mark it seen since we know it
    std::queue<std::pair<Vertex, std::vector<std::string>>> queue; // queue stores pair of: vertex and path leading up to it
    std::vector<std::string> start_path; // initial path, which contains nothing
    std::pair<Vertex, std::vector<std::string>> start_pair(start, start_path); // starting pair which contains start vertex and initial path
    queue.push(start_pair);

    while (!queue.empty()) {

        std::pair<Vertex, std::vector<std::string>> current_pair = queue.front(); // get the current vertex we are
        queue.pop();

        // read from current pair
        Vertex vertex = current_pair.first;
        std::vector<std::string> cur_path = current_pair.second;

        if (vertex.cell == end.cell) { // way to identify that we have reached the end
            return cur_path;
        }

        // adding the edges to the queue
        if (vertex.N != nullptr){
            find_path_bfs_helper(*vertex.N, visitedSet, cur_path, "N", queue);
        }

        if (vertex.S != nullptr){
            find_path_bfs_helper(*vertex.S, visitedSet, cur_path, "S", queue);
        }

        if (vertex.E != nullptr){
            find_path_bfs_helper(*vertex.E, visitedSet, cur_path, "E", queue);
        }

        if (vertex.W != nullptr){
            find_path_bfs_helper(*vertex.W, visitedSet, cur_path, "W", queue);
        }

        if (vertex.U != nullptr){
            find_path_bfs_helper(*vertex.U, visitedSet, cur_path, "U", queue);
        }

        if (vertex.D != nullptr){
            find_path_bfs_helper(*vertex.D, visitedSet, cur_path, "D", queue);
        }
    }

    return start_path; // if no path is found, returns empty path
}

std::vector<std::vector<std::vector<Vertex>>> Graph(std::tuple <int, int, int> dimensions, std::ifstream& read_file){
    /*
        Given the dimensions and file to be read from, this function will create and return a graph with vertices and pointers
        to other vertices, which corresponds to the binary string input from the file
    */
    std::vector<std::vector<std::vector<Vertex>>> graph;    // graph that will be returned
    std::vector<std::vector<std::vector<std::string>>> helper_graph; // graph that will store the read bits from the textfile

    for (int z = 0; z < (std::get<0>(dimensions)*std::get<1>(dimensions)); z = z + std::get<1>(dimensions)){ // traverses until the number of (rows * levels) is reached
        // helper vectors which are used later to build upper layers of graph
        std::vector<std::vector<Vertex>> build_vertex_graph_helper; 
        std::vector<std::vector<std::string>> build_graph_level_helper; 

        for (int y = 0; y < std::get<1>(dimensions); y++){ // loops until number of rows
            // helper vectors which are used later to build the layers of the graph
            std::vector<Vertex> build_vertex_in_graph_helper; 
            std::vector<std::string> build_graph_column_helper; 

            for (int x = 0; x < std::get<2>(dimensions); x++){ // loops until number of columns
                std::string temp_string; // temporary to hold current string read from file
                read_file >> temp_string; 
                build_graph_column_helper.push_back(get_directions(temp_string));
                Vertex current_vertex; // Vertex to be added
                current_vertex.cell = cell_number; // for identification used later
                cell_number += 1;
                build_vertex_in_graph_helper.push_back(current_vertex); // start of building graph
            }
            // build levels
            build_vertex_graph_helper.push_back(build_vertex_in_graph_helper);
            build_graph_level_helper.push_back(build_graph_column_helper);
        }
        // build upper layer
        graph.push_back(build_vertex_graph_helper);
        helper_graph.push_back(build_graph_level_helper);
    }

    // creating the edges for the graph
    for (int z = 0; z < helper_graph.size(); z++){
        for (int y = 0; y < helper_graph[z].size(); y++){
            for (int x = 0; x < helper_graph[z][y].size(); x++){
                std::string current_string = helper_graph[z][y][x]; // will go through each letter in the string and determine the dependencies (where to direct pointers)
            
                for (int w = 0; w < current_string.length(); w++){
                    switch(current_string[w]){
                        case 'N':
                            graph[z][y][x].N = &graph[z][y-1][x]; // north is above current row
                            break;
                        case 'S':
                            graph[z][y][x].S = &graph[z][y+1][x]; // south is below current row
                            break;
                        case 'W':
                            graph[z][y][x].W = &graph[z][y][x-1]; // west is in the previous column
                            break;
                        case 'E':
                            graph[z][y][x].E = &graph[z][y][x+1]; // east is in the next column
                            break;
                        case 'U':
                            graph[z][y][x].U = &graph[z+1][y][x]; // up is in above level
                            break;
                        case 'D':
                            graph[z][y][x].D = &graph[z-1][y][x]; // down is a level below
                            break;
                    }
                }
            }
        }
    }

    return graph;
}

int main(){
    
    std::ifstream file("/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/itsybitsy-maze.txt");

    if (!file.is_open()){ // checking if we're able to open the file, checker to see if it exists
        throw std::runtime_error("cannot read file");
    }

    std::tuple <int, int, int> size; // levels, rows, columns
    std::tuple <int, int, int> start; // coordinates for the starting vertex
    std::tuple <int, int, int> end; // coordinates for the destination vertex

    // reading and storing first three lines to their respective tuples
    write_to_tuple(file, size);
    write_to_tuple(file, start);
    write_to_tuple(file, end);

    std::vector<std::vector<std::vector<Vertex>>> graph = Graph(size, file);
    file.close();
    std::vector<std::string> path = find_path_bfs(graph[std::get<0>(start)][std::get<1>(start)][std::get<2>(start)], graph[std::get<0>(end)][std::get<1>(end)][std::get<2>(end)]);
    write_to_file(path);

    return 0;
}
