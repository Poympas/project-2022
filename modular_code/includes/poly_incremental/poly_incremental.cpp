#include "poly_incremental.hpp"

// dunno why but i get undefined references on visibility otherwise
#include "../visibility/visibility.cpp"

// definition of static variables
int poly_incremental::edge_selection; 
int poly_incremental::initialization; 
bool poly_incremental::vis;           
bool poly_incremental::vis_min;       

// also set visualisation paths
int poly_incremental::vis_counter;
std::string poly_incremental::vis_points="visualisation/points";
std::string poly_incremental::vis_ch="visualisation/ch_";
std::string poly_incremental::vis_visible="visualisation/visible_";
std::string poly_incremental::vis_poly_line="visualisation/poly_line_";
std::string poly_incremental::vis_visible_poly="visualisation/visible_poly_";

// step of ch_bb
void poly_incremental::bb_inc_step(const Point_2& next_point,
                                   Polygon_2& ch_bb,
                                   Polygon_2& poly_line,
                                   int& last_point_i,
                                   NUM& poly_area){
        
        
   // get size of ch_bb
   int size=ch_bb.size();
   // get last point from given index
   Point_2 last_point=ch_bb[last_point_i];
   
   // check points turning right
   int right_i=last_point_i;
   Segment_2 right_edge(ch_bb[right_i],ch_bb[(right_i+1)%size]);
   
   while (visibility::is_visible_p_from_e(next_point,right_edge,ch_bb)){
         //draw_edge(right_edge)
         right_i=(right_i+1)%size;
         right_edge=Segment_2(ch_bb[right_i],ch_bb[(right_i+1)%size]);
   }

   // check points turning left
   int left_i=last_point_i;
   Segment_2 left_edge(ch_bb[(left_i-1)%size],ch_bb[left_i]);

   while (visibility::is_visible_p_from_e(next_point,left_edge,ch_bb)){
         //draw_edge(left_edge)
         left_i=(left_i-1)%size;
         left_edge=Segment_2(ch_bb[(left_i-1)%size],ch_bb[left_i]);
   }

   // vis - save visible points on ch
   if(vis) {
         int visible_points_count=right_i-left_i+1;
         Points visible_points;
         for(int i=0;i<visible_points_count;i++){
            int index=(left_i+i)%size;
            visible_points.push_back(ch_bb[index]);
         }
         io_manip::save_points_to_file(visible_points,vis_visible+std::to_string(vis_counter));
   }

   // find the "red" edges on the poly line and update poly_line
   /////////////////////////////////////////////////////////////////////////////////
   
   // first find index of point at poly_line that is equal to ch_bb[left_i]
   int poly_left_i;
   for (int i=0; i<poly_line.size(); i++)
         if (ch_bb[left_i] == poly_line[i]) {
            poly_left_i=i;
            break;
         }

   // traverse poly line until the point equal to ch_bb[right_i] and save edges
   Edges edges;
   int poly_i=poly_left_i;
   do {
         int next_poly_i=(poly_i+1)%poly_line.size();
         Segment_2 edge(poly_line[poly_i],poly_line[next_poly_i]);
         edges.push_back(edge);
         poly_i=next_poly_i;
   } while (poly_line[poly_i] != ch_bb[right_i]);

   // check which edges are visible from next_point and calculate area
   std::vector<bool> visibility_vec;
   std::vector<NUM> areas;

   for(const Segment_2& edge:edges) {
         NUM area = CGAL::abs(Triangle_2(edge.source(),edge.target(),next_point).area());
         areas.push_back(area);
         visibility_vec.push_back(visibility::is_visible_p_from_e(next_point,edge,poly_line));
   }

   // choose next index to insert - edge_selection = 1,2,3 -> random, min, max
   int chosen_index=visibility::choose_index(visibility_vec,areas,edge_selection);

   // find acctual index on poly_line
   int poly_index=(poly_left_i+chosen_index)%poly_line.size();

   // insert next point in poly_line
   if (poly_line.vertices_begin()+poly_index == poly_line.vertices_end()) 
         poly_line.push_back(next_point);
   else
         poly_line.insert(poly_line.vertices_begin()+poly_index+1,next_point);
   
   // update area
   poly_area+=areas[chosen_index];
   
   // vis - save visible edges on poly line
   if(vis) io_manip::save_points_and_vis_to_file(edges,visibility_vec,vis_visible_poly+std::to_string(vis_counter));

   /////////////////////////////////////////////////////////////////////////////////

   // continue with ch_bb

   // remove points from ch
   int remove_count=right_i-left_i-1;
   int index;
   for(int reps=0;reps<remove_count;reps++) {
         index=(left_i+1)%ch_bb.size(); 
         ch_bb.erase(ch_bb.begin()+index);
   }

   // and add new point to ch
   index=(left_i+1)%ch_bb.size(); 
   ch_bb.insert(ch_bb.begin()+index,next_point);

   // vis - increase vis_counter and save new ch
   if(vis) vis_counter++;
   if(vis) io_manip::save_points_to_file(ch_bb,vis_ch+std::to_string(vis_counter));
   if(vis) io_manip::save_points_to_file(poly_line,vis_poly_line+std::to_string(vis_counter));

   // set last_point_i as the index where the last point was inserted at ch
   last_point_i=index;
}


