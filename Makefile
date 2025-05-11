######################## 🛠️ ##############################

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RFLAGS = -lreadline -lhistory

######################## 🛠️ ##############################

RM = rm -rf

######################## 🤖 #############################

NAME = minishell

######################## 📁 #############################

LIBFT = libft.a
LIBFT_DIR = srcs/dependency/libft

LIBC = $(shell ls $(LIBFT_DIR)/*.c)

LIBFT_OBJS = $(LIBC:.c=.o)

######################## 📁 #############################

SRC = $(shell ls srcs/*.c) $(shell ls srcs/token/*.c)\
		$(shell ls srcs/env/*.c) $(shell ls srcs/parsing/*.c) \
		$(shell ls srcs/struct/*.c) $(shell ls srcs/signals/*.c)\
		$(shell ls srcs/io/*.c) $(shell ls srcs/exec/*.c)\
		$(shell ls srcs/error/*.c) $(shell ls srcs/checker/*.c)

SRCS = ${SRC} $(LIBC) $(READ)

OBJS = $(SRCS:.c=.o)

######################## 🧠 #############################

INCLUDES = -Iincludes -I$(LIBFT_DIR)

######################## 🎨 #############################

BLUE	=	\033[0;34m
GREEN	=	\033[0;32m
RED		=	\033[31m
RESET	=	\033[0m
YELLOW	=	\033[0;33m

define HEADER

 ██████╗ ██╗  ██╗ ██████╗ ███████╗████████╗
██╔════╝ ██║  ██║██╔═══██╗██╔════╝╚══██╔══╝
██║  ███╗███████║██║   ██║███████╗   ██║
██║   ██║██╔══██║██║   ██║╚════██║   ██║
╚██████╔╝██║  ██║╚██████╔╝███████║   ██║
 ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚══════╝   ╚═╝
██╗███╗   ██╗    ████████╗██╗  ██╗███████╗
██║████╗  ██║    ╚══██╔══╝██║  ██║██╔════╝
██║██╔██╗ ██║       ██║   ███████║█████╗
██║██║╚██╗██║       ██║   ██╔══██║██╔══╝
██║██║ ╚████║       ██║   ██║  ██║███████╗
╚═╝╚═╝  ╚═══╝       ╚═╝   ╚═╝  ╚═╝╚══════╝
███████╗██╗  ██╗███████╗██╗     ██╗
██╔════╝██║  ██║██╔════╝██║     ██║
███████╗███████║█████╗  ██║     ██║
╚════██║██╔══██║██╔══╝  ██║     ██║
███████║██║  ██║███████╗███████╗███████╗
╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝

endef
export HEADER

######################## 🗃️ #############################

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


######################## 🎶🎹 ############################

all: $(NAME) header

header:
	@echo "$(GREEN)$$HEADER$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(RFLAGS)
	@echo "Compiled ✅"
	@echo "The program $(NAME) is created ✅"

clean:
	@$(RM) $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS)
	@echo ".o files are destroyed ✅"

fclean: clean
	@$(RM) $(NAME)
	@echo "Everything is clean ✅"

re: fclean all

.PHONY: all clean fclean header re
