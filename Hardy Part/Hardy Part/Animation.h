#pragma once
#include <memory>
#include <vector>
#include <map>
class Entity;
class Texture;
class Sprite;

//*** Class with only static members; use them to get frames
class Animation
{
public:
	//*** Adds an animation to an existing texture
	//*** Select it's unique name and number and order of each frame
	//*** If the name is already taken, this function will replace it instead of making new
	static Animation* Add(Texture* texture, std::string name, std::string frame_sequence, bool repeat = false);
	//*** Adds an animation to an existing texture in a given entity
	//*** Select it's unique name and number and order of each frame
	//*** If the name is already taken, this function will replace it instead of making new
	//*** - ent - pointer to an entity; must be supplied; otherwise use the other Animation::Add function
	static Animation* Add(Entity* ent, std::string name, std::string frame_sequence, bool repeat = false);
	//*** Returns pointer if animation with given name exists in supplied sprite
	static Animation* Exists(Texture* sprite, std::string name);
	//*** Returns the sequence of frames in given animation
	static std::vector<unsigned> Get_Sequence(Texture* sprite, std::string name);
	//*** Returns the name of this animation
	std::string Get_Name();

	//*** Returns current frame based on the Sequence Iterator form Sprite
	unsigned Get_Current_Frame(unsigned sequence_iterator);
	//*** Sets the current frame of a Sprite to the given value
	//*** Can't set the frame to a number greater than the number of frames
	static bool Set_Frame(Entity* ent, unsigned frame);
	//*** Sets the frame to the next one in the frame sequence
	static unsigned Next_Frame(Entity* ent);




	//*** Sets the currently playing animation to the given one
	//*** Does nothing if given animation is already playing
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	static Animation* Play(Entity* ent, std::string name = "idle");
	//*** Sets the currently playing animation to the given one
	//*** Does nothing if given animation is already playing
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	static Animation* Play(Sprite* sprite, std::string name = "idle");

	//*** Sets the currently playing animation to the given one
	//*** Does nothing if an animation is being played
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	static Animation* Soft_Play(Entity* ent, std::string name = "idle");
	//*** Sets the currently playing animation to the given one
	//*** Does nothing if an animation is being played
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	static Animation* Soft_Play(Sprite* sprite, std::string name = "idle");

	//*** Sets the currently playing animation to the given one
	//*** Stops the current animaiton and forces the given one
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	static Animation* Force_Play(Entity* ent, std::string name = "idle");
	//*** Sets the currently playing animation to the given one
	//*** Stops the current animaiton and forces the given one
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	static Animation* Force_Play(Sprite* sprite, std::string name = "idle");

	//*** Sets the currently playing animation nullptr
	//*** Does nothing if given animation is not being played
	//*** Leave blank if terminate any currently playing animation
	static bool Terminate(Entity* ent, std::string name = "");
	//*** Sets the currently playing animation nullptr
	//*** Does nothing if given animation is not being played
	//*** Leave blank if terminate any currently playing animation
	static bool Terminate(Sprite* sprite, std::string name = "");



	//*** Decodes the given code into a vector of unsigned ints
	//*** Code details:
	//*** 0x5    ==  frame 0 will be played 5 times
	//*** 3-6    ==  the sequence will be 3, 4, 5, 6
	//*** 2-6x3  ==  2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6
	//*** 2x3-6  == same as above, but not recomended - for clarity
	//*** You can add new segment fragments by placing space between them:
	//*** 3-6 2x2 3 9-4x5
	//*** If size of the new vector == 0, adds frame '0' to it
	static std::vector<unsigned> Decode(std::string code);
private:
	//*** helps Animation::Decode function
	static std::vector<unsigned> __Decode_Segment(std::string code);
	//*** If true, the animation will start again after it finishes
	bool __Repeat = false;
	//*** The name of this animation
	std::string __Name;
	//*** The Sequence of frames in this animation
	std::vector<unsigned> __Frame_Sequence;
};