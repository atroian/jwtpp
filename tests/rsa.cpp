// The MIT License (MIT)
//
// Copyright (c) 2016 Artur Troian
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

#include <josepp/claims.hpp>
#include <josepp/crypto.hpp>
#include <josepp/jws.hpp>
#include <openssl/err.h>

TEST(JosePP, rsa_gen_invalid_size) {
	jose::sp_rsa_key key;

	EXPECT_THROW(key = jose::rsa::gen(1023), std::exception);
}

TEST(JosePP, create_close_rsa_crypto) {
	jose::sp_rsa_key key;

	EXPECT_NO_THROW(key = jose::rsa::gen(1024));

	EXPECT_NO_THROW(std::make_shared<jose::rsa>(jose::alg::RS256, key));
	EXPECT_NO_THROW(std::make_shared<jose::rsa>(jose::alg::RS384, key));
	EXPECT_NO_THROW(std::make_shared<jose::rsa>(jose::alg::RS512, key));

	EXPECT_THROW(std::make_shared<jose::rsa>(jose::alg::HS256, key), std::exception);
	EXPECT_THROW(std::make_shared<jose::rsa>(jose::alg::ES384, key), std::exception);
}

TEST(JosePP, sign_verify_rsa256) {
	jose::claims cl;

	jose::sp_rsa_key key;
	jose::sp_rsa_key pubkey;
	jose::sp_crypto r256;
	jose::sp_crypto r256_pub;
	jose::sp_crypto r384;
	jose::sp_crypto r384_pub;
	jose::sp_crypto r512;
	jose::sp_crypto r512_pub;

	EXPECT_NO_THROW(key = jose::rsa::gen(1024));
	EXPECT_NO_THROW(pubkey = jose::sp_rsa_key(RSAPublicKey_dup(key.get()), ::RSA_free));
	EXPECT_NO_THROW(r256 = std::make_shared<jose::rsa>(jose::alg::RS256, key));
	EXPECT_NO_THROW(r256_pub = std::make_shared<jose::rsa>(jose::alg::RS256, pubkey));
	EXPECT_NO_THROW(r384 = std::make_shared<jose::rsa>(jose::alg::RS384, key));
	EXPECT_NO_THROW(r384_pub = std::make_shared<jose::rsa>(jose::alg::RS384, pubkey));
	EXPECT_NO_THROW(r512 = std::make_shared<jose::rsa>(jose::alg::RS512, key));
	EXPECT_NO_THROW(r512_pub = std::make_shared<jose::rsa>(jose::alg::RS512, pubkey));

	std::string bearer = jose::jws::sign_bearer(cl, r256);

	jose::sp_jws jws;

	EXPECT_NO_THROW(jws = jose::jws::parse(bearer));

	EXPECT_TRUE(jws->verify(r256_pub));

	auto vf = [](jose::sp_claims cl) {
		return !cl->check().iss("troian");
	};

	EXPECT_TRUE(jws->verify(r256_pub, vf));
	EXPECT_THROW(jws->verify(r384_pub, vf), std::exception);
	EXPECT_THROW(jws->verify(r512_pub, vf), std::exception);

	bearer = "ghdfgddf";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);

	bearer = "Bearer ";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);

	bearer = "Bearer bla.bla.bla";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);
}

