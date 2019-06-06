SRC_PATH=src
OBJ_PATH=obj
SRC_NAME = defines config test_config_main
SRC_FILE= $(addsuffix .c, $(addprefix $(SRC_PATH)/, $(SRC_NAME)))
OBJ_FILE= $(addsuffix .o, $(addprefix $(OBJ_PATH)/, $(SRC_NAME)))

CLEAN_OBJ =$(OBJ_FILE)
build: .depend bin/test_config_main

bin/test_config_main: $(OBJ_FILE) ../wmj_delog/obj/wmj_delog.o
	gcc $^ -o $@

.depend: $(SRC_FILE)
	gcc -MM -Iinc $^ > $@
	sed -i '/.o:/ s,^,obj/,' $@

sinclude .depend

obj/%.o: src/%.c $(MAKEFILE_LIST)
	gcc -c $< -Iinc -DDEBUG -o $@

rebuild: clean build

clean:
	-rm $(CLEAN_OBJ)
	-rm bin/*
	-rm .depend

.PHONY: build rebuild clean