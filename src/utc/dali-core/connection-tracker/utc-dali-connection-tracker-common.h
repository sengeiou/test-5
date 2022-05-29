#ifndef _UTC_DALI_CONNECTION_TRACKER_COMMON_H_
#define _UTC_DALI_CONNECTION_TRACKER_COMMON_H_

#include <exception>

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "CONNECTION_TRACKER_UTC"

class TestCallBackFunction
{
  public:
    TestCallBackFunction(){}

    static void CallBack()
    {

    }
};

class ConnectionTrackerSlotObserver : public SlotObserver
{
  public:
    ConnectionTrackerSlotObserver()
    {
    }

    virtual ~ConnectionTrackerSlotObserver()
    {
    }

    virtual void SlotDisconnected( CallbackBase *callback )
    {
    }
};

class TestConnectionTrackerInterface : public ConnectionTrackerInterface
{
  public:

    TestConnectionTrackerInterface(){}
    ~TestConnectionTrackerInterface(){}
    void SignalConnected( SlotObserver* pSlotObserver, CallbackBase* pCallBack )
    {
      int* pnConnection = new int();
      *pnConnection = 0;
      m_vecnConnections.push_back( pnConnection );
    }

    void SignalDisconnected( SlotObserver* signal, CallbackBase* pCallBack )
    {
      std::size_t size = m_vecnConnections.size();

      for( std::size_t i = 0; i< size; ++i )
      {
        int* pnCconnection = m_vecnConnections[i];
        m_vecnConnections.erase( m_vecnConnections.begin()+i );
        delete pnCconnection;
      }
    }

    std::size_t GetConnectionCount() const
    {
      return m_vecnConnections.size();
    }

  private:
    vector< int* >  m_vecnConnections;
};

extern ConnectionTrackerSlotObserver* gConnectionTrackerSlotObserver;
extern CallbackFunction* gConnectionTrackerCallBack;
enum EConnectionCount { SingleConnection = 1, NoConnection = 0 };

//Reset all resources
void ConnectionTrackerReset();

#endif  //_UTC_DALI_CONNECTION_TRACKER_COMMON_H_
