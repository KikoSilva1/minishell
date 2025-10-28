//Redirecionadores colados → cat<<EOF deve virar ["cat", "<<", "EOF"].
//
//Aspas → '...' é literal; "..." permite expansões; tudo dentro é um só token.
//
//Escape (\) → só funciona fora ou em certas aspas (não nas simples).
//
//Espaços → só separam tokens fora de aspas.
//
//Símbolos compostos → >>, <<, &&, || devem ser lidos como unidades únicas.
//
//Comentários (#) → ignorar o resto da linha se estiver fora de aspas.
//
//Concatenação implícita → "a"b'c' deve gerar um único token: abc.
//
//Subshells / parênteses → têm de ser reconhecidos como tokens próprios.
//Aspas simples '...' e duplas "..." formam um único token mesmo com espaços ou operadores,
//mas enquanto "..." permite expansão de variáveis e escapes, '...' é totalmente literal.

#include "minishell.h"

size_t	get_quoted_size(char *line, char quote)
{
	size_t size;

	size = 0;
	line++; //para passar a prmeira aspa a frente (so quero o conteudo)
	while(*line != quote && *line != '\0')
	{
		size++;
		line++;
	}
	if(*line == '\0')
		return (0);
	return(size);
}
t_token *create_token(char* value, t_token_type type, int is_expandable) //esta funcao precisa de receber o type do token e atualizar o guardalo.
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return NULL; // falha na alocação
	token ->type = type;
	token->value = value;
	token->expandable = is_expandable;
	token->next = NULL;
	return token;
}

char *get_quoted_text(char *line,char quote)
{
	size_t size;
	char *str;
	size = get_quoted_size(line,quote);//este size e' zero se a quote nao fechar ou se nao tiver nada dentro da quote
	str = malloc((size + 1)*sizeof(char));
	ft_memcpy(str, ++line, size); //ando line um char para a frente para nao copiar a aspa inicial
	str[size] = '\0';
	return str;
}

void	append_token(t_token **head, t_token **last_token, t_token *new_token)
{
	if (!new_token)
		return;

	if (*head == NULL) //sefor o primeiro node a ser criado, head aponta para ele
		*head = new_token;
	else
		(*last_token)->next = new_token;
	*last_token = new_token;
}
//Aspas simples '...' e duplas "..." formam um único token mesmo com espaços ou operadores,
//mas enquanto "..." permite expansão de variáveis e escapes, '...' é totalmente literal.
void	create_quoted_node(t_token **last_token, t_token **head, char *line, char quote)
{
	char	*str;
	t_token	*token;
	int is_expandable;

	is_expandable = 1;
	if(is_single_quote(*line))
		is_expandable = 0;

	str = get_quoted_text(line,quote);
	if(ft_strlen(str) < 1) //neste caso nao crio token,
		return;
	token = create_token(str, WORD, is_expandable);
	append_token(head,last_token,token);
}
// Not interpret unclosed quotes or special characters which are not required by the
//subject such as \ (backslash) or ; (semicolon)
void	handle_quote(char *line, int *i,t_token **last_node, t_token **head)
{
	create_quoted_node(last_node,head,line,*line);
	*i = *i + get_quoted_size(line,*line) + 2; //passar a frente o tento dentro das quotes e das prprias quotes
}

void	skip_spaces(char *line,int *i)
{
	int j;
	j = 0;
	while(is_space(line[j]))
		j++;
	*i = *i + j;
}

void	handle_word(char *line, int *i,t_token **last_token, t_token **head)
{
	int		j;
	t_token	*token;
	char	*str;

	j = 1; //vou para o char seguinte apos a letra que encontrei
	while(!is_operator(&line[j]) && !is_space(line[j]) && line[j] != '\0' && !is_quote(line[j]) && line[j] != '-' ) //validar a mudanca no is_operator, ver o que fazer se receber uma quote
	{
		j++;
	}
	//neste ponto line[j] e' um operador, espaco ou '\0'
	// com j tava deslocado, tamanhao a copiar da str e' j
	str = malloc((j + 1)*sizeof(char));
	ft_memcpy(str, line, j); //ando line um char para a frente para nao copiar a aspa inicial
	str[j] = '\0';
	token = create_token(str, WORD, 1);
	append_token(head,last_token,token);
	//atualizar i (posicao na line)
	*i = *i + j;
}

