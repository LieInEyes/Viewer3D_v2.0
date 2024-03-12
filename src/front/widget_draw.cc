#include "widget_draw.h"

WidgetDraw::WidgetDraw(QWidget *parent)
    : QGLWidget(parent),
      max_coordinate_(1),
      fov_(60.0 * M_PI / 180),
      heap_height_(3 / (2 * tan(fov_ / 2))),
      xRot_(0),
      yRot_(0),
      model_exists_(false),
      current_position_model_(nullptr) {}

void WidgetDraw::SetCurrentPositionModel(
    my_space::model_position *current_position_model) {
  current_position_model_ = current_position_model;
}

void WidgetDraw::MoveModel() const {
  glTranslatef(0, 0, -heap_height_ * 3);
  glRotatef(xRot_, 1, 0, 0);
  glRotatef(yRot_, 0, 1, 0);
}

void WidgetDraw::InitializeOption() const {
  if (setting_3d_model_.model_options_.model_draw_parameter_line.type == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else if (setting_3d_model_.model_options_.model_draw_parameter_line.type ==
             1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(0, 0x00ff);
  }

  glLineWidth(setting_3d_model_.model_options_.model_draw_parameter_line.size);

  if (setting_3d_model_.model_options_.model_draw_parameter_vertex.type == 0) {
    glDisable(GL_POINT_SMOOTH);
  } else if (setting_3d_model_.model_options_.model_draw_parameter_vertex
                 .type == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (setting_3d_model_.model_options_.model_draw_parameter_vertex
                 .type == 2) {
    glDisable(GL_POINT_SMOOTH);
  }

  glPointSize(
      setting_3d_model_.model_options_.model_draw_parameter_vertex.size);

  if (!setting_3d_model_.model_options_.projection) {
    glOrtho(-max_coordinate_, max_coordinate_, -max_coordinate_,
            max_coordinate_, -max_coordinate_ * 100, max_coordinate_ * 100);
  } else {
    glFrustum(-max_coordinate_, max_coordinate_, -max_coordinate_,
              max_coordinate_, heap_height_, max_coordinate_ * 100);
  }
}

void WidgetDraw::DrawModel() {
  InitializeOption();
  MoveModel();

  glVertexPointer(3, GL_FLOAT, 0,
                  current_position_model_->vertex_coordinates.data());

  glEnableClientState(GL_VERTEX_ARRAY);
  glColor3f(
      setting_3d_model_.model_options_.model_draw_parameter_line.color.redF(),
      setting_3d_model_.model_options_.model_draw_parameter_line.color.greenF(),
      setting_3d_model_.model_options_.model_draw_parameter_line.color.blueF());

  auto iter = current_position_model_->vertex_index.data();
  for (unsigned int i = 0;
       i < current_position_model_->vertex_count_index.size(); i++) {
    glDrawElements(GL_LINE_LOOP, current_position_model_->vertex_count_index[i],
                   GL_UNSIGNED_INT, iter);
    iter += current_position_model_->vertex_count_index[i];
  }

  if (setting_3d_model_.model_options_.model_draw_parameter_vertex.type) {
    glColor3f(setting_3d_model_.model_options_.model_draw_parameter_vertex.color
                  .redF(),
              setting_3d_model_.model_options_.model_draw_parameter_vertex.color
                  .greenF(),
              setting_3d_model_.model_options_.model_draw_parameter_vertex.color
                  .blueF());
    glDrawArrays(GL_POINTS, 1,
                 current_position_model_->vertex_coordinates.size() / 3 - 1);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void WidgetDraw::mousePressEvent(QMouseEvent *mo) { mPos_ = mo->pos(); }

void WidgetDraw::mouseMoveEvent(QMouseEvent *mo) {
  xRot_ = 0.5 / M_PI * (mo->pos().y() - mPos_.y());
  yRot_ = 0.5 / M_PI * (mo->pos().x() - mPos_.x());
  update();
}

void WidgetDraw::initializeGL() {
  glClearColor(setting_3d_model_.model_options_.backgraund_color.redF(),
               setting_3d_model_.model_options_.backgraund_color.greenF(),
               setting_3d_model_.model_options_.backgraund_color.blueF(),
               setting_3d_model_.model_options_.backgraund_color.alphaF());
  glEnable(GL_DEPTH_TEST);
}

void WidgetDraw::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void WidgetDraw::paintGL() {
  glClearColor(setting_3d_model_.model_options_.backgraund_color.redF(),
               setting_3d_model_.model_options_.backgraund_color.greenF(),
               setting_3d_model_.model_options_.backgraund_color.blueF(),
               setting_3d_model_.model_options_.backgraund_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (current_position_model_) {
    DrawModel();
  }
}
