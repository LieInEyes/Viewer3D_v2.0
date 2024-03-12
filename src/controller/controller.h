#ifndef VIEWER3D_V2_0_CONTROLLER_H
#define VIEWER3D_V2_0_CONTROLLER_H

#include <string>

#include "../backend/common_backend.h"
#include "../backend/main_back_end.h"

namespace my_space {

class Controller {
 public:
  Controller() = default;
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) noexcept = delete;
  ~Controller() = default;

  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) noexcept = delete;

 public:
  void parse_after_open_file(std::string &file_path, unsigned int &count_vertex,
                             unsigned int &count_polygon,
                             float &max_coordinate);
  model_position *UpdateFrame(const model_transform &settings);

 private:
  MainBackEnd &main_back_end_ = MainBackEnd::Instance();
};

}  // namespace my_space

#endif  // VIEWER3D_V2_0_CONTROLLER_H
