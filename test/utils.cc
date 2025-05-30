#include <gtest/gtest.h>

#include <cmath>
#include <string>
#include <stdexcept>
#include <bits/stdc++.h>

#include <cuid2/contants.h>
#include <cuid2/utils.h>



TEST(Alpha, AssertLowercase) {
    EXPECT_TRUE(islower(cuid2::alpha()));
    EXPECT_TRUE(islower(cuid2::alpha()));
    EXPECT_TRUE(islower(cuid2::alpha()));
    EXPECT_TRUE(islower(cuid2::alpha()));
    EXPECT_TRUE(islower(cuid2::alpha()));
    EXPECT_TRUE(islower(cuid2::alpha()));
}


TEST(Base36, AssertEncoding) {
    EXPECT_EQ(cuid2::base36Encode("83738"),                         "1sm2");
    EXPECT_EQ(cuid2::base36Encode("87236492"),                      "1fxs3w");
    EXPECT_EQ(cuid2::base36Encode("45678323"),                      "r71mb");
    EXPECT_EQ(cuid2::base36Encode("74395"),                         "1lej");
    EXPECT_EQ(cuid2::base36Encode("982451653"),                     "g8xcjp");
    EXPECT_EQ(cuid2::base36Encode("999999999"),                     "gjdgxr");
    EXPECT_EQ(cuid2::base36Encode("28374982374892374982374982374972398472"),    
                                                                    "19hvh60691uggc0yf8hr0qc20");
    EXPECT_EQ(cuid2::base36Encode("100000000000000000000000000000000000000000000000000"),
                                                                    "1ku3a4pjfxx2nd2gl07gtqboljenwn75s");
}


TEST(Base36, AssertZero) {
    EXPECT_EQ(cuid2::base36Encode("0"),                             "0");
}


TEST(Base36, AssertNegative) {
    EXPECT_EQ(cuid2::base36Encode("-83738"),                        "1sm2");
    EXPECT_EQ(cuid2::base36Encode("-87236492"),                     "1fxs3w");
    EXPECT_EQ(cuid2::base36Encode("-45678323"),                     "r71mb");
    EXPECT_EQ(cuid2::base36Encode("-74395"),                        "1lej");
    EXPECT_EQ(cuid2::base36Encode("-982451653"),                    "g8xcjp");
    EXPECT_EQ(cuid2::base36Encode("-999999999"),                    "gjdgxr");
    EXPECT_EQ(cuid2::base36Encode("-28374982374892374982374982374972398472"),    
                                                                    "19hvh60691uggc0yf8hr0qc20");
    EXPECT_EQ(cuid2::base36Encode("-100000000000000000000000000000000000000000000000000"),
                                                                    "1ku3a4pjfxx2nd2gl07gtqboljenwn75s");
}


TEST(Base36, AssertLowerAlphanumeric) {
    auto encoded = cuid2::base36Encode("8373878367272");

    for (const char ch: encoded) {
        EXPECT_TRUE(islower(ch) || isdigit(ch));
    }
}


