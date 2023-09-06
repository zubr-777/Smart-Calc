#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(get_button_value()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::get_button_value() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + button->text());
}

void MainWindow::get_function_value() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + button->text() + "(");
}

void MainWindow::on_pushButton_eq_clicked() {
  QString expression;
  expression.clear();
  expression = ui->label->text();
  draw_graph(expression, expression.contains("x"));
}

void MainWindow::draw_graph(QString expression, bool with_variable) {
  QVector<double> x_coord, y_coord;

  double x_min = ui->doubleSpinBox->value();
  double x_max = ui->doubleSpinBox_2->value();
  double step = fabs(x_max - x_min) / 100000;
  // variables for calculating the expression
  int status = 0;
  double result;

  double x = x_min;
  while (x <= x_max) {
    if (fabs(x) < step) {
      x = 0;
    }
    QByteArray mass_chars = expression.toLocal8Bit();
    char *ptr_mass_chars = mass_chars.data();
    if ((int)strlen(ptr_mass_chars)) {
        setlocale(LC_NUMERIC, "C");
        status = calc_function(ptr_mass_chars, x, &result);
        if (status != 0) {
          result = acos(2);
        }
        if (!isnan(result)) {
          x_coord.push_back(x);
          if (std::numeric_limits<qreal>::max() < result)
            result = 1000000;
          if (result < -std::numeric_limits<qreal>::max())
            result = -1000000;
          y_coord.push_back(result);
        }
    }
    x += step;
  }
  QByteArray mass_chars = expression.toLocal8Bit();
  char *ptr_mass_chars = mass_chars.data();
  if (x_coord.length() == y_coord.length() && (int)strlen(ptr_mass_chars)) {
    if (!with_variable)
      ui->label->setText(QString::number(result, 'g', 8));

    x_min = *std::min_element(x_coord.begin(), x_coord.end());
    x_max = *std::max_element(x_coord.begin(), x_coord.end());
    double y_min = *std::min_element(y_coord.begin(), y_coord.end());
    double y_max = *std::max_element(y_coord.begin(), y_coord.end());
    double y_delta = (y_max - y_min) / 10;
    if (!y_delta)
      y_delta = 10;
    ui->widget->clearGraphs();
    ui->widget->addGraph();

    ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));

    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min - y_delta, y_max + y_delta);
    ui->widget->graph(0)->rescaleAxes();

    ui->widget->graph(0)->addData(x_coord, y_coord);
    ui->widget->replot();
  } else
    ui->label->setText("Impossible to build a graph");
}

void MainWindow::on_pushButton_truncate_clicked() { ui->label->clear(); }
