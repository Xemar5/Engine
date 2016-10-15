#pragma once
#include <map>
#include <SDL.h>
#include "Input.h"
#include <vector>
#include <string>
#include <regex>


std::pair<std::string, Input> operator+(std::string name, const Input& input);

class Mapping
{
public:
	//*** Initializes the Mapping class
	//*** - path - the path to the file where keybinds are stored
	static void Init(std::string path);
	//*** The map containing the default binding with all unassigned keys
	//*** All controllers starts with this binding
	static std::map<std::string, Input> Default_Bindings;

	//*** Reads the string line and converts it to Input and its action name
	//*** If is_action is false, looks for '[ ]' parenthesis and sets their content
	//***	as the name of a new mapping
	//*** if not succeded, dst_str and binding returns as nullptr
	//*** - is_action - if true, given line should contain action name
	//***				and Input values to initialize
	//*** - src_str - the line of string to read
	//*** - dst_str - the string this function writes the action name to
	//*** - binding - the Input this function sets
	static int Read_Line(std::string& src_str, std::string* const dst_str = nullptr, Input* const binding = nullptr);
	//*** Reads the file from given path and saves all recognised action-inputs pairs
	//***	as a map; if no action was read succesfuly, but the name of a map is,
	//***	creates an empty map of this name
	static std::map<std::string, std::map<std::string, Input>> Load_From_File(std::string path);
	//*** Contains all maps of all seen devices
	static std::map<std::string, std::map<std::string, Input>> Maps;
	//*** The default path to the keybinds file
	static std::string Default_Path;

	//*** returns true if this Mapping contains given key
	bool Has_Binding(std::string name) { return (__Map.find(name) == __Map.end() ? false : true); };
	//*** Saves this Mapping with given name to the default file
	bool Save(std::string name);

	Mapping() { __Map = {}; };
	Mapping(std::map<std::string, Input> map);
	Mapping(std::initializer_list<std::pair<std::string const, Input>> list);
	//*** Returns the action of given name from the __Map if it exists
	Input operator[](std::string name) const;
	Mapping& operator=(std::map<std::string, Input> map);
	Mapping& operator<<(std::pair<std::string, Input> input);
	//*** Iterator to the first element of __Map
	std::map<std::string, Input>::const_iterator begin() const { return __Map.begin(); };
	//*** Iterator to the past-the-last element of __Map
	std::map<std::string, Input>::const_iterator end() const { return __Map.end(); };
private:
	//*** The regex to convert mapping line to Input action
	static std::regex __Regex;
	//*** Converts a map of mapping names and Input maps to the program-readable string and writes it to the end of the given file
	//*** - path - the keybinds filepath
	//*** - maps - a map of mapping names and Input maps
	static bool __Save_To_File(const std::string path, const std::map<std::string, std::map<std::string, Input>>& maps);
	//*** A map containing all inputs and their action names this mapping contains
	std::map<std::string, Input> __Map;
};