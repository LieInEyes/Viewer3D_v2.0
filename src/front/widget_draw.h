#ifndef VIEWER3D_V2_0_WIDGET_DRAW_H
#define VIEWER3D_V2_0_WIDGET_DRAW_H

#include <QGLWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include <cmath>

#include "common_front.h"
#include "model_settings.h"

class WidgetDraw : public QGLWidget {
  Q_OBJECT

 public:
  WidgetDraw() = delete;
  explicit WidgetDraw(QWidget *parent = nullptr);
  WidgetDraw(const WidgetDraw &other) = delete;
  WidgetDraw(WidgetDraw &&other) noexcept = delete;
  ~WidgetDraw() override = default;

  WidgetDraw &operator=(const WidgetDraw &other) = delete;
  WidgetDraw &operator=(WidgetDraw &&other) noexcept = delete;

 public:
  void SetCurrentPositionModel(my_space::model_position *current_position_model);

 public:
  float max_coordinate_;
  bool model_exists_;
  my_space::ModelSettings setting_3d_model_;

 private:
  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void MoveModel() const;
  void InitializeOption() const;
  void DrawModel();

 private:
  float fov_;
  float heap_height_;
  float xRot_;
  float yRot_;
  QPoint mPos_;

  my_space::model_position *current_position_model_;
};

#endif  // VIEWER3D_V2_0_WIDGET_DRAW_H
