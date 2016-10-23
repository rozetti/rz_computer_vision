#pragma once

#include <stdint.h>
#include <memory>
#include <array>
#include <assert.h>
#include "processor_context.h"
#include "cascade_classifier.h"

enum filter_type_t
{
    Greyscale,
    Canny,
    Otsu,
    Face,
    Laplacian,
    Box,
    ScharrX,
    ScharrY,
    ScharrQuad,
    ScharrMax,
    SobelX,
    SobelY,
    SobelQuad,
    SobelMax,
    Sobel,
    Chrominance,
    RenderScriptHighPass,
    RenderScriptLowPass,
    RenderScriptBandPass,
    RenderScriptBandStop
};

enum parameter_type_t
{
    INVALID,
    BLUR_KERNEL_SIZE,
    CONTRAST,
    BRIGHTNESS,
    SOBEL_KERNEL_SIZE,
    CANNY_THRESHOLD1,
    CANNY_THRESHOLD2,
    CANNY_KERNEL_SIZE,
    OTSU_THRESHOLD,
    OTSU_MAX,
    PARAMETER_COUNT
};

namespace cv
{
    class Mat;
}

namespace rz
{
    class processor_context;

	class processor_base
	{
		friend class processors;

	public:
		typedef int id_type;

	private:
		id_type m_id;

		void set_id(int id) { m_id = id; }

	protected:
		rz::processor_context &m_context;

	public:
		processor_base(rz::processor_context &context) :
			m_context(context)
		{
		}

		virtual void process() = 0;

		int get_id() const { return m_id; }

		virtual int get_parameter(int parameter) const = 0;
		virtual rz::processor_base &set_parameter(int parameter, int value) = 0;
	};

    template <class TProcessor, int NInput = 1, int NOutput = 1, int NParms = 1>
    class processor : public processor_base
    {
    protected:

        std::array<int, NInput> m_inputMatId;
        std::array<int, NOutput> m_outputMatId;
        std::array<int, NParms> m_parameters;

        processor(rz::processor_context &context,
                  std::array<int, NInput> inputs,
                  std::array<int, NOutput> outputs) :
			processor_base(context),
            m_inputMatId(inputs),
            m_outputMatId(outputs)
        {
            for(int &i : m_parameters) i = 0;
        }

    public:
        virtual ~processor() {}

        int get_first_input() const { return m_inputMatId[0]; }
		int get_second_input() const { return m_inputMatId[1]; }
		int get_first_output() const { return m_outputMatId[0]; }
	
		int get_parameter(int parameter) const override
		{

			return m_parameters[parameter];
		}

		rz::processor_base &set_parameter(int parameter, int value) override
		{
			m_parameters[parameter] = value;

			return *this;
		}
	};
}



