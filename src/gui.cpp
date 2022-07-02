/**
 * @file gui.cpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief UI 界面相关的实现
 * @version 0.1
 * @date 2022-06-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define _CRT_SECURE_NO_WARNINGS
#include "gui.h"
#include <QObject>
#include <QDebug>

MainWindow::MainWindow(QApplication* App, QWidget* parent)
    : QMainWindow(parent)
{
    ui = std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow);
    ui->setupUi(this);

    data_structures = std::make_unique<Collection>();
    data_structures->part->setMainWindow(ui.get());
    this->part = data_structures->part;

    this->App = App;

    this->setup();
}

MainWindow::~MainWindow()
{
}

/**
 * @brief 初始化 UI 界面并绑定按钮
 * 
 */
void MainWindow::setup()
{
    // 单元大小与单元总数，绑定相关信号与槽
    unsigned int unit_size = part->getUnitSize();
    QObject::connect(ui->unitSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeUnitSum(int)));

    ui->unitSizeSpinBox->setValue(unit_size);
    ui->unitSizeSpinBox->setMinimum(1);

    QObject::connect(ui->unitSizeLabel, &QClickedLabel::clicked, this, [this]() {
        auto changeUnitSizeDialog = std::unique_ptr<UiDialog>(new UiDialog);
        changeUnitSizeDialog->unitSizeSpinBox->setValue(ui->unitSizeSpinBox->value());

        if (changeUnitSizeDialog->exec() == QDialog::Accepted && 
            changeUnitSizeDialog->unitSizeSpinBox->value() != ui->unitSizeSpinBox->value()) {
            changeUnitSize(changeUnitSizeDialog->unitSizeSpinBox->value());
        }
    });

    // 内存分配算法
    ui->memoryAllocationAlgorithmComboBox->setCurrentIndex(part->getMemoryAllocationAlgorithm());

    QObject::connect(ui->memoryAllocationAlgorithmComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
        part->changeMemoryAllocationAlgorithm((MEMORY_ALLOCATION_ALGORITHM)index);
    });

    // 其它操作
    QObject::connect(ui->clearPartitionPushButton, &QPushButton::clicked, this, [this]() {
        int ret = customWarning("确定要进行操作吗？该操作会重置分区，并删除所有数据结构，操作不可逆!");
            if (ret == QMessageBox::Yes) {
                this->clearPartition();
            }
        });
    QObject::connect(ui->clearOutputInfoPushButton, &QPushButton::clicked, this, [this]() {
        int ret = customWarning("确定要清空下方的输出信息吗？");
            if (ret == QMessageBox::Yes) {
                ui->outputInfoTextEdit->clear();
            }
        });
    
    QObject::connect(ui->locateUnitFreeInfoPushButton, SIGNAL(clicked()), this, SLOT(locateBlock()));
    ui->unitFreeInfoIndexSpinBox->setKeyboardTracking(false);
    QObject::connect(ui->unitFreeInfoIndexSpinBox, SIGNAL(valueChanged(int)), this, SLOT(locateBlock()));

    QObject::connect(ui->writePartitionToFilePushButton, &QPushButton::clicked, this, [this]() {
        part->writeFile();
        part->sendOutput(QString::fromUtf8("已将分区所有数据写入到数据文件!\n"));
        });


    // 绑定 Logo 和 关于界面
    QObject::connect(ui->logoLabel, &QClickedLabel::clicked, this, [this]() {
        Ui::About dialog;
        QObject::connect(dialog.pushButton, &QPushButton::clicked, &dialog, &QDialog::close);
        dialog.exec();
    });

    // 绑定数据结构操作与 UI 界面按钮
    bindLinkedListButton();
    bindArrayButton();
    bindStackButton();
    bindHeapButton();
    bindTreeButton();
    bindUndirectionGraphButton();
    bindDirectionGraphButton();
    // more data structure

    // 更新 UI 界面信息
    update();
    part->printPartitionAddress();
}

/**
 * @brief 更新 UI 界面信息
 * 
 */