void	handle_pipe_or_or(char *line, int *i, t_token **last_token, t_token **head) //em todas estas funcoes de handle, seja o que receber aqui sei que e' um operador valido basta me saber qual
{
	t_token *token;
	char *str;

	if(*(++line) == '|')
	{
		str = ft_strdup("||");
		token = create_token(str, OR, 1);
		append_token(head,last_token,token);
		*i = *i + 2;
	}
	else
	{
		str = ft_strdup("|");
		token = create_token(str, PIPE, 1);
		append_token(head,last_token,token);
		*i = *i + 1;
	}
}
void	handle_and(char *line, int *i, t_token **last_token, t_token **head)
{
	t_token *token;
	char *str;

	if(*(++line) == '&') //esta verificacao pode ser redundante, confirmar
	{
		str = ft_strdup("&&"); //faco strdup porque ate agora todos os values dos tokens foram dinamicamente alocadas
		token = create_token(str, OR, 1);
		append_token(head,last_token,token);
		*i = *i + 2;
	}
}
void	handle_redin_or_heredoc(char *line, int *i, t_token **last_token, t_token **head)
{
	t_token *token;
	char *str;
	if (*(++line) == '<')
	{
		str = ft_strdup("<<"); //faco strdup porque ate agora todos os values dos tokens foram dinamicamente alocadas
		token = create_token(str, HEREDOC, 1);
		append_token(head,last_token,token);
		*i = *i + 2;
	}
	else
	{
		str = ft_strdup("<");
		token = create_token(str, REDIR_IN, 1);
		append_token(head,last_token,token);
		*i = *i + 1;
	}
}

void	handle_redap_or_redout(char *line, int *i, t_token **last_token, t_token **head)
{
	t_token *token;
	char *str;

	if(*(++line) == '>')
	{
		str = ft_strdup(">>");
		token = create_token(str, APPEND, 1);
		append_token(head,last_token,token);
		*i = *i + 2;
	}
	else
	{
		str = ft_strdup(">");
		token = create_token(str, REDIR_OUT, 1);
		append_token(head,last_token,token);
		*i = *i + 1;
	}
}

void handle_operator(char *line, int *i, t_token **last_token, t_token **head)
{
	if (*line == '|')
		handle_pipe_or_or(line,i,last_token,head);  // função que vai criar token PIPE ou OR (||)
	else if (*line == '&')
		handle_and(line, i,last_token,head);         // função que cria token AND (&&)
	else if (*line == '<')
		handle_redin_or_heredoc(line,i,last_token,head);       // função que cria token REDIR_INPUT (<) ou ou HEREDOC (<<)
	else if (*line == '>')
		handle_redap_or_redout(line,i,last_token,head); // função que cria token REDIR_OUTPUT (>) ou REDIR_APPEND (>>)
}

//por agora o trata espacos e aspas;
t_token	*tokenize(char* line)
{
	int	i;
	t_token *last_token;
	t_token *head;

	last_token = NULL;
	head = NULL;
 	i = 0;
	//convem manter esta hierarquia de operacoes exemplo  grep &ola ,quero tratar &ola como palavra e nao separar em tokens
	while(line[i] != 0)
	{
		if(is_space(line[i]))
			skip_spaces(&line[i], &i);
		else if(is_quote(line[i]))
			handle_quote(&line[i],&i, &last_token, &head);
		else if(is_operator(&line[i]))
			handle_operator(&line[i],&i, &last_token, &head);
		else
			handle_word(&line[i],&i, &last_token, &head);
	}
	return (head);
}
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
	char	*prompt;

	prompt = malloc(sizeof(MAXPATHLEN));
	getcwd(prompt, MAXPATHLEN);
	while (1)
	{
		line = readline(prompt);
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
		check_builtins(head);
		getcwd(prompt, MAXPATHLEN);
		free_tokens(head);
		free(line);
	}
	return exit_status;
}


