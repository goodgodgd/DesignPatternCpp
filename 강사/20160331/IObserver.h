// IObserver.h
// #pragma once // C11 ���� ���� ǥ������ ä�õǾ����ϴ�. - g++������ �����մϴ�.
#ifndef IOBSERVER_H
#define IOBSERVER_H

struct IObserver
{
  virtual void onUpdate(void* data) = 0;
  virtual ~IObserver() {}
};

#endif
