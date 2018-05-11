#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>
#include <vector>
#include <map>

class TeamData {
 public:
	explicit TeamData(std::string filename);
	int numPlayers() const;
 	//double winPercentages(int i, int j) const { return winPercentages_[i][j]; }
	std::map<int, std::map<int, double>>winPercentages_;

private:

	int numPlayers_;

};  // class TeamData

#endif  // _TEAMDATA_H_