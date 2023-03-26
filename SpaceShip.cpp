//se usa stdio.h en lugar de iostream
#include<stdio.h> //es mucho más simple imprimir caracteres especiales para dibujo
//porque printf a diferencia de cout, pide el formato de variables a imprimir
#include<windows.h> //se requiere de una funcion de esta biblioteca para posicionar el cursor
//SetConsoleCursorPosition()
#include<stdbool.h>
#include<conio.h>//para detectar la presion de teclas
//funcion para detectar si se presiono una tecla kbhit()
#include<stdlib.h>
#include<list>
#include<iostream>
#include<cstring>
#include<ctype.h>
using namespace std;
using std::string;

#define ESPACIO 32
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define Ve 86


/*

                                        Funcion para las coordenadas
                                                              
                                                                                                            */
void gotoxy(int x, int y){
//Esta funcion requiere de dos parametros, un handle (identificador) y el segundo una estructura de datos
//Se requiere un identificador de la ventana a la que se quiere manipular, para eso es el handle
    
	HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //El parametro es de salida, se toma el control de la salida
   
    //de la consola, debido a que la accion de dar una posicion a un caracter en la pantalla es una accion de salida
    COORD dwPos; //COORD es una estructura, dwPos es un objeto, sus valores son coordenadas
    
	dwPos.X = x; //X Y son atributos que seran interpretados como coordenadas
    dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
	
	
}

/*

                                        Funcion para esconder el cursor
                                                              
                                                                                                            */
void ocultarCursor(){
	HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci; //Se puede controlar la apariencia del cursor
    //atributos
    cci.dwSize = 50; //ingresar variables de tipo entera, funciona solamente si el siguiente atributo esta en true
    cci.bVisible = FALSE; //Toma valores falso o verdadero TRUE para que el cursor se muestre en pantalla, FALSE para que no

    SetConsoleCursorInfo(hCon, &cci); //el segundo parametro se pasa por referencia
}

/*

                                        FUNCION PARA PINTAR LOS LÍMITES
                                                              
                                                                                                            */
                                                                                                            
void pintarLimites(){
	for(int i = 2; i<78; i++){
		Sleep(5);
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,33); printf("%c",205);
	}
	for(int i = 4; i<33; i++){
		Sleep(5);
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	Sleep(5);
	gotoxy(2,3); printf("%c",201);
	Sleep(5);
	gotoxy(2,33); printf("%c",200);
	Sleep(5);
	gotoxy(77,3); printf("%c",187);
	Sleep(5);
	gotoxy(77,33); printf("%c",188);
	
}

/*

                                        CLASE NAVE, FUNCIONES
                                                              
                                                                                                            */
                                                                                                            
class NAVE{
	private: //atributos
		int x, y;
		int corazones;
		int vidas;
	public: //metodos
		NAVE(int, int, int, int); //constructor, tambien ya se lo puede inicializar desde ahi con NAVE::NAVE(int _x, int_y) : x(_x), y(_y){}
		int coorX(){ return x;}
		int coorY(){ return y;}
		int VIDAS(){ return vidas;}
		void corazon(){ corazones--; }
		void pintar(); //dibujar la nave
		void borrar(); //borrar su rastro
		void mover(); 
		void pintarCorazones();
		void explosion();
};

NAVE::NAVE(int _x, int _y, int _corazones, int _vidas){
	x = _x;
	y = _y;
	corazones = _corazones;
	vidas = _vidas;
}

//otra forma para el constructor
/*NAVE::NAVE(int _x, int_y) : x(_x), y(_y){

}*/

void NAVE::pintar(){
	gotoxy(x,y); printf("  %c",30);
	gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);
	
}

void NAVE::borrar(){
	gotoxy(x,y); printf("         ");
	gotoxy(x,y+1); printf("        ");
	gotoxy(x,y+2); printf("        ");
}

void NAVE::mover(){
			if(kbhit()){
			char tecla = getch(); //guarda la letra que se presione
			
			borrar();
			
			if(tecla == IZQUIERDA && x > 3) x--;
			if(tecla == DERECHA && x+6 < 77) x++; //+6 porque la nave está hecha de varios caracteres
			if(tecla == ARRIBA && y>4) y--;
			if(tecla == ABAJO && y+3 < 33) y++; //+3 debido a que es la altura del caracter
			if(tecla == 'e') corazones--;
			pintar();
			pintarCorazones();
		}

	
}

void NAVE::pintarCorazones(){
	gotoxy(50,2); printf("Vidas %d",vidas);
	gotoxy(64,2); printf("Vida");
	gotoxy(70,2); printf("     ");
	
	for(int i = 0; i < corazones; i++){
		gotoxy(70+i,2); printf("%c",3);
	}
}

