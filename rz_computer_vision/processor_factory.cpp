#include "processor_factory.h"

#include "opencv_processor.h"

rz::processor_factory::processor_factory(rz::processor_context &context) :
        m_context(context)
{
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_frame_luminance_processor(
        int output)
{
    return std::unique_ptr<rz::processor_base>(new opencv_frame_luminance_processor(m_context, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_extract_processor(int input)
{
    return std::unique_ptr<rz::processor_base>(new opencv_extract_processor(m_context, input));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_greyscale_to_bgra_processor(
        int input, int output)
{
    return std::unique_ptr<rz::processor_base>(new opencv_greyscale_to_bgra_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_greyscale_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_greyscale_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_blur_processor(int input,
                                                                                   int output)
{
    return std::unique_ptr<rz::processor_base>(new opencv_blur_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_brightness_constrast_processor(
        int input, int output)
{
    return std::unique_ptr<rz::processor_base>(new opencv_brightness_constrast_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_equalise_histogram_processor(
        int input, int output)
{
    return std::unique_ptr<rz::processor_base>(new opencv_equalise_histogram_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_sobel_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_sobel_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_canny_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_canny_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_scharr_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_scharr_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_laplacian_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_laplacian_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_otsu_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_otsu_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_resize_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_resize_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_fill_processor(int input, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_fill_processor(m_context, input, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_max_processor(int input1, int input2, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_max_processor(m_context, input1, input2, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_diff_processor(int input1, int input2, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_diff_processor(m_context, input1, input2, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_mask_processor(int image, int mask, int output)
{
	return std::unique_ptr<rz::processor_base>(new opencv_mask_processor(m_context, image, mask, output));
}

std::unique_ptr<rz::processor_base> rz::processor_factory::create_opencv_face_detector_processor(
        int input, int output)
{
    return std::unique_ptr<rz::processor_base>(new opencv_cascade_classifier_processor(m_context, input, output));
}

















