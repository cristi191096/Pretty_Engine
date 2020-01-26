#include "pepch.h"
#include "Profiler.h"

namespace PrettyEngine
{

	Profiler::Profiler(const char * name,  std::vector<ProfileResult>* results)
		: m_Name(name), m_Results(results), m_Finished(false)
	{
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}
	Profiler::~Profiler()
	{
		if (!m_Finished)
			Stop();
	}

	void Profiler::Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		float duration = (end - start) * 0.001f;

		m_Results->push_back({ m_Name, duration });

		m_Finished = true;
	}
}