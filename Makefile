NAME :=					ft_ssl

INC_DIR :=				./includes
SRC_DIR :=				./src
LIB_DIR :=				./lib

LIBFT_DIR :=			$(LIB_DIR)/libft
LIBFT_INC :=			$(LIBFT_DIR)/includes
LIBFT_LINK_FLAG :=		-lft -L$(LIBFT_DIR)
LIBFT :=				$(LIBFT_DIR)/libft.a

HEADERS :=				ft_ssl.h						\
						md5.h							\
						utils.h							\
						sha224_256.h					\
						base64.h						\

HEADERS_DEP :=			$(addprefix $(INC_DIR)/, $(HEADERS))

SRCS :=					md5_core.c						\
						md5_transform.c					\
						md5_driver.c					\
						sha224_256_core.c				\
						sha256_transform.c				\
						sha224_core.c					\
						sha256_core.c					\
						sha256_driver.c					\
						sha224_driver.c					\
						utils1.c						\
						utils2.c						\
						error.c							\
						process_digest.c				\
						digest_handlers.c				\
						base64_handler.c				\
						print_digest.c					\
						base64.c						\
						main.c							\

OBJ_DIR :=				./obj
OBJS :=					$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC :=					clang

CC_FLAGS :=				-Wall
CC_FLAGS +=				-Wextra
CC_FLAGS +=				-Werror
CC_FLAGS +=				-g

INC_FLAGS :=			$(addprefix -I, $(INC_DIR) $(LIBFT_INC))

LINK_FLAGS :=			$(LIBFT_LINK_FLAG)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LINK_FLAGS) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS_DEP)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(INC_FLAGS)

clean:
	rm -f $(OBJS)		

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all test clean fclean re

vpath %.c		$(SRC_DIR)
