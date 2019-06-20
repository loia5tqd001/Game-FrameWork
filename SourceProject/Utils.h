#pragma once

struct Utils
{
	template<typename T>
	static void Clamp(T& toClamp, T low, T high)
	{
		         assert(low  < high);
		     if (toClamp < low ) toClamp = low ;
		else if (toClamp > high) toClamp = high;
	}

	template<typename T, typename Functor>
	static void Clamp(T& toClamp, T low, T high, Functor action)
	{
		         assert(low  < high);
		     if (toClamp < low ) toClamp = low , action();
		else if (toClamp > high) toClamp = high, action();
	}

	template<typename T, typename Pred>
	static void RemoveIf(std::vector<T>& container, Pred remove_condition)
	{
		auto newEnd = std::remove_if(container.begin(), container.end(), remove_condition);
		container.erase(newEnd, container.end());
	}

	template<typename T, typename Pred>
	static void RemoveIf(std::unordered_set<T>& container, Pred remove_condition) 
	{
		for (auto it = container.begin(), end = container.end(); it != end; ) 
		{
			if (remove_condition(*it)) it = container.erase(it);
			else                       it++;
		}
	}
};
