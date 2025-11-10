/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_node_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framiran <framiran@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:07:19 by framiran          #+#    #+#             */
/*   Updated: 2025/11/10 16:19:50 by framiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// possible redirect types: < ,> ,>>, <<
int	is_redirect_token(t_token *tmp_token)
{
	if(ft_strncmp(tmp_token -> value, ">>", 2) == 0)
		return 1;
	if(ft_strncmp(tmp_token -> value, "<<", 2) == 0)
		return 1;
	if(ft_strncmp(tmp_token -> value, ">", 1) == 0)
		return 1;
	if(ft_strncmp(tmp_token -> value, "<", 1) == 0)
		return 1;
	return 0;
}

int	calculate_numb_of_args(t_token *tmp_token)//o primeiro token 'e sempre o node do comando, mas entra na lista de args porque o execve precisa dele na lista de args que recebe por param;
{//nesta funcao altero a copia do ponteiro tmp_token entao na funcao create_cmd esta mudanca nao se vai refletir
	int count;

	count = 0;
	while(tmp_token && tmp_token->is_operator == 0)//aqui vou guardar os args e os redirects;
	{
		if(is_redirect_token(tmp_token))//se encontrar um token de redirect passo dois tokens a frente (o de redirect e o filename)
		{
			tmp_token = tmp_token -> next;
			tmp_token = tmp_token -> next;
		}
		else
		{
			count++;
			tmp_token = tmp_token -> next;
		}
	}
	return count;
}

void	update_token_to_eval(t_token **tmp_token) //esta funcao e chamada para atualizar o token a avaliar depois de criar um node comando (tenho de saltar redirects e argumantos a frente)
{
	while((*tmp_token))
	{
		if((*tmp_token) ->is_operator) //se emcontrar um operador atualiza tmp_token para a posicao desse operador
			return;
		*tmp_token = (*tmp_token) -> next;
	}
	//se sair aqui, nao encontrou nenhum operador antes do fim entao acabou a construcao da lista (tmp_token = NULL)
}



