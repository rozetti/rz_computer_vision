#include "processor_context.h"

rz::processor_context::processor_context(int number_of_mats) :
        m_width(0),
        m_height(0),
        m_mat(number_of_mats),
        m_frameData(nullptr),
        m_frameDataSize(0)
{
}

rz::processor_context::~processor_context()
{
    release();
}

void rz::processor_context::set_frame_data(uint8_t *data)
{
    if (m_frameData)
    {
        memcpy(m_frameData, data, m_frameDataSize);
    }
}

void rz::processor_context::set_output_buffer(uint8_t *buffer)
{
    m_outputBuffer = buffer;
}

void rz::processor_context::release()
{
    if (m_frameData)
    {
        delete [] m_frameData;
        m_frameData = nullptr;
    }
}

void rz::processor_context::init(int width, int height)
{
    m_width = width;
    m_height = height;

    release();

    m_frameDataSize = static_cast<int>(1.5 * width * height);
    m_frameData = new uint8_t[m_frameDataSize];
}

