/*
: Copyright (c) 2015-2017 Jean-Marc Mercier, www.crimere.com
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
#include "md5.c"
#include "pugi/src/pugixml.cpp"

typedef std::list<int> type_list;

struct my_int_list_interface : public XML_BaseXInterface<>
{
	virtual ~my_int_list_interface(){};

	virtual type_list get(){
		type_list my_int_list_;
		std::string results = execute("XQUERY <list>{for $i in 1 to 10 return <i>{$i}</i>}</list>");
		std::cout << "Result: " << results << std::endl;
		load_string(results.c_str());
		my_int_list_ = get_list<int>("/list/i");
		return my_int_list_;
	};
};


int test()
{
	std::cout << "----------test_pugi--------------- "<< std::endl;
    my_int_list_interface list_interface;
	type_list list_ = list_interface.get();
	BOOST_FOREACH(int i, list_) {
		std::cout << "value : "<< i << std::endl;
	};

    return 0;
};

int main() {
	::test();
	return 0;
};
