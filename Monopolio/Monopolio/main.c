#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include "b.c" - inclui outro ficheiro com codigo

//variaveis globais
#define numeroMaximoJogadores 8//define o numero maximo de jogadores
int jogadorActual = 0;
int numeroDeJogadores = 0;
int saldoInicial = 1500;
int gameOver = 0;//passa a 1 quando jogo terminar

//------------------------------------------------------------------
typedef struct rc // registo de casa
{
	int posição;
	char nome[50];
	int preço;
	int renda, renda_com_1_casa, renda_com_2_casas, renda_com_3_casas, renda_com_4_casas, renda_com_hotel;
	int valorHipoteca;
	int precoCasa;
	int precoHotel;
	int dono;
	int estado;//0 para livre, 1 se tiver dono
	int hipotecada;//0 quando nao hipotecada, 1 para hipotecada





} Casa;
//-------------------------------------------------------------------
typedef struct registo//registo jogador
{
	char nome[50];
	int saldo;
	int estado;//0 se puder jogar, 1 se estiver preso e nao puder jogar,
	int posicao;
	Casa propriedadesJogador[40];


}jogador;
//inicializacao de registos--------------------------------------------------------------------------
void criarTabuleiro(Casa tabuleiro[40])
{

	//jogador jogadores[numeroMaximoJogadores];
	//definicao das casas do tabuleiro
	strcpy(tabuleiro[0].nome, "Casa Partida");

	strcpy(tabuleiro[1].nome, "Mediterranean Avenue");
	tabuleiro[1].preço = 60;
	tabuleiro[1].estado = 0;

	strcpy(tabuleiro[2].nome, "Community Chest");

	strcpy(tabuleiro[3].nome, "Baltic Avenue");
	tabuleiro[3].preço = 60;
	tabuleiro[3].estado = 0;

	strcpy(tabuleiro[4].nome, "Income Tax");

	strcpy(tabuleiro[5].nome, "Reading Railroad");
	tabuleiro[5].preço = 200;
	tabuleiro[5].estado = 0;

	strcpy(tabuleiro[6].nome, "Oriental Avenue");
	tabuleiro[6].preço = 100;
	tabuleiro[6].estado = 0;

	strcpy(tabuleiro[7].nome, "Chance");

	strcpy(tabuleiro[8].nome, "Vermount Avenue");
	tabuleiro[8].preço = 100;
	tabuleiro[8].estado = 0;

	strcpy(tabuleiro[9].nome, "Connectikut Avenue");
	tabuleiro[9].preço = 120;
	tabuleiro[9].estado = 0;

	strcpy(tabuleiro[10].nome, "Jail");

	strcpy(tabuleiro[11].nome, "St Charles Place");
	tabuleiro[11].preço = 140;
	tabuleiro[11].estado = 0;

	strcpy(tabuleiro[12].nome, "Electric Company");
	tabuleiro[12].preço = 150;
	tabuleiro[12].estado = 0;

	strcpy(tabuleiro[13].nome, "States Avenue");
	tabuleiro[13].preço = 140;
	tabuleiro[13].estado = 0;

	strcpy(tabuleiro[14].nome, "Virginia Avenue");
	tabuleiro[14].preço = 160;
	tabuleiro[14].estado = 0;

	strcpy(tabuleiro[15].nome, "Pennsylvania Railroad");
	tabuleiro[15].preço = 200;
	tabuleiro[15].estado = 0;

	strcpy(tabuleiro[16].nome, "St James Place");
	tabuleiro[16].preço = 180;
	tabuleiro[16].estado = 0;

	strcpy(tabuleiro[17].nome, "Community Chest");

	strcpy(tabuleiro[18].nome, "Tennesse Avenue");
	tabuleiro[18].preço = 180;
	tabuleiro[18].estado = 0;

	strcpy(tabuleiro[19].nome, "NewYork Avenue");
	tabuleiro[19].preço = 200;
	tabuleiro[19].estado = 0;

	strcpy(tabuleiro[20].nome, "Free Parking");

	strcpy(tabuleiro[21].nome, "Kentucky Avenue");
	tabuleiro[21].preço = 220;
	tabuleiro[21].estado = 0;

	strcpy(tabuleiro[22].nome, "Chance");

	strcpy(tabuleiro[23].nome, "Indiana Avenue");
	tabuleiro[23].preço = 220;
	tabuleiro[23].estado = 0;

	strcpy(tabuleiro[24].nome, "Illinois Avenue");
	tabuleiro[24].preço = 240;
	tabuleiro[24].estado = 0;

	strcpy(tabuleiro[25].nome, "B & O Railroad");
	tabuleiro[25].preço = 200;
	tabuleiro[25].estado = 0;

	strcpy(tabuleiro[26].nome, "Atlantic Avenue");
	tabuleiro[26].preço = 260;
	tabuleiro[26].estado = 0;

	strcpy(tabuleiro[27].nome, "Ventnor Avenue");
	tabuleiro[27].preço = 260;
	tabuleiro[27].estado = 0;

	strcpy(tabuleiro[28].nome, "Water Works");
	tabuleiro[28].preço = 150;
	tabuleiro[28].estado = 0;

	strcpy(tabuleiro[29].nome, "Marvin Gardens");
	tabuleiro[29].preço = 280;
	tabuleiro[29].estado = 0;

	strcpy(tabuleiro[30].nome, "Go To Jail");

	strcpy(tabuleiro[31].nome, "Pacific Avenue");
	tabuleiro[31].preço = 300;
	tabuleiro[31].estado = 0;

	strcpy(tabuleiro[32].nome, "North Carolina Avenue");
	tabuleiro[32].preço = 300;
	tabuleiro[32].estado = 0;

	strcpy(tabuleiro[33].nome, "Community Chest");

	strcpy(tabuleiro[34].nome, "Pennsylvania Avenue");
	tabuleiro[34].preço = 320;
	tabuleiro[34].estado = 0;

	strcpy(tabuleiro[35].nome, "Short Line");
	tabuleiro[35].preço = 200;
	tabuleiro[35].estado = 0;

	strcpy(tabuleiro[36].nome, "Chance");

	strcpy(tabuleiro[37].nome, "Park Place");
	tabuleiro[37].preço = 350;
	tabuleiro[37].estado = 0;

	strcpy(tabuleiro[38].nome, "Luxury Tax");

	strcpy(tabuleiro[39].nome, "Boardwalk");
	tabuleiro[39].preço = 400;
	tabuleiro[39].estado = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------
void definirNumeroDeJogadores()//pede ao utilizador o numero de jogadores.Volta a pedir se for inserido um numero fora do intervalo 1 a 8.
//variavel numeroDeJogadores é global.
{

	do
	{
		printf("Escolha numero de jogadores: ");
		scanf("%d", &numeroDeJogadores);
	} while (numeroDeJogadores<1 || numeroDeJogadores>numeroMaximoJogadores);

}
//criar jogadores-------------------------------------------------------------------------------------
void criarJogadores(jogador jogadores[numeroMaximoJogadores])
{

	for (int i = 0; i < numeroDeJogadores; i++)
	{
		printf("Nome do jogador %d: ", i + 1);
		scanf("%s", jogadores[i].nome);
		jogadores[i].saldo = saldoInicial;
		jogadores[i].estado = 0;
		jogadores[i].posicao = 0;

	}

}
//apresentar lancamento de dados------------------------------------------------------------------------
int lancamentoDados(jogador jogadores[numeroMaximoJogadores])
{

	srand((unsigned)time(0));
	int dado1 = (rand() % 6) + 1;
	int dado2 = (rand() % 6) + 1;
	int resultado = dado1 + dado2;
	printf("\njogador %s %d + %d Total: %d\n", jogadores[jogadorActual].nome, dado1, dado2, resultado);
	return(resultado);
}
//calucular em que casa cai o jogador------------------------------------------------------------------------
void jogar(jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40])
{
	int resultadoLancamentoDados = lancamentoDados(jogadores);
	jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao + resultadoLancamentoDados;
	//quando acaba o tabuleiro faz a conta para continuar
	if (jogadores[jogadorActual].posicao >= 40)
	{
		jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao - 40;
	}
	//return(jogadores[jogadorActual].posicao); teste
	//printf("\n%d",jogadores[jogadorActual].posicao); teste
	int posicao = jogadores[jogadorActual].posicao;
	switch (posicao)
	{
	case 0:printf("%s", tabuleiro[posicao].nome); break;//colocar funcao para cada casa
	case 1:printf("%s", tabuleiro[posicao].nome); break;
	case 2:printf("%s", tabuleiro[posicao].nome); break;
	case 3:printf("%s", tabuleiro[posicao].nome); break;
	case 4:printf("%s", tabuleiro[posicao].nome); break;
	case 5:printf("%s", tabuleiro[posicao].nome); break;
	case 6:printf("%s", tabuleiro[posicao].nome); break;
	case 7:printf("%s", tabuleiro[posicao].nome); break;
	case 8:printf("%s", tabuleiro[posicao].nome); break;
	case 9:printf("%s", tabuleiro[posicao].nome); break;
	case 10:printf("%s", tabuleiro[posicao].nome); break;
	case 11:printf("%s", tabuleiro[posicao].nome); break;
	case 12:printf("%s", tabuleiro[posicao].nome); break;
	case 13:printf("%s", tabuleiro[posicao].nome); break;
	case 14:printf("%s", tabuleiro[posicao].nome); break;
	case 15:printf("%s", tabuleiro[posicao].nome); break;
	case 16:printf("%s", tabuleiro[posicao].nome); break;
	case 17:printf("%s", tabuleiro[posicao].nome); break;
	case 18:printf("%s", tabuleiro[posicao].nome); break;
	case 19:printf("%s", tabuleiro[posicao].nome); break;
	case 20:printf("%s", tabuleiro[posicao].nome); break;
	case 21:printf("%s", tabuleiro[posicao].nome); break;
	case 22:printf("%s", tabuleiro[posicao].nome); break;
	case 23:printf("%s", tabuleiro[posicao].nome); break;
	case 24:printf("%s", tabuleiro[posicao].nome); break;
	case 25:printf("%s", tabuleiro[posicao].nome); break;
	case 26:printf("%s", tabuleiro[posicao].nome); break;
	case 27:printf("%s", tabuleiro[posicao].nome); break;
	case 28:printf("%s", tabuleiro[posicao].nome); break;
	case 29:printf("%s", tabuleiro[posicao].nome); break;
	case 30:printf("%s", tabuleiro[posicao].nome); break;
	case 31:printf("%s", tabuleiro[posicao].nome); break;
	case 32:printf("%s", tabuleiro[posicao].nome); break;
	case 33:printf("%s", tabuleiro[posicao].nome); break;
	case 34:printf("%s", tabuleiro[posicao].nome); break;
	case 35:printf("%s", tabuleiro[posicao].nome); break;
	case 36:printf("%s", tabuleiro[posicao].nome); break;
	case 37:printf("%s", tabuleiro[posicao].nome); break;
	case 38:printf("%s", tabuleiro[posicao].nome); break;
	case 39:printf("%s", tabuleiro[posicao].nome); break;
	}
}
//trocar de jogador------------------------------------------------------------------------------------------------
void trocarJogador()
{
	if (jogadorActual >= numeroDeJogadores - 1)
	{
		jogadorActual = 0;
	}
	else
	{
		jogadorActual++;
		printf("\n");
	}
}
//Main------------------------------------------------------------------------------------------------------------------------------
int main()
{
	Casa tabuleiro[40];
	jogador jogadores[numeroMaximoJogadores];
	criarTabuleiro(tabuleiro);

	definirNumeroDeJogadores();
	criarJogadores(jogadores);
	while (gameOver == 0)
	{
		jogar(jogadores, tabuleiro);
		trocarJogador();
		system("pause");
	}
	/*teste de inicializacao de jogadores
	printf("%s", jogadores[0].nome);
	printf("%d", jogadores[0].saldo);
	printf("%s", jogadores[1].nome);
	printf("%d", jogadores[1].saldo);
	//fim de teste*/

	system("pause");
}
