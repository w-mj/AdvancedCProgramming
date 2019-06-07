SRC_PATH=src
OBJ_PATH=obj
BIN_PATH=bin
LIB_PATH=bin
MODULE_NAME = my_config
SRC_NAME = defines config
MAIN_NAME = test_config_main
SRC_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(SRC_NAME)))
OBJ_FILE= $(addsuffix .o, $(addprefix $(OBJ_PATH)/, $(SRC_NAME)))
MAIN_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(MAIN_NAME)))
LIB_FILE= $(addsuffix .a, $(addprefix $(OBJ_PATH)/, $(SRC_NAME)))
BIN_FILE = $(addprefix $(BIN_PATH)/, $(MAIN_NAME))


CLEAN_OBJ =$(OBJ_FILE) $(BIN_FILE) $(LIB_FILE) .depend
build: .depend $(BIN_FILE)

$(BIN_FILE): $(OBJ_FILE) $(MAIN_FILE) ../wmj_delog/obj/wmj_delog.o
	gcc $^ -o $@ -Iinc

.depend: $(SRC_FILE) $(MAIN_FILE)
	gcc -MM -Iinc $^ > $@
	sed -i '/.o:/ s,^,obj/,' $@

sinclude .depend

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(MAKEFILE_LIST)
	gcc -c $< -Iinc -DDEBUG -o $@

rebuild: clean build

clean:
	-rm $(CLEAN_OBJ)


.PHONY: build rebuild clean