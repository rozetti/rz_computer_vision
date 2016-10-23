#pragma once

#include "processor.h"
#include "processor_context.h"

namespace rz
{
    struct opencv_frame_luminance_processor : public processor<opencv_frame_luminance_processor, 0, 1, 0>
    {
        opencv_frame_luminance_processor(rz::processor_context &context, int output) :
                processor(context, {{ }}, {{ output }}) {}
        virtual void process() override;
    };

    struct opencv_extract_processor : public processor<opencv_extract_processor, 1, 0, 0>
    {
        opencv_extract_processor(rz::processor_context &context, int input) :
                processor(context, {{ input }}, {{ }}) {}
        virtual void process() override;
    };

    struct opencv_greyscale_to_bgra_processor : public processor<opencv_greyscale_to_bgra_processor, 1, 1, 0>
    {
        opencv_greyscale_to_bgra_processor(rz::processor_context &context, int input, int output) :
                processor(context, {{ input }}, {{ output }}) {}
        virtual void process() override;
    };

	struct opencv_greyscale_processor : public processor<opencv_greyscale_processor, 1, 1, 0>
	{
		opencv_greyscale_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	enum opencv_blur_processor_parms_t
	{
		OPENCV_BLUR_PROCCESSOR_PARMS_KERNEL_SIZE = 0,
		OPENCV_BLUR_PROCCESSOR_PARMS_COUNT
	};

	struct opencv_blur_processor : public processor<opencv_blur_processor, 1, 1, rz::OPENCV_BLUR_PROCCESSOR_PARMS_COUNT>
    {
		opencv_blur_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
        virtual void process() override;
    };

	enum opencv_brightness_constrast_processor_parms_t
	{
		OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_BRIGHTNESS = 0,
		OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_CONTRAST,
		OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_COUNT
	};
	
	struct opencv_brightness_constrast_processor : public processor<opencv_brightness_constrast_processor, 1, 1, rz::OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_COUNT>
    {
        opencv_brightness_constrast_processor(rz::processor_context &context, int input, int output) :
                processor(context, {{ input }}, {{ output }}) {}
        virtual void process() override;
    };

    struct opencv_equalise_histogram_processor : public processor<opencv_equalise_histogram_processor, 1, 1, 0>
    {
        opencv_equalise_histogram_processor(rz::processor_context &context, int input, int output) :
                processor(context, {{ input }}, {{ output }}) {}
        virtual void process() override;
    };

	struct opencv_sobel_processor : public processor<opencv_sobel_processor, 1, 1, 0>
	{
		opencv_sobel_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_canny_processor : public processor<opencv_canny_processor, 1, 1, 0>
	{
		opencv_canny_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_otsu_processor : public processor<opencv_otsu_processor, 1, 1, 0>
	{
		opencv_otsu_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_scharr_processor : public processor<opencv_scharr_processor, 1, 1, 0>
	{
		opencv_scharr_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_laplacian_processor : public processor<opencv_laplacian_processor, 1, 1, 0>
	{
		opencv_laplacian_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	enum opencv_resize_processor_parm_t
	{
		OPENCV_RESIZE_PROCESSOR_PARMS_SCALE_PERCENT = 0,
		OPENCV_RESIZE_PROCESSOR_PARMS_COUNT
	};

	struct opencv_resize_processor : public processor<opencv_resize_processor, 1, 1, rz::OPENCV_RESIZE_PROCESSOR_PARMS_COUNT>
	{
		opencv_resize_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	enum opencv_fill_processor_parm_t
	{
		OPENCV_FILL_PROCESSOR_PARMS_COLOUR = 0,
		OPENCV_FILL_PROCESSOR_PARMS_COUNT
	};

	struct opencv_fill_processor : public processor<opencv_fill_processor, 1, 1, rz::OPENCV_FILL_PROCESSOR_PARMS_COUNT>
	{
		opencv_fill_processor(rz::processor_context &context, int input, int output) :
			processor(context, { { input } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_max_processor : public processor<opencv_max_processor, 2, 1, 0>
	{
		opencv_max_processor(rz::processor_context &context, int input1, int input2, int output) :
			processor(context, { { input1, input2 } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_diff_processor : public processor<opencv_diff_processor, 2, 1, 0>
	{
		opencv_diff_processor(rz::processor_context &context, int input1, int input2, int output) :
			processor(context, { { input1, input2 } }, { { output } }) {}
		virtual void process() override;
	};

	struct opencv_mask_processor : public processor<opencv_mask_processor, 2, 1, 0>
	{
		opencv_mask_processor(rz::processor_context &context, int input1, int input2, int output) :
			processor(context, { { input1, input2 } }, { { output } }) {}
		virtual void process() override;
	};

	enum opencv_cascade_classifier_processor_parms_t
	{
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_SCALE_FACTOR = 0,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MIN_NEIGHBOURS,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MIN_OBJECT_SIZE,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MAX_OBJECT_SIZE,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_COLOUR,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_THICKNESS,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_SHAPE,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_COUNT
	};

	enum opencv_cascade_classifier_processor_mark_type_t
	{
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_MARK_SHAPE_RECTANGLE,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_MARK_SHAPE_ELLIPSE,
		OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_MARK_SHAPE_COUNT
	};

	struct opencv_cascade_classifier_processor : public processor<opencv_cascade_classifier_processor, 1, 1, rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_COUNT>
    {
        rz::cascade_classifier m_classifier;

        opencv_cascade_classifier_processor(rz::processor_context &context, int input, int output) :
                processor(context, {{ input }}, {{ output }})
        {
			auto cascade = "C:/SDK/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
            m_classifier.load_cascade(cascade); // hack crz
        }

        virtual void process() override;
    };
}