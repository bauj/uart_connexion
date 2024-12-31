#pragma once

#include <QWidget>
#include <QMainWindow>
#include "CentralPanelWidget.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:


private:
    CentralPanelWidget *centralWidget;
};