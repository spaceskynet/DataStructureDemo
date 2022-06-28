#include "gui.h"
#include <QObject>

MainWindow::MainWindow(QApplication* App, QWidget* parent)
    : QMainWindow(parent)
{
    ui = std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow);
    ui->setupUi(this);
    changeUnitSizeDialog = std::unique_ptr<UiDialog>(new UiDialog);

    data_structures = std::make_unique<Collection>();
    data_structures->part->setMainWindow(ui.get());
    this->part = data_structures->part;

    this->App = App;

    this->setup();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup()
{
    // 单元大小与单元总数，绑定相关信号与槽
    unsigned int unit_size = part->getUnitSize();
    QObject::connect(ui->unitSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeUnitSum(int)));
    QObject::connect(ui->unitSizeSpinBox, SIGNAL(valueChanged(int)), changeUnitSizeDialog->unitSizeSpinBox, SLOT(setValue(int)));

    ui->unitSizeSpinBox->setValue(unit_size);

    QObject::connect(ui->unitSizeLabel, &QClickedLabel::clicked, this, [this]() {
        if (changeUnitSizeDialog->exec() == QDialog::Accepted) {
            changeUnitSize();
        }
    });

    ui->memoryAllocationAlgorithmComboBox->setCurrentIndex(part->getMemoryAllocationAlgorithm());

    QObject::connect(ui->memoryAllocationAlgorithmComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
        part->changeMemoryAllocationAlgorithm((MEMORY_ALLOCATION_ALGORITHM)index);
    });


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

    update();
}

void MainWindow::update()
{
    // 根据分区信息更新分区空闲块界面信息
    part->updateBlockFreeInfoMainWindow();

    ui->linkedListCountSpinBox->setValue(data_structures->linked_list.size());
}

void MainWindow::changeUnitSum(int unit_size)
{
    ui->unitSumSpinBox->setValue(PARTITION_TOTAL_SIZE / unit_size);
}

void MainWindow::changeUnitSize()
{
    unsigned int unit_size = changeUnitSizeDialog->unitSizeSpinBox->value();
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

int customWarning(QString content)
{
    QMessageBox msg_box(QMessageBox::Warning, QString::fromUtf8("警告"), content, QMessageBox::Yes | QMessageBox::No);
    return msg_box.exec();
}
int customWarning(const char* content)
{
    return customWarning(QString::fromUtf8(content));
}
int customQuestion(QString content)
{
    QMessageBox msg_box(QMessageBox::Question, QString::fromUtf8("询问"), content, QMessageBox::Yes | QMessageBox::No);
    return msg_box.exec();
}
int customQuestion(const char* content)
{
    return customQuestion(QString::fromUtf8(content));
}
