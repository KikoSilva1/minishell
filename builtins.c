#include "minishell.h"

int ft_strcmp(char *input, char *check)
{
	int	i;

	i = 0;
	if (!input || !check || !*input || !*check)
		return (0);
	while (input[i] && check[i] && input[i] == check[i])
		++i;
	if (!check[i])
		return (1);
	return (0);
}

int	check_builtins(t_token *tokens)
{
	if (ft_strcmp(tokens->value, "cd"))
		if (chdir(tokens->next->value) == -1)
			return (0);
	return (1);
}

