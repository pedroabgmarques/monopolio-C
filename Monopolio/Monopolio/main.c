#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include "b.c" - inclui outro ficheiro com codigo

//variaveis globais
#define numeroMaximoJogadores 8//define o numero maximo de jogadores

typedef struct rc // registo de casa
{
	int posi��o;
	char nome[50];
	int pre�o;
	
	

} Casa;

typedef struct registo//registo jogador
{
	char nome[50];
	float saldo;
	int estado;
	Casa propriedadesJogador[40];


}jogador;
//inicializacao de registos
void iniciarRegistos()
{
	Casa tabuleiro[40];
	jogador jogadores[numeroMaximoJogadores];
	//definicao das casas do tabuleiro
	strcpy(tabuleiro[0].nome, "Casa Partida");

	strcpy(tabuleiro[1].nome, "Mediterranean Avenue");
	tabuleiro[1].pre�o = 60;

	strcpy(tabuleiro[2].nome,"Community Chest");
	
	strcpy(tabuleiro[3].nome, "Baltic Avenue");
	tabuleiro[3].pre�o = 60;

	strcpy(tabuleiro[4].nome, "Income Tax");

	strcpy(tabuleiro[5].nome, "Reading Railroad");
	tabuleiro[5].pre�o = 200;

	strcpy(tabuleiro[6].nome, "Oriental Avenue");
	tabuleiro[6].pre�o = 100;

	strcpy(tabuleiro[7].nome, "Chance");

	strcpy(tabuleiro[8].nome, "Vermount Avenue");
	tabuleiro[8].pre�o = 100;

	strcpy(tabuleiro[9].nome, "Connectikut Avenue");
	tabuleiro[9].pre�o = 120;

	strcpy(tabuleiro[10].nome, "Jail");

	strcpy(tabuleiro[11].nome, "St Charles Place");
	tabuleiro[11].pre�o = 140;

	strcpy(tabuleiro[12].nome, "Electric Company");
	tabuleiro[12].pre�o = 150;
	
	strcpy(tabuleiro[13].nome, "States Avenue");
	tabuleiro[13].pre�o = 140;

	strcpy(tabuleiro[14].nome, "Virginia Avenue");
	tabuleiro[14].pre�o = 160;

	strcpy(tabuleiro[15].nome, "Pennsylvania Railroad");
	tabuleiro[15].pre�o = 200;

	strcpy(tabuleiro[16].nome, "St James Place");
	tabuleiro[16].pre�o = 180;

	strcpy(tabuleiro[17].nome, "Community Chest");

	strcpy(tabuleiro[18].nome, "Tennesse Avenue");
	tabuleiro[18].pre�o = 180;

	strcpy(tabuleiro[19].nome, "NewYork Avenue");
	tabuleiro[19].pre�o = 200;

	strcpy(tabuleiro[20].nome, "Free Parking");

	strcpy(tabuleiro[21].nome, "Kentucky Avenue");
	tabuleiro[21].pre�o = 220;

	strcpy(tabuleiro[22].nome, "Chance");

	strcpy(tabuleiro[23].nome, "Indiana Avenue");
	tabuleiro[23].pre�o = 220;

	strcpy(tabuleiro[24].nome, "Illinois Avenue");
	tabuleiro[24].pre�o = 240;

	strcpy(tabuleiro[25].nome, "B & O Railroad");
	tabuleiro[25].pre�o = 200;

	strcpy(tabuleiro[26].nome, "Atlantic Avenue");
	tabuleiro[26].pre�o = 260;

	strcpy(tabuleiro[27].nome, "Ventnor Avenue");
	tabuleiro[27].pre�o = 260;

	strcpy(tabuleiro[28].nome, "Water Works");
	tabuleiro[28].pre�o = 150;

	strcpy(tabuleiro[29].nome, "Marvin Gardens");
	tabuleiro[29].pre�o = 280;

	strcpy(tabuleiro[30].nome, "Go To Jail");

	strcpy(tabuleiro[31].nome, "Pacific Avenue");
	tabuleiro[31].pre�o = 300;

	strcpy(tabuleiro[32].nome, "North Carolina Avenue");
	tabuleiro[32].pre�o = 300;

	strcpy(tabuleiro[33].nome, "Community Chest");

	strcpy(tabuleiro[34].nome, "Pennsylvania Avenue");
	tabuleiro[34].pre�o = 320;

	strcpy(tabuleiro[35].nome, "Short Line");
	tabuleiro[35].pre�o = 200;

	strcpy(tabuleiro[36].nome, "Chance");

	strcpy(tabuleiro[37].nome, "Park Place");
	tabuleiro[37].pre�o = 350;

	strcpy(tabuleiro[38].nome, "Luxury Tax");

	strcpy(tabuleiro[39].nome, "Boardwalk");
	tabuleiro[39].pre�o = 400;
}


int main()
{


	
	



	
}