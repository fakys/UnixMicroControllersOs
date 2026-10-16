//
// Created by fakys on 15.10.2026.
//

#include <unix_os.h>
#include "init_os_kernel.h"

int main() {
    os_kernel::init_os_kernel();
    userMain();

    while (true) {



    }
    return 0;
}
