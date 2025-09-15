#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "food.h"

using namespace std;

int main()
{
	string dir = "P:/EspacioRodrigo/Docs/RecetasCocina/files";
	string path_recetas = dir + "/recetas.txt";
	string path_instrucciones = dir + "/instrucciones.csv";

	bool salir = false;

	vector<Receta*> lista_recetas;
	vector<Ingrediente*> lista_ingredientes;

	do {
		int opcion = 0;

		system("cls");
		MostrarMenu();
		cin >> opcion;

		if (cin.fail() || opcion < 1 || opcion > 6) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Opcion no valida. Por favor, introduce un numero valido (1 - 6)." << endl;
			system("pause");
			system("cls");
		}

		switch (opcion) {
		case 1:
		{

		}
		break;
		case 2:
		{
			// Leemos las recetas del archivo
			try {
				if (!LeerRecetas(path_recetas, lista_recetas)) {
					throw runtime_error("");
				}
			}

			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				return 1;
			}
			
			// Ordenamos las recetas
			OrdenarRecetas(lista_recetas, Receta());
			AsignarIDR(lista_recetas);

			// Pedimos un número de receta al usuario
			int num_receta = PedirNumeroReceta(lista_recetas.size());

			// Si el usuario ha elegido salir, no hacemos nada
			if (num_receta == 0) {
				LimpiarRecetas(lista_recetas);
				continue;
			}

			// Buscamos en el archivo de instrucciones la receta seleccionada
			try {
				if (!EncuentraInstruccion(path_instrucciones, lista_recetas, num_receta)) {
					throw runtime_error("");
				}
			}

			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				return 1;
			}

			// Mostramos la receta seleccionada
			MostrarRecetaSeleccionada(lista_recetas, num_receta);

			// Liberamos la memoria de las recetas
			LimpiarRecetas(lista_recetas);
		}
		break;
		case 3:
		{
			// Leemos las recetas del archivo
			try {
				if (!LeerRecetas(path_recetas, lista_recetas)) {
					throw runtime_error("");
				}
			}

			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				return 1;
			}

			// Mostramos las recetas
			system("cls");
			OrdenarRecetas(lista_recetas, Receta());
			MostrarRecetas(lista_recetas);

			// Liberamos la memoria de las recetas
			LimpiarRecetas(lista_recetas);
			system("pause");
		}
		break;
		case 4:
		{
			// Leemos los ingredientes del archivo
			try {
				if (!LeerIngredientes(path_recetas, lista_ingredientes)) {
					throw runtime_error("");
				}
			}

			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				return 1;
			}

			// Mostramos los ingredientes
			system("cls");
			OrdenarIngredientes(lista_ingredientes, Ingrediente());
			MostrarIngredientes(lista_ingredientes);

			// Liberamos la memoria de los ingredientes
			LimpiarIngredientes(lista_ingredientes);
			system("pause");
		}
		break;
		case 5:
		{
			vector<Receta*> recetas_por_ingrediente;
			vector<int> ids_ingredientes;

			// Leemos los ingredientes del archivo
			try {
				if (!LeerIngredientes(path_recetas, lista_ingredientes)) {
					throw runtime_error("");
				}
			}

			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				return 1;
			}

			// Ordenamos los ingredientes y asignamos IDs
			OrdenarIngredientes(lista_ingredientes, Ingrediente());
			AsignarIDI(lista_ingredientes);

			// Pedimos al usuario los ingredientes
			if (SeleccionarIngredientesPorID(lista_ingredientes, ids_ingredientes)) {
				LimpiarIngredientes(lista_ingredientes);
				break; // Sale del case 5 y vuelve al menú principal
			}

			// Leemos las recetas del archivo
			try {
				if (!LeerRecetas(path_recetas, lista_recetas)) {
					throw runtime_error("");
				}
			}

			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				return 1;
			}

			// Ordenamos las recetas y asignamos IDs
			OrdenarRecetas(lista_recetas, Receta());
			AsignarIDR(lista_recetas);

			// TODO: NO ESTA BIEN
			// Buscamos en las recetas los ingredientes seleccionados y si contienen los ingredientes seleccionados lo metemos al vector de recetas_por_ingrediente
			FiltrarRecetasPorIngrediente(lista_recetas, ids_ingredientes, recetas_por_ingrediente, lista_ingredientes);

			// Mostramos las recetas filtradas
			system("cls");
			if (recetas_por_ingrediente.empty()) {
				cout << "No se encontraron recetas con los ingredientes seleccionados." << endl;
			}
			else {
				cout << "Recetas que contienen los ingredientes seleccionados:" << endl;
				for (const auto& receta : recetas_por_ingrediente) {
					cout << receta->nombre << endl;
				}
			}
			system("pause");

			// Liberamos la memoria de los ingredientes y recetas
			LimpiarIngredientes(lista_ingredientes);
			LimpiarRecetas(lista_recetas);
		}
		break;
		case 6:
			salir = true;
			break;
	}

	} while (salir == false);

	return 0;
}
