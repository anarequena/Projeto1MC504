#include <curses.h> //Incluiremos a biblioteca ao nosso sistema
#include <stdio.h>
#include <unistd.h>

#define L1 9
#define L2 16
#define EMB getmaxx(stdscr)/2+10
#define DES getmaxx(stdscr)/2-30
#define N_P_CAR 4			// Numero de passageiros por carrinho
#define N_CARS 2			// Numero de carrinhos

struct Carrinho{
   int id;
   int passageiros;
};


void printCar(int coluna, int L, struct Carrinho carrinho);
void printRail();
void printTitulo();

int main(){
  	int i, tamanhoCarro = N_P_CAR + N_P_CAR%2;
  	struct Carrinho car[N_CARS];

	for(i=0; i<N_CARS; i++){
		car[i].passageiros = N_P_CAR;
  		car[i].id = i;
	}
	
	noecho();
  	curs_set(0);

  	initscr();   /*Esta função  inicializa a ncurses. Para todos os programas
                 devemos sempre inicializar a ncurses e depois finalizar, como
                veremos adiante. */
	printTitulo();
	//printRail();
	refresh();
	sleep(1);
	
	//printRail(L1);
	//printCar(EMB, L1, car[0]);
	//printCar(EMB-tamanhoCarro*2, L1, car[1]);
	// faz o carrinho andar
	for (i=0;i<getmaxx(stdscr)/2;i++){
		printRail(L1);
		printCar(EMB+i, L1, car[0]);	
		printCar(EMB+i-tamanhoCarro*2, L1, car[1]);
		/*if (i<40)
		  printCar(DES+i, L1, car[2]);
		else*/
		printRail(L2);
		printCar(DES+i, L2, car[1]);
		//sleep(1);
		usleep(100000);

		refresh();    //Atualiza a tela
	}
	getch();      //Fica esperando que o usuário aperte alguma tecla

	endwin();
	return 0;
}
*/

void printTitulo(){
  int i;
  move(0,0);
  for (i = 0; i < getmaxx(stdscr); i++){
    printw("=");
  }
  move(2,getmaxx(stdscr)/2-5);  //Aqui estamos movendo o cursor para a linha 2 coluna 1.
  printw("MONTANHA RUSSA");

  move(4,0);
  for (i = 0; i < getmaxx(stdscr); i++){
    printw("=");
  }
  move(6,DES);
  printw("*EMBARQUE*");
  printRail(L1);
  move(13,DES);
  printw("*DESEMBARQUE*");
  printRail(L2);
  move(0,0);
}


void printRail(int L){
  int i;

  move(L-1,0);
  for (i = 0; i < getmaxx(stdscr); i++){
    printw(" ");
  }
  move(L,0);
  for (i = 0; i < getmaxx(stdscr); i++){
    printw("-");
  }
  move(L+1,0);
  for (i = 0; i < getmaxx(stdscr); i++){
    printw("-");
  }
  move(L+2,0);
  for (i = 0; i < getmaxx(stdscr); i++){
    printw(" ");
  }
  move(0,0);
}
void printCar(int coluna, int L, struct Carrinho carrinho){
  int largura = carrinho.passageiros + carrinho.passageiros%2;
  int i;

  move(L-1, coluna);
  /*-----------FRENTE-----------*/
  if (getcury(stdscr) == L-1)
    printw(" ");

  for (i=0; i<largura;i++){
    //printw("%d %d",getcury(stdscr), getcurx(stdscr));
    if ((getcury(stdscr) == L-1))
      printw("_");
  }

  if ((getcury(stdscr) == L-1))
    printw("%d", carrinho.id);

  move(L, coluna);
  /*-----------Fileira 1-----------*/
  if (getcury(stdscr) == L)
    printw("|");

  for (i=0; i<largura;i++){
    if (getcury(stdscr) == L){
      if (i % 2 == 0){
        printw("o");
      }else
        printw(" ");
    }
  }

  if (getcury(stdscr) == L)
    printw(")");

  move(L+1, coluna);
  /*-----------Fileira 2-----------*/
  if (getcury(stdscr) == L+1)
    printw("|");

  for (i=0; i<largura;i++){
    if (getcury(stdscr) == L+1){
      if ((i == 0) && (carrinho.passageiros%2 == 1)){
        printw(" ");
      }
      else if (i % 2 == 0){
        printw("o");
      }else
        printw("_");
    }
  }

  if (getcury(stdscr) == L+1)
      printw(")");

  move(0,0);
}
