#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class FileHandler;

class DayHandler
{
public:
	DayHandler(const std::string inputDir, const std::string outputDir);
	void HandleDay(const int day);
	int getCurrentDay() const;
private:
	struct TupleHash {
		template <class T1, class T2, class T3>
		std::size_t operator () (const std::tuple<T1, T2, T3>& p) const {
			auto h1 = std::hash<T1>{}(std::get<0>(p));
			auto h2 = std::hash<T2>{}(std::get<1>(p));
			auto h3 = std::hash<T3>{}(std::get<2>(p));

			return h1 ^ h2 ^ h3;
		}
	};

	struct Instruction {
		char type;
		std::vector<std::string> arguments;
	};

	struct Brick {
		int id;
		std::pair<int, int> x;
		std::pair<int, int> y;
		std::pair<int, int> z;
		int xSize() const { return x.second - x.first + 1; }
		int ySize() const { return y.second - y.first + 1; }
		int zSize() const { return z.second - z.first + 1; }
		std::vector<int> supportedBy = {};
		std::vector<int> supports = {};
		std::vector<std::tuple<int, int, int>> getBottomCoordinates() const
		{
			std::vector<std::tuple<int, int, int>> coordinates;
			for (int i = x.first; i <= x.second; i++)
				for (int j = y.first; j <= y.second; j++)
					coordinates.push_back(std::make_tuple(i, j, z.first));
			return coordinates;
		}
		std::vector<std::tuple<int, int, int>> getTopCoordinates() const
		{
			std::vector<std::tuple<int, int, int>> coordinates;
			for (int i = x.first; i <= x.second; i++)
				for (int j = y.first; j <= y.second; j++)
					coordinates.push_back(std::make_tuple(i, j, z.second + 1));
			return coordinates;
		}
		std::vector<std::tuple<int, int, int>> getCoordinates() const
		{
			std::vector<std::tuple<int, int, int>> coordinates;
			for (int i = x.first; i <= x.second; i++)
				for (int j = y.first; j <= y.second; j++)
					for (int k = z.first; k <= z.second; k++)
						coordinates.push_back(std::make_tuple(i, j, k));
			return coordinates;
		}
		bool moveDown()
		{
			if (z.first <= 1)
				return false;
			z.first--;
			z.second--;
			return true;
		}
	};

	struct pair_hash {
		template <class T1, class T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const {
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);

			// Mainly for demonstration purposes, i.e. works but is overly simple
			// In the real world, use sth like boost.hash_combine
			return h1 ^ h2;
		}
	};

	struct HailStone {
		long double x, y, z, vx, vy, vz;
		HailStone(std::vector<long double> tab) : x(tab[0]), y(tab[1]), z(tab[2]), vx(tab[3]), vy(tab[4]), vz(tab[5]) {}

		bool WillIntersect2D(const HailStone& other, const long double& min, const long double& max) const
		{
			if (vx == other.vx && vy == other.vy)
				return (x == other.x && y == other.y); // Linie s¹ identyczne, sprawdzamy, czy siê nak³adaj¹
			else
			{
				long double t = (vx * (other.y - y) + vy * (x - other.x)) / (other.vx * vy - other.vy * vx);
				long double u = (other.x + t * other.vx - x) / vx;
				long double x1 = x + vx * u;
				long double y1 = y + vy * u;
				if (x1 < min || x1 > max || y1 < min || y1 > max)
					return false;
				return (t >= 0 && u >= 0);
			}
		}
	};

	std::vector<Brick> bricks;
	std::unordered_map<std::tuple<long long, long long, long long>, long long, TupleHash> RP;
	// private variables
	int currentDay;
	std::vector<void (DayHandler::*)(FileHandler&)> dayFunctions;
	std::vector<std::string> dayNames;
	FileHandler* fileHandler;

	// Main day functions
	void Day1(FileHandler& fileHandler);
	void Day2(FileHandler& fileHandler);
	void Day3(FileHandler& fileHandler);
	void Day4(FileHandler& fileHandler);
	void Day5(FileHandler& fileHandler);
	void Day6(FileHandler& fileHandler);
	void Day7(FileHandler& fileHandler);
	void Day8(FileHandler& fileHandler);
	void Day9(FileHandler& fileHandler);
	void Day10(FileHandler& fileHandler);
	void Day11(FileHandler& fileHandler);
	void Day12(FileHandler& fileHandler);
	void Day13(FileHandler& fileHandler);
	void Day14(FileHandler& fileHandler);
	void Day15(FileHandler& fileHandler);
	void Day16(FileHandler& fileHandler);
	void Day17(FileHandler& fileHandler);
	void Day18(FileHandler& fileHandler);
	void Day19(FileHandler& fileHandler);
	void Day20(FileHandler& fileHandler);
	void Day21(FileHandler& fileHandler);
	void Day22(FileHandler& fileHandler);
	void Day23(FileHandler& fileHandler);
	void Day24(FileHandler& fileHandler);

	// Additional day functions
	std::vector<std::pair<long long, long long>> Day5ApplyRange(const std::vector<std::pair<long long, long long>> tab, const std::vector<std::vector<long long>> mapping) const;
	int Day7GetType(const std::string type, const bool activeJokers = false) const;
	bool Day10HandlePipe(std::pair<int, int>* previousLocation, std::pair<int, int>* currentLocation, const std::vector<std::string> map) const;
	long long Day12CountOccurencies(const std::string& conditionReport, const std::vector<int>& damagedGroups, long long i = 0, long long gi = 0, long long current = 0);
	void Day16DrawMap(std::vector<std::string>& map, const std::vector<std::string> tab, int x = 0, int y = 0, int dx = 1, int dy = 0);
	char Day19HandleInstructions(const std::unordered_map<std::string, std::vector<Instruction>>& worklows, const std::unordered_map<std::string, int>& part);
	std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> >Day19GetAllRanges(const std::unordered_map<std::string, std::vector<Instruction>>& workflows, std::vector<Instruction> currentInstruction, std::unordered_map<std::string, int> min, std::unordered_map<std::string, int> max);
	std::pair<long long, long long> Day20CountPulses(const std::unordered_map<std::string, std::pair<std::vector<std::string>, char>>& moduleConfiguration, std::unordered_map<std::string, bool> flipFlopPulses, std::unordered_map<std::string, std::unordered_map<std::string, bool>> conjuctionPulses, const long long& buttonRepeats = 1000, const bool& part2 = false);
	void Day22PrintMap(const std::vector<Brick>& bricks, std::string filename = "Day22Map.txt") const;
	int Day22GenerateChainReaction(const std::vector<Brick>& bricks, int currentBrick, std::vector<int>& fallen);
	std::vector<std::vector<std::pair<int, int>>> Day23GetAllPaths(const std::vector<std::string>& map, const std::pair<int, int>& start, const std::pair<int, int>& end, const bool canClimbSlopes = false, std::vector<std::pair<int, int>> currentPath = {});
	void Day23MaxPathsSteps(const std::vector<std::string>& map, const std::pair<int, int>& start, const std::pair<int, int>& end, long long& maxSteps, const bool canClimbSlopes = false, std::unordered_set<std::pair<int, int>, pair_hash> currentPath = {});
};