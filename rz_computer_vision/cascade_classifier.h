#pragma once

#include <string>
#include "opencv2/objdetect.hpp"

namespace rz
{
	class cascade_classifier
	{
		cv::CascadeClassifier m_classifier;

		bool m_isOk;
		double m_scaleFactor;
		int m_minNeighbours;
		double m_minObjSize;
		double m_maxObjSize;

	public:

		cascade_classifier() :
			m_isOk(false),
			m_scaleFactor(1.0),
			m_minNeighbours(1),
			m_minObjSize(0.0),
			m_maxObjSize(100000.0)
		{
		}

		void set_scale_factor(double factor) { m_scaleFactor = factor; }
		void set_min_neighbours(int n) { m_minNeighbours = n; }
		void set_min_object_size(double size) { m_minObjSize = size; }
		void set_max_object_size(double size) { m_maxObjSize = size; }

		void load_cascade(std::string const &path);

		void detect(const cv::Mat &Image, std::vector<cv::Rect> &objects);
	};
}