#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include "iostream"
#include <thread>
#include <QRegularExpression>

void MainWindow::buscaYconectaArduino(){
    arduino_esta_disponible = false;
    arduino_puerto = "";
    arduino = new QSerialPort;

    QString nombreDispositivoSerial = "";
    int nombreProductID = 0;

    qDebug() << "Puertos disponibles: " << QSerialPortInfo::availablePorts().length();
            foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
            qDebug() << "Identificador del fabricante (VENDOR ID): " << serialPortInfo.hasVendorIdentifier();
            if(serialPortInfo.hasVendorIdentifier()){
                qDebug() << "ID Vendedor " << serialPortInfo.vendorIdentifier();
                qDebug() << "ID Producto: " << serialPortInfo.productIdentifier();

                if(serialPortInfo.productIdentifier() == arduino_UNO || serialPortInfo.productIdentifier() == arduino_MEGA){
                    arduino_esta_disponible = true;
                    nombreDispositivoSerial = serialPortInfo.portName();
                    nombreProductID = serialPortInfo.productIdentifier();
                }
            }

        }

    if(arduino_esta_disponible){
        arduino_puerto = nombreDispositivoSerial;
        arduino ->setPortName(arduino_puerto);
        arduino->open(QIODevice::ReadWrite);
        arduino->setDataBits(QSerialPort::Data8);
        arduino ->setBaudRate(QSerialPort::Baud115200);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        ui->label->clear();
        qDebug() << "Producto: " << nombreProductID;

        if(nombreProductID == 67) ui->label->setText("Arduino UNO R3 conectado");
        else if(nombreProductID == 68) ui->label->setText("Arduino Mega conectado");
        else ui->label->setText("Error 3");
    }
    else{
        ui->label->clear();
        ui->label->setText("No hay arduino");
    }
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buscaYconectaArduino();

    // Initialize the timer to trigger every 1 second
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_3_clicked()));
    timer->start(500); // Trigger every 1 second
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    buscaYconectaArduino();
}

void MainWindow::on_pushButton_2_clicked(bool checked)
{
    if(arduino_esta_disponible && arduino->isWritable()){
        if(checked){
            arduino->write("1\n");
        }
        else{
            arduino->write("2\n");
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(arduino_esta_disponible && arduino->isWritable()){
        arduino->write("3\n");
        if(arduino->isReadable()){
            QByteArray datoLeido = arduino->readAll();
            QString str(datoLeido); // convert QByteArray to QString
            QStringList tokens = str.split(","); // split the string into substrings
            if (tokens.size() == 3) { // make sure we received three integers
                int analogValue = std::stoi(tokens[0].toStdString());
                int upButton = std::stoi(tokens[1].toStdString());
                int downButton = std::stoi(tokens[2].toStdString());
                qDebug() << "Potenciometro:" << analogValue << "Up:" << upButton << "Down:" << downButton;
                if (upButton == 1){
                    std::cout<<"yendo pa rriba" << std::endl;
                }
            }
        }

    }
}

