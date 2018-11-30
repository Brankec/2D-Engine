#pragma once

#include <map>
#include "Resource.h"
#include "../Util/Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	//virtual ~ResourceManager();

	void addResource(Resource* resource, const std::string& name, const std::string& path);

	template <typename T>
	T* getResource(const std::string& name) {
		return dynamic_cast<T*>(mResources.find(name)->second);
	}

	static ResourceManager& getInstance();
	//static ResourceManager* getInstancePtr();

private:
	std::map<std::string, Resource*> mResources;

};