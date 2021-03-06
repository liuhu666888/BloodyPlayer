﻿#include "trackwidget.h"
#include "ui_trackwidget.h"

#include <QMouseEvent>
#include <QMenu>
#include <QAction>

TrackWidget::TrackWidget(QString TrackName, QString TrackInfo, QString TrackTime, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackWidget)
{
    ui->setupUi(this);
    setFixedHeight(height());

    setContextMenuPolicy(Qt::CustomContextMenu);

    pMenuContextMenu = new QMenu(this);
    pMenuContextMenu->setStyleSheet("QMenu::item:selected\n{\n	background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(81, 0, 0, 255), stop:1 rgba(131, 19, 19, 255));\n}\n\n\nQMenu::separator\n{\n	background-color: rgb(50, 0, 0);\n	height: 2px;\n    margin-left: 10px; \n    margin-right: 5px;\n}");

        pActionMoveUp = new QAction  ("Move Up              W");
        connect(pActionMoveUp, &QAction::triggered, this, &TrackWidget::slotMoveUp);

        pActionMoveDown = new QAction("Move Down         S");
        connect(pActionMoveDown, &QAction::triggered, this, &TrackWidget::slotMoveDown);

        pActionDelete = new QAction  ("Delete                  Del");
        connect(pActionDelete, &QAction::triggered, this, &TrackWidget::slotDelete);

    pMenuContextMenu->addAction(pActionMoveUp);
    pMenuContextMenu->addAction(pActionMoveDown);
    pMenuContextMenu->addAction(pActionDelete);


    connect(this, &TrackWidget::signalSetPlaying, this, &TrackWidget::slotSetPlaying);
    connect(this, &TrackWidget::signalDisablePlaying, this, &TrackWidget::slotDisablePlaying);

    ui->label_TrackName->setText(TrackName);
    ui->label_TrackInfo->setText(TrackInfo);
    ui->label_TrackTime->setText(TrackTime);

    trackName = TrackName;
    trackInfo = TrackInfo;
    trackTime = TrackTime;

    bPlaying = false;
    bSelected = false;

    styleDefault = "QFrame"
                   "{"
                   "  background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(18, 18, 18, 255), stop:1 rgba(35, 35, 35, 255));"
                   "  border-radius: 25px;"
                   "  border: 1px solid rgb(140, 0, 0);"
                   "  color: white;"
                   "}"
                   ""
                   "QFrame:hover"
                   "{"
                   "  background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(18, 18, 18, 255), stop:1 rgba(56, 56, 56, 255));"
                   "}";

    styleSelected = "QFrame"
                    "{"
                    "  background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(35, 30, 30, 255), stop:1 rgba(88, 39, 39, 255));"
                    "  border-radius: 25px;"
                    "  border: 1px solid rgb(140, 0, 0);"
                    "  color: white;"
                    "}"
                    ""
                    "QFrame:hover"
                    "{"
                    "  background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(35, 30, 30, 255), stop:1 rgba(128, 59, 59, 255));"
                    "}";

    stylePlaying = "QFrame"
                   "{"
                   "  background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(35, 0, 0, 255), stop:1 rgba(65, 0, 0, 255));"
                   "  border-radius: 25px;"
                   "  border: 1px solid rgb(140, 0, 0);"
                      "color: white;"
                   "}"
                   ""
                   "QFrame:hover"
                   "{"
                   "  background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(35, 0, 0, 255), stop:1 rgba(98, 40, 40, 255));"
                   "}";

    ui ->frame ->setStyleSheet(styleDefault);
}

void TrackWidget::setPlaying()
{
    emit signalSetPlaying();
}

void TrackWidget::setBitrate(QString sBitrate)
{
    int iPos = trackInfo .indexOf("hz, ");

    if (iPos != -1)
    {
        QString sNewInfo = trackInfo .left(iPos + 4);
        sNewInfo += sBitrate;
        sNewInfo += " kbit/s, ";
        sNewInfo += trackInfo .right( trackInfo .size() - iPos - 4 );

        trackInfo = sNewInfo;

        ui ->label_TrackInfo ->setText(sNewInfo);

        emit signalUpdateTrackInfo(trackIndex);
    }
}

void TrackWidget::setNumber(size_t iNumber)
{
     ui->label_No->setText( QString::number(iNumber) );

     trackIndex = iNumber - 1;
}

void TrackWidget::enableSelected()
{
    mousePressEvent(nullptr);
}

void TrackWidget::disablePlaying()
{
    emit signalDisablePlaying();
}

void TrackWidget::disableSelected()
{
    bSelected = false;

    if (bPlaying)
    {
        slotSetPlaying();
    }
    else
    {
        disablePlaying();
    }
}

void TrackWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (bSelected)
    {
        bSelected = false;
        emit signalSelected(trackIndex);
    }

    emit signalDoubleClick(trackIndex);
    setPlaying();
}

void TrackWidget::mousePressEvent(QMouseEvent *ev)
{
    if (bSelected)
    {
        if (bPlaying)
        {
            ui->frame->setStyleSheet(stylePlaying);
        }
        else
        {
            ui->frame->setStyleSheet(styleDefault);
        }

        emit signalSelected(trackIndex);
        bSelected = false;
    }
    else
    {
        ui->frame->setStyleSheet(styleSelected);

        emit signalSelected(trackIndex);
        bSelected = true;
    }
}

void TrackWidget::slotMoveUp()
{
    emit signalMoveUp();

    bSelected = false;

    if (bPlaying)
    {
        ui->frame->setStyleSheet(stylePlaying);
    }
    else
    {
        ui->frame->setStyleSheet(styleDefault);
    }
}

void TrackWidget::slotMoveDown()
{
    emit signalMoveDown();

    bSelected = false;

    if (bPlaying)
    {
        ui->frame->setStyleSheet(stylePlaying);
    }
    else
    {
        ui->frame->setStyleSheet(styleDefault);
    }
}

void TrackWidget::slotDelete()
{
    emit signalDelete();
}

void TrackWidget::slotSetPlaying()
{
    if (!bSelected)
    {
        ui->frame->setStyleSheet(stylePlaying);
        update();
    }

    bPlaying = true;
}

void TrackWidget::slotDisablePlaying()
{
    if (bSelected)
    {
        ui->frame->setStyleSheet(styleSelected);
    }
    else
    {
        ui->frame->setStyleSheet(styleDefault);
    }

    bPlaying = false;
}

void TrackWidget::on_TrackWidget_customContextMenuRequested(const QPoint &pos)
{
    if (bSelected) pMenuContextMenu->exec(mapToGlobal(pos));
}

TrackWidget::~TrackWidget()
{
    delete pActionDelete;
    delete pActionMoveDown;
    delete pActionMoveUp;
    delete pMenuContextMenu;

    delete ui;
}
