/********************************************************************************
** Form generated from reading UI file 'fatigue.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FATIGUE_H
#define UI_FATIGUE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Fatigue
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_7;
    QWidget *STATUS;
    QGridLayout *gridLayout_8;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QGridLayout *gridLayout_6;
    QWidget *widget_5;
    QGridLayout *gridLayout_5;
    QProgressBar *fx_pB;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_6;
    QProgressBar *pl_pB;
    QLabel *label_5;
    QWidget *widget_4;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_10;
    QLabel *plot;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QToolButton *open_close_video;
    QSpacerItem *verticalSpacer_4;
    QComboBox *vido_cbx;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_2;
    QLabel *detect_status;
    QSpacerItem *horizontalSpacer_5;
    QLabel *clock;
    QSpacerItem *horizontalSpacer_3;
    QWidget *VIDEO;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_2;
    QLabel *video_zoom;
    QWidget *TITLE;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *Fatigue)
    {
        if (Fatigue->objectName().isEmpty())
            Fatigue->setObjectName(QString::fromUtf8("Fatigue"));
        Fatigue->resize(414, 574);
        centralwidget = new QWidget(Fatigue);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_7 = new QGridLayout(centralwidget);
        gridLayout_7->setSpacing(0);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        STATUS = new QWidget(centralwidget);
        STATUS->setObjectName(QString::fromUtf8("STATUS"));
        gridLayout_8 = new QGridLayout(STATUS);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_8->addItem(verticalSpacer_3, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 3, 0, 1, 1);

        widget_3 = new QWidget(STATUS);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_6 = new QGridLayout(widget_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        sizePolicy.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(widget_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, -1);
        fx_pB = new QProgressBar(widget_5);
        fx_pB->setObjectName(QString::fromUtf8("fx_pB"));
        fx_pB->setStyleSheet(QString::fromUtf8("QProgressBar{border:1px;background:white;}\n"
"QProgressBar::chunk{background:red}"));
        fx_pB->setValue(100);
        fx_pB->setTextVisible(false);

        gridLayout_5->addWidget(fx_pB, 1, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 1, 1, 1, 1);

        pl_pB = new QProgressBar(widget_5);
        pl_pB->setObjectName(QString::fromUtf8("pl_pB"));
        pl_pB->setStyleSheet(QString::fromUtf8("QProgressBar{border:1px;background:white;}\n"
"QProgressBar::chunk{background:red}"));
        pl_pB->setValue(30);
        pl_pB->setTextVisible(false);

        gridLayout_5->addWidget(pl_pB, 0, 2, 1, 1);

        label_5 = new QLabel(widget_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 0, 1, 1, 1);


        gridLayout_6->addWidget(widget_5, 0, 0, 1, 1);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_4 = new QGridLayout(widget_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, -1);
        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_10, 0, 1, 1, 1);

        plot = new QLabel(widget_4);
        plot->setObjectName(QString::fromUtf8("plot"));
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);
        plot->setPixmap(QPixmap(QString::fromUtf8(":/mintor.svg")));
        plot->setScaledContents(true);
        plot->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(plot, 0, 0, 1, 1);


        gridLayout_6->addWidget(widget_4, 0, 1, 1, 1);


        gridLayout_8->addWidget(widget_3, 5, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_8->addItem(verticalSpacer_5, 2, 0, 1, 1);

        widget_2 = new QWidget(STATUS);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 0));
        widget_2->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, -1);
        open_close_video = new QToolButton(widget_2);
        open_close_video->setObjectName(QString::fromUtf8("open_close_video"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(open_close_video->sizePolicy().hasHeightForWidth());
        open_close_video->setSizePolicy(sizePolicy1);
        open_close_video->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/triangle-play.svg"), QSize(), QIcon::Normal, QIcon::Off);
        open_close_video->setIcon(icon);
        open_close_video->setAutoExclusive(false);
        open_close_video->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        open_close_video->setAutoRaise(false);

        gridLayout_3->addWidget(open_close_video, 1, 4, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_4, 0, 3, 1, 1);

        vido_cbx = new QComboBox(widget_2);
        vido_cbx->addItem(QString());
        vido_cbx->setObjectName(QString::fromUtf8("vido_cbx"));

        gridLayout_3->addWidget(vido_cbx, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 1, 5, 1, 1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setMaximumSize(QSize(70, 70));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/shexiang.svg")));
        label_7->setScaledContents(true);

        gridLayout_3->addWidget(label_7, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 0, 1, 1);


        gridLayout_8->addWidget(widget_2, 1, 0, 1, 1);

        widget = new QWidget(STATUS);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 40));
        widget->setMaximumSize(QSize(16777215, 100000));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 5, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        detect_status = new QLabel(widget);
        detect_status->setObjectName(QString::fromUtf8("detect_status"));

        gridLayout_2->addWidget(detect_status, 0, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        clock = new QLabel(widget);
        clock->setObjectName(QString::fromUtf8("clock"));
        clock->setMaximumSize(QSize(130, 16777215));

        gridLayout_2->addWidget(clock, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 3, 1, 1);


        gridLayout_8->addWidget(widget, 0, 0, 1, 1);


        gridLayout_7->addWidget(STATUS, 2, 0, 1, 1);

        VIDEO = new QWidget(centralwidget);
        VIDEO->setObjectName(QString::fromUtf8("VIDEO"));
        sizePolicy.setHeightForWidth(VIDEO->sizePolicy().hasHeightForWidth());
        VIDEO->setSizePolicy(sizePolicy);
        VIDEO->setMaximumSize(QSize(16777215, 16777215));
        VIDEO->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(VIDEO);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(10, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 1);

        video_zoom = new QLabel(VIDEO);
        video_zoom->setObjectName(QString::fromUtf8("video_zoom"));
        video_zoom->setStyleSheet(QString::fromUtf8(""));
        video_zoom->setPixmap(QPixmap(QString::fromUtf8(":/dectRect.svg")));
        video_zoom->setAlignment(Qt::AlignCenter);
        video_zoom->setWordWrap(false);
        video_zoom->setOpenExternalLinks(false);

        gridLayout->addWidget(video_zoom, 1, 0, 1, 1);


        gridLayout_7->addWidget(VIDEO, 1, 0, 1, 1);

        TITLE = new QWidget(centralwidget);
        TITLE->setObjectName(QString::fromUtf8("TITLE"));
        sizePolicy2.setHeightForWidth(TITLE->sizePolicy().hasHeightForWidth());
        TITLE->setSizePolicy(sizePolicy2);
        TITLE->setMinimumSize(QSize(0, 100));
        TITLE->setMaximumSize(QSize(16777215, 60));
        TITLE->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 127);"));
        horizontalLayout = new QHBoxLayout(TITLE);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(TITLE);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMaximumSize(QSize(90, 70));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/mintor.svg")));
        label_3->setScaledContents(true);

        horizontalLayout->addWidget(label_3);

        label = new QLabel(TITLE);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 50));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setLineWidth(1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_7->addWidget(TITLE, 0, 0, 1, 1);

        Fatigue->setCentralWidget(centralwidget);

        retranslateUi(Fatigue);

        QMetaObject::connectSlotsByName(Fatigue);
    } // setupUi

    void retranslateUi(QMainWindow *Fatigue)
    {
        Fatigue->setWindowTitle(QApplication::translate("Fatigue", "Fatigue", nullptr));
        label_6->setText(QApplication::translate("Fatigue", "\345\210\206\345\277\203\347\250\213\345\272\246\357\274\232", nullptr));
        label_5->setText(QApplication::translate("Fatigue", "\347\226\262\345\212\263\347\250\213\345\272\246\357\274\232", nullptr));
        plot->setText(QString());
        open_close_video->setText(QApplication::translate("Fatigue", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        vido_cbx->setItemText(0, QApplication::translate("Fatigue", "\346\221\204\345\203\217\345\244\264", nullptr));

        label_7->setText(QString());
        label_2->setText(QApplication::translate("Fatigue", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\232", nullptr));
        detect_status->setText(QApplication::translate("Fatigue", "\346\250\241\345\236\213\345\210\235\345\247\213\345\214\226\344\270\255...", nullptr));
        clock->setText(QApplication::translate("Fatigue", "Time", nullptr));
        video_zoom->setText(QString());
        label_3->setText(QString());
        label->setText(QApplication::translate("Fatigue", "\347\226\262\345\212\263\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Fatigue: public Ui_Fatigue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FATIGUE_H
