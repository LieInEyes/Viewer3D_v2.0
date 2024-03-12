#include "model_settings.h"

namespace my_space {
ModelSettings::ModelSettings()
    : model_options_{"", 0, Qt::black, {Qt::white, 1, 0}, {Qt::red, 1, 0}},
      model_transform_{1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f} {}

void ModelSettings::SaveSettings() const {
  QSettings settings("School21", "Viewer3D");
  settings.beginGroup("Main");
  settings.setValue("Projection", model_options_.projection);
  settings.setValue("ScaleModel", model_transform_.scale_val);
  settings.setValue("BackgraundColor", model_options_.backgraund_color);

  settings.setValue("TranslateX", model_transform_.move_x_val);
  settings.setValue("TranslateY", model_transform_.move_y_val);
  settings.setValue("TranslateZ", model_transform_.move_z_val);

  settings.setValue("RotateX", model_transform_.axis_x_val);
  settings.setValue("RotateY", model_transform_.axis_y_val);
  settings.setValue("RotateZ", model_transform_.axis_z_val);

  settings.setValue("LineColor",
                    model_options_.model_draw_parameter_line.color);
  settings.setValue("LineType", model_options_.model_draw_parameter_line.type);
  settings.setValue("SizeLine", model_options_.model_draw_parameter_line.size);

  settings.setValue("PointColor",
                    model_options_.model_draw_parameter_vertex.color);
  settings.setValue("PointType",
                    model_options_.model_draw_parameter_vertex.type);
  settings.setValue("SizePoint",
                    model_options_.model_draw_parameter_vertex.size);

  settings.endGroup();
}

void ModelSettings::LoadSettings() {
  QSettings settings("School21", "Viewer3D");
  settings.beginGroup("Main");
  model_options_.projection = settings.value("Projection").toInt();
  model_transform_.scale_val = settings.value("ScaleModel").toDouble();
  model_options_.backgraund_color =
      settings.value("BackgraundColor", QColor(Qt::black)).value<QColor>();

  model_transform_.move_x_val = settings.value("TranslateX").toDouble();
  model_transform_.move_y_val = settings.value("TranslateY").toDouble();
  model_transform_.move_z_val = settings.value("TranslateZ").toDouble();

  model_transform_.axis_x_val = settings.value("RotateX").toDouble();
  model_transform_.axis_y_val = settings.value("RotateY").toDouble();
  model_transform_.axis_z_val = settings.value("RotateZ").toDouble();

  model_options_.model_draw_parameter_line.color =
      settings.value("LineColor", QColor(Qt::white)).value<QColor>();
  model_options_.model_draw_parameter_line.type =
      settings.value("LineType").toInt();
  model_options_.model_draw_parameter_line.size =
      settings.value("SizeLine").toInt();

  model_options_.model_draw_parameter_vertex.color =
      settings.value("PointColor", QColor(Qt::red)).value<QColor>();
  model_options_.model_draw_parameter_vertex.type =
      settings.value("PointType").toInt();
  model_options_.model_draw_parameter_vertex.size =
      settings.value("SizePoint").toInt();

  settings.endGroup();
}

void ModelSettings::DefaultInitializingSettings() {
  model_options_.projection = 0;
  model_transform_.scale_val = 1;
  model_options_.backgraund_color = Qt::black;

  model_transform_.move_x_val = 0.0;
  model_transform_.move_y_val = 0.0;
  model_transform_.move_z_val = 0.0;

  model_transform_.axis_x_val = 0.0;
  model_transform_.axis_y_val = 0.0;
  model_transform_.axis_z_val = 0.0;

  model_options_.model_draw_parameter_line.color = Qt::white;
  model_options_.model_draw_parameter_line.type = 0;
  model_options_.model_draw_parameter_line.size = 1;

  model_options_.model_draw_parameter_vertex.color = Qt::red;
  model_options_.model_draw_parameter_vertex.type = 0;
  model_options_.model_draw_parameter_vertex.size = 1;
}
}  // namespace my_space
