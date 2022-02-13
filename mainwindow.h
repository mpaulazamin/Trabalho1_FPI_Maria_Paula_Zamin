#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core.hpp>
#include "opencv2/core/core.hpp"
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonDisplayImage_clicked();
    void on_pushButtonCopyImage_clicked();
    void on_pushButtonInvertVertical_clicked();
    void on_pushButtonInvertHorizontal_clicked();
    void on_pushButtonConvertGrayscale_clicked();
    void on_pushButtonSaveNewImage_clicked();
    void on_pushButtonQuantizeImage_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
