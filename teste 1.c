#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EQUIP 100
// Definição da estrutura do equipamento
 typedef struct Equipamento {
    int id;
    char nome[50];
    int quantidade;
    char status[20]; // "Disponivel", "Emprestado", "Manutencao"
 ;

// Variáveis globais (para simplificar)

int totalEquipamentos = 0;

// Protótipos das funções
void menuPrincipal();
void cadastrarEquipamento();
void listarEquipamentos();
void emprestarEquipamento();
void devolverEquipamento();
void salvarDados();
void carregarDados();

int main() {
    carregarDados(); // Carrega os dados ao iniciar
    
    int opcao;
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: cadastrarEquipamento(); break;
            case 2: listarEquipamentos(); break;
            case 3: emprestarEquipamento(); break;
            case 4: devolverEquipamento(); break;
            case 5: salvarDados(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}

void menuPrincipal() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Cadastrar equipamento\n");
    printf("2. Listar equipamentos\n");
    printf("3. Emprestar equipamento\n");
    printf("4. Devolver equipamento\n");
    printf("5. Salvar dados\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void cadastrarEquipamento() {
    if (totalEquipamentos >= 100) {
        printf("Limite de equipamentos atingido!\n");
        return;
    }
    
    printf("\n=== CADASTRO DE EQUIPAMENTO ===\n");
    
    // Preenche os dados do novo equipamento
    printf("ID: ");
    scanf("%d", &equipamentos[totalEquipamentos].id);
    
    printf("Nome: ");
    scanf("%s", equipamentos[totalEquipamentos].nome); // %s lê uma palavra sem espaços
    
    printf("Quantidade: ");
    scanf("%d", &equipamentos[totalEquipamentos].quantidade);
    
    printf("Status (Disponivel/Emprestado/Manutencao): ");
    scanf("%s", equipamentos[totalEquipamentos].status);
    
    totalEquipamentos++;
    printf("Equipamento cadastrado com sucesso!\n");
}

void listarEquipamentos() {
    if (totalEquipamentos == 0) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }
    
    printf("\n=== LISTA DE EQUIPAMENTOS ===\n");
    printf("ID\tNome\tQuantidade\tStatus\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < totalEquipamentos; i++) {
        printf("%d\t%s\t%d\t\t%s\n", 
               equipamentos[i].id,
               equipamentos[i].nome,
               equipamentos[i].quantidade,
               equipamentos[i].status);
    }
}

void emprestarEquipamento() {
    int id, qtd;
    
    printf("\n=== EMPRESTIMO ===\n");
    printf("Digite o ID do equipamento: ");
    scanf("%d", &id);
    
    // Procura o equipamento
    int encontrado = 0;
    for (int i = 0; i < totalEquipamentos; i++) {
        if (equipamentos[i].id == id) {
            encontrado = 1;
            
            if (strcmp(equipamentos[i].status, "Disponivel") != 0) {
                printf("Este equipamento nao esta disponivel.\n");
                return;
            }
            
            printf("Quantidade disponivel: %d\n", equipamentos[i].quantidade);
            printf("Quantidade a emprestar: ");
            scanf("%d", &qtd);
            
            if (qtd > equipamentos[i].quantidade) {
                printf("Quantidade indisponivel!\n");
                return;
            }
            
            equipamentos[i].quantidade -= qtd;
            if (equipamentos[i].quantidade == 0) {
                strcpy(equipamentos[i].status, "Emprestado");
            }
            
            printf("Emprestimo realizado com sucesso!\n");
            return;
        }
    }
    
    if (!encontrado) {
        printf("Equipamento nao encontrado!\n");
    }
}

void devolverEquipamento() {
    int id, qtd;
    
    printf("\n=== DEVOLUCAO ===\n");
    printf("Digite o ID do equipamento: ");
    scanf("%d", &id);
    
    // Procura o equipamento
    int encontrado = 0;
    for (int i = 0; i < totalEquipamentos; i++) {
        if (equipamentos[i].id == id) {
            encontrado = 1;
            
            if (strcmp(equipamentos[i].status, "Emprestado") != 0) {
                printf("Este equipamento nao consta como emprestado.\n");
                return;
            }
            
            printf("Quantidade a devolver: ");
            scanf("%d", &qtd);
            
            equipamentos[i].quantidade += qtd;
            strcpy(equipamentos[i].status, "Disponivel");
            
            printf("Devolucao realizada com sucesso!\n");
            return;
        }
    }
    
    if (!encontrado) {
        printf("Equipamento nao encontrado!\n");
    }
}

void salvarDados() {
    FILE *arquivo = fopen("equipamentos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }
    
    for (int i = 0; i < totalEquipamentos; i++) {
        fprintf(arquivo, "%d %s %d %s\n", 
                equipamentos[i].id,
                equipamentos[i].nome,
                equipamentos[i].quantidade,
                equipamentos[i].status);
    }
    
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

void carregarDados() {
    FILE *arquivo = fopen("equipamentos.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo nao encontrado. Iniciando com lista vazia.\n");
        return;
    }
    
    totalEquipamentos = 0;
    while (fscanf(arquivo, "%d %s %d %s", 
                 &equipamentos[totalEquipamentos].id,
                 equipamentos[totalEquipamentos].nome,
                 &equipamentos[totalEquipamentos].quantidade,
                 equipamentos[totalEquipamentos].status) != EOF) {
        totalEquipamentos++;
    }
    
    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}