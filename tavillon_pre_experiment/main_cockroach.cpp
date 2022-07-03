

#include "pch.h"


typedef open3d::geometry::PointCloud PC_o3d;
typedef std::shared_ptr<PC_o3d> PC_o3d_ptr;

typedef cilantro::PointCloud3f PC_cil;
typedef std::shared_ptr<PC_cil> PC_cil_ptr;

int main(int argc, char* argv[])
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LOAD CLOUD FROM FILE
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Open cloud
	PC_o3d_ptr cloud_op3_one(new PC_o3d);
	cloud_op3_one = Cockroach::importCloud("C:\\tavillon_point_cloud_processing\\tavillon_point_cloud_processing\\tavillon_pre_experiment\\build\\Release\\tavillon10.ply");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PLANE TO PLANE TRANSFORMATION
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Cockroach::orient_pointcloud(
		cloud_op3_one,
		//Source plane
		Eigen::Vector3d(-15.932689, 1.450952, 0.566604),
		Eigen::Vector3d(0.928573, -0.288704, -0.233243),
		Eigen::Vector3d(0.371139, 0.72719, 0.577452),
		Eigen::Vector3d(0.0029, -0.622772, 0.782398),


		//Target Plane
		Eigen::Vector3d(0, 0, 0),
		Eigen::Vector3d(1, 0, 0),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(0, 0, 1)
		);
	



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CROP
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cloud_op3_one = cloud_op3_one->Crop(open3d::geometry::AxisAlignedBoundingBox(
		Eigen::Vector3d(-1, -1, 0.07),
		Eigen::Vector3d(1, 1, 0.20)
	));


	//PC_o3d_ptr cloud_op3_two(new PC_o3d);
	//cloud_op3_two = Cockroach::importCloud("C:\\tavillon_point_cloud_processing\\tavillon_point_cloud_processing\\tavillon_pre_experiment\\build\\Release\\transfomation_test.ply");
	//
	//PC_o3d_ptr cloud_op3_axes(new PC_o3d);
	//cloud_op3_axes = Cockroach::importCloud("C:\\tavillon_point_cloud_processing\\tavillon_point_cloud_processing\\tavillon_pre_experiment\\build\\Release\\transfomation_axes.ply");
	//



	//Cockroach::visualize_standard(clouds, false);
	//return EXIT_SUCCESS;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CLUSTER BASED ON NORMALS
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// downsample
	std::cout << cloud_op3_one->points_.size() << std::endl;
	PC_o3d_ptr cloud_op3_one_ = Cockroach::voxelDownSampling(cloud_op3_one, 0.001);
	std::cout << cloud_op3_one_->points_.size() << std::endl;

	//Compute normals
	Cockroach::estimateUnstructuredPCDNormals(cloud_op3_one_, 16, 0.1);

	// Convert Open3d>>Cilantro
	PC_cil_ptr cloud_cli(new PC_cil);
	Cockroach::convert_Open3DToCilantroCloud(cloud_op3_one_, cloud_cli);

	//Cluster pointclouds
	auto result = Cockroach::cluster_connectedComponentKSearch(cloud_cli, 30, 2.0, 100, true);
	
	// Convert Cilantro>>Open3d
	std::vector<std::shared_ptr<PC>> open3d_clouds_d;
	Cockroach::convert_CilantroToOpen3DCloud_multiple(result, open3d_clouds_d);
	std::cout << "number of points in the first cloud" << std::endl << std::endl;

	//std::cout << open3d_clouds_d[0]->points_.size() << std::endl << std::endl;
	//std::cout << open3d_clouds_d[1]->points_.size() << std::endl << std::endl;
	//std::cout << open3d_clouds_d[2]->points_.size() << std::endl << std::endl;
	//std::cout << open3d_clouds_d[3]->points_.size() << std::endl << std::endl;
	//std::cout << open3d_clouds_d[4]->points_.size() << std::endl << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Create Bounding Box
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	auto bbox = open3d_clouds_d[0]->GetOrientedBoundingBox();
	std::vector<Eigen::Vector3d> corner_points=bbox.GetBoxPoints();
	std::cout << bbox.GetMinBound() << std::endl << std::endl;
	std::cout << bbox.GetBoxPoints()[0] << std::endl << std::endl;
	PC_o3d_ptr cloud_op3_pca(new PC_o3d);
	cloud_op3_pca->points_.insert(cloud_op3_pca->points_.begin(),corner_points.begin(),corner_points.end());
	for(auto& p : corner_points)
		std::cout << p << std::endl << std::endl;
	open3d::io::WritePointCloud("C:\\tavillon_point_cloud_processing\\tavillon_point_cloud_processing\\tavillon_pre_experiment\\build\\Release\\output.ply", *cloud_op3_pca);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VISUALIZE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//std::vector<PC_o3d_ptr> clouds{ cloud_op3_one,open3d_clouds_d[0] };
	
	Cockroach::visualize_standard(open3d_clouds_d[0]);
	return EXIT_SUCCESS;
}