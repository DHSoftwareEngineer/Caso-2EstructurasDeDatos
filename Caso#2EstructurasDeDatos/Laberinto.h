#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "TxtFile.h"

class Laberinto
{

public:
	int t = 0; // Contador de tesoros
	int positionX, positionY, row, columns; // Variables para la posición actual y dimensiones del laberinto
	vector<vector<string>> mainMaze; // Laberinto principal
	TxtFile ResultsFile; // Objeto para manejar archivos de texto

	/**
	 * Crea un laberinto con las dimensiones dadas por los parámetros 'row' y 'columns'.
	 * Devuelve la matriz del laberinto creado.
	 */
	vector<vector<string>> CreateMaze(int row, int columns) {
		vector<vector<string>> maze(row, vector<string>(columns)); // Crea una matriz con las dimensiones dadas
		string obj; // Variable para almacenar el objeto (camino, obstáculo, tesoro)
		cout << "A continuación digite un punto (.) para representar caminos, "
			<< "X (equis) para representar obstáculos "
			<< "y t para representar un tesoro" << endl;

		/** Recorre la matriz para asignar los objetos a cada posición */
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < columns; j++) {
				cout << "Ingrese la figura para la fila: " << i << " y columna: " << j << ": ";
				cin >> obj;

				// Conteo de tesoros
				if (obj == "t") {
					t++;
				}
				cout << endl;

				// Asigna el objeto a la posición en la matriz
				maze[i][j] = obj;
			}
		}

		// Guarda la matriz inicial
		mainMaze = maze;

		// Crea el archivo de texto
		ResultsFile.createFile();

		// Guarda la matriz en el archivo de texto
		ResultsFile.addMazeToFile(mainMaze);

		// Imprime la matriz
		PrintMaze(mainMaze, row);

		// Devuelve la matriz creada
		return maze;
	}

	// Imprime el laberinto
	void PrintMaze(vector<vector<string>> maze, int row) {
		cout << "------------------------------------" << endl;
		cout << "Este es el laberinto" << endl;
		cout << "------------------------------------" << endl;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < maze[i].size(); j++) {
				cout << maze[i][j];
			}
			cout << endl;
		}
		cout << "------------------------------------" << endl;
	}

	// Función principal para jugar en el laberinto
	void Play(vector<vector<string>> maze, int row) {
		bool flag = false;
		bool out = false;
		int positionX, positionY, option, previous;
		int treasures = 0;

		// Solicita las posiciones iniciales al usuario
		do {
			cout << " " << endl;
			PrintMaze(maze, row);
			cout << " " << endl;
			cout << "A continuación ingrese las posiciones para comenzar a jugar (Y)" << endl;
			cout << "Ingrese la posición X: ";
			cin >> positionX;
			cout << "Ingrese la posición Y: ";
			cin >> positionY;

			// Verifica que la posición inicial sea válida
			if (maze[positionX][positionY] != ".") {
				cout << "Debe comenzar en una posición diferente de 'X' o 't'" << endl;
			}
			else {
				maze[positionX][positionY] = "Y"; // Marca la posición inicial del jugador
				out = true;
			}
		} while (!out);

		// Loop principal del juego
		do {
			// Imprime el laberinto
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < maze[i].size(); j++) {
					cout << maze[i][j];
				}
				cout << endl;
			}

			// Menú de opciones para moverse
			cout << "Debe moverse a través de la fila o de la columna, digite: " << endl;
			cout << "1. Si se desea mover a través de la fila\n2. Si se desea mover a través de la columna\n3. Salir" << endl;
			cout << "Escoja una opción: ";
			cin >> option;

			if (option == 1) {
				// Movimiento en la fila
				cout << "Ingrese la columna a la que desea moverse: ";
				previous = positionY;
				cin >> positionY;
				if (maze[positionX][positionY] == "x") {
					cout << "La posición que ingresó es inválida" << endl;
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
				// Movimiento en la columna
				cout << "Ingrese la fila a la que desea moverse: ";
				previous = positionX;
				cin >> positionX;
				if (maze[positionX][positionY] == "x") {
					cout << "La posición que ingresó es inválida" << endl;
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

			// Verifica si se han encontrado todos los tesoros
			if (treasures == t) {
				cout << "Todos los tesoros fueron encontrados" << endl;
				option = 3; // Sale del juego
			}
		} while (option < 3);

	}

	// Menú principal del juego
	void Menu() {
		int option;

		vector<vector<string>> maze;
		cout << "Ingrese la cantidad de filas del laberinto: ";
		cin >> row;
		cout << "Ingrese la cantidad de columnas del laberinto: ";
		cin >> columns;

		// Loop principal del menú
		do {
			cout << "\n1. Crear laberinto" << endl;
			cout << "2. Jugar" << endl;
			cout << "3. Información del archivo de texto" << endl;
			cout << "4. Conclusiones" << endl;
			cout << "5. Salir" << endl;

			cout << "Escoja una opción: ";
			cin >> option;
			switch (option) {
			case 1:
				// Crea un nuevo laberinto
				CreateMaze(row, columns);
				break;
			case 2:
				// Inicia el juego
				Play(mainMaze, row);
				break;
			case 3:
				// Muestra la información del archivo de texto
				ResultsFile.printTxtFile();
				break;
			case 4:
				// Muestra las conclusiones
				cout << endl;
				cout << "Conclusiones" << endl;
				cout << "Conclusiones:" << endl;
				cout << "1. Es fundamental analizar el contexto y diseñar un algoritmo que considere todas las posibles situaciones. En este problema, fue crucial contemplar los movimientos en cuatro direcciones para evitar errores." << endl;
				cout << "2. Los archivos de texto son estáticos, lo que significa que no se pueden modificar directamente. Para alterar su contenido, es necesario cargar la información en memoria temporalmente, realizar las modificaciones y luego guardar los cambios en el archivo." << endl;
				cout << "3. El uso de matrices es eficaz para organizar, visualizar y manipular datos relacionados. En particular, son ideales para representar gráficamente estructuras como laberintos en juegos." << endl;
				break;
			}
		} while (option < 5);
	}
};
