

#include "pch.h"


typedef open3d::geometry::PointCloud PC_o3d;
typedef std::shared_ptr<PC_o3d> PC_o3d_ptr;

typedef cilantro::PointCloud3f PC_cil;
typedef std::shared_ptr<PC_cil> PC_cil_ptr;

int main(int argc, char* argv[])
{
    // Open cloud
    PC_o3d_ptr cloud_op3_one(new PC_o3d);
    cloud_op3_one = Cockroach::importCloud("C:\\tavillon_point_cloud_processing\\tavillon_point_cloud_processing\\tavillon_pre_experiment\\build\\Release\\tavillon3.ply");


    // downsample
    std::cout << cloud_op3_one->points_.size() << std::endl;
    PC_o3d_ptr cloud_op3_one_ = Cockroach::voxelDownSampling(cloud_op3_one, 0.01);
    std::cout << cloud_op3_one_->points_.size() << std::endl;



    //Compute normals
    Cockroach::estimateUnstructuredPCDNormals(cloud_op3_one_, 16, 0.1);
    Cockroach::visualize_standard(cloud_op3_one_);
    //for (auto& normal : cloud_op3_one->normals_) {
    //    //std::cout << normal << std::endl << std::endl;
    //}


    //// Convert Open3d>>Cilantro>>Open3d
    //PC_cil_ptr cloud_cli(new PC_cil);
    //Cockroach::convert_Open3DToCilantroCloud(cloud_op3_one, cloud_cli);
    //PC_o3d_ptr cloud_op3_two(new PC_o3d);
    //Cockroach::convert_CilantroToOpen3DCloud(cloud_cli, cloud_op3_two);

    // Visualize cloud
   // Cockroach::visualize_standard(cloud_op3_two);

    return EXIT_SUCCESS;
}