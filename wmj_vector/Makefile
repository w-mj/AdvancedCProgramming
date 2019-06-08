
MODULE_NAME=wmj_vector
SRC_NAME=wmj_vector
MAIN_NAME=test_wmj_vector


#MODULE_NAME = wmj_delog
#SRC_NAME = wmj_delog
#MAIN_NAME = test_wmj_delog
DEPEND_LIBS = wmj_delog
DEFINES = DEBUG

COMMON_INC_PATH = ../wmj_commons/inc
COMMON_LIB_PATH = ../wmj_commons/lib
RELEASE_PATH = ../wmj_commons
INC_PATH = inc $(COMMON_INC_PATH)
SRC_PATH=src
OBJ_PATH=obj
BIN_PATH=bin
LIB_PATH=bin
SRC_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(SRC_NAME)))
OBJ_FILE= $(addsuffix .o, $(addprefix $(OBJ_PATH)/, $(SRC_NAME)))
MAIN_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(MAIN_NAME)))
OUT_LIB_FILE= $(addsuffix .a, $(addprefix $(LIB_PATH)/lib, $(MODULE_NAME)))
BIN_FILE = $(addprefix $(BIN_PATH)/, $(MAIN_NAME))
INC_FLAG = $(addprefix -I, $(INC_PATH))
DEF_FLAG = $(addprefix -D, $(DEFINES))
LIB_FILE = $(addsuffix .a, $(addprefix $(COMMON_LIB_PATH)/lib, $(DEPEND_LIBS)))

CLEAN_OBJ = $(OBJ_FILE) $(BIN_FILE) $(OUT_LIB_FILE) .depend
build: .depend $(BIN_FILE)

$(BIN_FILE): $(MAIN_FILE) $(OUT_LIB_FILE)
	gcc $^ $(LIB_FILE) -g -o $@ $(INC_FLAG) $(DEF_FLAG)

.depend: $(SRC_FILE) $(MAIN_FILE)
	gcc -MM $(INC_FLAG) $(DEF_FLAG) $^ > $@
	sed -i '/.o:/ s,^,$(OBJ_PATH)/,' $@

sinclude .depend

$(OUT_LIB_FILE): $(OBJ_FILE)
	ar -rs $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(MAKEFILE_LIST)
	gcc -c $< $(INC_FLAG)  $(DEF_FLAG) -g -o $@

rebuild: clean build

clean:
	-rm $(CLEAN_OBJ)

release: build
	cp inc/$(MODULE_NAME).h $(RELEASE_PATH)/inc/
	cp $(OUT_LIB_FILE) $(RELEASE_PATH)/lib

.PHONY: build rebuild clean release