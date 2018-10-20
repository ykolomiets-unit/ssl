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

HEADERS_DEP :=			$(addprefix $(INC_DIR)/, $(HEADERS))

SRCS :=					md5_core.c						\
						md5_transform.c					\
						md5_driver.c					\
						utils.c							\
						main.c							\

OBJ_DIR :=				./obj
OBJS :=					$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

TEST_DIR :=				./t
TEST_EXEC :=			$(TEST_DIR)/ft_ssl_test
TEST_OBJ_DIR :=			$(TEST_DIR)/obj

UNITY_DIR :=			$(TEST_DIR)/Unity
UNITY_INC :=			$(UNITY_DIR)/src	
UNITY_FIXTURE_INC :=	$(UNITY_DIR)/extras/fixture/src
#UNITY_FLAGS :=			-DUNITY_INCLUDE_CONFIG_H

UNITY_SRCS :=			unity.c							\
						unity_fixture.c

TEST_SRCS :=			$(UNITY_SRCS)						\
						all_tests.c							\

TEST_INC_FLAGS :=		-I$(UNITY_INC) -I$(UNITY_FIXTURE_INC)

TEST_OBJS :=			$(addprefix $(TEST_OBJ_DIR)/, $(TEST_SRCS:.c=.o))

CC :=					clang

CC_FLAGS :=				-Wall
CC_FLAGS +=				-Wextra
CC_FLAGS +=				-Werror
CC_FLAGS +=				-g

INC_FLAGS :=			$(addprefix -I, $(INC_DIR) $(LIBFT_INC))

LINK_FLAGS :=			$(LIBFT_LINK_FLAG)

TEST_CC_FLAGS :=		-Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LINK_FLAGS) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS_DEP)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(INC_FLAGS)

test: $(TEST_EXEC)
	clear
	./$(TEST_EXEC)

$(TEST_EXEC): $(NAME) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(NAME) -o $(TEST_EXEC) 

$(TEST_OBJS): | $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(TEST_CC_FLAGS) $(UNITY_FLAGS) $(TEST_INC_FLAGS) $(INC_FLAGS)

clean:
	rm -f $(OBJS)		
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_EXEC)
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OBJ_DIR)

re: fclean all

.PHONY: all test clean fclean re

vpath %.c		$(SRC_DIR) $(TEST_DIR) $(UNITY_DIR)/src $(UNITY_DIR)/extras/fixture/src
