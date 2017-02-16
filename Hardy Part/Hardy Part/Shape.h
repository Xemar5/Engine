#pragma once

#include "Texture.h"
#include <boost\any.hpp>

class Shape : public Texture
{
public:
	using ShapeFunction = std::function<bool(std::shared_ptr<Entity> ent, std::shared_ptr<Shape> texture, double parent_x, double parent_y, double parent_scale, double parent_rotation)>;
	std::vector<boost::any> values;
	ShapeFunction drawing_function;

	static std::shared_ptr<Texture> Load(std::shared_ptr<Entity> ent, ShapeFunction foo)
	{
		ent->texture = std::make_shared<Shape>();
		std::dynamic_pointer_cast<Shape>(ent->texture)->drawing_function = foo;
		return ent->texture;
	}
	template <typename... Args>
	static void SetValues(std::shared_ptr<Entity> ent, Args&&... args)
	{
		std::shared_ptr<Shape> s = ent ? ent->texture ? std::dynamic_pointer_cast<Shape>(ent->texture) : nullptr : nullptr;
		if (s)
		{
			s->values.push_back(std::forward<Args>(args)...);
		}
	}

	bool Draw(std::shared_ptr<Entity> ent, double parent_x, double parent_y, double parent_scale, double parent_rotation) override
	{
		return drawing_function ? drawing_function(ent, std::dynamic_pointer_cast<Shape>(ent->texture), parent_x, parent_y, parent_scale, parent_rotation) : false;
	}

};