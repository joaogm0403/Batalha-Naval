#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale.h>
#include <time.h>

using namespace std;

void menu_inicial();

void LimpaTela(){
    system("CLS");
}

void inicia_tabuleiro( char tabuleiro[10][10], char mascara[10][10]){

int linha, coluna;

 //Preenche o tabuleiro com "água"
    for(linha = 0; linha < 10; linha ++){

        for(coluna = 0; coluna < 10; coluna++){

            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

void exibe_mapa(){

    //Mapa indicador de colunas
    int cont;

    for(cont = 0; cont < 10; cont++){

        if(cont == 0){
             cout << "     ";
        }

        cout << cont << " ";
    }

    cout << "\n";

    for(cont = 0; cont < 10; cont++){

       if(cont == 0){
            cout << "     ";
        }

        cout << "| ";
    }
    cout << "\n";
}

void exibe_tabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostra_gabarito){

//Definindo as cores de cada item do tabuleiro
char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm', 0 }; // água
char green[] = {0x1b, '[', '1', ';', '3', '2', 'm', 0 }; //barco pequeno
char red[] = {0x1b, '[', '1', ';', '3', '1', 'm', 0 }; //barco grande
char normal[] = {0x1b, '[', '1', ';', '3', '9', 'm', 0 }; // cor do tabuleiro

int linha, coluna;

    //Exibe o tabuleiro
    for(linha = 0; linha < 10; linha++){
         cout << linha << " - ";

         for(coluna = 0; coluna < 10; coluna++){

            switch(mascara[linha][coluna]){

                case 'A':
                    cout << blue << " " <<mascara[linha][coluna] << normal;
                    break;

                case 'P':
                    cout << green << " " <<mascara[linha][coluna] << normal;
                    break;

                case 'G':
                    cout << red << " " << mascara[linha][coluna] << normal;
                    break;

                default:
                    cout << " " <<mascara[linha][coluna];
                    break;
            }

         }

         cout << "\n";
    }

    if(mostra_gabarito == true){

     for(linha = 0; linha < 10; linha ++){

        for(coluna = 0; coluna < 10; coluna++){

           cout << " " << tabuleiro[linha][coluna];
            }

        cout << "\n";
        }
    }
}

void posiciona_barcos(char tabuleiro[10][10]){

    //adiciona 15 barcos, 10 "pequenos" e  5 "grandes"
    int quantidade = 10;
    int cont;
    int quantidade_posicionada = 0;
    int quantidadeG = 5;
    int quantidade_posicionadaG = 0;

     //Verifica se já foram posicionados todos os barcos
    while(quantidade_posicionada < quantidade){

       int Linha_aleatoria = rand() % 10;
       int Coluna_aleatoria = rand() % 10;

       if(tabuleiro[Linha_aleatoria][Coluna_aleatoria] = 'A') {

            //Posiciona os 10 primeiros barcos aleatoriamente
            tabuleiro[Linha_aleatoria][Coluna_aleatoria] = 'P';

            quantidade_posicionada++;
       }
    }

    while(quantidade_posicionadaG < quantidadeG){

       int Linha_aleatoria = rand() % 5;
       int Coluna_aleatoria = rand() % 5;

        if(tabuleiro[Linha_aleatoria][Coluna_aleatoria] = 'A') {

        //Posiciona os 5  barcos restantes aleatoriamente
        tabuleiro[Linha_aleatoria][Coluna_aleatoria] = 'G';

        quantidade_posicionadaG++;
        }
    }
}

//função que verifica o que o tiro acertou
void verifica_tiro(char tabuleiro[10][10], int linha_jogada, int coluna_jogada, int *pontos, string *mensagem){

    switch (tabuleiro[linha_jogada][coluna_jogada]){

            //adiciona a quantidade de pontos correspondente ao tiro
            case 'G':
                *pontos = *pontos + 20;
                *mensagem = "BOA! Você acertou um barco grande! (20 pontos)\n\n";
                break;

            case 'P':
                *pontos = *pontos + 10;
                *mensagem = "BOA! Você acertou um barco pequeno!(10 pontos)\n\n";
                break;

            case 'A':
                *mensagem = "Tiro na água!\n";
                break;
    }
}

void jogo(string nome_do_jogador){

    ///Variáveis Gerais
    char tabuleiro [10][10], mascara[10][10];
    int linha, coluna;
    int linha_jogada, coluna_jogada;
    int estado_de_jogo = 1;
    int pontos = 0;
    int tentativas = 0;
    int maximo_de_tentativas = 20;
    int opcao;

    string mensagem;

    //inicia o tabuleiro com água
    inicia_tabuleiro(tabuleiro, mascara);

    //Gera os barcos aleatoriamente
    posiciona_barcos(tabuleiro);

    while(tentativas < maximo_de_tentativas){

    LimpaTela();

    exibe_mapa();

    exibe_tabuleiro(tabuleiro, mascara, false);

    cout << "\n" << mensagem;
    cout << "\nPontos: " << pontos;
    cout << "\nTentativas restantes : " << maximo_de_tentativas - tentativas;

    linha_jogada = -1;
    coluna_jogada = -1;

    while( (linha_jogada < 0  || coluna_jogada < 0) || (linha_jogada > 9  || coluna_jogada > 9)){

        cout << "\n" << nome_do_jogador << ", digite uma linha: ";
        cin >> linha_jogada;

        cout << "\n" << nome_do_jogador << ", digite uma coluna: ";
        cin >> coluna_jogada;
    }


    verifica_tiro(tabuleiro, linha_jogada, coluna_jogada, &pontos, &mensagem);

    //revela o que está embaixo da mascara
    mascara[linha_jogada][coluna_jogada] = tabuleiro[linha_jogada][coluna_jogada];

    tentativas++;
    }

    LimpaTela();

    cout << "Fim de jogo, o que deseja fazer ?";
    cout << "\n1 - Jogar novamente";
    cout << "\n2 - Voltar para o menu";
    cout << "\n3 - Sair";
    cin >> opcao;

    switch(opcao){

        case 1:
            jogo(nome_do_jogador);
            break;

        case 2:
            menu_inicial();
            break;
    }
}

void menu_inicial(){

 int opcao = 0;
 int opcao2 = 0;
 int opcao3 = 0;

 string nome_do_jogador;

    while(opcao < 1 || opcao > 3){

    LimpaTela();

    //Enquanto o jogador não digita, o menu continua sendo mostrado

    cout << "Bem-Vindo ao Jogo de Batalha Naval!\n";
    cout << "\n1 - Jogar";
    cout << "\n2 - Sobre";
    cout << "\n3 - Regras\n";
    cout << "\nEscolha uma opção e tecle ENTER:";
    cin >> opcao;


    switch(opcao){
        case 1:

            LimpaTela();

            cout <<"Nome de usuário:";
            cin >> nome_do_jogador;
            jogo(nome_do_jogador);

            break;

        case 2:
             LimpaTela();

            cout<<"Jogo criado por João Gabriel G. Machado para o componente curricular Programação em linguagem C da 7° Fase do curso técnico em eletrônica\n";

            cout << "\n1 - Voltar para o menu";
            cout << "\n2 - Sair";
            cin >> opcao2;

                switch(opcao2){
                    case 1:
                        menu_inicial();
                    break;

                    case 2:
                        cout << "Até mais";
                    break;
                }

         case 3:

            LimpaTela();

            cout << "Você possui 20 tentativas para acertar 15 barcos e atingir a sua maior pontuação\n\n"
                  "Tiro na água (A) = 0 pontos\n"
                  "Barco pequeno (P) = 10 pontos\n"
                  "Barco grande (G) = 20 pontos\n";

            cout << "\n1 - Voltar para o menu";
            cout << "\n2 - Sair";
            cin >> opcao3;

                switch(opcao3){
                    case 1:
                        menu_inicial();
                    break;

                    case 2:
                        cout << "Até mais";
                    break;
                }

        break;


        }
    }
}


int main(){

//Para utilizar acentos
setlocale(LC_ALL,"");

//Para gerar números aleatórios
    srand((unsigned)time(NULL));

menu_inicial();

return 0;
}
