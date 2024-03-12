#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      gifimage_(nullptr),
      delay_(nullptr),
      path_to_save_gif_(nullptr),
      frame_(0),
      is_open_file_(false) {
  ui_->setupUi(this);
  ui_->widget_draw->setting_3d_model_.LoadSettings();
  InitializingValuesFrontAfterStart();
}

MainWindow::~MainWindow() {
  ui_->widget_draw->setting_3d_model_.SaveSettings();
  delete ui_;
  if (path_to_save_gif_) {
    delete path_to_save_gif_;
    path_to_save_gif_ = nullptr;
  }
  if (delay_) {
    delete delay_;
    delay_ = nullptr;
  }
  if (gifimage_) {
    delete gifimage_;
    gifimage_ = nullptr;
  }
}

//// меню открыть файл
void MainWindow::on_qaction_open_file_triggered() {
  QString filter = "3DModel file (*.obj)";
  ui_->widget_draw->setting_3d_model_.model_options_.file_path =
      QFileDialog::getOpenFileName(this, "Открыть файл", QDir::homePath(),
                                   filter);
  QFileInfo fileinfo(
      ui_->widget_draw->setting_3d_model_.model_options_.file_path);
  QString file_name = fileinfo.fileName();
  std::string file_path = ui_->widget_draw->setting_3d_model_.model_options_
                              .file_path.toStdString();

  try {
    unsigned int count_vertex;
    unsigned int count_polygon;
    controller_.parse_after_open_file(file_path, count_vertex, count_polygon,
                                      ui_->widget_draw->max_coordinate_);
    ui_->label_count_vertex->setText("Количество вершин: " +
                                     QString::number(count_vertex));
    ui_->label_count_polygon->setText("Количество полигонов: " +
                                      QString::number(count_polygon));
    ui_->label_name_file->setText("Имя файла: " + file_name);
    is_open_file_ = true;
  } catch (const my_space::BackEndError &ex) {
    QMessageBox::warning(this, "Ошибка", ex.what());
  }
  ui_->widget_draw->model_exists_ = false;
}

//// меню сбросить настройки
void MainWindow::on_qaction_clear_model_triggered() {
  ui_->widget_draw->setting_3d_model_.DefaultInitializingSettings();
  InitializingValuesFrontDefault();
}

//// доп функция для записи в переменную пути куда сохранять картинку
QString MainWindow::GetPath() {
  return QFileDialog::getExistingDirectory(
      ui_->widget_draw, tr("Choose files"), QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

//// меню сохранить изображение бмп
void MainWindow::on_qaction_save_bmp_triggered() {
  QString save_path = GetPath();
  ui_->widget_draw->grabFrameBuffer().save(
      save_path + "/screenshot" + QTime::currentTime().toString() + ".bmp");
}

//// меню сохранить изображение жпек
void MainWindow::on_qaction_save_jpeg_triggered() {
  QString save_path = GetPath();
  ui_->widget_draw->grabFrameBuffer().save(
      save_path + "/screenshot" + QTime::currentTime().toString() + ".jpeg");
}

//// что то для гифок
void MainWindow::AddFrameGIF() {
  frame_++;
  gifimage_->addFrame(ui_->widget_draw->grabFrameBuffer(), 100);
  if (frame_ == 50) {
    delay_->stop();
    gifimage_->save(*path_to_save_gif_ + "/screengif" +
                    QTime::currentTime().toString() + ".gif");
    delete gifimage_;
  }
}

//// меню сохранить гиф анимацию
void MainWindow::on_qaction_save_gif_triggered() {
  path_to_save_gif_ = new QString(GetPath());
  gifimage_ = new QGifImage();
  frame_ = 0;
  delay_ = new QTimer(this);
  connect(delay_, SIGNAL(timeout()), this, SLOT(AddFrameGIF()));
  delay_->start(100);
}

//// кнопка отрисовать
void MainWindow::on_button_draw_clicked() {
    if (is_open_file_) {
        ui_->widget_draw->SetCurrentPositionModel(controller_.UpdateFrame(
                ui_->widget_draw->setting_3d_model_.model_transform_));

        ui_->widget_draw->model_exists_ = true;
        ui_->widget_draw->update();
    }
}

//// кнопка выбора типа проекции
void MainWindow::on_combo_box_projection_type_currentIndexChanged(
    const QString &arg1) {
  ui_->widget_draw->setting_3d_model_.model_options_.projection =
      ui_->combo_box_projection_type->currentIndex();
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// кнопка изменения значения масштаба проекции
void MainWindow::on_spin_box_scale_model_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.scale_val = arg1;
  UpdateFrame();
}

//// кнопка выбора фона проекции
void MainWindow::on_button_select_background_color_clicked() {
  ui_->widget_draw->setting_3d_model_.model_options_.backgraund_color =
      QColorDialog::getColor(Qt::white, this);
  ui_->widget_draw->update();
}

//// кнопка изменения значения по оси x для движения
void MainWindow::on_spin_box_movement_x_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.move_x_val = arg1;
  UpdateFrame();
}

//// кнопка изменения значения по оси y для движения
void MainWindow::on_spin_box_movement_y_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.move_y_val = arg1;
  UpdateFrame();
}

