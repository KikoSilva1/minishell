#include "minishell.h"

int is_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}
int is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
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

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}
