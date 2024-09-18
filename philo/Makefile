
CC = cc

INCLUDE_DIR = header/

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INCLUDE_DIR) 
DFLAGS = -MMD -MP
LFLAGS = 

SRC_DIR = src
OBJECT_DIR = .obj/

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJECT_DIR)%.o,\
				$(SRC_DIR)/free.c\
				$(SRC_DIR)/init.c\
				$(SRC_DIR)/scene.c\
				$(SRC_DIR)/status.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/main.c\
			)

DEPENDENCIES = $(OBJECTS:.o=.d)

NAME = $(notdir /home/saperrie/cmor/42/Philosophers/philo)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $^ $(LFLAGS)

$(OBJECT_DIR)%.o: $(SRC_DIR)/%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p $(sort $(dir $(OBJECTS))) 

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean
	@make --no-print-directory all

.PHONY: run
.SILENT: run
run:
	clear
	make -sj re
	./$(NAME)

-include $(DEPENDENCIES)
