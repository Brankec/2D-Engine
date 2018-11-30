#pragma once

#include <iostream>

class Resource
{
public:
	Resource();
	virtual ~Resource();

	virtual void loadResource() = 0;
	virtual void unloadResource() = 0;

	void setResourceId(unsigned id);
	unsigned getResourceId() const;

	void setResourcePath(const std::string& path);
	std::string getResourcePath() const;

protected:
	unsigned mResourceId;
	std::string mResourcePath;

};