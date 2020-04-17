#pragma once
class job
{
public:
	int index;
	int sum;
	bool operator< (const job& other) const {
		return sum < other.sum;
	}
	
};

