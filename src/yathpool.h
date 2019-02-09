#ifndef yathpool_H
#define yathpool_H

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <future>
#include <functional>
#include <condition_variable>

namespace MT
{

using Task = std::function<void()>;

class yathpool
{
public:
    yathpool(unsigned int numberOfThreads = std::thread::hardware_concurrency()-1);
    ~yathpool();

    template<typename Function, typename ...Args>
    std::future<typename std::result_of<Function(Args...)>::type> pushTask(Function&& func, Args&&... args)
    {
        using resultType = typename std::result_of<Function(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<resultType()>>(std::bind(std::forward<Function>(func),
                                                                       std::forward<Args>(args)...));

        auto futureResult = task->get_future();

        std::lock_guard<std::mutex> lock(queueMutex_);

        tasks_.emplace(Task( [task] { (*task)(); } ));

        waitCondition_.notify_one();

        return futureResult;
    }

    bool tryToGetTask(Task& t);

private:
    std::mutex threadMutex_;
    std::mutex queueMutex_;
    std::condition_variable waitCondition_;
    std::atomic_bool destroyFlag_;
    std::vector<std::thread> threads_;
    std::queue<Task> tasks_;
};

} //end of namespace MT

#endif // yathpool_H
