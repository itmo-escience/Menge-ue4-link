// UseDLLLinkMengeCore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <iostream>

#include "C:\Users\102-Lebin\Documents\Lebin\Project\TutorialLinkingDllUE4\LinkMengeCore\LinkMengeCore\CreateAndLinkMenge.h"

#pragma comment(lib,"C:\\Users\\102-Lebin\\Documents\\Lebin\\Project\\Menge-ue4-link\\LinkMengeCore\\x64\\Release\\LinkMengeCore.lib")

int main()
{
	MengeManager manager = MengeManager();

	const char* pathProj = "C:\\Users\\102-Lebin\\Documents\\Lebin\\Project\\ExampleCrowd\\NavMeshTest\\Menge\\core\\MengeProj.xml";

	manager.LoadMengeProject(pathProj);

#if _DEBUG
	const char* pathProjPL = "C:\\Users\102-Lebin\\Documents\\Lebin\\Project\\Menge\\Menge-master\\Exe\\plugins\\debug";
#else
	const char* pathProjPL = "C:\\Users\\102-Lebin\\Documents\\Lebin\\Project\\Menge\\Menge-master\\Exe\\plugins";
#endif

	manager.StartMenge(pathProjPL);


	int count = manager.GetAgentCount();
	agentInfo* agent = new agentInfo[count];
	manager.GetPositionAgents(agent);
    return 0;
}

