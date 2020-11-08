#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <list>
#include <limits>

#include "../include/vibes.h" // might need to change those includes
#include "../include/Cell.h"
#include "../include/Path.h"

struct Maze {
    Cell *init;  // the whole graph can be explored having the root
    Cell *exit;
};

void draw_gate(const Cell *n1, const Cell *n2);
void draw_link(const Cell *c1, const Cell *c2);
void display_graph(Cell *cell);
void display(Maze m);
Maze create_maze(Cell *init, Cell *exit);
bool find_path(Cell *c, Cell *cf, Path *path);

// TD4
void save_maze(const Maze& maze, const std::string& file_name);
void save_cells(Cell* cell, std::ofstream *f);
Maze read_maze(const std::string& file_name);

int main() {
    vibes::beginDrawing();
    vibes::newFigure("Maze");
    vibes::setFigureProperties("Maze",
                               vibesParams("x", 100, "y", 100,
                                          "width", 400, "height", 400)
                            );
    vibes::axisLimits(0-0.5, 4+0.5, 0-0.5, 4+0.5);


    // -------------- activity B ---------------------
    // the cells
    Cell *c11 = new Cell(1,1);
    Cell *c12 = new Cell(1,2);
    Cell *c13 = new Cell(1,3);
    Cell *c14 = new Cell(1,4);
    Cell *c21 = new Cell(2,1);
    Cell *c22 = new Cell(2,2);
    Cell *c23 = new Cell(2,3);
    Cell *c24 = new Cell(2,4);
    Cell *c31 = new Cell(3,1);
    Cell *c32 = new Cell(3,2);
    Cell *c33 = new Cell(3,3);
    Cell *c34 = new Cell(3,4);
    Cell *c41 = new Cell(4,1);
    Cell *c42 = new Cell(4,2);
    Cell *c43 = new Cell(4,3);
    Cell *c44 = new Cell(4,4);

    // the connections
    Cell::add_neighb(c14,c24);
    Cell::add_neighb(c24,c34);
    Cell::add_neighb(c34,c44);
    Cell::add_neighb(c44,c43);
    Cell::add_neighb(c43,c42);
    Cell::add_neighb(c42,c41);
    Cell::add_neighb(c41,c31);
    Cell::add_neighb(c31,c32);
    Cell::add_neighb(c32,c22);
    Cell::add_neighb(c22,c23);
    Cell::add_neighb(c23,c33);
    Cell::add_neighb(c22,c21);
    Cell::add_neighb(c21,c11);
    Cell::add_neighb(c11,c12);
    Cell::add_neighb(c12,c13);

    display_graph(c21);

    Maze maze = create_maze(c13,c14);

    save_maze(maze, "../data/td4_maze.txt");  // save the maze on a file

    display(maze);

    Path *path = new Path(c13);
    bool path_exists = find_path(c13, c14, path);

    if (path_exists)
        path->print_path();
    else
        std::cout << "There is no path between " << c13->toString() << " and " << c14->toString() << std::endl;

    // freeing memory
    delete path;
    delete c11;
    delete c12;
    delete c13;
    delete c14;
    delete c21;
    delete c22;
    delete c23;
    delete c24;
    delete c31;
    delete c32;
    delete c33;
    delete c34;
    delete c41;
    delete c42;
    delete c43;
    delete c44;

    // -------------- END activity B ---------------------

    // -------------- activity C ---------------------
    vibes::newFigure("Maze4");
    vibes::setFigureProperties("Maze4", vibesParams("x", 100, "y", 100, "width", 400, "height", 400));
    vibes::axisLimits(0-0.5, 4+0.5, 0-0.5, 4+0.5);
    Maze maze4 = read_maze("../data/laby4x4.txt");
    display(maze4);

    vibes::newFigure("Maze8");
    vibes::setFigureProperties("Maze8", vibesParams("x", 100, "y", 100, "width", 400, "height", 400));
    vibes::axisLimits(0-0.5, 8+0.5, 0-0.5, 8+0.5);
    Maze maze8 = read_maze("../data/laby8x8.txt");
    display(maze8);

    vibes::newFigure("Maze10");
    vibes::setFigureProperties("Maze10", vibesParams("x", 100, "y", 100, "width", 400, "height", 400));
    vibes::axisLimits(0-0.5, 10+0.5, 0-0.5, 10+0.5);
    Maze maze10 = read_maze("../data/laby10x10.txt");
    display(maze10);
    // -------------- END activity C ---------------------

    return 0;
}

