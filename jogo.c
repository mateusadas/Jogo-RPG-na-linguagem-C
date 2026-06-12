#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#define TAM 7
#define MONSTROS 7

char mapa[TAM][TAM] = {{'H','.','.','.','.','.','.',},
                   {'.','.','.','.','.','.','.',},
                   {'.','.','.','.','.','.','.',},
                   {'.','.','.','.','.','.','.',},
                   {'.','.','.','.','.','P','.',},
                   {'.','.','.','.','.','P','.',},
                   {'.','.','.','.','.','.','S',}
                    };


struct personagem{
    int vida, atq, def, posx, posy, chave;
}heroi, monstros[MONSTROS];

int movimentos = 0;

void gotoxy(int x, int y){
    COORD c;
    c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}



void moldura(int linhaInicial, int linhaFinal, int colunaInicial, int colunaFinal, int tipo){
    int l, c;
    int borda[2][6] = {{205, 186, 201, 187, 200, 188},//Linha da matriz das bordas duplas
                      {196, 179, 218, 191, 192, 217}};//Linha da matriz das bordas simples

    //Faz a borda de cima
    for(c=colunaInicial+1; c<=colunaFinal-1;c++){
        gotoxy(c,linhaInicial); printf("%c", borda[tipo][0]);
        gotoxy(c,linhaFinal); printf("%c", borda[tipo][0]);
    }

    //Faz as bordas das laterais
    for(l=linhaInicial+1;l<=linhaFinal-1;l++){
        gotoxy(colunaInicial,l);printf("%c", borda[tipo][1]);
        gotoxy(colunaFinal,l);printf("%c", borda[tipo][1]);
    }

    //Coloca os cantos da moldura
    gotoxy(colunaInicial,linhaInicial); printf("%c", borda[tipo][2]);
    gotoxy(colunaFinal,linhaInicial); printf("%c", borda[tipo][3]);
    gotoxy(colunaInicial,linhaFinal);printf("%c", borda[tipo][4]);
    gotoxy(colunaFinal,linhaFinal); printf("%c", borda[tipo][5]);
}

void mostraMapa(){
    int l,c, aux;
    aux = (80 - TAM - 2)/2; //Tamanho total da janela menos 2 d borda menos a qtde de colunas, dividido por 2
    moldura(1,23,1,80,1); //Chamou pra fazer a moldura maior
    moldura(9,17,aux,aux+TAM+1,1); //Chamou pra fazer a moldura menor

    //Imprime o mapa do heroi
    for (l=0; l<TAM;l++){
        for(c=0;c<TAM;c++){
            gotoxy(aux+1+c, 10+l);
            /*if (mapa[l][c] == 'M')
                printf(".");
            else*/
            printf("%c", mapa[l][c]);
        }
    }
}

void geraMonstros(int qtde){
    int x, y, cont;

    //Colocando os montros
    for(cont=0;cont<qtde;cont++){
        x = rand()%TAM;
        y = rand()%TAM;
        if (mapa[x][y]=='.'){ //Se o espaço tiver um ponto pode colocar o monstro
            if (cont == 0){
                mapa[x][y] = 'B';
                monstros[cont].chave = 1;
            } else {
                mapa[x][y] = 'M';
                monstros[cont].chave = 0;
            }
            monstros[cont].posx = x;
            monstros[cont].posy = y;
            monstros[cont].atq = 2;
            monstros[cont].def = 1;
            monstros[cont].vida = 7;
        }else{//Se não ele descarta o movimento e tenta colocar de novo
            cont--;
        }
    }


}
void menssagem(int lin, int col, char *mens, int tam){
    int x;
    gotoxy(col,lin);
    printf("%s", mens);

    for(x=strlen(mens); x<=tam; x++){
        printf(" ");
    }
}

