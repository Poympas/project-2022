#include "io_manip.hpp"

/*
Reads points and convex hull area from path. Expected format of input is:
    <line describing point set>
    parameters "convex_hull": {"area": "x"} // where x is the ch area
    0 x0 y0
    1 x1 y1
    ...
    n-1 xn yn
*/ 
void io_manip::read_data(const std::string& path, Points& points, NUM& ch_area) {
    // open file to read
    std::ifstream input_file(path);
    
    if (!input_file.good()) {
        std::cout<<"input file: "<<path<<" does not exist.\n";
        exit(1);
    }

    // read file line by line
    std::string line;
    int i=0;
    while (std::getline(input_file, line))
    {
        // 2nd line has ch_area
        if (i==1) {
            // convert read string to stringstream
            std::stringstream convestsion_stream;
            std::string ch_area_str = line.substr(38,line.size()-2-38);
            convestsion_stream << ch_area_str;
            // then convert the stringstream to NUM to handle greater values
            convestsion_stream >> ch_area;
        }
        // starting from the 3d line
        else if (i>=2) {
            std::string item;            
            std::stringstream ss_line(line);
            std::vector<std::string> vals;

            // separate values by tab
            while (std::getline(ss_line, item, '\t'))    
                vals.push_back(item);

            // insert new point from vals[1] and vals[2] (vals[0] is an index)
            points.push_back(Point_2(stoi(vals[1]),stoi(vals[2])));
        }
        // increase line counter number
        i++;
    }

    // close read file
    input_file.close();
}