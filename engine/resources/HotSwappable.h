//
// Created by Olivier on 15/01/17.
//

#ifndef YEAST_HOTSWAPPABLE_H
#define YEAST_HOTSWAPPABLE_H

#include <string>

class HotSwappable {
public:
    // returns 0 if the hotswap succeeded, 1 otherwise
    virtual bool hotSwap(const std::string& path) = 0;
};


#endif //YEAST_HOTSWAPPABLE_H