TEST(Base36, AssertBigassNumber) {
    auto ctx    = BN_CTX_new();
    auto big    = BN_new();
    auto tenK   = BN_new();

    BN_set_word(big, 2);
    BN_set_word(tenK, 10000);
    BN_exp(big, big, tenK, ctx);

    std::string expected = "";
        expected += "2kqaqr9n8eopgtn6k95g23riodx51p4o3jwyma480okqkygdk2cn232qvv2svfuvbzb5dy9yeoqceom";
        expected += "839h5k1yzf6izbx3rnrjx4pfili0r67ebjqnjhwqevgboilk8yf8ueh7pnd28hk2xttyvgmiqcew98g";
        expected += "rghfhqz4xe93yiifh69uh4kxt2ld4ba87izsm9u323ekhjh37k5tsyn9of1gds6lzq526i1r3f70gd7";
        expected += "4z9ni2b2ej456p7frfijzu9hpdkw1vpsuwds7zpbr7uwcu2qbb0o9djiehjcltlpptcqg19sxajz8vy";
        expected += "ffjeuajmdew0q9j9h7ovpgmyat92n3rx0fgfsu4kluaoi146z5v1t00q073fe6f6ijdue1g06lvqx9i";
        expected += "jmezax2tooljo5c362eil7nkkz91d0n5ghfe1rhofsyujw4209klyhjzcu10ycc0oc19pq7sqo1ugs1";
        expected += "0ym59phjo752siiuj56z2yns5dtodwff92we0a9sgho98t2jgqtgiwilmcmksi5aighqi8h5pxsvyc6";
        expected += "owrans06be91u2gtwi43s3i46rjkvpn85xzco0dgwfzzp8hto1axij5w3j69snadxvc0ed3971r936q";
        expected += "zc0cyou95081lvplzcrid76kf8wbm68tj3zv4j9fj4dnl19etn1koc3hx8eixx85uda4rv92j3dl0ib";
        expected += "8ixgeywnjmivv3kmich1balqsp1hd4b88r7aephwoc9uphu9u2eorlvjmquvqziuu7w1usbf3lmdx28";
        expected += "9lkdeyecnymd88xlb7thrlmxvzjlmnxfjzmqcnaie4sfz81mlqq6n48b4vdkh7gimhfy9rddxdy3fi2";
        expected += "faochb1cnikvkwdz02qa5v9p3l7cnzhxqwhrqdhrcawfl2lbzvs26uzf2fyj2u5i7gv750aitt8drg8";
        expected += "md9i551u8hpaw28r1p3qi29soq8d2iakhw2ezzeux71zlex537kgs18lgk56nw1gbrk00oqowzb5t11";
        expected += "7bvgp6221nr5slvxz3ozr2gqdzume9xuqpeeza98qd009p50qkmghyb3tqsyhmo72h9ptv98w6dh1vw";
        expected += "rja2oa5lfi2ei234f2haziqh3jp0v8vv40tur6cydgv8dohm20yurg6gymgjgm3pb8q2hf57hxioeiy";
        expected += "ild50rersbfumcyc4ij5nhxavlg5s976mkphr0wurzuri1uk44vmrw6w3mftfozkxvo14aii0xct1t6";
        expected += "czu9w9njatnx9igw51aqy3c7rjz7vugf0yzlo6t61a72ddp7lrd9ymgyca271cr17f16fojq5g688h6";
        expected += "rgxg1hhb5zzedw23723s93mai3f603gd4utc7levfzpdhqt7l7t4b70efvq029zofoqrzgno8bpyg5v";
        expected += "gz12jdun0of0ua47zzpa7wk0psnrq0yal1isbf6hbnlvfundz2hbrl4mfxnxxgobkv2jyaag9872k45";
        expected += "x8uwau1mlzx8xhtc43829wyauwejfqifs4em5ipgih0ypn8bfjyq6b3blevcmrostiqldnqa7znph1z";
        expected += "fm7xdjmhghmx57qit1ojxjkjliendm98redq1xtai822suagwdzhq1y8kf523m0nslhvjomttuydoqq";
        expected += "e6pr5rf76aqe3pwx6pmcrub3gmvg6scojyjj4o429qjpzjsehoqe8y6rivp7i904dricmv1l75cfomy";
        expected += "5x92cd34m7r8k886i7o58krwj5257b9wfq7dcj4mwq76vctcezae4v8jtz29fsjl2lbjqhxfjb8itp6";
        expected += "x89ems9fga26i7t7zl5njmbqtp2jt9ommmhiz3ty7izh9gk5dxr26n9bz6j3swbu980hfd9v0vbdrn7";
        expected += "2ra3eiawckwkvhmdgfpi12cjamr0jf22jf268sg";
    
    auto bigStr = BN_bn2dec(big);
    EXPECT_EQ(cuid2::base36Encode(std::string(bigStr)), expected),
        
    BN_free(big);
    BN_free(tenK);
    BN_CTX_free(ctx);
    OPENSSL_free(bigStr);
}


