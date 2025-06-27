#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EQUIP 100

//estrutura do equipamento
typedef struct {
    int id;
    char nome[50];
    int quantidade_max;
    int quantidade_disponivel;
    char status[20];
} Equipamento;

// var globais
int id=0;

//funções
void cadastrarEquipamento(Equipamento*, int*);
void listarEquipamentos(Equipamento*,int); 
void emprestarEquipamento(Equipamento*,int n); 
void devolverEquipamento(Equipamento*,int n); 
void salvarDados(Equipamento*,int,const char*);
void carregarDados(Equipamento*,int*,const char*);
void menu();

int main() {

    Equipamento equipamentos[MAX_EQUIP];
    int n = 0;
    int opcao;

    carregarDados(equipamentos,&n,"equipamentos.txt");
	id = n;

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
            default: printf("Opcao invalida.\n");

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
    printf("Escolha uma opcao: ");
}

void cadastrarEquipamento(Equipamento *equipamentos, int *n){

    int p;
	int s;
	do {
		puts("Digite o nome do equipamento para cadastro: ");
		scanf("%s", equipamentos[*n].nome);

		puts("Digite a quantidade desse equipamento: ");
		scanf("%d", &equipamentos[*n].quantidade_max);
		if(!(equipamentos[*n].quantidade_max)){

			puts("Digite uma quantidade válida.");
			continue;

		}

		equipamentos[*n].quantidade_disponivel=equipamentos[*n].quantidade_max;	

		puts("\nDigite o estado do equipamento(0=Disponivel,1=Emprestado,2=Manuten��o): ");
		scanf("%d", &s);
		if(s<0&&s>2){

			puts("Digite um equipamento válido;");
			continue;

		} 
		if(!(s)) strcpy(equipamentos[*n].status, "Disponível");
		if(s==1) strcpy(equipamentos[*n].status, "Emprestado");
		if(s==2) strcpy(equipamentos[*n].status, "Manuntenção");

		equipamentos[*n].id = id;
		*n += 1;
		id++;

		puts("voce quer cadastrar mais um equipamento? (1 = sim, 0 = nao): ");
		scanf("%d", &p);
		} while(p);
		
	}

void listarEquipamentos(Equipamento *equipamentos, int n){

	int a;
	
	puts("NOME |ID |QTD_MAX |QTD_DISP | STATUS\n");
	for(a=0; a<n;a++) {

		if(!(equipamentos[a].quantidade_max)) continue;
		printf("%s |%d |%d |%d |%s", equipamentos[a].nome, equipamentos[a].id, equipamentos[a].quantidade_max, equipamentos[a].quantidade_disponivel, equipamentos[a].status);
		puts("");

	}
}
void emprestarEquipamento(Equipamento *equipamentos, int n){
int idn;
	do {
		puts("Digite o ID do equipamento que deseja pegar: (ou 0 para retornar ao menu)");
		scanf("%d",&idn);
		int i;
		int q;
		for(i=0;i<n;i++){
			
			if (idn == equipamentos[i].id){
				puts("Digite a quantidade a ser emprestada:");
				scanf("%d", &q);
				if(q>equipamentos[idn].quantidade_disponivel){

					puts("Quantidade não disponível");
					i--;
					continue;

				}
				
				equipamentos[idn].quantidade_disponivel -= q;
				strcpy(equipamentos[idn].status, "Emprestado");
				return;
			}
		}
	puts("Digite um ID valido.\n");
	} while (idn);
}

void devolverEquipamento(Equipamento *equipamentos,int n){

int idn=0;

	do {

		puts("Digite o ID do equipamento que deseja devolver: (ou 0 para retornar ao menu)");
		scanf("%d",&idn);

		int q;

		for(int i=0;i<n;i++){

			if (idn == equipamentos[i].id){
				
				puts("Digite a quantidade a ser devolvida:");
				scanf("%d", &q);

			if(equipamentos[idn].quantidade_disponivel+q>equipamentos[idn].quantidade_max){ 

				puts("Não é quantidade máxima do equipemento, digite uma quantidade válida");
				i--;
				continue;

			}

				equipamentos[idn].quantidade_disponivel += q;
				strcpy(equipamentos[idn].status, "Disponível");
				return;

			}
			
		}

		puts("Digite um ID valido.");

	} while(idn);
}

void salvarDados(Equipamento *equipamentos,int n,const char *nome_arquivo){

	FILE *file = fopen(nome_arquivo, "w");

	if (file == NULL) {
		puts("Erro ao abrir o arquivo para escrita.");
		return;
	}
	
	for (int i = 0; i < n; i++) {

		fprintf(file, "%d %s %d %d %s\n", 
				equipamentos[i].id, 
				equipamentos[i].nome, 
				equipamentos[i].quantidade_max, 
				equipamentos[i].quantidade_disponivel, 
				equipamentos[i].status);

	}
	
	fclose(file);
	puts("Dados salvos com sucesso.");

}

void carregarDados(Equipamento *equipamentos,int *n, const char *nome_arquivo) {

    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        puts("Erro ao abrir o arquivo.");
        return;
    }

    int i = 0;

    while (fscanf(file, "%d %49s %d %d %19s",
                  &equipamentos[i].id,
                  equipamentos[i].nome,
                  &equipamentos[i].quantidade_max,
                  &equipamentos[i].quantidade_disponivel,
                  equipamentos[i].status) == 5) {
        i++;
    }

    fclose(file);

	*n =i;

}
	
