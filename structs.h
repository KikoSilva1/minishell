#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum e_token_type
{
	WORD,        // texto normal: comando, argumento, nome de arquivo
	PIPE,        // |
	REDIR_IN,    // <
	REDIR_OUT,   // >
	APPEND,      // >>
	HEREDOC,      // <<
	OR,
	AND,
}	t_token_type;

typedef struct s_token
{
	int	expandable; //0 - does not expand ,1 - expands
	char            *value;   // conteúdo do token ("cat", ">", etc.)
	t_token_type    type;     // tipo (WORD, PIPE, etc.)
	struct s_token  *next;    // próximo token
}	t_token;

#endif

