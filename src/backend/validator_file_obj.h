#ifndef VIEWER3D_V2_0_VALIDATOR_FILE_OBJ_H
#define VIEWER3D_V2_0_VALIDATOR_FILE_OBJ_H

#include <iostream>
#include <regex>

#include "common_backend.h"

namespace my_space {
class ValidatorFileOBJ {
 public:
  ValidatorFileOBJ();
  ValidatorFileOBJ(const ValidatorFileOBJ &other) = delete;
  ValidatorFileOBJ(ValidatorFileOBJ &&other) noexcept = delete;
  ~ValidatorFileOBJ() = default;

  ValidatorFileOBJ &operator=(const ValidatorFileOBJ &other) = delete;
  ValidatorFileOBJ &operator=(ValidatorFileOBJ &&other) noexcept = delete;

 public:
  void ValidateV(const std::string &line) const;
  void ValidateF(const std::string &line) const;

 private:
  std::regex regex_v_;
  std::regex regex_f_;
};
}  // namespace my_space

#endif  // VIEWER3D_V2_0_VALIDATOR_FILE_OBJ_H
