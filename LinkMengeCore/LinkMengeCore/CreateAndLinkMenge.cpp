#include <MengeCore/Agents/SimulatorInterface.h>
#include <MengeCore/Agents/BaseAgent.h>
#include <MengeCore/Math/RandGenerator.h>
#include "MengeCore/PluginEngine/CorePluginEngine.h"
#include "MengeCore/ProjectSpec.h"
#include "MengeCore/Runtime/Logger.h"
#include "MengeCore/Runtime/os.h"
#include "MengeCore/Runtime/SimulatorDB.h"
#include "MengeCore/Math/Vector2.h"

#include "MengeCore/CoreConfig.h"
#include "MengeCore/MengeException.h"
#include "MengeCore/Agents/AgentInitializer.h"
#include "MengeCore/BFSM/FSM.h"
#include "MengeCore/BFSM/FSMDescrip.h"

#include "MengeCore/BFSM/FSMDescrip.h"

#include "MengeCore/Core.h"
#include "MengeCore/Agents/BaseAgent.h"
#include "MengeCore/Agents/Elevations/Elevation.h"
#include "MengeCore/Agents/Events/Event.h"
#include "MengeCore/Agents/Events/EventException.h"
#include "MengeCore/Agents/Events/EventSystem.h"
#include "MengeCore/Agents/SimulatorInterface.h"
#include "MengeCore/Agents/SimulatorState.h"
#include "MengeCore/Agents/SpatialQueries/SpatialQuery.h"
#include "MengeCore/BFSM/FSM.h"
#include "MengeCore/BFSM/fsmCommon.h"
#include "MengeCore/BFSM/State.h"
#include "MengeCore/BFSM/GoalSelectors/GoalSelector.h"
#include "MengeCore/BFSM/GoalSelectors/GoalSelectorIdentity.h"
#include "MengeCore/BFSM/GoalSelectors/GoalSelectorShared.h"
#include "MengeCore/BFSM/Transitions/Transition.h"
#include "MengeCore/BFSM/VelocityComponents/VelCompConst.h"
#include "MengeCore/resources/NavMesh.h"
#include "MengeCore/BFSM/FSMDescrip.h"
#include "MengeCore/BFSM/fsmCommon.h"
#include "MengeCore/BFSM/StateDescrip.h"
#include "MengeCore/resources/ResourceManager.h"
#include "MengeCore/resources/VectorField.h"
#include "MengeCore/Runtime/Logger.h"
#include "MengeCore/Runtime/os.h"

#include "MengeCore/resources/ResourceManager.h"

#include "MengeCore/BFSM/GoalSet.h"
#include "MengeCore/BFSM/GoalSelectors/GoalSelectorExplicit.h"


#include "thirdParty/tclap/CmdLine.h"

#include "CreateAndLinkMenge.h"


MengeManager::MengeManager()
{
	
}


MengeManager::~MengeManager()
{
	if (!isDisposed) {
		if (simDB != nullptr) {
			delete simDB;
			simDB = nullptr;
		}

		if (projSpec != nullptr) {
			delete projSpec;
			projSpec = nullptr;
		}

		if (sim != nullptr) {
			delete sim;
			sim = nullptr;
		}

		Menge::ResourceManager::forceCleanup();
	
		isDisposed = true;
	}
}


bool MengeManager::LoadMengeProject(const char * path)
{
	if (path != NULL)
	{
		pathProject = path;
		return true;
	}
	return false;
}

//Exported method that invertes a given boolean.
bool MengeManager::StartMenge(const char * pluginPath)
{
	simDB = new Menge::SimulatorDB();
	projSpec = new Menge::ProjectSpec();

	Menge::PluginEngine::CorePluginEngine* plugins = new Menge::PluginEngine::CorePluginEngine(simDB);
	std::string pl = pluginPath;
	plugins->loadPlugins(pl);
	int  d = simDB->modelCount();
	if (d == 0) 
	{
		return bool(false);
	}
	// Read the project file
	std::string projName = pathProject;
	if (projName != "") 
	{
		if (!projSpec->loadFromXML(projName))
		{
			return bool(false);
		}
	}
	if (!projSpec->fullySpecified()) {
		return bool(false);
	}
	
	VERBOSE = projSpec->getVerbosity();
	TIME_STEP = projSpec->getTimeStep();
	SUB_STEPS = projSpec->getSubSteps();
	SIM_DURATION = projSpec->getDuration();
	std::string dumpPath = projSpec->getDumpPath();
	Menge::Math::setDefaultGeneratorSeed(projSpec->getRandomSeed());
	std::string outFile = projSpec->getOutputName();
	
	std::string viewCfgFile = projSpec->getView();
	bool useVis = viewCfgFile != "";
	std::string model(projSpec->getModel());
	
	Menge::SimulatorDBEntry * simDBEntry = simDB->getDBEntry(model);
	if (simDBEntry == 0x0) {
		return bool(false);
	}

	delete plugins;
	
	sim = simDBEntry->getSimulator(agentCount, TIME_STEP, SUB_STEPS,
		SIM_DURATION, projSpec->getBehavior(), projSpec->getScene(), outFile,
		projSpec->getSCBVersion(), VERBOSE);
	if (sim == nullptr)
	{
		return bool(false);
	}
	return bool(true);
}

int MengeManager::GetAgentCount()
{
	return agentCount;
}

void MengeManager::GetPositionAgents(agentInfo* agentsPos)
{
	agentsPos[0].running = false;
	float* modifiedVector3 = new float[3];
	bool running = true;
	Menge::Agents::BaseAgent* a;
	running = sim->step();
	printf("\n");
	if(running)
	{
		for (int i = 0; i < agentCount; i++)
		{
			a = sim->getAgent(i);
			Menge::Math::Vector2 ac = a->_pos;
			Menge::Math::Vector2 av = a->_vel;
			Menge::Math::Vector2 avn = a->_velNew;
			Menge::Math::Vector2 ao = a->_orient;
			agentsPos[i].running = true;
			agentsPos[i].agentNumber = i;
			agentsPos[i].pos = new float[2];
			agentsPos[i].pos[0] = ac.x();
			agentsPos[i].pos[1] = ac.y();
			agentsPos[i].vel = new float[2];
			agentsPos[i].vel[0] = av.x();
			agentsPos[i].vel[1] = av.y();
			agentsPos[i].velnew = new float[2];
			agentsPos[i].velnew[0] = avn.x();
			agentsPos[i].velnew[1] = avn.y();
			agentsPos[i].orient = new float[2];
			agentsPos[i].orient[0] = ao.x();
			agentsPos[i].orient[1] = ao.y();
		}
		running = false;
	}
}

bool MengeManager::SetGoalAgent(const char * idState, size_t idGoal)
{
	sim->getNumAgents();
	Menge::BFSM::FSM* fsm = sim->getBFSM();
	Menge::BFSM::GoalSet* t = fsm->getGoalSet(0);
	std::string bufer = idState;
	Menge::BFSM::State* states = fsm->getNode(bufer);
	auto goalsel = states->getGoalSelector();
	
	auto test = dynamic_cast<Menge::BFSM::ExplicitGoalSelector*>(goalsel);
	
	if (test == nullptr) {
		return false;		
	}
		
	auto y = t->getGoalByID(idGoal);
	test->setGoalID((size_t)y);
	return true;
}
