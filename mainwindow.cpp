#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "include/editDistance.h"

void MainWindow::MetricSlotWrapper(std::function<size_t(std::wstring, std::wstring)> func, QLabel* outputLabel) {
    std::wstring str1 = ui->textEdit->toPlainText().toStdWString();
    std::wstring str2 = ui->textEdit_2->toPlainText().toStdWString();
    size_t distance = func(str1, str2);
    QString output = QString("%1").arg(distance);
    outputLabel->setText(output);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Levenstein_slot() {
    MetricSlotWrapper(Levenstein<wchar_t>, ui->LevensteinLabel);
}

void MainWindow::DamerauLevenstein_slot() {
    MetricSlotWrapper(DamerauLevenstein<wchar_t>, ui->DamerauLevensteinLabel);
}

void MainWindow::LCS_slot() {
    MetricSlotWrapper(Lcs<wchar_t>, ui->LCSLabel);
}

void MainWindow::Hamming_slot() {
    MetricSlotWrapper(Hamming<wchar_t>, ui->HammingLabel);
}