TEST(JosePP, sign_verify_rsa384) {
	jose::claims cl;

	jose::sp_rsa_key key;
	jose::sp_rsa_key pubkey;
	jose::sp_crypto r256;
	jose::sp_crypto r256_pub;
	jose::sp_crypto r384;
	jose::sp_crypto r384_pub;
	jose::sp_crypto r512;
	jose::sp_crypto r512_pub;

	EXPECT_NO_THROW(key = jose::rsa::gen(1024));
	EXPECT_NO_THROW(pubkey = jose::sp_rsa_key(RSAPublicKey_dup(key.get()), ::RSA_free));
	EXPECT_NO_THROW(r256 = std::make_shared<jose::rsa>(jose::alg::RS256, key));
	EXPECT_NO_THROW(r256_pub = std::make_shared<jose::rsa>(jose::alg::RS256, pubkey));
	EXPECT_NO_THROW(r384 = std::make_shared<jose::rsa>(jose::alg::RS384, key));
	EXPECT_NO_THROW(r384_pub = std::make_shared<jose::rsa>(jose::alg::RS384, pubkey));
	EXPECT_NO_THROW(r512 = std::make_shared<jose::rsa>(jose::alg::RS512, key));
	EXPECT_NO_THROW(r512_pub = std::make_shared<jose::rsa>(jose::alg::RS512, pubkey));

	std::string bearer = jose::jws::sign_bearer(cl, r384);

	jose::sp_jws jws;

	EXPECT_NO_THROW(jws = jose::jws::parse(bearer));

	EXPECT_TRUE(jws->verify(r384_pub));

	auto vf = [](jose::sp_claims cl) {
		return !cl->check().iss("troian");
	};

	EXPECT_TRUE(jws->verify(r384_pub, vf));
	EXPECT_THROW(jws->verify(r256_pub, vf), std::exception);
	EXPECT_THROW(jws->verify(r512_pub, vf), std::exception);

	bearer = "ghdfgddf";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);

	bearer = "Bearer ";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);

	bearer = "Bearer bla.bla.bla";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);
}

TEST(JosePP, sign_verify_rsa512) {
	jose::claims cl;

	jose::sp_rsa_key key;
	jose::sp_rsa_key pubkey;
	jose::sp_crypto r256;
	jose::sp_crypto r256_pub;
	jose::sp_crypto r384;
	jose::sp_crypto r384_pub;
	jose::sp_crypto r512;
	jose::sp_crypto r512_pub;

	EXPECT_NO_THROW(key = jose::rsa::gen(1024));
	EXPECT_NO_THROW(pubkey = jose::sp_rsa_key(RSAPublicKey_dup(key.get()), ::RSA_free));
	EXPECT_NO_THROW(r256 = std::make_shared<jose::rsa>(jose::alg::RS256, key));
	EXPECT_NO_THROW(r256_pub = std::make_shared<jose::rsa>(jose::alg::RS256, pubkey));
	EXPECT_NO_THROW(r384 = std::make_shared<jose::rsa>(jose::alg::RS384, key));
	EXPECT_NO_THROW(r384_pub = std::make_shared<jose::rsa>(jose::alg::RS384, pubkey));
	EXPECT_NO_THROW(r512 = std::make_shared<jose::rsa>(jose::alg::RS512, key));
	EXPECT_NO_THROW(r512_pub = std::make_shared<jose::rsa>(jose::alg::RS512, pubkey));

	std::string bearer = jose::jws::sign_bearer(cl, r512);

	jose::sp_jws jws;

	EXPECT_NO_THROW(jws = jose::jws::parse(bearer));

	EXPECT_TRUE(jws->verify(r512_pub));

	auto vf = [](jose::sp_claims cl) {
		return !cl->check().iss("troian");
	};

	EXPECT_TRUE(jws->verify(r512_pub, vf));
	EXPECT_THROW(jws->verify(r384_pub, vf), std::exception);
	EXPECT_THROW(jws->verify(r256_pub, vf), std::exception);

	bearer = "ghdfgddf";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);

	bearer = "Bearer ";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);

	bearer = "Bearer bla.bla.bla";
	EXPECT_THROW(jws = jose::jws::parse(bearer), std::exception);
}

TEST(JosePP, load_rsa_from_file) {
	jose::sp_rsa_key key;

	EXPECT_NO_THROW(key = jose::rsa::load_from_file("./tests/private.pem", [](jose::secure_string &pass, int rwflag) {
		pass.assign("12345");
	}));

	EXPECT_THROW(key = jose::rsa::load_from_file("./tests/private.pem"), std::exception);
}
