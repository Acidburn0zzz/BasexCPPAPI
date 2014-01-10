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
#pragma once
#include <boost/mpl/assert.hpp>
#include "BaseXClient.h"

using namespace BaseXClient;

template<class structure>
class BaseXInterface{
public :
	typedef structure type;
	BaseXSession& session(){return BaseXSession_;};
	BaseXInterface(const BaseXSession& BaseXSession) : BaseXSession_(BaseXSession) {};
	BaseXInterface(const std::string& DBHOST, const std::string& DBPORT, const std::string& DBUSER,const std::string& DBPASSWD) : BaseXSession_(DBHOST,DBPORT,DBUSER,DBPASSWD) {};
	virtual type get()=0; // must be overloaded
private :
		BaseXSession BaseXSession_;
};

