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
    void add_neighb(Cell *c);
    static void add_neighb(Cell *c1, Cell *c2);
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
