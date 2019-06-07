#!/bin/bash
INPUT_PATH=input
OUT_PATH=out
SRC_PATH=src
INC_PATH=inc
BIN_PATH=bin
OBJ_PATH=obj
print_help() {
    echo "submodel.sh <model name>"
}

create_dir() {
    mkdir $1 > /dev/null 2>&1
    if [ $? = 0 ]; then
        echo create dir $1.
        return 0
    else
        echo "could not create directory "/$1
        exit
    fi
}

create_file() {
    if [ -e $1 ]; then
        echo $1 is already exists.
        return 1
    fi
    touch $1
    echo create $1
    return 0
}

create_test_file() {
    text="#include <stdio.h>\n"
    text=$text"#include <stdlib.h>\n"
    text=$text"#include \""$1".h\"\n"
    text=$text"\n"
    text=$text"/**\n"
    text=$text" * File: test_"$1".c\n"
    text=$text" * Time: "`date +%c`"\n"
    text=$text" * Author: "$USER"\n"
    text=$text" * Comment: 模块"$1"的测试程序\n"
    text=$text" **/\n"
    text=$text"int main(int argc, char* argv[]) {\n"
    text=$text"    // 在此处加入测试代码\n"
    text=$text"    return 0;\n"
    text=$text"}\n"
    echo -e "$text" > "src/test_"$1".c"
    echo create src/test_$1.c
}

create_source() {
    text="#ifndef _"$1"_H_\n"
    text=$text"#define _"$1"_H_\n"
    text=$text"/**\n"
    text=$text" * File: "$1".h\n"
    text=$text" * Time: "`date +%c`"\n"
    text=$text" * Author: "$USER"\n"
    text=$text" * Comment: \n"
    text=$text" **/\n\n\n\n\n\n\n\n"
    text=$text"#endif"
    echo -e "$text" > inc/$1.h
    echo create inc/$1.h
    
    text="/**\n"
    text=$text" * File: "$1".c\n"
    text=$text" * Time: "`date +%c`"\n"
    text=$text" * Author: "$USER"\n"
    text=$text" * Comment: \n"
    text=$text" **/\n"
    text=$text"#include \""$1".h\""
    echo -e "$text" > src/$1.c
    echo create src/$1.c
}

create_makefile() {
    text="\n"
    text=$text"MODULE_NAME="$1"\n"
    text=$text"SRC_NAME="$1"\n"
    text=$text"MAIN_NAME=test_"$1"\n"
    echo -e "$text" > $1/Makefile
    cat Makefile.template >> $1/Makefile
    echo create Makefile
}

create_module() {
    if [ -d $1 ]; then
        echo $1 is already exists.
        exit
    fi
    create_dir $1
    cd $1
    create_dir $SRC_PATH
    create_dir $INC_PATH
    create_dir $OBJ_PATH
    create_dir $BIN_PATH
    create_dir $INPUT_PATH
    create_dir $OUT_PATH
    create_test_file $1
    create_source $1
    cd ..
    create_makefile $1
}

if [ $# -eq "0" ]; then
    print_help
    exit
fi
if [ $1 = "submodule" ]; then
    if [ $# -lt 2 ]; then
        echo "no submodule name"
        exit
    fi
    create_module $2
    exit
fi
if [ $1 = "source" ]; then
    if [ $# -lt 2 ]; then
        echo "no source name"
        exit
    fi
    create_source $2
    exit
fi