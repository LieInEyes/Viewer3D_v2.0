#ifndef VIEWER3D_V2_0_MODELSETTINGS_H
#define VIEWER3D_V2_0_MODELSETTINGS_H

#include <QColor>
#include <QSettings>
#include <QString>

#include "../backend/common_backend.h"
#include "common_front.h"

namespace my_space {
class ModelSettings {
 public:
  ModelSettings();
  ModelSettings(const ModelSettings &other) = delete;
  ModelSettings(ModelSettings &&other) noexcept = delete;
  ~ModelSettings() = default;

  ModelSettings &operator=(const ModelSettings &other) = delete;
  ModelSettings &operator=(ModelSettings &&other) noexcept = delete;

 public:
  void SaveSettings() const;
  void LoadSettings();
  void DefaultInitializingSettings();

 public:
  model_options model_options_;
  model_transform model_transform_;
};
}  // namespace my_space

#endif  // VIEWER3D_V2_0_MODELSETTINGS_H
