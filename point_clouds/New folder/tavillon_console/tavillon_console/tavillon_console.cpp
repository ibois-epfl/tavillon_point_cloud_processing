// tavillon_console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define CGAL_USE_BASIC_VIEWER
#include <iostream>
#include "easy3d_pointcloud_viewer.h"
#include "cgal_pointcloud_processing.h"
#include <CGAL/draw_point_set_3.h>
//#include <CGAL/Qt/Basic_viewer_qt.h>

int main()
{
	const std::string filename_0 = "C:\\tavillon_point_cloud_processing\\tavillon_point_cloud_processing\\point_clouds\\model0.ply";

	Point_set points;
	auto is_read_0 = CGAL::IO::read_point_set(filename_0, points);




	// Add a cluster map
	Point_set::Property_map<int> cluster_map = points.add_property_map<int>("cluster", -1).first;



	// Compute average spacing
	double spacing = CGAL::compute_average_spacing<CGAL::Parallel_if_available_tag>(points, 35);
	std::cerr << "Spacing = " << spacing << std::endl;



	// Adjacencies stored in vector
	std::vector<std::pair<std::size_t, std::size_t> > adjacencies;
	// Compute clusters
	CGAL::Real_timer t;
	t.start();
	std::size_t nb_clusters
		= CGAL::cluster_point_set(points, cluster_map,
			points.parameters().neighbor_radius(spacing)
			.adjacencies(std::back_inserter(adjacencies)));
	t.stop();
	std::cerr << "Found " << nb_clusters << " clusters with " << adjacencies.size()
		<< " adjacencies in " << t.time() << " seconds" << std::endl;
	// Output a colored PLY file
	Point_set::Property_map<unsigned char> red = points.add_property_map<unsigned char>("red", 0).first;
	Point_set::Property_map<unsigned char> green = points.add_property_map<unsigned char>("green", 0).first;
	Point_set::Property_map<unsigned char> blue = points.add_property_map<unsigned char>("blue", 0).first;
	for (Point_set::Index idx : points)
	{
		// One color per cluster
		CGAL::Random rand(cluster_map[idx]);
		red[idx] = rand.get_int(64, 192);
		green[idx] = rand.get_int(64, 192);
		blue[idx] = rand.get_int(64, 192);
	}
	std::ofstream ofile("out.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(ofile);
	ofile << points;
	


	//easy3d::Viewer viewer = viewer_init();
	//viewer_display_point_cloud(viewer, points);
	//
	////
	//viewer_run(viewer);
	CGAL::draw(points);
	return EXIT_SUCCESS;
}

 //Run program: Ctrl + F5 or Debug > Start Without Debugging menu
 //Debug program: F5 or Debug > Start Debugging menu

 /*Tips for Getting Started: 
   1. Use the Solution Explorer window to add/manage files
   2. Use the Team Explorer window to connect to source control
   3. Use the Output window to see build output and other messages
   4. Use the Error List window to view errors
   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
   6. In the future, to open this project again, go to File > Open > Project and select the .sln file*/
