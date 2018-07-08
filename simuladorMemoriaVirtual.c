#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define TRUE  1
#define FALSE 0


char *  itoa ( int value, char * str ){
    char temp;
    int i =0;
    while (value > 0) {
        int digito = value % 10;

        str[i] = digito + '0';
        value /= 10;
        i++;

    }
   i = 0;
   int j = strlen(str) - 1;

   while (i < j) {
      temp = str[i];
      str[i] = str[j];
      str[j] = temp;
      i++;
      j--;
   }
    return str;
}

void _pause(){
	getchar();
	getchar();
}

void menu(){

	int opcao = -1;

	system("clear");

	printf("Menu:\n\n");

	printf("1 - Criar arquivo com elementos;\n");
	printf("2 - Gerar subArquivos;\n");
	printf("9 - Fechar programa;\n\n");
	printf("Opcao: ");

	scanf("%d", &opcao);
	chamaOpcoes(opcao);
}

void chamaOpcoes(int opcao){

	if(opcao == 1){
		criaArquivoOpcao1();
	}else if(opcao == 2){
		criarArquivoDivididoOpcao2();
	}else if(opcao == 9){
		system("clear");
		printf("Tchau...\n");
		exit(1);
	}else{
		printf("Opcao invalida.\n");
		_pause();
		menu();
	}

}

void criaArquivoOpcao1(){
	system("clear");
	int qtd=0;
	printf("Criacao de arquivo:\n\n");
	printf("Informe a quantidade de numeros que deseja no arquivo: ");
	scanf("%d", &qtd);

	FILE * fp = fopen("arquivoTotal.txt" , "w");

	if(fp == NULL){
		printf("Nao foi possivel escrever no arquivo.\n");
		_pause();
		menu();
	}

	int i=0;

	for( ; i<=qtd ; i++){
		fprintf(fp, "%d ",i );
	}

	fclose(fp);

	printf("Arquivo Gerado com sucesso!\n");
	_pause();
	menu();
}

void criarArquivoDivididoOpcao2(){
	system("clear");

	int tamArquivos = -1;

	printf("Divisao do arquivo em subArquivos\n\n");
	printf("Digite a quantidade de bytes maximo que os subArquivos terao (MINIMO 4): ");
	scanf("%d", &tamArquivos);

	//criar os subArquivos
	//int total = total + sizeof(int); //soma a quantidade de inteiros enquanto for menor que tamArquivo.

	char NomeArquivo[] = "arquivoTotal - parte ";	
	char formato[] = ".txt";
	int total = 0 , parte = 1;

	FILE * aTotal = fopen("arquivoTotal.txt","r");
    FILE * fp = NULL;

	while(!feof(aTotal)){

		if(total == 0){
			char sql[40] = "";
			strcat(sql,NomeArquivo);			
			char valor[50] = "";
			itoa(parte, valor);			
			strcat(sql,valor);
			strcat(sql,formato);

			printf("NOME = %s\n",sql);

			fp = fopen(sql , "w");
		} 

		int vv = 0;
		fscanf(aTotal ,"%d ",&vv);
		total += sizeof(int);
		fprintf(fp , "%d ", vv);

		if(total >= tamArquivos){
			fclose(fp);
			total = 0;
			parte++;
		}
	}

    fclose(fp);
    fclose(aTotal);

	_pause();
	menu();
}

int main(){
	menu();
	return 0;
}
