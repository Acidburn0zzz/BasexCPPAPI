/*
 : Copyright (c) 2014-2015 Jean-Marc Mercier, www.crimere.com
 : Licensed under the Apache License, Version 2.0 (the "License");
 : you may not use this file except in compliance with the License.
 : You may obtain a copy of the License at
 :
 :     http://www.apache.org/licenses/LICENSE-2.0
 :
 : Unless required by applicable law or agreed to in writing, software
 : distributed under the License is distributed on an "AS IS" BASIS,
 : WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 : See the License for the specific language governing permissions and
 : limitations under the License.
*/
#include "stdafx.h"
using namespace std;
using namespace BaseXClient;

struct my_int_list : std::list<int>
{};

struct my_int_list_interface : public BaseXInterface<my_int_list>
{
	typedef BaseXInterface<my_int_list> base_type;
	virtual ~my_int_list_interface(){};

	my_int_list_interface(const std::string& DBHOST, const std::string& DBPORT, const std::string& DBUSER,const std::string& DBPASSWD)  : base_type(DBHOST,DBPORT,DBUSER,DBPASSWD) {};
	virtual type get(){
		type my_int_list_;
		pugi::xml_parse_result parse_;
		pugi::xml_document doc;
		std::string results = session().execute("XQUERY <list>{for $i in 1 to 10 return <i>{$i}</i>}</list>");
		parse_ = doc.load(results.c_str());

		std::cout << "Load XML Input File : " << parse_.description() << std::endl;

		pugi::xpath_node_set is = doc.select_nodes("/list/i");
		for (pugi::xpath_node_set::const_iterator it = is.begin(); it != is.end(); ++it)
		{
			my_int_list_.push_back(it->node().text().as_int());
		};

		return my_int_list_;
	};
};


int main() {
	cout << "Hello World!!!" << endl; // prints !!!Hello World!!!
	::test_pugixml();
	return 0;
}


int test_pugixml()
{
	cout << "----------test_pugi--------------- "<< endl;
	std::string DBHOST("127.0.0.1");
	std::string DBPORT("1984");
	std::string DBUSER("admin");
	std::string DBPASSWD("admin");
    my_int_list_interface list_interface(DBHOST,DBPORT,DBUSER,DBPASSWD);
	my_int_list list_ = list_interface.get();
	BOOST_FOREACH(int i, list_) {
		cout << "value : "<< i << endl;
	};

    return 0;
};

