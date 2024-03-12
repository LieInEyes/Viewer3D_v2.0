#include <gtest/gtest.h>

#include <cmath>
#include <string>
#include <vector>

#include "../backend/main_back_end.h"

// дефолтные координаты кубика
std::vector<float> coordinates_default = {
    0.0f,  0.0f, 0.0f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
    0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f};

std::vector<float> coordinates_after_transform = {0.0f,
                                                  0.0f,
                                                  0.0f,
                                                  -0.658551871776581f,
                                                  2.343854427337646f,
                                                  -0.012478425167501f,
                                                  -0.031867336481810f,
                                                  2.608812570571899f,
                                                  -1.349289536476135f,
                                                  -1.426513910293579f,
                                                  1.196995019912720f,
                                                  -0.599801123142242f,
                                                  -0.799829363822937f,
                                                  1.461952924728394f,
                                                  -1.936612129211426f,
                                                  -0.300680369138718f,
                                                  0.267204374074936f,
                                                  -0.256306797266006f,
                                                  0.326004117727280f,
                                                  0.532162308692932f,
                                                  -1.593117833137512f,
                                                  0.467281579971313f,
                                                  1.414063811302185f,
                                                  0.331015855073929f,
                                                  1.093966126441956f,
                                                  1.679021835327148f,
                                                  -1.005795240402222f};

// дефолтное значение количества вершин у полигона
std::vector<unsigned int> count_index_default = {3, 3, 3, 3, 3, 3,
                                                 3, 3, 3, 3, 3, 3};

// дефолтные индексы полигонов для отрисовки
std::vector<unsigned int> indexes_default = {
    1, 2, 3, 3, 2, 4, 3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8,
    7, 8, 1, 1, 8, 2, 2, 8, 4, 4, 8, 6, 7, 1, 5, 5, 1, 3,
};

// дефолтное значение количества вершин, полигонов, и максимального значение
// осей (что бы картинка уместилась в виджет)
int count_vertex_default = 8;
int count_polygon_default = 12;
float max_coordinate_default = 1.5;

float EPS = 0.000001f;

bool EqualVertexCoordinate(std::vector<float> &test,
                           std::vector<float> &verification) {
  for (size_t i = 0; i < verification.size(); ++i) {
    if (fabs(test[i] - verification[i]) > EPS) {
      return false;
    }
  }
  return true;
}

bool EqualVectorUInt(std::vector<unsigned int> &test,
                     std::vector<unsigned int> &verification) {
  for (size_t i = 0; i < verification.size(); ++i) {
    if (test[i] != verification[i]) {
      return false;
    }
  }
  return true;
}

TEST(test_parse, error_v) {
  my_space::MainBackEnd &test_cube_error_v = my_space::MainBackEnd::Instance();
  unsigned int count_vertex = 0;
  unsigned int count_polygon = 0;
  float max_coordinate = 1;
  std::string file_path = "../src/tests/cube_error_v.obj.obj";
  ASSERT_THROW((test_cube_error_v.Parse(file_path, count_vertex, count_polygon,
                                        max_coordinate)),
               std::logic_error);
}

TEST(test_parse, error_f) {
  my_space::MainBackEnd &test_cube_error_f = my_space::MainBackEnd::Instance();
  unsigned int count_vertex = 0;
  unsigned int count_polygon = 0;
  float max_coordinate = 1;
  std::string file_path = "../src/tests/cube_error_f.obj.obj";
  ASSERT_THROW((test_cube_error_f.Parse(file_path, count_vertex, count_polygon,
                                        max_coordinate)),
               std::logic_error);
}

TEST(test_transform, transform_cube) {
  my_space::model_transform settings = {1.5, 0.9, -0.7, 1.2, -2.1, 1.1, 0.4};
  my_space::MainBackEnd &test_cube = my_space::MainBackEnd::Instance();
  unsigned int count_vertex = 0;
  unsigned int count_polygon = 0;
  float max_coordinate = 1;
  std::string file_path = "../src/tests/cube.obj";

  test_cube.Parse(file_path, count_vertex, count_polygon, max_coordinate);

  ASSERT_EQ(count_vertex, count_vertex_default);
  ASSERT_EQ(count_polygon, count_polygon_default);
  ASSERT_EQ(max_coordinate, max_coordinate_default);

  ASSERT_EQ(EqualVertexCoordinate(
                test_cube.GetModelPositionDefault()->vertex_coordinates,
                coordinates_default),
            true);
  ASSERT_EQ(
      EqualVectorUInt(test_cube.GetModelPositionDefault()->vertex_count_index,
                      count_index_default),
      true);
  ASSERT_EQ(EqualVectorUInt(test_cube.GetModelPositionDefault()->vertex_index,
                            indexes_default),
            true);

  test_cube.Transform(settings);

  ASSERT_EQ(EqualVertexCoordinate(
                test_cube.GetModelPositionCurrent()->vertex_coordinates,
                coordinates_after_transform),
            true);
  ASSERT_EQ(
      EqualVectorUInt(test_cube.GetModelPositionCurrent()->vertex_count_index,
                      count_index_default),
      true);
  ASSERT_EQ(EqualVectorUInt(test_cube.GetModelPositionCurrent()->vertex_index,
                            indexes_default),
            true);
}

TEST(test_leaks, reopen_file) {
  my_space::model_transform settings = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  my_space::MainBackEnd &model = my_space::MainBackEnd::Instance();
  unsigned int count_vertex = 0;
  unsigned int count_polygon = 0;
  float max_coordinate = 1;

  std::string file_path = "../src/tests/cube.obj";
  model.Parse(file_path, count_vertex, count_polygon, max_coordinate);

  file_path = "../src/tests/deer.obj";
  model.Parse(file_path, count_vertex, count_polygon, max_coordinate);

  file_path = "../src/tests/cube.obj";
  model.Parse(file_path, count_vertex, count_polygon, max_coordinate);

  model.Transform(settings);

  file_path = "../src/tests/deer.obj";
  model.Parse(file_path, count_vertex, count_polygon, max_coordinate);
  model.Transform(settings);

  file_path = "../src/tests/cube.obj";
  model.Parse(file_path, count_vertex, count_polygon, max_coordinate);
  model.Transform(settings);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
