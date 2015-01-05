#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>



//variaveis globais
#define numeroMaximoJogadores 8//define o numero maximo de jogadores
int jogadorActual = 0;
int numeroDeJogadores = 0;
int saldoInicial = 1500;
int gameOver = 0;//passa a 1 quando jogo terminar
int posicaoActual;
int numeroCartaComunidade = 0;
int numeroCartaSorte = 0;
int ultimoLancamento;//guarda o ultimo lancamento de dados.variavel usada para calcular o valor a pagar caso caia numa casa de utilidade
FILE* data;

typedef struct estruturaCaixaComunidade
{
	int idCarta;
	char texto[100];



}caixaComunidade;


//------------------------------------------------------------------
typedef struct estruturaCasa // registo de casa
{
	int posicao;
	char nome[50];
	char cor[20];
	int preço;
	int renda, renda_1_casa, renda_2_casas, renda_3_casas, renda_4_casas, renda_hotel;
	int valorHipoteca;
	int precoCasa;
	int precoHotel;
	int dono;
	int estado;//0 para livre, 1 se tiver dono
	int hipotecada;//0 quando nao hipotecada, 1 para hipotecada
	int numeroCasas;//guarda a quantidade de casas construidas nessa propriedade
	int hotel;
	int codigoCor;//serve para verificar se um jogador possui todas as casas dessa cor 1-roxo 2-azul claro 3-rosa 4-laranja 5-vermelho 6-amarelo 7-verde 8-azul
	int hipoteca;//valor a receber por hipotecar a casa






} Casa;
//-------------------------------------------------------------------
typedef struct estruturaJogador//registo jogador
{
	char nome[50];
	int saldo;
	int estado;//0 se puder jogar, 1 se estiver preso e nao puder jogar,
	int posicao;
	int quantidadeCasas;
	Casa propriedadesJogador[40];
	int id; //identificador de jogador para usar na compra e verificação de casas.
	int NumVezesSemJogar;// regista a vezes em que o jogar fica sem jogar
	int cartaLivreDaPrisao;
	int estacoes;//regista o numero de estacoes que o jogador possui
	int utilidade;//regista o numero de casas de tulidade que o jogador possui


}jogador;
//inicializacao de registos--------------------------------------------------------------------------
void criarComunidade(caixaComunidade comunidade[15])
{
	comunidade[0].idCarta = 1;
	strcpy(comunidade[0].texto, "Avance para a Casa Partida e ganha 200€");
	comunidade[1].idCarta = 2;
	strcpy(comunidade[1].texto, "Erro do banco a seu favor. Ganha 75€");
	comunidade[2].idCarta = 3;
	strcpy(comunidade[2].texto, "Conta do Médico: Pague 50€");
	comunidade[3].idCarta = 4;
	strcpy(comunidade[3].texto, "Voce esta livre da prisao.");
	comunidade[4].idCarta = 5;
	strcpy(comunidade[4].texto, "E o seu aniversario. Ganhe 10€ de Cada jogador.");
	comunidade[5].idCarta = 6;
	strcpy(comunidade[5].texto, "IRS. Ganha 20€");
	comunidade[6].idCarta = 7;
	strcpy(comunidade[6].texto, "Seguro de Vida. Ganhe 100€");
	comunidade[7].idCarta = 8;
	strcpy(comunidade[7].texto, "Pague conta do Hospital 100€");
	comunidade[8].idCarta = 9;
	strcpy(comunidade[8].texto, "Pagamento de Propinas 50€");
	comunidade[9].idCarta = 10;
	strcpy(comunidade[9].texto, "Pagamento por servicos prestados. Ganha 25€");
	comunidade[10].idCarta = 10;
	strcpy(comunidade[10].texto, "Conta de reparacao dos seus edificios. 40€ por cada casa. 150€ por cada hotel");
	comunidade[11].idCarta = 10;
	strcpy(comunidade[11].texto, "Ganhou um concurso de beleza. Ganha 10€");
	comunidade[12].idCarta = 10;
	strcpy(comunidade[12].texto, "Heranca. Ganha 100€");
	comunidade[13].idCarta = 10;
	strcpy(comunidade[13].texto, "Subsidio de ferias. Ganha 100€");
	comunidade[14].idCarta = 10;
	strcpy(comunidade[14].texto, "Grande noite de Opera. Receba 50€ de cada jogador pelos bilhetes para a estreia.");
}

