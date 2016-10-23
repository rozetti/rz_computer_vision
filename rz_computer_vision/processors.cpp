#include "processors.h"
#include "processor.h"

#include <assert.h>

rz::processor_base &rz::processors::add(std::unique_ptr<rz::processor_base> processor)
{
    auto id = static_cast<rz::processor_base::id_type>(m_processors.size());

	auto p = processor.get();

    processor->set_id(id);
    m_processors.push_back(std::move(processor));

    return *p;
}

rz::processor_base *rz::processors::get(rz::processor_base::id_type id) const
{
    auto idx = static_cast<processors_t::size_type>(id);

    if (idx >= m_processors.size())
    {
        return nullptr;
    }

    auto p = m_processors[idx].get();

    assert(p->get_id() == id);

    return p;
}

void rz::processors::process()
{
	for (auto &processor : m_processors)
	{
		processor->process();
	}
}
