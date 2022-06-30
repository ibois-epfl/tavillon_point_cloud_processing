#include <cilantro/utilities/nearest_neighbor_graph_utilities.hpp>
#include <cilantro/clustering/spectral_clustering.hpp>
#include <cilantro/utilities/point_cloud.hpp>
#include <iostream>
#include <cilantro/utilities/timer.hpp>

void generate_input_data(cilantro::VectorSet3f &points, Eigen::SparseMatrix<float> &affinities)
{
    points.resize(3, 1700);
    for (size_t i = 0; i < 1500; i++)
    {
        points.col(i).setRandom().normalize();
    }
    for (size_t i = 1500; i < 1700; i++)
    {
        points.col(i).setRandom().normalize();
        points.col(i) *= 0.3f;
    }
    points.row(2).array() += 4.0f;

    // Build neighborhood graph
    // 30 neighbors
    cilantro::NeighborhoodSet<float> nn =
        cilantro::KDTree3f<>(points).search(points, cilantro::KNNNeighborhoodSpecification<>(30));
    affinities = cilantro::getNNGraphFunctionValueSparseMatrix(
        nn, cilantro::RBFKernelWeightEvaluator<float>(), true);
}

int main(int argc, char **argv)
{
    // Generate input dataset
    cilantro::VectorSet3f points;
    Eigen::SparseMatrix<float> affinities;
    generate_input_data(points, affinities);

    std::cout << "Number of points: " << points.cols() << std::endl;

    size_t max_num_clusters = 4;

    cilantro::Timer timer;
    timer.start();

    // cilantro::SpectralClustering<float,2> sc(affinities);
    // cilantro::SpectralClustering<float> sc(affinities, max_num_clusters, true,
    //                                        cilantro::GraphLaplacianType::UNNORMALIZED);
    // cilantro::SpectralClustering<float> sc(affinities, max_num_clusters, true,
    //                                        cilantro::GraphLaplacianType::NORMALIZED_SYMMETRIC);
    cilantro::SpectralClustering<float> sc(affinities, max_num_clusters, true,
                                           cilantro::GraphLaplacianType::NORMALIZED_RANDOM_WALK);

    timer.stop();
    std::cout << "Clustering time: " << timer.getElapsedTime() << "ms" << std::endl;
    std::cout << "Number of clusters: " << sc.getNumberOfClusters() << std::endl;
    std::cout << "Performed k-means iterations: " << sc.getNumberOfPerformedIterations() << std::endl;

    const auto &cpi = sc.getClusterToPointIndicesMap();
    size_t mins = points.cols(), maxs = 0;
    for (size_t i = 0; i < cpi.size(); i++)
    {
        if (cpi[i].size() < mins)
            mins = cpi[i].size();
        if (cpi[i].size() > maxs)
            maxs = cpi[i].size();
    }
    std::cout << "Cluster size range is: [" << mins << "," << maxs << "]" << std::endl;

    // Create a color map
    cilantro::VectorSet3f color_map(3, max_num_clusters);
    for (size_t i = 0; i < max_num_clusters; i++)
    {
        color_map.col(i) = Eigen::Vector3f::Random().cwiseAbs();
    }

    const auto &idx_map = sc.getPointToClusterIndexMap();

    cilantro::VectorSet3f colors(3, idx_map.size());
    for (size_t i = 0; i < colors.cols(); i++)
    {
        colors.col(i) = color_map.col(idx_map[i]);
    }

    return 0;
}