//// кнопка изменения значения по оси z для движения
void MainWindow::on_spin_box_movement_z_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.move_z_val = arg1;
  UpdateFrame();
}

//// кнопка изменения значения по оси x для вращения
void MainWindow::on_spin_box_rotate_x_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.axis_x_val = arg1;
  UpdateFrame();
}

//// кнопка изменения значения по оси y для вращения
void MainWindow::on_spin_box_rotate_y_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.axis_y_val = arg1;
  UpdateFrame();
}

//// кнопка изменения значения по оси z для вращения
void MainWindow::on_spin_box_rotate_z_valueChanged(double arg1) {
  ui_->widget_draw->setting_3d_model_.model_transform_.axis_z_val = arg1;
  UpdateFrame();
}

void MainWindow::UpdateFrame() {
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->SetCurrentPositionModel(controller_.UpdateFrame(
        ui_->widget_draw->setting_3d_model_.model_transform_));
    ui_->widget_draw->update();
  }
}

//// кнопка выбора цвета ребра
void MainWindow::on_button_select_color_line_clicked() {
  ui_->widget_draw->setting_3d_model_.model_options_.model_draw_parameter_line
      .color = QColorDialog::getColor(Qt::white, this);
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// кнопка выбора типа ребра
void MainWindow::on_combo_box_type_line_currentIndexChanged(
    const QString &arg1) {
  ui_->widget_draw->setting_3d_model_.model_options_.model_draw_parameter_line
      .type = ui_->combo_box_type_line->currentIndex();

  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// слайдер выбора размера ребра
void MainWindow::on_slider_size_line_valueChanged(int value) {
  ui_->widget_draw->setting_3d_model_.model_options_.model_draw_parameter_line
      .size = value;
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// кнпока выбора цвета вершины
void MainWindow::on_button_select_color_point_clicked() {
  ui_->widget_draw->setting_3d_model_.model_options_.model_draw_parameter_vertex
      .color = QColorDialog::getColor(Qt::red, this);
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// кнопка выбора типа вершины
void MainWindow::on_combo_box_type_vertex_currentIndexChanged(
    const QString &arg1) {
  ui_->widget_draw->setting_3d_model_.model_options_.model_draw_parameter_vertex
      .type = ui_->combo_box_type_vertex->currentIndex();
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// слайдер выбора размера вершины
void MainWindow::on_slider_size_vertex_valueChanged(int value) {
  ui_->widget_draw->setting_3d_model_.model_options_.model_draw_parameter_vertex
      .size = value;
  if (ui_->widget_draw->model_exists_) {
    ui_->widget_draw->update();
  }
}

//// загрузка настроек
void MainWindow::InitializingValuesFrontAfterStart() {
  ui_->combo_box_projection_type->setCurrentIndex(
      ui_->widget_draw->setting_3d_model_.model_options_.projection);
  ui_->spin_box_scale_model->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.scale_val);

  ui_->spin_box_movement_x->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.move_x_val);
  ui_->spin_box_movement_y->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.move_y_val);
  ui_->spin_box_movement_z->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.move_z_val);

  ui_->spin_box_rotate_x->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.axis_x_val);
  ui_->spin_box_rotate_y->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.axis_y_val);
  ui_->spin_box_rotate_z->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.axis_z_val);

  ui_->combo_box_type_line->setCurrentIndex(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_line.type);
  ui_->slider_size_line->setValue(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_line.size);

  ui_->combo_box_type_vertex->setCurrentIndex(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_vertex.type);
  ui_->slider_size_vertex->setValue(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_vertex.size);

  ui_->widget_draw->update();
}

void MainWindow::InitializingValuesFrontDefault() {
  ui_->combo_box_projection_type->setCurrentIndex(
      ui_->widget_draw->setting_3d_model_.model_options_.projection);
  ui_->spin_box_scale_model->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.scale_val);

  ui_->spin_box_movement_x->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.move_x_val);
  ui_->spin_box_movement_y->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.move_y_val);
  ui_->spin_box_movement_z->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.move_z_val);

  ui_->spin_box_rotate_x->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.axis_x_val);
  ui_->spin_box_rotate_y->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.axis_y_val);
  ui_->spin_box_rotate_z->setValue(
      ui_->widget_draw->setting_3d_model_.model_transform_.axis_z_val);

  ui_->combo_box_type_line->setCurrentIndex(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_line.type);
  ui_->slider_size_line->setValue(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_line.size);

  ui_->combo_box_type_vertex->setCurrentIndex(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_vertex.type);
  ui_->slider_size_vertex->setValue(
      ui_->widget_draw->setting_3d_model_.model_options_
          .model_draw_parameter_vertex.size);

  ui_->widget_draw->update();
}
