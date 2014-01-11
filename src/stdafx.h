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

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include "BaseXInterface.h"
#include "BasexClient.h"
#include "BasexExample.h"


// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme
int test_pugixml();
