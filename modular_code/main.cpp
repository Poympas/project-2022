// program includes
#include <iostream> // std::cout

#include "includes/io_manip/io_manip.hpp"                         // for read_data()
#include "includes/poly_line_algorithms/poly_line_algorithms.hpp" // polygonization algorithms

void process_input(int argc, 
                   char** argv, 
                   std::string& inpout_file,
                   std::string& output_file,
                   int& algorithm,
                   int& edge_selection,
                   int& init_inc,
                   int& init_onion,
                   bool& vis,
                   bool& vis_min);

std::string create_output(const Polygon_2& poly_line,
                          const NUM& poly_area,
                          const NUM& pick_area,
                          const NUM& ch_area,
                          const NUM& time,
                          const int& algorithm,
                          const int& edge_selection,
                          const int& init_inc,
                          const int& init_onion) {

    std::string output_string;

    output_string += "Polygonization\n";

    // write points
    for (const Point_2& p:poly_line) 
       output_string += std::to_string((NUM)p.x())+" "+std::to_string((NUM)p.y())+"\n";
    
    // write edges
    for (const Segment_2& e:poly_line.edges()) {
        Point_2 p1=e.source(), p2=e.target();
        output_string +=  std::to_string((NUM)p1.x())+" "+std::to_string((NUM)p1.y())+" "+std::to_string((NUM)p2.x())+" "+std::to_string((NUM)p2.y())+"\n";
    }

    // write algorithm
    output_string += "Algorithm: ";
    switch(algorithm) {
        case 1:
            output_string += "incremental";
            //write edges
            output_string += "_edge_selection_" + std::to_string(edge_selection);
            output_string += "_initialization_";
            //write init_inc
            switch(init_inc) {
                case 1: output_string += "1b"; break;
                case 2: output_string += "1a"; break;
                case 3: output_string += "2b"; break;
                case 4: output_string += "2a"; break;
            }
            break;
        case 2:
            output_string += "convex_hull";
            //write edges
            output_string += "_edge_selection_" + std::to_string(edge_selection);
            break;
        case 3:
            output_string += "onion";
            //write init_onion
            output_string += "_initialization_" + std::to_string(init_onion);
            break;
    }
    output_string += "\n";

    // write area, pick, ratio, time
    output_string += "area: " + std::to_string(poly_area) + "\n";
    output_string += "pick_calculated_area: " + std::to_string(pick_area) + "\n";
    output_string += "ratio: " + std::to_string(poly_area*1.0/ch_area) + "\n";
    output_string += "construction time: " + std::to_string(time) + "\n";

    return output_string;
}

int main(int argc, char** argv) {
    std::string inpout_file;
    std::string output_file;
    int algorithm;
    int edge_selection;
    int init_inc;
    int init_onion;
    bool vis=false;    
    bool vis_min=false;  

    process_input(argc, argv, inpout_file, output_file, algorithm, edge_selection, init_inc, init_onion, vis, vis_min);

    Points points;
    NUM ch_area;
    io_manip::read_data(inpout_file,points,ch_area);

    Polygon_2 poly_line;
    NUM poly_area;
    NUM pick_area=-1;
    NUM time=-1;

    switch(algorithm){
        case 1:
            poly_line_algorithms::incremental(points,init_inc,edge_selection,poly_line,poly_area);
            break;
        case 2:
            poly_line_algorithms::convex_hull(points,edge_selection,poly_line,poly_area,ch_area);
            break;
        case 3:
            std::cout<<"Maybe next time\n";
            //poly_line_algorithms::onion(points,init_onion,poly_line,poly_area);
            break;
    }

    std::cout << create_output(poly_line, poly_area, pick_area, ch_area, time, algorithm, edge_selection, init_inc, init_onion);
}

void print_correct_use() {
    std::cout<<"\ngeneral use: ./to_polygon -i <input_file> -o <output_file> -algorithm <algorithm> -edge_selection <edge_selection> -initialization <initialization> -onion_initialization <onion_initialization> \n";
    std::cout<<"use1: ./to_polygon -i <input_file> -o <output_file> -algorithm <incremental> -edge_selection <1/2/3> \n";
    std::cout<<"use2: ./to_polygon -i <input_file> -o <output_file> -algorithm <convex_hull> -edge_selection <1/2/3> -initialization <1a/1b/2a/2b>\n";
    std::cout<<"use3: ./to_polygon -i <input_file> -o <output_file> -algorithm <onion> -onion_initialization <1/2/3/4/5> \n";
    std::cout<<"\n";
    std::cout<<"parameters: \n";
    std::cout<<"edge_selection: 1/2/3 -> random, min area, max area\n";
    std::cout<<"initialization: 1a/1b/2a/2b -> sort x dec, x inc, y dec, y inc\n";
    std::cout<<"onion_initialization: 1/2/3/4/5 -> ch construction random pick, min x, max x, min y, max y\n\n";
    std::cout<<"Optionally add -vis <1/2> for full or minimal visualisation.\n\n";
}

