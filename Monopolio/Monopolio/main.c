#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct rc // registo de casa
{
	int posição;
	char nome[50];
	int preço;

} Casa;

typedef struct rj//registo jogador
{
	char nome[50];
	float saldo;
	int estado;
	Casa propriedadesJogador[40];


};


int main(){


	return 1;
}