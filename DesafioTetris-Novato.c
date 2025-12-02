#include <stdio.h>
#include <string.h>

#define TAM_FILA 5   // Tamanho fixo da fila

// Struct que representa uma peça de Tetris
typedef struct {
    char nome[10];   // Nome da peça (I, O, T, L, etc.)
    int id;          // ID único gerado automaticamente
} Peca;

// Fila circular
Peca fila[TAM_FILA];
int frente = 0;   // Índice para remover itens (dequeue)
int tras = 0;     // Índice para inserir itens (enqueue)
int qtd = 0;      // Quantidade de elementos na fila

int idGlobal = 1; // Controle simples para gerar IDs únicos


// -------------------
// Função que gera uma nova peça automaticamente
// -------------------
Peca gerarPeca() {
    Peca nova;
    
    // Vetor de peças possíveis
    char pecas[][10] = {"I", "O", "T", "L", "J"};

    // Escolhe uma peça baseado no ID (apenas para variar)
    strcpy(nova.nome, pecas[idGlobal % 5]);

    // Define ID da peça e incrementa o contador global
    nova.id = idGlobal++;

    return nova;
}


// -------------------
// Insere peça na fila (enqueue)
// -------------------
void inserirPeca() {
    if (qtd == TAM_FILA) {
        printf("\n  A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    // Insere a peça na posição "tras"
    fila[tras] = gerarPeca();

    // Atualiza o índice do final da fila (fila circular)
    tras = (tras + 1) % TAM_FILA;

    // Incrementa quantidade total
    qtd++;

    printf("\n Nova peça inserida na fila!\n");
}


// -------------------
// Remove peça da fila (dequeue)
// -------------------
void jogarPeca() {
    if (qtd == 0) {
        printf("\n  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    // Exibe a peça que está sendo jogada
    printf("\n🎮 Peça jogada: %s (ID %d)\n", fila[frente].nome, fila[frente].id);

    // Atualiza o índice da frente da fila (fila circular)
    frente = (frente + 1) % TAM_FILA;

    // Decrementa quantidade
    qtd--;
}


// -------------------
// Exibe o estado atual da fila
// -------------------
void exibirFila() {
    if (qtd == 0) {
        printf("\nA fila está vazia.\n");
        return;
    }

    printf("\n===== ESTADO ATUAL DA FILA =====\n");

    // Variável auxiliar para percorrer a fila circular
    int idx = frente;

    for (int i = 0; i < qtd; i++) {
        printf("Pos %d -> Peça: %s (ID %d)\n",
               idx,
               fila[idx].nome,
               fila[idx].id);

        // avança no buffer circular
        idx = (idx + 1) % TAM_FILA;
    }
}


// -------------------
// Inicializa a fila com 5 peças automáticas
// -------------------
void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
    }

    // Atualiza ponteiros da fila circular
    frente = 0;
    tras = 0;
    qtd = TAM_FILA;

    printf("\nFila inicializada com 5 peças!\n");
}


// -------------------
// Programa principal (menu)
// -------------------
int main() {
    int opcao;

    inicializarFila(); // Preenche fila com peças iniciais

    do {
        printf("\n===== MENU TETRIS STACK =====\n");
        printf("1. Visualizar fila\n");
        printf("2. Jogar peça (dequeue)\n");
        printf("3. Inserir nova peça (enqueue)\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirFila();
                break;

            case 2:
                jogarPeca();
                break;

            case 3:
                inserirPeca();
                break;

            case 4:
                printf("\n Saindo do jogo. Até mais!\n");
                break;

            default:
                printf("\n Opção inválida!\n");
        }

    } while (opcao != 4);

    return 0;
}
