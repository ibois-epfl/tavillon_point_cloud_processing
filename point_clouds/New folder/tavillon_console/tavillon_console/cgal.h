#pragma once
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <boost/exception/diagnostic_information.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>

//CGAL
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Intersections.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Plane_3.h>
#include <iostream>
#include <fstream>
#include <CGAL/Boolean_set_operations_2.h>
#include <list>
#include <CGAL/Random.h>
#include <CGAL/Real_timer.h>

//meshing 2D
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Polygon_2.h>

//closest polylines
#include <CGAL/box_intersection_d.h>
#include <CGAL/Iterator_range.h>
#include <CGAL/tuple.h>

#include <CGAL/boost/iterator/counting_iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator/function_output_iterator.hpp>
#include <boost/graph/properties.hpp>

#include <cmath>
#include <string>
#include <chrono>

//Pointclouds
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Point_set_3/IO.h>
#include <CGAL/cluster_point_set.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/draw_point_set_3.h>


using EK = CGAL::Exact_predicates_exact_constructions_kernel;
using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point_3 = Kernel::Point_3;
using Point_set = CGAL::Point_set_3<Point_3>;
//typedef CGAL::Cartesian_converter<IK, EK> IK_to_EK;
//typedef CGAL::Cartesian_converter<EK, IK> EK_to_IK;
//using CGAL_Polyline = std::vector<IK::Point_3>;
//using CGAL_Polylines = std::list<CGAL_Polyline>;
//typedef typename CGAL::Box_intersection_d::Box_with_info_d<double, 3, std::pair<std::size_t, std::size_t> > Box;