//criar Sorte-------------------------------------------
void criarSorte(caixaComunidade sorte[15])
{
	sorte[0].idCarta = 1;
	strcpy(sorte[0].texto, "Avance para a Casa Partida e ganha 200€");
	sorte[1].idCarta = 2;
	strcpy(sorte[1].texto, "Avance para a Rua Santa Catarina.");
	sorte[2].idCarta = 3;
	strcpy(sorte[2].texto, "Avance para a proxima casa de utilidade.");
	sorte[3].idCarta = 4;
	strcpy(sorte[3].texto, "Avance ate a proxima Estacao.");
	sorte[4].idCarta = 5;
	strcpy(sorte[4].texto, "Venceu uma competicao de palavras cruzadas. Ganha 100€");
	sorte[5].idCarta = 6;
	strcpy(sorte[5].texto, "Dividendos do Banco. Ganha 50€");
	sorte[6].idCarta = 7;
	strcpy(sorte[6].texto, "Voce esta livre da prisao.");
	sorte[7].idCarta = 8;
	strcpy(sorte[7].texto, "Retroceda 3 casas.");
	sorte[8].idCarta = 9;
	strcpy(sorte[8].texto, "Va directamente para a prisao, sem passar pela Casa Partida e sem receber 200€.");
	sorte[9].idCarta = 10;
	strcpy(sorte[9].texto, "Faca reparacoes nos seus edificios. 25€ por cada Casa. 100€ por cada Hotel ");
	sorte[10].idCarta = 10;
	strcpy(sorte[10].texto, "Pague impostos 15€");
	sorte[11].idCarta = 10;
	strcpy(sorte[11].texto, "Va para a Estacao da Campanha. Se passar pela Casa Partida receba 200€.");
	sorte[12].idCarta = 10;
	strcpy(sorte[12].texto, "Va para o Rossio.");
	sorte[13].idCarta = 10;
	strcpy(sorte[13].texto, "Foi eleito presidente da direcao. Pague a cada jogador 50€");
	sorte[14].idCarta = 10;
	strcpy(sorte[14].texto, "O seu emprestimo terminou. Ganha 150€");
}
//---cria tabuleiro-----------------------------------------------------------
void criarTabuleiro(Casa tabuleiro[40])
{

	//jogador jogadores[numeroMaximoJogadores];
	//definicao das casas do tabuleiro
	strcpy(tabuleiro[0].nome, "Casa Partida");
	strcpy(tabuleiro[0].cor, "");


	strcpy(tabuleiro[1].nome, "Campo Grande");
	strcpy(tabuleiro[1].cor, "Roxo");
	tabuleiro[1].preço = 60;
	tabuleiro[1].estado = 0;
	tabuleiro[1].dono = 0;
	tabuleiro[1].renda = 2;
	tabuleiro[1].numeroCasas = 0;
	tabuleiro[1].hotel = 0;
	tabuleiro[1].precoCasa = 50;
	tabuleiro[1].precoHotel = 50;
	tabuleiro[1].renda_1_casa = 10;
	tabuleiro[1].renda_2_casas = 30;
	tabuleiro[1].renda_3_casas = 90;
	tabuleiro[1].renda_4_casas = 160;
	tabuleiro[1].renda_hotel = 250;
	tabuleiro[1].codigoCor = 1;
	tabuleiro[1].hipoteca = 30;
	tabuleiro[1].posicao = 1;
	tabuleiro[1].hipotecada = 0;


	strcpy(tabuleiro[2].nome, "Caixa Comunidade");
	strcpy(tabuleiro[2].cor, "");

	strcpy(tabuleiro[3].nome, "Avenida Fernão De Magalhães");
	strcpy(tabuleiro[3].cor, "Roxo");
	tabuleiro[3].preço = 60;
	tabuleiro[3].estado = 0;
	tabuleiro[3].dono = 0;
	tabuleiro[3].renda = 4;
	tabuleiro[3].numeroCasas = 0;
	tabuleiro[3].hotel = 0;
	tabuleiro[3].precoCasa = 50;
	tabuleiro[3].precoHotel = 50;
	tabuleiro[3].renda_1_casa = 20;
	tabuleiro[3].renda_2_casas = 60;
	tabuleiro[3].renda_3_casas = 180;
	tabuleiro[3].renda_4_casas = 320;
	tabuleiro[3].renda_hotel = 450;
	tabuleiro[3].codigoCor = 1;
	tabuleiro[3].hipoteca = 30;
	tabuleiro[3].posicao = 3;
	tabuleiro[3].hipotecada = 0;

	strcpy(tabuleiro[4].nome, "Imposto Sobre Renda");
	strcpy(tabuleiro[4].cor, "");

	strcpy(tabuleiro[5].nome, "Estacao do Rossio");
	strcpy(tabuleiro[5].cor, "");
	tabuleiro[5].preço = 200;
	tabuleiro[5].estado = 0;
	tabuleiro[5].dono = 0;
	tabuleiro[5].hipoteca = 100;
	tabuleiro[5].posicao = 5;
	tabuleiro[5].codigoCor = 0;
	tabuleiro[5].hipotecada = 0;

	strcpy(tabuleiro[6].nome, "Avenida Almirante Reis");
	strcpy(tabuleiro[6].cor, "Azul claro");
	tabuleiro[6].preço = 100;
	tabuleiro[6].estado = 0;
	tabuleiro[6].dono = 0;
	tabuleiro[6].renda = 6;
	tabuleiro[6].numeroCasas = 0;
	tabuleiro[6].hotel = 0;
	tabuleiro[6].precoCasa = 50;
	tabuleiro[6].precoHotel = 50;
	tabuleiro[6].renda_1_casa = 30;
	tabuleiro[6].renda_2_casas = 90;
	tabuleiro[6].renda_3_casas = 270;
	tabuleiro[6].renda_4_casas = 400;
	tabuleiro[6].renda_hotel = 550;
	tabuleiro[6].codigoCor = 2;
	tabuleiro[6].hipoteca = 50;
	tabuleiro[6].posicao = 6;
	tabuleiro[6].hipotecada = 0;

	strcpy(tabuleiro[7].nome, "Sorte");
	strcpy(tabuleiro[7].cor, "");

	strcpy(tabuleiro[8].nome, "Avenida Todi");
	strcpy(tabuleiro[8].cor, "Azul claro");
	tabuleiro[8].preço = 100;
	tabuleiro[8].estado = 0;
	tabuleiro[8].dono = 0;
	tabuleiro[8].renda = 6;
	tabuleiro[8].numeroCasas = 0;
	tabuleiro[8].hotel = 0;
	tabuleiro[8].precoCasa = 50;
	tabuleiro[8].precoHotel = 50;
	tabuleiro[8].renda_1_casa = 30;
	tabuleiro[8].renda_2_casas = 90;
	tabuleiro[8].renda_3_casas = 270;
	tabuleiro[8].renda_4_casas = 400;
	tabuleiro[8].renda_hotel = 550;
	tabuleiro[8].codigoCor = 2;
	tabuleiro[8].hipoteca = 50;
	tabuleiro[8].posicao = 8;
	tabuleiro[8].hipotecada = 0;

	strcpy(tabuleiro[9].nome, "Avenida 24 de Julho");
	strcpy(tabuleiro[9].cor, "Azul claro");
	tabuleiro[9].preço = 120;
	tabuleiro[9].estado = 0;
	tabuleiro[9].dono = 0;
	tabuleiro[9].renda = 8;
	tabuleiro[9].numeroCasas = 0;
	tabuleiro[9].hotel = 0;
	tabuleiro[9].precoCasa = 50;
	tabuleiro[9].precoHotel = 50;
	tabuleiro[9].renda_1_casa = 40;
	tabuleiro[9].renda_2_casas = 100;
	tabuleiro[9].renda_3_casas = 300;
	tabuleiro[9].renda_4_casas = 450;
	tabuleiro[9].renda_hotel = 600;
	tabuleiro[9].codigoCor = 2;
	tabuleiro[9].hipoteca = 60;
	tabuleiro[9].posicao = 9;
	tabuleiro[9].hipotecada = 0;

	strcpy(tabuleiro[10].nome, "Prisão");
	strcpy(tabuleiro[10].cor, "");

	strcpy(tabuleiro[11].nome, "Avenida dos Combatentes");
	strcpy(tabuleiro[11].cor, "Rosa");
	tabuleiro[11].preço = 140;
	tabuleiro[11].estado = 0;
	tabuleiro[11].dono = 0;
	tabuleiro[11].renda = 10;
	tabuleiro[11].numeroCasas = 0;
	tabuleiro[11].hotel = 0;
	tabuleiro[11].precoCasa = 100;
	tabuleiro[11].precoHotel = 100;
	tabuleiro[11].renda_1_casa = 50;
	tabuleiro[11].renda_2_casas = 150;
	tabuleiro[11].renda_3_casas = 450;
	tabuleiro[11].renda_4_casas = 625;
	tabuleiro[11].renda_hotel = 750;
	tabuleiro[11].codigoCor = 3;
	tabuleiro[11].hipoteca = 70;
	tabuleiro[11].posicao = 11;
	tabuleiro[11].hipotecada = 0;

	strcpy(tabuleiro[12].nome, "Companhia Electricidade");
	strcpy(tabuleiro[12].cor, "");
	tabuleiro[12].preço = 150;
	tabuleiro[12].estado = 0;
	tabuleiro[12].dono = 0;
	tabuleiro[12].hipoteca = 75;
	tabuleiro[12].posicao = 12;
	tabuleiro[12].hipotecada = 0;

	strcpy(tabuleiro[13].nome, "Rua Ferreira Borges");
	strcpy(tabuleiro[13].cor, "Rosa");
	tabuleiro[13].preço = 140;
	tabuleiro[13].estado = 0;
	tabuleiro[13].dono = 0;
	tabuleiro[13].renda = 10;
	tabuleiro[13].numeroCasas = 0;
	tabuleiro[13].hotel = 0;
	tabuleiro[13].precoCasa = 100;
	tabuleiro[13].precoHotel = 100;
	tabuleiro[13].renda_1_casa = 50;
	tabuleiro[13].renda_2_casas = 150;
	tabuleiro[13].renda_3_casas = 450;
	tabuleiro[13].renda_4_casas = 625;
	tabuleiro[13].renda_hotel = 750;
	tabuleiro[13].codigoCor = 3;
	tabuleiro[13].hipoteca = 70;
	tabuleiro[13].posicao = 13;
	tabuleiro[13].hipotecada = 0;

	strcpy(tabuleiro[14].nome, "Avenida de Roma");
	strcpy(tabuleiro[14].cor, "Rosa");
	tabuleiro[14].preço = 160;
	tabuleiro[14].estado = 0;
	tabuleiro[14].dono = 0;
	tabuleiro[14].renda = 12;
	tabuleiro[14].numeroCasas = 0;
	tabuleiro[14].hotel = 0;
	tabuleiro[14].precoCasa = 50;
	tabuleiro[14].precoHotel = 50;
	tabuleiro[14].renda_1_casa = 60;
	tabuleiro[14].renda_2_casas = 180;
	tabuleiro[14].renda_3_casas = 500;
	tabuleiro[14].renda_4_casas = 700;
	tabuleiro[14].renda_hotel = 900;
	tabuleiro[14].codigoCor = 3;
	tabuleiro[14].hipoteca = 80;
	tabuleiro[14].posicao = 14;
	tabuleiro[14].hipotecada = 0;

	strcpy(tabuleiro[15].nome, "Estação da Campanhã");
	strcpy(tabuleiro[15].cor, "");
	tabuleiro[15].preço = 200;
	tabuleiro[15].estado = 0;
	tabuleiro[15].dono = 0;
	tabuleiro[15].hipoteca = 100;
	tabuleiro[15].posicao = 15;
	tabuleiro[15].codigoCor = 0;
	tabuleiro[15].hipotecada = 0;

	strcpy(tabuleiro[16].nome, "Avenida da Boavista");
	strcpy(tabuleiro[16].cor, "Laranja");
	tabuleiro[16].preço = 180;
	tabuleiro[16].estado = 0;
	tabuleiro[16].dono = 0;
	tabuleiro[16].renda = 14;
	tabuleiro[16].numeroCasas = 0;
	tabuleiro[16].hotel = 0;
	tabuleiro[16].precoCasa = 100;
	tabuleiro[16].precoHotel = 100;
	tabuleiro[16].renda_1_casa = 70;
	tabuleiro[16].renda_2_casas = 200;
	tabuleiro[16].renda_3_casas = 550;
	tabuleiro[16].renda_4_casas = 750;
	tabuleiro[16].renda_hotel = 950;
	tabuleiro[16].codigoCor = 4;
	tabuleiro[16].hipoteca = 90;
	tabuleiro[16].posicao = 16;
	tabuleiro[16].hipotecada = 0;

	strcpy(tabuleiro[17].nome, "Caixa Comunidade");
	strcpy(tabuleiro[17].cor, "");

	strcpy(tabuleiro[18].nome, "Avenida da Republica");
	strcpy(tabuleiro[18].cor, "Laranja");
	tabuleiro[18].preço = 180;
	tabuleiro[18].estado = 0;
	tabuleiro[18].dono = 0;
	tabuleiro[18].renda = 14;
	tabuleiro[18].numeroCasas = 0;
	tabuleiro[18].hotel = 0;
	tabuleiro[18].precoCasa = 100;
	tabuleiro[18].precoHotel = 100;
	tabuleiro[18].renda_1_casa = 70;
	tabuleiro[18].renda_2_casas = 200;
	tabuleiro[18].renda_3_casas = 550;
	tabuleiro[18].renda_4_casas = 750;
	tabuleiro[18].renda_hotel = 950;
	tabuleiro[18].codigoCor = 4;
	tabuleiro[18].hipoteca = 90;
	tabuleiro[18].posicao = 18;
	tabuleiro[18].hipotecada = 0;

	strcpy(tabuleiro[19].nome, "Rua Sá da Bandeira");
	strcpy(tabuleiro[19].cor, "Laranja");
	tabuleiro[19].preço = 200;
	tabuleiro[19].estado = 0;
	tabuleiro[19].dono = 0;
	tabuleiro[19].renda = 16;
	tabuleiro[19].numeroCasas = 0;
	tabuleiro[19].hotel = 0;
	tabuleiro[19].precoCasa = 100;
	tabuleiro[19].precoHotel = 100;
	tabuleiro[19].renda_1_casa = 80;
	tabuleiro[19].renda_2_casas = 220;
	tabuleiro[19].renda_3_casas = 600;
	tabuleiro[19].renda_4_casas = 800;
	tabuleiro[19].renda_hotel = 1000;
	tabuleiro[19].codigoCor = 4;
	tabuleiro[19].hipoteca = 100;
	tabuleiro[19].posicao = 19;
	tabuleiro[19].hipotecada = 0;

	strcpy(tabuleiro[20].nome, "Estacionamento Livre");
	strcpy(tabuleiro[20].cor, "");

	strcpy(tabuleiro[21].nome, "Rua de Santa Catarina");
	strcpy(tabuleiro[21].cor, "Vermelho");
	tabuleiro[21].preço = 220;
	tabuleiro[21].estado = 0;
	tabuleiro[21].dono = 0;
	tabuleiro[21].renda = 18;
	tabuleiro[21].numeroCasas = 0;
	tabuleiro[21].hotel = 0;
	tabuleiro[21].precoCasa = 150;
	tabuleiro[21].precoHotel = 150;
	tabuleiro[21].renda_1_casa = 90;
	tabuleiro[21].renda_2_casas = 250;
	tabuleiro[21].renda_3_casas = 700;
	tabuleiro[21].renda_4_casas = 875;
	tabuleiro[21].renda_hotel = 1050;
	tabuleiro[21].codigoCor = 5;
	tabuleiro[21].hipoteca = 110;
	tabuleiro[21].posicao = 21;
	tabuleiro[21].hipotecada = 0;

	strcpy(tabuleiro[22].nome, "Sorte");
	strcpy(tabuleiro[22].cor, "");

	strcpy(tabuleiro[23].nome, "Rua do Carmo");
	strcpy(tabuleiro[23].cor, "Vermelho");
	tabuleiro[23].preço = 220;
	tabuleiro[23].estado = 0;
	tabuleiro[23].dono = 0;
	tabuleiro[23].renda = 18;
	tabuleiro[23].numeroCasas = 0;
	tabuleiro[23].hotel = 0;
	tabuleiro[23].precoCasa = 150;
	tabuleiro[23].precoHotel = 150;
	tabuleiro[23].renda_1_casa = 90;
	tabuleiro[23].renda_2_casas = 250;
	tabuleiro[23].renda_3_casas = 700;
	tabuleiro[23].renda_4_casas = 875;
	tabuleiro[23].renda_hotel = 1050;
	tabuleiro[23].codigoCor = 5;
	tabuleiro[23].hipoteca = 110;
	tabuleiro[23].posicao = 23;
	tabuleiro[23].hipotecada = 0;

	strcpy(tabuleiro[24].nome, "Avenida Marechal Gomes da Costa");
	strcpy(tabuleiro[24].cor, "Vermelho");
	tabuleiro[24].preço = 240;
	tabuleiro[24].estado = 0;
	tabuleiro[24].dono = 0;
	tabuleiro[24].renda = 20;
	tabuleiro[24].numeroCasas = 0;
	tabuleiro[24].hotel = 0;
	tabuleiro[24].precoCasa = 150;
	tabuleiro[24].precoHotel = 150;
	tabuleiro[24].renda_1_casa = 100;
	tabuleiro[24].renda_2_casas = 300;
	tabuleiro[24].renda_3_casas = 750;
	tabuleiro[24].renda_4_casas = 925;
	tabuleiro[24].renda_hotel = 1100;
	tabuleiro[24].codigoCor = 5;
	tabuleiro[24].hipoteca = 120;
	tabuleiro[24].posicao = 24;
	tabuleiro[24].hipotecada = 0;

	strcpy(tabuleiro[25].nome, "Estação de São Bento");
	strcpy(tabuleiro[25].cor, "");
	tabuleiro[25].preço = 200;
	tabuleiro[25].estado = 0;
	tabuleiro[25].dono = 0;
	tabuleiro[25].hipoteca = 100;
	tabuleiro[25].codigoCor = 0;
	tabuleiro[25].hipotecada = 0;


	strcpy(tabuleiro[26].nome, "Rua de Santo António");
	strcpy(tabuleiro[26].cor, "Amarelo");
	tabuleiro[26].preço = 260;
	tabuleiro[26].estado = 0;
	tabuleiro[26].dono = 0;
	tabuleiro[26].renda = 22;
	tabuleiro[26].numeroCasas = 0;
	tabuleiro[26].hotel = 0;
	tabuleiro[26].precoCasa = 150;
	tabuleiro[26].precoHotel = 150;
	tabuleiro[26].renda_1_casa = 110;
	tabuleiro[26].renda_2_casas = 330;
	tabuleiro[26].renda_3_casas = 800;
	tabuleiro[26].renda_4_casas = 975;
	tabuleiro[26].renda_hotel = 1150;
	tabuleiro[26].codigoCor = 6;
	tabuleiro[26].hipoteca = 130;
	tabuleiro[26].posicao = 26;
	tabuleiro[26].hipotecada = 0;

	strcpy(tabuleiro[27].nome, "Rua Garret");
	strcpy(tabuleiro[27].cor, "Amarelo");
	tabuleiro[27].preço = 260;
	tabuleiro[27].estado = 0;
	tabuleiro[27].dono = 0;
	tabuleiro[27].renda = 22;
	tabuleiro[27].numeroCasas = 0;
	tabuleiro[27].hotel = 0;
	tabuleiro[27].precoCasa = 150;
	tabuleiro[27].precoHotel = 150;
	tabuleiro[27].renda_1_casa = 110;
	tabuleiro[27].renda_2_casas = 330;
	tabuleiro[27].renda_3_casas = 800;
	tabuleiro[27].renda_4_casas = 975;
	tabuleiro[27].renda_hotel = 1150;
	tabuleiro[27].codigoCor = 6;
	tabuleiro[27].hipoteca = 130;
	tabuleiro[27].posicao = 27;
	tabuleiro[27].hipotecada = 0;

	strcpy(tabuleiro[28].nome, "Companhia das Àguas");
	strcpy(tabuleiro[28].cor, "");
	tabuleiro[28].preço = 150;
	tabuleiro[28].estado = 0;
	tabuleiro[28].dono = 0;
	tabuleiro[28].hipoteca = 75;
	tabuleiro[28].posicao = 28;
	tabuleiro[28].hipotecada = 0;

	strcpy(tabuleiro[29].nome, "Avenida dos Aliados");
	strcpy(tabuleiro[29].cor, "Amarelo");
	tabuleiro[29].preço = 280;
	tabuleiro[29].estado = 0;
	tabuleiro[29].dono = 0;
	tabuleiro[29].renda = 24;
	tabuleiro[29].numeroCasas = 0;
	tabuleiro[29].hotel = 0;
	tabuleiro[29].precoCasa = 150;
	tabuleiro[29].precoHotel = 150;
	tabuleiro[29].renda_1_casa = 120;
	tabuleiro[29].renda_2_casas = 360;
	tabuleiro[29].renda_3_casas = 850;
	tabuleiro[29].renda_4_casas = 1025;
	tabuleiro[29].renda_hotel = 1200;
	tabuleiro[29].codigoCor = 6;
	tabuleiro[29].hipoteca = 140;
	tabuleiro[29].posicao = 29;
	tabuleiro[29].hipotecada = 0;

	strcpy(tabuleiro[30].nome, "Vá para a Prisão");
	strcpy(tabuleiro[30].cor, "");

	strcpy(tabuleiro[31].nome, "Avenida da Liberdade");
	strcpy(tabuleiro[31].cor, "Verde");
	tabuleiro[31].preço = 300;
	tabuleiro[31].estado = 0;
	tabuleiro[31].dono = 0;
	tabuleiro[31].renda = 26;
	tabuleiro[31].numeroCasas = 0;
	tabuleiro[31].hotel = 0;
	tabuleiro[31].precoCasa = 200;
	tabuleiro[31].precoHotel = 200;
	tabuleiro[31].renda_1_casa = 130;
	tabuleiro[31].renda_2_casas = 390;
	tabuleiro[31].renda_3_casas = 900;
	tabuleiro[31].renda_4_casas = 1100;
	tabuleiro[31].renda_hotel = 1275;
	tabuleiro[31].codigoCor = 7;
	tabuleiro[31].hipoteca = 150;
	tabuleiro[31].posicao = 31;
	tabuleiro[31].hipotecada = 0;

	strcpy(tabuleiro[32].nome, "Praça da Liberdade");
	strcpy(tabuleiro[32].cor, "Verde");
	tabuleiro[32].preço = 300;
	tabuleiro[32].estado = 0;
	tabuleiro[32].dono = 0;
	tabuleiro[32].renda = 26;
	tabuleiro[32].numeroCasas = 0;
	tabuleiro[32].hotel = 0;
	tabuleiro[32].precoCasa = 200;
	tabuleiro[32].precoHotel = 200;
	tabuleiro[32].renda_1_casa = 130;
	tabuleiro[32].renda_2_casas = 390;
	tabuleiro[32].renda_3_casas = 900;
	tabuleiro[32].renda_4_casas = 1100;
	tabuleiro[32].renda_hotel = 1275;
	tabuleiro[32].codigoCor = 7;
	tabuleiro[32].hipoteca = 150;
	tabuleiro[32].posicao = 32;
	tabuleiro[32].hipotecada = 0;

	strcpy(tabuleiro[33].nome, "Caixa Comunidade");
	strcpy(tabuleiro[33].cor, "");

	strcpy(tabuleiro[34].nome, "Rua do Ouro");
	strcpy(tabuleiro[34].cor, "Verde");
	tabuleiro[34].preço = 320;
	tabuleiro[34].estado = 0;
	tabuleiro[34].dono = 0;
	tabuleiro[34].renda = 28;
	tabuleiro[34].numeroCasas = 0;
	tabuleiro[34].hotel = 0;
	tabuleiro[34].precoCasa = 200;
	tabuleiro[34].precoHotel = 200;
	tabuleiro[34].renda_1_casa = 150;
	tabuleiro[34].renda_2_casas = 450;
	tabuleiro[34].renda_3_casas = 1000;
	tabuleiro[34].renda_4_casas = 1200;
	tabuleiro[34].renda_hotel = 1400;
	tabuleiro[34].codigoCor = 7;
	tabuleiro[34].hipoteca = 160;
	tabuleiro[34].posicao = 34;
	tabuleiro[34].hipotecada = 0;

	strcpy(tabuleiro[35].nome, "Estação de Sta. Apolónia");
	strcpy(tabuleiro[35].cor, "");
	tabuleiro[35].preço = 200;
	tabuleiro[35].estado = 0;
	tabuleiro[35].dono = 0;
	tabuleiro[35].hipoteca = 100;
	tabuleiro[35].posicao = 35;
	tabuleiro[35].codigoCor = 0;
	tabuleiro[35].hipotecada = 0;

	strcpy(tabuleiro[36].nome, "Sorte");
	strcpy(tabuleiro[36].cor, "");

	strcpy(tabuleiro[37].nome, "Rua Augusta");
	strcpy(tabuleiro[37].cor, "Azul");
	tabuleiro[37].preço = 350;
	tabuleiro[37].estado = 0;
	tabuleiro[37].dono = 0;
	tabuleiro[37].renda = 35;
	tabuleiro[37].numeroCasas = 0;
	tabuleiro[37].hotel = 0;
	tabuleiro[37].precoCasa = 200;
	tabuleiro[37].precoHotel = 200;
	tabuleiro[37].renda_1_casa = 175;
	tabuleiro[37].renda_2_casas = 500;
	tabuleiro[37].renda_3_casas = 1100;
	tabuleiro[37].renda_4_casas = 1300;
	tabuleiro[37].renda_hotel = 1500;
	tabuleiro[37].codigoCor = 8;
	tabuleiro[37].hipoteca = 175;
	tabuleiro[37].posicao = 37;
	tabuleiro[37].hipotecada = 0;

	strcpy(tabuleiro[38].nome, "Taxa de Luxo");
	strcpy(tabuleiro[38].cor, "");

	strcpy(tabuleiro[39].nome, "Rossio");
	strcpy(tabuleiro[39].cor, "Azul");
	tabuleiro[39].preço = 400;
	tabuleiro[39].estado = 0;
	tabuleiro[39].dono = 0;
	tabuleiro[39].renda = 50;
	tabuleiro[39].numeroCasas = 0;
	tabuleiro[39].hotel = 0;
	tabuleiro[39].precoCasa = 200;
	tabuleiro[39].precoHotel = 200;
	tabuleiro[39].renda_1_casa = 200;
	tabuleiro[39].renda_2_casas = 600;
	tabuleiro[39].renda_3_casas = 1400;
	tabuleiro[39].renda_4_casas = 1700;
	tabuleiro[39].renda_hotel = 2000;
	tabuleiro[39].codigoCor = 8;
	tabuleiro[39].hipoteca = 200;
	tabuleiro[39].posicao = 39;
	tabuleiro[39].hipotecada = 0;
}
//---define numero de jogadores-----------------------------------------------------------------------------------------------------------------------------------
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
		jogadores[i].quantidadeCasas = 0;
		jogadores[i].id = i + 1;
		jogadores[i].cartaLivreDaPrisao = 0;
		jogadores[i].estacoes = 0;
		jogadores[i].utilidade = 0;
		jogadores[i].propriedadesJogador[i].codigoCor = 0;
		jogadores[i].NumVezesSemJogar = 0;




	}

}
//hipotecar casa--------------------------------------------------------
void hipotecarCasa(jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40])
{
	int casaHipotecar;
	int c;
	printf("\nSaldo insuficiente para pagar renda. Hipoteque casas para ganhar dinheiro: ");
	for (c = 0; c < jogadores[jogadorActual].quantidadeCasas; c++)
	{
		if (jogadores[jogadorActual].propriedadesJogador[c].hipotecada == 0)
		{
			printf("\n%d , %s , %d", c + 1, jogadores[jogadorActual].propriedadesJogador[c].nome, jogadores[jogadorActual].propriedadesJogador[c].hipoteca);
		}
	}
	printf("\nEscolha casa a hipotecar. ");
	scanf("%d", &casaHipotecar);
	jogadores[jogadorActual].saldo += jogadores[jogadorActual].propriedadesJogador[casaHipotecar - 1].hipoteca;
	jogadores[jogadorActual].propriedadesJogador[casaHipotecar - 1].hipotecada = 1;
	tabuleiro[jogadores[jogadorActual].propriedadesJogador[casaHipotecar - 1].posicao].hipotecada = 1;
	printf("\nNovo saldo: %d", jogadores[jogadorActual].saldo);

	c = 0;
}
//mostrar casa----------------------------------
void mostrarCasa(Casa tabuleiro[40], jogador jogadores[numeroMaximoJogadores], int posicaoActual)
{
	int valorPagar = 0;//variavel que guarda valor a pagar se a casa for uma estacao
	int valorPagarUtilidade;
	int numeroEstacoes;
	int numeroUtilidades;
	int resposta;
	int cor;
	int j, z;
	int contadorCor;//guarda a quantidade de casas da mesma cor para o respetivo dono.usada para calcular o valor que o adversario paga.
	int contadorCorDono = 0;//obtem a quantidade de casas da mesma cor que o jogador tem.usada para verificar se o jogador pode colocar casas.
	int casasPorConstruir;//obtem o numero de casas que ainda pode construir na propriedade
	int numeroCasasAconstruir;
	int construirHotel;
	int querConstruir;
	int casaHipotecar;
	int c;
	//int posicaoActual = jogadores[jogadorActual].posicao;
	printf("\n\n Casa Actual\n");


	printf("---------------------------\n");
	printf("|                         |\n");
	printf("%s                      \n", tabuleiro[jogadores[jogadorActual].posicao].nome);
	printf("%s                      \n", tabuleiro[jogadores[jogadorActual].posicao].cor);
	printf("---------------------------\n");
	printf("\tPreco %d                \n", tabuleiro[jogadores[jogadorActual].posicao].preço);
	printf("casas:%d                        \n", tabuleiro[jogadores[jogadorActual].posicao].numeroCasas);
	printf("Hotel:%d                         \n", tabuleiro[jogadores[jogadorActual].posicao].hotel);
	printf("                         \n");
	printf("                         \n");
	printf("                         \n");
	printf("                         \n");
	printf("                         \n");
	printf("|                         |\n");
	printf("---------------------------\n");

	//confirma se tem dono
	if (tabuleiro[jogadores[jogadorActual].posicao].dono == 0)
	{
		printf("Quem comprar? 1-Sim, 2-Nao");

		scanf("%d", &resposta);

		//se nao tiver dono e quiser comprar, actualiza o dono da casa e insere a casa no registo propriedadesJogador
		if (resposta == 1)
		{
			if (jogadores[jogadorActual].saldo >= tabuleiro[jogadores[jogadorActual].posicao].preço)
			{
				//guarda dados da casa no array de registo das propriedades do jogador
				tabuleiro[jogadores[jogadorActual].posicao].dono = jogadores[jogadorActual].id;
				strcpy(jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].nome, tabuleiro[jogadores[jogadorActual].posicao].nome);
				strcpy(jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].cor, tabuleiro[jogadores[jogadorActual].posicao].cor);
				jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].codigoCor = tabuleiro[jogadores[jogadorActual].posicao].codigoCor;
				jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].hipoteca = tabuleiro[jogadores[jogadorActual].posicao].hipoteca;
				jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].posicao = tabuleiro[jogadores[jogadorActual].posicao].posicao;
				jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].hipotecada = 0;
				//jogadores[jogadorActual].codigosCor[jogadores[jogadorActual].posicaoArray] = tabuleiro[jogadores[jogadorActual].posicao].codigoCor;
				//jogadores[jogadorActual].posicaoArray++;
				jogadores[jogadorActual].quantidadeCasas++;
				//se a casa que comprou for estacao adiciona um valor a variavel estacoes
				if (jogadores[jogadorActual].posicao == 5 || jogadores[jogadorActual].posicao == 15 || jogadores[jogadorActual].posicao == 25 || jogadores[jogadorActual].posicao == 35)
				{
					jogadores[jogadorActual].estacoes++;
				}
				//se a casa for uma utilidade, adiciona um valor a variavel utilidade do jogador

				if (jogadores[jogadorActual].posicao == 12 || jogadores[jogadorActual].posicao == 28)
				{
					jogadores[jogadorActual].utilidade++;
				}
				jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].preço;
				printf("\nParabens %s, comprou a casa\n ", jogadores[jogadorActual].nome);
			}
			else
			{
				printf("\nNao tem dinheiro suficiente para comprar a casa.\n");
			}
		}
	}

	//verifica se o dono é o jogador actual, verifica se ja tem todas as casas dessa cor, se sim da a opcao de colocar casas ou hotel.
	if (tabuleiro[jogadores[jogadorActual].posicao].dono == jogadores[jogadorActual].id)
	{
		for (z = 0; z < jogadores[jogadorActual].quantidadeCasas; z++)
		{
			if (jogadores[jogadorActual].propriedadesJogador[z].codigoCor == tabuleiro[jogadores[jogadorActual].posicao].codigoCor)
			{

				contadorCorDono++;

			}
		}
		//se possuir as 3 casas dessa cor
		if (contadorCorDono == 3)
		{
			//se tiver 4 casas construidas pode construir hotel
			if (tabuleiro[jogadores[jogadorActual].posicao].numeroCasas == 4)
			{
				printf("\nJa tem 4 casas na propriedade. Pretende construir Hotel? 1-sim 2-nao ");
				scanf("%d", &construirHotel);
				if (construirHotel == 1)
				{
					tabuleiro[jogadores[jogadorActual].posicao].numeroCasas = 0;
					tabuleiro[jogadores[jogadorActual].posicao].hotel = 1;
					jogadores[jogadorActual].saldo -= tabuleiro[jogadores[jogadorActual].posicao].precoHotel;
					printf("\nHotel construido");
					printf("\nNovo saldo: %d ", jogadores[jogadorActual].saldo);
				}
			}
			//se a propriedade tiver menos de 4 casas e nao tiver hotel, pode construir mais.
			if (tabuleiro[jogadores[jogadorActual].posicao].numeroCasas < 4 && tabuleiro[jogadores[jogadorActual].posicao].hotel == 0)
			{
				casasPorConstruir = 4 - tabuleiro[jogadores[jogadorActual].posicao].numeroCasas;
				printf("\nPode construir nesta propriedade %d casas.Preco por casa: %d .Pretende construir? 1-sim 2-nao ", casasPorConstruir, tabuleiro[jogadores[jogadorActual].posicao].precoCasa);
				scanf("%d", &querConstruir);
				while (querConstruir == 1)
				{
					printf("\nQuantas casas pretende construir? ");
					scanf("%d", &numeroCasasAconstruir);
					//se ainda tiver espaco para as casas que quer construir, constroi e cobra ao jogador.
					if (numeroCasasAconstruir <= casasPorConstruir)
					{
						tabuleiro[jogadores[jogadorActual].posicao].numeroCasas++;
						jogadores[jogadorActual].saldo -= tabuleiro[jogadores[jogadorActual].posicao].precoCasa * numeroCasasAconstruir;
						querConstruir = 0;
						printf("\nCasas construidas");
						printf("\nNovo saldo: %d", jogadores[jogadorActual].saldo);
					}
					else
					{
						printf("\nSo pode construir 4 casas por propriedade");

					}
				}

			}


		}
	}


	//se ja tiver dono percorre todos os jogadores
	for (int i = 0; i < numeroDeJogadores; i++)
	{

		//verifica quem é o dono da casa---------------------------------------------------------------------------------------
		if (tabuleiro[jogadores[jogadorActual].posicao].dono == jogadores[i].id && tabuleiro[jogadores[jogadorActual].posicao].dono != jogadores[jogadorActual].id)
		{
			//se a casa estiver hipotecada nao paga nada
			if (tabuleiro[jogadores[jogadorActual].posicao].hipotecada == 1)
			{
				printf("\n Casa esta hipotecada. Nao paga renda.\n");
				return;
			}
			//se casa for uma utilidade calcula o valor a pagar ao dono
			if (jogadores[jogadorActual].posicao == 12 || jogadores[jogadorActual].posicao == 28)
			{
				if (jogadores[i].utilidade == 1)
				{
					valorPagarUtilidade = 4 * ultimoLancamento;
					//se nao tiver dinheiro pede ao jogador para hipotecar casas

					while (jogadores[jogadorActual].saldo - valorPagarUtilidade < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);
					}
					jogadores[jogadorActual].saldo -= valorPagarUtilidade;
					printf("\nTem de pagar ao Jogador %s , %d\n", jogadores[i].nome, valorPagarUtilidade);
					printf("\nNovo saldo : %d\n", jogadores[jogadorActual].saldo);
					return;
				}
				if (jogadores[i].utilidade == 2)
				{
					valorPagarUtilidade = 10 * ultimoLancamento;
					jogadores[jogadorActual].saldo -= valorPagarUtilidade;
					printf("\nTem de pagar ao Jogador %s , %d\n", jogadores[i].nome, valorPagarUtilidade);
					printf("\nNovo saldo : %d\n", jogadores[jogadorActual].saldo);
					return;
				}
			}
			//se casa for estacao verifica quantas estacoes o dono tem e calcula valor a pagar
			if (jogadores[jogadorActual].posicao == 5 || jogadores[jogadorActual].posicao == 15 || jogadores[jogadorActual].posicao == 25 || jogadores[jogadorActual].posicao == 35)
			{
				//printf("\n Entrou no IF");
				numeroEstacoes = jogadores[i].estacoes;
				//printf("\nnumero estacoes %d ", jogadores[i].estacoes);
				switch (numeroEstacoes)
				{
				case 1:valorPagar = 25;
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while (jogadores[jogadorActual].saldo - valorPagar < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("\nTem de pagar ao Jogador %s , %d\n", jogadores[i].nome, valorPagar);
					jogadores[jogadorActual].saldo -= valorPagar;
					printf("\nNovo saldo : %d\n", jogadores[jogadorActual].saldo);
					return;
				case 2:valorPagar = 50;
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while (jogadores[jogadorActual].saldo - valorPagar < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("\nTem de pagar ao Jogador %s , %d\n", jogadores[i].nome, valorPagar);
					jogadores[jogadorActual].saldo -= valorPagar;
					printf("\nNovo saldo : %d\n", jogadores[jogadorActual].saldo);
					return;
				case 3:valorPagar = 100;
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while (jogadores[jogadorActual].saldo - valorPagar < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("\nTem de pagar ao Jogador %s , %d\n", jogadores[i].nome, valorPagar);
					jogadores[jogadorActual].saldo -= valorPagar;
					printf("\nNovo saldo : %d\n", jogadores[jogadorActual].saldo);
					return;
				case 4:valorPagar = 200;
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while (jogadores[jogadorActual].saldo - valorPagar < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("\nTem de pagar ao Jogador %s , %d\n", jogadores[i].nome, valorPagar);
					jogadores[jogadorActual].saldo -= valorPagar;
					printf("\nNovo saldo : %d\n", jogadores[jogadorActual].saldo);
					return;
				}

			}


			//se o jogador nao tem casas construidas na propriedade
			if (tabuleiro[jogadores[jogadorActual].posicao].numeroCasas == 0 && tabuleiro[jogadores[jogadorActual].posicao].hotel == 0)
			{
				//verifica se o dono da casa possui as 3 da mesma cor
				contadorCor = 0;
				for (j = 0; j < jogadores[i].quantidadeCasas; j++)
				{
					if (jogadores[i].propriedadesJogador[j].codigoCor == tabuleiro[jogadores[jogadorActual].posicao].codigoCor)
					{
						//printf("\n %d ", jogadores[i].propriedadesJogador[j].codigoCor);
						//printf("\n %d ", tabuleiro[jogadores[jogadorActual].posicao].codigoCor);
						contadorCor++;
						//printf("\ncontou = %d", contadorCor);
					}
				}
				//se o jogador possuir as 3 casas dessa cor, o adversario paga o dobro da renda
				if (contadorCor == 3)
				{
					//printf("\ncontador=3");
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while (jogadores[jogadorActual].saldo - (tabuleiro[jogadores[jogadorActual].posicao].renda * 2) < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda * 2);
					jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda * 2;
					printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
					contadorCor = 0;
					return;
				}
			}


			//se o dono tiver casas constuidas
			if (tabuleiro[jogadores[jogadorActual].posicao].numeroCasas > 0 && tabuleiro[jogadores[jogadorActual].posicao].hotel == 0)
			{
				//paga renda conssoante numero de casas
				switch (tabuleiro[jogadores[jogadorActual].posicao].numeroCasas)
				{
				case 1:
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while ((jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda_1_casa) < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda_1_casa);
					jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda;
					printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
					break;
				case 2:
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while ((jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda_2_casas) < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda_2_casas);
					jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda;
					printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
					break;

				case 3:
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while ((jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda_3_casas) < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda_3_casas);
					jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda;
					printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
					break;
				case 4:
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while ((jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda_4_casas) < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda_4_casas);
					jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda;
					printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
					break;
				}
				//se tiver hotel paga renda com hotel
				if (tabuleiro[jogadores[jogadorActual].posicao].hotel == 1)
				{
					//se nao tiver dinheiro pede ao jogador para hipotecar casas
					while ((jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda_hotel) < 0)
					{
						hipotecarCasa(jogadores, tabuleiro);

					}

					printf("Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda_hotel);
					jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda;
					printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
				}

			}
			//se nao tiver casas constuidas paga apenas a renda
			else
			{
				//jogador actual paga ao dono da casa, caso a casa nao seja estacao nem utilidade.
				//se nao tiver dinheiro pede ao jogador para hipotecar casas
				while ((jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda) < 0)
				{
					hipotecarCasa(jogadores, tabuleiro);

				}

				printf("pagar casa normal->Tem de pagar ao Jogador %s , %d\n", jogadores[i].nome, tabuleiro[jogadores[jogadorActual].posicao].renda);
				jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - tabuleiro[jogadores[jogadorActual].posicao].renda;
				printf("Novo saldo : %d\n", jogadores[jogadorActual].saldo);
			}
		}
	}


}

//Ver que casas possui-----------------------------------------------------------

void verCasasEsaldo(jogador jogadores[numeroMaximoJogadores])
{

	//indica qual o jogador que está activo
	printf("-------------------------------\n");
	printf("Jogador: %s\n", jogadores[jogadorActual].nome);
	printf("-------------------------------");
	//mostra todas as casas que possui
	printf("\nCasas que possui: \n");

	for (int i = 0; i < jogadores[jogadorActual].quantidadeCasas; i++)
	{
		printf("\n%s, %s\n", jogadores[jogadorActual].propriedadesJogador[i].nome, jogadores[jogadorActual].propriedadesJogador[i].cor);
	}
	printf("-------------------------------\n");
	printf("Saldo: %d\n", jogadores[jogadorActual].saldo);
	printf("-------------------------------\n");

}


//apresentar lancamento de dados------------------------------------------------------------------------
int lancamentoDados(Casa tabuleiro[40], jogador jogadores[numeroMaximoJogadores])
{
	/*
	int dado1 = 0;
	int dado2 = 0;
	int resultado = 0;


	srand((unsigned)time(NULL));
	dado1 = (rand() % 6) + 1;
	dado2 = (rand() % 6) + 1;
	resultado = dado1 + dado2;
	printf("\njogador %s %d + %d Total: %d\n", jogadores[jogadorActual].nome, dado1, dado2, resultado);
	jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao + resultado;*/





	//mostrarCasa(tabuleiro, jogadores, jogadores[jogadorActual].posicao);

	/*if (dado1 == dado2)
	{

	dado1 = (rand() % 6) + 1;
	dado2 = (rand() % 6) + 1;
	resultado = dado1 + dado2;
	printf("\njogador %s %d + %d Total: %d\n", jogadores[jogadorActual].nome, dado1, dado2, resultado);
	jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao + resultado;
	mostrarCasa(tabuleiro, jogadores, jogadores[jogadorActual].posicao);
	if (dado1 == dado2)
	{
	mostrarCasa(tabuleiro,jogadores,jogadores[jogadorActual].posicao);
	system("pause");
	dado1 = (rand() % 6) + 1;
	dado2 = (rand() % 6) + 1;
	resultado = dado1 + dado2;
	printf("esta sorte nao e normal!!");
	printf("\njogador %s %d + %d Total: %d\n", jogadores[jogadorActual].nome, dado1, dado2, resultado);
	jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao + resultado;
	if (dado1 == dado2)
	{
	printf("a tua sorte acabou!!! vai para a cadeia!!!\n");
	jogadores[jogadorActual].posicao = 10;
	jogadores[jogadorActual].estado = 1;

	}

	}
	return (resultado);

	}*/
	//return (resultado);
}
//***Funçoes de todas as casas*****************************************************************************************************
void CasaPartida(jogador jogadores[numeroMaximoJogadores])
{
	jogadores[jogadorActual].saldo += 200;
	printf("%d", jogadores[jogadorActual].saldo);
}

//-----CaixaComunidade----------------------------------
void metodoCaixaComunidade(caixaComunidade comunidade[15], jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40])
{
	//mostra no ecra a carta
	numeroCartaComunidade++;
	int auxiliar;
	char auxiliarTexto[100];
	if (numeroCartaComunidade == 15)
	{
		numeroCartaComunidade = 0;
	}

	printf("\n\n      Caixa Comunidade: %s", comunidade[numeroCartaComunidade].texto);

	//executa a funcionalidade da carta
	switch (numeroCartaComunidade)
	{
	case 0:jogadores[jogadorActual].posicao = 0; mostrarCasa(tabuleiro, jogadores, posicaoActual); break;
	case 1:jogadores[jogadorActual].saldo += 75; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 2:jogadores[jogadorActual].saldo -= 50; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 3: jogadores[jogadorActual].cartaLivreDaPrisao++;
		//strcpy(jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].nome,"Carta esta Livre da prisao");
		//jogadores[jogadorActual].quantidadeCasas++;
		break;
	case 4:jogadores[jogadorActual].saldo += 10 * numeroDeJogadores;
		for (int j = 0; j < numeroDeJogadores; j++)
		{
			if (jogadores[j].id != jogadorActual)
			{
				jogadores[j].saldo -= 10;
			}
		}
		printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 5:jogadores[jogadorActual].saldo += 20; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 6:jogadores[jogadorActual].saldo += 100; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 7:jogadores[jogadorActual].saldo -= 100; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 8:jogadores[jogadorActual].saldo -= 50; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 9:jogadores[jogadorActual].saldo += 25; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 10:	break;
	case 11:jogadores[jogadorActual].saldo += 10; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);	break;
	case 12:jogadores[jogadorActual].saldo += 100; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);	break;
	case 13:jogadores[jogadorActual].saldo += 100; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);	break;
	case 14:jogadores[jogadorActual].saldo += 50 * numeroDeJogadores;
		for (int z = 0; z < numeroDeJogadores; z++)
		{
			if (jogadores[z].id != jogadorActual)
			{
				jogadores[z].saldo -= 50;
			}
		}
		printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	}

}

