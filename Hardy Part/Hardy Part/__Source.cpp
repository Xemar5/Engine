#include <cctype>
#include "System.h"
#include "MultiplayerState.h"


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		if (std::string(argv[i]) == "-s") { Output_Handler::Output << "MSG main : Started in server mode\n"; Network::connectionType = ConnectionType::CT_Server; }
		if (std::string(argv[i]) == "-c") { Output_Handler::Output << "MSG main : Entering Windowless mode\n"; Screen::ShowWindow = false; }
		if (std::isdigit(argv[i][0])) { Output_Handler::Output << "MSG main : Connecting " << argv[i] << "\n"; Network::toConnect = argv[i]; }
	}
	System::Start<MultiplayerState>();
	return 0;
}