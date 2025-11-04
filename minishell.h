
#ifndef MINISHELL_H
#define MINISHELL_H


#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>

# include <unistd.h>

int is_operator(char *line);
int is_letter(char c);
int	is_quote(char c);
int is_single_quote(char c);
int	is_double_quote(char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s1);
int	is_space(char c);
void handle_pipe_or_or(char *line, int *i, t_token **last_token, t_token **head);  // função que vai criar token PIPE ou OR (||)
void handle_and(char *line, int *i, t_token **last_token, t_token **head);         // função que cria token AND (&&)
void handle_redin(char *line, int *i, t_token **last_token, t_token **head);       // função que cria token REDIR_INPUT
void handle_redap_or_redout(char *line, int *i, t_token **last_token, t_token **head); // função que cria token REDIR_OUTPUT (>) ou REDIR_APPEND (>>)
size_t	ft_strlen(const char *s);


#endif
