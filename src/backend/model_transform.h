#ifndef VIEWER3D_V2_0_MODEL_TRANSFORM_H
#define VIEWER3D_V2_0_MODEL_TRANSFORM_H

#include <cmath>

#include "common_backend.h"

namespace my_space {

class ModelTransform {
 public:
  ModelTransform();
  ModelTransform(const ModelTransform &other) = delete;
  ModelTransform(ModelTransform &&other) noexcept = delete;
  ~ModelTransform();

  ModelTransform &operator=(const ModelTransform &other) = delete;
  ModelTransform &operator=(ModelTransform &&other) noexcept = delete;

 public:
  model_position *Transform(const model_transform &settings);

  model_position *GetModelPositionDefault() const;
  model_position *GetModelPositionCurrent() const;

  unsigned int GetCountVertex() const;
  unsigned int GetCountPolygon() const;

  void SetModelPositionDefault(model_position *new_default_position);

  float MaxAbsCoordinate() const;

 private:
  void CopyCurrentTempDefault();
  void MoveModelAll(const model_transform &settings);

  void ScaleModel(const model_transform &settings) const;

  void MoveVolume(int i, const float &volume) const;
  void MoveXModel(const model_transform &settings) const;
  void MoveYModel(const model_transform &settings) const;
  void MoveZModel(const model_transform &settings) const;

  void AxisXModel(const model_transform &settings) const;
  void AxisYModel(const model_transform &settings) const;
  void AxisZModel(const model_transform &settings) const;
  void LoopForMove() const;

 private:
  model_position *model_position_default_;
  model_position *model_position_temp_;
  model_position *model_position_current_;
};
}  // namespace my_space

#endif  // VIEWER3D_V2_0_MODEL_TRANSFORM_H