void rolarDados(int m){
    int dado, dano, atq;
    dado = rand()%2; //Dado para ver quem começa, heroi 0, monstro 1
    if(dado == 0){//heroi começa
        atq = rand()%6+heroi.atq;
        dano= atq - monstros[m].def;

        if(dano>0)
            monstros[m].vida -= dano;

        if(monstros[m].vida>0){
            atq = rand()%6+monstros[m].atq;
            dano = atq - heroi.def;
            if(dano>0)
                heroi.vida -= dano;
        }
    }
    else{
        atq = rand()%6+monstros[m].atq;
        dano= atq - heroi.def;
        if(dano>0)
            heroi.vida -= dano;
        if(heroi.vida>0){
            atq = rand()%6+heroi.atq;
            dano= atq - monstros[m].def;

            if(dano>0)
                monstros[m].vida -= dano;
        }
    }
    gotoxy(18, 22);
    printf("Ataque inicial [%02d] | Vida heroi [%02d] | Vida Monstro [%02d]", dado, heroi.vida, monstros[m].vida);


}

int batalha(int x, int y){
    int m;
    for(m=0; m<MONSTROS; m++){
        if (monstros[m].posx == x && monstros[m].posy == y){
            rolarDados(m);
            if(monstros[m].vida <=0){
                if (mapa[x][y] == 'B'){
                    menssagem(18, 22, "Boss derrotado!!! - Chave dropada!!", 30);
                    heroi.chave = 1;
                } else {
                    menssagem(18, 22, "Monstro derrotado!!!", 30);
                }

                mapa[x][y] = '.';
        }
      }
    }
    if(heroi.vida <=0){
        menssagem(18, 22,"Heroi Derrotado!!!", 30);
        return 0;
    }
/*{

    menssagem(20, 18, "Porrada!!!", 30);
    getch();
    menssagem(20, 18, "aaaaaaaaaaaaaaaaaaaaa", 30);
    getch();
    menssagem(20, 18, "oi", 30);
*/
}

int movimenta(char letra){
    int vivo =1;
    movimentos++;
    gotoxy(11,24); printf("Movimentos: %03d", movimentos);
    mapa[heroi.posx][heroi.posy]='.';
    if(letra == 80 || letra=='s'){  //Colocando pra ele andar para baixo tanto com S como com a flechinha para baixosws
        //Seria o conceito de colisão
        if(heroi.posx < TAM-1){       //Colocando TAM-1 pra que ele não saia da tela e tambem pra ele só se movimentar pra proxima posição se for um ponto
            if(mapa[heroi.posx+1][heroi.posy]=='.')
                heroi.posx++;
            else{
                if((mapa[heroi.posx+1][heroi.posy]=='M') ||
                   (mapa[heroi.posx+1][heroi.posy]=='B'))
                    vivo = batalha(heroi.posx+1, heroi.posy);
                else
                    if ((mapa[heroi.posx+1][heroi.posy]== 'S') &&
                        heroi.chave == 1){
                            vivo = 2;
                            menssagem(18, 22, "Barabeeeeennns, você venceu!!", 34);
                        }
            }

    }
    }
    if(letra == 72 || letra=='w'){ //Anda para cima
        if(heroi.posx > 0)
            if(mapa[heroi.posx-1][heroi.posy]=='.')
                heroi.posx--;
            else {
                if((mapa[heroi.posx-1][heroi.posy]=='M') ||
                   (mapa[heroi.posx-1][heroi.posy]=='B'))
                    vivo = batalha(heroi.posx-1,heroi.posy);
                else
                    if ((mapa[heroi.posx-1][heroi.posy]=='S') &&
                        heroi.chave == 1){
                            vivo = 2;
                            menssagem(18, 22, "Barabeeeeennns, você venceu!!", 34);
                        }
            }
    }
    if(letra ==77 || letra=='d'){  //Anda para a d
        if(heroi.posy < TAM-1)
            if(mapa[heroi.posx][heroi.posy+1]=='.')
                heroi.posy++;
            else {
                if((mapa[heroi.posx][heroi.posy+1]=='M') ||
                   (mapa[heroi.posx][heroi.posy+1]=='B'))
                    vivo = batalha(heroi.posx, heroi.posy+1);
                else
                    if((mapa[heroi.posx][heroi.posy+1] == 'S') &&
                        heroi.chave == 1){
                            vivo = 2;
                            menssagem(18, 22, "Barabeeeeennns, você venceu!!", 34);
                        }
            }
    }
    if(letra ==75 || letra=='a'){  //Anda para a e
        if(heroi.posy > 0)
            if(mapa[heroi.posx][heroi.posy-1]=='.')
                heroi.posy--;
            else{
                if((mapa[heroi.posx][heroi.posy-1]=='M') ||
                   (mapa[heroi.posx][heroi.posy-1]=='B'))
                    vivo = batalha(heroi.posx, heroi.posy-1);
                else
                    if((mapa[heroi.posx][heroi.posy-1] == 'S') &&
                        heroi.chave == 1){
                            vivo = 2;
                            menssagem(18, 22, "Barabeeeeennns, você venceu!!", 34);
                        }
            }
    }
    mapa[heroi.posx][heroi.posy]='H';
    return vivo;
}


