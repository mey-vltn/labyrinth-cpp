#ifndef CASE_H
#define CASE_H

#include <iostream>

class Case {
    public:

    virtual char afficher() = 0;
    virtual ~Case() = default;
};

#endif