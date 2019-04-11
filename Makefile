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
						sha384_512.h					\
						base64.h						\
						hmac_sha256.h					\
						pbkdf2.h						\
						des.h							\

HEADERS_DEP :=			$(addprefix $(INC_DIR)/, $(HEADERS))

SRCS :=					md5_core.c						\
						md5_transform.c					\
						md5_driver.c					\
						sha224_256_core.c				\
						sha384_512_core.c				\
						sha256_transform.c				\
						sha512_transform.c				\
						sha224_core.c					\
						sha256_core.c					\
						sha384_core.c					\
						sha512_core.c					\
						sha224_driver.c					\
						sha256_driver.c					\
						sha384_driver.c					\
						sha512_driver.c					\
						utils1.c						\
						utils2.c						\
						error.c							\
						process_digest.c				\
						digest_handlers.c				\
						base64_handler.c				\
						print_digest.c					\
						base64_decode.c					\
						base64_encode.c					\
						hmac_sha256.c					\
						pbkdf2.c						\
						des_get_key_and_iv.c			\
						des_handler.c					\
						des_keys.c						\
						des_core.c						\
						des_padding.c					\
						des_ecb.c						\

MAIN :=					main.c

OBJ_DIR :=				./obj
CORE_OBJS :=			$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

OBJS := 				$(CORE_OBJS) \
						$(addprefix $(OBJ_DIR)/, $(MAIN:.c=.o))


TEST_DIR :=				./t
TEST_EXEC :=			$(TEST_DIR)/test
TEST_OBJ_DIR :=			$(TEST_DIR)/obj

TEST_SRCS :=			run_tests.c						\
						hmac_tests.c					\
						pbkdf2_tests.c					\
						des_tests.c						\

TEST_OBJS :=			$(addprefix $(TEST_OBJ_DIR)/, $(TEST_SRCS:.c=.o))

CC :=					clang

CC_FLAGS :=				-Wall -Wextra -Werror -g -O0
TEST_CC_FLAGS :=		-Wall -Wextra -g -O0

INC_FLAGS :=			$(addprefix -I, $(INC_DIR) $(LIBFT_INC))

LINK_FLAGS :=			$(LIBFT_LINK_FLAG)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LINK_FLAGS) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS_DEP)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(INC_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

test: $(TEST_EXEC)
	clear
	./$(TEST_EXEC)

$(TEST_EXEC): $(CORE_OBJS) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(CORE_OBJS) $(LINK_FLAGS) -o $(TEST_EXEC) 

$(TEST_OBJS): | $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(TEST_CC_FLAGS) $(INC_FLAGS)

clean:
	rm -f $(OBJS)		

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re

vpath %.c		$(SRC_DIR) $(TEST_DIR)
