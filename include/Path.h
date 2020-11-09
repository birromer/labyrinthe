#pragma once

#include <cstddef>
#include "Cell.h"
#include "vibes.h"

class Cell;

class Path {
    public:
        Path(const Cell *c);
        ~Path();
        /**
         * \brief Adds the cell c to the calling path, recursivelly calling itself in m_next until no next cell is found
         * \note Creates a new path if m_next is NULL
         * \param c a pointer to a Cell
         */
        void add_to_path(const Cell *c);
        /**
         * \brief Displays the path  by drawing rectangles connecting the points
         */
        void print_path();
    private:
        const Cell *m_c;
        Path *m_next = NULL;
};
