
MODULE_NAME = wmj_delog
SRC_NAME = wmj_delog
MAIN_NAME = test_wmj_delog

DEFINES = DEBUG
INC_PATH = inc ../wmj_commons/inc

SRC_PATH=src
OBJ_PATH=obj
BIN_PATH=bin
LIB_PATH=bin
SRC_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(SRC_NAME)))
OBJ_FILE= $(addsuffix .o, $(addprefix $(OBJ_PATH)/, $(SRC_NAME)))
MAIN_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(MAIN_NAME)))
LIB_FILE= $(addsuffix .a, $(addprefix $(LIB_PATH)/lib, $(MODULE_NAME)))
BIN_FILE = $(addprefix $(BIN_PATH)/, $(MAIN_NAME))
INC_FLAG = $(addprefix -I, $(INC_PATH))
DEF_FLAG = $(addprefix -D, $(DEFINES))
RELEASE_PATH = ../wmj_commons

CLEAN_OBJ = $(OBJ_FILE) $(BIN_FILE) $(LIB_FILE) .depend
build: .depend $(BIN_FILE)

$(BIN_FILE): $(MAIN_FILE) $(LIB_FILE)
	gcc $^ -o $@ $(INC_FLAG) $(DEF_FLAG)

.depend: $(SRC_FILE) $(MAIN_FILE)
	gcc -MM $(INC_FLAG) $(DEF_FLAG) $^ > $@
	sed -i '/.o:/ s,^,$(OBJ_PATH)/,' $@

sinclude .depend

$(LIB_FILE): $(OBJ_FILE)
	ar -rs $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(MAKEFILE_LIST)
	gcc -c $< $(INC_FLAG)  $(DEF_FLAG) -o $@

rebuild: clean build

clean:
	-rm $(CLEAN_OBJ)

release: build
	cp inc/$(MODULE_NAME).h $(RELEASE_PATH)/inc/
	cp $(LIB_FILE) $(RELEASE_PATH)/lib

.PHONY: build rebuild clean release