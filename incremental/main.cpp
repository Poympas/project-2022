// program includes
#include <iostream>                 // std::cout
#include <CGAL/Polygon_2.h>         // CGAL::Polygon_2<K>
#include <CGAL/convex_hull_2.h>     // CGAL::convex_hull_2
#include <fstream>                  // std::ifstream
#include <sstream>                  // std::ifstream
#include <ctime>                    // for random seed
#include <boost/optional/optional_io.hpp>       // for are_intersecting(...)

#include <algorithm>                // for sorting

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


// CS = Choice Strategy
enum CS { RANDOM, MIN, MAX };

// find inner points = points - points on CH
template <typename Point_container> // Points or Polygon_2
void find_inner_points(const Points& points, const Point_container& CH, Points& inner_points) {
    // for each point
    for (const Point_2& p:points) {
        bool check=true;
        // check if it is equal to one of the point on the CH
        for (const Point_2& p_ch:CH) {
            if (p==p_ch) {
                check=false;
                break;
            }
        } 
        // if not check remains one so add it to inner points
        if (check)
            inner_points.push_back(p);
    }
}

// from a set of points find the one closest to the given edge
void point_closest_to_edge(const Segment_2& e,const Points& points, Point_2& closest_point, int& closest_i) {
    closest_point = points[0];
    closest_i = 0;
    NUM min_distance = CGAL::squared_distance(e,points[0]); 

    // run through all points and find min distance and point
    int i=0;
    for (const Point_2& p:points) {
        NUM distance = CGAL::squared_distance(e,p);
        if ( distance < min_distance ){
            min_distance = distance;
            closest_point=p;
            closest_i=i;
        }
        i++;
    }
}

