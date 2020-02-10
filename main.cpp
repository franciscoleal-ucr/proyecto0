#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <typeinfo>//para comprobacion de tipos de variables
#include <string>
#include "proyecto0.h"

using namespace std;
int suma1, suma2;
void Unit::setAtributos(int id,	string vivoomuerto,string type,string name,int maxHitPoints,int hitpoints,int attack,int defense,int range,int level,int experience,int movement){
	this->id=id;
	this->type=type;
	this->name=name;
	this->maxHitPoints=maxHitPoints;
	this->hitpoints=hitpoints;
	this->atk=attack;
	this->defense=defense;
	this->range=range;
	this->level=level;
	this->experience=experience;
	this->movement=movement;
  this->vivoomuerto= vivoomuerto;
	
}
bool Unit::move(Cell *celdaactual,Cell *celdallegada,int nuevax,int nuevay){//celda a la que quiere llegar y en la que estaba (cuando se va se borra) y las coordenadas ingresadas por el usuario de donde quiere ir 

	if(celdallegada->passable==true){
		//vamo a moverno
		//me parece que funciona para los 3 tipos de movimiento, hacer prueba mental
		//this->posx + this->movement >= nuevax || this->posx- this->movement <= nuevax
		if(nuevax>=this->posx - this->movement   &&  nuevax<=this->posx+this->movement){
			if(nuevay>=this->posy - this->movement   &&  nuevay<=this->posy+this->movement){
			//check, si se puede mover ahi
			this->posy=nuevay;
			this->posx=nuevax;
			celdaactual->passable= true;
			celdallegada->passable = false;
			celdallegada->army = celdaactual->army;//le guardo a la celdallegada la unidad que ahora tiene
			celdaactual->army=NULL;//ya de aqui la unidad se fue, entonces la quito
			celdaactual->encasilla= "   -   ";
			celdallegada->encasilla="  "+this->type + this->unodos +" ";
            return true;
		    }
		    else{return false;}
		} else{return false;}
	}
	else{//no le da el movimiento para llegar donde quiere ir
		return false;
	}
	    
}


bool Unit::attack(Unit *objetivo,Cell *celdaEnemigo){//le agregue que reciba la celda del enemigo por si en caso se muere limpiar esa celda
    if(celdaEnemigo->army!=NULL){
	if(objetivo->posx >=this->posx - this->range   &&  objetivo->posx <= this->posx+this->range ){
		if(objetivo->posy >= this->posy - this->range   &&  objetivo->posy <= this->posy+  this->range ){
			//check, si se puede atacar ahi
			int resultado = this->atk - objetivo->defense;
			objetivo->hitpoints= objetivo->hitpoints - resultado;
			if(objetivo->hitpoints<0){//caso en que se muere el enemigo
				this->experience=this->experience+1;
				if(this->experience== 2*this->level){
					this->level=this->level+1;
					}
				this->atk= this->atk +this->atk*0.25;
				this->defense=this->defense + this->defense*0.25;
				this->maxHitPoints=this->maxHitPoints + this->maxHitPoints*0.25;
				this->hitpoints=this->hitpoints+ this->hitpoints*0.25;
				this->range=this->range + this->range*0.25;
				this->movement=this->movement+ this->movement*0.25;
				this->experience=0;
				celdaEnemigo->passable=true;
				celdaEnemigo->army=NULL;
				celdaEnemigo->encasilla = "   -   " ;
				objetivo=NULL;
				}
            return true;
		 }
		 else{return false;}
     }
     
     else{return false;}//no se puede atacar
     }
     else{
		 return true;//ataco, pero pifio
		 cout<<"Acaba de atacar a una celda sin Unidad \n";
		 }
	
}

void Cell::setAtributos(bool passable,Unit *army){
	this->passable=passable;
	this->army= army;	
}

