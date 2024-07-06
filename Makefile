##############################################
###LIBS									######
##############################################

LIBFTDIR		=	libft
LIBFTINC		=	-I$(LIBFTDIR)/includes/
LIBFTLD			=	-L$(LIBFTDIR) -lft
LIBFT			=	$(LIBFTDIR)/libft.a

READLINEDIR		=	readline
READLINEINC		=	-I$(READLINEDIR)
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
					debug/minishell_print_token_list									\
					utils/ft_arraylen													\
					error_handling/minishell_perror_exit								\
					error_handling/minishell_perror										\
					minishell_env/minishell_env_init									\
					minishell_env/minishell_env_getvar									\
					minishell_env/minishell_env_setvar									\
					minishell_env/minishell_env_free									\
					minishell_history/minishell_load_history							\
					minishell_history/minishell_save_history							\
					minishell_tokenise/minishell_tokenise								\
					minishell_tokenise/minishell_tokenise_create_token					\
					minishell_tokenise/minishell_tokenise_insert_token					\
					minishell_tokenise/minishell_tokenise_free							\
					minishell_tokenise/minishell_tokenise_get_next_token				\
					minishell_parse/expression/minishell_parse_grouping					\
					minishell_parse/expression/minishell_parse_list						\
					minishell_parse/expression/minishell_parse_pipeline					\
					minishell_parse/expression/cmd/minishell_parse_cmd					\
					minishell_parse/expression/cmd/minishell_parse_cmd_arguments		\
					minishell_parse/expression/cmd/minishell_parse_cmd_redirections		\
					minishell_parse/token/minishell_parse_word_string					\
					minishelL_parse/token/minishell_parse_word							\
					minishell_parse/token/minishell_parse_operator						\
					minishell_parse/token/minishell_parse_token							\
					minishell_parse/ast/minishell_parse_astnew							\
					minishell_parse/ast/minishell_parse_astadd_child					\
					minishell_parse/ast/minishell_parse_astprint						\
					minishell_parse/ast/minishell_parse_astfree							\
					minishell_parse/minishell_parse										\
					minishell/minishell_prompt											\
					minishell/minishell													\

SRCS			=	$(addsuffix .c, $(addprefix $(SRCDIR), $(SRC_M)))


##############################################
###OBJS									######
##############################################

OBJDIR			=	objs/
OBJS			=	$(subst $(SRCDIR), $(OBJDIR), $(subst .c,.o,$(SRCS)))
OBJDIRS			=	$(sort $(dir $(OBJS)))


##############################################
###FLAGS								######
##############################################

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror$(if $(FSANITIZE), $(FSANITIZE))
#FSANITIZE		=	-fsanitize=address -g

IFLAGS			=	$(HDRINC) $(LIBFTINC) $(READLINEINC)
LFLAGS			=	$(LIBFTLD) $(READLINELD)

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
	$(RM) .minishell_history
	$(MAKE_C) $(LIBFTDIR) $@

fclean: clean
	$(RM) $(NAME)
	$(MAKE_C) $(LIBFTDIR) $@

re: fclean all

.PHONY: all bonus clean fclean re
