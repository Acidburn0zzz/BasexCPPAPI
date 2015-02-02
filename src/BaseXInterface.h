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
#pragma once

#include "BaseXClient.h"
#include "XMLInterface.h"

using namespace BaseXClient;

template <class dummy = double> // template mandatory ... bug boost::asio ??
class BaseXInterface
{
public :
	BaseXSession& session(){return BaseXSession_;};
	BaseXInterface(const BaseXSession& BaseXSession) : BaseXSession_(BaseXSession) {};
	BaseXInterface(const std::string& DBHOST, const std::string& DBPORT, const std::string& DBUSER,const std::string& DBPASSWD) : BaseXSession_(DBHOST,DBPORT,DBUSER,DBPASSWD) {};
	BaseXInterface() : BaseXSession_("127.0.0.1","1984","admin","admin") {};
	std::string execute(const std::string& query){return session().execute(query);}

protected :
	BaseXSession BaseXSession_;
};
template <class dummy = double>
class XML_BaseXInterface : public XML_Interface, public BaseXInterface<>
{
	typedef BaseXInterface<> base_type;
public :
	XML_BaseXInterface(){};
	XML_BaseXInterface(const BaseXSession& BaseXSession) : base_type(BaseXSession) {};
	XML_BaseXInterface(const std::string& DBHOST, const std::string& DBPORT, const std::string& DBUSER,const std::string& DBPASSWD) : base_type(DBHOST,DBPORT,DBUSER,DBPASSWD) {};
};


