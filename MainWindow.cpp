#include "MainWindow.h"
#include <QStringList>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    // Создаем QTabWidget
    auto *tabWidget = new QTabWidget(this);

    // Раздел для разреженного вектора
    auto *sparseVectorTab = new QWidget(this);
    auto *sparseLayout = new QVBoxLayout(sparseVectorTab);

    sparseInputSize = new QLineEdit(this);
    sparseInputSize->setPlaceholderText("Введите размер вектора");
    sparseLayout->addWidget(new QLabel("Размер вектора:", this));
    sparseLayout->addWidget(sparseInputSize);

    sparseInputValues = new QLineEdit(this);
    sparseInputValues->setPlaceholderText("Введите элементы через пробел");
    sparseLayout->addWidget(new QLabel("Элементы вектора:", this));
    sparseLayout->addWidget(sparseInputValues);

    auto *sparseProcessButton = new QPushButton("Создать разреженный вектор", this);
    sparseLayout->addWidget(sparseProcessButton);

    sparseResultLabel = new QLabel("Результат будет отображен здесь", this);
    sparseLayout->addWidget(sparseResultLabel);

    connect(sparseProcessButton, &QPushButton::clicked, this, &MainWindow::processSparseVector);

    tabWidget->addTab(sparseVectorTab, "Разреженный вектор");

    // Раздел для гистограммы
    auto *histogramTab = new QWidget(this);
    auto *histogramLayout = new QVBoxLayout(histogramTab);

    histogramInputValues = new QLineEdit(this);
    histogramInputValues->setPlaceholderText("Введите элементы через пробел");
    histogramLayout->addWidget(new QLabel("Элементы для гистограммы:", this));
    histogramLayout->addWidget(histogramInputValues);

    binWidthSpinBox = new QDoubleSpinBox(this);
    binWidthSpinBox->setMinimum(0.1);
    binWidthSpinBox->setValue(1.0);  // Значение по умолчанию
    histogramLayout->addWidget(new QLabel("Длина разбиения (ширина бина):", this));
    histogramLayout->addWidget(binWidthSpinBox);

    auto *histogramProcessButton = new QPushButton("Построить гистограмму", this);
    histogramLayout->addWidget(histogramProcessButton);

    histogramResultLabel = new QLabel("Гистограмма будет отображена ниже", this);
    histogramLayout->addWidget(histogramResultLabel);

    histogramView = new QGraphicsView(this);
    histogramScene = new QGraphicsScene(this);
    histogramView->setScene(histogramScene);
    histogramLayout->addWidget(histogramView);

    connect(histogramProcessButton, &QPushButton::clicked, this, &MainWindow::processHistogram);

    tabWidget->addTab(histogramTab, "Гистограмма");

    // Устанавливаем основной макет
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void MainWindow::processSparseVector() {
    bool ok;
    int size = sparseInputSize->text().toInt(&ok);
    if (!ok || size <= 0) {
        sparseResultLabel->setText("Ошибка: Введите корректный размер вектора.");
        return;
    }

    QStringList elements = sparseInputValues->text().split(" ", QString::SkipEmptyParts);
    if (elements.size() != size) {
        sparseResultLabel->setText("Ошибка: Количество элементов не соответствует размеру вектора.");
        return;
    }

    std::vector<int> vector;
    for (const QString &elem : elements) {
        int value = elem.toInt(&ok);
        if (!ok) {
            sparseResultLabel->setText("Ошибка: Все элементы должны быть числами.");
            return;
        }
        vector.push_back(value);
    }

    sparseResultLabel->setText("Разреженный вектор создан: [" + sparseInputValues->text() + "]");
}

void MainWindow::processHistogram() {
    histogramScene->clear();

    QStringList elements = histogramInputValues->text().split(" ", QString::SkipEmptyParts);
    std::vector<double> values;
    bool ok;
    for (const QString &elem : elements) {
        double value = elem.toDouble(&ok);
        if (!ok) {
            histogramResultLabel->setText("Ошибка: Все элементы должны быть числами.");
            return;
        }
        values.push_back(value);
    }


    if (values.empty()) {
        histogramResultLabel->setText("Ошибка: Введите хотя бы одно значение.");
        return;
    }

    double binWidth = binWidthSpinBox->value();
    if (binWidth <= 0) {
        histogramResultLabel->setText("Ошибка: Длина разбиения должна быть больше 0.");
        return;
    }

    double minValue = *std::min_element(values.begin(), values.end());
    double maxValue = *std::max_element(values.begin(), values.end());

    int binCount = static_cast<int>(std::ceil((maxValue - minValue) / binWidth));
    std::vector<int> bins(binCount, 0);

    for (double value : values) {
        int binIndex = static_cast<int>((value - minValue) / binWidth);
        if (binIndex >= binCount) binIndex = binCount - 1;
        bins[binIndex]++;
    }

    int barWidth = 30;
    int spacing = 10;
    int x = 0;

    for (int i = 0; i < bins.size(); ++i) {
        double rangeStart = minValue + i * binWidth;
        double rangeEnd = rangeStart + binWidth;

        QGraphicsRectItem *bar = new QGraphicsRectItem(x, -bins[i] * 10, barWidth, bins[i] * 10);
        bar->setBrush(Qt::blue);
        histogramScene->addItem(bar);

        QGraphicsTextItem *label = new QGraphicsTextItem(QString("[%1, %2)").arg(rangeStart).arg(rangeEnd));
        label->setPos(x, 10);
        histogramScene->addItem(label);

        x += barWidth + spacing;
    }

    histogramView->fitInView(histogramScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    histogramResultLabel->setText("Гистограмма построена.");
}