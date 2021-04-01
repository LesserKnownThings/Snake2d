#pragma once
#include <chrono>



	struct Timer
	{
		std::chrono::steady_clock::time_point TimeStart = std::chrono::steady_clock::now();

		long long ElapsedMils() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - TimeStart).count();
		}
	};


