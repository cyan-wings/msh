##############################################
###LIBS									######
##############################################

LIBFTDIR		=	libft
LIBFTINC		=	-I$(LIBFTDIR)/includes/
LIBFTLD			=	-L$(LIBFTDIR) -lft
LIBFT			=	$(LIBFTDIR)/libft.a

READLINEDIR		=	readline
READLINEINC		=	-I$(READLINEDIR)/
READLINELD		=	-L$(READLINEDIR) -lreadline -lncurses -lhistory


##############################################
###HEADERS								######
##############################################

HDRDIR			=	includes/
HDRINC			=	-I$(HDRDIR)


##############################################
###SRCS									######
##############################################

SRCDIR			=	srcs/
SRC_M			=	\
					msh/msh													\
					msh/history/msh_history_load							\
					msh/history/msh_history_save							\
					msh/input/msh_input_get									\
					msh/input/msh_input_process								\
					msh_perror/msh_perror									\
					msh_perror/msh_perror_exit								\
					msh_env/msh_env_init									\
					msh_env/msh_env_getvar									\
					msh_env/msh_env_setvar									\
					msh_env/msh_env_delvar									\
					msh_env/msh_env_free_t_env								\
					msh_env/msh_env_free									\
					msh_env/msh_env_print									\
					msh_tokenise/msh_tokenise								\
					msh_tokenise/msh_tokenise_create_token					\
					msh_tokenise/msh_tokenise_insert_token					\
					msh_tokenise/msh_tokenise_free							\
					msh_tokenise/msh_tokenise_get_next_token				\
					msh_tokenise/msh_tokenise_print_token_list				\
					msh_parse/msh_parse										\
					msh_parse/token/msh_parse_token							\
					msh_parse/token/msh_parse_token_word					\
					msh_parse/token/msh_parse_token_word_string				\
					msh_parse/token/msh_parse_token_operator				\
					msh_parse/ast/msh_parse_astnew							\
					msh_parse/ast/msh_parse_astadd_child					\
					msh_parse/ast/msh_parse_astprint						\
					msh_parse/ast/msh_parse_astfree							\
					msh_parse/expression/msh_parse_list						\
					msh_parse/expression/msh_parse_pipeline					\
					msh_parse/expression/msh_parse_grouping					\
					msh_parse/expression/cmd/msh_parse_cmd					\
					msh_parse/expression/cmd/msh_parse_cmd_arguments		\
					msh_parse/expression/cmd/msh_parse_cmd_redirections		\
					msh_expansion/msh_expansion								\
					msh_expansion/msh_expansion_dollar						\
					msh_expansion/msh_expansion_wildcards_and_quotes		\
					msh_expansion/msh_expansion_quotes						\
					msh_expansion/utils/msh_expansion_utils_strappend		\
					msh_builtins/msh_builtins_func_cd						\
					msh_builtins/msh_builtins_func_echo						\
					msh_builtins/msh_builtins_func_env						\
					msh_builtins/msh_builtins_func_exit						\
					msh_builtins/msh_builtins_func_export					\
					msh_builtins/msh_builtins_func_pwd						\
					msh_builtins/msh_builtins_func_unset					\
					msh_builtins/msh_builtins_get_builtin					\
					msh_execute/msh_execute		 							\
					msh_execute/msh_execute_util_dup2						\
					msh_execute/msh_execute_simple_cmd_get_envp_arr			\
					msh_execute/msh_execute_simple_cmd_redirs				\
					msh_execute/msh_execute_simple_cmd						\
					msh_execute/msh_execute_pipeline						\
					msh_execute/msh_execute_grouping						\
					utils/ft_arraylen										\


SRCS			=	$(addsuffix .c, $(addprefix $(SRCDIR), $(SRC_M) ))


##############################################
###OBJS									######
##############################################

OBJDIR			=	objs/
OBJS			=	$(subst $(SRCDIR), $(OBJDIR), $(subst .c,.o,$(SRCS)))
OBJDIRS			=	$(sort $(dir $(OBJS)))


##############################################
###FLAGS								######
##############################################

NAME			=	msh
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror$(if $(FSANITIZE), $(FSANITIZE))
FSANITIZE		=	-fsanitize=address -g

IFLAGS			=	$(READLINEINC) $(LIBFTINC) $(HDRINC)
LFLAGS			=	$(READLINELD) $(LIBFTLD)

RM				=	rm -rf
MAKE			=	make
MAKE_C			=	$(MAKE) -C

UP				=	\033[1A
FLUSH			=	\033[2K




##############################################
###RULES								######
##############################################

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(LIBFT):
	$(MAKE_C) $(LIBFTDIR)

$(OBJDIRS):
	mkdir -p $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)
	$(RM) .DS_Store
	$(RM) .msh_history
	$(RM) out
	$(MAKE_C) $(LIBFTDIR) $@

fclean: clean
	$(RM) $(NAME)
	$(MAKE_C) $(LIBFTDIR) $@

re: fclean all

.PHONY: all bonus clean fclean re
