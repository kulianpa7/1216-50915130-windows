#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect save button to the saveToFile slot
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::saveToFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (fileName.isEmpty()) {
        return; // User canceled the save dialog
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing: %1").arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // Save the content of textEdit
    file.close();

    QMessageBox::information(this, tr("Success"), tr("File saved successfully!"));
}
