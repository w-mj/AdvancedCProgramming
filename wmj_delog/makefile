main: bin/test_delog_main
	gcc -c src/wmj_delog.c -Iinc -I../inc -o obj/wmj_delog.o
	gcc -c src/test_delog_main.c -Iinc -I../inc -o obj/test_delog_main.o
	gcc obj/test_delog_main.o obj/wmj_delog.o -o bin/test_delog_main
