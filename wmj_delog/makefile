
build: .depend bin/test_delog_main

bin/test_delog_main: obj/test_delog_main.o obj/wmj_delog.o
	gcc $^ -o $@

# $^ 所有依赖
# $< 第一个依赖
# $@ 目标

.depend: src/test_delog_main.c src/wmj_delog.c
	gcc -MM -Iinc $^ > $@
	sed -i '/.o:/ s,^,obj/,' $@

sinclude .depend

obj/%.o: src/%.c
	gcc -c $< -Iinc -o $@

rebuild: clean build

clean:
	-rm obj/*
	-rm bin/*
	-rm .depend

.PHONY: build rebuild clean