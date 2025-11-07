#include "minishell.h"

//1- token WORD encontrada no inicio da list ou logo apos um operador e o nume de um comando, o que vem a seguir sao args ou redirecionamentos
//2- operadores separam comandos

void	append_node(t_ast *new_node,t_ast *last_node)
{
	last_node -> right = new_node;
	new_node -> left = last_node;
}
t_ast	*create_node(t_token *token, t_cmd* cmd)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if(cmd == NULL) //neste caso vou criar um node operador
	{
		new_node -> cmd == NULL;
		new_node -> type = token ->type;
	}
	else //estou num comando
	{
		new_node -> cmd == cmd;
		new_node -> type = CMD;
	}
	return (new_node);
}

void	update_token_to_eval(t_token **tmp_token)
{
	while((*tmp_token))
	{
		if((*tmp_token) ->is_operator) //se emcontrar um operador atualiza tmp_token para a posisao desse operador
			return;
		*tmp_token = (*tmp_token) -> next;
	}
	//se sair aqui, nao encontrou nenhum operador antes do fim entao acabou a construcao da lista (tmp_token = NULL)
}
int	is_redirect_token(t_token *tmp_token)
{
	if(tmp_token -> value)
}
t_cmd	*create_cmd(t_token *tmp_token)
{
	t_cmd	*cmd;
	char	**args;
	int		i;
	int		j;


	cmd = malloc(sizeof(t_cmd));
	cmd ->cmd_name = tmp_token ->value; //o cmd name e sempre o primeiro token
	tmp_token = tmp_token ->next;
	while(tmp_token && tmp_token->is_operator == 0)//aqui vou guardar os args e os redirects;
	{
		if(is_redirect_token(tmp_token))//se encontrar um token de redirect
			handle_redirect_token(cmd);//vou adicionar a redirecao encontrada a lista de redirecoes
		else // e um argumento
			handle_arg_token(cmd);//guardo esse argumento na lista de argumentos
		tmp_token = tmp_token -> next;
	}
	//chegamos ao fim dos tokens ou a um operador, retorno o comando criado
	return cmd;
}
void	create_cmd_node(t_token **tmp_token,t_token *head, t_ast **first_node, t_ast **last_node) // o inicio da node list sera sempre o primeiro comando que recebe, tenho que atualizar este pointer apenas uma vez quando encontro o primeiro comando(primeiro token)
{
	t_cmd *cmd;
	t_ast *new_node;

	cmd = create_cmd(*tmp_token);
	new_node  = create_node(*tmp_token, cmd);
	if(*tmp_token == head) // no caso de ser o primeiro node:
		*first_node = new_node;
	append_node(new_node,*last_node);//ligo estes dois nodes e atualizo last_node
	*last_node = new_node; // agora last_node aponta para o novo node que foi adicionado ao fim da lista
	update_token_to_eval(tmp_token); //atualizar o proximo token a avaliar, (tenho de passar todos os tokens que pertencem a este CMD)
}
void	create_op_node(t_token **tmp_token, t_ast **last_node)//
{
	t_ast *new_node;

	new_node  = create_node(*tmp_token, NULL);
	append_node(new_node,*last_node);//listo estes dois nodes e atualizo last_node
	(*last_node) = new_node; // agora last_node aponta para o novo node que foi adicionado ao fim da lista
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
			create_cmd_node(&tmp_token, head, &first_node, &last_node);//nestas funcoes atualizo o token que vou analizar a seguir (no caso de um comando passo a frente os tokens de args e redirects)
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

