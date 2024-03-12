#include "main_back_end.h"

namespace my_space {

MainBackEnd &MainBackEnd::Instance() {
  static MainBackEnd res;
  return res;
}

void MainBackEnd::Parse(std::string &file_path, unsigned int &count_vertex,
                        unsigned int &count_polygon, float &max_coordinate) {
  setlocale(LC_NUMERIC, "C");
  std::ifstream file(file_path);
  if (file.is_open()) {
    try {
      model_transform_.SetModelPositionDefault(parser_.Parse(file));

      max_coordinate = model_transform_.MaxAbsCoordinate();
      count_vertex = model_transform_.GetCountVertex();
      count_polygon = model_transform_.GetCountPolygon();

      file.close();
    } catch (const BackEndError &ex) {
      file.close();
      throw &ex;
    }
  } else {
    throw OpenFileError("Ошибка открытия файла");
  }
}

model_position *MainBackEnd::Transform(const model_transform &settings) {
  return model_transform_.Transform(settings);
}

model_position *MainBackEnd::GetModelPositionDefault() const {
  return model_transform_.GetModelPositionDefault();
}

model_position *MainBackEnd::GetModelPositionCurrent() const {
  return model_transform_.GetModelPositionCurrent();
}

}  // namespace my_space