void Cell::printInfo(){
	if(this->passable == 1){
		cout<<"El terreno en esta celda es franqueable. \n";
		}
	else{
		cout<<"El terreno en esta celda no es franqueable, hay una unidad tipo:   "<< army->type << "\n";
		}
}
void Field::printCampo(){
	
	for(int i=0;i<6;i++){
		for(int j=0; j<6;j++){
			cout << this->playfield[i][j]->encasilla;
			}
			cout <<"\n";
		}
}

void Field::creacionCampo(){
	for(int i=0;i<6;i++){
	for(int j=0; j<6;j++){
		this->playfield[i][j]=new Cell();
		this->playfield[i][j]->encasilla = "   -   ";
		}
	}
}

void Lancer::setcost(){	
	Lancer::cost = 3;  //esta dando problemas esta declaración de este lado.
	}
	
void Cavalry::setcost(){
	Cavalry::cost = 5;
	}
	
void Archer::setcost(){
    Archer::cost = 4;
	}
void Player::createArmy(int UnidadesLancer, int UnidadesCavalry,int UnidadesArcher){
	    
	    
	    
	    
     	Lancer *lancer = new Lancer();
     	Cavalry *cavalry = new Cavalry();
     	Archer *archer = new Archer();
     	lancer->setcost();
     	cavalry->setcost();
     	archer->setcost();
     	


		/**
		 * en el .h tenia la tipica declaracion de vector<Unit> *army; porque queria rellena el vector haciendo push_back, he decidido cambiar esa idea
		 * 
		 * for(int i=0; i< UnidadesLancer; i++){
			
				this->army->push_back(*(new Unit()));//antes sin el asterisco le pasaba una direccion 
             
			}
		for(int i=0; i< UnidadesCavalry; i++){
                this->army->push_back(*(new Cavalry()));//antes sin el asterisco le pasaba una direccion 
			}
		for(int i=0; i< UnidadesArcher; i++){
				this->army->push_back(*(new Archer()));//antes sin el asterisco le pasaba una direccion 
			}*/
		
		this->army = new Unit[UnidadesLancer+ UnidadesCavalry+ UnidadesArcher + 1];//defino tamano del array
        for(int i=0; i< UnidadesLancer; i++){
			Unit *unidadL = new Lancer();
			unidadL->setAtributos(i,"vivo"," L "," Lancer ",20,20,7,7,1,1,0,1);//int id,string type,string name,int maxHitPoints,int hitpoints,int attack,int defense,int range,int level,int movement
			this->army[i]=*unidadL;
			}
        for(int i=UnidadesLancer; i< UnidadesCavalry+UnidadesLancer; i++){
			Unit *unidadC = new Cavalry();
			unidadC->setAtributos(i,"vivo"," C "," Cavalry ",25,25,15,5,1,1,0,3);
			this->army[i]=*unidadC;
			}
        for(int i=UnidadesCavalry+UnidadesLancer; i< UnidadesCavalry+UnidadesLancer+ UnidadesArcher; i++){
			Unit *unidadA = new Archer();
			unidadA->setAtributos(i,"vivo"," A "," Archer ",15,15,9,5,3,1,0,1);
			this->army[i]=*unidadA;
			}
	    
	   
		
}

void Player::createPlayfield(Field *campo){
    //esto a continuacion setea el mapa como una matriz de tipo celda
    this->playfield = campo;	
}

