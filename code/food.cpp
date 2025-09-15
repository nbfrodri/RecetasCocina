#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm> // Para sort


#include "food.h"

using namespace std;

// Constructores

Receta::Receta() : nombre(""), id(-1), ingredientes(), instrucciones("") {}
Receta::Receta(string n, int id, map<string, int> ing, string instr) : nombre(n), id(id), ingredientes(ing), instrucciones(instr) {}

Ingrediente::Ingrediente() : nombre(""), cantidad(0), id(-1) {}
Ingrediente::Ingrediente(string n, int c, int id) : nombre(n), cantidad(c), id(id) {}

// Sobrecarga de operadores

istream& operator >> (istream& is, Receta& e) {
    string line;
    if (getline(is, line)) {
		e.ingredientes.clear(); // Limpiar ingredientes antes de leer una nueva receta
        stringstream ss(line);
        string temp;

        // Leer el nombre de la receta
        getline(ss, temp, ' ');
        e.nombre = temp;

		// Cambiar _ por espacio en el nombre de la receta
		for (size_t i = 0; i < e.nombre.length(); i++) {
			if (e.nombre[i] == '_') {
				e.nombre[i] = ' ';
			}
		}

		// Leemos los ingredientes y sus cantidades
		string ingrediente, cantidad_str;
		int cantidad;
		while (ss >> ingrediente >> cantidad_str) {

			// Cambiar _ por espacio en el nombre del ingrediente
			for (size_t i = 0; i < ingrediente.length(); i++) {
				if (ingrediente[i] == '_') {
					ingrediente[i] = ' ';
				}
			}

			cantidad = stoi(cantidad_str);
			e.ingredientes[ingrediente] = cantidad;
		}
    }
    return is;
}

ostream& operator << (ostream& os, const Receta& e) {
	os << e.nombre << ": ";
	for (const auto& ing : e.ingredientes) {
		os << ing.first << " (" << ing.second << ") | ";
	}
	cout << endl;
	return os;
}

istream& operator >> (istream& is, Ingrediente& e) {
	string line;
	if (getline(is, line)) {
		stringstream ss(line);
		string temp;

		// Leer el nombre de la receta e ignorar
		getline(ss, temp, ' ');

		// Leemos los ingredientes y sus cantidades
		string ingrediente, cantidad_str;
		int cantidad;
		while (ss >> ingrediente >> cantidad_str) {
			cantidad = stoi(cantidad_str);
			e.nombre = ingrediente;
			e.cantidad = cantidad;

			// Cambiar _ por espacio en el nombre de la receta
			for (size_t i = 0; i < e.nombre.length(); i++) {
				if (e.nombre[i] == '_') {
					e.nombre[i] = ' ';
				}
			}
		}
	}
	return is;
}

ostream& operator << (ostream& os, const Ingrediente& e) {
	os << e.nombre << ": " << e.cantidad;
	return os;
}

// Funciones

void MostrarMenu() {
	cout << "Menu de Recetas de Cocina" << endl;
	cout << "==========================" << endl;
	cout << "1. Crear receta" << endl;
	cout << "2. Mostrar receta" << endl;
	cout << "3. Mostrar todas las recetas" << endl;
	cout << "4. Mostrar todos los ingredientes" << endl;
	cout << "5. Mostrar recetas por ingredientes" << endl;
	cout << "6. Salir" << endl;
}

void InsertarReceta(const Receta& e, vector<Receta*>& recetas) {
	// Comprobar si la receta ya existe
	for (size_t i = 0; i < recetas.size(); ++i) {
		if (recetas[i]->nombre == e.nombre) {
			return; // La receta ya existe, no se inserta
		}
	}
	// Si no existe, se inserta
	Receta* receta = new Receta(e);
	recetas.push_back(receta);
}

bool LeerRecetas(const string& path, vector<Receta*>& recetas) {
	ifstream read_file(path);
	if (!read_file.is_open()) {
		cout << "Error al abrir el archivo de recetas." << endl;
		return false;
	}

	Receta temp;
	while (read_file >> temp) {
		InsertarReceta(temp, recetas);
	}

	read_file.close();
	return true;
}

void MostrarRecetas(const vector<Receta*>& recetas) {
	int i = 1;
	if (recetas.empty()) {
		cout << "No hay recetas disponibles." << endl;
		return;
	}
	for (const auto& receta : recetas) {
		cout << i << ". " << *receta << endl;
		i++;
	}
}

void AsignarIDR(vector<Receta*>& recetas) {
	// Asignar un ID a cada receta
	for (size_t i = 0; i < recetas.size(); ++i) {
		recetas[i]->id = i + 1; // ID comienza en 1
	}
}

