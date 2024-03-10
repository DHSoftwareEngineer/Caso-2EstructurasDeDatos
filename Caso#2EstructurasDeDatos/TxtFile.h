#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

class TxtFile
{
    private: 
        string filename = "results.txt"; 
        ofstream outFile; 
        int mazeX = 0; 
        int mazeY = 0; 
    public:
    

    void createFile(){
        outFile.open(filename); 
        outFile.close(); 
    }

    void addMazeToFile(vector<vector<string>> mainMaze){
        outFile.open(filename); 
        mazeX = mainMaze.size(); 
        mazeY = mainMaze[0].size(); 
        for (int i = 0; i < mainMaze.size(); i++) {
            for (int j = 0; j < mainMaze[i].size(); j++) {
                string information; 
                information = "A partir de la posición " + to_string(i) + " " + to_string(j) +" se desconoce si es posible llegar a un tesoro.\n"; 
                outFile <<information; 
            }
        }
        outFile.close(); 
    }

    void writeResult(int xPosition, int yPosition, bool treasureReachable){
        vector<string> lines; 
        string result = "A partir de la posición " + to_string(xPosition) + 
                        " " + to_string(yPosition) +" SÍ se puede llegar a un tesoro."; 
; 
        if(!treasureReachable){
            result = "A partir de la posición " + to_string(xPosition) + 
                        " " + to_string(yPosition) +" NO se puede llegar a un tesoro."; 
        }
        ifstream inFile(filename); 
        for(int i = 0; i < mazeX; i++){
            for(int j = 0; j <mazeY; j++ ){
                string line; 
                getline(inFile, line); 
                
                if(i == xPosition && j == yPosition){
                    lines.push_back(result); 
                }else{
                    lines.push_back(line); 
                }
            }
        }
        outFile.close(); 
        outFile.open(filename, ofstream::out | ofstream ::trunc); 

        for(const auto& updated: lines){
            outFile <<updated <<"\n"; 
        }
        outFile.close(); 

    }

    void printTxtFile (){
        ifstream inFile(filename); 
        for(int i = 0; i < mazeX; i++){
            for(int j = 0; j <mazeY; j++ ){
                string line; 
                getline(inFile, line); 
                cout<<line <<endl; 
            }
        }
    }

}; 