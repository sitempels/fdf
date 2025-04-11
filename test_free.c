#include <unistd.h>
#include <stdlib.h>

void	fcttest(char **test);

int	main()
{
	char **test;

	test = (char **) malloc(sizeof(char) * 3);
	test[0] = (char *) malloc(sizeof(char) * 3);
	test[1] = (char *) malloc(sizeof(char) * 3);
	fcttest(&test[0]);
	return (0);
}

void	fcttest(char **test)
{
	free(test[0]);
	test[0] = NULL;
}