void MainWindow::update()
{
    // 根据分区信息更新分区空闲块界面信息
    part->updateBlockFreeInfoMainWindow();

    // 更新 UI 中各数据结构对象个数
    ui->linkedListCountSpinBox->setValue(data_structures->linked_list.size());
    ui->arrayCountSpinBox->setValue(data_structures->my_array.size());
    ui->stackCountSpinBox->setValue(data_structures->my_stack.size());
    ui->heapCountSpinBox->setValue(data_structures->my_heap.size());
    ui->treeCountSpinBox->setValue(data_structures->my_tree.size());
    ui->undirectionGraphCountSpinBox->setValue(data_structures->undirection_graph.size());
    ui->directionGraphCountSpinBox->setValue(data_structures->direction_graph.size());

    // more data structure
    qDebug("UI 界面更新完毕\n");
}

void MainWindow::bindLinkedListButton()
{
// 链表
    // 当前对象的个数
    QObject::connect(ui->linkedListCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->linkedListOptionWidget->setEnabled(false);
        else {
            ui->linkedListOptionWidget->setEnabled(true);
            ui->linkedListIndexSpinBox->setMinimum(0);
            ui->linkedListIndexSpinBox->setMaximum(value - 1);
        }
    });
    // 新建对象
    QObject::connect(ui->linkedListCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(LINKED_LIST, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
    });

    // 默认展示
    QObject::connect(ui->linkedListDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->linkedListIndexSpinBox->value();
        data_structures->linked_list[index]->defaultShow();
    });
    // 链表长度
    QObject::connect(ui->linkedListLengthPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->linkedListIndexSpinBox->value();
        data_structures->linked_list[index]->listLength();
    });
    // 打印所有元素
    QObject::connect(ui->linkedListPrintAllElemPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->linkedListIndexSpinBox->value();
        data_structures->linked_list[index]->printAllElem();
    });
    
    // 销毁对象
    QObject::connect(ui->linkedListDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->linkedListIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的链表吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(LINKED_LIST, index);
            this->update();
        }
        delete[] buffer;
    });

    // 清空链表
    QObject::connect(ui->linkedListClearListPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->linkedListIndexSpinBox->value();
        sprintf(buffer, "确定要清空索引为 %d 的链表吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->linked_list[index]->clearList();
            this->update();
        }
        delete[] buffer;
    });

    // 插入元素
    QObject::connect(ui->linkedListInsertPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->linkedListIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的链表中 pos 处插入元素 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val, pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d %d", &pos, &val) == 2){
                data_structures->linked_list[index]->insert(pos, val);
                this->update();
            }
        }
        delete[] buffer;
    });

    // 删除元素
    QObject::connect(ui->linkedListDeletePushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->linkedListIndexSpinBox->value();
        sprintf(buffer, "删除索引为 %d 的链表 pos 处的元素", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &pos) == 1) {
                data_structures->linked_list[index]->del(pos);
                this->update();
            }
        }
        delete[] buffer;
    });

    // 按位序获取元素
    QObject::connect(ui->linkedListGetElemPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->linkedListIndexSpinBox->value();
        sprintf(buffer, "获取索引为 %d 的链表位序为 pos 的元素", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &pos) == 1) {
                data_structures->linked_list[index]->getElem(pos);
                this->update();
            }
        }
        delete[] buffer;
    });

    // 按值寻找元素
    QObject::connect(ui->linkedListLocateElemPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->linkedListIndexSpinBox->value();
        sprintf(buffer, "获取索引为 %d 的链表第一个值为 val 的元素", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &val) == 1) {
                data_structures->linked_list[index]->locateElem(val);
                this->update();
            }
        }
        delete[] buffer;
    });
}

