///////////////////////////////////////////////////////////////////////////////
// Filename: cpuclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _CPUCLASS_H_
#define _CPUCLASS_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "pdh.lib")


//////////////
// INCLUDES //
//////////////
#include <pdh.h>


///////////////////////////////////////////////////////////////////////////////
// Class name: CpuClass
///////////////////////////////////////////////////////////////////////////////
class CpuClass
{
public:

	static CpuClass& GetInstance()
	{
		static CpuClass instance;
		return instance;
	}

	void Initialize();
	void Shutdown();
	void Frame();
	int GetCpuPercentage();

private:
	CpuClass();
	~CpuClass();
	CpuClass(const CpuClass&) = delete;
	CpuClass& operator=(const CpuClass&) = delete;




	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
};

#endif