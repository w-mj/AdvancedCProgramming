#include "wmj_types.h"
#include "wmj_delog.h"

_i32 main(_i32 argc, _s argv[]) {
    if (argc < 3) {
        init_delog(0, 0);
    } else {
        init_delog(argv[1], argv[2]);
    }
    init_delog("testa", "testb");
    return 0;
}