// Closest pair problem.cpp : Defines the entry Point2D for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include <Error.h>

struct Point2D
{
public:
	double m_x, m_y;

	double dist(const Point2D &b) const
	{
		return std::sqrt(std::pow(m_x - b.m_x, 2) + std::pow(m_y - b.m_y, 2));
	}
};
using Points = std::vector<Point2D>;

struct Pair
{
public:
	Point2D s_a, s_b;
	double s_dis;

	constexpr operator double() const { return s_dis; }
	constexpr bool operator<(const Pair &b) const { return s_dis < b.s_dis; }
};

class PointManip
{
public:
	PointManip() = delete;
	PointManip(const PointManip &) = delete;
	PointManip(PointManip &&) = delete;

	static Pair closest(Points &v)
	{
		std::sort(v.begin(), v.end(), [](const Point2D &a, const Point2D &b) constexpr { return (a.m_x == b.m_x) ? (a.m_y < b.m_y) : (a.m_x < b.m_x); });
		return closestDiv(v);
	}

	static Pair closestBruteForce(const Points &v, Pair min = { 0, 0, 0, 0, HUGE_VAL })
	{
		for (auto it1 = v.begin(); it1 != v.end(); it1++)
			for (auto it2 = it1 + 1; it2 != v.end() && std::abs(it2->m_y - it1->m_y) < static_cast<double>(min); it2++)
			{
				double dist = it1->dist(*it2);
				if (dist < min)
					min = { *it1, *it2, std::move(dist) };
			}
		return min;
	}

private:
	static Pair closestDiv(const Points &v)
	{
		if (v.size() <= 3)
			return closestBruteForce(v);

		size_t mid = v.size() / 2;

		const Pair dl = closestDiv(Points(v.begin(), v.begin() + mid));
		const Pair dr = closestDiv(Points(v.begin() + mid, v.end()));
		const Pair d = std::min(dl, dr);

		Points strip;
		const Point2D &midPoint = v[mid];

		for (auto p : v)
			if (std::abs(midPoint.m_x - p.m_x) < static_cast<double>(d))
				strip.push_back(std::move(p));

		std::sort(strip.begin(), strip.end(), [](const Point2D &a, const Point2D &b) constexpr { return (a.m_y == b.m_y) ? (a.m_x < b.m_x) : (a.m_y < b.m_y); });
		return std::min(d, closestBruteForce(strip, d));
	}
};


int main()
{
	Points v({ { 0.5, 3 }, { 1, 0.5 }, { 2, 2 }, { 3, 3 }, { 3.5, 1 }, { 3.5, 3 } });

	const double ret = PointManip::closest(v);
	if (ret == HUGE_VAL)
		return -1;

	std::cout << ret << std::endl;


	getchar();
	return 0;
}