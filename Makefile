NAME	= wolf3d

INCL	= -I./libft/includes \
			-I./mlx \
			-I./wolf.h

SFILE	= wolf.c \
			wolf_cast.c \
			wolf_map.c \
			wolf_hook.c

SRC		= $(addprefix $(SDIR), $(SFILE))
SDIR	= ./

LFILE	= ./libft/libft.a \
			./mlx/libmlx.a
LIB		= -L./libft -lft \
			-L./mlx -lmlx
LDIR	= ./libft

OFILE	= $(SRC:.c=.o)
OBJ		= $(addprefix $(ODIR), $(OFILE))
ODIR	= ./obj/

CC		= gcc
FLAG	= -Wall -Wextra -Werror
FRAME	= -framework OpenGL -framework AppKit
RM		= rm -rf
MC		= make -C

all: $(LIB) $(NAME)

lib: $(LIB)

$(LIB):
	@$(MC) $(LDIR)
	@$(MC) ./mlx

$(ODIR)%.o: %.c
	@mkdir -p $(ODIR)
	@$(CC)  -c $< -o $@ $(FLAG) $(INCL)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(FRAME) $(OBJ) $(LIB)

clean:
	@$(MC) $(LDIR) clean
	@$(RM) ./mlx/*.o
	@$(RM) $(ODIR)

fclean: clean
	@$(RM) $(LFILE)
	@$(RM) $(NAME)

re: fclean all
