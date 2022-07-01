/********************************************************************************
** Form generated from reading UI file 'aboutvtnPnr.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ABOUTVTNPNR_H
#define ABOUTVTNPNR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About : public QDialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;

    Ui_About(QWidget* parent = nullptr) : QDialog(parent)
    {
        if (this->objectName().isEmpty())
            this->setObjectName(QString::fromUtf8("About"));
        this->resize(532, 347);
        this->setMinimumSize(QSize(532, 347));
        this->setMaximumSize(QSize(532, 347));
        this->setWindowTitle(QString::fromUtf8("\345\205\263\344\272\216"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        this->setWindowIcon(icon);
        groupBox = new QGroupBox(this);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 511, 331));
#if QT_CONFIG(tooltip)
        groupBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QString::fromUtf8(""));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 121, 121));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setText(QString::fromUtf8(""));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icon/icon.ico")));
        label->setScaledContents(true);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 30, 321, 16));
        label_2->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
            "font-size:14px;"));
        label_2->setText(QString::fromUtf8("Data Structure Demo - \346\225\260\346\215\256\347\273\223\346\236\204\347\232\204\346\274\224\347\244\272\347\250\213\345\272\217"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 60, 371, 21));
        label_3->setText(QString::fromUtf8("\345\210\251\347\224\250\350\207\252\345\256\236\347\216\260\347\232\204\345\206\205\345\255\230\345\210\206\351\205\215\344\270\216\345\233\236\346\224\266\346\223\215\344\275\234\357\274\214\345\256\214\346\210\220\347\232\204\344\270\203\347\247\215\346\225\260\346\215\256\347\273\223\346\236\204\347\232\204\346\274\224\347\244\272\347\250\213\345\272\217"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 130, 121, 16));
        label_6->setText(QString::fromUtf8("\350\256\270\345\217\257\357\274\232 MIT License"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(140, 90, 261, 141));
        label_4->setText(QString::fromUtf8("<html><head/><body><p>Logo \350\256\276\350\256\241\357\274\232SpaceSkyNet<br/>UI \350\256\276\350\256\241\344\270\216\347\274\226\345\206\231\357\274\232SpaceSkyNet<br/>\345\206\205\345\255\230\345\210\206\351\205\215\345\233\236\346\224\266\347\256\227\346\263\225\350\256\276\350\256\241\344\270\216\347\274\226\345\206\231\357\274\232SpaceSkyNet<br/>\351\223\276\350\241\250\347\233\270\345\205\263\357\274\232SpaceSkyNet<br/>\346\225\260\347\273\204\347\233\270\345\205\263\357\274\232Louis0612 SpaceSkyNet<br/>\346\240\210\343\200\201\345\240\206\347\233\270\345\205\263\357\274\232cytotropism SpaceSkyNet<br/>\346\240\221\347\233\270\345\205\263\357\274\232Louis0612 SpaceSkyNet<br/>\345\233\276\347\233\270\345\205\263\357\274\232believable<br/>\346\225\260\346\215\256\347\273\223\346\236\204\346\216\245\345\205\245\357\274\232SpaceSkyNet</p></body></html>"));
        label_4->setTextFormat(Qt::AutoText);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 250, 451, 51));
        label_5->setText(QString::fromUtf8("<html><head/><body><p align=\"center\">Copyright (C) 2022 SpaceSkyNet </p><p align=\"center\"><a href=\"https://github.com/spaceskynet/DataStructureDemo\"><span style=\" text-decoration: underline; color:#0000ff;\">https://github.com/spaceskynet/DataStructureDemo</span></a></p></body></html>"));
        label_5->setOpenExternalLinks(true);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(420, 300, 81, 21));
        pushButton->setText(QString::fromUtf8("\347\241\256\345\256\232"));

        retranslateUi(this);

        QMetaObject::connectSlotsByName(this);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        (void)About;
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ABOUTVTNPNR_H
