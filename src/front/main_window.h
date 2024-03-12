#ifndef VIEWER3D_V2_0_MAIN_WINDOW_H
#define VIEWER3D_V2_0_MAIN_WINDOW_H

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>
#include <string>

#include "../controller/controller.h"
#include "../includes/qtgifimage/src/gifimage/qgifimage.h"
#include "common_front.h"
#include "model_settings.h"
#include "ui_main_window.h"
#include "widget_draw.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  MainWindow(const MainWindow &other) = delete;
  MainWindow(MainWindow &&other) noexcept = delete;
  ~MainWindow() override;

  MainWindow &operator=(const MainWindow &other) = delete;
  MainWindow &operator=(MainWindow &&other) noexcept = delete;

 private slots:

  void on_qaction_open_file_triggered();
  void on_qaction_clear_model_triggered();
  void on_qaction_save_bmp_triggered();
  void on_qaction_save_jpeg_triggered();
  void on_qaction_save_gif_triggered();
  void AddFrameGIF();

  void on_button_draw_clicked();
  void on_combo_box_projection_type_currentIndexChanged(const QString &arg1);
  void on_spin_box_scale_model_valueChanged(double arg1);
  void on_button_select_background_color_clicked();

  void on_spin_box_movement_x_valueChanged(double arg1);
  void on_spin_box_movement_y_valueChanged(double arg1);
  void on_spin_box_movement_z_valueChanged(double arg1);

  void on_spin_box_rotate_x_valueChanged(double arg1);
  void on_spin_box_rotate_y_valueChanged(double arg1);
  void on_spin_box_rotate_z_valueChanged(double arg1);

  void on_button_select_color_line_clicked();
  void on_combo_box_type_line_currentIndexChanged(const QString &arg1);
  void on_slider_size_line_valueChanged(int value);

  void on_button_select_color_point_clicked();
  void on_combo_box_type_vertex_currentIndexChanged(const QString &arg1);
  void on_slider_size_vertex_valueChanged(int value);

 private:
  QString GetPath();
  void InitializingValuesFrontAfterStart();
  void InitializingValuesFrontDefault();
  void UpdateFrame();

 private:
  Ui::MainWindow *ui_;
  my_space::Controller controller_;

  QGifImage *gifimage_;
  QTimer *delay_;
  QString *path_to_save_gif_;
  int frame_;

  bool is_open_file_;
};

#endif  // VIEWER3D_V2_0_MAIN_WINDOW_H
