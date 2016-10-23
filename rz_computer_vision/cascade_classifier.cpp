#include "cascade_classifier.h"

void rz::cascade_classifier::load_cascade(std::string const &path)
{
    m_isOk = m_classifier.load(path.c_str());
}

void rz::cascade_classifier::detect(cv::Mat const &input, std::vector<cv::Rect> &objects)
{
	m_classifier.detectMultiScale(
		input, 
		objects, 
		m_scaleFactor, 
		m_minNeighbours, 
		cv::CASCADE_SCALE_IMAGE, // todo crz: other flags
		cv::Size(static_cast<int>(m_minObjSize), static_cast<int>(m_minObjSize)),
		cv::Size(static_cast<int>(m_maxObjSize), static_cast<int>(m_maxObjSize)));
}