void UI::guardarJuego(Player *jugador1, Player *jugador2){
  std::ofstream field;
  field.open("field.csv");
  // aqui ponemos lo que hay que escribirle al archivo, para lo que hay que escribir un wile para guardar el playfield solo, y despues guardar cada jugador y unidad por separado
  for(int i=0; i<6; i++){
    for(int j=0; j<6; j++){
      field << jugador1->playfield->playfield[i][j]->encasilla << ",";
    }
    field << endl;
  }
  field.close();

  //// abrimos el archivo en el que vamo a guardar los atributos del player 1
  std::ofstream fileplayer1;
  fileplayer1.open("player1.csv");
  for(int i=0; i<jugador1->cantidadEjercito; i++){
    fileplayer1 << jugador1->cantidadEjercito << ",";
    fileplayer1 << jugador1->army[i].id << ",";
    fileplayer1 << jugador1->army[i].type << ",";
    fileplayer1 << jugador1->army[i].maxHitPoints << ",";
    fileplayer1 << jugador1->army[i].atk << ",";
    fileplayer1 << jugador1->army[i].defense << ",";
    fileplayer1 << jugador1->army[i].range << ",";
    fileplayer1 << jugador1->army[i].level << ",";
    fileplayer1 << jugador1->army[i].experience << ",";
    fileplayer1 << jugador1->army[i].movement << ",";
    fileplayer1 << jugador1->army[i].posx << ",";
    fileplayer1 << jugador1->army[i].posy << ",";
    fileplayer1 << jugador1->army[i].vivoomuerto << ",";
    fileplayer1 << endl;
  }
  fileplayer1.close();

  ////// abrimo el jugadore donde vamo a guardar los jugadores del player 2
  std::ofstream fileplayer2;
  fileplayer2.open("player2.csv");
  for(int i=0; i<jugador2->cantidadEjercito; i++){
    fileplayer2 << jugador2->cantidadEjercito << ",";
    fileplayer2 << jugador2->army[i].id << ",";
    fileplayer2 << jugador2->army[i].type << ",";
    fileplayer2 << jugador2->army[i].maxHitPoints << ",";
    fileplayer2 << jugador2->army[i].atk << ",";
    fileplayer2 << jugador2->army[i].defense << ",";
    fileplayer2 << jugador2->army[i].range << ",";
    fileplayer2 << jugador2->army[i].level << ",";
    fileplayer2 << jugador2->army[i].experience << ",";
    fileplayer2 << jugador2->army[i].movement << ",";
    fileplayer2 << jugador2->army[i].posx << ",";
    fileplayer2 << jugador2->army[i].posy << ",";
    fileplayer2 << jugador2->army[i].vivoomuerto << ",";
    fileplayer2 << endl;
  }
  fileplayer2.close();
}


void UI::traerJuegoGuardado(Player *jugador1, Player *jugador2){
  std::ifstream field;
  field.open("field.csv");
  vector<string> row;
  string line, word, temp;
  while(field>>temp){
    getline(field, line);
    stringstream s(line);
    while(getline(s, word, ',')){
      row.push_back(word);
    }
  }
  int k = 0;
  while(k<36){
    for(int i=0; i<6; i++){
      for(int j=0; j<6; j++){
        jugador1->playfield->playfield[i][j]->encasilla = row[k];
        k++;
        cout<<jugador1->playfield->playfield[i][j]->encasilla;
      }
      cout<<endl;
    }
  }





}

