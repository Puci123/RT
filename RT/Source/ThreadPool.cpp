#include "ThreadPool.h"
#include "DebugUtilty.h"

#include <iostream>

ThreadPool::ThreadPool(int32_t numOfWorkers) 
	: m_ThreadCount(1)
{
	ASSERT(numOfWorkers <= std::thread::hardware_concurrency()); // TO MANY WORKERS
	ASSERT(numOfWorkers  >  0);									//Must be greater than 0

	m_ThreadCount = numOfWorkers;
	
	
	m_WorkerState.resize(m_ThreadCount);
	
}

ThreadPool::~ThreadPool()
{
    
    Terminate();
}

void ThreadPool::Start()
{
    m_ShuldTerminate = false;

    std::cout << "Thread pool started (" << m_ThreadCount << " threads)" << std::endl;
    m_Workers.resize(m_ThreadCount);

	for (int32_t i = 0; i < m_ThreadCount; i++)
	{
		m_Workers[i] = std::thread(&ThreadPool::ThreadLoop, this,i);
	}

    m_Started = true;
}

void ThreadPool::Terminate()
{
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_ShuldTerminate = true;
    }

    m_MutexCond.notify_all();

    for (int i = 0; i < m_ThreadCount; i++)
    {
        m_Workers[i].join();
        m_WorkerState[i] = WorkerState::Joblles;
    }


    m_Workers.clear();
    m_Started = false;

    std::cout << "Thread pool terminated all threads (" << m_ThreadCount << ")" << std::endl;

}

void ThreadPool::Wait()
{
    while (Working())
    {
    }
    
    Terminate();
}

void ThreadPool::QueueJob(const std::function<void()>& job)
{
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_Jobs.push(job);
    }


    m_MutexCond.notify_one();
}

void ThreadPool::SetThreadCount(int32_t count)
{
    ASSERT(count <= std::thread::hardware_concurrency()); // TO MANY WORKERS
    ASSERT(count > 0);									//Must be greater than 0

    m_ThreadCount = (count);
    m_WorkerState.resize(m_ThreadCount);

}

bool ThreadPool::Working()
{

    if (!m_Started) return false;

    for (int i = 0; i < m_ThreadCount; i++)
    {
        if (m_WorkerState[i] == WorkerState::Working) return true;
    }

    return false;
}

void ThreadPool::ThreadLoop(int id)
{
    while (true) 
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_MutexCond.wait(lock, [this]
                {
                    return !m_Jobs.empty() || m_ShuldTerminate;
                });

            if (m_ShuldTerminate) 
            {
                return;
            }

            m_WorkerState[id] = WorkerState::Working;
            job = m_Jobs.front();
            m_Jobs.pop();
        }

        job();
        m_WorkerState[id] = WorkerState::Done;

    }
}
