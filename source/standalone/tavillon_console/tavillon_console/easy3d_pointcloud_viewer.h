#pragma once
#define NOMINMAX
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <iostream>
#include <easy3d/viewer/viewer.h>
#include <easy3d/core/surface_mesh.h>
#include <easy3d/renderer/drawable_lines.h>
#include <easy3d/core/model.h>
#include <easy3d/renderer/drawable_points.h>
#include <easy3d/renderer/renderer.h>
#include <easy3d/fileio/resources.h>
#include <easy3d/util/logging.h>
#include <easy3d/core/point_cloud.h>
#include <easy3d/fileio/point_cloud_io.h>
#include "cgal.h"

inline easy3d::Viewer viewer_init() {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Initialize logging.
    // Create the default Easy3D viewer.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    easy3d::logging::initialize();
    return easy3d::Viewer("viewer_joinery_solver", 4, 3, 2, false, true, 24, 8, 3840 * 0.495, 2160 * 0.9);
}

inline void viewer_display_polylines(easy3d::Viewer& viewer, std::vector<std::vector<IK::Point_3>>& polylines, int display_specific_id = -1) {//, std::vector<std::vector<IK::Point_3>>& polylines

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Convert geometry to easy3d lines
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //count the number of vertices
    int count_v = 0;
    int count_e = 0;
    for (auto& polyline : polylines) {
        count_v += polyline.size();
        count_e += polyline.size() - 1;
        //std::cout << "\n Number of Polylines" << polyline.size();
    }

    std::vector<easy3d::vec3> pts;
    std::vector<uint32_t> lineIndices;
    pts.reserve(count_v);
    pts.reserve(count_e);

    //add vertices
    //add indices
    int id_count = 0;
    for (size_t i = 0; i < polylines.size(); i++)
    {
        //Output specific output
        if (display_specific_id > -1) {
            int panel_id = (i - (i % 2)) * 0.5;
            if (panel_id != display_specific_id) continue;
        }

        for (int j = 0; j < polylines[i].size(); j++) {
            pts.emplace_back(easy3d::vec3(polylines[i][j].x(), polylines[i][j].y(), polylines[i][j].z()));
        }

        for (int j = 0; j < polylines[i].size() - 1; j++) {
            lineIndices.emplace_back(id_count);
            lineIndices.emplace_back(id_count + 1);
            id_count++;
        }
        id_count++;//go to next polyline
    }



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //add vertices with indicies of lines
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto drawable = new easy3d::LinesDrawable("lines");
    drawable->update_element_buffer(lineIndices);
    drawable->update_vertex_buffer(pts);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //update easy3d settings
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    drawable->set_uniform_coloring(easy3d::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    drawable->set_line_width(2.0f);
    viewer.add_drawable(drawable);
}


inline void viewer_display_polylines_tree(easy3d::Viewer& viewer, std::vector<std::vector<std::vector<IK::Point_3>>>& polylines_tree, int display_specific_id = -1) {//, std::vector<std::vector<IK::Point_3>>& polylines

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Convert geometry to easy3d lines
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //count the number of vertices
    int count_v = 0;
    int count_e = 0;
    for (auto& polylines : polylines_tree) {
        for (auto& polyline : polylines) {
            count_v += polyline.size();
            count_e += polyline.size() - 1;
            //std::cout << "\n Number of Polylines" << polyline.size();
        }
    }

    std::vector<easy3d::vec3> pts;
    std::vector<uint32_t> lineIndices;
    pts.reserve(count_v);
    pts.reserve(count_e);

    //add vertices
    //add indices
    int id_count = 0;
    int tree_count = 0;
    for (auto& polylines : polylines_tree) {

        //Output specific output
        if (display_specific_id > -1) {
            tree_count++;
            if (tree_count - 1 != display_specific_id) continue;
        }

        for (size_t i = 0; i < polylines.size(); i++)
        {

            for (int j = 0; j < polylines[i].size(); j++) {
                pts.emplace_back(easy3d::vec3(polylines[i][j].x(), polylines[i][j].y(), polylines[i][j].z()));
            }

            for (int j = 0; j < polylines[i].size() - 1; j++) {
                lineIndices.emplace_back(id_count);
                lineIndices.emplace_back(id_count + 1);
                id_count++;
            }
            id_count++;//go to next polyline
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //add vertices with indicies of lines
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto drawable = new easy3d::LinesDrawable("lines");
    drawable->update_element_buffer(lineIndices);
    drawable->update_vertex_buffer(pts);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //update easy3d settings
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    drawable->set_uniform_coloring(easy3d::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    drawable->set_line_width(5.0f);
    viewer.add_drawable(drawable);

}


inline void viewer_display_point_cloud(easy3d::Viewer& viewer, CGAL::Point_set_3<IK::Point_3>& cgal_cloud, float r = 0, float g = 0, float b = 0, float weight = 5) {

    // Read the point cloud from a known file. 
    
    // Create a point cloud
    easy3d::PointCloud* cloud = new easy3d::PointCloud;

    // Add some points. Here we add 100 points on a 10*10 grid.
    //for (float i = -5; i < 5; ++i) {
    //    for (float j = -5; j < 5; ++j)
    //        cloud->add_vertex(easy3d::vec3(i, j, 0));// z = 0: all points are on XY plane
    //}
    for (auto& p : cgal_cloud.points()) {
		cloud->add_vertex(easy3d::vec3(p.x(), p.y(), p.z()));
    }
    std::cout << "point cloud has " << cloud->n_vertices() << " points" << std::endl;

     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //add vertices with indicies of lines
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto drawable = new easy3d::PointsDrawable("points");
    drawable->update_vertex_buffer(cloud->points());
	
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //update easy3d settings
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    drawable->set_uniform_coloring(easy3d::vec4(r, g, b, 1.0f));
    viewer.add_drawable(drawable);
    drawable->set_point_size(weight);
    drawable->set_lighting_two_sides(false);

    // Delete the point cloud (i.e., release memory)
    delete cloud;
	
    //if (!cloud) {
    //    LOG(ERROR) << "Error: failed to load model. Please make sure the file exists and format is correct.";
    //    return;
    //}
        //// Delete the point cloud (i.e., release memory)
     //delete cloud;

    //std::cout << "point cloud has " << cloud->n_vertices() << " points" << std::endl;

    //// You can save the model into a file of one of the supported file formats using 'PointCloudIO::save()'.
    //// In this example, let's save the model into a file with a special format. In each line we store the
    //// x, y, z coordinates, followed by the normal (nx, ny, nz) and color (r, g, b) if they exist.
    //std::ofstream output("./bunny-copy.txt");
    //if (output.is_open()) { // if the file has been successfully created
    //    // The point coordinates.
    //    PointCloud::VertexProperty<vec3> points = cloud->get_vertex_property<vec3>("v:point");
    //    // The point normals.
    //    PointCloud::VertexProperty<vec3> normals = cloud->get_vertex_property<vec3>("v:normal");
    //    // The point colors.
    //    PointCloud::VertexProperty<vec3> colors = cloud->get_vertex_property<vec3>("v:color");
    //    std::cout << "saving the point cloud..." << std::endl;

    //    for (auto v : cloud->vertices()) {
    //        output << points[v];
    //        if (normals)	// if normals exist
    //            output << " " << normals[v];
    //        if (colors)		// if colors exist
    //            output << " " << colors[v];
    //        output << std::endl;
    //    }
    //    std::cout << "point cloud saved to './bunny-copy.txt'" << std::endl;
    //}


}

inline void viewer_run(easy3d::Viewer& viewer) {
    viewer.set_background_color(easy3d::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    viewer.fit_screen();
    viewer.run();
}
