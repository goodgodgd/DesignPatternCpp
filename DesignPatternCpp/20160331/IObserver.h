//#pragma once	// C11���� ���� ǥ������ ä�õǾ����ϴ�.	g++������ �����մϴ�. ǥ���� �ƴ�
				// MS���� �ڽŵ��� ����� C11�� ǥ�ؿ� �־�

#ifndef IOSBERVER_H
#define IOSBERVER_H

// IObserver.h �� �̵��ؾ� �մϴ�.
struct IObserver
{
	virtual void onUpdate(void* data) = 0;
	virtual ~IObserver() {}
};


#endif