#pragma once

#include <string>
#include <map>


using namespace std;

typedef void * (*ReflectClass)(void);

class ReflectManager
{
private:
	map<string, ReflectClass> m_ReflectClasses;
	ReflectManager() {}
public:
	static ReflectManager * Get()
	{
		static ReflectManager _m;
		return &_m;
	}
	
	void * GetClassByName(string _className)
	{
		map<string, ReflectClass>::iterator iter = m_ReflectClasses.find(_className);
		if (iter == m_ReflectClasses.end())
		{
			return nullptr;
		}
		return iter->second();
	}
	void RegisterClass(string _className, ReflectClass method)
	{
		m_ReflectClasses.insert(std::pair<string, ReflectClass>(_className, method));
	}
};
class RegisterAction
{
public:
	RegisterAction(string _className, ReflectClass _method)
	{
		ReflectManager::Get()->RegisterClass(_className, _method);
	}
};

//TestC * CreateTestC(void)
//{
//	return new TestC();
//}
//RegisterAction ra("TestC", (ReflectClass)CreateTestC);

#define G_REGISTER_CLASS(ClassName) \
ClassName * _Create##ClassName(void) \
{ \
 return new ClassName(); \
} \
RegisterAction m_RegisterAction##ClassName(#ClassName,(ReflectClass)_Create##ClassName);