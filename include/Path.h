#pragma once

#include <cstddef>
#include "Cell.h"
#include "vibes.h"

class Cell;

class Path {
    public:
        Path(const Cell *c);
        ~Path();
        void add_to_path(const Cell *c);
        void print_path();
    private:
        const Cell *m_c;
        Path *m_next = NULL;
};
