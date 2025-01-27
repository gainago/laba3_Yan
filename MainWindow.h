#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDoubleSpinBox>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void processSparseVector();
    void processHistogram();

private:
    // Для вкладки "Разреженный вектор"
    QLineEdit *sparseInputSize;
    QLineEdit *sparseInputValues;
    QLabel *sparseResultLabel;

    // Для вкладки "Гистограмма"
    QLineEdit *histogramInputValues;
    QDoubleSpinBox *binWidthSpinBox;
    QLabel *histogramResultLabel;
    QGraphicsView *histogramView;
    QGraphicsScene *histogramScene;
};

#endif // MAINWINDOW_H