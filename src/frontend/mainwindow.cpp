#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connections();
  set_range();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::connections() {
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_brl, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_brr, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  //    connect(ui->pushButton_eq,SIGNAL(clicked()),this,SLOT(digits_numbers()));
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString label_text = ui->lineEdit->text();

  if (label_text == "0" || label_text == "ERROR") {
    label_text = button->text();
    if ((button->text().length() >= 3 || button->text() == "ln") &&
        button->text() != "mod") {
      label_text += "(";
    }
  } else {
    label_text += button->text();
    if ((button->text().length() >= 3 || button->text() == "ln") &&
        button->text() != "mod") {
      label_text += "(";
    }
  }
  ui->lineEdit->setText(label_text);
}

void MainWindow::on_pushButton_AC_clicked() { ui->lineEdit->setText("0"); }

void MainWindow::on_pushButton_eq_clicked() {
  QString label_text = ui->lineEdit->text();
  label_text += "=";
  QByteArray byteArray = label_text.toUtf8();
  const char *charArray = byteArray.constData();
  char string[256];
  qstrncpy(string, charArray, 255);
  string[255] = '\0';
  double res = 0;
  if (!Smart_calc(string, &res, 0)) {
    QString result = QString::number(res);
    ui->lineEdit->setText(result);
  } else {
    ui->lineEdit->setText("ERROR");
  }
}

void MainWindow::on_pushButton_back_clicked() {
  QString label_text = ui->lineEdit->text();
  label_text.chop(1);
  ui->lineEdit->setText(label_text);
}

void MainWindow::set_range() {
  x0 = ui->spin_X0->text().toDouble();
  x1 = ui->spin_X1->text().toDouble();
  y0 = ui->spin_Y0->text().toDouble();
  y1 = ui->spin_Y1->text().toDouble();
  ;
  ui->qcustomplot->xAxis->setRange(x0, x1);
  ui->qcustomplot->yAxis->setRange(y0, y1);
  ui->qcustomplot->xAxis->setLabel("x");
  ui->qcustomplot->yAxis->setLabel("y");
}

void MainWindow::on_pushButton_graph_clicked() {
  ui->qcustomplot->clearGraphs();
  x.clear();
  y.clear();
  QString label_text = ui->lineEdit->text();
  label_text += "=";
  QByteArray byteArray = label_text.toUtf8();
  const char *charArray = byteArray.constData();
  char string[256];
  qstrncpy(string, charArray, 255);
  string[255] = '\0';
  double res = 0;

  h = 0.1;
  x0 = ui->spin_X0->text().toDouble();
  x1 = ui->spin_X1->text().toDouble();
  y0 = ui->spin_Y0->text().toDouble();
  y1 = ui->spin_Y1->text().toDouble();
  ;
  if (x0 < x1 && y0 < y1) {
    ui->qcustomplot->xAxis->setRange(x0, x1);
    ui->qcustomplot->yAxis->setRange(y0, y1);
    if (x0 < 0 && (label_text.contains("log(") || label_text.contains("ln(") ||
                   label_text.contains("sqrt("))) {
      x0 = 0;
    }
    if (label_text.contains("acos(") || label_text.contains("asin(")) {
      if (x0 < -1) x0 = -1;
      if (x1 > 1) x1 = 1;
    }
    N = (x1 - x0) / h + 2;

    for (X = x0; X <= x1; X += h) {
      if (!Smart_calc(string, &res, X)) {
        Y = res;
        x.push_back(X);
        y.push_back(Y);
      } else {
        ui->lineEdit->setText("ERROR");
      }
    }

    ui->qcustomplot->addGraph();
    ui->qcustomplot->graph(0)->addData(x, y);
    ui->qcustomplot->replot();
  } else {
    ui->lineEdit->setText("ERROR");
  }
}