TEST(Hash, AssertHash) {
    EXPECT_EQ(cuid2::hash(""),                                      "hwy9hczxnhp8h02w8vk5ozzfbicdzl7bm3tokbnp700ruweb66gvvn2smv2u019fy0avhunqj6eta7kgi9qwexyqb5aufudz52");
    EXPECT_EQ(cuid2::hash("sjk"),                                   "awvr2ds5ym8rceo6uurn974q1tfik94nr1thxrguwitp4nudwt268pu1wd3ztuc4a1yja6rodyn0jao4uzxnz0ni7dhjw8wt2f");
    EXPECT_EQ(cuid2::hash("asjlkdhfjklsadfh"),                      "o17n1yvsm2cx5601hxwnfwwvqteath6dgpz6qxlsvorrzjfljr8v78sc5rrmk1f4vu7wr80dsynd7nhfc0vwyemkeyh1ufu505");
    EXPECT_EQ(cuid2::hash("46dfsjw78dh"),                           "420drb7g40bnu55ppcnlfqjh5k2ldk379wja8tzm5baclns0gn38arbkdbsnrfinltdb9bhko7zumaag8nukqz9tkqciz6fdb4s");
    EXPECT_EQ(cuid2::hash("hjdudf8eh32jjdfu8iweyu3hn34n4f8c8fcujed"),
                                                                    "0zdz1vxdvcpmkxwmvmwmoz6uq2czglye3efgjorbykizdgmj8tpv3aww5f47dwhx4ijntso856tvjllzu9v82cehxflege2jzf");
    EXPECT_EQ(cuid2::hash("test!@#$%^&*()_+-=[]{}|;':\",./<>? string"),
                                                                    "2j3ufbaheq5twqa2hpr2exql7oiv4688uo8f7geivuyjyyn6pjxup3cj2wt2xnvp2a1aap9htigohvsc816djbdu7i1dhgyiwd");
    EXPECT_EQ(cuid2::hash("awvr2ds5ym8rceo6uurn974q1tfik94nr1thxrguwitp4nudwt268pu1wd3ztuc4a1yja6rodyn0jao4uzxnz0ni7dhjw8wt2f"),
                                                                    "me8k2up636zyds5r8buum3ifow37eigr9mu3nwqslfmrqvyub9ugijnuwh8mtchpvlspkoodp2278g3btqusfv4ujlq47worh2");
}


TEST(Hash, AssertHashLength) {
    EXPECT_EQ(cuid2::hash("").length(),                             98);
    EXPECT_EQ(cuid2::hash("sjk").length(),                          98);
    EXPECT_EQ(cuid2::hash("asjlkdhfjklsadfh").length(),             98);
    EXPECT_EQ(cuid2::hash("46dfsjw78dh").length(),                  99);    // edge cases returning 99 instead of 98
    EXPECT_EQ(cuid2::hash("hjdudf8eh32jjdfu8iweyu3hn34n4f8c8fcujed").length(),
                                                                    98);
    EXPECT_EQ(cuid2::hash("test!@#$%^&*()_+-=[]{}|;':\",./<>? string").length(),
                                                                    98);
    EXPECT_EQ(cuid2::hash("awvr2ds5ym8rceo6uurn974q1tfik94nr1thxrguwitp4nudwt268pu1wd3ztuc4a1yja6rodyn0jao4uzxnz0ni7dhjw8wt2f").length(),
                                                                    98);
}


TEST(Hash, AssertBigassString) {
    auto input = std::string(1000000, 'a');

    EXPECT_NO_THROW(cuid2::hash(input));
    EXPECT_EQ(cuid2::hash(input).length(), 98);
}


TEST(Entropy, AssertValidEntropy) {
    using namespace std::string_literals;

    auto entropy = ""s;

    entropy = cuid2::entropy();
    EXPECT_EQ(entropy.length(), 4);
    for (const char ch: entropy) {
        EXPECT_TRUE(islower(ch) || isdigit(ch));
    }

    entropy = cuid2::entropy(36);
    EXPECT_EQ(entropy.length(), 36);
    for (const char ch: entropy) {
        EXPECT_TRUE(islower(ch) || isdigit(ch));
    }
}


TEST(Entropy, AssertInvalidLength) {
    EXPECT_THROW(cuid2::entropy(0), std::runtime_error);
    EXPECT_THROW(cuid2::entropy(-1), std::runtime_error);
}


TEST(FingerPrint, AssertFingerPrintLength) {
    EXPECT_EQ(cuid2::fingerprint().length(),                        cuid2::BIG_LENGTH);
    EXPECT_EQ(cuid2::fingerprint("test_data").length(),             cuid2::BIG_LENGTH);
    
    EXPECT_EQ(cuid2::fingerprint("", 4).length(),                   4);
    EXPECT_EQ(cuid2::fingerprint("test_data", 4).length(),          4);

    EXPECT_EQ(cuid2::fingerprint("", 12).length(),                  12);
    EXPECT_EQ(cuid2::fingerprint("test_data", 12).length(),         12);
}