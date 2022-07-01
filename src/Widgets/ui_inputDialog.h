/********************************************************************************
** Form generated from reading UI file 'inputDialogNNxOSR.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef INPUTDIALOGNNXOSR_H
#define INPUTDIALOGNNXOSR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_inputDialog : public QDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *inputVerticalLayout;
    QLabel *inputLabel;
    QLineEdit *inputLineEdit;
    QDialogButtonBox *buttonBox;

    Ui_inputDialog(QWidget* parent = nullptr) : QDialog(parent)
    {
        if (this->objectName().isEmpty())
            this->setObjectName(QString::fromUtf8("inputDialog"));
        this->resize(311, 72);
        this->setWindowTitle(QString::fromUtf8("\350\276\223\345\205\245"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        this->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        inputVerticalLayout = new QVBoxLayout();
        inputVerticalLayout->setObjectName(QString::fromUtf8("inputVerticalLayout"));
        inputLabel = new QLabel(this);
        inputLabel->setObjectName(QString::fromUtf8("inputLabel"));
        inputLabel->setText(QString::fromUtf8("\350\276\223\345\205\245\357\274\232"));

        inputVerticalLayout->addWidget(inputLabel);

        inputLineEdit = new QLineEdit(this);
        inputLineEdit->setObjectName(QString::fromUtf8("inputLineEdit"));

        inputVerticalLayout->addWidget(inputLineEdit);


        horizontalLayout->addLayout(inputVerticalLayout);

        buttonBox = new QDialogButtonBox(this);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(this);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(this);
    } // setupUi

    void retranslateUi(QDialog *inputDialog)
    {
        (void)inputDialog;
    } // retranslateUi

};

namespace Ui {
    class inputDialog: public Ui_inputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // INPUTDIALOGNNXOSR_H