void poly_incremental::run(const Points& points, 
                           const int& initialization, 
                           const int& edge_selection, 
                           Polygon_2& poly_line,
                           NUM& poly_area,
                           const bool& vis,
                           const bool& vis_min) {

    // initialize parameters
    poly_incremental::vis_counter=0;
    poly_incremental::vis=vis; 
    poly_incremental::vis_min=vis_min;
    poly_incremental::edge_selection = edge_selection;  
    poly_incremental::initialization = initialization; 


    // initialize rest of points to be added to poly_line, as the given points
    Points rest_of_points;
    for (const Point_2& p:points)
        rest_of_points.push_back(p);

    // initialise rest of points by sorting
    if (initialization==1 || initialization==2){
        std::stable_sort(rest_of_points.begin(), rest_of_points.end());
        if(initialization==2)
            std::reverse(rest_of_points.begin(), rest_of_points.end());
    }
    if (initialization==3 || initialization==4){
        struct YCopmare {
            bool operator() (Point_2 p1, Point_2 p2) { return (p1.y() < p2.y());}
        } yCompare;
        std::stable_sort(rest_of_points.begin(), rest_of_points.end(), yCompare);
        if(initialization==4)
            std::reverse(rest_of_points.begin(), rest_of_points.end());
    }

    // vis - create visualisation directory and save points
    if(vis || vis_min)  mkdir("visualisation",0777);
    if(vis || vis_min) io_manip::save_points_to_file(rest_of_points,vis_points);

    // create poly line, ch_bb - both start as first triangle
    Polygon_2 ch_bb;
    for (int i=0;i<3;i++) {
        poly_line.push_back(rest_of_points[0]);
        ch_bb.push_back(rest_of_points[0]);
        rest_of_points.erase(rest_of_points.begin());
    }

    // calculate area of first triangle
    poly_area = CGAL::abs(poly_line.area());
    // vis - save ch_bb
    if(vis) io_manip::save_points_to_file(ch_bb,vis_ch+std::to_string(vis_counter));
    if(vis) io_manip::save_points_to_file(poly_line,vis_poly_line+std::to_string(vis_counter));

    // index of last inserted point
    int last_point_i=2;

    // incremental algorithm loop
    int max_reps = rest_of_points.size();
    for (int reps=0; reps<max_reps; reps++) {
        Point_2 next_point = rest_of_points[0];      

        bb_inc_step(next_point,
                    ch_bb,
                    poly_line,
                    last_point_i,
                    poly_area);

        rest_of_points.erase(rest_of_points.begin());
    }
    
    // vis - save final poly_line and ch
    if(vis_min) io_manip::save_points_to_file(ch_bb,vis_ch);
    if(vis_min) io_manip::save_points_to_file(poly_line,vis_poly_line);
}
