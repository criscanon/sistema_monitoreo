#ifndef PROYECTO_H
#define PROYECTO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Proyecto; }
QT_END_NAMESPACE

class Proyecto : public QMainWindow
{
    Q_OBJECT

public:
    Proyecto(QWidget *parent = nullptr);
    ~Proyecto();

private slots:
    void on_BtStart_clicked();

    void on_GREEN_linkActivated(const QString &link);

private:
    Ui::Proyecto *ui;
};
#endif // PROYECTO_H
