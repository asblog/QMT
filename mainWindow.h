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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newStyle.h"
#include "spinSound.h"
#include "spinTime.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <random>
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void on_buttonStart_clicked() { start(); }
    void on_buttonStop_clicked() { stop(); }
    void on_buttonQuit_clicked();
    void on_spin_change();
    void on_timer_sound();
    void on_timer_finish() { stop(); }

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void setupLayout();
    void start();
    void stop();

private:
    QLabel *m_labelImage, *m_labelTime, *m_labelSound;
    QPushButton *m_buttonStart, *m_buttonStop, *m_buttonQuit;
    QTimer *m_timerSound, *m_timerFinish;

    SpinTime *m_spinTime;
    SpinSound *m_spinSound;

    random_device m_randDevice;
    mt19937 m_randGenerator;
};

#endif // MAINWINDOW_H
