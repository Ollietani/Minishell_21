S_DIR = ./srcs

INCL = ./includes

BLD_IN = $(S_DIR)/build_ins

EXEC = $(S_DIR)/execute

PARS = $(S_DIR)/parsing

PRE_EXEC = $(S_DIR)/pre_executing

SIGN = $(S_DIR)/signals

UTILIS = $(S_DIR)/utilis

####           		SRCS                    ####

SRCS =	main.c\
		$(PARS)/parsing_start.c				$(PARS)/parsing.c\
		$(PARS)/parsing2.c					$(PARS)/parsing3.c\
		$(PARS)/parsing4.c					$(PARS)/parsing5.c\
		$(PARS)/parsing6.c\
		$(PRE_EXEC)/lists_for_new_struct.c 	$(PRE_EXEC)/made_redirects_data.c\
		$(PRE_EXEC)/heredoc.c				$(PRE_EXEC)/utilis_for_redirects.c\
		$(PRE_EXEC)/heredoc2.c				$(PRE_EXEC)/for_new_struct.c\
		$(PRE_EXEC)/made_new_struct.c		$(PRE_EXEC)/for_redirects.c\
		$(EXEC)/error.c						$(EXEC)/fill_list.c\
		$(EXEC)/parse_cmdstr.c				$(EXEC)/pipex.c\
		$(EXEC)/pipex_1.c					$(EXEC)/pipex_2.c\
		$(BLD_IN)/build_in.c				$(BLD_IN)/cd.c\
		$(BLD_IN)/echo.c					$(BLD_IN)/export.c\
		$(BLD_IN)/exit.c					$(BLD_IN)/unset.c\
		$(BLD_IN)/env.c						$(BLD_IN)/pwd.c\
		$(SIGN)/signals.c					$(SIGN)/signals2.c\
		$(UTILIS)/utilis.c					$(UTILIS)/utilis2.c\
		$(UTILIS)/free_data.c				$(UTILIS)/lists_env.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

CFLAGS = -g -Wall -Wextra -Werror -I $(INCL)

RM = rm -rf

CC = gcc

LDFLAGS =  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS = -I/Users/$(USER)/.brew/opt/readline/include

HEADER = $(INCL)/minishell.h

#for libft

LIB = libft/libft.a

LIB_O = libft/srcs/*.o

######	

%.o:	%.c $(HEADER)  
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIB) 
		$(CC) $(CFLAGS) $(LIB) $(LDFLAGS) $(OBJS) -o $(NAME) 

$(LIB):  libft/srcs/*.c includes/libft.h
		make -C libft
clean: 
			$(RM) $(LIB_O)
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(LIB)
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