void NAVE::explosion(){
	if(corazones == 0){
		borrar();
		gotoxy(x,y); printf("   %c%c  ",176,178);
		gotoxy(x,y+1); printf(" %c%c%c ",176,177,178);
		gotoxy(x,y+2); printf("   %c%c ",178,177);
		Sleep(400);
		
		borrar();
		
		gotoxy(x,y); printf("%c  %c%c ",178,177,178);
		gotoxy(x,y+1); printf(" %c%c%c%c",178,178,177,177);
		gotoxy(x,y+2); printf(" %c %c%c %c",178,177,177,178);
		Sleep(400);
		
		borrar();
		
		gotoxy(x,y); printf("%c%c%c%c%c",178,177,178,177,178);
		gotoxy(x,y+1); printf("%c%c%c%c",178,178,177,177);
		gotoxy(x,y+2); printf(" %c%c%c%c %c",177,178,177,177,178);
		Sleep(400);
		
		borrar();
		vidas--;
		corazones = 3;
		pintarCorazones();
		pintar();
		
	}
}

/*

                                        CLASE ASTEROIDES, FUNCIONES
                                                              
                                                                                                            */
class asteroide{
	private: //atributos
	    int x,y;
	public: //metodos
		asteroide(int _x, int _y) : x(_x), y(_y){} //se inicializa dentro de los metodos
		int coorX(){ return x;}
		int coorY(){ return y;}
		void pintar();
		void mover();
		void colision(class NAVE &N); //tambien se puede poner struct en lugar de class
};

void asteroide::colision(class NAVE &N){
	
	if( x >= N.coorX() && x < N.coorX()+5 && y >= N.coorY() && y < N.coorY()+2){ //+5 porque la nave esta pintada por varios caracteres, este es el ancho de la nave
	//+2 porque es la altura de la nave
	N.corazon(); //reduce la cantidad de corazones
	N.borrar(); //Aca se utiliza para que no queden asteroides pegados a la nave
	N.pintar(); //se redibuja la nave
	N.pintarCorazones(); //los corazones se actualizan 
		x = rand() % 71 + 4;
		y = 4;
	}
}

void asteroide::pintar(){
	gotoxy(x,y); printf("%c",2);

}

void asteroide::mover(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y>32){
		x = rand() % 71 + 4;
		y = 4;
	}
	pintar();
}

/*

                                        CLASE BALAS, FUNCIONES
                                                              
                                                                                                            */
class bala{
	private:
		int x, y;
	public:
		bala(int _x, int _y) : x(_x), y(_y){}
		int coorX(){return x;}
		int coorY(){return y;}
		void mover();
		bool fuera();
};

void bala::mover(){ //movimiento de las balas
	gotoxy(x,y); printf(" "); //elimina el rastro de las balas
	y--;
	gotoxy(x,y); printf("%c",6); //diseño de las balas
}

bool bala::fuera(){ //detecta las balas que salen del marco
	if( y == 4) return true;
	return false;
}

/*

                                        CLASE ULTI, FUNCIONES
                                                              
                                                                                                            */
                                                                                                            
class ulti{
	private:
		int x, y;
	public:
		ulti(int _x, int _y) : x(_x), y(_y){}
		int coorX(){return x;}
		int coorY(){return y;}
		void mover();
		bool fuera();
};

void ulti::mover(){
	gotoxy(x,y); printf(" ");//10 espacios
	y--;
	gotoxy(x,y); printf("%c",178);
}

bool ulti::fuera(){
	if( y == 4) return true;
	return false;
}
                                                                                                            
/*

                                        APLICACION DE LAS FUNCIONES Y CLASES
                                                              
                                                                                                            */
                                                                                                            
