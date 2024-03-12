#ifndef VIEWER3D_V2_0_1_MAIN_BACK_END_H
#define VIEWER3D_V2_0_1_MAIN_BACK_END_H

#include <cmath>
#include <string>

#include "common_backend.h"
#include "model_transform.h"
#include "parser.h"

namespace my_space {
class MainBackEnd {
 private:
  MainBackEnd() = default;

 public:
  MainBackEnd(const MainBackEnd &other) = delete;
  MainBackEnd(MainBackEnd &&other) noexcept = delete;
  ~MainBackEnd() = default;

  MainBackEnd &operator=(const MainBackEnd &other) = delete;
  MainBackEnd &operator=(MainBackEnd &&other) noexcept = delete;

 public:
  static MainBackEnd &Instance();
  void Parse(std::string &file_path, unsigned int &count_vertex,
             unsigned int &count_polygon, float &max_coordinate);
  model_position *Transform(const model_transform &settings);

  model_position *GetModelPositionDefault() const;
  model_position *GetModelPositionCurrent() const;

 private:
  ModelTransform model_transform_;
  Parser parser_;
};
}  // namespace my_space

#endif  // VIEWER3D_V2_0_1_MAIN_BACK_END_H
