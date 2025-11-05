
#ifndef MINISHELL_H
#define MINISHELL_H


#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>

# include <unistd.h>



//----------------------------------------------------TOKENIZER-----------------------------------------------------------------------------

/* ---------------- Funções auxiliares ---------------- */
int     is_space(char c);
int     is_quote(char c);
int     is_single_quote(char c);
int     is_double_quote(char c);
int     is_operator(char *line);

/* ---------------- Funções de criação e manipulação de tokens ---------------- */
t_token *create_token(char *value, t_token_type type, int is_expandable);
void    append_token(t_token **head, t_token **last_token, t_token *new_token);

/* ---------------- Funções para lidar com aspas ---------------- */
size_t  get_quoted_size(char *line, char quote);
char    *get_quoted_text(char *line, char quote);
void    create_quoted_node(t_token **last_token, t_token **head, char *line, char quote);

/* ---------------- Funções para operadores ---------------- */
void    handle_pipe_or_or(char *line, int *i, t_token **last_token, t_token **head);
void    handle_and(char *line, int *i, t_token **last_token, t_token **head);
void    handle_redap_or_redout(char *line, int *i, t_token **last_token, t_token **head);
void    handle_redin_or_heredoc(char *line, int *i, t_token **last_token, t_token **head);

/* ---------------- Funções principais ---------------- */
void    handle_quote(char *line, int *i, t_token **last_token, t_token **head);
void    handle_word(char *line, int *i, t_token **last_token, t_token **head);
void    handle_operator(char *line, int *i, t_token **last_token, t_token **head);
void    skip_spaces(char *line, int *i);
t_token *tokenize(char *line);

/* ---------------- Funções de Memoria---------------- */
void	free_tokens(t_token *head);
//--------------------------------------------------------------------------------------------------------------------------------

#endif
