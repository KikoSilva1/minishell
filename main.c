#include "minishell.h"

const char *token_type_to_str(t_token_type type)
{
	if (type == WORD)
		return "WORD";
	if (type == REDIR_IN)
		return "REDIR_IN";
	if (type == REDIR_OUT)
		return "REDIR_OUT";
	if (type == APPEND)
		return "APPEND";
	if (type == HEREDOC)
		return "HEREDOC";
	if (type == PIPE)
		return "PIPE";
	if (type == OR)
		return "OR";
	if (type == AND)
		return "AND";
	return "UNKNOWN";
}


int	main(void)
{
	char *line;
	t_token *head;
	t_token *tmp;
	int exit_status = 0;
	while (1)
	{
		line = readline("minishell$>");
		//add_history(line);
		head = tokenize(line);
		if (!head)
		{
			fprintf(stderr, "Erro ao tokenizar.\n");
			free(line);
			continue;
		}
		tmp = head;
		while(tmp)
		{
			printf("Token: \"%s\"| type: %s | Expandable: %d\n", tmp->value,  token_type_to_str(tmp->type), tmp ->expandable);
			tmp = tmp->next;
		}
		free_tokens(head);
		free(line);
	}
	return exit_status;
}
