/********************************************************************************
** Form generated from reading UI file 'changeUnitSizeDialogcYWCst.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CHANGEUNITSIZEDIALOGCYWCST_H
#define CHANGEUNITSIZEDIALOGCYWCST_H

#include <QtCore/QVariant>
#include <QtWidgets>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

class UiDialog : public QDialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *unitSizeFormLayout;
    QLabel *unitSizeLabel;
    QSpinBox *unitSizeSpinBox;
    QLabel* warningLabel;
    QDialogButtonBox *buttonBox;

    UiDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        if (this->objectName().isEmpty())
            this->setObjectName(QString::fromUtf8("changeUnitSizeDialog"));
        this->resize(366, 74);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        this->setWindowIcon(icon);
        gridLayout = new QGridLayout(this);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        unitSizeFormLayout = new QFormLayout();
        unitSizeFormLayout->setObjectName(QString::fromUtf8("unitSizeFormLayout"));
        unitSizeLabel = new QLabel(this);
        unitSizeLabel->setObjectName(QString::fromUtf8("unitSizeLabel"));

        unitSizeLabel->setText(QString::fromUtf8("\344\277\256\346\224\271\345\215\225\345\205\203\345\244\247\345\260\217\357\274\210\345\255\227\350\212\202\357\274\211\344\270\272\357\274\232"));

        unitSizeFormLayout->setWidget(0, QFormLayout::LabelRole, unitSizeLabel);

        unitSizeSpinBox = new QSpinBox(this);
        unitSizeSpinBox->setObjectName(QString::fromUtf8("unitSizeSpinBox"));
        unitSizeSpinBox->setReadOnly(false);
        unitSizeSpinBox->setMinimum(1);
        unitSizeSpinBox->setMaximum(104857600);

        unitSizeFormLayout->setWidget(0, QFormLayout::FieldRole, unitSizeSpinBox);


        gridLayout->addLayout(unitSizeFormLayout, 0, 0, 1, 1);

        warningLabel = new QLabel(this);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        warningLabel->setText(QString::fromUtf8("\346\263\250: \350\257\245\346\223\215\344\275\234\344\274\232\351\207\215\347\275\256\345\210\206\345\214\272\357\274\214\345\271\266\345\210\240\351\231\244\346\211\200\346\234\211\346\225\260\346\215\256\347\273\223\346\236\204\357\274\214\344\270\215\345\217\257\351\200\206!"));

        gridLayout->addWidget(warningLabel, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(this);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 0, 1, 2, 1);


        this->setWindowTitle(QString::fromUtf8("\344\277\256\346\224\271\345\215\225\345\205\203\345\244\247\345\260\217"));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(this);
    } // setupUi



};

#endif // CHANGEUNITSIZEDIALOGCYWCST_H
