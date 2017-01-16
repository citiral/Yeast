//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_PATHS_H
#define I_WANNA_KILL_THE_BOSHY_PATHS_H

#include <string>

#define FOLDER_RES "res\\"
#define FOLDER_ENTITIES FOLDER_RES "entities\\"
#define FOLDER_ASSETS FOLDER_RES "assets\\"
#define FOLDER_WORLDS FOLDER_RES "worlds\\"
#define FOLDER_SCRIPTS FOLDER_RES "scripts\\"
#define FOLDER_SHADERS FOLDER_RES "shaders\\"

// formats a path to a platform compatible string
std::string formatPath(std::string path);

#endif //I_WANNA_KILL_THE_BOSHY_PATHS_H
