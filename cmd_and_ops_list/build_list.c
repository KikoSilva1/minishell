#include "minishell.h"

//1- token WORD encontrada no inicio da list ou logo apos um operador e o nume de um comando, o que vem a seguir sao args ou redirecionamentos
//2- operadores separam comandos

create_node()
{

}
void	create_op_node(t_token **tmp_token, t_ast **last_node)
{
	t_ast *new_node  = create_node((*tmp_token) -> type, NULL);
	append_node(new_node,last_node);//listo estes dois nodes e atualizo last_node
	*tmp_token = (*tmp_token) -> next;
}
t_ast	*build_cmds_and_ops_list(t_token *head)
{
	int		in_operator;
	t_token	*tmp_token = head;
	t_ast	*first_node;
	t_ast	*last_node;

	in_operator = 0;
	t_ast	*first_node = NULL;
	t_ast	*last_node = NULL;
	while(tmp_token)
	{
		if(tmp_token == head || in_operator)//quando estou no inicio da lista ou o ultimo token era um operador
		{
			create_cmd_node(&tmp_token, &first_node, &last_node);//nestas funcoes atualizo o token que vou analizar a seguir (no caso de um comando passo a frente os tokens de args e redirects)
			in_operator = 0;
		}
		else if(tmp_token -> is_operator && tmp_token != head)//a minha lista nao pode comecar com um operador, poderar fazer essa validacao antes
		{
			create_op_node(&tmp_token, &last_node);
			in_operator = 1;
		}
	}
	return first_node;
}

