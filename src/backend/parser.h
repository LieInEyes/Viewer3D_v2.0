#ifndef VIEWER3D_V2_0_PARSER_H
#define VIEWER3D_V2_0_PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "common_backend.h"
#include "validator_file_obj.h"

namespace my_space {

class Parser {
 public:
  Parser() = default;
  Parser(const Parser &other) = delete;
  Parser(Parser &&other) noexcept = delete;
  ~Parser() = default;

  Parser &operator=(const Parser &other) = delete;
  Parser &operator=(Parser &&other) noexcept = delete;

 public:
  model_position *Parse(std::ifstream &file);

 private:
  static void RecordCoordinate(std::string &line, model_position *temp);
  static void RecordVertexIndex(std::string &line, model_position *temp,
                                size_t &position_polygon);

 private:
  ValidatorFileOBJ validator_;
};
}  // namespace my_space

#endif  // VIEWER3D_V2_0_PARSER_H
