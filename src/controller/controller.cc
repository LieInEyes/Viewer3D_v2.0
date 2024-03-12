#include "controller.h"

namespace my_space {

void Controller::parse_after_open_file(std::string &file_path,
                                       unsigned int &count_vertex,
                                       unsigned int &count_polygon,
                                       float &max_coordinate) {
  main_back_end_.Parse(file_path, count_vertex, count_polygon, max_coordinate);
}

model_position *Controller::UpdateFrame(const model_transform &settings) {
  return main_back_end_.Transform(settings);
}

}  // namespace my_space
