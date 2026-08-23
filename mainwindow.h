#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include <functional>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void ClearOutput();

    void Levenstein_slot();
    void DamerauLevenstein_slot();
    void LCS_slot();
    void Hamming_slot();

private:
    Ui::MainWindow *ui;

    void MetricSlotWrapper(std::function<size_t(std::wstring, std::wstring)> func, QLabel* outputLabel);
};
#endif // MAINWINDOW_H
