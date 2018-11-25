/*
 * https://github.com/asblog
 * https://neurodiversethoughts.wordpress.com/
 *
 * MIT License
 *
 * Copyright (c) 2018 asblog/neurodiversethoughts
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "mainWindow.h"
#include <QApplication>
#include <QDir>
#include <QKeyEvent>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setStyleSheet("background-color: #44BBFF;");
    this->setStyle(new NewStyle);
    this->setFixedSize(500, 330);

    m_labelImage = new QLabel(this);
    m_buttonStart = new QPushButton("Start", this);
    m_buttonStop = new QPushButton("Stop", this);
    m_buttonQuit = new QPushButton("Quit", this);
    m_spinTime = new SpinTime(this);
    m_spinSound = new SpinSound(this);
    m_labelTime = new QLabel(this);
    m_labelSound = new QLabel(this);
    m_timerSound = new QTimer(this);
    m_timerFinish = new QTimer(this);

    connect(m_buttonStart, SIGNAL(released()), this, SLOT(on_buttonStart_clicked()));
    connect(m_buttonStop, SIGNAL(released()), this, SLOT(on_buttonStop_clicked()));
    connect(m_buttonQuit, SIGNAL(released()), this, SLOT(on_buttonQuit_clicked()));
    connect(m_spinTime, SIGNAL(timeChanged(QTime)), this, SLOT(on_spin_change()), Qt::QueuedConnection);
    connect(m_spinSound, SIGNAL(valueChanged(double)), this, SLOT(on_spin_change()), Qt::QueuedConnection);
    connect(m_timerSound, SIGNAL(timeout()), this, SLOT(on_timer_sound()));
    connect(m_timerFinish, SIGNAL(timeout()), this, SLOT(on_timer_finish()));

    setupLayout();

    m_randGenerator.seed(m_randDevice());
}

void MainWindow::on_buttonQuit_clicked()
{
    qApp->quit();
}

void MainWindow::on_spin_change()
{
    m_spinTime->findChild<QLineEdit*>()->deselect();
    m_spinSound->findChild<QLineEdit*>()->deselect();
}

void MainWindow::on_timer_sound()
{
    int n;
    static int oldN = 0;

    uniform_int_distribution<int> distribution(1, 4);

    do // don't want repeating numbers
    {
        n = distribution(m_randGenerator);
    } while(n == oldN);

    oldN = n;

    m_playSound.read(QDir(QApplication::applicationDirPath()).filePath("sound/%1.wav").arg(n).toLocal8Bit().data());
    m_playSound.play();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        qApp->quit();
}

void MainWindow::setupLayout()
{
    m_labelImage->setPixmap(QPixmap(QDir(QApplication::applicationDirPath()).filePath("image/qmt.png")));
    m_labelImage->setGeometry(230, 60, 200, 200);

    m_buttonStart->setGeometry(70, 50, 100, 50);

    m_buttonStop->setGeometry(70, 50, 100, 50);
    m_buttonStop->setStyleSheet("background-color: #AAAAAA;");
    m_buttonStop->hide();
    m_buttonStop->setEnabled(false);

    m_buttonQuit->setGeometry(85, 240, 70, 30);
    m_buttonQuit->setStyleSheet("background-color: #FF8888;");

    m_spinTime->setGeometry(90, 130, 60, 30);
    m_spinTime->setTime(QTime(0, 7, 30, 0));

    m_spinSound->setGeometry(95, 190, 50, 30);
    m_spinSound->setValue(2.0);

    m_labelTime->setText("Time Limit");
    m_labelTime->setStyleSheet("color: #000000");
    m_labelTime->setGeometry(88, 110, 80, 20);

    m_labelSound->setText("Step Frequency");
    m_labelSound->setStyleSheet("color: #000000");
    m_labelSound->setGeometry(74, 170, 110, 20);
}

void MainWindow::start()
{
    int getTime = m_spinTime->time().minute() * 60;
    getTime += m_spinTime->time().second();
    getTime *= 1000;

    m_timerSound->start(m_spinSound->value() * 1000);
    m_timerFinish->start(getTime);

    m_labelImage->hide();
    m_spinTime->setEnabled(false);
    m_spinSound->setEnabled(false);

    m_buttonStart->hide();
    m_buttonStart->setEnabled(false);

    m_buttonStop->show();
    m_buttonStop->setEnabled(true);
}

void MainWindow::stop()
{
    m_timerSound->stop();
    m_timerFinish->stop();

    m_labelImage->show();
    m_spinTime->setEnabled(true);
    m_spinSound->setEnabled(true);

    m_buttonStart->show();
    m_buttonStart->setEnabled(true);

    m_buttonStop->hide();
    m_buttonStop->setEnabled(false);
}
