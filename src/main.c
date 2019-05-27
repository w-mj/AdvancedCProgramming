#include "wmj_info.h"

int main(int argc, char **argv) {
    __info("This is Main func %d", 1);
    _error(argc < 2, "param is too less! only %d \n", argc);
    return 0;
}