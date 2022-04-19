#pragma once
#include "cgal.h"

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/algorithm.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Search_traits_3.h>
typedef CGAL::Simple_cartesian<double>                K;
typedef K::Point_3                                    Point_d;
typedef CGAL::Search_traits_3<K>                      Traits;
typedef CGAL::Fuzzy_sphere<Traits>                    Fuzzy_circle;
typedef CGAL::Kd_tree<Traits>                         Tree;

inline void cgal_pointcloud_boolean_difference(CGAL::Point_set_3<IK::Point_3>& cgal_cloud_0, CGAL::Point_set_3<IK::Point_3>& cgal_cloud_1, CGAL::Point_set_3<IK::Point_3>& cgal_cloud_result, double radius = 2)
{

    Tree tree;

    for (auto& p : cgal_cloud_0.points()) {
        Point_d point(p.x(), p.y(), p.z());
        tree.insert(point);
    }
	

    cgal_cloud_result.reserve(cgal_cloud_1.size());
	
    for (auto& point : cgal_cloud_1.points()) {

        Point_d center(point.hx(), point.hy(), point.hz());

        Fuzzy_circle default_range(center, radius);
        std::list<Point_d> result;
        tree.search(std::back_inserter(result), default_range);

        if (result.size() == 0) {
            cgal_cloud_result.insert(point);
         }
        
    }
 
}