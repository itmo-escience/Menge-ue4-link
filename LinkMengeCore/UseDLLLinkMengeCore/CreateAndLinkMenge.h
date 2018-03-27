#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <stdio.h>

#ifdef MENGEEXPORT
#define LINKMENGE_API __declspec(dllexport)
#else
#define LINKMENGE_API __declspec( dllimport )
#endif // MENGEEXPORT_API


	struct agentInfo
	{
		bool running;
		int agentNumber;
		float* pos;
		float* vel;
		float* velnew;
		float* orient;
	};

	namespace Menge
	{
		namespace Agents
		{
			class SimulatorInterface;
		}
	}
	namespace Menge
	{
		class SimulatorDB;
	}
	namespace Menge
	{
		class ProjectSpec;
	}

	class LINKMENGE_API MengeManager {
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

	private:
#pragma warning(push)
#pragma warning(disable: 4251)

		/*namespace Menge
		{
			class SimulatorDB;
			class ProjectSpec;
			namespace Agents
			{
				class SimulatorInterface;
			}
		}*/
		Menge::SimulatorDB simDB;
		Menge::ProjectSpec projSpec;
		Menge::Agents::SimulatorInterface* sim;

#pragma warning(pop)
	public:

		MengeManager();
		~MengeManager();

		bool LoadMengeProject(const char* path);

		bool StartMenge(const char * pluginPath);

		int GetAgentCount();

		agentInfo* GetPositionAgents();

		bool SetGoalAgent(const char* idState, size_t idGoal);
	};
