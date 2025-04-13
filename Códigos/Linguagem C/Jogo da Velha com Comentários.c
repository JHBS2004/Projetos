//-BIBLIOTECAS-//

#include <stdio.h>  
//Essa biblioteca é a mais comum e é a mais necessária, pois ela é responsável por fornecer funções de entradas e saídas 
//de dados. Nesse código, ela possuí os comandos caracteristicos: printf() e scanf(). Stdio significa Standard Input Output.

#include <stdlib.h>  
//Essa biblioteca é responsável por manipular dados e processos para propor funções especificas dentro do código. Nesse
//código, ela possuí os comandos caracteristicos: system(). Stdlib significa Standard Library. 

#include <string.h> 
//Essa biblioteca fornece funções para strings e para a memoria. Nesse código, ela possuí os comandos característicos:
//strcpy().

#include <unistd.h>  
//Essa biblioteca é especifica para sistemas do tipo Unix, mas também fornece funções para interagir com o sistema ope-
//racional. Nesse código, ela possuí os comandos característicos: sleep(). 

#include <stdbool.h>
//Essa biblioteca introduz o suporte para o tipo de dado booleano. Nesse código, ela possuí os comandos característicos: bool_.


char tabuleiro[3][3];
//Essa variável char representa uma matriz de 3x3 caracteres, onde cada elemento pode armazenar um caracteres.

char simb='X', nome1[30], nome2[30], nom[30];
//Essas variáveis de char (nome1, nome2 e nom), representam strings que armazenam os caracteres dos nomes dos Jogadores e o simbolo significa 
//que quando o jogador for selecionar no espaçamento do tabuleiro, o mesmo já ficará marcado.

int op, jogadas=0;
//A variável op seria uma int armazenada que é responsável para representar a opção escolhida pelo usuário e a int jogadas seria responsável
//por contar cada rodada até o jogo terminar.

int vitoriasX = 0, vitoriasO = 0, empates = 0, partidas = 0;
//Essas variáveis são responsáveis por mostrar o placar dos jogadores depois de cada partida acabar.

void lerJogador(){
    printf("Digite o nome do Jogador 1:  ");
    scanf("%s", nome1);
    printf("\nDigite o nome do Jogador 2: ");
    scanf("%s", nome2);
    strcpy(nom, nome1);
}
//Esse void tem como função perguntar os nomes aos jogadores um e dois, possuindo um comando (strcpy) que permite que a string dos nomes seja
//reutilizada em outros pontos da estrutura do código.

void inicializarTabuleiro() {
    char num = '1';
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            tabuleiro[i][j] = num++;
        }
    }
}
//Esse void seria como a tabela seria apresentada de primeira instância sem nenhuma jogada realizada. Ela tem uma contagem de um a nove, sendo
//estabelecida pelo char num = '1', tendo suas linhas sendo estabelecidas pelo int[i] e suas colunas por int[j]. 

void exibirTabuleiro() {
    system("cls");
    printf("Partida %d\n\n", partidas);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
}
//Esse void é basicamente a mesma coisa da estrutura do void acima, exceto que este é responsável pela formatação de sua saída no terminal.
//A depender da formatação, as linhas(i<2) e as colunas(j<2) podem estar assimétricas e podem causar problemas de registro de pontuação no
//código.

void resetarTabuleiro() {
    char num = '1';
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            tabuleiro[i][j] = num++;
        }
    }
    jogadas = 0;
    simb = 'X';
}
//Esse void é responsável por alterar os simbolos do tabuleiro para afirmar que o jogador 1 realizou a jogada em tal posição. Além disso,
//também serve para contabilizar cada rodada até que tenha um vencedor ou tenha um empate.

_Bool verificarVencedor() {
    for(int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == simb && tabuleiro[i][1] == simb && tabuleiro[i][2] == simb) return true;
        if (tabuleiro[0][i] == simb && tabuleiro[1][i] == simb && tabuleiro[2][i] == simb) return true;
    }
    if (tabuleiro[0][0] == simb && tabuleiro[1][1] == simb && tabuleiro[2][2] == simb) return true;
    if (tabuleiro[0][2] == simb && tabuleiro[1][1] == simb && tabuleiro[2][0] == simb) return true;
    return false;
}
//Essa estrutura booleana serve para verificar o vencedor da partida ou o empate.

void alternarJogador() {
    simb = (simb == 'X') ? 'O' : 'X';
}
//Esse void é responsável por alterar os simbolos do tabuleiro para afirmar que o jogador 2 realizou a jogada em tal posição.