/* Na função gera monstro eu estava em loop infinito pois estava mexendo com as posições reais do heroi. Para solução primeiro
declaro variaveis de linha e coluna inicial e final pegando a posição do heroi e decrescedo um e acrescendo um, depois usando if's
eu granti que as variaveis de inicio e fim do for sejam sempre valores dentro da matriz(ex:se a heroi posx for 0 a variavel l_inicial valeria -1
oque daria erro então caso de isso eu atribuo 0 que é o menor valor possível), e por fim fiz os laços for tendo como inicialização a atribuição
da linha inicial a uma variavel linha para não ocorrer loop infinito.
*/


void contaMonstros(){
    int qtd_monstros = 0, l_inicial, l_final, c_inicial, c_final, linha, coluna;
    l_inicial = heroi.posx - 1;
    l_final = heroi.posx + 1;
    c_inicial = heroi.posy - 1;
    c_final = heroi.posy + 1;
    if(l_inicial < 0){
        l_inicial = 0;
    }
    if(l_final > TAM-1){
        l_final = TAM-1;
    }
    if(c_inicial < 0){
        c_inicial = 0;
    }
    if(c_final > TAM-1){
        c_final = TAM-1;
    }

    for(linha=l_inicial; linha<=l_final; linha++){
        for(coluna = c_inicial; coluna<=c_final; coluna++){
            if(mapa[linha][coluna] == 'M' || mapa[linha][coluna] == 'B'){
                qtd_monstros = qtd_monstros + 1;
            }
        }
    }
    gotoxy(18,21);printf("Existem %02d monstros por perto!",qtd_monstros);

}
/*
VERSAO ERRADA
Aqui eu usava a mesma variavel para acrecer e servir de condição então quando posx valia 1 a posx+1 valia 2 e se repetia infinitamente
int qtd_monstros = 0;
    if(heroi.posx == 0 && heroi.posy == 0 || heroi.posx == 0 && heroi.posy == 1 || heroi.posx == 1 && heroi.posy == 0){
        for( ;heroi.posx <= heroi.posx+1; heroi.posx++){
            for( ; heroi.posy-1 <= heroi.posy+1; heroi.posy++){
                if(mapa[heroi.posx][heroi.posy] == 'M'){
                    qtd_monstros = qtd_monstros +1;
                }
            }
        }
    }
    if(heroi.posx == 6 && heroi.posy == 1){
        for( ;heroi.posx <= heroi.posx+1; heroi.posx++){
            for( ; heroi.posy-1 <= heroi.posy+1; heroi.posy++){
                if(mapa[heroi.posx][heroi.posy] == 'M'){
                    qtd_monstros = qtd_monstros +1;
                }
            }
        }
    }
    for( ;heroi.posx-1 <= heroi.posx+1; heroi.posx++){
        for( ; heroi.posy-1 <= heroi.posy+1; heroi.posy++){
            if(mapa[heroi.posx][heroi.posy] == 'M'){
                qtd_monstros = qtd_monstros +1;
            }
        }
    }
    gotoxy(20,26);printf("Existem %02d monstros por perto.",qtd_monstros);

}
*/


int main(){
    char letra;
    int vivo = 1;
    srand(time(NULL)); //Gerador randomico

    heroi.posx = heroi.posy = 0;
    heroi.vida = 10;
    heroi.atq = 4;
    heroi.def = 2;
    heroi.chave = 0;
    movimentos = 0;

    char nomeJogo[] = "Jogo de RPG";
    gotoxy((80-strlen(nomeJogo))/2, 5); //Nesta linha 5 cantralizando o jogo
    printf("%s", nomeJogo);
    geraMonstros(MONSTROS);
    do{
            mostraMapa();
            contaMonstros();
            char letra = getch();
            vivo = movimenta(letra);


    }while(letra != 27 && vivo >= 1);


}
