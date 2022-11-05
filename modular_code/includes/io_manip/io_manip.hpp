#ifndef io_manip_hpp
#define io_manip_hpp

#include <sstream> // std::ifstream

#include "../cgal_config/cgal_config.hpp"

namespace io_manip{

    void read_data(const std::string& path, Points& points, NUM& ch_area);

    // save points or segments to file at path 
    template <typename Container> // Points or Polygon_2 or Segments
    void save_points_to_file(const Container& container, const std::string& path){
        std::ofstream outfile(path);

        for (int i=0;i<container.size();i++)
            outfile << container[i] << std::endl;

        outfile.close();
    }

    // save points or segments and visibility to file at path 
    template <typename Container> 
    void save_points_and_vis_to_file(const Container& container, const std::vector<bool> visibility_vec, const std::string& path) {
       std::ofstream outfile(path);

        for (int i=0;i<container.size();i++)
            outfile << container[i] <<" "<<visibility_vec[i]<< std::endl;

        outfile.close();
    }

    // print points or segments
    template <typename Container>    
    void print_points(const Container& container){
        for (int i=0;i<container.size();i++)
            std::cout << container[i] << std::endl; 
    }

}

#endif
