#pragma once
#include "engine\Core\Core.h"




namespace PrettyEngine {


	class PE_API NetworkContext {

	public:

		static void Create();

		inline static NetworkContext* Get() { return s_Instance; }

		void Update();

		void Destroy() const;

	private:
		static NetworkContext* s_Instance;
		NetworkContext();
		~NetworkContext();

	
	};
}
