# Jogo-RPG-na-linguagem-C

Com certeza! Um bom arquivo `README.md` é essencial para trabalhos acadêmicos, pois ajuda o professor (ou qualquer outra pessoa) a entender rapidamente o que é o projeto, como ele funciona e como executá-lo.

Aqui está um modelo customizado e estruturado em Markdown para o seu jogo de RPG em C:

---

# Jogo de RPG em C (Console)

Este é um jogo de RPG em modo texto desenvolvido em linguagem C para o console do Windows. O projeto foi construído como parte da disciplina de **Fundamentos da Programação**.

O jogador controla um herói (`H`) em um mapa de tamanho $7 \times 7$, onde o objetivo é derrotar o Boss (`B`) para conseguir a chave (`S`) e conseguir escapar pela saída. Pelo caminho, o jogador enfrentará monstros comuns (`M`) em combates baseados em rolagens de dados.

---

## 🎮 Como Jogar

### Controles

Você pode movimentar o herói utilizando tanto as teclas **WASD** quanto as **Selas Direcionais** do teclado:

* `W` ou `↑` : Mover para Cima
* `S` ou `↓` : Mover para Baixo
* `A` ou `←` : Mover para a Esquerda
* `D` ou `→` : Mover para a Direita
* `ESC` : Sair do jogo a qualquer momento.

### Elementos do Mapa

* `H` : O Herói (Você)
* `.` : Espaços vazios/caminho livre
* `P` : Paredes / Obstáculos intransponíveis
* `M` : Monstros comuns
* `B` : Chefe (Boss) — derrotá-lo garante a chave de saída
* `S` : Saída do mapa (só pode ser acessada com a chave)

---

## ⚙️ Mecânicas Implementadas

* **Geração Aleatória:** Os monstros e o Boss são posicionados aleatoriamente no mapa a cada nova execução utilizando `srand(time(NULL))`.
* **Sistema de Combate por Turnos:** Quando o herói tenta andar sobre a posição de um inimigo, uma batalha é iniciada. Um dado determina quem ataca primeiro, e o dano é calculado com base nos atributos de ataque do atacante menos a defesa do defensor.
* **Renderização em Tempo Real:** Utilização de funções da API do Windows (`windows.h`), como a `gotoxy`, para atualizar a tela apenas nas posições necessárias, evitando o efeito de "piscar" da tela (`system("cls")`).
* **Bordas Customizadas:** Uma função dedicada a desenhar molduras baseadas na tabela ASCII estendida para melhorar a interface visual no terminal.

---

## 🚀 Como Executar o Projeto

Como o projeto utiliza a biblioteca `<windows.h>` e `<conio.h>`, ele é **exclusivo para o sistema operacional Windows**.

### Pré-requisitos

* Um compilador C instalado (como o **GCC** através do MinGW) ou uma IDE como o **Dev-C++**, **Code::Blocks**, ou **VS Code** configurado.

### Passo a Passo pelo Terminal

1. Baixe o arquivo do código-fonte (ex: `main.c`).
2. Abra o Prompt de Comando (CMD) ou PowerShell na pasta do arquivo.
3. Compile o código com o comando:
gcc main.c -o jogo_rpg.exe
4. Execute o jogo:
./jogo_rpg.exe

## 📊 Estrutura de Dados Utilizada

O projeto utiliza uma `struct` principal para gerenciar os atributos das entidades do jogo:

struct personagem {
    int vida;   // Pontos de vida atuais
    int atq;    // Valor base de ataque
    int def;    // Valor de defesa contra danos
    int posx;   // Posição na linha da matriz
    int posy;   // Posição na coluna da matriz
    int chave;  // Flag (0 ou 1) que indica a posse da chave
};

## 👤 Autor

* **Seu Nome Aqui**
* Disciplina: Fundamentos da Programação
* Instituição: *Nome da sua Faculdade/Universidade*

---

### 💡 Dica extra para a apresentação:

Notei que no seu código, na função `main`, você declarou a variável `char letra;` no escopo global da função, mas dentro do laço `do { ... }` você colocou `char letra = getch();`.

Essa **redeclaração** faz com que a variável do `while(letra != 27...)` verifique a variável de fora, que nunca muda, podendo gerar um loop infinito ao apertar ESC. Para corrigir isso na apresentação, basta tirar o `char` de dentro do loop, deixando apenas:
letra = getch(); // Sem o 'char' antes
