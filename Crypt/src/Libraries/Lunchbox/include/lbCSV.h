//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-09-30 13:47:08
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#ifndef _LB_CSV_H
#define _LB_CSV_H

#include <string>
#include <map>
#include <vector>

typedef std::vector<std::map<std::string, std::string> > TABLE;

class lbCSV
{
public:
	static TABLE read(std::string);

private:
	lbCSV();
	~lbCSV();

	static std::vector<std::string> splitLine(std::string);

};

#endif // _LB_CSV_H
