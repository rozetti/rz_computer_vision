#pragma once

#include <memory>
#include <vector>
#include "processor.h"

namespace rz
{
    class processors
    {
        typedef std::vector<std::unique_ptr<rz::processor_base>> processors_t;
        processors_t m_processors;

    public:

		rz::processor_base &add(std::unique_ptr<rz::processor_base> processor);
        rz::processor_base *get(rz::processor_base::id_type id) const; 

		void process();
    };
}
