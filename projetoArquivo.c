#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
//---------------- Define
#define maxNomeArquivo 100
#define maxExtencao 5
#define maxDiretorio 100

/* 
	Fazer um programa para o usuário que leia um arquivo e 
	retorne a quantidade de caracteres e a quntidade de strings 
	que possui no arquivo. 
 */
 
//---------------------------------- Protótipos das Funçoes -------------------------------
char* retornaNomeDoArquivoComAExencao(char* nomeDoArquivo, char* extencao,char* caracterAdd);
void leValidaTexto (char *texto, char *mensagemTitulo, int tamanho,char *mensagemErro);
void menu();
int contaQtdDeCaractersDaString(char* texto);
int contaQtdPalavrasNaLinha(char* texto);
void lerValidaCaracter(char *msgTitulo,char *msgErro,char *caracter,char *opcoes);
void fim();
//--------------------------------------------------------------------------------------


int main(int argc, char *argv[]) {
	
	// -------------- Variáveis de contagem
    
	int qtdPalavras = 0; 
	int qtdLinhas = 0; 
	int qtdCaracteres = 0;
    //----------------------------------
    FILE *arquivo; // Aponta para o arquivo 
    char texto[50]; //Variável que irá receber a string de onde está o arquivo
    char caracter; //Variável que irá receber os caracteres de onde está o arquivo
    char diretorio[200];//Diretorio do arquivo
    //------------------------------------ 
    char nomeDoArquivo[60];
    char extencao[4];
    char linha[100];
    int comecouPalavra = 0;
    char continuar;
    //------------------------------------
   	
	do
	{
		qtdPalavras = 0; 
		qtdLinhas = 0; 
		qtdCaracteres = 0;
	    system("cls");
	    
	    menu();
	    printf("\t| Forneca o diretorio do arquivo, sem o nome do arquivo.           |\n");
	    printf("\t| Exemplo: O diretorio do arquivo e C:/Users/Rebeca Divina/Desktop |\n");
	    printf("\t| ATENCAO: USE ESTA BARRA '/'                                      |\n");
		leValidaTexto(diretorio,"\t| Diretorio: ",maxDiretorio,"\t| Por algum motivo este diretorio não é válido! |");
		system("cls");
		
		
	    menu();
	    printf("\t| Para ler seu arquivo, escreva o nome do arquivo sem a extencao. |\n");
	    printf("\t| Exemplo: O nome do arquivo e 'arquivo.txt',                     |\n");
	    printf("\t| entao eu devo escrever apenas 'arquivo'                         |\n");
	    leValidaTexto(nomeDoArquivo,"\t| Nome: ",maxNomeArquivo,"\t| Por algum motivo este nome não é válido! |");
		system("cls"); 
	    
	    menu();
	    printf("\t\t| Forneca a extencao do arquivo.              |\n");
	    printf("\t\t| Exemplo: txt, doc, entre outros             |\n");
	    leValidaTexto(extencao,"\t\t| Extencao: ",maxExtencao,"\t| Por algum motivo este nome não é válido! |");
		system("cls"); 
		
		menu();
		strcpy(nomeDoArquivo, retornaNomeDoArquivoComAExencao(nomeDoArquivo, extencao,".")); //nome do arquivo com a extencao
	    strcpy(diretorio, retornaNomeDoArquivoComAExencao(diretorio, nomeDoArquivo,"/"));
		
	    arquivo = fopen(diretorio, "r"); //Abrindo o arquivo para leitura
	    
	    // --------- Verificar se o arquivo abriu corretamente
		if(arquivo == NULL){
	     printf("\nErro na abertura do arquivo!");
	     
	 	}else{
	
			while (!feof(arquivo)) {
				fgets(linha, 100, arquivo);
				qtdLinhas++;
				qtdCaracteres += contaQtdDeCaractersDaString(linha);
				qtdPalavras += contaQtdPalavrasNaLinha(linha);
			}	
			 
		}
		fclose(arquivo);
	
      	
		system("cls");
		menu();
	   	printf("\n\n\t __Resultado______________________________________________");
		printf("\n\t  O numero de palavras do arquivo e: %d", qtdPalavras);
		printf("\n\t  O numero de linhas do arquivo e: %d", qtdLinhas);
		printf("\n\t  O numero de caracteres do arquivo e: %d", qtdCaracteres);
		printf("\n\t _________________________________________________________");	
	
	   	lerValidaCaracter("\n\t\t Deseja ler outro arquivo?\n\t\t Se sim aperte(s) se nao(n): ","Infelizmente esa opcao não existe para este programa",&continuar,"SN");
	}while(continuar != 'N');
	fim();
   getchar();//finalizar programa
   return 0;
}
/*	Objetivo: Contar a quantidade de palavras de um texto
	Parâmetros: referencia ao vetor do texto.
	Retorno: quantidade de palavras que o texto possui
*/
int contaQtdPalavrasNaLinha(char* texto){
	int i;
	int qtd = 0;
	int soma = strlen(texto);
	int comecaPalavra = 0;
	strncat(texto,"\n",soma+1);

	for(i = 0; i < strlen(texto); i++){
		
		if(texto[i] != ' ' && texto[i] != '\n' && texto[i] != '\t'){
			comecaPalavra = 1;
		}
		
		if((texto[i] == ' ' || texto[i] == '\n') && comecaPalavra == 1){
			qtd++;
			comecaPalavra = 0;
		}
			
			
	}
	return qtd;
}

