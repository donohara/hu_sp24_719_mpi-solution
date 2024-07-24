#include <chrono>
#include <iostream>

std::chrono::steady_clock::time_point StartTimer();
long GetDurationInSeconds(std::chrono::steady_clock::time_point start);
long GetDurationInMilliSeconds(std::chrono::steady_clock::time_point start);
long GetDurationInMicroSeconds(std::chrono::steady_clock::time_point start);
long GetDurationInNanoSeconds(std::chrono::steady_clock::time_point start);


inline std::chrono::steady_clock::time_point StartTimer()
{
    return std::chrono::steady_clock::now();
}

inline std::chrono::steady_clock::time_point StopTimer()
{
    return std::chrono::steady_clock::now();
}

inline __int64 GetDurationInSeconds(std::chrono::steady_clock::time_point start, 
                                std::chrono::steady_clock::time_point end)
{
    return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
}

inline __int64 GetDurationInMilliSeconds(std::chrono::steady_clock::time_point start, 
                                std::chrono::steady_clock::time_point end)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

inline __int64 GetDurationInMicroSeconds(std::chrono::steady_clock::time_point start, 
                                std::chrono::steady_clock::time_point end)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

inline __int64 GetDurationInNanoSeconds(std::chrono::steady_clock::time_point start, 
                                std::chrono::steady_clock::time_point end)
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}