#include "auto_mapping_ros//skeletonizer.h"

int main()
{
    amr::Skeletonizer processor;
    processor.read_map("/home/yash/yasht_ws/src/auto_mapping_ros/maps/levine.jpg");
    const auto skeleton = processor.skeletonize();
    return 0;
}