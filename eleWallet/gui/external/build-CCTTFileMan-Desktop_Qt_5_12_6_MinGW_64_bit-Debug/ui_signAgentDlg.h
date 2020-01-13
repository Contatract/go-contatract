/********************************************************************************
** Form generated from reading UI file 'signAgentDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNAGENTDLG_H
#define UI_SIGNAGENTDLG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SignAgentDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout_23;
    QSpacerItem *horizontalSpacer_37;
    QLabel *AgMethodLabel;
    QRadioButton *timeRadioBtn;
    QRadioButton *flowRadioBtn;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_24;
    QSpacerItem *horizontalSpacer_25;
    QLabel *AgTStartLabel;
    QDateTimeEdit *startDateTimeEdit;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_25;
    QSpacerItem *horizontalSpacer_35;
    QLabel *AgTStopLabel;
    QDateTimeEdit *stopDateTimeEdit;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_26;
    QSpacerItem *horizontalSpacer_36;
    QLabel *AgFlowLabel;
    QLineEdit *flowLineEdit;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *SignAgentDialog)
    {
        if (SignAgentDialog->objectName().isEmpty())
            SignAgentDialog->setObjectName(QString::fromUtf8("SignAgentDialog"));
        SignAgentDialog->setWindowModality(Qt::NonModal);
        SignAgentDialog->resize(394, 239);
        SignAgentDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(SignAgentDialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hintLabel = new QLabel(SignAgentDialog);
        hintLabel->setObjectName(QString::fromUtf8("hintLabel"));
        hintLabel->setMinimumSize(QSize(0, 30));
        hintLabel->setMaximumSize(QSize(16777215, 30));
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(6, -1, 6, -1);
        horizontalSpacer_37 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_37);

        AgMethodLabel = new QLabel(SignAgentDialog);
        AgMethodLabel->setObjectName(QString::fromUtf8("AgMethodLabel"));
        AgMethodLabel->setMinimumSize(QSize(116, 25));
        AgMethodLabel->setMaximumSize(QSize(116, 25));

        horizontalLayout_23->addWidget(AgMethodLabel);

        timeRadioBtn = new QRadioButton(SignAgentDialog);
        timeRadioBtn->setObjectName(QString::fromUtf8("timeRadioBtn"));
        timeRadioBtn->setMaximumSize(QSize(80, 16777215));
        timeRadioBtn->setChecked(true);

        horizontalLayout_23->addWidget(timeRadioBtn);

        flowRadioBtn = new QRadioButton(SignAgentDialog);
        flowRadioBtn->setObjectName(QString::fromUtf8("flowRadioBtn"));
        flowRadioBtn->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_23->addWidget(flowRadioBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(6, -1, 6, -1);
        horizontalSpacer_25 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_25);

        AgTStartLabel = new QLabel(SignAgentDialog);
        AgTStartLabel->setObjectName(QString::fromUtf8("AgTStartLabel"));
        AgTStartLabel->setMinimumSize(QSize(140, 25));
        AgTStartLabel->setMaximumSize(QSize(140, 25));

        horizontalLayout_24->addWidget(AgTStartLabel);

        startDateTimeEdit = new QDateTimeEdit(SignAgentDialog);
        startDateTimeEdit->setObjectName(QString::fromUtf8("startDateTimeEdit"));
        startDateTimeEdit->setMinimumSize(QSize(140, 25));
        startDateTimeEdit->setMaximumSize(QSize(140, 25));
        startDateTimeEdit->setDate(QDate(2019, 1, 1));

        horizontalLayout_24->addWidget(startDateTimeEdit);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(6, -1, 6, -1);
        horizontalSpacer_35 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_35);

        AgTStopLabel = new QLabel(SignAgentDialog);
        AgTStopLabel->setObjectName(QString::fromUtf8("AgTStopLabel"));
        AgTStopLabel->setMinimumSize(QSize(140, 25));
        AgTStopLabel->setMaximumSize(QSize(140, 25));

        horizontalLayout_25->addWidget(AgTStopLabel);

        stopDateTimeEdit = new QDateTimeEdit(SignAgentDialog);
        stopDateTimeEdit->setObjectName(QString::fromUtf8("stopDateTimeEdit"));
        stopDateTimeEdit->setMinimumSize(QSize(140, 25));
        stopDateTimeEdit->setMaximumSize(QSize(140, 25));
        stopDateTimeEdit->setDate(QDate(2019, 1, 1));

        horizontalLayout_25->addWidget(stopDateTimeEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(6, -1, 6, -1);
        horizontalSpacer_36 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_36);

        AgFlowLabel = new QLabel(SignAgentDialog);
        AgFlowLabel->setObjectName(QString::fromUtf8("AgFlowLabel"));
        AgFlowLabel->setMinimumSize(QSize(140, 25));
        AgFlowLabel->setMaximumSize(QSize(140, 25));

        horizontalLayout_26->addWidget(AgFlowLabel);

        flowLineEdit = new QLineEdit(SignAgentDialog);
        flowLineEdit->setObjectName(QString::fromUtf8("flowLineEdit"));
        flowLineEdit->setEnabled(false);
        flowLineEdit->setMinimumSize(QSize(140, 25));
        flowLineEdit->setMaximumSize(QSize(140, 25));

        horizontalLayout_26->addWidget(flowLineEdit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_26);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        confirmBtn = new QPushButton(SignAgentDialog);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_2->addWidget(confirmBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancelBtn = new QPushButton(SignAgentDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(100, 25));

        horizontalLayout_2->addWidget(cancelBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SignAgentDialog);

        QMetaObject::connectSlotsByName(SignAgentDialog);
    } // setupUi

    void retranslateUi(QDialog *SignAgentDialog)
    {
        SignAgentDialog->setWindowTitle(QApplication::translate("SignAgentDialog", "Apply for service", nullptr));
        hintLabel->setText(QApplication::translate("SignAgentDialog", "Please complete the parameters needed for applying for the agent service: ", nullptr));
        AgMethodLabel->setText(QApplication::translate("SignAgentDialog", "Payment method: ", nullptr));
        timeRadioBtn->setText(QApplication::translate("SignAgentDialog", "Time limit", nullptr));
        flowRadioBtn->setText(QApplication::translate("SignAgentDialog", "Flow limit", nullptr));
        AgTStartLabel->setText(QApplication::translate("SignAgentDialog", "Time to start service: ", nullptr));
        AgTStopLabel->setText(QApplication::translate("SignAgentDialog", "Time to end service:  ", nullptr));
        AgFlowLabel->setText(QApplication::translate("SignAgentDialog", "Flow amount to use:", nullptr));
        flowLineEdit->setPlaceholderText(QApplication::translate("SignAgentDialog", "GB", nullptr));
        confirmBtn->setText(QApplication::translate("SignAgentDialog", "Confirm", nullptr));
        cancelBtn->setText(QApplication::translate("SignAgentDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignAgentDialog: public Ui_SignAgentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNAGENTDLG_H
