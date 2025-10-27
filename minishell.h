
#ifndef MINISHELL_H
#define MINISHELL_H
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int is_operator(char c);
int is_letter(char c);
int	is_quote(char c);
int is_single_quote(char c);
int	is_double_quote(char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int	is_space(char c);


#endif
