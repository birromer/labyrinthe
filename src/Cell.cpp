#include "../include/Cell.h"
#include <iostream>

Cell::Cell(int x, int y) : m_x(x), m_y(y) {

}
Cell::~Cell() {
   delete[] m_neighb;
}


void Cell::add_neighb(Cell *c) {
   bool first = false;

   for (int i=0; i < this->m_nb_neighb; i++) {  // searches for the case neighbour already exists
      if (this->m_neighb[i]->m_x == c->m_x && this->m_neighb[i]->m_y == c->m_y) {
         return;
      }
   }

   if (this->m_neighb == NULL) {  // initializes neighbour list if first niehgbour
      this->m_neighb = new Cell*[1];
      this->m_nb_neighb = 1;  // increases number of neighbours, as another is being added
      this->m_neighb[0] = c;  // sets new neighbour
      first = true;
   }

   if (!first) { // if it is the first time it has already incremented
      this->m_nb_neighb += 1;  // increases number of neighbours, as another is being added
      auto aux_m_neighb = this->m_neighb;  // temporary variable so that previous values are not lost in case
      // reallocation uses another area of the memory
      this->m_neighb = new Cell*[this->m_nb_neighb];  // allocates new memory space so that bigger array can be stored

//      memcpy(this->m_neighb, aux_m_neighb, this->m_nb_neighb-1);
      for (int i=0; i<m_nb_neighb-1; i++)  // as one cannot test if previous addresses were reused, previous elements
         this->m_neighb[i] = aux_m_neighb[i];    // are copied

      this->m_neighb[m_nb_neighb-1] = c;  // sets new neighbour

      delete[] aux_m_neighb;
   }

   c->add_neighb(this);                // repeats for neighbour
}


void Cell::add_neighb(Cell *c1, Cell *c2) {
   c1->add_neighb(c2);
}

std::string Cell::toString() {
   std::string tmp = "(";
   tmp.append(std::to_string(this->m_x));
   tmp.append(",");
   tmp.append(std::to_string(this->m_y));
   tmp.append(")");

   return tmp;
}

std::ostream& operator<<(std::ostream& stream, const Cell& c) {
   std::string tmp = "(";
   tmp.append(std::to_string((int)c.m_x));
   tmp.append(",");
   tmp.append(std::to_string((int)c.m_y));
   tmp.append(")");

   stream << tmp;

   return stream;
}

std::istream& operator>>(std::istream& stream, Cell& c) {
   std::string tmp;
   stream.get();
   c.m_x = stream.get() - 48;
   stream.get();
   c.m_y = stream.get() - 48;
   stream.get();
   return stream;
}