void LimpiarRecetas(vector<Receta*>& recetas) {
	for (auto& receta : recetas) {
		delete receta; // Liberar memoria
	}
	recetas.clear(); // Limpiar el vector
}

void InsertarIngrediente(const Ingrediente& e, vector<Ingrediente*>& ingredientes) {
	// Comprobar si el ingrediente ya existe
	for (size_t i = 0; i < ingredientes.size(); ++i) {
		if (ingredientes[i]->nombre == e.nombre) {
			ingredientes[i]->cantidad += e.cantidad; // Sumar la cantidad del ingrediente existente
			return; // El ingrediente ya existe, no se inserta pero se suma la cantidad
		}
	}
	// Si no existe, se inserta
	Ingrediente* ingrediente = new Ingrediente(e);
	ingredientes.push_back(ingrediente);
}

bool LeerIngredientes(const string& path, vector<Ingrediente*>& ingredientes) {
	ifstream read_file(path);
	if (!read_file.is_open()) {
		cout << "Error al abrir el archivo de recetas." << endl;
		return false;
	}

	Ingrediente temp;
	while (read_file >> temp) {
		InsertarIngrediente(temp, ingredientes);
	}

	read_file.close();
	return true;
}

void MostrarIngredientes(const vector<Ingrediente*>& ingredientes) {
	int i = 1;
	if (ingredientes.empty()) {
		cout << "No hay ingredientes disponibles." << endl;
		return;
	}
	for (const auto& ingrediente : ingredientes) {
		cout << i << ". " << *ingrediente << endl;
		i++;
	}
}

void AsignarIDI(vector<Ingrediente*>& ingredientes) {
	// Asignar un ID a cada ingrediente
	for (size_t i = 0; i < ingredientes.size(); ++i) {
		ingredientes[i]->id = i + 1; // ID comienza en 1
	}
}

void LimpiarIngredientes(vector<Ingrediente*>& ingredientes) {
	for (auto& ingrediente : ingredientes) {
		delete ingrediente; // Liberar memoria
	}
	ingredientes.clear(); // Limpiar el vector
}

void OrdenarRecetas(vector<Receta*>& recetas, const Receta&) {
	// Ordenar recetas por nombre
	sort(recetas.begin(), recetas.end(),
		[](const Receta* a, const Receta* b) {
			return a->nombre < b->nombre;
		}
	);
}

void OrdenarIngredientes(vector<Ingrediente*>& ingredientes, const Ingrediente&) {
	// Ordenar ingredientes por nombre
	sort(ingredientes.begin(), ingredientes.end(),
		[](const Ingrediente* a, const Ingrediente* b) {
			return a->nombre < b->nombre;
		}
	);
}

int PedirNumeroReceta(size_t total_recetas) {
	int num_receta = -1;
	do {
		system("cls");
		cout << "Introduce el numero de la receta que quieres ver (1 - " << total_recetas << ") o 0 para salir: ";
		cin >> num_receta;

		if (cin.fail() || num_receta < 0 || num_receta > static_cast<int>(total_recetas)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Numero de receta no valido. Por favor, introduce un numero valido." << endl;
			system("pause");
		}
	} while (num_receta < 0 || num_receta > static_cast<int>(total_recetas));
	return num_receta;
}

bool EncuentraInstruccion(const string& path, vector<Receta*>& recetas, int id) {
	ifstream read_file(path);
	if (!read_file.is_open()) {
		cout << "Error al abrir el archivo de instrucciones." << endl;
		return false;
	}

	string line;
	while (getline(read_file, line)) {
		stringstream ss(line);
		string temp;
		string temp_n;

		// Leemos el nombre de la receta
		getline(ss, temp, ';');
		temp_n = temp;

		// Cambiar _ por espacio en el nombre de la receta
		for (size_t i = 0; i < temp_n.length(); i++) {
			if (temp_n[i] == '_') {
				temp_n[i] = ' ';
			}
		}

		// Buscamos la receta por ID
		for (size_t i = 0; i < recetas.size(); ++i) {
			if (recetas[id - 1]->nombre == temp_n) {
				getline(ss, temp, ';');
				recetas[id - 1]->instrucciones = temp;
			}
		}
	}

	read_file.close();
	return true;
}

void MostrarRecetaSeleccionada(const vector<Receta*>& recetas, int num_receta) {
	system("cls");
	cout << "Receta seleccionada: " << endl << endl;
	cout << *recetas[num_receta - 1] << endl;
	cout << "Instrucciones: " << endl;
	cout << "----------------------------------------" << endl << endl;
	cout << recetas[num_receta - 1]->instrucciones << endl << endl;
	system("pause");
}

