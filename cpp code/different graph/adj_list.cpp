#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <list>
#include <queue>


void helper(std::vector<std::vector<int>> adjacency_list, std::string letter, std::vector<bool>& seen, int current, int i, std::vector<std::string> path, std::queue<std::pair<int, std::vector<std::string>>>& bfs_queue){
    
    if (seen[adjacency_list[current][i]]) {
        std::cout << "have seen already: " << seen[adjacency_list[current][i]] << std::endl; 
        return;
    }

    path.push_back(letter);
    std::pair <int, std::vector<std::string>> to_add (adjacency_list[current][i], path);
    seen[adjacency_list[current][i]] = true;
    bfs_queue.push(to_add);

    std::cout << "added " << adjacency_list[current][i] << " size: " << bfs_queue.size() << std::endl;
}

int main(){
    std::ifstream infile;
    infile.open("tiny-maze.txt");

    std::ofstream outfile;
    outfile.open("output.txt");

    int x;
    int y;
    int z;

    // dimensions of the cube
    infile >> x;
    infile >> y;
    infile >> z;

    const int x1 = x;
    const int y1 = y;
    const int z1 = z;

    int startpoint[3], endpoint[3];
    for(int i = 0; i < 3; i++){
        infile >> startpoint[i];
    }
    for(int i = 0; i < 3; i++){
        infile >> endpoint[i];
    }


    std::string readMatrix[x1][y1][z1]; 

    int num = 0;
    for(int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for(int k = 0; k < z; k++){
                std::string coordinate;
                infile >> coordinate;
                readMatrix[i][j][k] = coordinate ;
            }
        }
    }
    int actual_start;
    int actual_end;
    std::vector<std::vector<int>> adjacency_list;
    num = 0;
    for(int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for(int k = 0; k < z; k++){

                if (startpoint[0] == i && startpoint[1] == j and startpoint[2] == k) {
                    actual_start = num;
                }

                if (endpoint[0] == i && endpoint[1] == j and endpoint[2] == k) {
                    actual_end = num;
                }

                std::vector<int> cur_list (6, -1);
                std::string bit = readMatrix[i][j][k];
                if (bit[0] == '1'){ // north
                    int temp = num - y;
                    cur_list[0] = temp;
                }
                if (bit[1] == '1'){ // east
                    int temp = num + 1;
                    cur_list[1] = temp;
                }
                if (bit[2] == '1'){ // south
                    int temp = num + y;
                    cur_list[2] = temp;
                }
                if (bit[3] == '1'){ // west
                    int temp = num - 1;
                    cur_list[3] = temp;
                }
                if (bit[4] == '1'){
                    int temp = num + (y * z);
                    cur_list[4] = temp;
                }
                if (bit[5] == '1'){
                    int temp = num - (y * z);
                    cur_list[5] = temp;
                }

                adjacency_list.push_back(cur_list);
                num += 1;
            }
        }
    }

    // for (int i = 0; i < adjacency_list.size(); i++ ){
    //     std::cout << i << ": ";
    //     for (int j = 0; j < adjacency_list[i].size(); j ++){
    //         outfile << adjacency_list[i][j] << " ";
    //         // std::cout << adjacency_list[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for (int i = 0; i < adjacency_list[12].size(); i ++){
    //     std::cout << adjacency_list[12][i] << " ";
    // }

    std::queue<std::pair<int, std::vector<std::string>>> bfs_queue;
    std::vector<bool> seen (num, false);
    std::vector<std::string> start_path;
    std::pair<int, std::vector<std::string>> start_pair (actual_start, start_path);
    bfs_queue.push(start_pair);
    seen[actual_start] = true;

    while (!bfs_queue.empty()){
        std::pair<int, std::vector<std::string>> unpack = bfs_queue.front();
        bfs_queue.pop();

        int current = unpack.first;
        std::vector<std::string> path = unpack.second;

        std::cout << "current: " << current << std::endl;
        // std::cout << bfs_queue.size() << std::endl;
        if (current == actual_end) {
            for (int i = 0; i < path.size(); i ++ ){
                outfile << path[i] << " ";
                // std::cout << path[i] << " ";
            }
            break;
        }

        for (int i = 0; i < adjacency_list[current].size(); i++){        
            if (adjacency_list[current][i] != -1) {
                std::cout << "see: " << adjacency_list[current][i] << std::endl;
                if (i == 0){
                    helper(adjacency_list, "N", seen, current, i, path, bfs_queue);
                }
                if (i == 1){
                    helper(adjacency_list, "E", seen, current, i, path, bfs_queue);
                }
                if (i == 2){
                    helper(adjacency_list, "S", seen, current, i, path, bfs_queue);
                }
                if (i == 3){
                    helper(adjacency_list, "W", seen, current, i, path, bfs_queue);
                }
                if (i == 4){
                    helper(adjacency_list, "U", seen, current, i, path, bfs_queue);
                }
                if (i == 5){
                    helper(adjacency_list, "D", seen, current, i, path, bfs_queue);
                }

            }
        }
    }

}

