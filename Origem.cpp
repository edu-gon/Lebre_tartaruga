#include "lab.h"


typedef struct BARALHO {
	char* cartas;//L, T, W, w, R, C
	int size;
	int maxSize;
}baralho;

typedef struct JOGADOR {
	char nome[20 + 1];
	int pontuacao;
	int tipo;	//'0' - no player, '1'- humano, '2' - BOT
	baralho mao;
	baralho apostas;
}jogador;


#define BOT  2
#define HUMAN  1
#define NOPLAYER  0

//criar deck do tamanho pretendido
char* createDeck(int maxSize) {
	char* cartas = (char*)calloc(maxSize, sizeof(char));
	if (cartas == NULL) {
		return NULL;
	}
	for (int i = 0; i < maxSize; i++) {
		cartas[i] = 'x';
	}
	return cartas;
}
//criar baralho do tamanho pretendido
baralho* createBaralho(int maxSize) {
	baralho* myDeck = (baralho*)calloc(1, sizeof(baralho));
	if (myDeck == NULL) {
		return NULL;
	}
	myDeck->cartas = createDeck(maxSize);
	if (myDeck->cartas == NULL) {
		free(myDeck);
		myDeck = NULL;
		return NULL;
	}
	myDeck->maxSize = maxSize;
	myDeck->size = 0;
	return myDeck;
}

//Criar jogador,  humano ou bot
BOOL createJogador(jogador* jog) {
	strcpy_s(jog->nome, sizeof(jog->nome), "");
	jog->pontuacao = 0;
	jog->tipo = 0; //'0' - no player, '1'- humano, '2' - BOT
	jog->mao.cartas = createDeck(7);
	jog->apostas.cartas = createDeck(3);
	return TRUE;
}
	

void freeDeck(char** cartas) {
	if (*cartas != NULL) {
		free(*cartas);
	}
}
// libertar o espaço do baralho na memória ao sair
void freeBaralho(baralho** myDeck) {
	if ((*myDeck) == NULL) {
		return;
	}
	freeDeck(&((*myDeck)->cartas));
	free(*myDeck);
	(*myDeck) = NULL;
}
void freeJogador(jogador* jog) {
	strcpy_s(jog->nome, sizeof(jog->nome), "");
	jog->pontuacao = 0;
	jog->tipo = 0;			//'0' - no player
	/*free(&(jog->mao.cartas));
	free(&(jog->apostas.cartas));*/
}


//resetar baralho 
BOOL resetBaralho(baralho* myDeck) {
	int i = 0;
	if (myDeck == NULL) {
		return false;
	}
	for (i = 0; i < myDeck->maxSize; i++) {
		myDeck->cartas[i] = 'x';
	}
	myDeck->size = 0;
	return true;
}
//Função para inicializar o baralho principal com 81 cartas
BOOL initBaralho81(baralho* myDeck) {
	int i = 0;
	if (myDeck == NULL) {
		return false;
	}
	myDeck->size = 0;
	myDeck->maxSize = 81;

	if (myDeck->maxSize < 81) {
		return false;
	}

	for (i = 0; i < 18; i++) {
		myDeck->cartas[i] = 'L';
		myDeck->size++;
	}
	for (i = 18; i < 35; i++) {
		myDeck->cartas[i] = 'T';
		myDeck->size++;
	}
	for (i = 35; i < 48; i++) {
		myDeck->cartas[i] = 'W';
		myDeck->size++;
	}
	for (i = 48; i < 51; i++) {
		myDeck->cartas[i] = 'w';
		myDeck->size++;
	}
	for (i = 51; i < 66; i++) {
		myDeck->cartas[i] = 'R';
		myDeck->size++;
	}
	for (i = 66; i < 81; i++) {
		myDeck->cartas[i] = 'C';
		myDeck->size++;
	}
	return true;

}
BOOL initBaralhoApostas(baralho* myDeck) {
	int i = 0;
	if (myDeck == NULL) {
		return false;
	}

	if (myDeck->maxSize < 5) {
		return false;
	}

	myDeck->cartas[i] = 'L';	myDeck->size++;
	myDeck->cartas[i] = 'T';	myDeck->size++;
	myDeck->cartas[i] = 'W';	myDeck->size++;
	myDeck->cartas[i] = 'R';	myDeck->size++;
	myDeck->cartas[i] = 'C';	myDeck->size++;
	
	return true;

}

