#pragma once

class Body;

template <typename T = Body>
class Pointer final
{
public:
	//*** Returns the pointer to holded entity
	T* get() const;
	//*** Returns a shared_ptr to holded entity
	std::shared_ptr<T> get_shared() const;
	//*** Returns the use count of stored shared_ptr
	size_t count() const;


	template <typename... Args>
	static Pointer<T> Make(Args... args);




	template <typename N>
	Pointer(std::shared_ptr<N> ent);
	Pointer();
	Pointer(const Pointer& ent);
	Pointer(Body* ent);
	Pointer(std::nullptr_t null);
	~Pointer() = default;

	template<typename N> operator Pointer<N>();
	template<typename N> operator std::shared_ptr<N>();
	operator std::shared_ptr<T>();
	operator bool();

	std::shared_ptr<T>& operator->();
	bool operator==(const Pointer& ent);

	Pointer& operator=(const Pointer& ent);
	Pointer& operator=(std::nullptr_t null);
	Pointer& operator=(Body* ent);
	template<typename N> Pointer& operator=(std::shared_ptr<N> ent);

private:
	std::shared_ptr<T> _ptr = nullptr;

	template<typename N>
	friend class Pointer;
};




template<typename T>					  Pointer<T>::operator bool()
{
	return _ptr ? true : false;
}
template<typename T>					  Pointer<T>::operator std::shared_ptr<T>()
{
	return _ptr;
}
template<typename T> template<typename N> Pointer<T>::operator std::shared_ptr<N>()
{
	return std::dynamic_pointer_cast<N>(_ptr);
}
template<typename T> template<typename N> Pointer<T>::operator Pointer<N>()
{
	return Pointer<N>(std::dynamic_pointer_cast<N>(_ptr));
}

template<typename T> template<typename N> Pointer<T> & Pointer<T>::operator=(std::shared_ptr<N> ent)
{
	_ptr = std::dynamic_pointer_cast<T>(ent);
	return *this;
}
template<typename T>					  Pointer<T> & Pointer<T>::operator=(std::nullptr_t null)
{
	//std::cout << "nullptr asigned Pointer\n";
	_ptr = null;
	return *this;
}
template<typename T>					  Pointer<T> & Pointer<T>::operator=(Body * ent)
{
	_ptr = ent->shared_from_this();
	return *this;
}
template<typename T>					  Pointer<T> & Pointer<T>::operator=(const Pointer<T> & ent)
{
	//std::cout << "asigned Pointer\n";
	_ptr = ent._ptr;
	return *this;
}

template<typename T> std::shared_ptr<T> & Pointer<T>::operator->()
{
	return _ptr;
}
template<typename T> bool Pointer<T>::operator==(const Pointer<T> & ent)
{
	return _ptr == ent._ptr;
}

template<typename T>				T * Pointer<T>::get() const
{
	return _ptr.get();
}
template<typename T> std::shared_ptr<T> Pointer<T>::get_shared() const
{
	return _ptr;
}
template<typename T>			 size_t Pointer<T>::count() const
{
	return _ptr ? _ptr.use_count() : 0;
}

template<typename T>					  Pointer<T>::Pointer()
{
	//std::cout << "default constructed Pointer\n";
	_ptr = nullptr;
}
template<typename T>					  Pointer<T>::Pointer(const Pointer<T> & ent)
{
	//std::cout << "copy constructed Pointer\n";
	_ptr = ent._ptr;
}
template<typename T>					  Pointer<T>::Pointer(Body * ent)
{
	_ptr = ent->shared_from_this();
}
template<typename T>					  Pointer<T>::Pointer(std::nullptr_t null)
{
	//std::cout << "nullptr constructed Pointer\n";
	_ptr = null;
}


template<typename T>
template<typename ...Args> inline Pointer<T> Pointer<T>::Make(Args ...args)
{
	Pointer<T> e = std::make_shared<T>(args...);
	e->Create();
	return e;
}
template<typename T> template<typename N> Pointer<T>::Pointer(std::shared_ptr<N> ent)
{
	_ptr = std::dynamic_pointer_cast<T>(ent);
}
