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
#include "pugi\src\pugixml.hpp"
#include <boost/filesystem.hpp>
#include <string>

const char* node_types[] ={"null", "document", "element", "pcdata", "cdata", "comment", "pi", "declaration"};
struct simple_walker: pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node)
    {
        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation
        std::cout << node_types[node.type()] << ": name='" << node.name() << "', value='" << node.value() << "'\n";
        return true; // continue traversal
    }
};

struct XML_Interface {
	template<class T>	T						as(const pugi::xpath_node & node)						{return std::exception("not implemented");};
	template<>			double					as<double>(const pugi::xpath_node & node)				{return node.node().text().as_double();};
	template<>			int						as<int>(const pugi::xpath_node & node)					{return node.node().text().as_uint();};
	template<>			std::string				as<std::string>(const pugi::xpath_node & node)			{return node.node().text().as_string();};
	template<class T>	T						get(const std::string & xpath)							{return std::exception("not implemented");};
	template<>			pugi::xpath_node		get<pugi::xpath_node>(const std::string & xpath)		{return doc_.select_single_node(xpath.c_str());};
	template<>			pugi::xpath_node_set	get<pugi::xpath_node_set>(const std::string & xpath)	{return doc_.select_nodes(xpath.c_str());};
	template<>			std::size_t				get<std::size_t>(const std::string & xpath)				{return get<pugi::xpath_node>(xpath).node().text().as_uint();};
	template<>			double					get<double>(const std::string & xpath)					{return get<pugi::xpath_node>(xpath).node().text().as_double();};

	template<class T>	std::list<T>			get_list(const std::string & xpath)			{
		std::list<T> returned;
		for (const pugi::xpath_node &node : get<pugi::xpath_node_set>(xpath) ) {returned.push_back(as<T>(node));};
		return returned;
	};

	void load_string(const char* xml)
	{		
		pugi::xml_parse_result parse_;
		parse_ = doc_.load(xml);
		if (parse_)
			std::cout << "XML parsed without errors" << std::endl;
		else
		{
			std::cout << "XML parsed with errors: [" << std::endl;
			std::cout << "Error description: " << parse_.description() << std::endl;
		}
	}

	void load_file(const std::string& file) 
	{	
		assert(boost::filesystem::exists(file));
		pugi::xml_parse_result parse_;
		parse_ = doc_.load_file(file.c_str());
		std::cout << "config file " << file << "] size " << boost::filesystem::file_size(file) << std::endl;
		if (parse_)
			std::cout << "XML [" << file << "] parsed without errors" << std::endl;
		else
		{
			std::cout << "XML [" << file << "] parsed with errors: [" << std::endl;
			std::cout << "Error description: " << parse_.description() << std::endl;
		}

/*		simple_walker walker;
		doc_.traverse(walker);	*/
	};

	pugi::xml_document doc_;
};
