//
// Created by fakys on 17.10.2026.
//
#include "init_os_kernel.h"
#include "os_user_mod.h"



void os_kernel::useKernelMod() {
    os_kernel::kernel.userMod.user_mode_type = KERNEL_USER_MOD;
}

void os_kernel::useUserMod() {
    os_kernel::kernel.userMod.user_mode_type = USER_MOD;
}
