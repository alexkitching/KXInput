#ifndef __KXMANAGER_H__
#define __KXMANAGER_H__


class  KXManager
{
public:
	KXManager() = default;
	~KXManager() = default;

	virtual bool Init() = 0;
	virtual void Update() = 0;

protected:


private:
	bool testBool;

};

#endif
