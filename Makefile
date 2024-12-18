##############################################
###LIBS									######
##############################################

LIBFTDIR			=	libft
LIBFTINC			=	-I$(LIBFTDIR)/includes/
LIBFTLD				=	-L$(LIBFTDIR) -lft
LIBFT				=	$(LIBFTDIR)/libft.a

ARCH				:=	$(shell uname -m)
ifeq ($(ARCH), x86_64)
	READLINEDIR		=	readline
	READLINEINC		=	-I$(READLINEDIR)/
	READLINELD		=	-L$(READLINEDIR) -lreadline -lncurses -lhistory
else
	READLINEDIR		=	/opt/homebrew/Cellar/readline/8.2.13/lib/
	READLINEINC		=	-I/opt/homebrew/Cellar/readline/8.2.13/include/readline/
	READLINELD		=	 -L$(READLINEDIR) -lreadline -lncurses
endif


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
					msh/msh																\
					msh/history/msh_history_load										\
					msh/history/msh_history_save										\
					msh/input/msh_input_get												\
					msh/input/msh_input_process											\
					msh_signal/msh_signal_ctrl_c										\
					msh_signal/msh_signal_conf_term										\
					msh_perror/msh_perror												\
					msh_perror/msh_perror_int											\
					msh_perror/msh_perror_exit											\
					msh_perror/msh_perror_exit_int										\
					msh_env/msh_env_init												\
					msh_env/msh_env_getvar												\
					msh_env/msh_env_setvar												\
					msh_env/msh_env_delvar												\
					msh_env/msh_env_free_t_env											\
					msh_env/msh_env_free												\
					msh_env/msh_env_print												\
					msh_env/msh_env_check_restricted									\
					msh_tokenise/msh_tokenise											\
					msh_tokenise/msh_tokenise_create_token								\
					msh_tokenise/msh_tokenise_insert_token								\
					msh_tokenise/msh_tokenise_free										\
					msh_tokenise/msh_tokenise_get_next_token							\
					msh_tokenise/msh_tokenise_print_token_list							\
					msh_parse/msh_parse													\
					msh_parse/token/msh_parse_token										\
					msh_parse/token/msh_parse_token_word								\
					msh_parse/token/msh_parse_token_word_string							\
					msh_parse/token/msh_parse_token_operator							\
					msh_parse/ast/msh_parse_astnew										\
					msh_parse/ast/msh_parse_astadd_child								\
					msh_parse/ast/msh_parse_astprint									\
					msh_parse/ast/msh_parse_astfree										\
					msh_parse/expression/msh_parse_list									\
					msh_parse/expression/msh_parse_pipeline								\
					msh_parse/expression/msh_parse_grouping								\
					msh_parse/expression/msh_parse_cmd									\
					msh_parse/expression/msh_parse_cmd_argument							\
					msh_parse/expression/msh_parse_cmd_redirection						\
					msh_parse/expression/msh_parse_cmd_redirection_helper				\
					msh_parse/expression/msh_parse_cmd_redirection_helper_heredoc		\
					msh_expansion/msh_expansion_word									\
					msh_expansion/msh_expansion_dollar									\
					msh_expansion/msh_expansion_wildcards								\
					msh_expansion/msh_expansion_quotes									\
					msh_expansion/msh_expansion_utils_strappend							\
					msh_builtins/msh_builtins_func_cd									\
					msh_builtins/msh_builtins_func_echo									\
					msh_builtins/msh_builtins_func_env									\
					msh_builtins/msh_builtins_func_export								\
					msh_builtins/msh_builtins_func_pwd									\
					msh_builtins/msh_builtins_func_unset								\
					msh_builtins/msh_builtins_get_builtin								\
					msh_builtins/msh_builtins_exit										\
					msh_execute/msh_execute		 										\
					msh_execute/msh_execute_exit_status/msh_execute_exit_status_get		\
					msh_execute/msh_execute_exit_status/msh_execute_exit_status_ptr		\
					msh_execute/msh_execute_exit_status/msh_execute_exit_status_set		\
					msh_execute/msh_execute_simple_cmd									\
					msh_execute/msh_execute_simple_cmd_init								\
					msh_execute/msh_execute_simple_cmd_init_get_argv_arr				\
					msh_execute/msh_execute_simple_cmd_init_get_argv_arr_helper			\
					msh_execute/msh_execute_simple_cmd_redirs							\
					msh_execute/msh_execute_simple_cmd_redirs_process					\
					msh_execute/msh_execute_simple_cmd_redirs_restore					\
					msh_execute/msh_execute_simple_cmd_builtin							\
					msh_execute/msh_execute_simple_cmd_execute							\
					msh_execute/msh_execute_pipeline									\
					msh_execute/msh_execute_pipeline_pipe_fork							\
					msh_execute/msh_execute_pipeline_close								\
					msh_execute/msh_execute_list										\
					msh_execute/msh_execute_grouping									\
					msh_execute/msh_execute_wait_pid									\
					msh_execute/msh_execute_free										\
					msh_execute/msh_execute_free_exit									\
					msh_utils/msh_utils_strdup											\
					msh_utils/msh_utils_memalloc										\
					msh_utils/msh_utils_getcwd											\
					msh_utils/msh_utils_arraylen										\
					msh_utils/msh_utils_strrpad											\
					msh_utils/msh_utils_split											\


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
#FSANITIZE		=	-fsanitize=address
CFLAGS			:=	-Wall -Wextra -Werror$(if $(FSANITIZE), $(FSANITIZE))

ifeq ($(ARCH), x86_64)
	CFLAGS		+=	-DARCH_X86_64
endif


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

$(NAME): $(LIBFT) rl $(OBJDIRS) $(OBJS)
	$(CC) -g -v $(CFLAGS) $(IFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(LIBFT):
	$(MAKE_C) $(LIBFTDIR)

rl:
	(cd readline && ./configure)
	$(MAKE_C) readline

$(OBJDIRS):
	mkdir -p $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -g $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)
	$(RM) .DS_Store
	$(RM) .msh_history
	$(RM) out
	$(MAKE_C) $(LIBFTDIR) $@
	$(MAKE_C) readline $@

fclean: clean
	$(RM) $(NAME)
	$(MAKE_C) $(LIBFTDIR) $@
	$(MAKE_C) readline distclean

re: fclean rl all

.PHONY: all bonus rl clean fclean re