//--metodo Sorte-----------------------------------
void metodoSorte(caixaComunidade sorte[15], jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40])
{
	numeroCartaSorte++;
	int auxiliar;
	char auxiliarTexto[100];
	if (numeroCartaSorte == 15)
	{
		numeroCartaSorte = 0;
	}

	printf("\n\n      Sorte: %s", sorte[numeroCartaSorte].texto);

	//executa a funcionalidade da carta
	switch (numeroCartaSorte)
	{
	case 0:jogadores[jogadorActual].posicao = 0; mostrarCasa(tabuleiro, jogadores, posicaoActual); break;
	case 1:jogadores[jogadorActual].posicao = 21; mostrarCasa(tabuleiro, jogadores, posicaoActual); break;
	case 2:if (jogadores[jogadorActual].posicao == 7 || jogadores[jogadorActual].posicao == 36)
	{
		jogadores[jogadorActual].posicao = 12;
		mostrarCasa(tabuleiro, jogadores, posicaoActual);
	}
		   else
		   {
			   jogadores[jogadorActual].posicao = 28;
			   mostrarCasa(tabuleiro, jogadores, posicaoActual);
		   }
		   break;
	case 3:if (jogadores[jogadorActual].posicao == 7)
	{
		jogadores[jogadorActual].posicao = 15;
		mostrarCasa(tabuleiro, jogadores, posicaoActual);
	}
		   if (jogadores[jogadorActual].posicao == 22)
		   {
			   jogadores[jogadorActual].posicao = 25;
			   mostrarCasa(tabuleiro, jogadores, posicaoActual);
		   }
		   if (jogadores[jogadorActual].posicao == 36)
		   {
			   jogadores[jogadorActual].posicao = 5;
			   mostrarCasa(tabuleiro, jogadores, posicaoActual);
		   }
		   break;
	case 4:jogadores[jogadorActual].saldo += 100; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 5:jogadores[jogadorActual].saldo += 50; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 6:jogadores[jogadorActual].cartaLivreDaPrisao++;

		//strcpy(jogadores[jogadorActual].propriedadesJogador[jogadores[jogadorActual].quantidadeCasas].nome, "Carta esta Livre da prisao");
		//jogadores[jogadorActual].quantidadeCasas++;
		break;
	case 7:jogadores[jogadorActual].posicao -= 3; mostrarCasa(tabuleiro, jogadores, posicaoActual);		break;
	case 8:jogadores[jogadorActual].saldo -= 50; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 9:jogadores[jogadorActual].saldo += 25; printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);		break;
	case 10:printf("%s", sorte[numeroCartaSorte].texto);		break;
	case 11:if (jogadores[jogadorActual].posicao == 7)
	{
		jogadores[jogadorActual].posicao = 15;
		mostrarCasa(tabuleiro, jogadores, posicaoActual);
	}
			else
			{
				jogadores[jogadorActual].saldo += 25;

				jogadores[jogadorActual].posicao = 15;
				mostrarCasa(tabuleiro, jogadores, posicaoActual);
				printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);
			}


			break;
	case 12:jogadores[jogadorActual].posicao = 39; mostrarCasa(tabuleiro, jogadores, posicaoActual);	break;
	case 13:jogadores[jogadorActual].saldo -= 50 * numeroDeJogadores;
		for (int j = 0; j < numeroDeJogadores; j++)
		{
			if (jogadores[j].id != jogadorActual)
			{
				jogadores[j].saldo += 50;
			}
		}
		printf("\n      Novo saldo: %d\n", jogadores[jogadorActual].saldo);	break;
	case 14:jogadores[jogadorActual].saldo += 25; break;
	}
}

