#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *arq;
	arq = fopen(argv[1],"r");

	char senha[75];
	char salt[25];
	char comp[100];
	char *result;

	printf("Digite o Hash completo\n");
	scanf("%s", comp);

	printf("Digite o Salt\n");
	scanf("%s",salt);
	
	int f = 0;

	while(fscanf(arq, "%s", &senha) != EOF)
	{
	result = (char *) crypt(senha, salt);
		if (strcmp(comp,result)==0){
		printf("Senha encontrada: %s \n", senha);
		int f = 1;
		return(0);
		}else{
		printf("Testando.. %s \n", senha);
		}
	}if(f==0){
	printf("Senha não encontrada..\n");
	}
}
