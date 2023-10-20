NAME		=	philo

OBJ_DIR		=	objs/

FILES		=	main philo philo_aux utils check_errors

SRCS		=	$(addsuffix .c, $(FILES))

OBJS		=	$(addprefix $(OBJ_DIR), $(subst .c,.o,$(SRCS)))

DEPS		=	$(subst .o,.d,$(OBJS))

RM			=	rm -rf

MKD			=	mkdir -p

MK			=	Makefile

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -fsanitize=thread

$(OBJ_DIR)%.o	:	%.c
	$(MKD) $(dir $@)
	$(CC) -MT $@ $(CFLAGS) -MMD -MP -c $< -o $@

all				:
	$(MAKE) $(NAME)

$(NAME)			:	$(OBJS)
	$(CC) $(CFLAGS) -lm $(OBJS) -o $@

clean			:
	$(RM) $(OBJ_DIR)

fclean			:
	$(MAKE) clean
	$(RM)	$(NAME)

re				:
	$(MAKE) fclean
	$(MAKE) all

.PHONY			: all clean fclean re

-include		$(DEPS)
