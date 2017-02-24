#pragma once

class Container;

class Object : public virtual std::enable_shared_from_this<Object>
{
public:
	Object() = default;
	virtual ~Object() = default;


	template <typename T, typename... Args>
	static std::shared_ptr<T> Make(Args... args);

	virtual void Destroy();
	static void Destroy(std::shared_ptr<Object> obj) { if(obj) obj->Destroy(); }
	//*** Returns true if this object has been destroyed
	//*** Destroyed objects can't be used or displayed
	bool IsDestroyed() { return is_destroyed; }


	//*** The scale of this entity
	double scale = 1;
	//*** The scale of this entity
	double rotation = 0;

	//*** The x coordinate
	double X = 0;
	//*** The y coordinate
	double Y = 0;
	//*** The z coordinate
	double Z = 0;


	//*** The Container object that this entity belongs to
	std::shared_ptr<Container> parent = nullptr;


	//*** Returns the scale of this entity and all it's parents
	double RootScale();
	//*** Returns the real position of this entity
	std::vector<double> RootPos();


	//*** points to the lastly created Object
	static std::shared_ptr<Object> last_object;

private:
	//*** if true, the object is 
	bool is_destroyed = false;
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> Object::Make(Args ...args)
{
	if (!std::is_base_of<Object, T>())
	{
		Output_Handler::Error << "ERR Object::Make : Cannot instantiate object which does not derive from Object class\n";
		return nullptr;
	}
	std::shared_ptr<T> p = std::make_shared<T>(std::forward<Args>(args)...);
	last_object = std::dynamic_pointer_cast<Object>(p);
	if (std::shared_ptr<Entity> e = std::dynamic_pointer_cast<Entity>(p)) e->Create();
	if (!p->parent) State::CurrentState()->AddChild(0, p);
	return p;
}