void MainWindow::bindArrayButton()
{
// 数组
    // 当前对象的个数
    QObject::connect(ui->arrayCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->arrayOptionWidget->setEnabled(false);
        else {
            ui->arrayOptionWidget->setEnabled(true);
            ui->arrayIndexSpinBox->setMinimum(0);
            ui->arrayIndexSpinBox->setMaximum(value - 1);
        }
        });
    // 新建对象
    QObject::connect(ui->arrayCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(ARRAY, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
        });

    // 默认展示
    QObject::connect(ui->arrayDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->arrayIndexSpinBox->value();
        data_structures->my_array[index]->show();
        });
    // 数组长度
    QObject::connect(ui->arrayLengthPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->arrayIndexSpinBox->value();
        data_structures->my_array[index]->length();
        });
    // 打印所有元素
    QObject::connect(ui->arrayPrintAllElemPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->arrayIndexSpinBox->value();
        data_structures->my_array[index]->display();
        });

    // 销毁对象
    QObject::connect(ui->arrayDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的数组吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(ARRAY, index);
            this->update();
        }
        delete[] buffer;
        });

    // 申请空间
    QObject::connect(ui->arrayInitArrayPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "为索引为 %d 的数组申请 size 的容量", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：size"));
        if (dialog.exec() == QDialog::Accepted) {
            int size;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &size) == 1) {
                data_structures->my_array[index]->initArray(size);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 清空数组
    QObject::connect(ui->arrayClearPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "确定要清空索引为 %d 的数组吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->my_array[index]->clear();
            this->update();
        }
        delete[] buffer;
        });

    // 插入元素
    QObject::connect(ui->arrayInsertPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的数组中 pos 处插入元素 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val, pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d %d", &pos, &val) == 2) {
                data_structures->my_array[index]->insert(pos, val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 在尾部插入元素
    QObject::connect(ui->arrayAppendPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的数组尾部插入元素 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &val) == 1) {
                data_structures->my_array[index]->append(val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 删除元素
    QObject::connect(ui->arrayDeletePushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "删除索引为 %d 的数组 pos 处的元素", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &pos) == 1) {
                data_structures->my_array[index]->del(pos);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 按位序获取元素
    QObject::connect(ui->arrayGetElemPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "获取索引为 %d 的数组位序为 pos 的元素", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &pos) == 1) {
                data_structures->my_array[index]->get(pos);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 按值寻找元素
    QObject::connect(ui->arrayLocateElemPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->arrayIndexSpinBox->value();
        sprintf(buffer, "获取索引为 %d 的数组第一个值为 val 的元素", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &val) == 1) {
                data_structures->my_array[index]->locate(val);
                this->update();
            }
        }
        delete[] buffer;
    });
}

void MainWindow::bindStackButton()
{
// 栈
    // 当前对象的个数
    QObject::connect(ui->stackCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->stackOptionWidget->setEnabled(false);
        else {
            ui->stackOptionWidget->setEnabled(true);
            ui->stackIndexSpinBox->setMinimum(0);
            ui->stackIndexSpinBox->setMaximum(value - 1);
        }
        });
    // 新建对象
    QObject::connect(ui->stackCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(STACK, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
        });

    // 默认展示
    QObject::connect(ui->stackDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->stackIndexSpinBox->value();
        data_structures->my_stack[index]->Show();
        });
    // 栈长度
    QObject::connect(ui->stackLengthPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->stackIndexSpinBox->value();
        data_structures->my_stack[index]->StackLength();
        });
    // 打印所有元素
    QObject::connect(ui->stackPrintAllElemPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->stackIndexSpinBox->value();
        data_structures->my_stack[index]->PrintAllElem();
        });

    // 销毁对象
    QObject::connect(ui->stackDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->stackIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的栈吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(STACK, index);
            this->update();
        }
        delete[] buffer;
        });

    // 清空栈
    QObject::connect(ui->stackClearPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->stackIndexSpinBox->value();
        sprintf(buffer, "确定要清空索引为 %d 的栈吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->my_stack[index]->ClearStack();
            this->update();
        }
        delete[] buffer;
        });

    // 压栈
    QObject::connect(ui->stackPushPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->stackIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的栈中压入元素 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &val) == 1) {
                data_structures->my_stack[index]->Push(val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 弹栈
    QObject::connect(ui->stackPopPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->stackIndexSpinBox->value();
        sprintf(buffer, "确定要弹出索引为 %d 的栈的栈顶元素吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->my_stack[index]->Pop();
            this->update();
        }
        delete[] buffer;
        });

    // 获取栈顶元素
    QObject::connect(ui->stackGetTopPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->stackIndexSpinBox->value();
        data_structures->my_stack[index]->GetTop();
        });
}

