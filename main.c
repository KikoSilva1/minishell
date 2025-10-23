typedef enum e_token_type
{
	WORD,        // texto normal: comando, argumento, nome de arquivo
	PIPE,        // |
	REDIR_IN,    // <
	REDIR_OUT,   // >
	APPEND,      // >>
	HEREDOC      // <<
}	t_token_type;

typedef struct s_token
{
	char            *value;   // conteúdo do token ("cat", ">", etc.)
	t_token_type    type;     // tipo (WORD, PIPE, etc.)
	struct s_token  *next;    // próximo token
}	t_token;

//----------------------------------------------------------------TOKENIZER-----------------------------------------------------

//read_input()
//→ Lê a linha do utilizador com readline().
//skip_spaces()
//→ Avança pelos espaços até encontrar o próximo caractere útil.
//is_operator()
//→ Verifica se o caractere atual é |, <, >, ou parte de << / >>.
//handle_operator()
//→ Cria um token de operador (pipe, redir_in, redir_out, append, heredoc).
//handle_word()
//→ Lê uma palavra normal até encontrar espaço ou operador.
//handle_quotes()
//→ Trata texto entre ' ' ou " ", respeitando o tipo de aspa.
//create_token()
//→ Cria um novo token com o valor e o tipo identificados.
//add_token_to_list()
//→ Adiciona o token criado à lista ligada de tokens.
//check_unclosed_quotes()
//→ Verifica se há aspas não fechadas (erro de sintaxe).
//tokenize()
//→ Função principal: percorre a linha, chama as funções acima e devolve a lista de tokens.

//----------------------------------------------------------------------EXPANCAO DE VARIAVEIS--------------------------------------------

//expand_variables()
//→ Função principal: percorre todos os tokens e expande $VAR, $?, etc., quando permitido.
//should_expand()
//→ Verifica se o token pode ser expandido (não dentro de aspas simples, sim em aspas duplas ou fora delas).
//find_variable_name()
//→ Lê o nome da variável logo após o $.
//get_env_value()
//→ Procura o valor da variável no ambiente (envp ou lista interna).
//replace_variable()
//→ Substitui $VAR pelo valor correspondente no token.
//expand_exit_status()
//→ Substitui $? pelo valor do último código de saída.
//handle_quotes_after_expansion()
//→ Ajusta o token se as aspas influenciam o resultado final (ex: remover aspas se necessário).
//expand_in_heredoc()
//→ Só expande se o delimitador não estiver entre aspas.
//update_token_value()
//→ Atualiza o value do token com o texto expandido.
//remove_empty_tokens()
//→ Remove tokens que ficaram vazios após a expansão (ex: $VAR que não existia).


//----------------------------------------------------------------------CONSTRUIR AST(ARVORE BINARIA)--------------------------------------------
