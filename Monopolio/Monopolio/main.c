#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//variaveis globais
int numeroJogadores;

typedef struct rc // registo de casa
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

int main(){


	
}