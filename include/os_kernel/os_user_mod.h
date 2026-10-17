#ifndef UNIX_MICRO_CONTROLLERS_OPERATION_SYSTEM_OS_USER_MOD_H
#define UNIX_MICRO_CONTROLLERS_OPERATION_SYSTEM_OS_USER_MOD_H

#define KERNEL_USER_MOD 0
#define USER_MOD 3

namespace os_kernel {
    typedef struct {
        int user_mode_type;
    } UserMod;

    void useKernelMod();
    void useUserMod();
}

#endif
