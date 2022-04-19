// tavillon_console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "easy3d_pointcloud_viewer.h"
#include "cgal_pointcloud_processing.h"


int main()
{
	const std::string filename_0 = "C:\\IBOIS57\\_Code\\Software\\CPP\\tavillon_point_cloud_processing\\point_clouds\\Model1.ply";
	const std::string filename_1 = "C:\\IBOIS57\\_Code\\Software\\CPP\\tavillon_point_cloud_processing\\point_clouds\\Model2.ply";

	CGAL::Point_set_3<IK::Point_3> point_set_0;
	auto is_read_0 = CGAL::IO::read_point_set(filename_0, point_set_0);

	CGAL::Point_set_3<IK::Point_3> point_set_1;
	auto is_read_1 = CGAL::IO::read_point_set(filename_1, point_set_1);

	CGAL::Point_set_3<IK::Point_3> point_set_result;
	cgal_pointcloud_boolean_difference(point_set_0, point_set_1, point_set_result,3);
	

	easy3d::Viewer viewer = viewer_init();
	viewer_display_point_cloud(viewer, point_set_result, 0, 0, 0, 10);
	viewer_display_point_cloud(viewer, point_set_1, 1, 0.9, 0);
	viewer_display_point_cloud(viewer, point_set_0, 1,0,0);
	
	
	viewer_run(viewer);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
