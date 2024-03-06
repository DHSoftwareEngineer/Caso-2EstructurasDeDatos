#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Laberinto
{
	
	public:
		int t = 0;
		int positionX, positionY, row, columns;
		vector<vector<string>> mainMaze;

		vector<vector<string>> CreateMaze(int row, int columns) {
			vector<vector<string>> maze(row, vector<string>(columns));
			string obj;
			cout << "Acontinuación digite un punto(.) para representar caminos, X(equis) para representar obstáculos y t para representar un tesoro" << endl;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < columns; j++) {
					cout << "Ingrese la figura para la fila: " << i << " y columna: " << j << ": ";
					cin >> obj;
					if (obj == "t") {
						t++;
					}
					cout << endl;

					maze[i][j] = obj;
				}

			}
			mainMaze = maze;
			PrintMaze(mainMaze, row);
			return maze;
		}
		
		void PrintMaze(vector<vector<string>> maze, int row) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < maze[i].size(); j++) {
					cout << maze[i][j];
				}
				cout << endl;
			}
			
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
				cout << "Acontinuación ingrese las posiciones para comenzar a jugar (Y)" << endl;
				cout << "Ingrese la posición X: ";
				cin >> positionX;
				cout << "Ingrese la posición Y: ";
				cin >> positionY;
				if (maze[positionX][positionY] != ".") {
					cout << "Debe comenzar en una posición diferente de 'X' o 't'" << endl;
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
					cout << "Debe moverse a través de la fila o de la columna, digite: " << endl;
					cout << "1. Si se desea mover a través de la fila\n2. Si se desea mover a través de la columna\n3. Salir" << endl;
					cout << "Escoja una opción: ";
					cin >> option;
					if (option == 1) {
						cout << "Ingrese la columna a la que desea moverse: ";
						previous = positionY;
						cin >> positionY;
						if (maze[positionX][positionY] == "x") {
							cout << "La posición que ingreso es inválida"<<endl;
							positionY = previous;
						}
						else {
							if (maze[positionX][positionY] == "t") {
								cout << "¡Usted encontró un tesoro!" << endl;
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
							cout << "La posición que ingreso es inválida"<<endl;
							positionX = previous;
						}
						else {
							if (maze[positionX][positionY] == "t") {
								cout << "¡Usted encontró un tesoro!" << endl;
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
				cout << "3. Salir" << endl;
				cout << "Escoja una opción: ";
				cin >> option;
				switch (option) {
				case 1:
					CreateMaze(row, columns);
					break;
				case 2:
					Play(mainMaze, row);
					break;
				}
			} while (option < 3);
		}
};



