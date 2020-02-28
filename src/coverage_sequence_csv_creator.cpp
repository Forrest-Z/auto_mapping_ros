#define DEBUG 0

#include "auto_mapping_ros/coverage_planner.h"
#include "auto_mapping_ros/graph_builder.h"
#include "auto_mapping_ros/skeletonizer.h"
#include "auto_mapping_ros/utils.h"

static constexpr auto filepath = "/home/yash/yasht_ws/src/auto_mapping_ros/maps/levine.jpg";
static constexpr auto csv_filepath = "/home/yash/yasht_ws/src/auto_mapping_ros/csv/sequence.csv";

int main()
{
    amr::Skeletonizer processor;
    processor.read_map(filepath);
    cv::Mat skeleton = processor.skeletonize();

    cv::Mat map = cv::imread(filepath, 0);

    assert(skeleton.rows == map.rows);
    assert(skeleton.cols == map.cols);

    amr::GraphBuilder builder(skeleton, map);
    builder.build_graph();
    auto graph = builder.get_graph();

    amr::CoveragePlanner planner(&graph);
    planner.compute_sequence();
    std::vector<std::array<int, 2>> sequence = planner.get_sequence();

    amr::write_sequence_to_csv(sequence, csv_filepath);
    std::cout << "\nSize of sequence: " << sequence.size();

    return 0;
}