/*	Objetivo: Contar a quantidade de caracteres de um texto
	Parâmetros: referencia ao vetor do texto.
	Retorno: quantidade de caracteres que o texto possui
*/
int contaQtdDeCaractersDaString(char* texto){
	int i;
	int qtd = 0;

	for(i = 0; i < strlen(texto); i++){

		if(texto[i] != ' ' && texto[i] != '\n'){
			qtd++;	
		}
		
	}
	return qtd;
}

/*	Objetivo: Ler e validar um texto.
	Parâmetros: referencia ao vetor do texto, referencia ao vetor mensagem de titulo, valor maximo da string.
	Retorno:nenhum.
*/
void leValidaTexto (char *texto, char *mensagemTitulo, int tamanho,char *mensagemErro){
	do{
		printf("%s", mensagemTitulo);
		fflush(stdin);
		fgets(texto, tamanho, stdin);
		fflush(stdin);
		if(texto[strlen(texto)-1] == '\n'){
			texto[strlen(texto)-1] = '\0';
		}
		if(strlen(texto) == 0){
			system("cls");
			printf(mensagemErro);
			getch();
		}
	}while(strlen(texto) == 0);
}

/*	Objetivo: Juntar o nome do arquivo com a extencao
	Parâmetros: referencia ao vetor do nomeDoArquivo, referencia ao vetor extencao.
	Retorno:nome do arquivo com a extencao
*/
char* retornaNomeDoArquivoComAExencao(char* nomeDoArquivo, char* extencao,char* caracterAdd){
	int soma = 0;
	soma = strlen(nomeDoArquivo) + 1;//quantidade que possui no nomeDoArquivo + o ponto
	strncat(nomeDoArquivo,caracterAdd,soma);//nome do arquivo mais a extencao
	soma = 0;
	soma = strlen(nomeDoArquivo) + strlen(extencao);
	strncat(nomeDoArquivo,extencao,soma);
    return nomeDoArquivo;
}
/*	Objetivo: Mostrar Menu de fim
	Parâmetros: nenhum
	Retorno:nenhum
*/
void fim(){
	
	printf("\n\t _________________________Obrigada _________________________\n");

}
/*	Objetivo: Mostrar Menu
	Parâmetros: nenhum
	Retorno:nenhum
*/
void menu(){
	printf("\t\t ----------------- Bem Vindo -----------------\n");

}
/*
	Objetivo: Ler e validar um caracter
	Parametros; Endereço para mensagem titulo,Endereço para mensagem erro,Endereço do caracter e Endereço das opçoes
	Retorno;nenhum
*/
void lerValidaCaracter(char *msgTitulo,char *msgErro,char *caracter,char *opcoes)
{
	do
	{
		printf(msgTitulo);
		(*caracter) = toupper(getch());
		if(strchr(opcoes,*caracter) == 0)
		{
			printf(msgErro);
			getch();
			system("cls");
		}
	}while(strchr(opcoes,*caracter) == 0);
}

