// program includes
#include <iostream>                 // std::cout
#include <CGAL/Polygon_2.h>         // CGAL::Polygon_2<K>
#include <CGAL/convex_hull_2.h>     // CGAL::convex_hull_2
#include <fstream>                  // std::ifstream
#include <sstream>                  // std::ifstream
#include <ctime>                    // for random seed


// kernel setup
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef K::Triangle_2 Triangle_2;
typedef CGAL::Polygon_2<K> Polygon_2;


// vectors and iterators
typedef std::vector<Point_2> Points;


// new stuff
#include <CGAL/CORE_BigInt.h>


//#include <CGAL/CORE_BigInt.h>
//CORE::BigInt
typedef int NUM;

// find inner points = points - points on CH
void find_inner_points(const Points& points, const Points& CH, Points& inner_points) {
    for (const Point_2& p:points) {
        int check=1;
        for (const Point_2& p_ch:CH) {
            if (p==p_ch) {
                check=0;
                break;
            }
        } 
        if (check==1)
            inner_points.push_back(p);
    }
}

// from a set of points find the one closest to the given edge
Point_2 point_closest_to_edge(const Segment_2& e,const Points& points) {
    Point_2 closest_point = points[0];
    NUM min_distance = CGAL::squared_distance(e,points[0]); 

    for (const Point_2& p:points) {
        NUM distance = CGAL::squared_distance(e,p);
        if ( distance < min_distance ){
            min_distance = distance;
            closest_point=p;
        }
    }
    
    return closest_point;
}

// choose index of point - 0: random, 1: min area, 2: max area
int choose_index(const Points& points,const std::vector<NUM>& areas,int c){
    int i;
    switch(c) {
        case 0:
            std::srand(std::time(0));
            i = std::rand()%points.size();
            break;
        case 1:
            i = std::distance(std::begin(areas), std::min_element(std::begin(areas), std::end(areas)));
            break;
        case 2:
            i = std::distance(std::begin(areas), std::max_element(std::begin(areas), std::end(areas)));
            break;
    }
    return i;
}

// read input file from path and extract points and ch_area
void read_data(const std::string& path, Points& points, NUM& ch_area) {
    // open file to read
    std::ifstream input_file(path);

    // read file line by line
    std::string line;
    int i=0;
    while (std::getline(input_file, line))
    {
        // 2nd line has ch_area
        if (i==1) {
            
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
        i++;
    }

    input_file.close();
}

// save points to file at path
void save_points_to_file(const Points& points, const std::string& path){
    std::ofstream outfile(path);

    for (const Point_2& p:points) 
        outfile << p << std::endl;

    outfile.close();
}

// print points 
void print_points(const Points& points) {
    for (const Point_2& p:points) 
        std::cout << p << std::endl; 
}

int main() {
    std::cout<<"AAAAAAA";

    std::string path="euro-night-0000100.instance";
    Points points;
    NUM ch_area;

    read_data(path,points,ch_area);
/*
    // vis - paths for saving
    std::string vis_points="visualisation/points";
    std::string vis_poly_line="visualisation/vis_poly_line";
    std::string vis_closest="visualisation/closest";

    // vis - save points
    save_points_to_file(points,path);
*/

    // calculate CH
    Polygon_2 CHp;
    Points CH;
    CGAL::convex_hull_2( points.begin(), points.end(), std::back_inserter(CH) );

    // print CH and add point to CHp
    std::cout<<"\nCH:\n";
    int j=0;
    for (auto it=CH.begin(); it!=CH.end(); ++it) {
        CHp.push_back(*it);
        std::cout << j++ <<" "<< *it << std::endl;
    }

    // print area of CH
    std::cout << std::fixed <<"area = "<< CHp.area() << std::endl;

    // find inner points
    Points inner_points;

    find_inner_points(points,CH,inner_points);

    std::cout << "points: " << points.size() << ", CH: " << CH.size() << ", inner: " << inner_points.size() << std::endl;

    Points closest_points;
    std::vector<NUM> areas;

    // find closest point to each edge and area of created triangle
    for(const Segment_2& e : CHp.edges()) {
        Point_2 closest_point = point_closest_to_edge(e,inner_points);
        NUM area = Triangle_2(e.source(),e.target(),closest_point).area();
        areas.push_back(area);
        closest_points.push_back(closest_point);
    }

    // print closest points and areas
    std::cout<<"Closest Points:\n";
    for (int i=0; i<closest_points.size(); i++)
        std::cout << i << " " << closest_points[i] << " " << areas[i] << std::endl; 

    int chosen_index=choose_index(closest_points,areas,2);
    std::cout << choose_index(closest_points,areas,0) << std::endl; 
    std::cout << choose_index(closest_points,areas,1) << std::endl; 
    std::cout << choose_index(closest_points,areas,2) << std::endl; 

    // insert new point in polygon
    CHp.insert(CHp.vertices_begin()+chosen_index+1,closest_points[chosen_index]);
    if (CHp.vertices_begin()+chosen_index == CHp.vertices_end()) 
        CHp.push_back(closest_points[chosen_index]);
    else
        CHp.insert(CHp.vertices_begin()+chosen_index+1,closest_points[chosen_index]);

    // print new polygon
    std::cout<<"\nCH:\n";
    for (auto it=CHp.begin(); it!=CHp.end(); ++it) 
        std::cout << *it << std::endl;

}