void MainWindow::bindHeapButton()
{
// 堆
    // 当前对象的个数
    QObject::connect(ui->heapCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->heapOptionWidget->setEnabled(false);
        else {
            ui->heapOptionWidget->setEnabled(true);
            ui->heapIndexSpinBox->setMinimum(0);
            ui->heapIndexSpinBox->setMaximum(value - 1);
        }
        });
    // 新建对象
    QObject::connect(ui->heapCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(HEAP, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
        });

    // 默认展示
    QObject::connect(ui->heapDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->heapIndexSpinBox->value();
        data_structures->my_heap[index]->Show();
        });
    // 堆长度
    QObject::connect(ui->heapLengthPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->heapIndexSpinBox->value();
        data_structures->my_heap[index]->HeapSize();
        });
    // 打印所有元素
    QObject::connect(ui->heapPrintAllElemPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->heapIndexSpinBox->value();
        data_structures->my_heap[index]->HeapPrint();
        });

    // 销毁对象
    QObject::connect(ui->heapDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->heapIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的堆吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(HEAP, index);
            this->update();
        }
        delete[] buffer;
        });

    // 清空堆
    QObject::connect(ui->heapClearPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->heapIndexSpinBox->value();
        sprintf(buffer, "确定要清空索引为 %d 的堆吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->my_heap[index]->HeapClear();
            this->update();
        }
        delete[] buffer;
        });

    // 插入元素
    QObject::connect(ui->heapInsertPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->heapIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的堆中插入元素 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：val"));
        if (dialog.exec() == QDialog::Accepted) {
            int val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &val) == 1) {
                data_structures->my_heap[index]->HeapPush(val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 删除堆顶元素
    QObject::connect(ui->heapPopPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->heapIndexSpinBox->value();
        sprintf(buffer, "确定要删除索引为 %d 的栈的堆顶元素吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->my_heap[index]->HeapPop();
            this->update();
        }
        delete[] buffer;
        });

    // 获取堆顶元素
    QObject::connect(ui->heapGetTopPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->heapIndexSpinBox->value();
        data_structures->my_heap[index]->HeapTop();
        });
}

void MainWindow::bindTreeButton()
{
// 树
    // 当前对象的个数
    QObject::connect(ui->treeCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->treeOptionWidget->setEnabled(false);
        else {
            ui->treeOptionWidget->setEnabled(true);
            ui->treeIndexSpinBox->setMinimum(0);
            ui->treeIndexSpinBox->setMaximum(value - 1);
        }
        });
    // 新建对象
    QObject::connect(ui->treeCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(TREE, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
        });

    // 销毁对象
    QObject::connect(ui->treeDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->treeIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的树吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(TREE, index);
            this->update();
        }
        delete[] buffer;
        });


    // 默认展示
    QObject::connect(ui->treeDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->treeIndexSpinBox->value();
        data_structures->my_tree[index]->show();
        });

    // 树高度
    QObject::connect(ui->treeHeightPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->treeIndexSpinBox->value();
        data_structures->my_tree[index]->height();
        });

    // 树节点数
    QObject::connect(ui->treeNodeCountPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->treeIndexSpinBox->value();
        data_structures->my_tree[index]->count();
        });

    // 树最大度
    QObject::connect(ui->treeMaxDegreePushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->treeIndexSpinBox->value();
        data_structures->my_tree[index]->max_degree();
        });

    // 打印树
    QObject::connect(ui->treePrintPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->treeIndexSpinBox->value();
        data_structures->my_tree[index]->display();
        });

    // 清空树
    QObject::connect(ui->treeClearPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->treeIndexSpinBox->value();
        sprintf(buffer, "确定要清空索引为 %d 的树吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->my_tree[index]->clear();
        }
        delete[] buffer;
        });

    // 插入元素
    QObject::connect(ui->treeInsertPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->treeIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的树的 pos 处插入字符 c", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：c pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            char c;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%c %d", &c, &pos) == 2) {
                data_structures->my_tree[index]->insert(c, pos);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 删除元素
    QObject::connect(ui->treeDeleteNodePushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->treeIndexSpinBox->value();
        sprintf(buffer, "删除在索引为 %d 的树在 pos 处的节点", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &pos) == 1) {
                data_structures->my_tree[index]->deletenode(pos);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 按编号输出节点
    QObject::connect(ui->treeGetNodePushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->treeIndexSpinBox->value();
        sprintf(buffer, "获取在索引为 %d 的树在 pos 处的节点", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：pos"));
        if (dialog.exec() == QDialog::Accepted) {
            int pos;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &pos) == 1) {
                data_structures->my_tree[index]->get(pos);
                this->update();
            }
        }
        delete[] buffer;
        });
}

