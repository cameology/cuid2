#include <gtest/gtest.h>

#include <cuid2/utils.h>



TEST(BASE36, AssertEncoding) {
    EXPECT_EQ(cuid2::base36Encode(cuid2::toBignum(83738)),       "1sm2");
    EXPECT_EQ(cuid2::base36Encode(cuid2::toBignum(87236492)),    "1fxs3w");
    EXPECT_EQ(cuid2::base36Encode(cuid2::toBignum(45678323)),    "r71mb");
    EXPECT_EQ(cuid2::base36Encode(cuid2::toBignum(74395)),       "1lej");
}


TEST(Hash, AssertHash) {
    EXPECT_EQ(cuid2::hash("sjk"),               "awvr2ds5ym8rceo6uurn974q1tfik94nr1thxrguwitp4nudwt268pu1wd3ztuc4a1yja6rodyn0jao4uzxnz0ni7dhjw8wt2f");
    EXPECT_EQ(cuid2::hash("asjlkdhfjklsadfh"),  "o17n1yvsm2cx5601hxwnfwwvqteath6dgpz6qxlsvorrzjfljr8v78sc5rrmk1f4vu7wr80dsynd7nhfc0vwyemkeyh1ufu505");
    EXPECT_EQ(cuid2::hash("46dfsjw78dh"),       "420drb7g40bnu55ppcnlfqjh5k2ldk379wja8tzm5baclns0gn38arbkdbsnrfinltdb9bhko7zumaag8nukqz9tkqciz6fdb4s");
    EXPECT_EQ(cuid2::hash("hjdudf8eh32jjdfu8iweyu3hn34n4f8c8fcujed"),
                                                "0zdz1vxdvcpmkxwmvmwmoz6uq2czglye3efgjorbykizdgmj8tpv3aww5f47dwhx4ijntso856tvjllzu9v82cehxflege2jzf");
    EXPECT_EQ(cuid2::hash("awvr2ds5ym8rceo6uurn974q1tfik94nr1thxrguwitp4nudwt268pu1wd3ztuc4a1yja6rodyn0jao4uzxnz0ni7dhjw8wt2f"),
                                                "me8k2up636zyds5r8buum3ifow37eigr9mu3nwqslfmrqvyub9ugijnuwh8mtchpvlspkoodp2278g3btqusfv4ujlq47worh2");
}
