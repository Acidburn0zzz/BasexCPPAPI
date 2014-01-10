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
#include "stdafx.h"

using namespace boost::asio::ip;



namespace BaseXClient
{
	struct BaseXSession{
		std::string DBHOST_;
		std::string DBPORT_;
		std::string DBUSER_;
		std::string DBPASSWD_;
		boost::asio::io_service io_service_;
		tcp::socket socket_;
		char Basex_EO_[1];

		BaseXSession(const std::string& DBHOST, const std::string& DBPORT, const std::string& DBUSER,const std::string& DBPASSWD) : 
			DBHOST_(DBHOST), DBPORT_(DBPORT), DBUSER_(DBUSER), DBPASSWD_(DBPASSWD), socket_(io_service_)
		{
			Basex_EO_[0]=0;
			tcp::resolver resolver(socket_.get_io_service());
			tcp::resolver::query query(DBHOST_, DBPORT_);
			tcp::endpoint remote_endpoint = *resolver.resolve(query);

			socket_.connect(remote_endpoint);
			Send(DBUSER_);
			std::string Pwd = MD5(DBPASSWD_); Pwd += read(); Pwd = MD5(Pwd);
			Send(Pwd);
		};

		virtual ~BaseXSession() { 
			socket_.close();
			io_service_.stop();
		};
		std::string read() {boost::asio::streambuf response; return read(response);};


		std::string read(boost::asio::streambuf & response)
		{
			int debug_size = response.size() ;
			if (debug_size == 0 ) read_buffer(response);
			typedef boost::asio::streambuf::const_buffers_type buffer_type; 
			typedef boost::asio::buffers_iterator<buffer_type> iterator; 

			boost::asio::streambuf::const_buffers_type bufs = response.data();

			std::string line(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + response.size());
			std::string::const_iterator begin_(line.begin());
//			std::cout << line << std::endl;
			std::string returned_line;
			std::size_t size_e = 0;
				for (; size_e < response.size(); ++size_e,++begin_) {
					int debug = (int) *begin_;
					if ((size_e > 0) && debug == 0) {break;} else if (debug != 0) returned_line.push_back(*begin_);
				};
			if (size_e) response.consume(size_e); 
			return returned_line;
		};


		std::string execute(const char* query) {
			Send(query);
			boost::asio::streambuf response;
			std::string next = read(response);
			while (next == "") next = read(response);
			std::string info = read(response);
			return next;

		};



		void read_buffer(boost::asio::streambuf & response)	{
			std::size_t reply_length = boost::asio::read_until(socket_, response, "\0");
		};
 
		void Send(const std::string & msg)
		{
/*			std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
			std::wstring wstring_utf8(convert.from_bytes(msg));
			std::string utf8(convert.to_bytes(wstring_utf8)); */

			boost::system::error_code error;
			std::string utf8(msg);
			utf8.push_back('\0');

			boost::asio::write(socket_, boost::asio::buffer(utf8.data(),utf8.size()));
/*			std::cout << "send -- " << request_ << std::endl;
			for (int i=0;i < utf8.size()+1;++i)
				std::cout << (int) request_[i] << "-";
			std::cout << std::endl; */
		};

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
