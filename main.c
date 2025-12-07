#include "terrenos.h"
#include <unistd.h>

// --- DEFINIÇÃO DE CORES (Códigos ANSI) ---
#define RESET   "\033[0m"
#define VERMELHO "\033[31m"
#define VERDE   "\033[32m"
#define AMARELO "\033[33m"
#define AZUL    "\033[34m"
#define CYAN    "\033[36m"
#define NEGRITO "\033[1m"

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf(AMARELO "\n[Pressione ENTER para continuar...]" RESET);
    limparBuffer();
    getchar();
}

void exibirLogo() {
    printf(AZUL NEGRITO);
    printf("  _____                           _                       \n");
    printf(" |_   _|                         (_)                      \n");
    printf("   | | ___ _ __ _ __ ___ _ __   _ ___   ___ _   _ ___ \n");
    printf("   | |/ _ \\ '__| '__/ _ \\ '_ \\ | / __| / __| | | / __|\n");
    printf("   | |  __/ |  | | |  __/ | | || \\__ \\ \\__ \\ |_| \\__ \\\n");
    printf("   \\_/\\___|_|  |_|  \\___|_| |_|/ |___/ |___/\\__, |___/\n");
    printf("                              |__/           __/ |    \n");
    printf("                                            |___/     \n");
    printf(RESET);
    printf("  " CYAN ">>> SISTEMA DE GESTAO IMOBILIARIA v1.0 <<<" RESET "\n");
    printf("  ----------------------------------------------------\n");
}

int menu() {
    limparTela();
    exibirLogo();
    
    printf("\n" NEGRITO "  MENU PRINCIPAL:" RESET "\n\n");
    printf("  " VERDE "[1]" RESET " Cadastrar Novo Terreno\n");
    printf("  " CYAN  "[2]" RESET " Editar Terreno Existente\n");
    printf("  " VERMELHO"[3]" RESET " Remover Terreno\n");
    printf("  " AMARELO "[4]" RESET " Consultar por ID\n");
    printf("  " AZUL  "[5]" RESET " Relatorio Geral e Estatisticas\n");
    printf("  " NEGRITO "[0]" RESET " Salvar e Sair\n");
    
    printf("\n  " NEGRITO ">> Escolha uma opcao: " RESET);
    
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

int main(int argc, char *argv[]) {
    // Verifica argumentos
    if (argc < 2) {
        printf(VERMELHO "ERRO: Use %s <arquivo_dados.dat>" RESET "\n", argv[0]);
        return 1;
    }

    char *nomeArquivo = argv[1];
    Terreno *sistema[MAX_TERRENOS];

    limparTela();
    printf(AMARELO "Carregando sistema..." RESET "\n");
    inicializarVetor(sistema);
    carregarDados(sistema, nomeArquivo);
    sleep(1);

    int opcao;
    do {
        opcao = menu();

        printf("\n");
        switch(opcao) {
            case 1: 
                printf(VERDE "--- NOVO CADASTRO ---" RESET "\n");
                criarTerreno(sistema); 
                pausar();
                break;
            case 2: 
                printf(CYAN "--- EDITAR DADOS ---" RESET "\n");
                editarTerreno(sistema); 
                pausar();
                break;
            case 3: 
                printf(VERMELHO "--- REMOVER REGISTRO ---" RESET "\n");
                removerTerreno(sistema); 
                pausar();
                break;
            case 4: 
                printf(AMARELO "--- CONSULTA ---" RESET "\n");
                mostrarPorID(sistema); 
                pausar();
                break;
            case 5: 
                printf(AZUL "--- RELATORIO ---" RESET "\n");
                mostrarEstatisticas(sistema); 
                pausar();
                break;
            case 0: 
                printf(VERDE "Salvando alteracoes..." RESET "\n");
                salvarDados(sistema, nomeArquivo);
                liberarMemoria(sistema);
                printf(NEGRITO "Sistema encerrado. Ate logo!" RESET "\n");
                break;
            default: 
                printf(VERMELHO "Opcao invalida!" RESET "\n");
                pausar();
        }
    } while(opcao != 0);

    return 0;
}
