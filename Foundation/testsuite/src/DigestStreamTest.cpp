//
// DigestStreamTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/DigestStreamTest.cpp#1 $

//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "DigestStreamTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"
#include <sstream>


using Poco::DigestInputStream;
using Poco::DigestOutputStream;
using Poco::DigestEngine;
using Poco::MD5Engine;


DigestStreamTest::DigestStreamTest(const std::string& name): CppUnit::TestCase(name)
{
}


DigestStreamTest::~DigestStreamTest()
{
}


void DigestStreamTest::testInputStream()
{
	std::istringstream istr("abcdefghijklmnopqrstuvwxyz");
	MD5Engine md5;
	DigestInputStream ds(md5, istr);
	std::string s;
	ds >> s;
	assert (DigestEngine::digestToHex(md5.digest()) == "c3fcd3d76192e4007dfb496cca67e13b");
	assert (s == "abcdefghijklmnopqrstuvwxyz");
}


void DigestStreamTest::testOutputStream1()
{
	MD5Engine md5;
	DigestOutputStream ds(md5);
	ds << "abcdefghijklmnopqrstuvwxyz";
	ds.close();
	assert (DigestEngine::digestToHex(md5.digest()) == "c3fcd3d76192e4007dfb496cca67e13b");

	ds << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	ds << "abcdefghijklmnopqrstuvwxyz0123456789";
	ds.close();
	assert (DigestEngine::digestToHex(md5.digest()) == "d174ab98d277d9f5a5611c2c9f419d9f");
}


void DigestStreamTest::testOutputStream2()
{
	MD5Engine md5;
	std::ostringstream ostr;
	DigestOutputStream ds(md5, ostr);
	ds << "abcdefghijklmnopqrstuvwxyz";
	ds.close();
	assert (DigestEngine::digestToHex(md5.digest()) == "c3fcd3d76192e4007dfb496cca67e13b");
	assert (ostr.str() == "abcdefghijklmnopqrstuvwxyz");
}


void DigestStreamTest::testToFromHex()
{
	std::string digest("c3fcd3d76192e4007dfb496cca67e13b");
	Poco::DigestEngine::Digest dig = DigestEngine::digestFromHex(digest);
	std::string digest2 = DigestEngine::digestToHex(dig);
	assert (digest == digest2);
}


void DigestStreamTest::setUp()
{
}


void DigestStreamTest::tearDown()
{
}


CppUnit::Test* DigestStreamTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DigestStreamTest");

	CppUnit_addTest(pSuite, DigestStreamTest, testInputStream);
	CppUnit_addTest(pSuite, DigestStreamTest, testOutputStream1);
	CppUnit_addTest(pSuite, DigestStreamTest, testOutputStream2);
	CppUnit_addTest(pSuite, DigestStreamTest, testToFromHex);
	
	return pSuite;
}