void MostrarIngredientesSeleccionados(const vector<Ingrediente*>& lista_ingredientes, const vector<int>& ids_ingredientes) {
	cout << "Ingredientes seleccionados: " << endl << endl;
	for (int id : ids_ingredientes) {
		if (id > 0 && id <= static_cast<int>(lista_ingredientes.size())) {
			cout << "ID: " << id << " - Ingrediente: " << lista_ingredientes[id - 1]->nombre << endl;
		}
	}
	cout << endl << "====================================" << endl;
	cout << "Total ingredientes seleccionados: " << ids_ingredientes.size();
	cout << endl << "====================================" << endl << endl;
}

int PedirIDIngrediente(const vector<Ingrediente*>& lista_ingredientes) {
	int num_ingrediente = -1;
	cout << "Selecciona un ingrediente por su ID (1 - " << lista_ingredientes.size() << ") o presiona 0 para salir: " << endl << endl;
	cin >> num_ingrediente;
	if (cin.fail() || num_ingrediente < 0 || num_ingrediente > static_cast<int>(lista_ingredientes.size())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "ID de ingrediente no valido. Por favor, introduce un ID valido." << endl;
		system("pause");
		return -1;
	}
	return num_ingrediente;
}

bool IngredienteYaSeleccionado(int id, const vector<int>& ids_ingredientes) {
	for (int seleccionado : ids_ingredientes) {
		if (seleccionado == id) return true;
	}
	return false;
}

bool PreguntarSeleccionarOtroIngrediente() {
	char respuesta;
	bool respuesta_valida = false;
	do {
		cout << "Quieres seleccionar otro ingrediente? (s/n): ";
		cin >> respuesta;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Respuesta no valida. Por favor, introduce 's' o 'n'." << endl;
			system("pause");
			system("cls");
		}
		else if (respuesta == 's' || respuesta == 'S') {
			return true;
		}
		else if (respuesta == 'n' || respuesta == 'N') {
			return false;
		}
		else {
			cout << endl << "Respuesta no valida. Por favor, introduce 's' o 'n'." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			system("cls");
		}
	} while (!respuesta_valida);
	return false;
}

bool SeleccionarIngredientesPorID(const vector<Ingrediente*>& lista_ingredientes, vector<int>& ids_recetas) {
	bool terminar = false;
	bool cancelado = false;
	do {
		system("cls");
		MostrarIngredientesSeleccionados(lista_ingredientes, ids_recetas);
		int num_ingrediente = PedirIDIngrediente(lista_ingredientes);

		if (num_ingrediente == -1) {
			continue; // Entrada inválida, vuelve a pedir
		}
		else if (num_ingrediente == 0) {
			cancelado = true;
			break; // El usuario quiere salir
		}
		else if (IngredienteYaSeleccionado(num_ingrediente, ids_recetas)) {
			cout << "\nYa has seleccionado este ingrediente. Por favor, selecciona otro." << endl << endl;
			system("pause");
		}
		else {
			ids_recetas.push_back(num_ingrediente);
			system("cls");
			cout << "Has seleccionado el ingrediente: " << lista_ingredientes[num_ingrediente - 1]->nombre << endl << endl;
			terminar = !PreguntarSeleccionarOtroIngrediente();
		}
	} while (!terminar);
	return cancelado;
}

void FiltrarRecetasPorIngrediente(const vector<Receta*>& recetas, const vector<int>& ids_ingredientes, vector<Receta*>& recetas_filtradas, const vector<Ingrediente*>& lista_ingredientes) {
	recetas_filtradas.clear(); // Limpiar el vector de recetas filtradas
	// Iterar sobre las recetas
	for (const auto& receta : recetas) {
		bool contiene_ingrediente = false;
		// Verificar si la receta contiene alguno de los ingredientes seleccionados
		for (int id : ids_ingredientes) {
			if (id > 0 && id <= static_cast<int>(lista_ingredientes.size())) {
				const string& nombre_ingrediente = lista_ingredientes[id - 1]->nombre;
				if (receta->ingredientes.find(nombre_ingrediente) != receta->ingredientes.end()) {
					contiene_ingrediente = true;
					break; // No necesitamos seguir buscando, ya encontramos un ingrediente
				}
			}
		}
		// Si la receta contiene al menos un ingrediente seleccionado, la agregamos a las recetas filtradas
		if (contiene_ingrediente) {
			recetas_filtradas.push_back(receta);
		}
	}
}