void MainWindow::bindUndirectionGraphButton()
{
// 无向图
    // 当前对象的个数
    QObject::connect(ui->undirectionGraphCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->undirectionGraphOptionWidget->setEnabled(false);
        else {
            ui->undirectionGraphOptionWidget->setEnabled(true);
            ui->undirectionGraphIndexSpinBox->setMinimum(0);
            ui->undirectionGraphIndexSpinBox->setMaximum(value - 1);
        }
        });
    // 新建对象
    QObject::connect(ui->undirectionGraphCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(UNDIRECTED_GRAPH, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
        });

    // 销毁对象
    QObject::connect(ui->undirectionGraphDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的无向图吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(UNDIRECTED_GRAPH, index);
            this->update();
        }
        delete[] buffer;
        });


    // 默认展示
    QObject::connect(ui->undirectionGraphDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->undirectionGraphIndexSpinBox->value();
        data_structures->undirection_graph[index]->show_default();
        });
    // 打印图信息
    QObject::connect(ui->undirectionGraphDisplayInfoPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->undirectionGraphIndexSpinBox->value();
        data_structures->undirection_graph[index]->display();
        });

    // Prim
    QObject::connect(ui->undirectionGrapPrimPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->undirectionGraphIndexSpinBox->value();
        data_structures->undirection_graph[index]->prim();
        });

    // Kruskal
    QObject::connect(ui->undirectionGrapKruskalPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->undirectionGraphIndexSpinBox->value();
        data_structures->undirection_graph[index]->kruskal();
        });

    // Floyd
    QObject::connect(ui->undirectionGraphFloydPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->undirectionGraphIndexSpinBox->value();
        data_structures->undirection_graph[index]->floyd();
        });

    // 更改边权
    QObject::connect(ui->undirectionGraphreAssignWeightPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的无向图中更改边 <start, end> 的边权 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式(val为浮点数)：start end val"));
        if (dialog.exec() == QDialog::Accepted) {
            int start, end;
            double val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d %d %lf", &start, &end, &val) == 3) {
                data_structures->undirection_graph[index]->reassign_weight(start, end, val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 增加顶点数
    QObject::connect(ui->undirectionGraphAddVertexPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "将索引为 %d 的无向图的顶点数增加 num", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：num"));
        if (dialog.exec() == QDialog::Accepted) {
            int num;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &num) == 1) {
                data_structures->undirection_graph[index]->add_vertex(num);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 增加边
    QObject::connect(ui->undirectionGraphAddEdgeDeletePushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的无向图中增加边 <start, end>=val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式(val为浮点数)：start end val"));
        if (dialog.exec() == QDialog::Accepted) {
            int start, end;
            double val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d %d %lf", &start, &end, &val) == 3) {
                data_structures->undirection_graph[index]->add_edge(start, end, val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // DFS
    QObject::connect(ui->undirectionGraphDFSPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的无向图中以顶点 x 为起点 DFS", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：x"));
        if (dialog.exec() == QDialog::Accepted) {
            int x;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &x) == 1) {
                data_structures->undirection_graph[index]->DFS(x);
                this->update();
            }
        }
        delete[] buffer;
        });
    // BFS
    QObject::connect(ui->undirectionGraphBFSPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的无向图中以顶点 x 为起点 BFS", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：x"));
        if (dialog.exec() == QDialog::Accepted) {
            int x;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &x) == 1) {
                data_structures->undirection_graph[index]->BFS(x);
                this->update();
            }
        }
        delete[] buffer;
        });

    // Dijkstra
    QObject::connect(ui->undirectionGraphDijkstraPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->undirectionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的无向图中以顶点 x 为起点计算最短路", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：x"));
        if (dialog.exec() == QDialog::Accepted) {
            int x;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &x) == 1) {
                data_structures->undirection_graph[index]->dijkstra(x);
                this->update();
            }
        }
        delete[] buffer;
        });
}