// choose index of point - 0: random, 1: min area, 2: max area
int choose_index(const Points& points,const std::vector<bool>& visibility,const std::vector<NUM>& areas,CS cs){
    // only choose from points that are visible from their respective edge
    std::vector<int> visible_indexes;
    std::vector<int> visible_areas;

    // select visible indexes and areas
    for (int i=0; i<visibility.size(); i++) {
        if (visibility[i]) {
            visible_indexes.push_back(i);
            visible_areas.push_back(areas[i]);
        }
    }

    int i;
    switch(cs) {
        case CS::RANDOM: // random pick
            std::srand(std::time(0));
            i = std::rand()%visible_indexes.size();
            break;
        case CS::MIN: // min area
            i = std::distance(std::begin(visible_areas), std::min_element(std::begin(visible_areas), std::end(visible_areas)));
            break;
        case CS::MAX: // max area
            i = std::distance(std::begin(visible_areas), std::max_element(std::begin(visible_areas), std::end(visible_areas)));
            break;
    }

    return visible_indexes[i];
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
            ch_area = stoi(line.substr(38,line.size()-2-38));
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
template <typename Point_container> // Points or Polygon_2
void save_points_to_file(const Point_container& points, const std::string& path){
    std::ofstream outfile(path);

    for (const Point_2& p:points)
        outfile << p << std::endl;

    outfile.close();
}

// save points to file at path - uses visibility
template <typename Point_container> // Points or Polygon_2
void save_points_to_file(const Point_container& points,const std::vector<bool>& visibility, const std::string& path){
    std::ofstream outfile(path);

    for (int i=0; i<points.size(); i++){
        if (visibility[i])
            outfile << points[i] << std::endl;
        else
            outfile << "NOT_VISIBLE" << std::endl;
    } 

    outfile.close();
}

// print points 
template <typename Point_container> // Points or Polygon_2
void print_points(const Point_container& points) {
    for (const Point_2& p:points) 
        std::cout << p << std::endl; 
}

// check if two segments are intersecting
bool are_intersecting(Segment_2 seg1, Segment_2 seg2) {
    auto inter = intersection(seg1,seg2);

    // intersection handling
    if (inter) {
        // intresection is point
        if (const Point_2 *p = boost::get<Point_2>(&*inter)){
            // we dont care if intersection is at the defining points of the edges
            if (*p==seg1.source() || *p==seg1.target() || *p==seg2.source() || *p==seg2.target())
                return false;
            // intersection inside the edges - return true
            else 
                return true;
        } 
        // intersection is segment - this shouldn't happen - i guess?
        else {
            const Segment_2 *s = boost::get<Segment_2>(&*inter);
            std::cout << "LOOK AT ME!!! - Intersection is segment: " << inter << "\n";
            return true;
        }
    // no intersection return false
    } else {
        return false;
    }
}

// check if a point is visible from an edge, given a polygon to block visibility
bool is_visible_p_from_e(const Point_2& point, const Segment_2& edge, const Polygon_2& poly_line) {
    // suppose edge is visible
    bool is_visible=true;

    // create e1,e2,e3 - segment from point and edge source, target, midpoint
    Point_2 p1(edge.source()), p2(edge.target());
    Segment_2 e1(point,p1), e2(point,p2), e3(point,CGAL::midpoint(edge));

    // for each edge e of poly_line
    for(const Segment_2& e : poly_line.edges()){
        // if e is equal to the edge we are checking for visibility -> skip it
        if (e==edge) continue;
        // if e1,e2 or e3 is intersecting with e, return false
        if (are_intersecting(e,e1) || are_intersecting(e,e2) || are_intersecting(e,e3))
            return false;
    }

    // e1,e2 and e3 intersect with no edge of the poly -> return true
    return true;
}

// insert new closest_point, area, visibility, inner_point_i of edge with index i
void ch_to_poly_insert(const int& i,
                       const Polygon_2& poly_line,   
                       const Points& inner_points,
                       Points& closest_points, 
                       std::vector<NUM>& areas, 
                       std::vector<bool>& visibility, 
                       std::vector<int>& inner_points_i 
                     ){
    Segment_2 e = *(poly_line.edges_begin()+i);

    // closest point
    Point_2 closest_point;
    int inner_i;
    point_closest_to_edge(e,inner_points,closest_point,inner_i);
    closest_points.insert(closest_points.begin()+i,closest_point);
    inner_points_i.insert(inner_points_i.begin()+i,inner_i);

    // triangle area
    NUM area = Triangle_2(e.source(),e.target(),closest_point).area();
    areas.insert(areas.begin()+i,area);

    // visibility check
    visibility.insert(visibility.begin()+i,is_visible_p_from_e(closest_point,e,poly_line));
}

// update closest_point, area, visibility, inner_point_i of edge with index i
void ch_to_poly_update(const int& i,
                       const Polygon_2& poly_line,   
                       const Points& inner_points,
                       Points& closest_points, 
                       std::vector<NUM>& areas, 
                       std::vector<bool>& visibility, 
                       std::vector<int>& inner_points_i 
                     ){
    Segment_2 e = *(poly_line.edges_begin()+i);

    // closest point
    Point_2 closest_point;
    int inner_i;
    point_closest_to_edge(e,inner_points,closest_point,inner_i);
    closest_points[i]=closest_point;
    inner_points_i[i]=inner_i;

    // triangle area
    NUM area = Triangle_2(e.source(),e.target(),closest_point).area();
    areas[i]=area;

    // visibility check
    visibility[i]=is_visible_p_from_e(closest_point,e,poly_line);
}

// compare on y
struct YCopmare {
    bool operator() (Point_2 p1, Point_2 p2) { return (p1.y() < p2.y());}
} yCompare;



bool vis=true; // visualisation
bool vis_min=false; // minimal visualisation, points and final poly line

// vis - paths for saving
int vis_counter=0;
std::string vis_points="visualisation/points";
std::string vis_ch="visualisation/ch_";
std::string vis_visible="visualisation/visible_";

// step of ch_bb
void bb_step(const Point_2& next_point,Polygon_2& ch_bb,int& last_point_i){
    // get size of ch_bb
    int size=ch_bb.size();
    // get last point from given index
    Point_2 last_point=ch_bb[last_point_i];
    
    int right_i=last_point_i;
    Segment_2 right_edge(ch_bb[right_i],ch_bb[(right_i+1)%size]);
    
    // check points turning right
    while (is_visible_p_from_e(next_point,right_edge,ch_bb)){
        //draw_edge(right_edge)
        right_i=(right_i+1)%size;
        right_edge=Segment_2(ch_bb[right_i],ch_bb[(right_i+1)%size]);
    }

    int left_i=last_point_i;
    Segment_2 left_edge(ch_bb[(left_i-1)%size],ch_bb[left_i]);

    // check points turning left
    while (is_visible_p_from_e(next_point,left_edge,ch_bb)){
        //draw_edge(left_edge)
        left_i=(left_i-1)%size;
        left_edge=Segment_2(ch_bb[(left_i-1)%size],ch_bb[left_i]);
    }

    // vis - save visible points
    if(vis) {
        int visible_points_count=right_i-left_i+1;
        Points visible_points;
        for(int i=0;i<visible_points_count;i++){
            int index=(left_i+i)%size;
            visible_points.push_back(ch_bb[index]);
        }
        save_points_to_file(visible_points,vis_visible+std::to_string(vis_counter));
    }

    // remove points
    int remove_count=right_i-left_i-1;
    int index;
    for(int reps=0;reps<remove_count;reps++) {
        index=(left_i+1)%ch_bb.size(); 
        ch_bb.erase(ch_bb.begin()+index);
    }

    //  and add new point
    index=(left_i+1)%ch_bb.size(); 
    ch_bb.insert(ch_bb.begin()+index,next_point);

    // vis - increase vis_counter and save new ch
    if(vis) vis_counter++;
    if(vis) save_points_to_file(ch_bb,vis_ch+std::to_string(vis_counter));

    // set last_point_i as the index where the last point was inserted
    last_point_i=index;
}

int main() {
    
    // should be input
    std::string path="euro-night-0000050.instance";
    int edge_selection = 1;  // 1,2,3 -> random, min, max
    int initialization = 4;  // 1,2,3,4 -> sort x, srot x reverse, sort y, sort y reverse

    // read data from path
    Points rest_of_points;
    NUM poly_area;

    read_data(path,rest_of_points,poly_area);

    // initialise point by sorting
    if (initialization==1 || initialization==2){
        std::stable_sort(rest_of_points.begin(), rest_of_points.end());
        if(initialization==2)
            std::reverse(rest_of_points.begin(), rest_of_points.end());
    }
    if (initialization==3 || initialization==4){
        std::stable_sort(rest_of_points.begin(), rest_of_points.end(), yCompare);
        if(initialization==4)
            std::reverse(rest_of_points.begin(), rest_of_points.end());
    }

    // vis - save points
    if(vis || vis_min) save_points_to_file(rest_of_points,vis_points);

    // create poly line, ch_bb - both start as first triangle
    Polygon_2 poly_line;
    Polygon_2 ch_bb;
    for (int i=0;i<3;i++) {
        poly_line.push_back(rest_of_points[0]);
        ch_bb.push_back(rest_of_points[0]);
        rest_of_points.erase(rest_of_points.begin());
    }

    // vis - save ch_bb
    if(vis) save_points_to_file(ch_bb,vis_ch+std::to_string(vis_counter));

    // index of last inserted point
    int last_point_i=2;

    // incremental algorithm loop
    int max_reps = rest_of_points.size();
    for (int reps=0; reps<max_reps; reps++) {
        Point_2 next_point = rest_of_points[0];      
        bb_step(next_point,ch_bb,last_point_i);
        rest_of_points.erase(rest_of_points.begin());
    }

    if(vis_min) save_points_to_file(ch_bb,vis_ch);
}



