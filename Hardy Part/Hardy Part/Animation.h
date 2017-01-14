#pragma once
#include <memory>
#include <vector>
#include <map>

template <typename T>
class Pointer;
class Texture;
class Sprite;





//*** Class with only static members; use them to get frames
class Animation
{
public:
	//*** Creates and initializes an animation with given parameters
	//*** - name - the name of an animation
	//*** - frame_sequence - a string of all frames this animation contains (see Animation::Decode)
	//*** - repeat - if true, this animation will repeat until interuption
	Animation(std::string name, std::string frame_sequence, bool repeat = false) : __Name(name), __Repeat(repeat) { __Frame_Sequence = Decode(frame_sequence); };
	//*** Returns the sequence of frames in given animation
	std::vector<unsigned> Sequence() const { return __Frame_Sequence; };
	//*** Returns the name of this animation
	std::string Name() const { return __Name; };
	//*** Returns true if repeats
	bool Repeats() const { return __Repeat; };

	//*** Returns current frame based on the Sequence Iterator form Sprite
	int Current_Frame();
	//*** Sets the frame to the next one in the frame sequence
	int Next_Frame();




	//*** Sets the currently playing animation to the given one
	//*** Does nothing if given animation is already playing
	bool Play();

	//*** Sets the currently playing animation to the given one
	//*** Does nothing if an animation is being played
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	bool Soft_Play();

	//*** Sets the currently playing animation to the given one
	//*** Stops the current animaiton and forces the given one
	//*** If no name supplied or animation doesn't exist, frame 0 will be played
	bool Force_Play();

	//*** Sets the currently playing animation nullptr
	//*** Does nothing if given animation is not being played
	//*** Leave blank if terminate any currently playing animation
	bool Terminate();



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
	//*** Iterates through the __Frame_Sequence
	int __Iterator = -1;

	//*** If true, the animation will start again after it finishes
	bool __Repeat = false;
	//*** The name of this animation
	std::string __Name;
	//*** The Sequence of frames in this animation
	std::vector<unsigned> __Frame_Sequence;
	//*** The Sprite this Animation is given to
	std::shared_ptr<Sprite> __User = nullptr;


	//*** helps Animation::Decode function
	static std::vector<unsigned> __Decode_Segment(std::string code);


	friend class Sprite;
};
