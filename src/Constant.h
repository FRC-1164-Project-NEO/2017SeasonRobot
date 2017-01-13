#ifndef SRC_CONSTANT_H_
#define SRC_CONSTANT_H_
#include <string>
#include <unordered_map>
using namespace std;

class Constant {
private:
	unordered_map<string,double> map;
public:
	Constant();
	void reloadFile();

	double Get(string constantsName);
};

#endif /* SRC_CONSTANT_H_ */