void incomeTax(jogador jogadores[numeroMaximoJogadores])
{

	printf("\n Imposto. Paga 200€\n");
	jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - 200;
	printf("\nNovo saldo: %d", jogadores[jogadorActual].saldo);

}

void impostoLuxo(jogador jogadores[numeroMaximoJogadores])
{

	printf("\n Imposto. Paga 100€\n");
	jogadores[jogadorActual].saldo = jogadores[jogadorActual].saldo - 100;
	printf("\nNovo saldo: %d", jogadores[jogadorActual].saldo);

}

void prisao(jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40], int posicaoActual)
{
	jogadores[jogadorActual].posicao = 10;
	printf("\nVoce esta preso!\n");
	//mostrarCasa(tabuleiro, jogadores, posicaoActual);
	jogadores[jogadorActual].estado = 1;
	jogadores[jogadorActual].NumVezesSemJogar = 3;
}

//***Final de funçoes de casas******************************************************************************************************



//calcular em que casa cai o jogador e executa respetivo codigo------------------------------------------------------------------------
void jogar(jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40], caixaComunidade comunidade[15], caixaComunidade sorte[15])
{
	int dado1 = 0, dadoPrisao1;
	int dado2 = 0, dadoPrisao2;
	int resultado = 0;
	int repeteJogada = 0;
	int posicao;
	int resultadoLancamentoDados = 0;
	int utilizarCartaSairDaPrisao;
	//verifica se jogador nao esta preso
	if (jogadores[jogadorActual].estado == 0 || jogadores[jogadorActual].NumVezesSemJogar == 0)
	{

		do
		{
			dado1 = 0;
			dado2 = 0;
			resultado = 0;
			srand((unsigned)time(0));
			dado1 = (rand() % 6) + 1;
			dado2 = (rand() % 6) + 1;
			resultado = dado1 + dado2;
			ultimoLancamento = resultado;

			printf("\n ***Lancamento jogador %s %d + %d Total: %d***\n", jogadores[jogadorActual].nome, dado1, dado2, resultado);
			if (dado1 == dado2)
			{
				printf("\nDouble, jogue novamente.\n");
				//se sair tres doubles consecutivos prende o jogador
				repeteJogada++;
				if (repeteJogada == 3)
				{
					printf("\nSaiu terceiro Double consecutivo. Esta preso!\n");
					//jogadores[jogadorActual].posicao = 10;
					prisao(jogadores, tabuleiro, posicaoActual); break;
				}

			}
			else
			{
				repeteJogada = 0;
			}


			jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao + resultado;

			resultadoLancamentoDados = resultado;//lancamentoDados(tabuleiro,jogadores);

			//quando acaba o tabuleiro faz a conta para continuar
			if (jogadores[jogadorActual].posicao >= 40)
			{
				jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao - 40;
				jogadores[jogadorActual].saldo += 200;

			}
			//return(jogadores[jogadorActual].posicao); teste
			//printf("\n%d",jogadores[jogadorActual].posicao); teste
			posicao = jogadores[jogadorActual].posicao;
			printf("%d", posicao);
			switch (posicao)
			{
			case 0:/*CasaPartida(jogadores);*/printf("%s", tabuleiro[posicao].nome); break;//colocar funcao para cada casa
			case 1:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 2:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 3:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 4:mostrarCasa(tabuleiro, jogadores, posicaoActual); incomeTax(jogadores); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 5:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 6:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 7:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 8:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 9:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 10:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 11:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 12:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 13:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 14:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 15:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 16:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 17:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 18:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 19:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 20:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 21:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 22:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 23:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 24:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 25:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 26:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 27:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 28:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 29:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 30:mostrarCasa(tabuleiro, jogadores, posicaoActual); prisao(jogadores, tabuleiro, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 31:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 32:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 33:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 34:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 35:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 36:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 37:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 38:mostrarCasa(tabuleiro, jogadores, posicaoActual); impostoLuxo(jogadores); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 39:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			}

		} while (dado1 == dado2 && jogadores[jogadorActual].estado == 0);
	}
	//se estiver na prisao
	else
	{
		//verifica se jogador tem free pass da prisao
		if (jogadores[jogadorActual].cartaLivreDaPrisao > 0)
		{
			//se tiver perguntar se quer usa-la
			printf("\nTem na sua posse uma carta para sair da prisao. Deseja utiliza-la? 1-Sim 2-Nao\n");
			scanf("%d", &utilizarCartaSairDaPrisao);
			while (utilizarCartaSairDaPrisao == 1)
			{
				//se nao quiser fica preso
				if (utilizarCartaSairDaPrisao == 2)
				{
					break;
				}
				//se quiser usar fica livre e joga
				jogadores[jogadorActual].estado = 0;
				jogadores[jogadorActual].cartaLivreDaPrisao--;
				//jogar apos ficar livre
				do
				{
					dado1 = 0;
					dado2 = 0;
					resultado = 0;
					srand((unsigned)time(0));
					dado1 = (rand() % 6) + 1;
					dado2 = (rand() % 6) + 1;
					resultado = dado1 + dado2;
					ultimoLancamento = resultado;
					printf("\njogador %s %d + %d Total: %d\n", jogadores[jogadorActual].nome, dado1, dado2, resultado);
					if (dado1 == dado2)
					{
						//se sair tres doubles consecutivos prende o jogador
						repeteJogada++;
						if (repeteJogada == 3)
						{
							printf("\nSaiu terceiro Double consecutivo. Esta preso!\n");
							jogadores[jogadorActual].posicao = 10;
							prisao(jogadores, tabuleiro, posicaoActual); break;
						}

					}
					else
					{
						repeteJogada = 0;
					}


					jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao + resultado;

					resultadoLancamentoDados = resultado;//lancamentoDados(tabuleiro,jogadores);

					//quando acaba o tabuleiro faz a conta para continuar
					if (jogadores[jogadorActual].posicao >= 40)
					{
						jogadores[jogadorActual].posicao = jogadores[jogadorActual].posicao - 40;
						jogadores[jogadorActual].saldo += 200;

					}
					//return(jogadores[jogadorActual].posicao); teste
					//printf("\n%d",jogadores[jogadorActual].posicao); teste
					posicao = jogadores[jogadorActual].posicao;
					printf("%d", posicao);
					switch (posicao)
					{
					case 0:/*CasaPartida(jogadores);*/printf("%s", tabuleiro[posicao].nome); break;//colocar funcao para cada casa
					case 1:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 2:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 3:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 4:mostrarCasa(tabuleiro, jogadores, posicaoActual); incomeTax(jogadores); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 5:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 6:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 7:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 8:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 9:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 10:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 11:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 12:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 13:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 14:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 15:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 16:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 17:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 18:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 19:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 20:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 21:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 22:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 23:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 24:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 25:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 26:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 27:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 28:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 29:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 30:mostrarCasa(tabuleiro, jogadores, posicaoActual); prisao(jogadores, tabuleiro, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 31:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 32:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 33:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 34:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					case 35:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 36:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 37:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 38:mostrarCasa(tabuleiro, jogadores, posicaoActual); impostoLuxo(jogadores); break; //printf("%s", tabuleiro[posicao].nome); break;
					case 39:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
					}

				} while (dado1 == dado2 && jogadores[jogadorActual].estado == 0);

				//break;
				return;
			}

		}
		printf("\nEsta na prisao. Se obter o mesmo valor em ambos os dados fica livre.\n");
		srand((unsigned)time(0));
		dadoPrisao1 = (rand() % 6) + 1;
		dadoPrisao2 = (rand() % 6) + 1;
		ultimoLancamento = dadoPrisao1 + dadoPrisao2;
		printf("\nLancamento de dados: %d + %d = %d\n", dadoPrisao1, dadoPrisao2, dadoPrisao1 + dadoPrisao2);
		//se conseguir um double fica livre da prisao e joga
		if (dadoPrisao1 == dadoPrisao2)
		{
			printf("\nConseguiu um Double, esta livre.\n");
			jogadores[jogadorActual].posicao += dadoPrisao1 + dadoPrisao2;
			jogadores[jogadorActual].estado = 0;
			//jogadores[jogadorActual].NumVezesSemJogar = 0;
			jogadores[jogadorActual].posicao += dadoPrisao1 + dadoPrisao2;
			switch (jogadores[jogadorActual].posicao)
			{
			case 0:/*CasaPartida(jogadores);*/printf("%s", tabuleiro[jogadores[jogadorActual].posicao].nome); break;//colocar funcao para cada casa
			case 1:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 2:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 3:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 4:mostrarCasa(tabuleiro, jogadores, posicaoActual); incomeTax(jogadores); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 5:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 6:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 7:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 8:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 9:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 10:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 11:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 12:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 13:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 14:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 15:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 16:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 17:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 18:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 19:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 20:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 21:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 22:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 23:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 24:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 25:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 26:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 27:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 28:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 29:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 30:mostrarCasa(tabuleiro, jogadores, posicaoActual); prisao(jogadores, tabuleiro, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 31:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 32:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 33:metodoCaixaComunidade(comunidade, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 34:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			case 35:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 36:metodoSorte(sorte, jogadores, tabuleiro); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 37:mostrarCasa(tabuleiro, jogadores, posicaoActual); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 38:mostrarCasa(tabuleiro, jogadores, posicaoActual); impostoLuxo(jogadores); break; //printf("%s", tabuleiro[posicao].nome); break;
			case 39:mostrarCasa(tabuleiro, jogadores, posicaoActual); break;//printf("%s", tabuleiro[posicao].nome); break;
			}
		}
		//se nao conseguiu double continua preso
		else
		{
			printf("\nNao conseguiu Double, continua preso.\n");
			jogadores[jogadorActual].NumVezesSemJogar--;
			//se ja cumpriu 3 jogadas na prisao fica livre
			if (jogadores[jogadorActual].NumVezesSemJogar == 0)
			{
				printf("Cumpriu a pena de prisao de 3 dias, esta livre!");
				jogadores[jogadorActual].estado = 0;
			}
		}
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

//--menu sair-------------------------------------------------------------------------
void menuSair(jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40], FILE* data)
{
	int opcao, i, j;

	printf("\n Para sair e guardar jogo prima 9.\n");
	scanf("%d", &opcao);
	if (opcao == 9)
	{
		data = fopen("data.txt", "w");
		fprintf(data, "%d\n", numeroDeJogadores);
		fprintf(data, "%d\n", jogadorActual);
		for (i = 0; i < numeroDeJogadores; i++)
		{

			fprintf(data, "%s\n", jogadores[i].nome);
			fprintf(data, "%d\n", jogadores[i].saldo);
			fprintf(data, "%d\n", jogadores[i].estado);
			fprintf(data, "%d\n", jogadores[i].posicao);
			fprintf(data, "%d\n", jogadores[i].quantidadeCasas);
			fprintf(data, "%d\n", jogadores[i].id);
			fprintf(data, "%d\n", jogadores[i].NumVezesSemJogar);
			fprintf(data, "%d\n", jogadores[i].cartaLivreDaPrisao);
			fprintf(data, "%d\n", jogadores[i].estacoes);
			fprintf(data, "%d\n", jogadores[i].utilidade);
			for (j = 0; j < jogadores[i].quantidadeCasas; j++)
			{
				fprintf(data, "%s\n", jogadores[i].propriedadesJogador[j].nome);
				fprintf(data, "%s\n", jogadores[i].propriedadesJogador[j].cor);
				fprintf(data, "%d\n", jogadores[i].propriedadesJogador[j].codigoCor);
				fprintf(data, "%d\n", jogadores[i].propriedadesJogador[j].hipoteca);
				fprintf(data, "%d\n", jogadores[i].propriedadesJogador[j].posicao);
				fprintf(data, "%d\n", jogadores[i].propriedadesJogador[j].hipotecada);

			}
		}
		fprintf(data, "%d\n", tabuleiro[1].estado);
		fprintf(data, "%d\n", tabuleiro[1].dono);
		fprintf(data, "%d\n", tabuleiro[1].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[1].hotel);
		fprintf(data, "%d\n", tabuleiro[1].hipotecada);

		fprintf(data, "%d\n", tabuleiro[3].estado);
		fprintf(data, "%d\n", tabuleiro[3].dono);
		fprintf(data, "%d\n", tabuleiro[3].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[3].hotel);
		fprintf(data, "%d\n", tabuleiro[3].hipotecada);

		fprintf(data, "%d\n", tabuleiro[5].estado);
		fprintf(data, "%d\n", tabuleiro[5].dono);
		fprintf(data, "%d\n", tabuleiro[5].hipotecada);

		fprintf(data, "%d\n", tabuleiro[6].estado);
		fprintf(data, "%d\n", tabuleiro[6].dono);
		fprintf(data, "%d\n", tabuleiro[6].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[6].hotel);
		fprintf(data, "%d\n", tabuleiro[6].hipotecada);

		fprintf(data, "%d\n", tabuleiro[8].estado);
		fprintf(data, "%d\n", tabuleiro[8].dono);
		fprintf(data, "%d\n", tabuleiro[8].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[8].hotel);
		fprintf(data, "%d\n", tabuleiro[8].hipotecada);

		fprintf(data, "%d\n", tabuleiro[9].estado);
		fprintf(data, "%d\n", tabuleiro[9].dono);
		fprintf(data, "%d\n", tabuleiro[9].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[9].hotel);
		fprintf(data, "%d\n", tabuleiro[9].hipotecada);

		fprintf(data, "%d\n", tabuleiro[11].estado);
		fprintf(data, "%d\n", tabuleiro[11].dono);
		fprintf(data, "%d\n", tabuleiro[11].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[11].hotel);
		fprintf(data, "%d\n", tabuleiro[11].hipotecada);

		fprintf(data, "%d\n", tabuleiro[12].estado);
		fprintf(data, "%d\n", tabuleiro[12].dono);
		fprintf(data, "%d\n", tabuleiro[12].hipotecada);

		fprintf(data, "%d\n", tabuleiro[13].estado);
		fprintf(data, "%d\n", tabuleiro[13].dono);
		fprintf(data, "%d\n", tabuleiro[13].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[13].hotel);
		fprintf(data, "%d\n", tabuleiro[13].hipotecada);

		fprintf(data, "%d\n", tabuleiro[14].estado);
		fprintf(data, "%d\n", tabuleiro[14].dono);
		fprintf(data, "%d\n", tabuleiro[14].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[14].hotel);
		fprintf(data, "%d\n", tabuleiro[14].hipotecada);

		fprintf(data, "%d\n", tabuleiro[15].estado);
		fprintf(data, "%d\n", tabuleiro[15].dono);
		fprintf(data, "%d\n", tabuleiro[15].hipotecada);

		fprintf(data, "%d\n", tabuleiro[16].estado);
		fprintf(data, "%d\n", tabuleiro[16].dono);
		fprintf(data, "%d\n", tabuleiro[16].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[16].hotel);
		fprintf(data, "%d\n", tabuleiro[16].hipotecada);

		fprintf(data, "%d\n", tabuleiro[18].estado);
		fprintf(data, "%d\n", tabuleiro[18].dono);
		fprintf(data, "%d\n", tabuleiro[18].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[18].hotel);
		fprintf(data, "%d\n", tabuleiro[18].hipotecada);

		fprintf(data, "%d\n", tabuleiro[19].estado);
		fprintf(data, "%d\n", tabuleiro[19].dono);
		fprintf(data, "%d\n", tabuleiro[19].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[19].hotel);
		fprintf(data, "%d\n", tabuleiro[19].hipotecada);

		fprintf(data, "%d\n", tabuleiro[21].estado);
		fprintf(data, "%d\n", tabuleiro[21].dono);
		fprintf(data, "%d\n", tabuleiro[21].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[21].hotel);
		fprintf(data, "%d\n", tabuleiro[21].hipotecada);

		fprintf(data, "%d\n", tabuleiro[23].estado);
		fprintf(data, "%d\n", tabuleiro[23].dono);
		fprintf(data, "%d\n", tabuleiro[23].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[23].hotel);
		fprintf(data, "%d\n", tabuleiro[23].hipotecada);

		fprintf(data, "%d\n", tabuleiro[24].estado);
		fprintf(data, "%d\n", tabuleiro[24].dono);
		fprintf(data, "%d\n", tabuleiro[24].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[24].hotel);
		fprintf(data, "%d\n", tabuleiro[24].hipotecada);

		fprintf(data, "%d\n", tabuleiro[25].estado);
		fprintf(data, "%d\n", tabuleiro[25].dono);
		fprintf(data, "%d\n", tabuleiro[25].hipotecada);

		fprintf(data, "%d\n", tabuleiro[26].estado);
		fprintf(data, "%d\n", tabuleiro[26].dono);
		fprintf(data, "%d\n", tabuleiro[26].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[26].hotel);
		fprintf(data, "%d\n", tabuleiro[26].hipotecada);

		fprintf(data, "%d\n", tabuleiro[27].estado);
		fprintf(data, "%d\n", tabuleiro[27].dono);
		fprintf(data, "%d\n", tabuleiro[27].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[27].hotel);
		fprintf(data, "%d\n", tabuleiro[27].hipotecada);

		fprintf(data, "%d\n", tabuleiro[28].estado);
		fprintf(data, "%d\n", tabuleiro[28].dono);
		fprintf(data, "%d\n", tabuleiro[28].hipotecada);

		fprintf(data, "%d\n", tabuleiro[29].estado);
		fprintf(data, "%d\n", tabuleiro[29].dono);
		fprintf(data, "%d\n", tabuleiro[29].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[29].hotel);
		fprintf(data, "%d\n", tabuleiro[29].hipotecada);

		fprintf(data, "%d\n", tabuleiro[31].estado);
		fprintf(data, "%d\n", tabuleiro[31].dono);
		fprintf(data, "%d\n", tabuleiro[31].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[31].hotel);
		fprintf(data, "%d\n", tabuleiro[31].hipotecada);

		fprintf(data, "%d\n", tabuleiro[32].estado);
		fprintf(data, "%d\n", tabuleiro[32].dono);
		fprintf(data, "%d\n", tabuleiro[32].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[32].hotel);
		fprintf(data, "%d\n", tabuleiro[32].hipotecada);

		fprintf(data, "%d\n", tabuleiro[34].estado);
		fprintf(data, "%d\n", tabuleiro[34].dono);
		fprintf(data, "%d\n", tabuleiro[34].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[34].hotel);
		fprintf(data, "%d\n", tabuleiro[34].hipotecada);

		fprintf(data, "%d\n", tabuleiro[35].estado);
		fprintf(data, "%d\n", tabuleiro[35].dono);
		fprintf(data, "%d\n", tabuleiro[35].hipotecada);

		fprintf(data, "%d\n", tabuleiro[37].estado);
		fprintf(data, "%d\n", tabuleiro[37].dono);
		fprintf(data, "%d\n", tabuleiro[37].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[37].hotel);
		fprintf(data, "%d\n", tabuleiro[37].hipotecada);

		fprintf(data, "%d\n", tabuleiro[39].estado);
		fprintf(data, "%d\n", tabuleiro[39].dono);
		fprintf(data, "%d\n", tabuleiro[39].numeroCasas);
		fprintf(data, "%d\n", tabuleiro[39].hotel);
		fprintf(data, "%d\n", tabuleiro[39].hipotecada);

		fclose(data);
		exit(0);
	}

}
//actualizar dados de jogo anterior-------------------
void actualizar(jogador jogadores[numeroMaximoJogadores], Casa tabuleiro[40], FILE* data)
{
	int i, j;
	char nome[50], cor[50];

	data = fopen("data.txt", "r");
	fscanf(data, "%d\n", &numeroDeJogadores);
	fscanf(data, "%d\n", &jogadorActual);
	for (i = 0; i < numeroDeJogadores; i++)
	{

		fscanf(data, "%s\n", &jogadores[i].nome);
		fscanf(data, "%d\n", &jogadores[i].saldo);
		fscanf(data, "%d\n", &jogadores[i].estado);
		fscanf(data, "%d\n", &jogadores[i].posicao);
		fscanf(data, "%d\n", &jogadores[i].quantidadeCasas);
		fscanf(data, "%d\n", &jogadores[i].id);
		fscanf(data, "%d\n", &jogadores[i].NumVezesSemJogar);
		fscanf(data, "%d\n", &jogadores[i].cartaLivreDaPrisao);
		fscanf(data, "%d\n", &jogadores[i].estacoes);
		fscanf(data, "%d\n", &jogadores[i].utilidade);
		for (j = 0; j < jogadores[i].quantidadeCasas; j++)
		{

			fscanf(data, "%[^\n] \n", &jogadores[i].propriedadesJogador[j].nome);
			fscanf(data, "%[^\n] \n", &jogadores[i].propriedadesJogador[j].cor);
			fscanf(data, "%d\n", &jogadores[i].propriedadesJogador[j].codigoCor);
			fscanf(data, "%d\n", &jogadores[i].propriedadesJogador[j].hipoteca);
			fscanf(data, "%d\n", &jogadores[i].propriedadesJogador[j].posicao);
			fscanf(data, "%d\n", &jogadores[i].propriedadesJogador[j].hipotecada);
		}

	}
	fscanf(data, "%d\n", &tabuleiro[1].estado);
	fscanf(data, "%d\n", &tabuleiro[1].dono);
	fscanf(data, "%d\n", &tabuleiro[1].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[1].hotel);
	fscanf(data, "%d\n", &tabuleiro[1].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[3].estado);
	fscanf(data, "%d\n", &tabuleiro[3].dono);
	fscanf(data, "%d\n", &tabuleiro[3].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[3].hotel);
	fscanf(data, "%d\n", &tabuleiro[3].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[5].estado);
	fscanf(data, "%d\n", &tabuleiro[5].dono);
	fscanf(data, "%d\n", &tabuleiro[5].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[6].estado);
	fscanf(data, "%d\n", &tabuleiro[6].dono);
	fscanf(data, "%d\n", &tabuleiro[6].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[6].hotel);
	fscanf(data, "%d\n", &tabuleiro[6].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[8].estado);
	fscanf(data, "%d\n", &tabuleiro[8].dono);
	fscanf(data, "%d\n", &tabuleiro[8].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[8].hotel);
	fscanf(data, "%d\n", &tabuleiro[8].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[9].estado);
	fscanf(data, "%d\n", &tabuleiro[9].dono);
	fscanf(data, "%d\n", &tabuleiro[9].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[9].hotel);
	fscanf(data, "%d\n", &tabuleiro[9].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[11].estado);
	fscanf(data, "%d\n", &tabuleiro[11].dono);
	fscanf(data, "%d\n", &tabuleiro[11].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[11].hotel);
	fscanf(data, "%d\n", &tabuleiro[11].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[12].estado);
	fscanf(data, "%d\n", &tabuleiro[12].dono);
	fscanf(data, "%d\n", &tabuleiro[12].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[13].estado);
	fscanf(data, "%d\n", &tabuleiro[13].dono);
	fscanf(data, "%d\n", &tabuleiro[13].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[13].hotel);
	fscanf(data, "%d\n", &tabuleiro[13].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[14].estado);
	fscanf(data, "%d\n", &tabuleiro[14].dono);
	fscanf(data, "%d\n", &tabuleiro[14].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[14].hotel);
	fscanf(data, "%d\n", &tabuleiro[14].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[15].estado);
	fscanf(data, "%d\n", &tabuleiro[15].dono);
	fscanf(data, "%d\n", &tabuleiro[15].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[16].estado);
	fscanf(data, "%d\n", &tabuleiro[16].dono);
	fscanf(data, "%d\n", &tabuleiro[16].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[16].hotel);
	fscanf(data, "%d\n", &tabuleiro[16].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[18].estado);
	fscanf(data, "%d\n", &tabuleiro[18].dono);
	fscanf(data, "%d\n", &tabuleiro[18].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[18].hotel);
	fscanf(data, "%d\n", &tabuleiro[18].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[19].estado);
	fscanf(data, "%d\n", &tabuleiro[19].dono);
	fscanf(data, "%d\n", &tabuleiro[19].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[19].hotel);
	fscanf(data, "%d\n", &tabuleiro[19].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[21].estado);
	fscanf(data, "%d\n", &tabuleiro[21].dono);
	fscanf(data, "%d\n", &tabuleiro[21].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[21].hotel);
	fscanf(data, "%d\n", &tabuleiro[21].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[23].estado);
	fscanf(data, "%d\n", &tabuleiro[23].dono);
	fscanf(data, "%d\n", &tabuleiro[23].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[23].hotel);
	fscanf(data, "%d\n", &tabuleiro[23].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[24].estado);
	fscanf(data, "%d\n", &tabuleiro[24].dono);
	fscanf(data, "%d\n", &tabuleiro[24].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[24].hotel);
	fscanf(data, "%d\n", &tabuleiro[24].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[25].estado);
	fscanf(data, "%d\n", &tabuleiro[25].dono);
	fscanf(data, "%d\n", &tabuleiro[25].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[26].estado);
	fscanf(data, "%d\n", &tabuleiro[26].dono);
	fscanf(data, "%d\n", &tabuleiro[26].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[26].hotel);
	fscanf(data, "%d\n", &tabuleiro[26].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[27].estado);
	fscanf(data, "%d\n", &tabuleiro[27].dono);
	fscanf(data, "%d\n", &tabuleiro[27].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[27].hotel);
	fscanf(data, "%d\n", &tabuleiro[27].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[28].estado);
	fscanf(data, "%d\n", &tabuleiro[28].dono);
	fscanf(data, "%d\n", &tabuleiro[28].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[29].estado);
	fscanf(data, "%d\n", &tabuleiro[29].dono);
	fscanf(data, "%d\n", &tabuleiro[29].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[29].hotel);
	fscanf(data, "%d\n", &tabuleiro[29].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[31].estado);
	fscanf(data, "%d\n", &tabuleiro[31].dono);
	fscanf(data, "%d\n", &tabuleiro[31].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[31].hotel);
	fscanf(data, "%d\n", &tabuleiro[31].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[32].estado);
	fscanf(data, "%d\n", &tabuleiro[32].dono);
	fscanf(data, "%d\n", &tabuleiro[32].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[32].hotel);
	fscanf(data, "%d\n", &tabuleiro[32].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[34].estado);
	fscanf(data, "%d\n", &tabuleiro[34].dono);
	fscanf(data, "%d\n", &tabuleiro[34].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[34].hotel);
	fscanf(data, "%d\n", &tabuleiro[34].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[35].estado);
	fscanf(data, "%d\n", &tabuleiro[35].dono);
	fscanf(data, "%d\n", &tabuleiro[35].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[37].estado);
	fscanf(data, "%d\n", &tabuleiro[37].dono);
	fscanf(data, "%d\n", &tabuleiro[37].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[37].hotel);
	fscanf(data, "%d\n", &tabuleiro[37].hipotecada);

	fscanf(data, "%d\n", &tabuleiro[39].estado);
	fscanf(data, "%d\n", &tabuleiro[39].dono);
	fscanf(data, "%d\n", &tabuleiro[39].numeroCasas);
	fscanf(data, "%d\n", &tabuleiro[39].hotel);
	fscanf(data, "%d\n", &tabuleiro[39].hipotecada);


	fclose(data);
}
//Main------------------------------------------------------------------------------------------------------------------------------
int main()
{
	caixaComunidade comunidade[15];
	caixaComunidade sorte[15];
	Casa tabuleiro[40];
	jogador jogadores[numeroMaximoJogadores];
	criarTabuleiro(tabuleiro);
	criarComunidade(comunidade);
	criarSorte(sorte);
	data = fopen("data.txt", "r");
	//se ficheiro estiver preenchido pergunta ao jogador se deseja continuar jogo anterior ou se quer começar um novo jogo
	//se ficheiro nao está preenchido com dados cria automaticamente um novo jogo
	int opcao;
	if (data != NULL)
	{
		printf("Deseja continuar o jogo anterior ou criar um novo? 1-Continuar 2-Novo jogo");
		scanf("%d", &opcao);
		if (opcao == 1)
		{
			actualizar(jogadores, tabuleiro, data);
		}
		else
		{
			definirNumeroDeJogadores();
			criarJogadores(jogadores);
		}
		//fclose(data);
	}
	else
	{
		definirNumeroDeJogadores();
		criarJogadores(jogadores);
	}


	while (gameOver == 0)
	{
		verCasasEsaldo(jogadores);
		jogar(jogadores, tabuleiro, comunidade, sorte);
		menuSair(jogadores, tabuleiro, data);
		trocarJogador();

		system("pause");
		system("cls");
	}


	system("pause");
}

