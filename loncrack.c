#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SALT_BUFF 32 // Máximo valor do salt ~16
#define HASH_BUFF 128 // Máximo valor do hash ~105

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Modo de Uso: %s wordlist\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE *arq = fopen(argv[1],"r");

	// verificando se o fopen funcionou corretamente
	if (!arq) {
		fprintf(stderr, "O arquivo não existe.\n");
		return EXIT_FAILURE;
	}

	// declarando as variáveis - vetoresa
	int i = 0, j = 0, flag = 0;
	char *senha = NULL;
	char salt[SALT_BUFF] = { 0 };
	char hash[HASH_BUFF] = { 0 };
	char *result = NULL;
	size_t n = 0;

	// o hash vai ser armazenado na variável hash
	printf("Digite o Hash completo:\n");
	scanf("%s", hash);

	// armazenando o salt
	while (j < 3) {
		salt[i] = hash[i];

		if (salt[i] == '$') { ++j; }

		++i;

		// Evitar segmentation fault caso não encontre 3 '$'
		if (i == HASH_BUFF) {
			fprintf(stderr, "Formato do hash incorreto.\n");
			return EXIT_FAILURE;
		}
	}

	printf("Testando..\n");

	while (getline(&senha, &n, arq) > 0) {
		senha[strlen(senha) - 1] = 0; // eliminar o \n
		result = (char *) crypt(senha, salt);
		if (strcmp(hash, result) == 0) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		printf("Senha não encontrada..\n");
	} else {
		printf("Senha encontrada: %s \n", senha);
	}

	free(senha);
	fclose(arq);

	return 0;
}