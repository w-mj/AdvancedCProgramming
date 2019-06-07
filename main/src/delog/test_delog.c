#include "types.h"
#include "delog/delog.h"

_i32 main(_i32 argc, _s argv[]) {
    _error(argc < 2, _main_END, "%s need 2 params!", argv[0]);
    _bug(argc < 3);
    _si(argc);
    _sp(argc);
    _sf((double) argc);
    _sx(argc);
    _pos();
    _ss(argv[1]);
    _sc(argv[2][0]);
    _sa(argv[0], 20);
_main_END:
    return 0;
}