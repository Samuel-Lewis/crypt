//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-09-30 13:47:25
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#ifndef _LB_STRING_H
#define _LB_STRING_H

#include <vector>
#include <string>

class lbString {
public:
	static std::vector<std::string> split(std::string&, std::string);

	static void remove(std::string&, std::string);

	static void toUpper(std::string&);
	static void toLower(std::string&);

	static void getAlpha(std::string&);
	

private:
	// Stop the initialization of a lbString
	lbString();

};

#endif //_LB_STRING_H
