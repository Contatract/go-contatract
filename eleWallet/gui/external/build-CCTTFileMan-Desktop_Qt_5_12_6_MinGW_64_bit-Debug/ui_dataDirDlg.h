/********************************************************************************
** Form generated from reading UI file 'dataDirDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADIRDLG_H
#define UI_DATADIRDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *defaultLabel;
    QSpacerItem *horizontalSpacer;
    QLineEdit *dataDirLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *selectDirBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(480, 150);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 0);
        hintLabel = new QLabel(Dialog);
        hintLabel->setObjectName(QString::fromUtf8("hintLabel"));
        hintLabel->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(hintLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        defaultLabel = new QLabel(Dialog);
        defaultLabel->setObjectName(QString::fromUtf8("defaultLabel"));
        defaultLabel->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(defaultLabel);

        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        dataDirLineEdit = new QLineEdit(Dialog);
        dataDirLineEdit->setObjectName(QString::fromUtf8("dataDirLineEdit"));
        dataDirLineEdit->setMinimumSize(QSize(300, 27));
        dataDirLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(dataDirLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        selectDirBtn = new QPushButton(Dialog);
        selectDirBtn->setObjectName(QString::fromUtf8("selectDirBtn"));
        selectDirBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_2->addWidget(selectDirBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        confirmBtn = new QPushButton(Dialog);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_2->addWidget(confirmBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        hintLabel->setText(QApplication::translate("Dialog", "Please set data directory that stores your private data first before\n"
"your first time to use", nullptr));
        defaultLabel->setText(QApplication::translate("Dialog", "Default: ", nullptr));
        selectDirBtn->setText(QApplication::translate("Dialog", "Change", nullptr));
        confirmBtn->setText(QApplication::translate("Dialog", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADIRDLG_H
