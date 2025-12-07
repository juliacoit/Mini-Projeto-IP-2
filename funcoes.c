#include "terrenos.h"

void inicializarVetor(Terreno *lista[]) {
    for (int i = 0; i < MAX_TERRENOS; i++) {
        lista[i] = NULL;
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarPosicaoLivre(Terreno *lista[]) {
    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (lista[i] == NULL) return i;
    }
    return -1; // Cheio
}

int buscarPorID(Terreno *lista[], int id) {
    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (lista[i] != NULL && lista[i]->id == id) {
            return i;
        }
    }
    return -1; // Não encontrado
}

void criarTerreno(Terreno *lista[]) {
    int pos = buscarPosicaoLivre(lista);
    if (pos == -1) {
        printf("ERRO: Limite de terrenos atingido.\n");
        return;
    }

    // ALOCAÇÃO DINÂMICA
    lista[pos] = (Terreno*) malloc(sizeof(Terreno));
    if (lista[pos] == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    Terreno *t = lista[pos]; // Ponteiro auxiliar para facilitar

    printf("\n--- Novo Terreno (ID: %d) ---\n", pos + 1);
    t->id = pos + 1; // ID sequencial simples ou peça ao usuário
    
    printf("Largura (m): ");
    scanf("%f", &t->largura);
    printf("Comprimento (m): ");
    scanf("%f", &t->comprimento);
    printf("Preco por m2: ");
    scanf("%f", &t->preco_m2);

    // Cálculos automáticos
    t->area = t->largura * t->comprimento;
    t->valor_total = t->area * t->preco_m2;

    printf("--- Dados do Proprietario ---\n");
    limparBuffer();
    printf("Nome: ");
    fgets(t->dono.nome, 50, stdin);
    t->dono.nome[strcspn(t->dono.nome, "\n")] = 0; // Remove \n

    printf("CPF: ");
    fgets(t->dono.cpf, 15, stdin);
    t->dono.cpf[strcspn(t->dono.cpf, "\n")] = 0;

    t->ocupado = 1; // Marca como ocupado
    printf("Terreno cadastrado com sucesso! Valor Total: R$ %.2f\n", t->valor_total);
}

void editarTerreno(Terreno *lista[]) {
    int id;
    printf("Digite o ID para editar: ");
    scanf("%d", &id);
    
    int pos = buscarPorID(lista, id);
    if (pos == -1) {
        printf("Terreno nao encontrado.\n");
        return;
    }

    // Editar apenas o preço por exemplo (pode expandir para tudo)
    printf("Novo preco por m2 (Atual: %.2f): ", lista[pos]->preco_m2);
    scanf("%f", &lista[pos]->preco_m2);
    
    // Recalcular valor total
    lista[pos]->valor_total = lista[pos]->area * lista[pos]->preco_m2;
    printf("Atualizado!\n");
}

void removerTerreno(Terreno *lista[]) {
    int id;
    printf("Digite o ID para remover: ");
    scanf("%d", &id);

    int pos = buscarPorID(lista, id);
    if (pos != -1) {
        free(lista[pos]); // LIBERA MEMÓRIA
        lista[pos] = NULL; // Evita Ponteiro Selvagem
        printf("Terreno removido.\n");
    } else {
        printf("Nao encontrado.\n");
    }
}

void mostrarPorID(Terreno *lista[]) {
    int id;
    printf("Busca ID: ");
    scanf("%d", &id);
    int i = buscarPorID(lista, id);

    if (i != -1) {
        printf("\n--- Detalhes ID %d ---\n", lista[i]->id);
        printf("Proprietario: %s (CPF: %s)\n", lista[i]->dono.nome, lista[i]->dono.cpf);
        printf("Dimensoes: %.2fx%.2f m\n", lista[i]->largura, lista[i]->comprimento);
        printf("Area: %.2f m2\n", lista[i]->area);
        printf("Valor Total: R$ %.2f\n", lista[i]->valor_total);
    } else {
        printf("Nao encontrado.\n");
    }
}

void mostrarEstatisticas(Terreno *lista[]) {
    int ocupados = 0;
    float valorPatrimonio = 0;

    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (lista[i] != NULL) {
            ocupados++;
            valorPatrimonio += lista[i]->valor_total;
        }
    }

    printf("\n--- Estatisticas ---\n");
    printf("Terrenos Ocupados: %d\n", ocupados);
    printf("Terrenos Livres: %d\n", MAX_TERRENOS - ocupados);
    printf("Valor Total dos Imoveis: R$ %.2f\n", valorPatrimonio);
}

void salvarDados(Terreno *lista[], char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "wb");
    if (!f) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    // Primeiro salvamos quantos terrenos ativos existem
    int contador = 0;
    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (lista[i] != NULL) contador++;
    }
    fwrite(&contador, sizeof(int), 1, f);

    // Agora salvamos os dados das structs apontadas
    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (lista[i] != NULL) {
            fwrite(lista[i], sizeof(Terreno), 1, f);
        }
    }

    fclose(f);
    printf("Dados salvos em '%s'.\n", nomeArquivo);
}

void carregarDados(Terreno *lista[], char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "rb");
    if (!f) {
        printf("Arquivo '%s' nao encontrado. Iniciando vazio.\n", nomeArquivo);
        return;
    }

    int contador;
    fread(&contador, sizeof(int), 1, f);

    // Limpar lista atual antes de carregar
    liberarMemoria(lista);

    for (int i = 0; i < contador; i++) {
        int pos = buscarPosicaoLivre(lista);
        if (pos != -1) {
            lista[pos] = (Terreno*) malloc(sizeof(Terreno));
            fread(lista[pos], sizeof(Terreno), 1, f);
        }
    }

    fclose(f);
    printf("%d terrenos carregados.\n", contador);
}

void liberarMemoria(Terreno *lista[]) {
    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (lista[i] != NULL) {
            free(lista[i]);
            lista[i] = NULL;
        }
    }
}
