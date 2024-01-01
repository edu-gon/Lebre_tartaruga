----- PORTUGUES --------


O ficheiro 'lab.h' deve ser descomprimido, copiado para a diretoria de trabalho e incluído no projeto.

Para usar esta biblioteca:

#include "lab.h"

este ficheiro possui vários métodos

void trocaChars(char* a, char* b) //troca dois carateres
void trocaInts(int* a, int* b)    //troca dois inteiros

typedef struct MY_COLORS {
	int foreColor;
	int backColor;
}mycolors;  //estrutura para acomodar duas cores

void copyColors(mycolors* dest, mycolors ori) //copia um par de cores da origem para o destino
void setColors(mycolors now) //ativa na consola as cores presentes na estrutura
BOOL getColors(mycolors* cor) //recupera as cores em uso na consola guardando-as na estrutura 

void setFullScreen(BOOL on)  //permite alternar entre ecrã completo e modo de janela
void GetDesktopResolution(BOOL pixel, int* horizontal, int* vertical) // recupera a resolução x y da janela em pixeis ou em carateres consoante a flag pixel


gotoxy(int x, int y) //permite colocar o cursor em qualquer posição x,y  na consola, útil para organizar os menus e o desenho das cartas.

void showRect(int x, int y, int width, int height) //permite desenhar um retângulo na posição desejada

void show90RectAt(int x, int y, int width, int height)   //desenha um retangulo com linhas duplas na posicao X,Y com as dimensoes Width e Height, rodado 90º

void showCharAt(int x, int y, char c)      //mostra um carater na posição designada

void printfAt(int x, int y, char c[])    //escreve uma 'string' na horizontal na posição designada

void showVerticalWordAt(int x, int y, char c[], int charNumber)   //Escreve uma 'string' na vertical na posição designada

void setColor(int foreGround, int backGround)   //altera a cor do texto e do fundo

void setForeColor(int foreGround)             //altera a cor do texto, mantém a cor do fundo

void setBackColor(int backGround)          //altera a cor do fundo, mantém a cor do texto

void resetColor()       //Redefine as cores: branco para o texto e preto para o fundo

void printAscii(int N0, int N, int col)		// imprime a tabela ascii em duas localizações 
											// exemplo de utilização: printAscii(174, 223, 4);

------ENGLISH-------

The file lab.h should be decompressed, copied to the working directory and included in the project.
Any file needing it shoud have:

#include "lab.h"

this library contains several methods:

void trocaChars(char* a, char* b) //swaps two chars
void trocaInts(int* a, int* b)    //swaps two integers

typedef struct MY_COLORS {
	int foreColor;
	int backColor;
}mycolors;  //struct to acomodate two colors

void copyColors(mycolors* dest, mycolors ori) ////copy colors structure from ori to dest
void setColors(mycolors now) //changes both foreground and background colors
BOOL getColors(mycolors* cor) //retrieve the window colors in the structure

void setFullScreen(BOOL on)  //allows swapping from full screen to windowed mode
void GetDesktopResolution(BOOL pixel, int* horizontal, int* vertical) // gets screen resolution in pixel or chars accordingly with flag pixel

gotoxy(int x, int y) //allows to place the cursor at any given position

void showRect(int x, int y, int width, int height) //allows to draw a rectangle (double lines) at any given position

void show90RectAt(int x, int y, int width, int height)   //allows to draw a rectangle (double lines) at any given position, rotated by 90º

void showCharAt(int x, int y, char c)   //show a char at a designated position

void printfAt(int x, int y, char c[])    //write an horizontal 'string' at a designated position

void showVerticalWordAt(int x, int y, char c[], int charNumber)   //write a 'string' verticaly at a designated position

void setColor(int foreGround, int backGround)   //changes both foreground and background colors

void setForeColor(int foreGround)             //changes foreground color while keeping background color

void setBackColor(int backGround)          //changes background color while keeping foreground color

void resetColor()               //Colors reset: foreground white, background black


void printAscii(int N0, int N, int col)		// print the ascii table in two location specific settings 
											// usage sample: printAscii(174, 223, 4);

