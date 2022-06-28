/********************************************************************************
** Form generated from reading UI file 'MainWindowqBDZNe.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWQBDZNE_H
#define MAINWINDOWQBDZNE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "newWidgets.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QClickedLabel *logoLabel;
    QWidget *leftWidget;
    QWidget *rightWidget;
    QHBoxLayout *mainHorizontalLayout;
    QVBoxLayout *partitionInfoVerticalLayout;
    QGroupBox *basicInfoGroupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *unitSizeFormLayout;
    QClickedLabel *unitSizeLabel;
    QSpinBox *unitSizeSpinBox;
    QFormLayout *unitSumFormLayout;
    QLabel *unitSumLabel;
    QSpinBox *unitSumSpinBox;
    QFormLayout *freeUnitSumFormLayout;
    QLabel *freeUnitSumLabel;
    QSpinBox *freeUnitSumSpinBox;
    QFormLayout *memoryAllocationAlgorithmFormLayout;
    QLabel *memoryAllocationAlgorithmLabel;
    QComboBox *memoryAllocationAlgorithmComboBox;
    QGroupBox *blockFreeInfoGroupBox;
    QVBoxLayout *verticalLayout_4;
    QListWidget *blockFreeInfoListWidget;
    QVBoxLayout *operateVerticalLayout;
    QGroupBox *dataStructureOperateGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *dataStructureOperateTabWidget;
    QWidget *linkedListPage;
    QFormLayout *formLayout_2;
    QWidget *linkedListInfoWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *linkedListInfoGridLayout;
    QFormLayout *linkedListCountFormLayout;
    QLabel *linkedListCountLabel;
    QSpinBox *linkedListCountSpinBox;
    QPushButton *linkedListCreateObjectPushButton;
    QWidget *linkedListOptionWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *linkedListOptionGridLayout;
    QPushButton *linkedListDefaultShowObjectPushButton;
    QPushButton *linkedListLocateElemPushButton;
    QPushButton *linkedListLengthPushButton;
    QPushButton *linkedListDestoryObjectPushButton;
    QPushButton *linkedListGetElemPushButton;
    QPushButton *linkedListPrintAllElemPushButton;
    QPushButton *linkedListDeletePushButton;
    QPushButton *linkedListClearListPushButton;
    QFormLayout *linkedListIndexFormLayout;
    QLabel *linkedListIndexLabel;
    QSpinBox *linkedListIndexSpinBox;
    QPushButton *linkedListInsertPushButton;
    QWidget *arrayPage;
    QGroupBox *outputInfoGroupBox;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *outputInfoTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setWindowTitle(QString::fromUtf8("Data Structure Demo"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        logoLabel = new QClickedLabel(centralwidget);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setText(QString::fromUtf8("<html><head><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; }\n"
"hr { height: 1px; border-width: 0; }\n"
"span {font-family:'monospace'; font-size:10pt; color:#000000;}\n"
"</style></head><body>\n"
"<p><span>    ____        __           _____ __                  __                     ____                     </span></p>\n"
"<p><span>   / __ \\____ _/ /_____ _   / ___// /________  _______/ /___  __________     / __ \\___  ____ ___  ____ </span></p>\n"
"<p><span>  / / / / __ `/ __/ __ `/   \\__ \\/ __/ ___/ / / / ___/ __/ / / / ___/ _ \\   / / / / _ \\/ __ `__ \\/ __ \\</span></p>\n"
"<p><span> / /_/ / /_/ / /_/ /_/ /   ___/ / /_/ /  / /_/ / /__/ /_/ /_/ / /  /  __/  / /_/ /  __/ / / / / / /_/ /</span></p>\n"
"<p><span>/_____/\\__,_/\\__/\\__,_/   /____/\\__/_/   \\__,_/\\___/\\__/\\__,_/_/   \\___/  /_____/\\___/_/ /_/ /_/\\____/ </span></p></body></html>"));
        logoLabel->setMargin(5);

        gridLayout->addWidget(logoLabel, 0, 1, 1, 1);

        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName(QString::fromUtf8("leftWidget"));

        gridLayout->addWidget(leftWidget, 0, 0, 1, 1);

        rightWidget = new QWidget(centralwidget);
        rightWidget->setObjectName(QString::fromUtf8("rightWidget"));

        gridLayout->addWidget(rightWidget, 0, 2, 1, 1);

        mainHorizontalLayout = new QHBoxLayout();
        mainHorizontalLayout->setObjectName(QString::fromUtf8("mainHorizontalLayout"));
        partitionInfoVerticalLayout = new QVBoxLayout();
        partitionInfoVerticalLayout->setObjectName(QString::fromUtf8("partitionInfoVerticalLayout"));
        basicInfoGroupBox = new QGroupBox(centralwidget);
        basicInfoGroupBox->setObjectName(QString::fromUtf8("basicInfoGroupBox"));
        basicInfoGroupBox->setTitle(QString::fromUtf8("\345\210\206\345\214\272\345\237\272\346\234\254\344\277\241\346\201\257"));
        verticalLayout = new QVBoxLayout(basicInfoGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        unitSizeFormLayout = new QFormLayout();
        unitSizeFormLayout->setObjectName(QString::fromUtf8("unitSizeFormLayout"));
        unitSizeLabel = new QClickedLabel(basicInfoGroupBox);
        unitSizeLabel->setObjectName(QString::fromUtf8("unitSizeLabel"));
#if QT_CONFIG(tooltip)
        unitSizeLabel->setToolTip(QString::fromUtf8("unit size"));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        unitSizeLabel->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
        unitSizeLabel->setText(QString::fromUtf8("\345\215\225\345\205\203\345\244\247\345\260\217\357\274\210\345\255\227\350\212\202\357\274\211\357\274\232"));

        unitSizeFormLayout->setWidget(0, QFormLayout::LabelRole, unitSizeLabel);

        unitSizeSpinBox = new QSpinBox(basicInfoGroupBox);
        unitSizeSpinBox->setObjectName(QString::fromUtf8("unitSizeSpinBox"));
        unitSizeSpinBox->setReadOnly(true);
        unitSizeSpinBox->setMinimum(1);
        unitSizeSpinBox->setMaximum(104857600);

        unitSizeFormLayout->setWidget(0, QFormLayout::FieldRole, unitSizeSpinBox);


        verticalLayout->addLayout(unitSizeFormLayout);

        unitSumFormLayout = new QFormLayout();
        unitSumFormLayout->setObjectName(QString::fromUtf8("unitSumFormLayout"));
        unitSumLabel = new QLabel(basicInfoGroupBox);
        unitSumLabel->setObjectName(QString::fromUtf8("unitSumLabel"));
        unitSumLabel->setText(QString::fromUtf8("\345\215\225\345\205\203\346\200\273\346\225\260\357\274\232"));

        unitSumFormLayout->setWidget(0, QFormLayout::LabelRole, unitSumLabel);

        unitSumSpinBox = new QSpinBox(basicInfoGroupBox);
        unitSumSpinBox->setObjectName(QString::fromUtf8("unitSumSpinBox"));
        unitSumSpinBox->setReadOnly(true);
        unitSumSpinBox->setMinimum(1);
        unitSumSpinBox->setMaximum(104857600);

        unitSumFormLayout->setWidget(0, QFormLayout::FieldRole, unitSumSpinBox);


        verticalLayout->addLayout(unitSumFormLayout);

        freeUnitSumFormLayout = new QFormLayout();
        freeUnitSumFormLayout->setObjectName(QString::fromUtf8("freeUnitSumFormLayout"));
        freeUnitSumLabel = new QLabel(basicInfoGroupBox);
        freeUnitSumLabel->setObjectName(QString::fromUtf8("freeUnitSumLabel"));
        freeUnitSumLabel->setText(QString::fromUtf8("\347\251\272\351\227\262\345\215\225\344\275\215\346\200\273\346\225\260\357\274\232"));

        freeUnitSumFormLayout->setWidget(0, QFormLayout::LabelRole, freeUnitSumLabel);

        freeUnitSumSpinBox = new QSpinBox(basicInfoGroupBox);
        freeUnitSumSpinBox->setObjectName(QString::fromUtf8("freeUnitSumSpinBox"));
        freeUnitSumSpinBox->setMaximum(104857600);

        freeUnitSumFormLayout->setWidget(0, QFormLayout::FieldRole, freeUnitSumSpinBox);


        verticalLayout->addLayout(freeUnitSumFormLayout);

        memoryAllocationAlgorithmFormLayout = new QFormLayout();
        memoryAllocationAlgorithmFormLayout->setObjectName(QString::fromUtf8("memoryAllocationAlgorithmFormLayout"));
        memoryAllocationAlgorithmLabel = new QLabel(basicInfoGroupBox);
        memoryAllocationAlgorithmLabel->setObjectName(QString::fromUtf8("memoryAllocationAlgorithmLabel"));

        memoryAllocationAlgorithmFormLayout->setWidget(0, QFormLayout::LabelRole, memoryAllocationAlgorithmLabel);

        memoryAllocationAlgorithmComboBox = new QComboBox(basicInfoGroupBox);
        memoryAllocationAlgorithmComboBox->addItem(QString());
        memoryAllocationAlgorithmComboBox->addItem(QString());
        memoryAllocationAlgorithmComboBox->addItem(QString());
        memoryAllocationAlgorithmComboBox->setObjectName(QString::fromUtf8("memoryAllocationAlgorithmComboBox"));

        memoryAllocationAlgorithmFormLayout->setWidget(0, QFormLayout::FieldRole, memoryAllocationAlgorithmComboBox);


        verticalLayout->addLayout(memoryAllocationAlgorithmFormLayout);


        partitionInfoVerticalLayout->addWidget(basicInfoGroupBox);

        blockFreeInfoGroupBox = new QGroupBox(centralwidget);
        blockFreeInfoGroupBox->setObjectName(QString::fromUtf8("blockFreeInfoGroupBox"));
        blockFreeInfoGroupBox->setTitle(QString::fromUtf8("\345\210\206\345\214\272\347\251\272\351\227\262\346\203\205\345\206\265"));
        verticalLayout_4 = new QVBoxLayout(blockFreeInfoGroupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        blockFreeInfoListWidget = new QListWidget(blockFreeInfoGroupBox);
        blockFreeInfoListWidget->setObjectName(QString::fromUtf8("blockFreeInfoListWidget"));

        verticalLayout_4->addWidget(blockFreeInfoListWidget);


        partitionInfoVerticalLayout->addWidget(blockFreeInfoGroupBox);


        mainHorizontalLayout->addLayout(partitionInfoVerticalLayout);

        operateVerticalLayout = new QVBoxLayout();
        operateVerticalLayout->setObjectName(QString::fromUtf8("operateVerticalLayout"));
        dataStructureOperateGroupBox = new QGroupBox(centralwidget);
        dataStructureOperateGroupBox->setObjectName(QString::fromUtf8("dataStructureOperateGroupBox"));
        dataStructureOperateGroupBox->setTitle(QString::fromUtf8("\346\225\260\346\215\256\347\273\223\346\236\204\346\223\215\344\275\234\345\214\272"));
        verticalLayout_2 = new QVBoxLayout(dataStructureOperateGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dataStructureOperateTabWidget = new QTabWidget(dataStructureOperateGroupBox);
        dataStructureOperateTabWidget->setObjectName(QString::fromUtf8("dataStructureOperateTabWidget"));
        linkedListPage = new QWidget();
        linkedListPage->setObjectName(QString::fromUtf8("linkedListPage"));
        formLayout_2 = new QFormLayout(linkedListPage);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        linkedListInfoWidget = new QWidget(linkedListPage);
        linkedListInfoWidget->setObjectName(QString::fromUtf8("linkedListInfoWidget"));
        gridLayout_3 = new QGridLayout(linkedListInfoWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        linkedListInfoGridLayout = new QGridLayout();
        linkedListInfoGridLayout->setObjectName(QString::fromUtf8("linkedListInfoGridLayout"));
        linkedListCountFormLayout = new QFormLayout();
        linkedListCountFormLayout->setObjectName(QString::fromUtf8("linkedListCountFormLayout"));
        linkedListCountLabel = new QLabel(linkedListInfoWidget);
        linkedListCountLabel->setObjectName(QString::fromUtf8("linkedListCountLabel"));
        linkedListCountLabel->setText(QString::fromUtf8("\345\275\223\345\211\215\345\257\271\350\261\241\347\232\204\344\270\252\346\225\260\357\274\232"));

        linkedListCountFormLayout->setWidget(0, QFormLayout::LabelRole, linkedListCountLabel);

        linkedListCountSpinBox = new QSpinBox(linkedListInfoWidget);
        linkedListCountSpinBox->setObjectName(QString::fromUtf8("linkedListCountSpinBox"));
        linkedListCountSpinBox->setReadOnly(true);
        linkedListCountSpinBox->setPrefix(QString::fromUtf8(""));
        linkedListCountSpinBox->setMinimum(-1);
        linkedListCountSpinBox->setValue(-1);

        linkedListCountFormLayout->setWidget(0, QFormLayout::FieldRole, linkedListCountSpinBox);


        linkedListInfoGridLayout->addLayout(linkedListCountFormLayout, 0, 0, 1, 1);

        linkedListCreateObjectPushButton = new QPushButton(linkedListInfoWidget);
        linkedListCreateObjectPushButton->setObjectName(QString::fromUtf8("linkedListCreateObjectPushButton"));
        linkedListCreateObjectPushButton->setText(QString::fromUtf8("\346\226\260\345\273\272\345\257\271\350\261\241"));

        linkedListInfoGridLayout->addWidget(linkedListCreateObjectPushButton, 0, 1, 1, 1);


        gridLayout_3->addLayout(linkedListInfoGridLayout, 0, 0, 1, 1);


        formLayout_2->setWidget(0, QFormLayout::LabelRole, linkedListInfoWidget);

        linkedListOptionWidget = new QWidget(linkedListPage);
        linkedListOptionWidget->setObjectName(QString::fromUtf8("linkedListOptionWidget"));
        linkedListOptionWidget->setEnabled(true);
        gridLayout_2 = new QGridLayout(linkedListOptionWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        linkedListOptionGridLayout = new QGridLayout();
        linkedListOptionGridLayout->setObjectName(QString::fromUtf8("linkedListOptionGridLayout"));
        linkedListDefaultShowObjectPushButton = new QPushButton(linkedListOptionWidget);
        linkedListDefaultShowObjectPushButton->setObjectName(QString::fromUtf8("linkedListDefaultShowObjectPushButton"));
        linkedListDefaultShowObjectPushButton->setEnabled(true);
        linkedListDefaultShowObjectPushButton->setText(QString::fromUtf8("\351\273\230\350\256\244\345\261\225\347\244\272"));

        linkedListOptionGridLayout->addWidget(linkedListDefaultShowObjectPushButton, 0, 5, 1, 1);

        linkedListLocateElemPushButton = new QPushButton(linkedListOptionWidget);
        linkedListLocateElemPushButton->setObjectName(QString::fromUtf8("linkedListLocateElemPushButton"));
        linkedListLocateElemPushButton->setText(QString::fromUtf8("\346\214\211\345\200\274\345\257\273\346\211\276\345\205\203\347\264\240"));

        linkedListOptionGridLayout->addWidget(linkedListLocateElemPushButton, 2, 2, 1, 2);

        linkedListLengthPushButton = new QPushButton(linkedListOptionWidget);
        linkedListLengthPushButton->setObjectName(QString::fromUtf8("linkedListLengthPushButton"));
        linkedListLengthPushButton->setText(QString::fromUtf8("\351\223\276\350\241\250\351\225\277\345\272\246"));

        linkedListOptionGridLayout->addWidget(linkedListLengthPushButton, 1, 1, 1, 2);

        linkedListDestoryObjectPushButton = new QPushButton(linkedListOptionWidget);
        linkedListDestoryObjectPushButton->setObjectName(QString::fromUtf8("linkedListDestoryObjectPushButton"));
        linkedListDestoryObjectPushButton->setText(QString::fromUtf8("\351\224\200\346\257\201\345\257\271\350\261\241"));

        linkedListOptionGridLayout->addWidget(linkedListDestoryObjectPushButton, 0, 3, 1, 2);

        linkedListGetElemPushButton = new QPushButton(linkedListOptionWidget);
        linkedListGetElemPushButton->setObjectName(QString::fromUtf8("linkedListGetElemPushButton"));
        linkedListGetElemPushButton->setText(QString::fromUtf8("\346\214\211\344\275\215\345\272\217\350\216\267\345\217\226\345\205\203\347\264\240"));

        linkedListOptionGridLayout->addWidget(linkedListGetElemPushButton, 2, 0, 1, 2);

        linkedListPrintAllElemPushButton = new QPushButton(linkedListOptionWidget);
        linkedListPrintAllElemPushButton->setObjectName(QString::fromUtf8("linkedListPrintAllElemPushButton"));
        linkedListPrintAllElemPushButton->setText(QString::fromUtf8("\346\211\223\345\215\260\346\211\200\346\234\211\345\205\203\347\264\240"));

        linkedListOptionGridLayout->addWidget(linkedListPrintAllElemPushButton, 2, 4, 1, 2);

        linkedListDeletePushButton = new QPushButton(linkedListOptionWidget);
        linkedListDeletePushButton->setObjectName(QString::fromUtf8("linkedListDeletePushButton"));
        linkedListDeletePushButton->setText(QString::fromUtf8("\345\210\240\351\231\244\345\205\203\347\264\240"));

        linkedListOptionGridLayout->addWidget(linkedListDeletePushButton, 1, 5, 1, 1);

        linkedListClearListPushButton = new QPushButton(linkedListOptionWidget);
        linkedListClearListPushButton->setObjectName(QString::fromUtf8("linkedListClearListPushButton"));
        linkedListClearListPushButton->setText(QString::fromUtf8("\346\270\205\347\251\272\351\223\276\350\241\250"));

        linkedListOptionGridLayout->addWidget(linkedListClearListPushButton, 1, 0, 1, 1);

        linkedListIndexFormLayout = new QFormLayout();
        linkedListIndexFormLayout->setObjectName(QString::fromUtf8("linkedListIndexFormLayout"));
        linkedListIndexLabel = new QLabel(linkedListOptionWidget);
        linkedListIndexLabel->setObjectName(QString::fromUtf8("linkedListIndexLabel"));
        linkedListIndexLabel->setText(QString::fromUtf8("\345\260\206\350\246\201\346\223\215\344\275\234\345\257\271\350\261\241\347\232\204\347\264\242\345\274\225\357\274\232"));

        linkedListIndexFormLayout->setWidget(0, QFormLayout::LabelRole, linkedListIndexLabel);

        linkedListIndexSpinBox = new QSpinBox(linkedListOptionWidget);
        linkedListIndexSpinBox->setObjectName(QString::fromUtf8("linkedListIndexSpinBox"));

        linkedListIndexFormLayout->setWidget(0, QFormLayout::FieldRole, linkedListIndexSpinBox);


        linkedListOptionGridLayout->addLayout(linkedListIndexFormLayout, 0, 0, 1, 3);

        linkedListInsertPushButton = new QPushButton(linkedListOptionWidget);
        linkedListInsertPushButton->setObjectName(QString::fromUtf8("linkedListInsertPushButton"));
        linkedListInsertPushButton->setText(QString::fromUtf8("\346\217\222\345\205\245\345\205\203\347\264\240"));

        linkedListOptionGridLayout->addWidget(linkedListInsertPushButton, 1, 3, 1, 2);


        gridLayout_2->addLayout(linkedListOptionGridLayout, 0, 0, 1, 1);


        formLayout_2->setWidget(1, QFormLayout::LabelRole, linkedListOptionWidget);

        dataStructureOperateTabWidget->addTab(linkedListPage, QString());
        dataStructureOperateTabWidget->setTabText(dataStructureOperateTabWidget->indexOf(linkedListPage), QString::fromUtf8("\351\223\276\350\241\250"));
        arrayPage = new QWidget();
        arrayPage->setObjectName(QString::fromUtf8("arrayPage"));
        dataStructureOperateTabWidget->addTab(arrayPage, QString());
        dataStructureOperateTabWidget->setTabText(dataStructureOperateTabWidget->indexOf(arrayPage), QString::fromUtf8("\346\225\260\347\273\204"));

        verticalLayout_2->addWidget(dataStructureOperateTabWidget);


        operateVerticalLayout->addWidget(dataStructureOperateGroupBox);

        outputInfoGroupBox = new QGroupBox(centralwidget);
        outputInfoGroupBox->setObjectName(QString::fromUtf8("outputInfoGroupBox"));
        outputInfoGroupBox->setTitle(QString::fromUtf8("\350\276\223\345\207\272\344\277\241\346\201\257"));
        verticalLayout_3 = new QVBoxLayout(outputInfoGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        outputInfoTextEdit = new QTextEdit(outputInfoGroupBox);
        outputInfoTextEdit->setObjectName(QString::fromUtf8("outputInfoTextEdit"));
        outputInfoTextEdit->setReadOnly(true);

        verticalLayout_3->addWidget(outputInfoTextEdit);


        operateVerticalLayout->addWidget(outputInfoGroupBox);


        mainHorizontalLayout->addLayout(operateVerticalLayout);

        mainHorizontalLayout->setStretch(0, 1);
        mainHorizontalLayout->setStretch(1, 3);

        gridLayout->addLayout(mainHorizontalLayout, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(unitSizeSpinBox, unitSumSpinBox);
        QWidget::setTabOrder(unitSumSpinBox, freeUnitSumSpinBox);
        QWidget::setTabOrder(freeUnitSumSpinBox, blockFreeInfoListWidget);
        QWidget::setTabOrder(blockFreeInfoListWidget, outputInfoTextEdit);
        QWidget::setTabOrder(outputInfoTextEdit, linkedListCountSpinBox);
        QWidget::setTabOrder(linkedListCountSpinBox, linkedListIndexSpinBox);
        QWidget::setTabOrder(linkedListIndexSpinBox, linkedListCreateObjectPushButton);
        QWidget::setTabOrder(linkedListCreateObjectPushButton, linkedListDestoryObjectPushButton);
        QWidget::setTabOrder(linkedListDestoryObjectPushButton, linkedListDefaultShowObjectPushButton);

        retranslateUi(MainWindow);

        dataStructureOperateTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        memoryAllocationAlgorithmLabel->setText(QCoreApplication::translate("MainWindow", "\345\206\205\345\255\230\345\210\206\351\205\215\347\256\227\346\263\225\357\274\232", nullptr));
        memoryAllocationAlgorithmComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\351\246\226\346\254\241\351\200\202\345\272\224\347\256\227\346\263\225", nullptr));
        memoryAllocationAlgorithmComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\346\234\200\344\275\263\351\200\202\345\272\224\347\256\227\346\263\225", nullptr));
        memoryAllocationAlgorithmComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\346\234\200\345\267\256\351\200\202\345\272\224\347\256\227\346\263\225", nullptr));

        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWQBDZNE_H
