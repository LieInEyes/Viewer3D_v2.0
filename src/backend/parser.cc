#include "parser.h"

namespace my_space {

model_position *Parser::Parse(std::ifstream &file) {
  auto *temp = new model_position;
  temp->vertex_coordinates.push_back(0);
  temp->vertex_coordinates.push_back(0);
  temp->vertex_coordinates.push_back(0);

  std::string line;
  size_t position_polygon = 0;

  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      validator_.ValidateV(line);
      RecordCoordinate(line, temp);
    } else if (line[0] == 'f' && line[1] == ' ') {
      validator_.ValidateF(line);
      RecordVertexIndex(line, temp, position_polygon);
    }
  }

  return temp;
}

void Parser::RecordCoordinate(std::string &line, model_position *temp) {
  std::string str;
  std::stringstream ss(line);
  size_t count_coordinate = 0;
  while (getline(ss, str, ' ') && count_coordinate < 3) {
    if ((str[0] >= '0' && str[0] <= '9') ||
        (str[0] == '-' && (str[1] >= '0' && str[1] <= '9'))) {
      temp->vertex_coordinates.push_back(stof(str));
      ++count_coordinate;
    }
  }
}

void Parser::RecordVertexIndex(std::string &line, model_position *temp,
                               size_t &position_polygon) {
  std::string str;
  std::stringstream ss(line);
  int count_index_for_polygon = 0;
  while (getline(ss, str, ' ')) {
    if (str[0] >= '0' && str[0] <= '9') {
      ++count_index_for_polygon;
      temp->vertex_index.push_back(stoi(str));
    }
  }
  temp->vertex_count_index.push_back(count_index_for_polygon);
  ++position_polygon;
}
}  // namespace my_space
