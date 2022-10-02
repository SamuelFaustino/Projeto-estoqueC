#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

FILE *arq;
int indc = 0;
FILE *cont;

typedef struct{
    int id;
    char nome[50];
    char desc[50];
    float preco;
    char data[12];
    int quant;
}fichaProduto;

void menu(void);

int CadastroProduto(fichaProduto produto[10]);

int ExcluiProduto (fichaProduto produto[10]);

int AlteraProduto(fichaProduto produto[10], int altindc);
			
int LocalizaProduto(fichaProduto produto[10]);
	 
int ListaProduto(fichaProduto produto[10], int i);

void salvarAlt(fichaProduto produto[10]);

void indcfisico();
	
void lerarquivo(fichaProduto produto[10]);

int main(){
setlocale(LC_ALL, "Portuguese");

	menu();
	
	return 0;
}

void lerarquivo(fichaProduto produto[10]) {
	int indcsalvo = 0, i=0;
	cont = fopen("contador.txt","r");
	if(cont != NULL) {
		//cont = fopen("contador.txt","r");
		fscanf(cont,"%d",&indcsalvo);
		fclose(cont);

	}else{
		printf("\nArquivo naO criado!\n");

	}	
	arq = fopen("estoque.bin","rb");
	if (arq != NULL) {
		//arq = fopen("estoque.bin","r");
		for(i=0; i<indcsalvo; i++){
			fread(&produto[i].id, sizeof(fichaProduto), 10, arq);	
			fread(&produto[i].nome, sizeof(fichaProduto), 10, arq);	
			fread(&produto[i].desc, sizeof(fichaProduto), 10, arq);	
			fread(&produto[i].preco, sizeof(fichaProduto), 10, arq);	
			fread(&produto[i].data, sizeof(fichaProduto), 10, arq);	
			fread(&produto[i].quant, sizeof(fichaProduto), 10, arq);


			/*fscanf(arq,"%d\n",&produto[indc].id);
			fgets(produto[indc].nome,50,arq);
			fgets(produto[indc].desc,50,arq);
			fscanf(arq,"%f\n",&produto[indc].preco);
			fgets(produto[indc].data,12,arq);
			fscanf(arq,"%d\n",&produto[indc].quant);*/
			
			indc++;
		}
		printf("\nEstoque carregado com sucesso!\n\n");
		fclose(arq);
	
	}else{
		printf("Arquivo nao criado!\n");
	}
}

void indcfisico() {

	cont = fopen("contador.txt","w");
	
	if (arq == NULL){
		printf("Arquivo Nao criado!\n");
	}else{
		fprintf(cont,"%d",indc);
	}
	fclose(cont);
}

void salvarAlt(fichaProduto produto[10]) {
	
	arq = fopen("estoque.bin","wb");
	if (arq == NULL){
		printf("Arquivo Nao criado!\n");
	}else{
		int i;
		printf("\n**Estoque Aberto!**\n");
		for(i=0;i<indc;i++){
			fwrite(&produto[i].id, sizeof(fichaProduto), 10, arq);	
			fwrite(&produto[i].nome, sizeof(fichaProduto), 10, arq);	
			fwrite(&produto[i].desc, sizeof(fichaProduto), 10, arq);	
			fwrite(&produto[i].preco, sizeof(fichaProduto), 10, arq);	
			fwrite(&produto[i].data, sizeof(fichaProduto), 10, arq);	
			fwrite(&produto[i].quant, sizeof(fichaProduto), 10, arq);	
			
			/*fprintf(arq,"%d\n",produto[i].id);
		    fprintf(arq,"%s",produto[i].nome);
		    fprintf(arq,"%s",produto[i].desc);
		    fprintf(arq,"%.2f\n",produto[i].preco);
		    fprintf(arq,"%s",produto[i].data);
		    fprintf(arq,"%d\n\n",produto[i].quant);	*/
		}
	}
    fclose(arq);
}

