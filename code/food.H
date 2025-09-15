#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

// Struct

struct Receta {
	string nombre;
	int id;
	map<string, int> ingredientes; // clave: nombre del ingrediente, valor: cantidad
	string instrucciones; // Instrucciones de la receta

	Receta();
	Receta(string n, int id, map<string, int> ing, string instrucciones);

	friend istream& operator >> (istream& is, Receta& e);
	friend ostream& operator << (ostream& os, const Receta& e);
};

struct Ingrediente {
	string nombre;
	int cantidad;
	int id;

	Ingrediente();
	Ingrediente(string n, int c, int id);

	friend istream& operator >> (istream& is, Ingrediente& e);
	friend ostream& operator << (ostream& os, const Ingrediente& e);
};

// Funciones

void MostrarMenu();

void InsertarReceta(const Receta&, vector<Receta*>& recetas);
bool LeerRecetas(const string& path, vector<Receta*>& recetas);
void MostrarRecetas(const vector<Receta*>& recetas);
void AsignarIDR(vector<Receta*>& recetas);
void LimpiarRecetas(vector<Receta*>& recetas);
void OrdenarRecetas(vector<Receta*>& recetas, const Receta&);

void InsertarIngrediente(const Ingrediente&, vector<Ingrediente*>& ingredientes);
bool LeerIngredientes(const string& path, vector<Ingrediente*>& ingredientes);
void MostrarIngredientes(const vector<Ingrediente*>& ingredientes);
void AsignarIDI(vector<Ingrediente*>& ingredientes);
void LimpiarIngredientes(vector<Ingrediente*>& ingredientes);
void OrdenarIngredientes(vector<Ingrediente*>& ingredientes, const Ingrediente&);

int PedirNumeroReceta(size_t total_recetas);