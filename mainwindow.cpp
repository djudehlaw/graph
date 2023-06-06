#include "mainwindow.h"
#include "QPainter"
#include "ui_mainwindow.h"
#include <QtMath>
#include "poland.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    button = new QPushButton(this);
    button->setGeometry(width()-100-10, 10, 100,40);
    button->setText("draw graph");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonDraw()));
    ui->label->setGeometry(10, 10+40+10, width()-130, height()-120);
    ui->lineEdit->setGeometry(10, 10, ui->label->width(), 40);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::buttonDraw()
{


    QPixmap pm (ui->label->width(), ui->label->height());

    QPainter painter;
    painter.begin(&pm);
    pm.fill(Qt:: white);
    QPen pen;
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);

    painter.setPen(pen);
    //painter.setBrush(QBrush(0x608d6b));
    //painter.drawEllipse(100,50,150,150);



    double x, y;
    double xmin = -5;
    double xmax = 5;
    double ymin = -5;
    double ymax = 5;

    int xgmin = 0;
    int xgmax = pm.width();
    int ygmin = 0;
    int ygmax = pm.height();

    double kx = (xgmax - xgmin)/(xmax - xmin);
    double ky = (ygmin - ygmax)/(ymax - ymin);
    int xg, yg;
    int x0 = xgmin - kx*xmin;
    int y0 = ygmin - ky*ymax;

    double stepx = (xmax-xmin)/(xgmax-xgmin);

   // painter.drawLine(x0-pm.width(), y0, x0+pm.width(), y0);
   // painter.drawLine(x0, y0-pm.width(), x0, y0+pm.width());


    QPainterPath path;
    double ans = 0;
    QString funct = ui->lineEdit->text();
    QString ff = funct;



    x = xmin;
    QString fx = QString::number(x);
    fx = "(" +fx + ")";
    funct.replace("x", fx);
    ui->lineEdit->setText(funct);

    int pri = calc(funct.toStdString(), ans);
    ui->lineEdit->setText(QString::number(ans));
    y = ans;
    //y = sin(x);

    xg = x0 + kx*x;
    yg = y0 + ky*y;
    path.moveTo(xg, yg);

    while(x <= xmax) {
        fx = QString::number(x);
        fx = "(" +fx + ")";
        funct = ff;
        funct.replace("x", fx);
        int p = calc(funct.toStdString(), ans);

        if (p==0){
            y = ans;
            //y = sin(x);
            xg = x0 + kx*x;
            yg = y0 + ky*y;
            path.lineTo(xg, yg);
            x+=stepx;
        }
        else
            printf("%d", 7);
    }
    pen.setWidth(3);
    pen.setBrush(Qt::red);
    painter.setPen(pen);
    painter.drawPath(path);
    ui->label->setPixmap(pm);

}
