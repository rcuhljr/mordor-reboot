/********************************************************************************
** Form generated from reading UI file 'createcharacterwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECHARACTERWIDGET_H
#define UI_CREATECHARACTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createCharacterWidget
{
public:
    QWidget *dockWidgetContents;
    QPushButton *pushButton;

    void setupUi(QDockWidget *createCharacterWidget)
    {
        if (createCharacterWidget->objectName().isEmpty())
            createCharacterWidget->setObjectName(QStringLiteral("createCharacterWidget"));
        createCharacterWidget->resize(400, 300);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(180, 120, 75, 23));
        createCharacterWidget->setWidget(dockWidgetContents);

        retranslateUi(createCharacterWidget);

        QMetaObject::connectSlotsByName(createCharacterWidget);
    } // setupUi

    void retranslateUi(QDockWidget *createCharacterWidget)
    {
        createCharacterWidget->setWindowTitle(QApplication::translate("createCharacterWidget", "DockWidget", 0));
        pushButton->setText(QApplication::translate("createCharacterWidget", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class createCharacterWidget: public Ui_createCharacterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECHARACTERWIDGET_H
