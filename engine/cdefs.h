//
// Created by Citiral on 14/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_CDEFS_H
#define I_WANNA_KILL_THE_BOSHY_CDEFS_H

#define ASSERT(C, M) do {\
    if (!(C)) {\
        std::cout << "[ASSERT] Failed in " << __FILE__ << " line " << __LINE__ << std::endl;\
        std::cout << "[ASSERT] Condition: " << #C << std::endl;\
        std::cout << "[ASSERT] message: " << M << std::endl;\
    }\
}while(0)

#endif //I_WANNA_KILL_THE_BOSHY_CDEFS_H