// search an array of strings for str
// return position of str in strings, or -1 if not found
int find(const std::vector<std::string>& strings,const std::string& str) {
    for (int i=0; i<strings.size(); i++) 
        if (strings[i].compare(str)==0) return i;
    return -1;
}

// check and get input from arguments
// general use: ./to_polygon -i <input_file> -o <output_file> -algorithm <algorithm> -edge_selection <edge_selection> -initialization <initialization> -onion_initialization <onion_initialization>
// check if -i, -o, -algorithm, -edge_selection, -initialisation, -onion_initialization are present 
// and extract the corresponding values
// the paramaters do not need to be in that order
// specific parameters need to be present based on given algorithm
void process_input(int argc, 
                   char** argv, 
                   std::string& inpout_file,
                   std::string& output_file,
                   int& algorithm,
                   int& edge_selection,
                   int& init_inc,
                   int& init_onion,
                   bool& vis,
                   bool& vis_min) {

    // get arguments and convert them to strings
    std::vector<std::string> arguments;
    for (int i=1; i<argc; i++) {
        std::string arg;
        arg.assign(argv[i], strlen(argv[i]));
        arguments.push_back(arg);
    }

    /*
    search and set input vals to given variables
    */

    int loc;
    std::string arg;

    // input_file
    loc = find(arguments,"-i");
    if (loc != -1) {
        arg = arguments[loc+1];
        inpout_file = arg;
    } else {
        std::cout<<"\n\nInput Error: -i not found.\n\n";
        print_correct_use();
        exit(1);
    }

    // output_file
    loc = find(arguments,"-o");
    if (loc != -1) {
        arg = arguments[loc+1];
        output_file = arg;
    } else {
        std::cout<<"\n\nInput Error: -o not found.\n\n";
        print_correct_use();
        exit(1);
    }

    // algorithm   
    loc = find(arguments,"-algorithm");
    if (loc != -1) {
        arg = arguments[loc+1];
        if (arg.compare("incremental")==0) algorithm=1;
        else if (arg.compare("convex_hull")==0) algorithm=2;
        else if (arg.compare("onion")==0) algorithm=3;
        else {
            std::cout<<"\n\nInput Error: -algorithm = <incremental/convex_hull/onion>\n\n";
            print_correct_use();
            exit(1);
        }
    } else {
        std::cout<<"\n\nInput Error: -algorithm not found.\n\n";
        print_correct_use();
        exit(1);
    }

    // edge_selection, initialization, onion_initialization
    switch(algorithm) {
        case 1: // incremental only
            // initialization
            loc = find(arguments,"-initialization");
            if (loc != -1) {
                arg = arguments[loc+1];
                if (arg.compare("1a")==0) init_inc=2;
                else if (arg.compare("1b")==0) init_inc=1;
                else if (arg.compare("2a")==0) init_inc=4;
                else if (arg.compare("2b")==0) init_inc=3;
                else {
                    std::cout<<"\n\nInput Error: -initialization = <1a/ab/2a/2b>\n\n";
                    print_correct_use();
                    exit(1);
                }
            } else {
                std::cout<<"\n\nInput Error: -initialization not found.\n\n";
                print_correct_use();
                exit(1);
            }
            // no break here
        case 2: // convex hull and incremental
            // edge_selection
            loc = find(arguments,"-edge_selection");
            if (loc != -1) {
                arg = arguments[loc+1];
                if (arg.compare("1")==0) edge_selection=1;
                else if (arg.compare("2")==0) edge_selection=2;
                else if (arg.compare("3")==0) edge_selection=3;
                else {
                    std::cout<<"\n\nInput Error: -edge_selection = <1/2/3>\n\n";
                    print_correct_use();
                    exit(1);
                }
            } else {
                std::cout<<"\n\nInput Error: -edge_selection not found.\n\n";
                print_correct_use();
                exit(1);
            }
            break;
        case 3: // onion
        // onion_initialization
            loc = find(arguments,"-onion_initialization");
            if (loc != -1) { 
                arg = arguments[loc+1];
                if (arg.compare("1")==0) init_onion=1;
                else if (arg.compare("2")==0) init_onion=2;
                else if (arg.compare("3")==0) init_onion=3;
                else if (arg.compare("4")==0) init_onion=4;
                else if (arg.compare("5")==0) init_onion=5;
                else {
                    std::cout<<"\n\nInput Error: -initialization = <1a/ab/2a/2b>\n\n";
                    print_correct_use();
                    exit(1);
                }
            } else {
                std::cout<<"\n\nInput Error: -onion_initialization not found.\n\n";
                print_correct_use();
                exit(1);
            }
    }
    
    // vis
    loc = find(arguments,"-vis");
    if (loc != -1) {
        arg = arguments[loc+1];
        if (arg.compare("1")==0) vis=true;
        else if (arg.compare("2")==0) vis_min=true;
        else {
            std::cout<<"\n\nInput Error: -vis = <1/2>\n\n";
            print_correct_use();
            exit(1);
        }
    }

}

