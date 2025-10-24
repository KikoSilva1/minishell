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

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


//Aspas simples '...' e duplas "..." formam um único token mesmo com espaços ou operadores,
//mas enquanto "..." permite expansão de variáveis e escapes, '...' é totalmente literal.
int	is_quote(char c)
{
	return(c == '\"' || c == '\'');
}
int is_single_quote(char c)
{
	return(c == '\'');
}
int	is_double_quote(char c)
{
	return(c == '\"');
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	dst_cpy = (unsigned char *) dst;
	src_cpy = (unsigned char *) src;
	if (dst == (void *) 0 && src == (void *) 0)
		return (dst);
	while (n--)
		*(dst_cpy++) = *(src_cpy++);
	return (dst);
}

size_t	get_quoted_size(char *line, char quote)
{
	size_t size;

	size = 0;
	line++; //para passar a prmeira aspa a frente (so quero o conteudo)
	while(*line != quote)
	{
		size++;
		line++;
	}
	return(size);
}
t_token *create_token(char* value,int is_expandable)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return NULL; // falha na alocação
	token->value = value;
	token->expandable = is_expandable;
	token->next = NULL;
	return token;
}

char *get_quoted_text(char *line,char quote)
{
	size_t size;
	char *str;
	size = get_quoted_size(line,quote);//validar este size primeiro, pode ser 0 e assim n faco nada
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
	token = create_token(str, is_expandable);
	append_token(head,last_token,token);
}

void	handle_quote(int *in_quote,char *line, int *i,t_token **last_node, t_token **head)
{
	//em principio vou poder remover estes ifs
	if(is_single_quote(*line))
		*in_quote = 1;
	if(is_double_quote(*line))
		*in_quote = 2;
	create_quoted_node(last_node,head,line,*line);
	*i = *i + get_quoted_size(line,*line) + 2; //passar a frente o tento dentro das quotes e das prprias quotes
 }
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}
void	skip_spaces(char *line,int *i)
{
	int j;
	j = 0;
	while(is_space(line[j]))
		j++;
	*i = *i + j;
}
//por agora o trata espacos e aspas;
t_token	*tokenize(char* line)
{
	int	i;
	int in_quote; //1 in (') 2 in (")
	t_token *last_token;
	t_token *head;

	last_token = NULL;
	head = NULL;
 	i = 0;


	while(line[i] != 0)
	{
		if(is_space(line[i]))
			skip_spaces(&line[i], &i);
		else if(is_quote(line[i]))
			handle_quote(&in_quote,&line[i],&i, &last_token, &head);
		//else if(is_operator(line[i]))
		//	handle_operator(line[i],&i, &last_token, &head);
		//else if(is_letter())
		//	handle_word(line[i],&i, &last_token, &head);
	}
	return (head);
}

int	main(void)
{
	char *line;
	t_token *head;
	t_token *tmp;
	int exit_status = 0;
	while (1)
	{
		line = readline("minishell> ");
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
			printf("Token: \"%s\" | Expandable: %d\n", tmp->value, tmp ->expandable);
			tmp = tmp->next;
		}
		//free_tokens(tokens);
		free(line);
	}
	return exit_status;
}




