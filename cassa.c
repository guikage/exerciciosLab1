#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

// Programa exemplo do uso das funções de ncurses
// Além deste arquivo, necessitaria de tela.h e tela.c,
// mas eu fiz tudo usando ncurses :D
//
// Para compilar:
//   gcc cassa.c -o cassa -lncurses
//
// tente sobreviver à cerquinha assassina durante 10s

// funções auxiliares
int max(int a, int b)
{
  return a>b ? a : b;
}

int abs(int a)
{
  return a<0 ? -a : a;
}

double relogio(void) //funcao retirada diretamente do arquivo tela.c
{
  struct timespec agora;
  clock_gettime(CLOCK_REALTIME, &agora);
  return agora.tv_sec + agora.tv_nsec*1e-9;
}

int main()
{
  srand(time(0));
  initscr();
  noecho();
  halfdelay(1);
  keypad(stdscr, true);
  curs_set(0);
  start_color();

  //inicializa cores
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  // posição do jogador
  int lmax = 24, cmax = 40;
  //getmaxyx(stdscr, lmax, cmax);
  int lj = lmax/2;
  int cj = cmax/2;
  // posição do inimigo
  int li = rand()%lmax+1;
  int ci = rand()%cmax+1;

  double inicio = relogio();  // marca a hora de início do programa
  double tempo;   // há quanto tempo o programa tá rodando
  int dist;
  do {
    tempo = relogio() - inicio;
    dist = max(abs(lj-li), abs(cj-ci));
    // desenha a tela
    clear();
    move(1, 1);
    printw("%d %.1lf, %d %d  %d %d", dist, tempo, lj, cj, li, ci);
    move(lj, cj);
    attron(COLOR_PAIR(1));
    addch('@');
    move(li, ci);
    attron(COLOR_PAIR(2));
    addch('#');
    attron(COLOR_PAIR(1));
    refresh();

    // atualiza a posição do jogador, se foi teclada alguma tecla de movimentação
    int tecla = getch();
    switch (tecla) {
      case KEY_UP:
        if (lj>1) lj--;
        break;
      case KEY_DOWN:
        if (lj<lmax) lj++;
        break;
      case KEY_LEFT:
        if (cj>1) cj--;
        break;
      case KEY_RIGHT:
        if (cj<cmax) cj++;
        break;
      default:
        break;
    }
    // atualiza a posição do inimigo, em direção ao jogador
    if (ci < cj) ci += rand()%2;
    if (ci > cj) ci -= rand()%2;
    if (li < lj) li += rand()%2;
    if (li > lj) li -= rand()%2;
  } while (tempo < 10 && dist > 0);

  move(lmax-2, 1);
  if (tempo >= 10) {
    printw("Parabéns\n");
  } else {
    printw("Não foi desta vez!\n");
  }
  printw("tecle enter ");
  refresh();
  while (getch() != '\n');
  endwin();
  printf("tchau\n");
}
