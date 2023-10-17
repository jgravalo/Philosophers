NAME		=	philo

HEADER		=	./

OBJ_DIR		=	objs/

FILES		=	main philo philo_aux utils checker

SRCS		=	$(addsuffix .c, $(FILES))

OBJS		=	$(addprefix $(OBJ_DIR), $(subst .c,.o,$(SRCS)))

DEPS		=	$(subst .o,.d,$(OBJS))

INCLUDE		=	-I$(HEADER)

RM			=	rm -rf

MKD			=	mkdir -p

MK			=	Makefile

CFLAGS		=	-Wall -Wextra -Werror # -fsanitize=address

$(OBJ_DIR)%.o	:	%.c $(MK)
	@$(MKD) $(dir $@)
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP $(INCLUDE) -c $< -o $@

all				:
	@$(MAKE) $(NAME)

$(NAME)			:	$(OBJS)
	@$(CC) $(CFLAGS) -lm $(OBJS) -o $@

clean			:
	@$(RM) $(OBJ_DIR)

fclean			:
	@$(MAKE) clean

re				:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY			: all clean fclean re

-include		$(DEPS)
