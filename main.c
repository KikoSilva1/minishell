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
	if (type == RPAREN)
		return "RPAREN";
	if (type == LPAREN)
		return "LPAREN";
	return "UNKNOWN";
}


int	main(void)
{

	char *line;
	t_token *head;
	t_token *tmp;
	//t_ast *first_node;
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
			printf("Token: \"%s\"| type: %s | Expandable: %d | is operator: %d \n", tmp->value,  token_type_to_str(tmp->type), tmp ->expandable, tmp->is_operator);
			tmp = tmp->next;
		}
		//first_node = build_cmss_and_ops_list(head);
		free_tokens(head);
		free(line);
	}
	return exit_status;
}