int main(){
		char opcion[3];
	    char dificultad[9];
	    char dificultadMin[9];
	    int cantAst;
	    
	    //dificultad y tutorial
	    cout<<"Escriba la dificultad\n[facil/medio/dificil]: ";
	    gets(dificultad);
	
	    for(int i=0; dificultad[i] != '\0'; i++){
	    	dificultad[i] = tolower(dificultad[i]);
		}
		
	    if(strcmp(dificultad, "facil") == 0){
	    	cantAst = 3;
		}else if(strcmp(dificultad, "medio") == 0){
			cantAst = 10;
		}else if(strcmp(dificultad, "dificil") == 0){
		    cantAst = 16;
		}else{
			cout<<"Dificultad incorrecta, intente de nuevo\n"<<endl;
			system("pause");
			system("cls");
			main();
		}
		system("cls");
		printf("CONTROLES:[FLECHAS]\nARRIBA %c\nABAJO %c\nIZQUIERDA %c\n DERECHA %c\n",24,25,17,16);
		printf("DISPARAR:[ESPACIO] ULTI: [V] %c\n",22);
		system("Pause");
		system("cls");
	//termina dificultad y tutorial
	
	//List son secuencias de elementos almacenados en una lista encadenada, similar a un vector
	list<bala*> B; //lista de punteros con variable B
	list<bala*>::iterator it; //iterador para recorrer la lista 

	list<ulti*> U; //lista de punteros con variable U
	list<ulti*>::iterator itU; //iterador para recorrer la lista 
	
	pintarLimites();
	NAVE N(37,30,3,3);
	N.pintar();
    ocultarCursor();
    
    list<asteroide*> A;
    list<asteroide*>::iterator itA;
    for(int i=0; i<cantAst; i++){
    	A.push_back(new asteroide(rand()%75+3, rand()%5+4)); //se crean los nuevos asteroides
	}
	bool game_over = false;
	int puntos=0;
	while(game_over == false){
		        
		        
		        gotoxy(4,2); printf("PUNTOS %d",puntos);
		        if(kbhit()){
		        	char tecla = getch();
		        	if(tecla == ESPACIO){
					B.push_back(new bala(N.coorX()+2, N.coorY()-1));//Crear la bala en las coordenadas de la nave
					}
					
				}
				
				if(kbhit()){
		        	char tecla = getch();
		        	if(tecla == Ve){
					U.push_back(new ulti(N.coorX()+2, N.coorY()-1));//Crear la bala en las coordenadas de la nave
					}
					
				}
				
				
		        
		        for(it = B.begin();/*Primer iterador de la lista*/ it != B.end(); /*hasta el final*/ it++){
		        	//puntero it
		        	(*it)->mover();
		        	if((*it)->fuera()){
		        		gotoxy((*it)->coorX(), (*it)->coorY()); printf(" ");
		        		delete(*it); //se elimina la bala atascada, al elemento que está afuera
		        		it = B.erase(it); //se vuelve a hacer el enlace, al elemento que sigue despues del que fue disparado
					}
				}
				
		        for(itU = U.begin();/*Primer iterador de la lista*/ itU != U.end(); /*hasta el final*/ itU++){
		        	//puntero it
		        	(*itU)->mover();
		        	if((*itU)->fuera()){
		        		gotoxy((*itU)->coorX(), (*itU)->coorY()); printf(" ");
		        		delete(*itU); //se elimina la bala atascada, al elemento que está afuera
		        		itU = U.erase(itU); //se vuelve a hacer el enlace, al elemento que sigue despues del que fue disparado
					}
				}
				
				for(itA = A.begin(); itA != A.end(); itA++){ //recorre asteroides
					for(it = B.begin(); it != B.end(); it++){ //recorre las balas
						if((*itA)->coorX() == (*it)->coorX() && ( (*itA)->coorY()+1 == (*it)->coorY() || (*itA)->coorY() == (*it)->coorY())){
							gotoxy((*it)->coorX(), (*it)->coorY()); printf(" ");
							delete(*it);
							it = B.erase(it);
							
							A.push_back(new asteroide(rand() %74 + 3, 4)); //se crea un nuevo asteroide de forma aleatoria
							gotoxy((*itA)->coorX(), (*itA)->coorY()); printf(" ");
							delete(*itA);
							itA = A.erase(itA);
							puntos += 10;
						}
					}
				}
				
				for(itA = A.begin(); itA != A.end(); itA++){ //recorre asteroides
					for(itU = U.begin(); itU != U.end(); itU++){ //recorre la ULTI
						if((*itA)->coorX() == (*itU)->coorX() && ( (*itA)->coorY()+1 == (*itU)->coorY() || (*itA)->coorY() == (*itU)->coorY())){
							gotoxy((*itU)->coorX(), (*itU)->coorY()); printf(" ");
							delete(*itU);
							itU = U.erase(itU);
							
							A.push_back(new asteroide(rand() %74 + 3, 4)); //se crea un nuevo asteroide de forma aleatoria
							gotoxy((*itA)->coorX(), (*itA)->coorY()); printf(" ");
							delete(*itA);
							itA = A.erase(itA);
							puntos += 10;
						}
					}
				}
		    
		        
		        for(itA = A.begin(); itA != A.end(); itA++){
		        	(*itA)->mover();
		        	(*itA)->colision(N);
				}
				
				if(N.VIDAS() ==0 ){
					game_over = true;
					
				}
				
	            N.explosion();
		        N.mover();

				Sleep(30); //reducir las iteraciones en milisegundos
	}
	system("cls");

	cout<<"Puntuacion: "<<puntos<<endl;
	cout<<"Volver a intentar?[si/no]: ";
	gets(opcion);
	if(strcmp(opcion, "si") == 0){
		system("cls");
		main();
	}
	
	getch();
	return 0;
}
