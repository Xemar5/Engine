#include "Player.h"

std::vector<std::shared_ptr<Player>> Player::players;
std::shared_ptr<Player> Player::me = nullptr;

std::shared_ptr<Player> Player::Add(unsigned device)
{
	if (device != -1)
	{
		for (auto p : players)
			if (p->_device == device) return p;
	}
	players.push_back(std::make_shared<Player>());
	players.back()->SetDevice(device);
	if (!me) me = players.back();
	return players.back();
}

controlls::Input & Player::GetInput(std::string input_name)
{
	if (_device == -1 || _mapping.size() <= 1) return controlls::undefined;
	for (auto it = _mapping.begin(); it != _mapping.end(); ++it)
		if (it->first == input_name) return it->second;
	return controlls::undefined;
}

void Player::SetDevice(unsigned device)
{
	if (_device != device)
	{
		_device = device;
		_mapping = controlls::Mapping::CreateInputs(device);
	}
}