void Player::play(){	
	int coordenadax, coordenaday;
	//vamos a moverlos
	 for(int i=0;i < this->cantidadEjercito;i++){
	 cout<< "Para la unidad " << this->army[i].name << " cuyas cordenadas son: ("<< this->army[i].posx << " , " <<this->army[i].posy << ")\n";
	 cout<< "coordenada x a mover: \n";
	 cin>>coordenadax;
	 cout<< "coordenada y a mover: \n";
	 cin>>coordenaday;
	 while((coordenadax==-1 && coordenaday!=-1) || (coordenadax!=-1 && coordenaday==-1) || (coordenadax>5) || (coordenaday>5)  ){
		 cout<< "Ha incresado coordenadas fuera del mapa, ingrese de nuevo las coordenandas \n";
		 cout<< "coordenada x a mover: \n";
	     cin>>coordenadax;
	     cout<< "coordenada y a mover: \n";
	     cin>>coordenaday;
		 }
	 ////
	 if(coordenadax==-1 && coordenaday==-1){
		 cout<<"Permanece igual\n";
		 }
	else{
     bool goodmove= this->army[i].move(this->playfield->playfield[this->army[i].posx][this->army[i].posy],this->playfield->playfield[coordenadax][coordenaday],coordenadax,coordenaday);
     if(goodmove==false){
		 cout<< "No se puede mover a ese lugar \n";
		 }
	 
	 }
     }
     //vamos a hacerlos que ataquen
     cout <<"\n\n\n";
     	 for(int i=0;i < this->cantidadEjercito;i++){
	 cout<< "Para la unidad " << this->army[i].name << " cuyas cordenadas son: ("<< this->army[i].posx << " , " <<this->army[i].posy << ")\n";
	 cout<< "coordenada x a atacar: \n";
	 cin>>coordenadax;
	 cout<< "coordenada y a atacar: \n";
	 cin>>coordenaday;
	 while((coordenadax==-1 && coordenaday!=-1) || (coordenadax!=-1 && coordenaday==-1) || (coordenadax>5) || (coordenaday>5)  ){
		 cout<< "Ha ingresado coordenadas fuera del mapa, ingrese de nuevo las coordenandas \n";
		 cout<< "coordenada x a atacar: \n";
	     cin>>coordenadax;
	     cout<< "coordenada y a atacar: \n";
	     cin>>coordenaday;
		 }
	 ////
	 if(coordenadax==-1 && coordenaday==-1){
		 cout<<"No ataca\n";
		 }
	else{
	 //ocupo ver las coordenadas para decifrar cual unidad es la que quiere atacar
	 	if(this->playfield->playfield[coordenadax][coordenaday]->army!=NULL){//significa que la coordenada digitada si tiene una unidad, osea que el jugador ataco fijandose bien
				bool goodatack= this->army[i].attack(this->playfield->playfield[coordenadax][coordenaday]->army,this->playfield->playfield[coordenadax][coordenaday]);
				cout <<"ataque exitoso\n";
                if(goodatack==false){
		            cout<< "No se puede atacar a ese lugar, rango no es suficiente\n";
		         }
	      	
		}

	 }
     }
     
}