void printBaralho(baralho myDeck) {
	int i = 0, aux = 0;

	if (myDeck.size > myDeck.maxSize) {//size errado?
		myDeck.size = myDeck.maxSize;//corrige o size
	}

	printf("\n(");
	for (i = 0; i < myDeck.size; i++) { //81 -> myDeck.size?
		printf("%c,", myDeck.cartas[i]);
	}
	printf(")");

}
void saveBaralho(FILE* fp, baralho myDeck) {
	//assumimos que o ficheiro já vem aberto e na posição descrita
	int i = 0;
	if (myDeck.size > myDeck.maxSize) {//size errado?
		myDeck.size = myDeck.maxSize;//corrige o size
	}
	fprintf(fp, "(%d,%d)", myDeck.maxSize, myDeck.size);
	fprintf(fp, "(");
	for (i = 0; i < myDeck.maxSize-1; i++) { //81 -> myDeck.size?
		fprintf(fp, "%c,", myDeck.cartas[i]);
	}

	fprintf(fp, "%c", myDeck.cartas[i]);
	fprintf(fp, ")");
	
}
void saveJogador(FILE* fp, jogador jog) {
	fprintf(fp, "(%d, %s, %d,", jog.tipo, jog.nome, jog.pontuacao);
	saveBaralho(fp, jog.mao);
	saveBaralho(fp, jog.apostas);
	fprintf(fp, ")");
}
BOOL readBaralho(FILE* fp, baralho* myDeck) {
	//assumimos que o ficheiro já vem aberto e na posição descrita
	int i = 0;

	if (myDeck == NULL) {
		return false;
	}
	fscanf_s(fp, "(%d,%d)", &(myDeck->maxSize), &(myDeck->size));
	fgetc(fp);//descarta o '('
	for (i = 0; i < myDeck->maxSize; i++) { //81 -> myDeck.size?
		myDeck->cartas[i] = fgetc(fp);
		fgetc(fp); // descarta a ','
	}
	myDeck->cartas[i] = fgetc(fp);
	fgetc(fp);
	return true;
}
BOOL baralharBaralho(baralho* myDeck) {
	
	int i = 0, r = 0, temp = 0;
	if (myDeck == NULL) {
		return false;
	}
	if (myDeck->size > myDeck->maxSize) {
		myDeck->size = myDeck->maxSize;
	}
	for (i = 0; i < myDeck->size; i++) {
		r = rand() % myDeck->size;

		temp = myDeck->cartas[i];
		myDeck->cartas[i] = myDeck->cartas[r];
		myDeck->cartas[r] = temp;
	}
	return true;
}



//identificação 
void identificação()
{
	setColor(MY_COLOR_DARK_BLUE, MY_COLOR_LIGTH_GREEN);
	setFullScreen(true);

	gotoxy(10, 10); printf("Jogo da Lebre e da Tartaruga");
	gotoxy(10, 12); printf("by Eduardo\t\t2023_24");

	gotoxy(10, 22); system("pause");
}
//menu do jogo
char menu(char* opt)
{
	setlocale(LC_ALL, "");
	//char opt = '0';
	do {
		system("cls");
		gotoxy(10, 10); printf("Menu");

		gotoxy(10, 12); printf("A.Jogar uma Partida");
		gotoxy(10, 13); printf("B.Carregar uma partida");
		gotoxy(10, 14); printf("C. Descrição do jogo");
		gotoxy(10, 15); printf("D.Sair da aplicação");

		gotoxy(10, 17); printf("Escolha uma opção:");
		(void)scanf(" %c", opt);
	} while ((*opt) != 'A' && (*opt) != 'B' && (*opt) != 'C' && (*opt) != 'D' && (*opt) != 'a' && (*opt) != 'b' && (*opt) != 'c' && (*opt) != 'd');

	setlocale(LC_ALL, "C");

	return *opt;

}

//regras do jogo
void regras() {

	system("cls");

	setlocale(LC_ALL, "");

	FILE* rulesFile = fopen("regras.txt", "a");

	if (rulesFile != NULL) {
		// Move the file pointer to the beginning
		fseek(rulesFile, 0, SEEK_SET);

		char c;
		while ((c = fgetc(rulesFile)) != EOF) {
			putchar(c);
		}

		fclose(rulesFile);
	}
	else {
		printf("Não é possível abrir as regras.\n");
	}
	setlocale(LC_ALL, "C");

}