int ListaProduto(fichaProduto produto[10], int i) {
	
	if ( indc  != 0){
			 
		printf("\n Produtos cadastrados: [%d]\n\n ", indc);
			 
		for (i = 0; i < indc; i++) {
			printf("\n-------------------\n");
			printf("\n -Id: %d", produto[i].id);
		    printf("\n -Nome: %s", produto[i].nome);
		    printf(" -Descricao: %s", produto[i].desc);
		    printf(" -Preco: %2.f", produto[i].preco);
		    printf("\n -Data: %s", produto[i].data);
		    printf(" -Quantidade: %d \n\n", produto[i].quant);
	}
		printf("\n\nListagem dos produtos concluída!");
		getchar();getchar();
    	system("clear");
    	
	}else
		printf("Nenhum produto cadastrado!\n\n");
    	
 	return indc;   
}

int LocalizaProduto(fichaProduto produto[10]) {
	int opclocaliza, localizaID, controle, i;
	char localizanome[15];
	
	if ( indc  != 0)
	{
	 	printf("\n LOCALIZAR PRODUTO\n\n");
		 
		printf("\n Selecione o modo de busca:\n\n");
		printf("1 - Por ID\n");
	 	printf("2 - Por nome\n\n");
	 	scanf("%d", &opclocaliza);
	 	if (opclocaliza == 1)
	 	{
			printf("Digite o ID do produto a ser localizado: ");
			scanf("%d", &localizaID);
			for (i = 0; i < indc; i++)
			{
				if (produto[i].id == localizaID)
				{
					printf("\n- ID: %d ", produto[i].id);
		    		printf("\n- Nome: %s ", produto[i].nome);
		    		printf("\n- Descrição: %s ", produto[i].desc);
		    		printf("\n- Preço: %2.f ", produto[i].preco);
		    		printf("\n- Data: %s ", produto[i].data);
		    		printf("\n- Quantidade: %d \n\n", produto[i].quant);
		    		controle++;
		    	}
			}
		}
	    
		else
		{
			printf("Digite o NOME do produto a ser localizado: ");
			scanf("%s", &localizanome);
			for (i=0; i<indc; i++)
			{
				if (strcmp (produto[i].nome,localizanome) == 0)
				{
					printf("\n- ID: %d ", produto[i].id);
		    		printf("\n- Nome: %s ", produto[i].nome);
		    		printf("\n- Descrição: %s ", produto[i].desc);
		    		printf("\n- Preço: %2.f ", produto[i].preco);
		    		printf("\n- Data: %s ", produto[i].data);
		    		printf("\n- Quantidade: %d \n\n", produto[i].quant);
		    		controle++;
		    	}
			}
		}
		
		if (controle==0)
			   printf("\n\nProduto NÃO localizado!\n\n");
	        else
	  		   printf("\n\nProduto(s) localizado(s) com sucesso!");
	  		   
		getchar();
	    system("clear");
		 
	 }
	 else
		printf("Nenhum produto cadastrado!\n\n");

    return indc;
}

int ExcluiProduto (fichaProduto produto[10]) {
	
	if ( indc  != 0) {
		
		printf("\n EXCLUIR PRODUTO\n\n");
		
		int opcexcluir, opcconfirma, i;
		printf ("\nEscolha a posição a ser excluída: ");
		scanf ("%d", &opcexcluir);
		
		if (opcexcluir > indc)
		   printf ("\n\nPosição não encontrada\n\n");
	    else
	 	{
	
		printf ("\n\nOs seguintes dados estão cadastrados neste registro: ");
		printf("\n\n- ID: %d ", produto[opcexcluir].id);
	 	printf("\n- Nome: %s ", produto[opcexcluir].nome);
	  	printf("\n- Descrição: %s ", produto[opcexcluir].desc);
	   	printf("\n- Preço: %2.f ", produto[opcexcluir].preco);
		printf("\n- Data: %s ", produto[opcexcluir].data);
	 	printf("\n- Quantidade: %d \n\n", produto[opcexcluir].quant);
	 	printf("\n\n Tem certeza que deseja excluir o registro? (Digite [1] para confirmar!)");
	 	scanf ("%d", &opcconfirma);
	 		if (opcconfirma == 1){
	 			
	 		for (i = opcexcluir; i < indc; i++){
			 
				produto[i].id = produto[i+1].id;
				strcpy (produto[i].nome, produto[i+1].nome);
				strcpy (produto[i].desc, produto[i+1].desc);
				produto[i].preco = produto[i+1].preco; 
				strcpy (produto[i].data, produto[i+1].data);
				produto[i].quant = produto[i+1].quant;
		
			}
				printf("Registro excluído com sucesso!");
				indc--;
					
		}
	 	   	else
	 			printf("\n\nOperação CANCELADA!");
	 	}
		getchar();
	 	system ("clear");	
				
		}
		 else {		
			printf("Nenhum produto cadastrado!");
			getchar();
			system("clear");
		}
		
 	return indc;
}

