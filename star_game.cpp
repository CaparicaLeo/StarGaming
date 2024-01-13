//para as ferramentas cin e cout...
#include <iostream>
//para a ferramenta getch...
#include <conio.h>
//para gerar numeros aleatorios com rand e para função de ambiente system("cls") e exit(0)...
#include <cstdlib>
//para uso da ferramenta usleep...
#include <unistd.h>
// para uso da ferramente sleep...
#include <windows.h>
#include <ctime>

using namespace std;
//variaveis universais
bool gameOver; //condição de existencia da partida
const int largura = 11;
const int altura = 14;
char tela[altura][largura];
int x, y; // posição da nave
int starX, starY; // posição da estrela
int meteorX, meteorY; //posição meteoro
int pontuacao;
int perdidas;
int vidas=3;
int posicoes[500]={0},contador=0;

//valores bases dos jogos
void base_look() {
    gameOver = false;
    x = largura / 2; //inicialização da nave no mapa
    y = altura - 1;
    meteorX = rand() % largura; //posição aleatoria inicial do meteoro no eixo x;
    meteorY = 0;
    pontuacao = 0;
}
void base_catch() {
    srand(time(NULL));
    gameOver = false;
    x = largura / 2;
    y = altura - 1;
    starX = rand() % largura; // posicao aleatoria inicial da estrela no eixo x;
    starY = 0;
    pontuacao = 0;
    perdidas = 0;
}

//geração do cenario dos jogos
void espaco_catch() {
    system("cls");
    for (int i = 0; i < largura + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "U"; // Nave
            else if (i == starY && j == starX)
                cout << "*"; // Estrela
            else
                cout << " ";
            if (j == largura - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < largura + 2; i++)
        cout << "_";
    cout << endl;

    cout << "Pontuacao: " << pontuacao << endl;
    cout << "Estrelas perdidas: " << perdidas << endl;
}
void espaco_look() {
    system("cls");
    for (int i = 0; i < largura + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "A"; // Nave
            else if (i == meteorY && j == meteorX)
                cout << "*"; // Meteoro
            else
                cout << " ";
            if (j == largura - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < largura + 2; i++)
        cout << "_";
    cout << endl;

    cout << "Pontuacao: " << pontuacao << endl;
    cout << "Vidas: " << vidas << endl;

}
//controles basicos
void controles() {
    if (kbhit()) {
        switch (getch()) {
            case 'a':
                x--;
                break;
            case 'A':
                x--;
                break;
            case 'd':
                x++;
                break;
            case 'D':
                x++;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

//logica de pontuação dos jogos
void logica_catch() {
    starY++;
    if (starY == altura - 1 && starX == x) {
        pontuacao++;
        starX = rand() % largura;
        starY = 0;
        perdidas = 0;
    }

    if (starY == altura - 1) {
        perdidas++;
        starX = rand() % largura;
        starY = 0;
    }

    if (perdidas == 3)
        gameOver = true;
}
void logica_look() {
    meteorY++;
    if (meteorY == altura ) {
        meteorX = rand() % largura;
        meteorY = 0;
        pontuacao++;
    }
    // Verifica a colisão entre a nave e o meteoro
    if (meteorY == y && meteorX == x) {
        vidas--;
    }
    if(vidas == 0){
        gameOver = true;}   
}
void menu(){
    cout<< "Bem vindo ao Star Game!!" << endl
        << endl
        << "Selecione seu modo de jogo..." << endl
        << endl;
    cout<< "Para jogar 'Catch the star', pressione 0." << endl
        << "Para jogar 'Look the meteor!', pressione 1." << endl
        << "Para sair do jogo, pressione 9."<<endl
        << "Insira aqui seu modo de jogo: ";
}

int main() {
    int escolha;
    do{
        menu();
        cin >> escolha;
        cout << endl;
        switch(escolha){
            case 0:
                base_catch();
                cout << "No jogo 'Catch the star', voce deve coletar o maximo de estrelas(*) possiveis!"<< endl
                     << "Caso voce perca 3 estrelas seguidas, O jogo acaba." << endl
                     << "Para controlar sua nave, use o botao 'A' para ir a esquerda ou o botao 'D' para ir a direita."<< endl
                     << "Para encerrar o jogo, aperte 'x'." << endl
                     << endl;
                sleep(10);
                cout << "Iniciando em 3...";
                sleep(1);
                cout << "2...";
                sleep(1);
                cout << "1..." << endl;
                while(!gameOver){
                    espaco_catch();
                    controles();
                    logica_catch();
                    posicoes[contador]=starX;
                    contador++;
                    usleep(30000);
                }
                for(int i=0;i<contador;i++){
                    cout << posicoes[i] << " ";
                }
                cout << endl;
                cout << "GAME OVER" << endl;
                break;
            case 1: 
                base_look();
                cout << "No jogo 'Look the Meteor!', voce deve desviar de todos os meteoros(*) em seu caminho." << endl
                     << "Caso um meteoro te atinja, voce perde uma vida. Se voce perder todas as vidas, GAME OVER." << endl
                     << "Quanto mais meteoros voce desviar, maior sua pontuacao!" << endl
                     << "Para controlar sua nave, use o botao 'A' para ir a esquerda e o botao 'D' para ir a direita." << endl
                     << "Para sair do jogo, aperte 'x'." << endl
                     << endl;
                sleep(10);
                cout << "Iniciando em 3...";
                sleep(1);
                cout << "2...";
                sleep(1);
                cout << "1..." << endl;
                while(!gameOver){
                    espaco_look();
                    controles();
                    logica_look();
                    usleep(100);
                }
                cout << "GAME OVER" << endl;
                break;
            case 9:
                cout << "Obrigado por jogar!!" << endl;
                exit(0);
                break;
            default:
                cout << "ESCOLHA INVALIDA" << endl;
                cout << endl;
        }
    }while(escolha!=9);
}