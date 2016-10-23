#pragma once

//#include "cascade_classifier.h"

#include <opencv2/core/mat.hpp>
#include <vector>

namespace rz
{
    class processor_context
    {
        int m_height;
        int m_width;

        uint8_t *m_frameData;
        int m_frameDataSize;

        uint8_t *m_outputBuffer;

        std::vector<cv::Mat> m_mat;

        void release();

    public:
        processor_context(int number_of_mats);
        ~processor_context();

        void init(int width, int height);

        cv::Mat &mat(int idx) { return m_mat[idx]; }

        void set_frame_data(uint8_t *data);
        uint8_t *get_frame_data() const { return m_frameData; }
        void set_output_buffer(uint8_t *buffer);
        uint8_t *get_output_buffer() const { return m_outputBuffer; }

        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
    };
}
