#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct rc // registo de casa
{
	int posi��o;
	char nome[50];
	int pre�o;

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