#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <stdio.h>

#ifdef LINKMENGECORE_EXPORTS
#define LINKMENGE_API __declspec(dllexport)
#else
#define LINKMENGE_API __declspec( dllimport )
#endif // MENGEEXPORT_API


	struct agentInfo
	{
		bool running;
		int agentNumber;
		float elevation;
		float* pos;
		float* vel;
		float* velnew;
		float* orient;
	};

	namespace  Menge
	{
		namespace Agents
		{
			class SimulatorInterface;
		}
	}
	namespace Menge
	{
		class  SimulatorDB;
	}
	namespace Menge
	{
		class ProjectSpec;
	}



	class MengeManager {
	private:
#pragma warning(push)
#pragma warning(disable: 4251)

		// Time step (in seconds)
		float TIME_STEP = 0.2f;
		// The number of uniform simulation steps to take between logical time steps
		size_t SUB_STEPS = 0;
		// Maximum duration of simulation (in seconds)
		float SIM_DURATION = 800.f;
		// Controls whether the simulation is verbose or not
		bool VERBOSE = false;
		// The location of the executable - for basic executable resources
		std::string ROOT;

		std::string pathProject;

		size_t agentCount;

		bool isDisposed = false;
		
		Menge::SimulatorDB* simDB;
		Menge::ProjectSpec* projSpec;
		Menge::Agents::SimulatorInterface* sim;

#pragma warning(pop)
	public:

		LINKMENGE_API MengeManager();
		LINKMENGE_API ~MengeManager();

		LINKMENGE_API bool LoadMengeProject(const char* path);

		LINKMENGE_API bool StartMenge(const char * pluginPath);

		LINKMENGE_API int GetAgentCount();

		LINKMENGE_API void GetPositionAgents(agentInfo* agentsPos);

		LINKMENGE_API bool SetGoalAgent(size_t idAgent, size_t goalSetId, size_t goalId);

		LINKMENGE_API void TeleportAgent(size_t idAgent, float x, float y);
	};
