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

#include "playSound.h"
#include <QApplication>
#include <QMessageBox>

PlaySound::PlaySound()
{
    initialiseAudio();
    openStream();
}

PlaySound::~PlaySound()
{
    m_err = Pa_CloseStream(m_stream);
    if(m_err != paNoError)
        error("Failed to close sound stream.");

    Pa_Terminate();
}

void PlaySound::play()
{
    m_err = Pa_StartStream(m_stream);
    if(m_err != paNoError)
        error("Failed to start sound stream.");

    static float data[cm_FRAMES_PER_BUFFER] = {0};
    float volume = 0.2;

    int readcount = 0;
    while((readcount = m_file.read(data, cm_FRAMES_PER_BUFFER)))
    {
        for(int i = 0; i < cm_FRAMES_PER_BUFFER; ++i)
            data[i] *= volume;

        m_err = Pa_WriteStream(m_stream, data, cm_FRAMES_PER_BUFFER);
        if(m_err != paNoError)
        {
            error("Failed to write sound stream.");
            break;
        }
    }

    m_err = Pa_StopStream(m_stream);
    if(m_err != paNoError)
        error("Failed to stop sound stream.");
}

void PlaySound::read(const char *fname)
{
    m_file = SndfileHandle(fname);

    if(m_file.error())
        error(QString("Failed to open file: %1").arg(fname));
}

void PlaySound::error(QString errorstr)
{
    QMessageBox::information(0, "Audio Error", errorstr);
    qApp->quit();
}

void PlaySound::initialiseAudio()
{
    m_err = Pa_Initialize();
    if(m_err != paNoError)
        error("Failed to initialise.");

    m_outputParameters.device = Pa_GetDefaultOutputDevice();
    m_outputParameters.channelCount = 1;
    m_outputParameters.sampleFormat = paFloat32;
    m_outputParameters.suggestedLatency = Pa_GetDeviceInfo(m_outputParameters.device)->defaultLowOutputLatency;
    m_outputParameters.hostApiSpecificStreamInfo = NULL;
}

void PlaySound::openStream()
{
    m_err = Pa_OpenStream(&m_stream, NULL, &m_outputParameters, cm_SAMPLE_RATE, cm_FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
    if(m_err != paNoError)
        error("Failed to open sound stream.");
}
