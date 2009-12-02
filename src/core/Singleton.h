#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<typename T> class Singleton
{
	public:
		static T *instance()
		{
			static T *instance = new T;
			return instance;
		}
};

/* Usage
class someClass : public Singleton<someClass>
{};
*/

#endif
