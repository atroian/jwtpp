// The MIT License (MIT)
//
// Copyright (c) 2016-2020 Artur Troian
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <gtest/gtest.h>

#include <functional>

#include <jwtpp/jwtpp.hh>

TEST(JosePP, header_decode_valid) {
	EXPECT_NO_THROW(jwtpp::hdr("{\"typ\":\"JWT\",\"alg\":\"RS256\"}"));

	EXPECT_THROW(jwtpp::hdr("{\"typ\":\"Jwt\",\"alg\":\"RS256\"}"), std::exception);
	EXPECT_THROW(jwtpp::hdr("{,\"alg\":\"RS256\"}"), std::exception);
	EXPECT_THROW(jwtpp::hdr("{\"alg\":\"RS256\"}"), std::exception);
	EXPECT_THROW(jwtpp::hdr("{\"alg\":\"BB6\"}"), std::exception);
}

TEST(JosePP, header_decode_invalid_typ) {
	EXPECT_THROW(jwtpp::hdr("{\"typ\":\"Jwt\",\"alg\":\"RS256\"}"), std::exception);
}

TEST(JosePP, header_invalid_json) {
	EXPECT_THROW(jwtpp::hdr("{,\"alg\":\"RS256\"}"), std::exception);
}


TEST(JosePP, header_no_typ) {
	EXPECT_THROW(jwtpp::hdr("{\"alg\":\"RS256\"}"), std::exception);
}

TEST(JosePP, header_no_alg) {
	EXPECT_THROW(jwtpp::hdr("{\"typ\":\"JWT\"}"), std::exception);
}

TEST(JosePP, header_invalid_alg) {
	EXPECT_THROW(jwtpp::hdr("{\"typ\":\"JWT\",\"alg\":\"BBs\"}"), std::exception);
}
