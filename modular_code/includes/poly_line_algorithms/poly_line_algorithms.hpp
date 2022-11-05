#ifndef poly_line_algorithms_hpp
#define poly_line_algorithms_hpp    

/*
This header file contains calls for algorithms that given a set of points
return a simple polygonal line passing through all the points.

Currently contains:
    1 - incremental algorithm
    2 - convex hull algorithm
    3 - onion algorithm (not yet)

This is supposed to be the main interface for the project.
*/

#include "../cgal_config/cgal_config.hpp"           // CGAL types
#include "../poly_incremental/poly_incremental.hpp" // incremental algorithm
#include "../poly_from_ch/poly_from_ch.cpp"         // convex hull algorithm

namespace poly_line_algorithms {
    
    // calls the incremental algorithm
    void incremental(const Points& points, 
                     const int& initialization, 
                     const int& edge_selection, 
                     Polygon_2& poly_line,
                     NUM& poly_area,
                     const bool& vis=false,
                     const bool& vis_min=false) {
    
        poly_incremental::run(points,initialization,edge_selection,poly_line,poly_area,vis,vis_min);
    }

    // calls the convex hull algorithm
    void convex_hull(const Points& points, 
                     const int& edge_selection, 
                     Polygon_2& poly_line,
                     NUM& poly_area,
                     const NUM& ch_area,
                     const bool& vis=false,
                     const bool& vis_min=false) {
    
        poly_from_ch::run(points,edge_selection,poly_line,poly_area,ch_area,vis,vis_min);
    }                       

}

#endif