int CadastroProduto(fichaProduto produto[10]) {
	
	if ( indc  < 10)
	{
	printf("\nCADASTRAR NOVO PRODUTO\n\n");
	printf("\n- ID: ");
    scanf("%d",&produto[indc].id);
    
    printf("\n- Nome: ");
    fflush(stdin);//__fpurge(stdin);
    fgets(produto[indc].nome,50,stdin);
    
    printf("\n- Descrição: ");
    fflush(stdin);//__fpurge(stdin);
    fgets(produto[indc].desc,50,stdin);
             
    printf("\n- Preço: ");
    scanf("%f", &produto[indc].preco);

    printf("\n- Data: ");
    fflush(stdin);//__fpurge(stdin);
    fgets(produto[indc].data,12,stdin);

    printf("\n- Quantidade: ");
    scanf("%d",&produto[indc].quant);
    
    printf("\n\nProduto cadastrado co sucesso!");
    getchar();
	getchar();
    system("clear");
			 
	indc++;
	}else
		printf("Estoque cheio!\n\n");

    return indc;
}

int AlteraProduto(fichaProduto produto[10], int altindc) {
	
	printf("\nDigite a posição que deseja alterar: ");
	scanf("%d", &altindc);
	
	if (altindc < indc) {
		
		printf("\nALTERAR DADOS DO PRODUTO\n\n");
			 
		printf("\n- ID: ");
	    scanf("%d",&produto[altindc].id);
	    printf("\n- Nome: ");
	    fflush(stdin);//__fpurge(stdin);
	    fgets(produto[altindc].nome,50,stdin);
	    printf("\n- Descrição: ");
	    fflush(stdin);//__fpurge(stdin);
	    fgets(produto[altindc].desc,50,stdin);
	             
	    printf("\n- Preço: ");
	    scanf("%f", &produto[altindc].preco);
	
	    printf("\n- Data: ");
	    fflush(stdin);//__fpurge(stdin);
	    fgets(produto[altindc].data,12,stdin);
	
	    printf("\n- Quantidade: ");
	    scanf("%d",&produto[altindc].quant);
	    
	    printf("\n\nProduto alterado com sucesso!");
	    
	    getchar();
	    system("clear");	
	    
		}else
		printf("\n\nPosição NÃO encontrada!\n\n");

    return indc;
}

void menu(void) {
	fichaProduto produto[10];   
	char op;
	int altindc = 0, i = 0;
	int opclocaliza = 0;
	
	lerarquivo(produto);
	
	do{
        printf("\n------- MENU -------- \n ");
        printf("1 - Inserir   Produto  \n ");
        printf("2 - Alterar   Produto  \n ");
        printf("3 - Excluir   Produto  \n ");
        printf("4 - Pesquisar Produto\n ");
        printf("5 - Listar    Produtos\n");
        printf(" 6 - Sair \n ");
        printf("--------------------- \n ");
        
        printf("Escolha a sua opção: ");
        fflush(stdin);//__fpurge(stdin);
		
		scanf("%c",&op);
		
        switch(op){
        
		case '1': 
			CadastroProduto(produto);
			break;
		
		case '2':
			AlteraProduto(produto, altindc);				
			break;
		
		case '3':
			indc = ExcluiProduto(produto);
			break;
			
		case '4':
			LocalizaProduto(produto);
			break;
			 
		case '5':
			ListaProduto(produto,i);
			break;
			
		case '6':
			system("clear");
	    	printf("\nPrograma Encerrado.");
	    	salvarAlt(produto);
	    	indcfisico();
			getchar();
			getchar();
			system("clear");
	        break;
	        
        default:
	        printf("\n**Opção inválida**"); 
			getchar();
			system("clear");
        }
    }while(op != '6' );
	
}

