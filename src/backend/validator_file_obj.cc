#include "validator_file_obj.h"

namespace my_space {

ValidatorFileOBJ::ValidatorFileOBJ()
    : regex_v_(
          "v(\\s+-?\\d*\\.\\d+){3}(\\s+\\d*\\.\\d+)?((\\s+\\d*\\.\\d+){3})?\\s*"
          "$"),
      regex_f_(
          "^f\\s+((\\d+\\s*){3,}$)|((\\d+\\/\\d+\\s*){3,}$)|((\\d+\\/\\d+\\/"
          "\\d+\\s*){3,}$)|((\\d+\\/\\/\\d+\\s*){3,}$)") {}

void ValidatorFileOBJ::ValidateV(const std::string& line) const {
  std::smatch matches;
  if (!(std::regex_search(line, matches, regex_v_))) {
    throw ValidationError("Некорректная строка с координатами вершины 'v'");
  }
}

void ValidatorFileOBJ::ValidateF(const std::string& line) const {
  std::smatch matches;
  if (!(std::regex_search(line, matches, regex_f_))) {
    throw ValidationError("Некорректная строка с параметрами полигонов 'f'");
  }
}
}  // namespace my_space
