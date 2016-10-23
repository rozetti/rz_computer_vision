#include "opencv_processor.h"
#include "cascade_classifier.h"

#include "opencv2/opencv.hpp"

#ifdef ANDROID
#include <android/log.h>

#define  LOG_TAG    "opencv_processor"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define  LOGI(...)  
#define  LOGE(...)  
#endif

void rz::opencv_frame_luminance_processor::process()
{
    auto &output = m_context.mat(get_first_output());

    output = cv::Mat(m_context.get_height(), m_context.get_width(), CV_8UC1, m_context.get_frame_data());
}

void rz::opencv_extract_processor::process()
{
    auto &input = m_context.mat(get_first_input());

    cv::Mat buffer(m_context.get_height(), m_context.get_width(), CV_8UC4, m_context.get_output_buffer());

    buffer = input.clone();
}

void rz::opencv_greyscale_to_bgra_processor::process()
{
    auto &input = m_context.mat(get_first_input());
    auto &output = m_context.mat(get_first_output());

    cv::cvtColor(input, output, cv::COLOR_GRAY2BGRA);
}

void rz::opencv_greyscale_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
}

void rz::opencv_brightness_constrast_processor::process()
{
    auto &input = m_context.mat(get_first_input());
    auto &output = m_context.mat(get_first_output());

    auto contrast_parm = m_parameters[rz::OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_CONTRAST];
    auto brightness_parm = m_parameters[rz::OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_BRIGHTNESS];

    auto contrast = (static_cast<double>(contrast_parm) + 100.0) / 100.0;
    auto brightness = 128.0 * (static_cast<double>(brightness_parm) / 100.0);

    input.convertTo(output, -1, contrast, brightness);
}

void rz::opencv_blur_processor::process()
{
    auto &input = m_context.mat(get_first_input());
    auto &output = m_context.mat(get_first_output());

    auto kernel_size_parm = get_parameter(rz::OPENCV_BLUR_PROCCESSOR_PARMS_KERNEL_SIZE);

	cv::medianBlur(input, output, kernel_size_parm);
}

void rz::opencv_equalise_histogram_processor::process()
{
    auto &input = m_context.mat(get_first_input());
    auto &output = m_context.mat(get_first_output());

    equalizeHist(input, output);
}

void rz::opencv_cascade_classifier_processor::process()
{
    auto &input = m_context.mat(get_first_input());
    auto &output = m_context.mat(get_first_output());

	auto scale_factor_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_SCALE_FACTOR);
	auto min_neighbours_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MIN_NEIGHBOURS);
	auto min_object_size_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MIN_OBJECT_SIZE);
	auto max_object_size_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MAX_OBJECT_SIZE);
	auto mark_colour_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_COLOUR);
	auto mark_thickness_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_THICKNESS);
	auto mark_shape_parm_parm = get_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_SHAPE);

	m_classifier.set_scale_factor((double)scale_factor_parm / 100.0);
	m_classifier.set_min_neighbours(min_neighbours_parm);
	m_classifier.set_min_object_size(min_object_size_parm);
	m_classifier.set_max_object_size(max_object_size_parm);

    std::vector<cv::Rect> rects;
    m_classifier.detect(input, rects);

    if (!rects.empty())
    {
        LOGI("found faces: %d\r\n", rects.size());

		auto thickness = 0 != mark_thickness_parm ? mark_thickness_parm : cv::FILLED;

        for(auto const &rect : rects)
        {
			switch (mark_shape_parm_parm)
			{
			case rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_MARK_SHAPE_RECTANGLE:
				cv::rectangle(output, rect.tl(), rect.br(), mark_colour_parm, thickness);
				break;
			case rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_MARK_SHAPE_ELLIPSE:
				{
					cv::Point centre(rect.x + rect.width / 2, rect.y + rect.height / 2);
					cv::Size size(rect.width, rect.height);
					cv::RotatedRect rr(centre, size, 0);
					cv::ellipse(output, rr, mark_colour_parm, thickness);
					break;
				}
			}
        }
    }
}

void rz::opencv_resize_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	auto scale_percent = get_parameter(rz::OPENCV_RESIZE_PROCESSOR_PARMS_SCALE_PERCENT);

	double scale = scale_percent / 100.0;

	cv::resize(input, output, cv::Size(), scale, scale, cv::INTER_LINEAR);
}

void rz::opencv_fill_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	if (&output != &input)
	{
		output = input.clone(); // todo crz: better
	}

	auto colour_parm = get_parameter(rz::OPENCV_FILL_PROCESSOR_PARMS_COLOUR);

	output = colour_parm;
}

void rz::opencv_max_processor::process()
{
	auto &input1 = m_context.mat(get_first_input());
	auto &input2 = m_context.mat(get_second_input());
	auto &output = m_context.mat(get_first_output());

	output = cv::max(input1, input2);
}
 
void rz::opencv_diff_processor::process()
{
	auto &input1 = m_context.mat(get_first_input());
	auto &input2 = m_context.mat(get_second_input());
	auto &output = m_context.mat(get_first_output());

	cv::absdiff(input1, input2, output);
}

void rz::opencv_mask_processor::process()
{
	auto &input1 = m_context.mat(get_first_input());
	auto &input2 = m_context.mat(get_second_input());
	auto &output = m_context.mat(get_first_output());

	input1.copyTo(output, input2);
}

void rz::opencv_sobel_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	cv::Sobel(input, output, -1, 1, 1);
}

void rz::opencv_canny_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	cv::Canny(input, output, 80, 100);
}

void rz::opencv_scharr_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	cv::Scharr(input, output, -1, 1, 0);
}

void rz::opencv_otsu_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	cv::threshold(input, output, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
}

void rz::opencv_laplacian_processor::process()
{
	auto &input = m_context.mat(get_first_input());
	auto &output = m_context.mat(get_first_output());

	cv::Laplacian(input, output, -1, 5);
	output = 255 - output;;
}