Maze read_maze(const std::string& file_name) {
    std::ifstream f(file_name);  // initializes file interface
    std::string tmp;  // temporary string for reading the file

    // each element will be referenced by a pair <int, int>
    // and will store the cell and a list of pairs (the neighbours),
    // a list is used because the number of neighbours is fixed and all reads/writes will be sequential
    std::map<std::pair<int,int>, std::pair<Cell*, std::list<std::pair<int,int>>>> m_cells;
    float init_x, init_y, end_x, end_y;

    std::getline(f, tmp);  // # Start: line
    std::getline(f, tmp);  // actual first cell
    init_x = (float)(tmp[1])-48;  // coordinats of entry cell
    init_y = (float)(tmp[3])-48;
//    std::cout << "Start: " << init_x << " " << init_y << std::endl;

    std::getline(f, tmp);  // # End: line
    std::getline(f, tmp);  // actual end cell
    end_x = (float)(tmp[1])-48;  // coordinates of exit cell
    end_y = (float)(tmp[3])-48;
//    std::cout << "End: " << end_x << " " << end_y << std::endl;

    std::getline(f, tmp);  // # Cells: line

    while (!f.eof()) {
        Cell *c_base = new Cell(0,0);
        f >> *c_base;
        std::pair<int,int>c_xy (c_base->m_x, c_base->m_y);   // instantiate the pair for future reference

        int nb_neighors = f.get() - 48;  // gets number of neighburs to iterate over them later and move pointer
        std::list<std::pair<int,int>> neighbours;

        Cell *c = new Cell(0,0);  // temporary cell to get cells from file
        for (int i = 0; i < nb_neighors; i++) {
            f >> *c;
            neighbours.push_back(std::make_pair(c->m_x, c->m_y)); // store coordinates on neighbours list
        }
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        m_cells[c_xy] = std::make_pair(c_base, neighbours);
    }
    f.close();

    // creates maze
    Maze maze = create_maze(m_cells[std::make_pair(init_x, init_y)].first, m_cells[std::make_pair(end_x, end_y)].first); // sets root and finish cell

    for (auto it = m_cells.begin(); it != m_cells.end(); it++) {
//        std::cout << std::endl << "(" << it->first.first << "," << it->first.second << ") " << std::endl;;
//        std::cout << " -> Cell = " << it->second.first->toString() << std::endl;
//        std::cout << " -> Neighbours = ";
        for (auto it2 = it->second.second.begin() ; it2 != it->second.second.end(); it2++) {
//            std::cout << ": (" << it2->first << "," << it2->second << ") ";
            Cell::add_neighb(it->second.first, m_cells[std::make_pair(it2->first, it2->second)].first);
        }
    }

    return maze;
}

void save_cells(Cell* cell, std::ofstream *f) {
    cell->m_saved = true;  // checks that the current cell is saved

    *f << *cell;  // saves the cell
    *f << std::to_string(cell->m_nb_neighb);  // saves the number of neighbors

    for(int i = 0 ; i < cell->m_nb_neighb ; i++) {  // saves all of the neighbors
        *f << *(cell->m_neighb[i]);
    }
    *f << std::endl;

    for(int i = 0 ; i < cell->m_nb_neighb ; i++) {  // recursively call the saving function for
        if (!cell->m_neighb[i]->m_saved) {          // every neighbour that hasnt been saved yet
            save_cells(cell->m_neighb[i], f);
        }
    }
}

void save_maze(const Maze& maze, const std::string& file_name) {
    std::ofstream f(file_name);  // open the file

    if (!f.is_open()) {  // test if file opening failed
        std::cout << "Error opening file " << file_name << std::endl;
        return;

    } else {
        // write starting lines of the file with start and end cells
        f << "# Start:" << std::endl;
        f << *maze.init << std::endl;
        f << "# End:" << std::endl;
        f << *maze.init << std::endl;

        f << "# Cells:" << std::endl;
        Cell *cell = maze.init;  // gets starting cell of the maze
        save_cells(cell, &f);    // start saving the cells by the initial cell
    }

    f.close();
}

bool compare_cells(const Cell *c1, const Cell *c2) {
    return (c1->m_x == c2->m_x && c1->m_y == c2->m_y);
}

bool find_path(Cell *c, Cell *cf, Path *path) {
    if (compare_cells(c, cf)) {  // tests if current cell if the desired one
        path->add_to_path(cf);
        return true;
    } else {
        Cell * c_curr;
        for (int i=0; i<c->m_nb_neighb; i++) {
            c_curr = c->m_neighb[i];
            if (c_curr->m_explored == true)
                continue;
            else {
                c_curr->m_explored = true;
                path->add_to_path(c);
                return find_path(c->m_neighb[i], cf, path);
            }
        }
    }

    return false;
}

void draw_gate(const Cell *n1, const Cell *n2) {  // two immutable cells by reference
    vibes::drawBox(std::min(n1->m_x, n2->m_x) + 0.1, std::max(n1->m_x, n2->m_x) + 0.9, // the limits of the gate
                   std::min(n1->m_y, n2->m_y) + 0.1, std::max(n1->m_y, n2->m_y) + 0.9, // are the outmost elements
                   "lightGray[lightGray]");                                            // in each direction
}

void display_graph(Cell *cell) {
    // draws the box surrounding the cell
    vibes::drawBox(cell->m_x, cell->m_x + 1, cell->m_y, cell->m_y + 1, "[lightGray]");

    cell->m_displayed = true;

    for(int i = 0 ; i < cell->m_nb_neighb ; i++) {
        if(!cell->m_neighb[i]->m_displayed)  // calls the display function for every neighbour that hasn't been
            display_graph(cell->m_neighb[i]);  // displayed yed, effectively reaching every cell in the graph

        draw_gate(cell, cell->m_neighb[i]);
    }
}

void display(Maze m) {
    display_graph(m.init);
    vibes::drawCircle(m.init->m_x+0.5, m.init->m_y+0.5, 0.3, "darkGreen[darkGreen]");
    vibes::drawCircle(m.exit->m_x+0.5, m.exit->m_y+0.5, 0.3, "organge[orange]");

}

Maze create_maze(Cell *init, Cell *exit) {
    Maze maze;
    maze.init = init;
    maze.exit = exit;
    return maze;
}
