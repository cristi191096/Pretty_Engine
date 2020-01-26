#pragma once


namespace PrettyEngine
{
	struct ProfileResult
	{
		const char* name;
		float time;
	};

	class Profiler 
	{
	public:
		Profiler(const char* name, std::vector<ProfileResult>* results);
		~Profiler();

		void Stop();

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
		std::vector<ProfileResult>* m_Results;
		bool m_Finished;
	};
}