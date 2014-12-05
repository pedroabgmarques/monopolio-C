#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//variaveis globais
int numeroJogadores;

typedef struct regito // registo de casa
{
	int posição;
	char nome[50];
	int preço;

} Casa;

typedef struct registo//registo jogador
{
	char nome[50];
	float saldo;
	int estado;
	Casa propriedadesJogador[40];


}jogador;
//inicializacao de registos
void inciarRegistos()
{
}

//funcao numero de jogadores
void numeroDeJogadores()
{
	
	printf("Insira numero de jogadores.Entre 1 a 8.");
	scanf("%d", &numeroJogadores);

}
void lançamento()
{
	srand(time(NULL));
	int r1 = rand() % 6 + 1;
	int r2 = rand() % 6 + 1;

	int dado1 = 0;
	int dado2 = 0;
	int soma = 0;
	dado1 = r1;
	dado2 = r2;
	soma = dado1 + dado2;
	printf("dado1 = %d\n", dado1);
	printf("dado2 = %d\n", dado2);
	printf("avança %d\n",soma);


}


int main(){

	Casa tabuleiro[40];
	lançamento();

	// teste do ipo de casa
	
	



	
}