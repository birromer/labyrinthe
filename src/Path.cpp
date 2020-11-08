#include "../include/Path.h"

Path::Path(const Cell *c) : m_c(c) {

}

Path::~Path() {
    if (this->m_next != NULL)
        delete this->m_next;
//    delete this->m_c;
}

void Path::add_to_path(const Cell *c) {
    if (this->m_next == NULL)
        this->m_next = new Path(c);
    else
        this->m_next->add_to_path(c);
}

void Path::print_path() {

    if (this->m_next == NULL) {
        return;
    }
    else {
        const Cell *c1 = this->m_c;
        const Cell *c2 = this->m_next->m_c;
        vibes::drawBox(std::min(c1->m_x, c2->m_x) + 0.45, std::max(c1->m_x, c2->m_x) + 0.55,
                       std::min(c1->m_y, c2->m_y) + 0.45, std::max(c1->m_y, c2->m_y) + 0.55,
                   "blue[blue]");
        this->m_next->print_path();
    }
}