void alternarNomes() {
    if (strcmp(nom, nome1) == 0) {
        strcpy(nom, nome2);
    } else {
        strcpy(nom, nome1);
    }
}
//Esse void é responsável por alternar os jogadores quando o turno de ação de cada ser executado.

void jogar() {
    char posicao;
    char resposta;

    do {
        resetarTabuleiro();
        strcpy(nom, nome1);
        partidas++;
        while (1) {
            exibirTabuleiro();
            printf("\nJogada %d\n", jogadas+1);
            printf("\nVez do jogador %s. Escolha a posição (1-9): ", nom);
            scanf(" %c", &posicao);

            int pos = posicao - '1';
            int linha = pos / 3;
            int coluna = pos % 3;

            if (pos < 0 || pos > 8 || tabuleiro[linha][coluna] == 'X'||tabuleiro[linha][coluna] == 'O') {
                printf("\nPosição inválida! Tente novamente.\n");
                sleep(2);
                continue;
            }

            tabuleiro[linha][coluna] = simb;
            jogadas++;

            if (jogadas >= 5 && verificarVencedor()) {
               
                exibirTabuleiro();
                printf("\n%s venceu!\n", nom);
                if (simb == 'X') vitoriasX++;
                else vitoriasO++;
                break;
            }

            if (jogadas == 9) {
                exibirTabuleiro();
                printf("Empate!\n");
                empates++;
                break;
            }

            alternarJogador();
            alternarNomes();
        }

        printf("\nVocês desejam jogar novamente? (s/n): ");
        scanf(" %c", &resposta);

    } while (resposta == 's' || resposta == 'S');

    printf("\nRetornando para o menu...\n");
    sleep(2);
}
//Esse void seria a junção todas as estruturas de funcionalidade vistas anteriormente para fazer com que o sistema criado funcione. 

void exibirEstatisticas() {
    printf("\n==== Estatísticas ====\n");
    printf("Vitórias de %s: %d\n", nome1, vitoriasX);
    printf("Vitórias de %s: %d\n", nome2, vitoriasO);
    printf("Empates: %d\n", empates);
    printf("Quantidade de partidas: %d\n", partidas);
    printf("======================\n\n");
    sleep(5);
}
//Esse void utiliza os voids de lerJogador e as váriaveis int vitoriasX, vitoriasO, empates e partidas, para exibir as estatísticas.

void menu(){

    printf("*\n");
    printf("*      JOGO DA VELHA      *\n");
    printf("*                         *\n");
    printf("*  1 - JOGAR              *\n");
    printf("*  2 - ESTATíSTICAS       *\n");
    printf("*  3 - SAIR               *\n");
    printf("*                         *\n");
    printf("*\n");
}
//Esse void seria a tela inicial que será mostrada após colocar os nomes dos jogadores.

int obterOpcao() {
    int opcao;
    char c;

    while (1) {
        printf("Digite a opção desejada: ");
        if (scanf("%d", &opcao) == 1) {
            return opcao;
        } else {
            printf("Opção inválida! Digite apenas números.\n");
            while ((c = getchar()) != '\n' && c != '\n');
        }
    }
}
//Essa váriavel assegura que os jogadores apenas coloquem números e toda vez que detecta um simbolo ou letra(getchar()), o código não
//irá concluir com seu loop programado.

int main(){
    setlocale(LC_ALL, "pt-BR.UTF-8");
    lerJogador();
   
    do{
        system("cls");
        menu();
        op = obterOpcao();
        system("cls");

        switch(op){
            case 1:{
                inicializarTabuleiro();
                jogar();
                break;
            }
            case 2:{
                exibirEstatisticas();
                break;
            }
            default:{
                if(op<0 || op>3){
                    printf("\nOpção inválida! Digite novamente\n");
                    sleep(2);

                }
                break;
            }
        }
    }while(op!=3);
    system("cls");
    printf("Obrigado por Jogar! =D");
}
//Esse void seria a estrutura geral do código, onde cada váriavel é posta em sequências de atuação quando o mesmo for compilado e que pode 
//ser alterado de acordo com a vontade do dev.

//-SIMBOLOGIA E LETRAS-//

//!=Seria para inverter o valor de uma condição.
//&=Essa condição serve para retornar ao endereço de uma variável está armazenada na mesma estrutura.
//&&=Seria usado para confirmar dois ou mais valores de acordo com a condição.
//++=Seria a condição usada para incrementar mais valores depois do estabelecido.
//[i]=Seria um comando para adicionar linhas.
//[j]=Seria um comando para adicionar colunas.