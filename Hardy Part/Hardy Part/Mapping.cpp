#include "Mapping.h"
#include "Input.h"
#include "Player.h"
#include <fstream>
#include <algorithm>
#include <tuple>

namespace controlls
{

	std::tuple<unsigned, unsigned> Mapping::undefined{ 0, 0 };
	std::map<std::string, Mapping::MapType> Mapping::Maps = {};
	std::string Mapping::Default_Path = "";
	std::map<std::string, Input> Mapping::Default_Bindings;
	std::regex Mapping::__Regex = std::regex("([a-zA-Z_][\\w_]*) *= *([a-zA-Z]+)(\\((\\d+)\\))? *(\\d+)|\\[([^\\]\\n]+)\\]");


	void Mapping::Init(std::string path)
	{
		Mapping::Default_Path = path;
		Maps = Load_From_File(Mapping::Default_Path);
	}

	std::string Map_To_String(const Mapping::MapType& map)
	{
		std::string str = "";
		for (auto key : map)
		{
			str += key.first + " = ";
			switch (std::get<0>(key.second))
			{
			case 0: str += "null"; break;
			case 1: str += "button"; break;
			case 2: str += "axis"; break;
			case 3: str += "hat"; break;
			default: break;
			}
			str += " " + std::to_string(std::get<1>(key.second));
			str += '\n';
		}
		if (!str.size()) str += "#No Keybinds Change\n";
		return str;
	}

	bool Mapping::__Save_To_File(const std::string path, const std::map<std::string, MapType>& maps)
	{
		std::ofstream file;
		file.open(path);
		if (!file)
		{
			file.close();
			return false;
		}

		for (auto map : maps)
		{
			file << '[' << map.first << "]\n";
			file << Map_To_String(map.second);
			file << "\n\n";
		}

		return true;
	}

	int Mapping::Read_Line(std::string& src_str, std::string* dst_str, unsigned* action, unsigned* index)
	{
		if (!src_str.size() || !dst_str) return -1;
		auto m = std::cmatch{};
		if (!std::regex_match(src_str.c_str(), m, __Regex)) return -1;

		if (m[1].matched)
		{
			unsigned a, i;// , mod;
			std::string input_name = m[1].str();
			std::string input_type = m[2].str();
			//int input_parameter = m[4].matched ? std::atoi(m[4].str().c_str()) : 0;
			int input_value = std::atoi(m[5].str().c_str());

			if (input_type == "null") a = 0;
			else if (input_type == "axis") a = 2;
			else if (input_type == "button") a = 1;
			else if (input_type == "hat") a = 3;
			else if (input_type == "mousev") a = 2;
			else if (input_type == "mouseh") a = 2;
			else return -1;

			i = input_value;
			//mod = input_parameter;

			*dst_str = input_name;
			*action = a;
			*index = i;
			return 0;

		}
		else if (m[6].matched)
		{
			*dst_str = m[6].str();
			return 1;
		}
		return -1;
	}

	std::map<std::string, Mapping::MapType> Mapping::Load_From_File(std::string path)
	{
		std::ifstream file;
		file.open(path);
		if (!file)
		{
			file.close();
			return{};
		}

		std::map<std::string, MapType> v = {};
		std::string str;
		std::string device_name = "";

		while (std::getline(file, str))
		{
			if (!str.size()) continue;
			std::string name;
			unsigned action = 0;
			unsigned index = 0;
			unsigned modifier = 0;
			auto result = Read_Line(str, &name, &action, &index);

			if (result == 1)
			{
				device_name = name;
				v.insert({ device_name, {} });
			}
			if (result == 0 && v.find(device_name) != v.end())
			{
				v[device_name].insert({ name, {action, index } });
			}
			//if (str[0] == '[' && Read_Line(str, &device_name))
			//	if (v.find(device_name) == v.end()) v.insert({ device_name, {} });
			//if (str[0] < 'a' || str[0] > 'z') continue;
			//
			//std::string action = "UNDEFINED";
			//
			//if (device_name.size() && v.find(device_name) != v.end() && Read_Line(str, &action, &binding))
			//	if (action != "UNDEFINED")
			//		v[device_name].insert({ action, binding });
		}
		return v;
	}

	bool Mapping::Save(std::string name)
	{
		//for (auto it = __Map.begin(); it != __Map.end(); ++it)
		//{
		//	if (it->first == "UNDEFINED") { __Map.erase(it); break; }
		//}
		Mapping::Maps[name] = __Map;
		Mapping::__Save_To_File(Mapping::Default_Path, Mapping::Maps);

		unsigned d = controlls::DeviceByName(name);
		for (auto p : Player::players)
		{
			if (p->device() == d || (p->device() == 2 && d == 1)) p->_mapping = Mapping::CreateInputs(d);
		}

		return true;
	}

	Mapping::MapInputs Mapping::CreateInputs(unsigned device)
	{
		MapInputs input_map;
		std::string device_name;
		switch (device)
		{
		case -1:
		case 0: return MapInputs{}; break;
		case 1:
		case 2: device_name = "Keyboard"; device = 1; break;
		default: device_name = gamepads[device - 3].name(); break;
		}

		for (auto map = Maps.begin(); map != Maps.end(); ++map)
		{
			if (map->first == device_name)
			{
				for (auto& i : map->second)
				{
					input_map.insert({ i.first, controlls::StoreInput(device, std::get<0>(i.second), std::get<1>(i.second)) });
				}
				break;
			}
		}
		return input_map;
	}

	Mapping::Mapping(const MapType map)
	{
		__Map = map;
	}
	Mapping::Mapping(std::initializer_list<MapTypePair> list)
	{
		__Map = list;
	}

	std::tuple<unsigned, unsigned> Mapping::operator[](std::string name) const
	{
		auto it = __Map.find(name);
		if (it != __Map.end()) return it->second;
		return undefined;
	}

	Mapping& Mapping::operator=(const MapType map)
	{
		__Map = map;
		return *this;
	}

	Mapping & Mapping::operator<<(MapTypePair binding)
	{
		auto it = __Map.find(binding.first);
		if (it != __Map.end())
		{
			it->second = binding.second;
			return *this;
		}
		__Map.insert(binding);
		return *this;
	}

	//std::pair<std::string, Input> operator+(std::string name, const Input& input)
	//{
	//	return std::pair<std::string, Input>(name, Input::Set(input.Type(), input.Key()));
	//}

} //namespace controlls