int passaCarta(baralho* dest, baralho* ori) {

	if (ori->size == 0) { //origem sem cartas
		return -1;
	}
	if (dest->size == dest->maxSize) { // destino cheio
		return -2;
	}
	dest->cartas[dest->size] = ori->cartas[ori->size-1];
	dest->size++;	
	ori->cartas[ori->size - 1] = 'x';
	ori->size--;

	return true;
}

int maoInicial(jogador* jog, baralho* mainDeck) {
	int erro = 0;
	while (jog->mao.maxSize > jog->mao.size) // preencher a mão do jogador
	{
		erro = passaCarta(&(jog->mao), mainDeck);
		if (erro == -1) {
			return false;
		}
	}
	return true;
}

int reporMao(jogador* jog, baralho* mainDeck, baralho* discardDeck) {
	int erro = 0;
	while (jog->mao.maxSize-1 > jog->mao.size) // preencher a mão do jogador
	{
		erro = passaCarta(&(jog->mao), mainDeck);
		if (erro == -1) { // se o deck de bisca ficar vazio ...
			while (discardDeck->size != 0) {
				erro = passaCarta(mainDeck, discardDeck);
				baralharBaralho(mainDeck);
			}

		}
	}
	return true;
}



////Função para inicializar o jogador
int initJogador(jogador* jog, baralho* mainDeck, baralho* betDeck) {

	int tipo;

	printf("\nDigite 1 para jogador humano, 2 para bot: ");
	scanf_s("%d", &tipo);

	printf("\nNome do jogador: ");
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	// Ler o nome
	fgets(jog->nome, sizeof(jog->nome), stdin);

	// Remover o '\n' do final, se houver
	size_t len = strlen(jog->nome);
	if (len > 0 && jog->nome[len - 1] == '\n') {
		jog->nome[len - 1] = '\0';
	}
	
	if (tipo == 1) {
		jog->tipo = HUMAN;
	}
	else if (tipo == 2) {
		jog->tipo = BOT;
	}
	else {
		printf("\nTipo inválido. Tente novamente.");
		return false;
	}

	jog->pontuacao = 0;

	maoInicial(jog, mainDeck);
	passaCarta(&jog->apostas, betDeck);
	passaCarta(&jog->apostas, betDeck);

	passaCarta(&jog->apostas, &jog->mao);


	return true;
}

int fazerContagem(int contagens[], baralho playDeck) {
	int i = 0;
	for (i = 0; i < 6; i++) {
		contagens[i] = 0;
	}
	i = 0;
	while (i < playDeck.size) {
		switch (playDeck.cartas[i])
		{
		case 'L':
			contagens[0]++;
			break;
		case 'T':
			contagens[1]++;
			break;
		case 'W':
			contagens[2]++;
			break;
		case 'w':
			contagens[3]++;
			break;
		case 'R':
			contagens[4]++;
			break;
		case 'C':
			contagens[5]++;
			break;
		default:
			printf("ERROOOOO!!!");
			break;
		}
		i++;
	}
	return NOERROR; 
}

int avancarAnimais(int posicoes[], int contagens[]) {
	if (contagens[3] != 0) {
		if ((contagens[2] + contagens[3]) == 1) {
			posicoes[2] += 1;
		}
		else {
			posicoes[2] += (contagens[2] + contagens[3]) - 1;
		}
		return NOERROR;
	}

	//Lebre
	if (contagens[0]) {
		posicoes[0] += 2;
		//falta ver exceçã0
	}
	//Tartaruga
	if(contagens[1]) {
		posicoes[1]++;
		if (contagens[1] == 4) {
			posicoes[1]++;
		}
	}
	//Lobo
	if (contagens[2]) {
		if (contagens[2] == 1 || contagens[2] == 2) {
			posicoes[2]++;
		}
		if (contagens[2] == 3 || contagens[2] == 4) {
			posicoes[2] += (contagens[2] - 1) ;
		}
	}
	//Raposa
	if (contagens[4]) {
		posicoes[4] += contagens[4];
	}
	//Cordeiro
	if (contagens[5]) {
		posicoes[5] += contagens[5] + 1;
	}
	

	return NOERROR;
}

