#ifndef RESOURCE_H
#define RESOURCE_H

template <class T>
class Resource
{
public:
	//template <class T>
	Resource();
    Resource(T* res);
    template<typename... ARGS>
    Resource(ARGS... args);
	
	//template <class T>
	Resource(const Resource<T>& res);
	
	//template <class T>
	virtual ~Resource();
	
	//template <class T>
	T* getResource() const;	
	int getCount() const;
	
	//template <class T>
	T* operator->() const;
	Resource<T>& operator=(const Resource<T>& res);

private:
	void decrement();

	T* _resource;
	int* _count;
};

template <class T>
Resource<T>::Resource() {
	_resource = nullptr;
	_count = new int;
	*_count = 1;
}

template <class T>
Resource<T>::Resource(T* res) {
	_resource = res;
	_count = new int;
	*_count = 1;
}

template <class T>
template<typename... ARGS>
Resource<T>::Resource(ARGS... args) {
    _resource = new T(args...);
    _count = new int;
    *_count = 1;
}

template <class T>
Resource<T>::Resource(const Resource<T>& res) {
	_resource = res.getResource();
	_count = res._count;
	(*_count)++;
}

template <class T>
Resource<T>::~Resource() {
	decrement();
}	

template <class T>
T* Resource<T>::getResource() const {
	return _resource;
}

template <class T>
int Resource<T>::getCount() const {
	return *_count;
}
	
template <class T>
T* Resource<T>::operator->() const {
	return _resource;
}

template <class T>
void Resource<T>::decrement() {
	(*_count)--;
	
	//cleanup if we are the last reference
	if (*_count == 0) {
		if (_resource != nullptr)
			delete _resource;
		delete _count;
	}
}

template <class T>
Resource<T>& Resource<T>::operator=(const Resource<T>& res) {
	//only copy if our resource and his resource are not identical, else used data might be deleted
	if (_resource != res._resource) {			
		//else do our decrement routine
		decrement();
		
		//now copy the values
		_resource = res._resource;
		_count = res._count;
		
		(*_count)++;
	}
	
	return *this;
}

#endif // RESOURCE_H
