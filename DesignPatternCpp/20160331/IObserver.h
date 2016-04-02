//#pragma once	// C11에서 공식 표준으로 채택되었습니다.	g++에서도 지원합니다. 표준은 아님
				// MS에서 자신들의 기능을 C11은 표준에 넣어

#ifndef IOSBERVER_H
#define IOSBERVER_H

// IObserver.h 로 이동해야 합니다.
struct IObserver
{
	virtual void onUpdate(void* data) = 0;
	virtual ~IObserver() {}
};


#endif