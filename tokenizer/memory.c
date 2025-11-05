
#include "minishell.h"

void	free_tokens(t_token *head)
{
	t_token *tmp;
	t_token *next_token;
	tmp = head;
	while(tmp)
	{
		next_token = tmp->next;
		free(tmp -> value);
		free(tmp);
		tmp = next_token;
	}
}
