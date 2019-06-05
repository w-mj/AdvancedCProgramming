
build: .depend bin/test_config_main

bin/test_config_main: obj/test_config_main.o obj/config.o ../wmj_delog/obj/wmj_delog.o
	gcc $^ -o $@

.depend: src/test_config_main.c src/config.c
	gcc -MM -Iinc $^ > $@
	sed -i '/.o:/ s,^,obj/,' $@

sinclude .depend

obj/%.o: src/%.c
	gcc -c $< -Iinc -DDEBUG -o $@

rebuild: clean build

clean:
	-rm obj/*
	-rm bin/*
	-rm .depend

.PHONY: build rebuild clean