void MainWindow::bindDirectionGraphButton()
{
// 有向图
    // 当前对象的个数
    QObject::connect(ui->directionGraphCountSpinBox, &QSpinBox::valueChanged, this, [this](int value) {
        if (value <= 0) ui->directionGraphOptionWidget->setEnabled(false);
        else {
            ui->directionGraphOptionWidget->setEnabled(true);
            ui->directionGraphIndexSpinBox->setMinimum(0);
            ui->directionGraphIndexSpinBox->setMaximum(value - 1);
        }
        });
    // 新建对象
    QObject::connect(ui->directionGraphCreateObjectPushButton, &QPushButton::clicked, this, [this]() {
        Ui::createObjectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            data_structures->init(DIRECTED_GRAPH, dialog.loadDefaultCheckBox->isChecked());
            this->update();
        }
        });

    // 销毁对象
    QObject::connect(ui->directionGraphDestoryObjectPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "确定要销毁索引为 %d 的有向图吗?", index);
        int ret = customQuestion(buffer);
        if (ret == QMessageBox::Yes) {
            data_structures->del(DIRECTED_GRAPH, index);
            this->update();
        }
        delete[] buffer;
        });


    // 默认展示
    QObject::connect(ui->directionGraphDefaultShowObjectPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->directionGraphIndexSpinBox->value();
        data_structures->direction_graph[index]->show_default();
        });
    // 打印图信息
    QObject::connect(ui->directionGraphDisplayInfoPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->directionGraphIndexSpinBox->value();
        data_structures->direction_graph[index]->display();
        });

    // TopuSort
    QObject::connect(ui->directionGraphTopoSortPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->directionGraphIndexSpinBox->value();
        data_structures->direction_graph[index]->toposort();
        });

    // Floyd
    QObject::connect(ui->directionGraphFloydPushButton, &QPushButton::clicked, this, [this]() {
        int index = ui->directionGraphIndexSpinBox->value();
        data_structures->direction_graph[index]->floyd();
        });

    // 更改边权
    QObject::connect(ui->directionGraphreAssignWeightPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的有向图中更改边 <start, end> 的边权 val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式(val为浮点数)：start end val"));
        if (dialog.exec() == QDialog::Accepted) {
            int start, end;
            double val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d %d %lf", &start, &end, &val) == 3) {
                data_structures->direction_graph[index]->reassign_weight(start, end, val);
                this->update();
            }
        }
        delete[] buffer;
        });
    
    // 增加顶点数
    QObject::connect(ui->directionGraphAddVertexPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "将索引为 %d 的有向图的顶点数增加 num", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：num"));
        if (dialog.exec() == QDialog::Accepted) {
            int num;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &num) == 1) {
                data_structures->direction_graph[index]->add_vertex(num);
                this->update();
            }
        }
        delete[] buffer;
        });

    // 增加边
    QObject::connect(ui->directionGraphAddEdgeDeletePushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的有向图中增加边 <start, end>=val", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式(val为浮点数)：start end val"));
        if (dialog.exec() == QDialog::Accepted) {
            int start, end;
            double val;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d %d %lf", &start, &end, &val) == 3) {
                data_structures->direction_graph[index]->add_edge(start, end, val);
                this->update();
            }
        }
        delete[] buffer;
        });

    // DFS
    QObject::connect(ui->directionGraphDFSPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的有向图中以顶点 x 为起点 DFS", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：x"));
        if (dialog.exec() == QDialog::Accepted) {
            int x;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &x) == 1) {
                data_structures->direction_graph[index]->DFS(x);
                this->update();
            }
        }
        delete[] buffer;
        });
    // BFS
    QObject::connect(ui->directionGraphBFSPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的有向图中以顶点 x 为起点 BFS", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：x"));
        if (dialog.exec() == QDialog::Accepted) {
            int x;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &x) == 1) {
                data_structures->direction_graph[index]->BFS(x);
                this->update();
            }
        }
        delete[] buffer;
        });

    // Dijkstra
    QObject::connect(ui->directionGraphDijkstraPushButton, &QPushButton::clicked, this, [this]() {
        char* buffer = new char[Q_FRINTF_BUFFER_SIZE];

        int index = ui->directionGraphIndexSpinBox->value();
        sprintf(buffer, "在索引为 %d 的有向图中以顶点 x 为起点计算最短路", index);
        Ui::inputDialog dialog;
        dialog.setWindowTitle(buffer);
        dialog.inputLabel->setText(QString::fromUtf8("输入格式：x"));
        if (dialog.exec() == QDialog::Accepted) {
            int x;
            if (sscanf(dialog.inputLineEdit->text().toStdString().c_str(), "%d", &x) == 1) {
                data_structures->direction_graph[index]->dijkstra(x);
                this->update();
            }
        }
        delete[] buffer;
        });
}

