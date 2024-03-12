#ifndef VIEWER3D_V2_0_COMMON_BACKEND_H
#define VIEWER3D_V2_0_COMMON_BACKEND_H

#include <stdexcept>
#include <vector>

namespace my_space {

typedef struct data {
  std::vector<float> vertex_coordinates;
  std::vector<unsigned int> vertex_count_index;
  std::vector<unsigned int> vertex_index;
} model_position;

typedef struct data_transform {
  float scale_val;
  float move_x_val;
  float move_y_val;
  float move_z_val;
  float axis_x_val;
  float axis_y_val;
  float axis_z_val;
} model_transform;

class BackEndError : public std::logic_error {
 public:
  explicit BackEndError(const std::string &message)
      : std::logic_error(message) {}
};

class ValidationError : public BackEndError {
 public:
  explicit ValidationError(const std::string &message)
      : BackEndError(message) {}
};

class OpenFileError : public BackEndError {
 public:
  explicit OpenFileError(const std::string &message) : BackEndError(message) {}
};

}  // namespace my_space

#endif  // VIEWER3D_V2_0_COMMON_BACKEND_H
