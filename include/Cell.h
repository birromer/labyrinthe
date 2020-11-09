#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <ostream>
#include <iostream>

class Cell {
  public:
    Cell(int x, int y);
    ~Cell();
    /**
     * \brief Adds the cell c to the neighbours of the calling cell, and does it the other way around
     * \note used to the add_neighb(c1,2)
     * \param c a pointer to a Cell
     */
    void add_neighb(Cell *c);
    /**
     * \brief Adds the cell c1 to the neighbours of the c2 cell, and does it the other way around
     * \param c1 a pointer to a Cell
     * \param c2 a pointer to a Cell
     */
    static void add_neighb(Cell *c1, Cell *c2);
    /**
     * \brief Creates a string in the format (m_x,m_y)
     */
    std::string toString();

    friend std::ostream& operator<<(std::ostream& stream, const Cell& c);
    friend std::istream& operator>>(std::istream& stream, Cell& c);

//  private:
    double m_x;
    double m_y;

    bool m_explored = false;
    bool m_displayed = false;
    bool m_saved = false;
    int m_nb_neighb = 0;
    Cell **m_neighb = NULL;
};
