##############################################
###LIBS									######
##############################################

LIBFTDIR		=	libft
LIBFTINC		=	-I$(LIBFTDIR)/includes/
LIBFTLD			=	-L$(LIBFTDIR) -lft
LIBFT			=	$(LIBFTDIR)/libft.a

# READLINEDIR		=	readline
READLINEDIR		=	/opt/homebrew/Cellar/readline/8.2.13/lib/
READLINEIDIR		=	/opt/homebrew/Cellar/readline/8.2.13/include/readline
READLINEINC		=	-I$(READLINEIDIR)/
# READLINELD		=	-L$(READLINEDIR) -lreadline -lncurses -lhistory
READLINELD		=	 -L$(READLINEDIR) -lreadline -lncurses 
# READLINELD		=	-lreadline -lncurses 


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
					debug/msh_print_token_list								\
					utils/ft_arraylen										\
					utils/ft_get_arr										\
					error_handling/msh_perror_exit							\
					error_handling/msh_perror								\
					msh_env/msh_env_init									\
					msh_env/msh_env_getvar									\
					msh_env/msh_env_setvar									\
					msh_env/msh_env_free									\
					msh_env/msh_env_getenvarray								\
					msh_expansion/utils/msh_expansion_utils_strappend		\
					msh_expansion/msh_expansion_wildcards_and_quotes		\
					msh_expansion/msh_expansion_quotes						\
					msh_expansion/msh_expansion_dollar						\
					msh_expansion/msh_expansion								\
					msh_history/msh_load_history							\
					msh_history/msh_save_history							\
					msh_tokenise/msh_tokenise								\
					msh_tokenise/msh_tokenise_create_token					\
					msh_tokenise/msh_tokenise_insert_token					\
					msh_tokenise/msh_tokenise_free							\
					msh_tokenise/msh_tokenise_get_next_token				\
					msh_parse/expression/msh_parse_grouping					\
					msh_parse/expression/msh_parse_list						\
					msh_parse/expression/msh_parse_pipeline					\
					msh_parse/expression/cmd/msh_parse_cmd					\
					msh_parse/expression/cmd/msh_parse_cmd_arguments		\
					msh_parse/expression/cmd/msh_parse_cmd_redirections		\
					msh_parse/token/msh_parse_word_string					\
					msh_parse/token/msh_parse_word							\
					msh_parse/token/msh_parse_operator						\
					msh_parse/token/msh_parse_token							\
					msh_parse/ast/msh_parse_astnew							\
					msh_parse/ast/msh_parse_astadd_child					\
					msh_parse/ast/msh_parse_astprint						\
					msh_parse/ast/msh_parse_astfree							\
					msh_parse/msh_parse										\
					msh_traversal/msh_traversal 							\
					msh_traversal/msh_pipe      							\
					msh_traversal/msh_execution_utils     					\
					msh_signals/msh_signals									\
					msh/msh_prompt											\
					msh/msh


# msh_traversal/msh_traversal								\

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
