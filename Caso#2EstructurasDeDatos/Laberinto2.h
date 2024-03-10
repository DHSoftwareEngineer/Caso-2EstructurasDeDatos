#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "TxtFile.h"

class Laberinto2
{
	
	public:
		int t = 0;
		int positionX, positionY, row, columns;
		vector<vector<Casilla>> mainMaze;
		TxtFile ResultsFile;

		/**Usuario crea una matriz. Los parámetros son las filas y columnas de tipo int*/
		vector<vector<Casilla>> CreateMaze(int row, int columns) {
            vector<vector<Casilla>> maze(row, vector<Casilla>(columns));
            mainMaze = maze; 
			string obj;
			cout << "A continuaci�n digite un punto(.) para representar caminos, " 
				<< "X(equis) para representar obst�culos "
				<< "y t para representar un tesoro" << endl;
			
			/**Recorre la matriz para guardar los objetos x, t o .*/
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < columns; j++) {
					cout << "Ingrese la figura para la fila: " << i << " y columna: " << j << ": ";
					cin >> obj;
                    Casilla cell = {obj, false, false, false, false, false};
					cout << endl;
					/**Ubicación de x, t o . en la matriz*/
					mainMaze[i][j] = cell;
				}

			}
			
			/**Creación del archivo de texto */
    		ResultsFile.createFile(); 

			/**Ingreso de matriz en el archivo de texto*/
			ResultsFile.addMazeToFile(mainMaze); 
			
			return mainMaze;
		}
		
		void PrintMaze(vector<vector<Casilla>> maze, int row) {

			cout<<"------------------------------------" <<endl; 
			cout<<"Este es el laberinto" <<endl; 
			cout<<"------------------------------------" <<endl; 

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < maze[i].size(); j++) {
					cout << maze[i][j].shape;
				}
				cout << endl;
			}
			cout<<"------------------------------------" <<endl; 
		}

		void Play() {
			int positionX, positionY;

            cout << " " << endl;
            cout << "A continuaci�n ingrese las posiciones para comenzar a jugar" << endl;
            cout << "Ingrese la posici�n X: ";
            cin >> positionX;
            cout << "Ingrese la posici�n Y: ";
            cin >> positionY;

            if(mover(positionX, positionY)){
                cout << "Sí se puede encontrar un tesoro a partir de la posición: " 
                    <<to_string(positionX)
                    << " " 
                    <<to_string(positionY) <<endl;
            }else{
                    cout << "No se puede encontrar un tesoro a partir de la posición: " 
                    <<to_string(positionX)
                    << " " 
                    <<to_string(positionY) <<endl; 
            }
            
            /*Limpiar variable de la matriz para que se pueda recorrer nuevamente*/
            for (int i = 0; i < row; i++) {
				for (int j = 0; j < mainMaze[i].size(); j++) {
					 mainMaze[i][j].visited = false;
				}
				
			}
            

		}

        bool mover(int positionX, int positionY) {
            if(positionX >=mainMaze.size() || positionX < 0 || positionY >= mainMaze[0].size() || positionY < 0) {
                return false;
            }
            if(mainMaze[positionX][positionY].visited) {
                return false;
            }
            if (mainMaze[positionX][positionY].shape == "t") {
                ResultsFile.writeResult(positionX, positionY, true); 
                    cout << "Aquí hay un tesoro: " 
                    <<to_string(positionX)
                    << " " 
                    <<to_string(positionY) <<endl; 
                return true;
            }
            else if(mainMaze[positionX][positionY].shape == "x") {
                ResultsFile.writeResult(positionX, positionY, false); 
                return false;
            }
            
            mainMaze[positionX][positionY].visited = true;
            //mover a la derecha
            bool hayTesoro = false;
            hayTesoro = mover(positionX + 1, positionY);
            if(hayTesoro){
                ResultsFile.writeResult(positionX, positionY, true); 
                return hayTesoro;
            } 
            //mover abajo
            hayTesoro = mover(positionX, positionY + 1);
            if(hayTesoro){
                ResultsFile.writeResult(positionX, positionY, true); 
                return hayTesoro;
            } 
            //mover izquierda
            hayTesoro = mover(positionX - 1, positionY);
            if(hayTesoro){
                ResultsFile.writeResult(positionX, positionY, true); 
                return hayTesoro;
            } 
             //mover arriba
            hayTesoro = mover(positionX, positionY - 1);
            if(hayTesoro){
                ResultsFile.writeResult(positionX, positionY, true); 
                return hayTesoro;
            } 
            ResultsFile.writeResult(positionX, positionY, false); 
            return false;
        }

		void Menu() {
			int option;
			
			vector<vector<string>> maze;
			cout << "Ingrese la cantidad de filas del laberinto: ";
			cin >> row;
			cout << "Ingrese la cantidad de columnas del laberinto: ";
			cin >> columns;
			do {
				cout << "\n1. Crear laberinto" << endl;
				cout << "2. Jugar" << endl;
				cout << "3. Información del archivo de texto" << endl;
				cout << "4. Conclusiones" << endl;
				cout << "5. Salir" << endl;


				cout << "Escoja una opci�n: ";
				cin >> option;
				switch (option) {
				case 1:
					CreateMaze(row, columns);
					break;
				case 2:
					Play();
					break;
				case 3:
					ResultsFile.printTxtFile();
					break;
				case 4:
					cout<<endl; 
					cout<<"Conclusiones"<<endl; 
					cout<<"1. Para la resolución de un problema es importante analizar el contexto y crear un logaritmo que contemple todas las aristas posibles." 
							<<"En el caso particular de este problema, es vital considerar que el agente podría desplazarse en cuatro sentidos, para evitar dar falsos negativos."<<endl;
					cout<<"2. La naturaleza de los archivos de texto, no permiten modificar información."
							<<"Por tanto, para su modificación se debe guardar en memoria temporal la información del archivo, "
							<<"hacer las modificaciones y luego guardar la información modificada en el archivo nuevamente."<<endl; 
					cout<<"3. El uso de matrices es muy útil, porque nos permite tener, presentar y manipular objetos que están relacionados. "
							<<"Además, las matrices son ideales para las representaciones gráficas como juegos de tableros. "<<endl; 

					break;
				}
			} while (option < 5);
		}

	
};




