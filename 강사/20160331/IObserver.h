// IObserver.h
// #pragma once // C11 에서 공식 표준으로 채택되었습니다. - g++에서도 지원합니다.
#ifndef IOBSERVER_H
#define IOBSERVER_H

struct IObserver
{
  virtual void onUpdate(void* data) = 0;
  virtual ~IObserver() {}
};

#endif
