// program includes
#include <iostream>                 // std::cout

#include "includes/io_manip/io_manip.hpp"
#include "includes/poly_incremental/poly_incremental.hpp" 

int main() {
    // should be input
    std::string path="euro-night-0000100.instance";
    bool vis=false; // visualisation
    bool vis_min=false; // minimal visualisation, points and final poly line
    int edge_selection = 3;  // 1,2,3 -> random, min, max
    int initialization = 3;  // 1,2,3,4 -> sort x, srot x reverse, sort y, sort y reverse

    Points points;
    Polygon_2 poly_line;
    NUM ch_area;
    NUM poly_area;

    io_manip::read_data(path,points,ch_area);
    poly_incremental::run(points,initialization,edge_selection,poly_line,poly_area);

    std::cout<<poly_line.is_simple()<<" "<<poly_line.size()<<std::endl;
    std::cout<<std::fixed<<CGAL::abs(poly_line.area())<<" "<<poly_area<<std::endl;
}



