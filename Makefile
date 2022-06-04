NAME=scop

CC=gcc
# FLAGS = -Wall -Werror -Wextra
# FLAGS += -Weverything
FLAGS += -Wno-documentation
FLAGS += -Wno-documentation-unknown-command
FLAGS += -Wno-reserved-id-macro
FLAGS += -Wno-missing-noreturn
FLAGS += -Wno-incompatible-pointer-types-discards-qualifiers

# Flags variables
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    FLAGS += -g3 -fsanitize=address
endif

OPTI ?= 0
ifeq ($(OPTI), 1)
    FLAGS += -Ofast -march=native
endif

SRC_PATH=src/
SRC_NAME=main.c\
			gl/callbacks.c\
			gl/gl_fps.c\
			gl/gl_init.c\
			gl/gl_render.c\
			gl/gl_shaders.c\
			gl/gl_textures.c\
			env_init.c\
			scop_exit.c\
			singletons.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))

INC_PATH=include/
INC_NAME=main.h

INC=$(addprefix $(INC_PATH), $(INC_NAME))

OBJS=$(SRC:.c=.o)

########################## Librarys ######################
LIBS_PATH=libs

LIB_PATH=$(LIBS_PATH)/libft
LIB=$(LIB_PATH)/libft.a

LIB_VEC_PATH=$(LIBS_PATH)/lib_vec
LIB_VEC=$(LIB_VEC_PATH)/lib_vec.a

LIBBMP_PATH=$(LIBS_PATH)/libbmp
LIBBMP=$(LIBBMP_PATH)/libbmp.a

LIB_GLAD_PATH = $(LIBS_PATH)/glad
GLAD_PATH = $(LIB_GLAD_PATH)/include/glad/
KHR_PATH = $(LIBS_PATH)/include/KHR/
LIB_GLAD = $(LIB_GLAD_PATH)/libglad.a

##########################################################

all: $(NAME)

$(NAME): $(LIB) $(LIB_VEC) $(LIBBMP) $(LIB_GLAD) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) $(LIB_VEC) $(LIBBMP) $(LIB_GLAD) ${CMAKE_DL_LIBS} -lpthread -lglfw -lGL -ldl -lm

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@tput civis
	@printf " Compiling $<"
	@printf "                                       \\r"
	@tput cnorm
	@$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -I$(LIB_VEC_PATH) -I$(LIBBMP_PATH) -I$(GLAD_PATH) -o $@ -c $<

########################## Library rules ##########################

$(LIB): $(LIB_PATH)
	@echo "Making Libft..."
	@make -C $(LIB_PATH)

$(LIB_VEC): $(LIB_VEC_PATH)
	@echo "Making lib_vec..."
	@make -C $(LIB_VEC_PATH)

$(LIBBMP): $(LIBBMP_PATH)
	@echo "Making libbmp..."
	@make -C $(LIBBMP_PATH)

$(LIB_GLAD): $(LIB_GLAD_PATH)
	@echo "Making libglad..."
	@make -C $(LIB_GLAD_PATH)


###################################################################

clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean
	@make -C $(LIB_VEC_PATH) clean
	@make -C $(LIBBMP_PATH) clean
	@make -C $(LIB_GLAD_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_PATH) fclean
	@make -C $(LIB_VEC_PATH) fclean
	@make -C $(LIBBMP_PATH) fclean
	@make -C $(LIB_GLAD_PATH) fclean

re: fclean all
