#pragma once

#include "processor.h"
#include "opencv_processor.h"

#include <memory>

namespace rz
{
    class processor_factory
    {
        rz::processor_context &m_context;

    public:
        processor_factory(rz::processor_context &context);

        std::unique_ptr<rz::processor_base> create_opencv_frame_luminance_processor(int output);
        std::unique_ptr<rz::processor_base> create_opencv_extract_processor(int input);
        std::unique_ptr<rz::processor_base> create_opencv_greyscale_to_bgra_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_greyscale_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_blur_processor(int input, int output);
        std::unique_ptr<rz::processor_base> create_opencv_brightness_constrast_processor(int input, int output);
        std::unique_ptr<rz::processor_base> create_opencv_equalise_histogram_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_sobel_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_canny_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_scharr_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_laplacian_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_otsu_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_resize_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_fill_processor(int input, int output);
		std::unique_ptr<rz::processor_base> create_opencv_max_processor(int input1, int input2, int output);
		std::unique_ptr<rz::processor_base> create_opencv_diff_processor(int input1, int input2, int output);
		std::unique_ptr<rz::processor_base> create_opencv_mask_processor(int input1, int input2, int output);
		std::unique_ptr<rz::processor_base> create_opencv_face_detector_processor(int input, int output);
    };
}
