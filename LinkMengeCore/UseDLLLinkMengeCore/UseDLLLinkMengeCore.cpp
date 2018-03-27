// UseDLLLinkMengeCore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <iostream>

#include "C:\Users\102-Lebin\Documents\Lebin\Project\TutorialLinkingDllUE4\LinkMengeCore\LinkMengeCore\CreateAndLinkMenge.h"



int main()
{
	MengeManager manager = MengeManager();

	const char* pathProj = "C:\\Users\\102-Lebin\\Documents\\Lebin\\Menge-master\\examples\\plugin\\fundDiag.xml";

	manager.LoadMengeProject(pathProj);

#if _DEBUG
	const char* pathProjPL = "C:\\Users\\102-Lebin\\Documents\\Lebin\\Menge-master\\Exe\\plugins\\debug";
#else
	const char* pathProjPL = "C:\\Users\\102-Lebin\\Documents\\Lebin\\Menge-master\\Exe\\plugins";
#endif

	manager.StartMenge(pathProjPL);


	int count = manager.GetAgentCount();
	
	
    return 0;
}

