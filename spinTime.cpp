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

#include "spinTime.h"
#include <QLineEdit>

SpinTime::SpinTime(QWidget *parent) : QTimeEdit(parent)
{
    setDisplayFormat(QString("m:ss"));
    setTimeRange(QTime(0, 1, 0, 0), QTime(0, 59, 59, 0));
    setCurrentSection(QTimeEdit::SecondSection);
    setStyleSheet("background-color: #FFFFFF;");
    setWrapping(true);

    findChild<QLineEdit*>()->setReadOnly(true);
}

void SpinTime::stepBy(int steps)
{
    if(currentSection() == QTimeEdit::MinuteSection)
        setTime(time().addSecs(steps * 60));
    else if(currentSection() == QTimeEdit::SecondSection)
        setTime(time().addSecs(steps));
}
