#include "model_transform.h"

namespace my_space {
ModelTransform::ModelTransform()
    : model_position_default_(nullptr),
      model_position_temp_(nullptr),
      model_position_current_(nullptr) {}

ModelTransform::~ModelTransform() {
  if (model_position_default_) {
    delete model_position_default_;
    model_position_default_ = nullptr;
  }
  if (model_position_temp_) {
    delete model_position_temp_;
    model_position_temp_ = nullptr;
  }
  if (model_position_current_) {
    delete model_position_current_;
    model_position_current_ = nullptr;
  }
}

model_position *ModelTransform::Transform(const model_transform &settings) {
  CopyCurrentTempDefault();
  MoveModelAll(settings);

  if (model_position_temp_) {
    delete model_position_temp_;
    model_position_temp_ = nullptr;
  }

  return model_position_current_;
}

model_position *ModelTransform::GetModelPositionDefault() const {
  return model_position_default_;
}
model_position *ModelTransform::GetModelPositionCurrent() const {
  return model_position_current_;
}

unsigned int ModelTransform::GetCountVertex() const {
  return model_position_default_->vertex_coordinates.size() / 3 - 1;
}
unsigned int ModelTransform::GetCountPolygon() const {
  return model_position_default_->vertex_count_index.size();
}

void ModelTransform::SetModelPositionDefault(
    model_position *new_default_position) {
  if (model_position_default_) {
    delete model_position_default_;
  }
  model_position_default_ = new_default_position;
}

float ModelTransform::MaxAbsCoordinate() const {
  float res = 0;
  for (unsigned int i = 0;
       i <
       (((model_position_default_->vertex_coordinates.size() / 3 - 1) + 1) * 3);
       i++) {
    if (res < fabsf(model_position_default_->vertex_coordinates[i])) {
      res = fabsf(model_position_default_->vertex_coordinates[i]) + 1;
    }
  }
  return res;
}

void ModelTransform::CopyCurrentTempDefault() {
  if (model_position_current_) {
    delete model_position_current_;
  }

  model_position_current_ = new model_position;
  model_position_current_->vertex_count_index =
      model_position_default_->vertex_count_index;
  model_position_current_->vertex_index = model_position_default_->vertex_index;
  model_position_current_->vertex_coordinates =
      model_position_default_->vertex_coordinates;

  model_position_temp_ = new model_position;
  model_position_temp_->vertex_count_index =
      model_position_default_->vertex_count_index;
  model_position_temp_->vertex_index = model_position_default_->vertex_index;
  model_position_temp_->vertex_coordinates =
      model_position_default_->vertex_coordinates;
}

//// ВСЕ НИЖЕ ОПИСАННЫЕ ФУНКЦИИ РАБОТАЮТ ТОЛЬКО В СОВОКУПНОСТИ
void ModelTransform::MoveModelAll(const model_transform &settings) {
  ScaleModel(settings);

  MoveXModel(settings);
  MoveYModel(settings);
  MoveZModel(settings);
  LoopForMove();

  AxisXModel(settings);
  LoopForMove();
  AxisYModel(settings);
  LoopForMove();
  AxisZModel(settings);
}

void ModelTransform::ScaleModel(const model_transform &settings) const {
  for (unsigned int i = 3;
       i < model_position_default_->vertex_coordinates.size(); i++) {
    model_position_temp_->vertex_coordinates[i] =
        model_position_default_->vertex_coordinates[i] * settings.scale_val;
  }
}

void ModelTransform::MoveVolume(int i, const float &volume) const {
  for (; i < model_position_default_->vertex_coordinates.size(); i += 3) {
    model_position_current_->vertex_coordinates[i] =
        model_position_temp_->vertex_coordinates[i] + volume;
  }
}

void ModelTransform::MoveXModel(const model_transform &settings) const {
  MoveVolume(3, settings.move_x_val);
}

void ModelTransform::MoveYModel(const model_transform &settings) const {
  MoveVolume(4, settings.move_y_val);
}

void ModelTransform::MoveZModel(const model_transform &settings) const {
  MoveVolume(5, settings.move_z_val);
}

void ModelTransform::AxisXModel(const model_transform &settings) const {
  for (unsigned int i = 3;
       i < model_position_default_->vertex_coordinates.size(); i += 3) {
    double y = model_position_temp_->vertex_coordinates[i + 1];
    double z = model_position_temp_->vertex_coordinates[i + 2];

    model_position_current_->vertex_coordinates[i + 1] =
        cos(settings.axis_x_val) * y - sin(settings.axis_x_val) * z;
    model_position_current_->vertex_coordinates[i + 2] =
        sin(settings.axis_x_val) * y + cos(settings.axis_x_val) * z;
  }
}

void ModelTransform::AxisYModel(const model_transform &settings) const {
  for (unsigned int i = 3;
       i < model_position_default_->vertex_coordinates.size(); i += 3) {
    double x = model_position_temp_->vertex_coordinates[i];
    double z = model_position_temp_->vertex_coordinates[i + 2];

    model_position_current_->vertex_coordinates[i] =
        cos(settings.axis_y_val) * x + sin(settings.axis_y_val) * z;
    model_position_current_->vertex_coordinates[i + 2] =
        -sin(settings.axis_y_val) * x + cos(settings.axis_y_val) * z;
  }
}

void ModelTransform::AxisZModel(const model_transform &settings) const {
  for (unsigned int i = 3;
       i < model_position_default_->vertex_coordinates.size(); i += 3) {
    double x = model_position_temp_->vertex_coordinates[i];
    double y = model_position_temp_->vertex_coordinates[i + 1];

    model_position_current_->vertex_coordinates[i] =
        cos(settings.axis_z_val) * x - sin(settings.axis_z_val) * y;
    model_position_current_->vertex_coordinates[i + 1] =
        sin(settings.axis_z_val) * x + cos(settings.axis_z_val) * y;
  }
}

void ModelTransform::LoopForMove() const {
  for (unsigned int i = 0;
       i < model_position_default_->vertex_coordinates.size(); i++) {
    model_position_temp_->vertex_coordinates[i] =
        model_position_current_->vertex_coordinates[i];
  }
}

}  // namespace my_space
