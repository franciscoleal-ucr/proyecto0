#pragma once
#include <string>
using namespace std;

/** @brief Implements a representation of a point in 3D.

    Detailed description here.
    @author Rolando Murillo Perez, Miguel Chavez Bejarano, Francisco Leal Tovar
    @date January 2019
    */
class Cell;//pasa que si no lo ponemos el compilador no encuentra a Cell al leer lo que contiene Unit, y lo necesita

class Unit{
	public:
	int id;
	string unodos;
	string type;
	string name;
	int maxHitPoints;
	int hitpoints;
	int atk;
	int defense;
	int range;
	int level;
	int experience;
	int movement;
	int posx;
	int posy;
  string vivoomuerto;
	static int cost;
	static int idCount;
	bool move(Cell *celdaactual,Cell *celdallegada,int nuevax,int nuevay);
	bool attack(Unit *objetivo,Cell *celdaenemigo);
	
	void setAtributos(int id,	string vivoomuerto,string type,string name,int maxHitPoints,int hitpoints,int attack,int defense,int range,int level,int experience,int movement);
};
class Cell{//maneja una posicion del campo de juego, representa o maneja 2 de los estados que tiene la celda
   public:
   bool passable;
   Unit *army;
   string encasilla; //creado por mi para uso en void printInfo()
   void printInfo();
   void setAtributos(bool passable,Unit *army);
};

class Field{//representa el conjunto de todas las celdas del campo de juego
	public:
	int cols;//columnas
	int rows;//filas
	Cell *playfield[6][6];//ocupo definirle el tamaño,no puedo ponerle cols y rows porque cuando quiere crear la matriz no tiene los valores reales para hacerlo
	void creacionCampo();
	void printCampo();
};

	
class Lancer : public Unit {
	public:
	int cost;
	//int Unit::cost;
	void setcost();
};

class Cavalry : public Unit {
	public:
	int cost;
    //int Unit::cost;
    void setcost();
	
};

class Archer : public Unit {
	public:
	int cost;
	//int Unit::cost;
	void setcost();
};

class Player{//esta clase representa a los jugadores
	public:
	int maxCost;
	Unit *army;
	Field *playfield;
	string name;
	int numerodejugador;
	int score;
	void createArmy(int UnidadesLancer, int UnidadesCavalry,int UnidadesArcher);
	void createPlayfield(Field *campo);
	int cantidadEjercito;
	void play();//contiene la logica de un turno del jugador
};
	
class UI{
    public:
    void guardarJuego(Player *jugador1, Player *jugador2);
    void traerJuegoGuardado(Player *jugador1, Player *jugador2);
};
