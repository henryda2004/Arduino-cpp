#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    QTimer* timer;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_UNO = 66;
    static const quint16 arduino_MEGA = 67;
    QString arduino_puerto;
    bool arduino_esta_disponible;
    void buscaYconectaArduino();
};

#endif // MAINWINDOW_H
