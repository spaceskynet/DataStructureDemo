/**
 * @file gui.h
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief UI 界面相关的声明
 * @version 0.1
 * @date 2022-06-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "utils.h"
#include "Widgets/ui_changeUnitSizeDialog.h"
#include "Widgets/ui_createObjectDialog.h"
#include "Widgets/ui_inputDialog.h"
#include "Widgets/ui_about.h"
#include <memory>

class PartitionIO;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief 主窗口类
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::unique_ptr<Ui::MainWindow> ui;
    QApplication* App;

    std::unique_ptr<Collection> data_structures;
    PartitionIO* part;

public:
    MainWindow(QApplication* App, QWidget* parent = nullptr);
    ~MainWindow();
    void setup();
    void update();

    void bindLinkedListButton();
    void bindArrayButton();
    void bindStackButton();
    void bindHeapButton();
    void bindTreeButton();
    void bindUndirectionGraphButton();
    void bindDirectionGraphButton();

public slots:
    void changeUnitSum(int);
    void changeUnitSize(int);
    void clearPartition();
    void locateBlock();
};

int customWarning(const char*);
int customWarning(QString);
int customQuestion(const char*);
int customQuestion(QString);

