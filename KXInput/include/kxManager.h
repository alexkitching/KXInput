#ifndef __KXMANAGER_H__
#define __KXMANAGER_H__


class KXManager
{
public:
	~KXManager() = default;

	virtual void Update() = 0;

protected:
	KXManager() = default;
	KXManager(bool a_bool) :
	testBool(a_bool)
	{
		
	}

private:
	bool testBool;

};

#endif