//novo jogo
void novoJogo()
{
	system("cls");


	baralho* mainDeck = createBaralho(81);
	baralho* discardDeck = createBaralho(81); /*passou a ser obrigatório*/
	baralho* betDeck = createBaralho(5);
	baralho* playDeck = createBaralho(8);	// deck para jogar as cartas


	int posicoes[6] = { 0 }, contagens[6] = { 0 };
	
	if (mainDeck == NULL) {
		return;
	}
	
	
	
	resetBaralho(mainDeck);
	resetBaralho(discardDeck);
	resetBaralho(betDeck);
	resetBaralho(playDeck);
	initBaralho81(mainDeck);
	initBaralhoApostas(betDeck);

	
	baralharBaralho(mainDeck);
	baralharBaralho(betDeck);

	jogador jog[2];
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		createJogador(&jog[i]);
		initJogador(&jog[i], mainDeck, betDeck);
	}
	int firstPlayer = rand() % 2;
	int activePlayer = firstPlayer;

	//Ronda
	//Fase de influência
	while (playDeck->size < playDeck->maxSize) {
		passaCarta(playDeck, &(jog[activePlayer].mao));  //jogar uma carta 
		passaCarta(&(jog[activePlayer].mao), mainDeck);  //repor uma carta
		passaCarta(playDeck, &(jog[!activePlayer].mao)); //jogar uma carta
		passaCarta(&(jog[!activePlayer].mao), mainDeck); //repor uma carta
	}

	//Fase da corrida 

	fazerContagem(contagens, *playDeck);
	avancarAnimais(posicoes, contagens);


	//Descarte da mesa 
	while (playDeck->size != 0) {
		passaCarta(discardDeck, playDeck);
	}



	gotoxy(2, 36); system("pause");

	FILE* fp = NULL;
	fopen_s(&fp, "deck.txt", "w");
	if (fp) {
		fprintf(fp, "mainDeck: ");
		saveBaralho(fp, *mainDeck);
		fprintf(fp, "\nbetDeck");
		saveBaralho(fp, *betDeck);	
		fprintf(fp, "\ndiscardDeck");
		saveBaralho(fp, *discardDeck);
		fprintf(fp, "\nplayDeck");
		saveBaralho(fp, *playDeck);
		fprintf(fp, "\njog[0]: ");
		saveJogador(fp, jog[0]);
		fprintf(fp, "\njog[1]: ");
		saveJogador(fp, jog[1]);
		fprintf(fp, "\ncont:( ");
		for (i = 0; i < 6; i++) {
			fprintf(fp, "%d,", contagens[i]);
		}
		fprintf(fp, "\nani: (");
		for (i = 0; i < 6; i++) {
			fprintf(fp, "%d,", posicoes[i]);
		}
		fclose(fp);
	}

	freeBaralho(&mainDeck);
	freeBaralho(&discardDeck);
	freeBaralho(&betDeck);
	freeBaralho(&playDeck); 
	for (i = 0; i < 2; i++)
	{
		freeJogador(&jog[i]);
	}
}

void carregarJogo() {
	system("cls");


	baralho* mainDeck = createBaralho(81); /*passou a ser obrigatório*/
	if (mainDeck == NULL) {
		return;
	}
	//resetBaralho(&myDeck);

	

	FILE* fp = NULL;
	fopen_s(&fp, "deck.txt", "r");
	if (fp) {
		readBaralho(fp, mainDeck);
		
		fclose(fp);
	}

	gotoxy(2, 8);  printBaralho(*mainDeck); 
	

	freeBaralho(&mainDeck);
	
}

int main() {

	identificação();
	char opcao = '0', check = '0';

	//voltar ao menu, exceto quando clicar na tecla 'D' que fecha o programa 
	do
	{
		check = menu(&opcao);
		switch (opcao)
		{
		case 'A':
			novoJogo();//opção para um jogo novo
			gotoxy(10, 22); system("pause");
			break;
		case 'B':
			carregarJogo();//carregar uma partida 
			gotoxy(10, 22); system("pause");
			break;
		case 'C':
			regras();//regras do jogo
			gotoxy(10, 22); system("pause");
			break;
		case 'D':
			printf("\n bye, bye!");// sair da aplicação
			break;
		default:
			printf("\n ERRO");
			break;
		}
	} while (opcao != 'D');



	gotoxy(10, 22); system("pause");
	return 0;
}