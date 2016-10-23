#include "stdafx.h"

#include <iostream>

#include "processor_factory.h"
#include "processors.h"

enum mat_id_t
{
	MAT_BGRA_FRAME = 0,
	MAT_GREYSCALE,
	MAT_CONTRAST,
	MAT_CARTOON,
	MAT_FACE_MASK,
	MAT_FACE,
	MAT_BIG_FACE,
	MAT_OUTLINE,
	MAT_BGRA_CARTOON_FACE,
	MAT_BGRA_FACE_MASK,
	MAT_BGRA_FINAL,
	MAT_TEMP1,
	MAT_TEMP2,
	MAT_TEMP3,
	MAT_COUNT
};

rz::processor_context context(MAT_COUNT);
rz::processors processors;
rz::processor_factory factory(context);

static void construct_graph(rz::processor_context &context, rz::processors &processors)
{
	processors.add(factory.create_opencv_greyscale_processor(MAT_BGRA_FRAME, MAT_TEMP1));

	processors.add(factory.create_opencv_brightness_constrast_processor(MAT_TEMP1, MAT_TEMP2))
		.set_parameter(rz::OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_BRIGHTNESS, 0)
		.set_parameter(rz::OPENCV_BRIGHTNESS_CONTRAST_PROCCESSOR_PARMS_CONTRAST, 50);
	processors.add(factory.create_opencv_blur_processor(MAT_TEMP2, MAT_TEMP2))
		.set_parameter(rz::OPENCV_BLUR_PROCCESSOR_PARMS_KERNEL_SIZE, 3);
	processors.add(factory.create_opencv_canny_processor(MAT_TEMP2, MAT_OUTLINE));

	processors.add(factory.create_opencv_resize_processor(MAT_TEMP1, MAT_GREYSCALE))
		.set_parameter(rz::OPENCV_RESIZE_PROCESSOR_PARMS_SCALE_PERCENT, 25);

	processors.add(factory.create_opencv_equalise_histogram_processor(MAT_GREYSCALE, MAT_GREYSCALE));

	processors.add(factory.create_opencv_fill_processor(MAT_GREYSCALE, MAT_FACE_MASK))
		.set_parameter(rz::OPENCV_FILL_PROCESSOR_PARMS_COLOUR, 0);

	processors.add(factory.create_opencv_face_detector_processor(MAT_GREYSCALE, MAT_FACE_MASK))
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_SCALE_FACTOR, 110)
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MIN_NEIGHBOURS, 2)
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MIN_OBJECT_SIZE, 30)
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MAX_OBJECT_SIZE, 10000)
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_COLOUR, 255)
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_THICKNESS, 0)
		.set_parameter(rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_PARMS_MARK_SHAPE, rz::OPENCV_CASCADE_CLASSIFIER_PROCCESSOR_MARK_SHAPE_ELLIPSE);
	processors.add(factory.create_opencv_greyscale_to_bgra_processor(MAT_FACE_MASK, MAT_BGRA_FACE_MASK));
	processors.add(factory.create_opencv_extract_processor(MAT_BGRA_FACE_MASK));

	processors.add(factory.create_opencv_fill_processor(MAT_FACE_MASK, MAT_FACE))
		.set_parameter(rz::OPENCV_FILL_PROCESSOR_PARMS_COLOUR, 0);
	processors.add(factory.create_opencv_laplacian_processor(MAT_GREYSCALE, MAT_CARTOON));

	processors.add(factory.create_opencv_mask_processor(MAT_CARTOON, MAT_FACE_MASK, MAT_FACE));

	processors.add(factory.create_opencv_greyscale_to_bgra_processor(MAT_FACE, MAT_BGRA_CARTOON_FACE));
	processors.add(factory.create_opencv_extract_processor(MAT_BGRA_CARTOON_FACE));

	processors.add(factory.create_opencv_resize_processor(MAT_FACE, MAT_BIG_FACE))
		.set_parameter(rz::OPENCV_RESIZE_PROCESSOR_PARMS_SCALE_PERCENT, 400);
	processors.add(factory.create_opencv_max_processor(MAT_TEMP1, MAT_OUTLINE, MAT_TEMP2));
	processors.add(factory.create_opencv_max_processor(MAT_BIG_FACE, MAT_TEMP2, MAT_TEMP2));

	processors.add(factory.create_opencv_greyscale_to_bgra_processor(MAT_TEMP2, MAT_BGRA_FINAL));
	processors.add(factory.create_opencv_extract_processor(MAT_BGRA_FINAL));
}

int main(int argc, const char** argv)
{
	construct_graph(context, processors);

	cv::VideoCapture camera;

	if (!camera.open(0))
	{
		std::cout << "camera fail" << std::endl;
		return 1;
	}

	while(1)
	{
		camera >> context.mat(MAT_BGRA_FRAME);
		if (context.mat(MAT_BGRA_FRAME).empty()) break;

		auto t0 = (double)cvGetTickCount();
		processors.process();
		auto t1 = (double)cvGetTickCount();

		auto dt = (t1 - t0) / ((double)cvGetTickFrequency() * 1000.0);
		std::cout << dt << std::endl;

		imshow("Cartoon Face", context.mat(MAT_BGRA_CARTOON_FACE));
		imshow("Face Mask", context.mat(MAT_BGRA_FACE_MASK));
		imshow("Final Image", context.mat(MAT_BGRA_FINAL));

		if (cv::waitKey(10) == 27) break;
	}

	return 0;
}