/**
 * @brief 清空分区
 * 
 */
void MainWindow::clearPartition()
{
    part->clear();
    data_structures->clearAll();
    this->update();

    _qprintf(part, "分区所有数据清空完毕\n");
}

/**
 * @brief 定位单元所在块
 * 
 */
void MainWindow::locateBlock()
{
    int unit_index = ui->unitFreeInfoIndexSpinBox->value();
    int block_index = part->getBlockIndex(unit_index);
    if (~block_index) {
        ui->blockFreeInfoListWidget->setFocus();
        ui->blockFreeInfoListWidget->setCurrentRow(block_index);
        ui->blockFreeInfoListWidget->scrollToItem(ui->blockFreeInfoListWidget->item(block_index));
    }
}

/**
 * @brief 修改单元总数
 * 
 * @param unit_size 
 */
void MainWindow::changeUnitSum(int unit_size)
{
    int unit_sum = PARTITION_TOTAL_SIZE / unit_size;
    ui->unitSumSpinBox->setValue(unit_sum);
    ui->unitFreeInfoIndexSpinBox->setMaximum(unit_sum);
}

/**
 * @brief 修改单元大小
 * 
 */
void MainWindow::changeUnitSize(int unit_size)
{
    if (unit_size <= 0 || unit_size > PARTITION_TOTAL_SIZE) return;

    _qprintf(part, "\n重设单元大小为 %d 字节\n", unit_size);

    // 修改核心
    part->changeUnitSize(unit_size);
    data_structures->clearAll();

    // 修改 UI
    ui->unitSizeSpinBox->setValue(unit_size);
    this->update();

    _qprintf(part, "重设单元大小完毕\n");
}

/**
 * @brief 自定义消息窗口
 * 
 * @param content 
 * @return int 
 */
int customWarning(QString content)
{
    QMessageBox msg_box(QMessageBox::Warning, QString::fromUtf8("警告"), content, QMessageBox::Yes | QMessageBox::No);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
    msg_box.setWindowIcon(icon);
    return msg_box.exec();
}
int customWarning(const char* content)
{
    return customWarning(QString::fromUtf8(content));
}
int customQuestion(QString content)
{
    QMessageBox msg_box(QMessageBox::Question, QString::fromUtf8("询问"), content, QMessageBox::Yes | QMessageBox::No);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
    msg_box.setWindowIcon(icon);
    return msg_box.exec();
}
int customQuestion(const char* content)
{
    return customQuestion(QString::fromUtf8(content));
}
