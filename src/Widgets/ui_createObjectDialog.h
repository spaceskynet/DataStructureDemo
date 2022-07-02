/********************************************************************************
** Form generated from reading UI file 'createObjectDialogFISQlX.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CREATEOBJECTDIALOGFISQLX_H
#define CREATEOBJECTDIALOGFISQLX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_createObjectDialog : public QDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *loadDefaultCheckBox;
    QDialogButtonBox *buttonBox;

    Ui_createObjectDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        if (this->objectName().isEmpty())
            this->setObjectName(QString::fromUtf8("createObjectDialog"));
        this->resize(194, 72);
        this->setWindowTitle(QString::fromUtf8("\346\226\260\345\273\272\345\257\271\350\261\241"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        this->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loadDefaultCheckBox = new QCheckBox(this);
        loadDefaultCheckBox->setObjectName(QString::fromUtf8("loadDefaultCheckBox"));
        loadDefaultCheckBox->setText(QString::fromUtf8("\345\212\240\350\275\275\351\273\230\350\256\244\346\225\260\346\215\256"));
        loadDefaultCheckBox->setCheckable(true);
        loadDefaultCheckBox->setChecked(true);
        loadDefaultCheckBox->setTristate(false);

        horizontalLayout->addWidget(loadDefaultCheckBox);

        buttonBox = new QDialogButtonBox(this);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(this);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(this);
    }

    void retranslateUi(QDialog *createObjectDialog)
    {
        (void)createObjectDialog;
    } // retranslateUi

};

namespace Ui {
    class createObjectDialog: public Ui_createObjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CREATEOBJECTDIALOGFISQLX_H
