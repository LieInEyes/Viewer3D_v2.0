#ifndef VIEWER3D_V2_0_COMMON_FRONT_H
#define VIEWER3D_V2_0_COMMON_FRONT_H

#include <QColor>
#include <QString>

namespace my_space {

typedef struct data_draw_parameter {
  QColor color;
  int size;
  int type;
} model_draw_parameter;

typedef struct data_options {
  QString file_path;
  int projection;
  QColor backgraund_color;

  model_draw_parameter model_draw_parameter_line;
  model_draw_parameter model_draw_parameter_vertex;
} model_options;

}  // namespace my_space

#endif  // VIEWER3D_V2_0_COMMON_FRONT_H