int main(){
  Field  *campo=new Field();
	Player *player1 = new Player();
	Player *player2 = new Player();
	int suma;
	
	campo->creacionCampo();

  
	
	player1->createPlayfield(campo);//le setea el campo a jugador1
	player2->createPlayfield(campo);//le setea el campo a jugador2

	UI ui;
  ui.traerJuegoGuardado(player1,player2);
	
	for(int i=0; i<6;i++){
	   for(int j=0;j<6;j++){
	       player2->playfield->playfield[i][j]->passable=true;
	       }
	}
	
	
	Lancer *lancer = new Lancer();
    Cavalry *cavalry = new Cavalry();
    Archer *archer= new Archer();
    lancer->setcost();
    cavalry->setcost();
    archer->setcost();
	int maxCost=15;//cost lancer es 3, cavalry es 5 y archer es 4
	int UnidadesLancer,  UnidadesCavalry, UnidadesArcher;
	cout << "                 Hola jugador1\n\n";
    cout<<"Para comprar su ejercito dispone de "<<maxCost<< " monedas" <<"\n";
    cout<<"Ingrese las unidades de Lancer que requiere (costo 3 monedad) \n";
    cin >> UnidadesLancer;
    cout<<"Ingrese las unidades de Cavalry que requiere (costo 5 monedad) \n";
    cin >> UnidadesCavalry;
    cout<<"Ingrese las unidades de Archer que requiere (costo 4 monedad) \n";
    cin >> UnidadesArcher;
     	
    //antes cree variables de costo directas, o sea como int lancercost=3, algo sucio y en unit no estaba guardando nada en su cost;
    suma = (lancer->cost)*UnidadesLancer + (cavalry->cost)*UnidadesCavalry	+ (archer->cost)*UnidadesArcher;//no perder la cabeza, los * son de multiplicacion
    
    
    while (suma > maxCost){
	  cout << "******************************************************************************* \n";
      cout <<"Ha excedido las 15 monedas, vuelva a elegir un monto valido con 15 monedas para su ejercito \n";
      cout << "******************************************************************************* \n";
      cout<<"Ingrese las unidades de Lancer que requiere (costo 3 monedad) \n";
      cin >> UnidadesLancer;
      cout<<"Ingrese las unidades de Cavalry que requiere (costo 5 monedad) \n";
      cin >> UnidadesCavalry;
      cout<<"Ingrese las unidades de Archer que requiere (costo 4 monedad) \n";
      cin >> UnidadesArcher;
      suma = (lancer->cost)*UnidadesLancer + (cavalry->cost)*UnidadesCavalry	+ (archer->cost)*UnidadesArcher;
			}
		
	player1->createArmy(UnidadesLancer, UnidadesCavalry,UnidadesArcher);
	player1->cantidadEjercito= UnidadesLancer+ UnidadesCavalry + UnidadesArcher;
	//cout<<player1->cantidadEjercito; 
     
    for(int i=0; i<(UnidadesLancer+UnidadesCavalry+UnidadesArcher);i++){
		player1->army[i].unodos="1";
		campo->playfield[0][i]->encasilla = "  "+player1->army[i].type+"1 ";
	    player1->army[i].posx=0;
	    player1->army[i].posy=i;
	    player1->playfield->playfield[0][i]->setAtributos(false,&player1->army[i]);	
		} 
     
		cout << "\n\n\n\n";
		
		
	cout << "                 Hola jugador2\n\n";
	cout<<"Para comprar su ejercito dispone de "<<maxCost<< " monedas" <<"\n";
    cout<<"Ingrese las unidades de Lancer que requiere (costo 3 monedad) \n";
    cin >> UnidadesLancer;
    cout<<"Ingrese las unidades de Cavalry que requiere (costo 5 monedad) \n";
    cin >> UnidadesCavalry;
    cout<<"Ingrese las unidades de Archer que requiere (costo 4 monedad) \n";
    cin >> UnidadesArcher;
     	
    //antes cree variables de costo directas, o sea como int lancercost=3, algo sucio y en unit no estaba guardando nada en su cost;
    suma = (lancer->cost)*UnidadesLancer + (cavalry->cost)*UnidadesCavalry	+ (archer->cost)*UnidadesArcher;//no perder la cabeza, los * son de multiplicacion
        
    while (suma > maxCost){
	  cout << "******************************************************************************* \n";
      cout <<"Ha excedido las 15 monedas, vuelva a elegir un monto valido con 15 monedas para su ejercito \n";
      cout << "******************************************************************************* \n";
      cout<<"Ingrese las unidades de Lancer que requiere (costo 3 monedad) \n";
      cin >> UnidadesLancer;
      cout<<"Ingrese las unidades de Cavalry que requiere (costo 5 monedad) \n";
      cin >> UnidadesCavalry;
      cout<<"Ingrese las unidades de Archer que requiere (costo 4 monedad) \n";
      cin >> UnidadesArcher;
      suma = (lancer->cost)*UnidadesLancer + (cavalry->cost)*UnidadesCavalry	+ (archer->cost)*UnidadesArcher;
			}
			
	player2->createArmy(UnidadesLancer, UnidadesCavalry,UnidadesArcher);
	player2->cantidadEjercito=UnidadesLancer+UnidadesCavalry+UnidadesArcher;
	//cout<<player2->cantidadEjercito;
	cout << "\n\n\n\n";
	

	for(int i=0; i<(UnidadesLancer+UnidadesCavalry+UnidadesArcher);i++){
		player2->army[i].unodos="2";
		campo->playfield[5][i]->encasilla = "  "+player2->army[i].type+"2 ";
	    player2->army[i].posx=5;
	    player2->army[i].posy=i;
	    player2->playfield->playfield[5][i]->setAtributos(false,&player2->army[i]);	
		}
    
    
	
	campo->printCampo();
	///// PRUEBA DEL GUARDADO DEL JUEGO //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ui.guardarJuego(player1,player2);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//aqui ya tendria que venir un loop para que sea la pelea
    player1->play();
    campo->printCampo();
    player2->play();	
    campo->printCampo(); 
	 //lalala
     player1->play();
    campo->printCampo();
    player2->play();	
    campo->printCampo(); 
	return 0;
	}
	