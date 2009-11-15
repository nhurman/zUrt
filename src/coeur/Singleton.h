#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<typename T> class Singleton
{
	public:
		T *instance()
		{
			static T *instance = new T;
			return instance;
		}
};

/* Utilisation
class uneClasse : public Singleton<uneClasse>
{};
*/

#endif
