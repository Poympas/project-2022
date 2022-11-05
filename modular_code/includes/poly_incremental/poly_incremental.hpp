#ifndef poly_incremental_hpp
#define poly_incremental_hpp

#include "../cgal_config/cgal_config.hpp"

#include "../visibility/visibility.hpp"
#include "../io_manip/io_manip.hpp"
#include <sys/stat.h>

class poly_incremental {
    private:
        static int edge_selection; // 1,2,3 -> random, min, max
        static int initialization; // 1,2,3,4 -> sort x, srot x reverse, sort y, sort y reverse
        static bool vis;           // visualisation
        static bool vis_min;       // minimal visualisation, points and final poly line

        // vis - paths for saving
        static int vis_counter;
        static std::string vis_points;
        static std::string vis_ch;
        static std::string vis_visible;
        static std::string vis_poly_line;
        static std::string vis_visible_poly;

        static void bb_inc_step(const Point_2& next_point,
                                Polygon_2& ch_bb,
                                Polygon_2& poly_line,
                                int& last_point_i,
                                NUM& poly_area);

    public:
        static void run(const Points& points, 
                        const int& initialization, 
                        const int& edge_selection, 
                        Polygon_2& poly_line,
                        NUM& poly_area,
                        const bool& vis=false,
                        const bool& vis_min=false);
};

#endif
