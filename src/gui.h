#pragma once
#include "utils.h"
#include "Widgets/ui_changeUnitSizeDialog.h"
#include "Widgets/ui_createObjectDialog.h"
#include "Widgets/ui_inputDialog.h"
#include <memory>

class PartitionIO;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::unique_ptr<Ui::MainWindow> ui;
    QApplication* App;

    std::unique_ptr<Collection> data_structures;
    PartitionIO* part;

    std::unique_ptr<UiDialog> changeUnitSizeDialog;
    
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
    void changeUnitSize();
    void clearPartition();
    void locateBlock();
};

int customWarning(const char*);
int customWarning(QString);
int customQuestion(const char*);
int customQuestion(QString);

