#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "TxtFile.h"

class Laberinto
{
	
	public:
		int t = 0;
		int positionX, positionY, row, columns;
		vector<vector<string>> mainMaze;
		TxtFile ResultsFile; 

		/**Usuario crea una matriz. Los parámetros son las filas y columnas de tipo int*/
		vector<vector<string>> CreateMaze(int row, int columns) {
			vector<vector<string>> maze(row, vector<string>(columns));
			string obj;
			cout << "A continuaci�n digite un punto(.) para representar caminos, " 
				<< "X(equis) para representar obst�culos "
				<< "y t para representar un tesoro" << endl;
			
			/**Recorre la matriz para guardar los objetos x, t o .*/
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < columns; j++) {
					cout << "Ingrese la figura para la fila: " << i << " y columna: " << j << ": ";
					cin >> obj;

					/**Conteo de tesoros*/
					if (obj == "t") {
						t++;
					}
					cout << endl;
					/**Ubicación de x, t o . en la matriz*/
					maze[i][j] = obj;
				}

			}
			/** Guarda la matriz inicial */
			mainMaze = maze;
			/**Creación del archivo de texto */
    		ResultsFile.createFile(); 

			/**Ingreso de matriz en el archivo de texto*/
			ResultsFile.addMazeToFile(mainMaze); 
			
			/*Imprime la matriz*/
			PrintMaze(mainMaze, row);
			return maze;
		}
		
		void PrintMaze(vector<vector<string>> maze, int row) {

			cout<<"------------------------------------" <<endl; 
			cout<<"Este es el laberinto" <<endl; 
			cout<<"------------------------------------" <<endl; 

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < maze[i].size(); j++) {
					cout << maze[i][j];
				}
				cout << endl;
			}
			cout<<"------------------------------------" <<endl; 
		}

		void Play(vector<vector<string>> maze, int row) {
			bool flag = false;
			bool out = false;
			int positionX, positionY, option, previous;
			int treasures = 0;
			do {
				cout << " " << endl;
				PrintMaze(maze, row);
				cout << " " << endl;
				cout << "Acontinuaci�n ingrese las posiciones para comenzar a jugar (Y)" << endl;
				cout << "Ingrese la posici�n X: ";
				cin >> positionX;
				cout << "Ingrese la posici�n Y: ";
				cin >> positionY;
				if (maze[positionX][positionY] != ".") {
					cout << "Debe comenzar en una posici�n diferente de 'X' o 't'" << endl;
				}
				else {
					maze[positionX][positionY] = "Y";
					out = true;
				}
			} while (!out);

			do {
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < maze[i].size(); j++) {

						cout << maze[i][j];
					}
					cout << endl;
				}
				cout << "Debe moverse a trav�s de la fila o de la columna, digite: " << endl;
				cout << "1. Si se desea mover a trav�s de la fila\n2. Si se desea mover a trav�s de la columna\n3. Salir" << endl;
				cout << "Escoja una opci�n: ";
				cin >> option;
				if (option == 1) {
					cout << "Ingrese la columna a la que desea moverse: ";
					previous = positionY;
					cin >> positionY;
					if (maze[positionX][positionY] == "x") {
						cout << "La posici�n que ingreso es inv�lida"<<endl;
						positionY = previous;
					}
					else {
						if (maze[positionX][positionY] == "t") {
							cout << "�Usted encontr� un tesoro!" << endl;
							cout << endl;
							treasures++;
						}
						maze[positionX][previous] = ".";
						maze[positionX][positionY] = "Y";
					}
				}
				if (option == 2) {
					cout << "Ingrese la fila a la que desea moverse: ";
					previous = positionX;
					cin >> positionX;
					if (maze[positionX][positionY] == "x") {
						cout << "La posici�n que ingreso es inv�lida"<<endl;
						positionX = previous;
					}
					else {
						if (maze[positionX][positionY] == "t") {
							cout << "�Usted encontr� un tesoro!" << endl;
							cout << endl;
							treasures++;
						}
						maze[previous][positionY] = ".";
						maze[positionX][positionY] = "Y";
					}

				}
				if (treasures == t) {
					cout << "Todos los tesoros fueron encontrados" << endl;
					option = 3;
				}
			} while (option < 3);			
				
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
					Play(mainMaze, row);
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




