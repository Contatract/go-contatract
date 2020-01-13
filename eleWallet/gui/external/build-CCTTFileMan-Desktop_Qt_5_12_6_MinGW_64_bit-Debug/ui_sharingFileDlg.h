/********************************************************************************
** Form generated from reading UI file 'sharingFileDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARINGFILEDLG_H
#define UI_SHARINGFILEDLG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SharingFileDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *SharingFileTab;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *fileSlectedEdit;
    QLabel *fileSelectedLabel;
    QHBoxLayout *horizontalLayout_24;
    QLabel *shareTStartLabel;
    QDateTimeEdit *startDateTimeEdit;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_25;
    QLabel *shareTStopLabel;
    QDateTimeEdit *stopDateTimeEdit;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_26;
    QLabel *priceLabel;
    QLineEdit *priceLineEdit;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QLabel *addressLabel;
    QLineEdit *shareAddrLineEdit;
    QLabel *opHintLabel;
    QPlainTextEdit *shareLinkTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *shareBtn;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *copyBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *doneBtn;
    QSpacerItem *horizontalSpacer_4;
    QWidget *getSharedFileTab;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *opHintLabel_2;
    QTextEdit *fileSharingCodeTextEdit;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *getSharingInfoBtn;
    QSpacerItem *horizontalSpacer_16;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *fileSharingNameLabel;
    QLineEdit *fileSharingNameLineEdit;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_27;
    QLabel *shareGetTStartLabel_2;
    QLineEdit *getStartDateLineEdit;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_28;
    QLabel *shareGetTStopLabel;
    QLineEdit *getStopDateLineEdit;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_29;
    QLabel *getPriceLabel;
    QLineEdit *priceShowLineEdit;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *ownerLabel;
    QLineEdit *ownerAddrLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *paySharingBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_13;

    void setupUi(QDialog *SharingFileDialog)
    {
        if (SharingFileDialog->objectName().isEmpty())
            SharingFileDialog->setObjectName(QString::fromUtf8("SharingFileDialog"));
        SharingFileDialog->setWindowModality(Qt::NonModal);
        SharingFileDialog->resize(479, 514);
        SharingFileDialog->setMinimumSize(QSize(479, 514));
        SharingFileDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(SharingFileDialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(SharingFileDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        SharingFileTab = new QWidget();
        SharingFileTab->setObjectName(QString::fromUtf8("SharingFileTab"));
        verticalLayout_3 = new QVBoxLayout(SharingFileTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, -1, 6, -1);
        fileSlectedEdit = new QLineEdit(SharingFileTab);
        fileSlectedEdit->setObjectName(QString::fromUtf8("fileSlectedEdit"));
        fileSlectedEdit->setEnabled(false);
        fileSlectedEdit->setMinimumSize(QSize(0, 27));
        fileSlectedEdit->setMaximumSize(QSize(16777215, 27));
        fileSlectedEdit->setReadOnly(true);

        gridLayout->addWidget(fileSlectedEdit, 0, 1, 1, 1);

        fileSelectedLabel = new QLabel(SharingFileTab);
        fileSelectedLabel->setObjectName(QString::fromUtf8("fileSelectedLabel"));
        fileSelectedLabel->setMinimumSize(QSize(130, 25));
        fileSelectedLabel->setMaximumSize(QSize(130, 25));

        gridLayout->addWidget(fileSelectedLabel, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(6, -1, 6, -1);
        shareTStartLabel = new QLabel(SharingFileTab);
        shareTStartLabel->setObjectName(QString::fromUtf8("shareTStartLabel"));
        shareTStartLabel->setMinimumSize(QSize(130, 25));
        shareTStartLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_24->addWidget(shareTStartLabel);

        startDateTimeEdit = new QDateTimeEdit(SharingFileTab);
        startDateTimeEdit->setObjectName(QString::fromUtf8("startDateTimeEdit"));
        startDateTimeEdit->setMinimumSize(QSize(140, 27));
        startDateTimeEdit->setMaximumSize(QSize(140, 27));
        startDateTimeEdit->setDate(QDate(2019, 1, 1));

        horizontalLayout_24->addWidget(startDateTimeEdit);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(6, -1, 6, -1);
        shareTStopLabel = new QLabel(SharingFileTab);
        shareTStopLabel->setObjectName(QString::fromUtf8("shareTStopLabel"));
        shareTStopLabel->setMinimumSize(QSize(130, 25));
        shareTStopLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_25->addWidget(shareTStopLabel);

        stopDateTimeEdit = new QDateTimeEdit(SharingFileTab);
        stopDateTimeEdit->setObjectName(QString::fromUtf8("stopDateTimeEdit"));
        stopDateTimeEdit->setMinimumSize(QSize(140, 27));
        stopDateTimeEdit->setMaximumSize(QSize(140, 27));
        stopDateTimeEdit->setDate(QDate(2019, 1, 1));

        horizontalLayout_25->addWidget(stopDateTimeEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(6, -1, 6, -1);
        priceLabel = new QLabel(SharingFileTab);
        priceLabel->setObjectName(QString::fromUtf8("priceLabel"));
        priceLabel->setMinimumSize(QSize(130, 25));
        priceLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_26->addWidget(priceLabel);

        priceLineEdit = new QLineEdit(SharingFileTab);
        priceLineEdit->setObjectName(QString::fromUtf8("priceLineEdit"));
        priceLineEdit->setEnabled(true);
        priceLineEdit->setMinimumSize(QSize(140, 27));
        priceLineEdit->setMaximumSize(QSize(140, 27));

        horizontalLayout_26->addWidget(priceLineEdit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_26);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, -1, 6, -1);
        addressLabel = new QLabel(SharingFileTab);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));
        addressLabel->setMinimumSize(QSize(130, 25));
        addressLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout->addWidget(addressLabel);

        shareAddrLineEdit = new QLineEdit(SharingFileTab);
        shareAddrLineEdit->setObjectName(QString::fromUtf8("shareAddrLineEdit"));
        shareAddrLineEdit->setMinimumSize(QSize(0, 27));
        shareAddrLineEdit->setMaximumSize(QSize(16777215, 27));

        horizontalLayout->addWidget(shareAddrLineEdit);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);

        opHintLabel = new QLabel(SharingFileTab);
        opHintLabel->setObjectName(QString::fromUtf8("opHintLabel"));
        opHintLabel->setMinimumSize(QSize(0, 30));
        opHintLabel->setWordWrap(true);

        verticalLayout_3->addWidget(opHintLabel);

        shareLinkTextEdit = new QPlainTextEdit(SharingFileTab);
        shareLinkTextEdit->setObjectName(QString::fromUtf8("shareLinkTextEdit"));
        shareLinkTextEdit->setMinimumSize(QSize(0, 80));
        shareLinkTextEdit->setReadOnly(true);

        verticalLayout_3->addWidget(shareLinkTextEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        shareBtn = new QPushButton(SharingFileTab);
        shareBtn->setObjectName(QString::fromUtf8("shareBtn"));
        shareBtn->setMinimumSize(QSize(100, 25));
        shareBtn->setMaximumSize(QSize(120, 25));

        horizontalLayout_2->addWidget(shareBtn);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        copyBtn = new QPushButton(SharingFileTab);
        copyBtn->setObjectName(QString::fromUtf8("copyBtn"));
        copyBtn->setEnabled(false);
        copyBtn->setMinimumSize(QSize(100, 25));
        copyBtn->setMaximumSize(QSize(120, 25));

        horizontalLayout_2->addWidget(copyBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        doneBtn = new QPushButton(SharingFileTab);
        doneBtn->setObjectName(QString::fromUtf8("doneBtn"));
        doneBtn->setMinimumSize(QSize(100, 25));
        doneBtn->setMaximumSize(QSize(120, 25));

        horizontalLayout_2->addWidget(doneBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(SharingFileTab, QString());
        getSharedFileTab = new QWidget();
        getSharedFileTab->setObjectName(QString::fromUtf8("getSharedFileTab"));
        verticalLayout_6 = new QVBoxLayout(getSharedFileTab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        opHintLabel_2 = new QLabel(getSharedFileTab);
        opHintLabel_2->setObjectName(QString::fromUtf8("opHintLabel_2"));
        opHintLabel_2->setMinimumSize(QSize(0, 30));
        opHintLabel_2->setWordWrap(true);

        verticalLayout_5->addWidget(opHintLabel_2);

        fileSharingCodeTextEdit = new QTextEdit(getSharedFileTab);
        fileSharingCodeTextEdit->setObjectName(QString::fromUtf8("fileSharingCodeTextEdit"));
        fileSharingCodeTextEdit->setMinimumSize(QSize(0, 80));

        verticalLayout_5->addWidget(fileSharingCodeTextEdit);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_15);

        getSharingInfoBtn = new QPushButton(getSharedFileTab);
        getSharingInfoBtn->setObjectName(QString::fromUtf8("getSharingInfoBtn"));
        getSharingInfoBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_6->addWidget(getSharingInfoBtn);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_16);


        verticalLayout_5->addLayout(horizontalLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(6, 0, 6, 0);
        fileSharingNameLabel = new QLabel(getSharedFileTab);
        fileSharingNameLabel->setObjectName(QString::fromUtf8("fileSharingNameLabel"));
        fileSharingNameLabel->setMinimumSize(QSize(130, 25));
        fileSharingNameLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_5->addWidget(fileSharingNameLabel);

        fileSharingNameLineEdit = new QLineEdit(getSharedFileTab);
        fileSharingNameLineEdit->setObjectName(QString::fromUtf8("fileSharingNameLineEdit"));
        fileSharingNameLineEdit->setEnabled(false);
        fileSharingNameLineEdit->setMinimumSize(QSize(0, 27));
        fileSharingNameLineEdit->setMaximumSize(QSize(16777215, 27));

        horizontalLayout_5->addWidget(fileSharingNameLineEdit);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_14);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(6, -1, 6, -1);
        shareGetTStartLabel_2 = new QLabel(getSharedFileTab);
        shareGetTStartLabel_2->setObjectName(QString::fromUtf8("shareGetTStartLabel_2"));
        shareGetTStartLabel_2->setMinimumSize(QSize(130, 25));
        shareGetTStartLabel_2->setMaximumSize(QSize(130, 25));

        horizontalLayout_27->addWidget(shareGetTStartLabel_2);

        getStartDateLineEdit = new QLineEdit(getSharedFileTab);
        getStartDateLineEdit->setObjectName(QString::fromUtf8("getStartDateLineEdit"));
        getStartDateLineEdit->setEnabled(false);
        getStartDateLineEdit->setMinimumSize(QSize(140, 27));
        getStartDateLineEdit->setMaximumSize(QSize(140, 27));
        getStartDateLineEdit->setReadOnly(true);

        horizontalLayout_27->addWidget(getStartDateLineEdit);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_9);


        verticalLayout_4->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(6, -1, 6, -1);
        shareGetTStopLabel = new QLabel(getSharedFileTab);
        shareGetTStopLabel->setObjectName(QString::fromUtf8("shareGetTStopLabel"));
        shareGetTStopLabel->setMinimumSize(QSize(130, 25));
        shareGetTStopLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_28->addWidget(shareGetTStopLabel);

        getStopDateLineEdit = new QLineEdit(getSharedFileTab);
        getStopDateLineEdit->setObjectName(QString::fromUtf8("getStopDateLineEdit"));
        getStopDateLineEdit->setEnabled(false);
        getStopDateLineEdit->setMinimumSize(QSize(140, 27));
        getStopDateLineEdit->setMaximumSize(QSize(140, 27));
        getStopDateLineEdit->setReadOnly(true);

        horizontalLayout_28->addWidget(getStopDateLineEdit);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_10);


        verticalLayout_4->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(6, -1, 6, -1);
        getPriceLabel = new QLabel(getSharedFileTab);
        getPriceLabel->setObjectName(QString::fromUtf8("getPriceLabel"));
        getPriceLabel->setMinimumSize(QSize(130, 25));
        getPriceLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_29->addWidget(getPriceLabel);

        priceShowLineEdit = new QLineEdit(getSharedFileTab);
        priceShowLineEdit->setObjectName(QString::fromUtf8("priceShowLineEdit"));
        priceShowLineEdit->setEnabled(false);
        priceShowLineEdit->setMinimumSize(QSize(140, 27));
        priceShowLineEdit->setMaximumSize(QSize(140, 27));
        priceShowLineEdit->setReadOnly(true);

        horizontalLayout_29->addWidget(priceShowLineEdit);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_11);


        verticalLayout_4->addLayout(horizontalLayout_29);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(6, -1, 6, -1);
        ownerLabel = new QLabel(getSharedFileTab);
        ownerLabel->setObjectName(QString::fromUtf8("ownerLabel"));
        ownerLabel->setMinimumSize(QSize(130, 25));
        ownerLabel->setMaximumSize(QSize(130, 25));

        horizontalLayout_4->addWidget(ownerLabel);

        ownerAddrLineEdit = new QLineEdit(getSharedFileTab);
        ownerAddrLineEdit->setObjectName(QString::fromUtf8("ownerAddrLineEdit"));
        ownerAddrLineEdit->setEnabled(false);
        ownerAddrLineEdit->setMinimumSize(QSize(0, 27));
        ownerAddrLineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(ownerAddrLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);

        paySharingBtn = new QPushButton(getSharedFileTab);
        paySharingBtn->setObjectName(QString::fromUtf8("paySharingBtn"));
        paySharingBtn->setEnabled(false);
        paySharingBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_3->addWidget(paySharingBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        cancelBtn = new QPushButton(getSharedFileTab);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);


        verticalLayout_6->addLayout(horizontalLayout_3);

        tabWidget->addTab(getSharedFileTab, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(SharingFileDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SharingFileDialog);
    } // setupUi

    void retranslateUi(QDialog *SharingFileDialog)
    {
        SharingFileDialog->setWindowTitle(QApplication::translate("SharingFileDialog", "File sharing", nullptr));
        fileSelectedLabel->setText(QApplication::translate("SharingFileDialog", "The file selected:", nullptr));
        shareTStartLabel->setText(QApplication::translate("SharingFileDialog", "Time to start share: ", nullptr));
        shareTStopLabel->setText(QApplication::translate("SharingFileDialog", "Time to end share:  ", nullptr));
        priceLabel->setText(QApplication::translate("SharingFileDialog", "Price to share:", nullptr));
        priceLineEdit->setPlaceholderText(QString());
        addressLabel->setText(QApplication::translate("SharingFileDialog", "Whom to share with:", nullptr));
        opHintLabel->setText(QApplication::translate("SharingFileDialog", "Click \"Share\" button and copy the content below then send it to the person who you want to share this file with:", nullptr));
        shareBtn->setText(QApplication::translate("SharingFileDialog", "Share", nullptr));
        copyBtn->setText(QApplication::translate("SharingFileDialog", "Copy", nullptr));
        doneBtn->setText(QApplication::translate("SharingFileDialog", "Done", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SharingFileTab), QApplication::translate("SharingFileDialog", "Share a file", nullptr));
        opHintLabel_2->setText(QApplication::translate("SharingFileDialog", "Get the file sharing content text and copy to the text box below, then click \"Get Sharing Info\" to get the infomation about this sharing, and then click \"Pay for it\" button to create a transaction and wait it to be done:", nullptr));
        getSharingInfoBtn->setText(QApplication::translate("SharingFileDialog", "Get Sharing Info", nullptr));
        fileSharingNameLabel->setText(QApplication::translate("SharingFileDialog", "file name:", nullptr));
        shareGetTStartLabel_2->setText(QApplication::translate("SharingFileDialog", "Time to start share: ", nullptr));
        shareGetTStopLabel->setText(QApplication::translate("SharingFileDialog", "Time to end share:  ", nullptr));
        getPriceLabel->setText(QApplication::translate("SharingFileDialog", "Price to share:", nullptr));
        priceShowLineEdit->setPlaceholderText(QApplication::translate("SharingFileDialog", "\302\245", nullptr));
        ownerLabel->setText(QApplication::translate("SharingFileDialog", "Who give the sharing:", nullptr));
        paySharingBtn->setText(QApplication::translate("SharingFileDialog", "Pay for it", nullptr));
        cancelBtn->setText(QApplication::translate("SharingFileDialog", "Cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(getSharedFileTab), QApplication::translate("SharingFileDialog", "Get a shared file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SharingFileDialog: public Ui_SharingFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARINGFILEDLG_H
