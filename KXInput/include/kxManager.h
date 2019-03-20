#ifndef __KXMANAGER_H__
#define __KXMANAGER_H__

class  KXManager
{
public:
	KXManager() : testBool(false)
	{
		int test = 1;
		++test;
	}
	virtual ~KXManager() = default;

	virtual bool Init() = 0;
	virtual void Update() = 0;

private:
	bool testBool;

};

#endif
