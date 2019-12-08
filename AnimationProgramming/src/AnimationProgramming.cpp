#include <Engine/Engine.h>
#include <Animation/Animation.h>

int main()
{
	try
	{
		CSimulation simulation;
		Run(&simulation, 1400, 800);
	}
	catch (const std::exception& p_exception)
	{
		std::cerr << p_exception.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

