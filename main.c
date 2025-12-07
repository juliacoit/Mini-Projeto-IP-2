#include "terrenos.h"

int main(int argc, char *argv[]) {
    // verifica se o usuário passou o nome do arquivo
    if (argc < 2) {
        printf("Uso correto: %s <arquivo_dados.dat>\n", argv[0]);
        return 1;
    }

    char *nomeArquivo = argv[1];
    Terreno *sistema[MAX_TERRENOS]; // vetor de ponteiros

    inicializarVetor(sistema);
    carregarDados(sistema, nomeArquivo);

    int opcao;
    do {
        printf("\n=== GESTAO DE TERRENOS ===\n");
        printf("1. Criar Terreno\n");
        printf("2. Editar Terreno\n");
        printf("3. Remover Terreno\n");
        printf("4. Mostrar por ID\n");
        printf("5. Estatisticas (Livres/Valor Total)\n");
        printf("0. Sair e Salvar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: criarTerreno(sistema); break;
            case 2: editarTerreno(sistema); break;
            case 3: removerTerreno(sistema); break;
            case 4: mostrarPorID(sistema); break;
            case 5: mostrarEstatisticas(sistema); break;
            case 0: 
                salvarDados(sistema, nomeArquivo);
                liberarMemoria(sistema);
                printf("Encerrando...\n");
                break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}
