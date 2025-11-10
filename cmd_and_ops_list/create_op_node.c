/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_op_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framiran <framiran@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:07:40 by framiran          #+#    #+#             */
/*   Updated: 2025/11/10 16:21:18 by framiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_op_node(t_token **tmp_token, t_ast **last_node)
{
	t_ast *new_node;

	new_node  = create_node(*tmp_token, NULL);
	append_node(new_node,*last_node);//listo estes dois nodes e atualizo last_node
	(*last_node) = new_node; // agora last_node aponta para o novo node que foi adicionado ao fim da lista
	*tmp_token = (*tmp_token) -> next;
}
