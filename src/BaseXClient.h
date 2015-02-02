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
#include <string>
#include <bitset>
#include <locale>
#include <iostream>
#include <iomanip>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include "md5.h"
#include <stdio.h>

using namespace boost::asio::ip;



namespace BaseXClient
{
	class Query;
	class BaseXSession
	{
	public :
		BaseXSession(const std::string& DBHOST, const std::string& DBPORT, const std::string& DBUSER,const std::string& DBPASSWD) : 
			DBHOST_(DBHOST), DBPORT_(DBPORT), DBUSER_(DBUSER), DBPASSWD_(DBPASSWD), socket_(io_service_)
		{
			Basex_EO_[0]=0;
			std::string BaseXsep(":");
			tcp::resolver resolver(socket_.get_io_service());
			tcp::resolver::query query(DBHOST_, DBPORT_);
			tcp::endpoint remote_endpoint = *resolver.resolve(query);

			typedef boost::tokenizer<boost::char_separator<char> > tokenizer_type;
			boost::char_separator<char> sep(":");


			socket_.connect(remote_endpoint);
			std::string answer(read());
			std::string code(DBUSER_);
			std::string nounce;
			tokenizer_type tokens(answer, sep);

			// bug in boost::tokenizer :(
			std::vector<std::string> tokenize_vector;
			for (auto tok_iter = tokens.begin();tok_iter != tokens.end(); ++tok_iter) 
				tokenize_vector.push_back(*tok_iter);


			if ( tokenize_vector.size() == 1)  
			{code = DBPASSWD_;
			nounce = *(tokenize_vector.begin());}
			else 
			{code += BaseXsep+*tokenize_vector.begin()+BaseXsep+DBPASSWD_;
			nounce = *( tokenize_vector.end()-1);}

			std::string Pwd = MD5(code); Pwd += nounce; Pwd = MD5(Pwd);
			Send(DBUSER_);
			Send(Pwd);
			if (! ok()) throw std::exception("BaseX authentication denied");
		};

		virtual ~BaseXSession() { 
			close();
			if (socket_.is_open()) socket_.close();
			io_service_.stop();
		};
		std::string read() { read_socket(); return read_streambuffer();};
		std::string read(boost::asio::streambuf & response) { read_socket(response); return read_streambuffer(response);};

		int last_character(boost::asio::streambuf & response){
			boost::asio::streambuf::const_buffers_type bufs = response.data();
			return (int) *(boost::asio::buffers_begin(bufs)+response.size()-1);
		};
		bool ok() {	
			read_socket(response_); bool ok = (int) *boost::asio::buffers_begin(response_.data()) == 0; return ok;};

		std::string read_streambuffer(){return read_streambuffer(response_);};
		std::string read_streambuffer(boost::asio::streambuf & response)
		{
//			typedef boost::asio::streambuf::const_buffers_type buffer_type; 
//			typedef boost::asio::buffers_iterator<buffer_type> iterator;
			std::string results;
			boost::system::error_code error;

			boost::asio::streambuf::const_buffers_type bufs = response.data();
//			std::string line(boost::asio::buffers_begin(bufs),boost::asio::buffers_end(bufs));

//			std::cout << "size---" << response.size() << std::endl; //for debug purposes

			std::size_t size(0);
			std::string line;
			auto ptr_b = boost::asio::buffers_begin(bufs);
			for(; ptr_b != boost::asio::buffers_end(bufs); ++ptr_b, ++ size) 
			{if  (*ptr_b != 0) {line.push_back(*ptr_b);} else if (size > 1) break; };


//			if (size == 1) std::cout << "line-int--" << (int) *ptr_b << std::endl; //for debug purposes
//			else std::cout << "line---" << line << std::endl; //for debug purposes
			response.consume(size);
			return line;

		};


		std::string execute(const std::string& query) {
			Send(query);
			boost::asio::streambuf response;
			std::string answer;
			while (! answer.size()) answer = read(response); // very strange bug ...
			info_ = read_streambuffer(response);
			return answer;
		};


		void close(){ Send("exit");	};
		std::string info(){ return info_;	};

		void Send(const std::string & msg)
		{
			boost::asio::write(socket_, boost::asio::buffer( msg+'\0',msg.size()+1));
		};

	private :
		std::size_t read_socket()	{return read_socket(response_);};

		std::size_t read_socket(boost::asio::streambuf & response)	{
			std::size_t size = boost::asio::read_until(socket_, response,'\0');
			return size;
		};

		std::string info_;
		std::string DBHOST_;
		std::string DBPORT_;
		std::string DBUSER_;
		std::string DBPASSWD_;
		boost::asio::io_service io_service_;
		boost::asio::streambuf response_;
		tcp::socket socket_;
		char Basex_EO_[1];


		std::string MD5(std::string & msg){
			unsigned char md[16];
			md5(  reinterpret_cast< unsigned char *> ((char*) msg.c_str()),msg.length(),md);
			std::stringstream ss;
			for (int i=0; i< 16;++i) {
				ss << std::setfill('0') << std::hex << std::setw(2) << (unsigned int) md[i];
			};
			return ss.str(); 
		};



	};
};
