#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Character.h"

class Profile
{
public:
	static bool Load(std::string);
	static std::vector<std::shared_ptr<Profile>> Get_Profiles();
	std::string Name;
	std::string Favourite_Character;
private:
	static std::vector<std::shared_ptr<Profile>> __Profiles;
};