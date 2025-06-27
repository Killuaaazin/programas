#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EQUIP 100

typedef struct {
    int id;
    char nome[50];
    int quantidade_max;
    int quantidade_disponivel;
    char status[20];
} Equipamento;

char status_possiveis[3][19] = {"Disponivel","Emprestado","Manutencao"};

void menu();
void cadastrarEquipamento(Equipamento *equipamentos, int *n){
    int p;
	do {
		printf("Digite o nome do equipamento para cadastro: ");
			scanf("%s", equipamentos[*n].nome);
		printf("Digite o ID do equipamento: ");
			scanf("%d", &equipamentos[*n].id);
		printf("Digite a quantidade desse equipamento: ");
		    scanf("%d", &equipamentos[*n].quantidade_max);
		    equipamentos[*n].quantidade_disponivel=equipamentos[*n].quantidade_max;
		int b;	
		printf("\nDigite o estado do equipamento(0=Disponivel,1=Emprestado,2=Manutenção): ");
			scanf("%d", &b);
			strcpy(equipamentos[*n].status, status_possiveis[b]);
		*n += 1;
		printf("voce quer cadastrar mais um equipamento? (1 = sim, 0 = nao): ");
		scanf("%d", &p);	
		} while(p);
	}


void listarEquipamentos(Equipamento *equipamentos, int n){
	int a;
	printf("NOME |ID |QTD_MAX |QTD_DISP | STATUS\n");
	for(a=0; a<n;a++) {
		printf("%s |", equipamentos[a].nome);
		printf(" %d |", equipamentos[a].id);
		printf(" %d |", equipamentos[a].quantidade_max);
		printf(" %d |", equipamentos[a].quantidade_disponivel);
		printf(" %s ", equipamentos[a].status);
		printf("\n");
	}
}
void emprestarEquipamento(Equipamento *equipamentos, int n){
	int id=0;
	do {
		printf("Digite o ID do equipamento que deseja pegar: (ou -1 para retornar ao menu)");
		scanf("%d",&id);
		int i;
		for(i=0;i<n;i++){
			int q;
			if (id == equipamentos[i].id){
				printf("Digite a quantidade a ser emprestada:");
				scanf("%d", &q);
				equipamentos[i].quantidade_disponivel -= q;
				strcpy(equipamentos[i].status, status_possiveis[1]);
				return;
			}
		}
		printf("Digite um ID valido.");
	} while (id!=-1);
		
}
void devolverEquipamento(Equipamento *equipamentos, int n){}
void salvarDados(Equipamento *equipamentos, int n, const char *nome_arquivo){}
void carregarDados(Equipamento *equipamentos, int *n, const char *nome_arquivo){}

int main() {
    Equipamento equipamentos[MAX_EQUIP];
    int n = 0;
    int opcao;

    carregarDados(equipamentos, &n, "equipamentos.txt");

    do {
        menu();
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: cadastrarEquipamento(equipamentos, &n); break;
            case 2: listarEquipamentos(equipamentos, n); break;
            case 3: emprestarEquipamento(equipamentos, n); break;
            case 4: devolverEquipamento(equipamentos, n); break;
            case 5: salvarDados(equipamentos, n, "equipamentos.txt"); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while(opcao != 0);

    return 0;
}

void menu() {
    printf("\n===== MENU =====\n");
    printf("1. Cadastrar Equipamento\n");
    printf("2. Listar Equipamentos\n");
    printf("3. Emprestar Equipamento\n");
    printf("4. Devolver Equipamento\n");
    printf("5. Salvar Dados\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

