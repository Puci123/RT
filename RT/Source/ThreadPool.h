#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>

class ThreadPool
{
	public:
		ThreadPool(int32_t numOfWorkers = std::thread::hardware_concurrency());
		

		~ThreadPool();

		void Start();
		void Terminate();
		void Wait();
		void QueueJob(const std::function<void()>& job);
		void SetThreadCount(int32_t count);


		bool Working();
		inline int32_t GetWokrersCount() const { return m_ThreadCount; }

		enum class WorkerState
		{
			Joblles = 0,
			Working = 1,
			Done    = 2
		};

	private:
		int32_t m_ThreadCount;
		
		std::vector<std::thread> m_Workers;
		std::vector<WorkerState> m_WorkerState;
		std::queue<std::function<void()>> m_Jobs;
		
		std::mutex m_QueueMutex;
		std::condition_variable m_MutexCond;

		bool m_ShuldTerminate = false;
		bool m_Started = false;

		void ThreadLoop(int id);
};

