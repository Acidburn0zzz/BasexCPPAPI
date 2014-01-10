// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

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
#include "../../src/md5.h"

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include "../../src/BaseXInterface.h"
#include "../../src/BasexClient.h"
#include "../../src/BasexExample.h"


// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme
int test_pugixml();



// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme
