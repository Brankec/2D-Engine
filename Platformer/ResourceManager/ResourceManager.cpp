#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

void ResourceManager::addResource(Resource* resource, const std::string &name, const std::string & path)
{
	resource->setResourcePath(path);
	resource->setResourceId(mResources.size());
	resource->loadResource();

	mResources.insert(std::pair<std::string, Resource*>(name, resource));
}

ResourceManager &ResourceManager::getInstance()
{
	return GetInstance();
}

/*ResourceManager* ResourceManager::getInstancePtr()
{
	return nullptr;
}*/
