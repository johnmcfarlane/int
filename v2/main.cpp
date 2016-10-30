
#include "int.h"

#include <iostream>
#include <iomanip>

using namespace std;

#define assert(a, info) {if (!(a)) throw std::runtime_error(#a ", line:" + std::to_string(__LINE__) + ", info:" + info );}

template<int bits, bool sgn>
void printNum(const wide_int<bits, sgn>& n) {
    for (auto c : n.m_arr) {
        std::cout << std::hex << std::setw(16) << std::setfill('0') << c << std::endl;
    }
}

void printNum(uint64_t n) {
    std::cout << std::hex << std::setw(16) << std::setfill('0') << n << std::endl;
}

void testCtors() {
    int512_t a1 = 0;
    for (auto c : a1.m_arr) {
        assert(c == 0, "");
    }
    uint512_t b1 = 0;
    for (auto c : b1.m_arr) {
        assert(c == 0, "");
    }

    int512_t a2 = 13;
    for (int idx = 0; idx < 7; ++idx) {
        assert(a2.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a2.m_arr[7] == 13, "");
    uint512_t b2 = 13;
    for (int idx = 0; idx < 7; ++idx) {
        assert(b2.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b2.m_arr[7] == 13, "");

    int512_t a3 = -13;
    for (int idx = 0; idx < 7; ++idx) {
        assert(a3.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a3.m_arr[7] == 0xfffffffffffffff3, "");
    uint512_t b3 = -13;
    for (int idx = 0; idx < 7; ++idx) {
        assert(b3.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b3.m_arr[7] == 0xfffffffffffffff3, "");

    int512_t a4 = int128_t(13);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a4.m_arr[7] == 13, "");
    uint512_t b4 = uint128_t(13);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b4.m_arr[7] == 13, "");

    int512_t a5 = uint128_t(13);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a5.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a5.m_arr[7] == 13, "");
    uint512_t b5 = int128_t(13);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b5.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b5.m_arr[7] == 13, "");

    int512_t a6 = uint128_t(-13);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a6.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a6.m_arr[6] == 0xffffffffffffffff, "");
    assert(a6.m_arr[7] == 0xfffffffffffffff3, "");
    uint512_t b6 = int128_t(-13);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b6.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b6.m_arr[7] == 0xfffffffffffffff3, "");

    int512_t a7 = int128_t(-13);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a7.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a7.m_arr[7] == 0xfffffffffffffff3, "");
    uint512_t b7 = uint128_t(-13);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b7.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b7.m_arr[6] == 0xffffffffffffffff, "");
    assert(b7.m_arr[7] == 0xfffffffffffffff3, "");
}

void testShifts() {
    //left
    uint512_t a1 = 0;
    for (auto c : uint512_t::shift_left(a1, 0).m_arr) {
        assert(c == 0, "");
    }
    uint512_t a2 = 0;
    for (auto c : uint512_t::shift_left(a2, 15).m_arr) {
        assert(c == 0, "");
    }

    uint512_t a3 = 0xf1f2f3f4f5f6f7f8;
    uint512_t a31 = uint512_t::shift_left(a3, 8);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a31.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a31.m_arr[6] == 0x00000000000000f1, "");
    assert(a31.m_arr[7] == 0xf2f3f4f5f6f7f800, "");

    uint512_t a32 = uint512_t::shift_left(a3, 16);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a32.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a32.m_arr[6] == 0x000000000000f1f2, "");
    assert(a32.m_arr[7] == 0xf3f4f5f6f7f80000, "");

    uint512_t a33 = uint512_t::shift_left(a3, 4);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a33.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a33.m_arr[6] == 0x000000000000000f, "");
    assert(a33.m_arr[7] == 0x1f2f3f4f5f6f7f80, "");

    uint512_t a34 = uint512_t::shift_left(a3, 64);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a34.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a34.m_arr[6] == 0xf1f2f3f4f5f6f7f8, "");
    assert(a34.m_arr[7] == 0, "");

    uint512_t a35 = uint512_t::shift_left(a3, 256);
    for (int idx = 0; idx < 3; ++idx) {
        assert(a35.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a35.m_arr[3] == 0xf1f2f3f4f5f6f7f8, "");
    for (int idx = 4; idx < 8; ++idx) {
        assert(a35.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a36 = uint512_t::shift_left(a3, 260);
    assert(a36.m_arr[0] == 0, "");
    assert(a36.m_arr[1] == 0, "");
    assert(a36.m_arr[2] == 0x000000000000000f, "");
    assert(a36.m_arr[3] == 0x1f2f3f4f5f6f7f80, "");
    for (int idx = 4; idx < 8; ++idx) {
        assert(a36.m_arr[idx] == 0, std::to_string(idx));
    }

    //right uint
    uint512_t a4 = 0;
    for (auto c : uint512_t::shift_right(a4, 0).m_arr) {
        assert(c == 0, "");
    }
    uint512_t a5 = 0;
    for (auto c : uint512_t::shift_right(a5, 15).m_arr) {
        assert(c == 0, "");
    }

    uint512_t a6 = 0xf1f2f3f4f5f6f7f8;
    a6.m_arr[0] = 0xf1f2f3f4f5f6f7f8;
    uint512_t a61 = uint512_t::shift_right(a6, 8);
    assert(a61.m_arr[0] == 0x00f1f2f3f4f5f6f7, "");
    assert(a61.m_arr[1] == 0xf800000000000000, "");
    for (int idx = 2; idx < 7; ++idx) {
        assert(a61.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a61.m_arr[7] == 0x00f1f2f3f4f5f6f7, "");

    uint512_t a62 = uint512_t::shift_right(a6, 16);
    assert(a62.m_arr[0] == 0x0000f1f2f3f4f5f6, "");
    assert(a62.m_arr[1] == 0xf7f8000000000000, "");
    for (int idx = 2; idx < 6; ++idx) {
        assert(a62.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a62.m_arr[7] == 0x0000f1f2f3f4f5f6, "");

    uint512_t a63 = uint512_t::shift_right(a6, 4);
    assert(a63.m_arr[0] == 0x0f1f2f3f4f5f6f7f, "");
    assert(a63.m_arr[1] == 0x8000000000000000, "");
    for (int idx = 2; idx < 6; ++idx) {
        assert(a63.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a63.m_arr[7] == 0x0f1f2f3f4f5f6f7f, "");

    uint512_t a64 = uint512_t::shift_right(a6, 64);
    assert(a64.m_arr[0] == 0, "");
    assert(a64.m_arr[1] == 0xf1f2f3f4f5f6f7f8, "");
    for (int idx = 2; idx < 7; ++idx) {
        assert(a64.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a65 = uint512_t::shift_right(a6, 256);
    for (int idx = 0; idx < 4; ++idx) {
        assert(a65.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a65.m_arr[4] == 0xf1f2f3f4f5f6f7f8, "");
    for (int idx = 5; idx < 8; ++idx) {
        assert(a65.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a66 = uint512_t::shift_right(a6, 260);
    for (int idx = 0; idx < 4; ++idx) {
        assert(a66.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a66.m_arr[4] == 0x0f1f2f3f4f5f6f7f, "");
    assert(a66.m_arr[5] == 0x8000000000000000, "");
    for (int idx = 6; idx < 8; ++idx) {
        assert(a66.m_arr[idx] == 0, std::to_string(idx));
    }

    //right int > 0
    int512_t b4 = 0;
    for (auto c : int512_t::shift_right(b4, 0).m_arr) {
        assert(c == 0, "");
    }
    int512_t b5 = 0;
    for (auto c : int512_t::shift_right(b5, 15).m_arr) {
        assert(c == 0, "");
    }

    int512_t b6 = 0xf1f2f3f4f5f6f7f8;
    b6.m_arr[0] = 0x71f2f3f4f5f6f7f8;
    int512_t b61 = int512_t::shift_right(b6, 8);
    assert(b61.m_arr[0] == 0x0071f2f3f4f5f6f7, "");
    assert(b61.m_arr[1] == 0xf800000000000000, "");
    for (int idx = 2; idx < 7; ++idx) {
        assert(b61.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b61.m_arr[7] == 0x00f1f2f3f4f5f6f7, "");

    int512_t b62 = int512_t::shift_right(b6, 16);
    assert(b62.m_arr[0] == 0x000071f2f3f4f5f6, "");
    assert(b62.m_arr[1] == 0xf7f8000000000000, "");
    for (int idx = 2; idx < 6; ++idx) {
        assert(b62.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b62.m_arr[7] == 0x0000f1f2f3f4f5f6, "");

    int512_t b63 = int512_t::shift_right(b6, 4);
    assert(b63.m_arr[0] == 0x071f2f3f4f5f6f7f, "");
    assert(b63.m_arr[1] == 0x8000000000000000, "");
    for (int idx = 2; idx < 6; ++idx) {
        assert(b63.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b63.m_arr[7] == 0x0f1f2f3f4f5f6f7f, "");

    int512_t b64 = int512_t::shift_right(b6, 64);
    assert(b64.m_arr[0] == 0, "");
    assert(b64.m_arr[1] == 0x71f2f3f4f5f6f7f8, "");
    for (int idx = 2; idx < 7; ++idx) {
        assert(b64.m_arr[idx] == 0, std::to_string(idx));
    }

    int512_t b65 = int512_t::shift_right(b6, 256);
    for (int idx = 0; idx < 4; ++idx) {
        assert(b65.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b65.m_arr[4] == 0x71f2f3f4f5f6f7f8, "");
    for (int idx = 5; idx < 8; ++idx) {
        assert(b65.m_arr[idx] == 0, std::to_string(idx));
    }

    int512_t b66 = int512_t::shift_right(b6, 260);
    for (int idx = 0; idx < 4; ++idx) {
        assert(b66.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b66.m_arr[4] == 0x071f2f3f4f5f6f7f, "");
    assert(b66.m_arr[5] == 0x8000000000000000, "");
    for (int idx = 6; idx < 8; ++idx) {
        assert(b66.m_arr[idx] == 0, std::to_string(idx));
    }

    //right int < 0
    int512_t b7 = 0xf1f2f3f4f5f6f7f8;
    b7.m_arr[0] = 0xf1f2f3f4f5f6f7f8;
    int512_t b71 = int512_t::shift_right(b7, 8);
    assert(b71.m_arr[0] == 0xfff1f2f3f4f5f6f7, "");
    assert(b71.m_arr[1] == 0xf800000000000000, "");
    for (int idx = 2; idx < 7; ++idx) {
        assert(b71.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b71.m_arr[7] == 0x00f1f2f3f4f5f6f7, "");

    int512_t b72 = int512_t::shift_right(b7, 16);
    assert(b72.m_arr[0] == 0xfffff1f2f3f4f5f6, "");
    assert(b72.m_arr[1] == 0xf7f8000000000000, "");
    for (int idx = 2; idx < 6; ++idx) {
        assert(b72.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b72.m_arr[7] == 0x0000f1f2f3f4f5f6, "");

    int512_t b73 = int512_t::shift_right(b7, 4);
    assert(b73.m_arr[0] == 0xff1f2f3f4f5f6f7f, "");
    assert(b73.m_arr[1] == 0x8000000000000000, "");
    for (int idx = 2; idx < 6; ++idx) {
        assert(b73.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b73.m_arr[7] == 0x0f1f2f3f4f5f6f7f, "");

    int512_t b74 = int512_t::shift_right(b7, 64);
    assert(b74.m_arr[0] == 0xffffffffffffffff, "");
    assert(b74.m_arr[1] == 0xf1f2f3f4f5f6f7f8, "");
    for (int idx = 2; idx < 7; ++idx) {
        assert(b74.m_arr[idx] == 0, std::to_string(idx));
    }

    int512_t b75 = int512_t::shift_right(b7, 256);
    for (int idx = 0; idx < 4; ++idx) {
        assert(b75.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b75.m_arr[4] == 0xf1f2f3f4f5f6f7f8, "");
    for (int idx = 5; idx < 8; ++idx) {
        assert(b75.m_arr[idx] == 0, std::to_string(idx));
    }

    int512_t b76 = int512_t::shift_right(b7, 260);
    for (int idx = 0; idx < 4; ++idx) {
        assert(b76.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b76.m_arr[4] == 0xff1f2f3f4f5f6f7f, "");
    assert(b76.m_arr[5] == 0x8000000000000000, "");
    for (int idx = 6; idx < 8; ++idx) {
        assert(b76.m_arr[idx] == 0, std::to_string(idx));
    }

    int512_t b8 = -13;
    int512_t b81 = int512_t::shift_right(b8, 1);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b81.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b81.m_arr[7] == 0xfffffffffffffff9, "");
}

void testAssign() {
    uint512_t a1 = 0;
    int512_t b1 = 0;

    a1 = 4;
    for (int idx = 0; idx < 7; ++idx) {
        assert(a1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a1.m_arr[7] == 4, "");
    b1 = 4;
    for (int idx = 0; idx < 7; ++idx) {
        assert(b1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b1.m_arr[7] == 4, "");

    a1 = -4;
    for (int idx = 0; idx < 7; ++idx) {
        assert(a1.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a1.m_arr[7] == 0xfffffffffffffffc, "");
    b1 = -4;
    for (int idx = 0; idx < 7; ++idx) {
        assert(b1.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b1.m_arr[7] == 0xfffffffffffffffc, "");

    a1 = uint128_t(4);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a1.m_arr[7] == 4, "");
    b1 = int128_t(4);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b1.m_arr[7] == 4, "");

    a1 = uint128_t(-4);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a1.m_arr[6] == 0xffffffffffffffff, "");
    assert(a1.m_arr[7] == 0xfffffffffffffffc, "");
    b1 = int128_t(-4);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b1.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b1.m_arr[7] == 0xfffffffffffffffc, "");

    a1 = int128_t(4);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a1.m_arr[7] == 4, "");
    b1 = uint128_t(4);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b1.m_arr[7] == 4, "");

    a1 = int128_t(-4);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a1.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a1.m_arr[7] == 0xfffffffffffffffc, "");
    b1 = uint128_t(-4);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b1.m_arr[6] == 0xffffffffffffffff, "");
    assert(b1.m_arr[7] == 0xfffffffffffffffc, "");
}

void testOperatorPlus() {
    uint512_t a1 = 3;
    a1.m_arr[6] = 1;

    uint512_t a11 = uint512_t::operator_plus_T(a1, 5);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a11.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a11.m_arr[6] == 1, "");
    assert(a11.m_arr[7] == 8, "");

    uint512_t a12 = uint512_t::operator_plus_T(a1, 0);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a12.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a12.m_arr[6] == 1, "");
    assert(a12.m_arr[7] == 3, "");

    uint512_t a13 = uint512_t::operator_minus_T(a1, 5);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a13.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a13.m_arr[7] == 0xfffffffffffffffe, "");

    uint512_t a14 = uint512_t::operator_plus_T(a1, std::numeric_limits<uint64_t>::max());
    for (int idx = 0; idx < 6; ++idx) {
        assert(a14.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a14.m_arr[6] == 2, "");
    assert(a14.m_arr[7] == 2, "");

    uint512_t a15 = uint512_t::operator_minus_T(a1, 0);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a15.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a15.m_arr[6] == 1, "");
    assert(a15.m_arr[7] == 3, "");

    int512_t b1 = 3;
    b1.m_arr[6] = 1;

    int512_t b11 = int512_t::operator_plus_T(b1, 5);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b11.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b11.m_arr[6] == 1, "");
    assert(b11.m_arr[7] == 8, "");

    int512_t b12 = int512_t::operator_plus_T(b1, 0);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b12.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b12.m_arr[6] == 1, "");
    assert(b12.m_arr[7] == 3, "");

    int512_t b13 = int512_t::operator_minus_T(b1, 5);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b13.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b13.m_arr[7] == 0xfffffffffffffffe, "");

    int512_t b14 = int512_t::operator_minus_T(b1, 0);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b14.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b14.m_arr[6] == 1, "");
    assert(b14.m_arr[7] == 3, "");

    int512_t b2 = -3;
    b2.m_arr[6] = -2;

    int512_t b21 = int512_t::operator_minus_T(b2, 5);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b21.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b21.m_arr[6] == 0xfffffffffffffffe, "");
    assert(static_cast<int64_t>(b21.m_arr[7]) == -8, "");

    int512_t b22 = int512_t::operator_plus_T(b2, 0);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b22.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b22.m_arr[6] == 0xfffffffffffffffe, "");
    assert(static_cast<int64_t>(b22.m_arr[7]) == -3, "");

    int512_t b23 = int512_t::operator_plus_T(b2, uint16_t(5));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b23.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b23.m_arr[6] == 0xffffffffffffffff, "");
    assert(b23.m_arr[7] == 0x0000000000000002, "");

    int512_t b3 = -3;

    int512_t b31 = int512_t::operator_plus_T(b3, 5);
    for (int idx = 0; idx < 7; ++idx) {
        assert(b31.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(static_cast<int64_t>(b31.m_arr[7]) == 2, "");

    int512_t b4 = -1;
    b4.m_arr[6] = -2;
    b4.m_arr[7] = 3;

    int512_t b41 = int512_t::operator_plus_T(b4, 5);
    for (int idx = 0; idx < 6; ++idx) {
        assert(b41.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b41.m_arr[6] == 0xfffffffffffffffe, "");
    assert(static_cast<int64_t>(b41.m_arr[7]) == 8, "");
}

void testOperatorTilda() {
    uint512_t a1 = 250;
    a1.m_arr[3] = 17;

    uint512_t a2 = uint512_t::operator_unary_tilda(a1);
    for (int idx = 0; idx < 3; ++idx) {
        assert(a2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a2.m_arr[3] == 0xffffffffffffffee, "");
    for (int idx = 4; idx < 7; ++idx) {
        assert(a2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a2.m_arr[7] == 0xffffffffffffff05, "");

    int512_t b1 = 250;
    b1.m_arr[3] = 17;

    int512_t b2 = int512_t::operator_unary_tilda(b1);
    for (int idx = 0; idx < 3; ++idx) {
        assert(b2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b2.m_arr[3] == 0xffffffffffffffee, "");
    for (int idx = 4; idx < 7; ++idx) {
        assert(b2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b2.m_arr[7] == 0xffffffffffffff05, "");

    int512_t b3 = -250;
    b3.m_arr[3] = 17;

    int512_t b4 = int512_t::operator_unary_tilda(b3);
    for (int idx = 0; idx < 3; ++idx) {
        assert(b4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b4.m_arr[3] == 0xffffffffffffffee, "");
    for (int idx = 4; idx < 7; ++idx) {
        assert(b4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b4.m_arr[7] == 0x00000000000000f9, "");
}

void testOperatorUnaryMinus() {
    uint512_t a1 = 250;
    a1.m_arr[3] = 17;

    uint512_t a2 = uint512_t::operator_unary_minus(a1);
    for (int idx = 0; idx < 3; ++idx) {
        assert(a2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a2.m_arr[3] == 0xffffffffffffffee, "");
    for (int idx = 4; idx < 7; ++idx) {
        assert(a2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(a2.m_arr[7] == 0xffffffffffffff06, "");

    int512_t b1 = 250;
    b1.m_arr[3] = 17;

    int512_t b2 = int512_t::operator_unary_minus(b1);
    for (int idx = 0; idx < 3; ++idx) {
        assert(b2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b2.m_arr[3] == 0xffffffffffffffee, "");
    for (int idx = 4; idx < 7; ++idx) {
        assert(b2.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b2.m_arr[7] == 0xffffffffffffff06, "");

    int512_t b3 = -250;
    b3.m_arr[3] = 17;

    int512_t b4 = int512_t::operator_unary_minus(b3);
    for (int idx = 0; idx < 3; ++idx) {
        assert(b4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b4.m_arr[3] == 0xffffffffffffffee, "");
    for (int idx = 4; idx < 7; ++idx) {
        assert(b4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b4.m_arr[7] == 0x00000000000000fa, "");
}

void testOperatorPlusWide() {
    uint512_t a1 = 3;
    a1.m_arr[6] = 1;

    uint512_t a11 = uint512_t::operator_plus_wide_int(a1, a1);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a11.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a11.m_arr[6] == 2, "");
    assert(a11.m_arr[7] == 6, "");

    uint512_t a12 = uint512_t::operator_plus_wide_int(a1, uint256_t(0));
    for (int idx = 0; idx < 6; ++idx) {
        assert(a12.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a12.m_arr[6] == 1, "");
    assert(a12.m_arr[7] == 3, "");

    uint512_t a13 = uint512_t::operator_minus_wide_int(a1, uint128_t(5));
    for (int idx = 0; idx < 7; ++idx) {
        assert(a13.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a13.m_arr[7] == 0xfffffffffffffffe, "");

    uint512_t a14 = uint512_t::operator_plus_wide_int(a1, uint512_t::operator_plus_T(a1, std::numeric_limits<uint64_t>::max()));
    for (int idx = 0; idx < 6; ++idx) {
        assert(a14.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a14.m_arr[6] == 3, "");
    assert(a14.m_arr[7] == 5, "");

    uint512_t a15 = uint512_t::operator_minus_wide_int(a1, uint256_t(0));
    for (int idx = 0; idx < 6; ++idx) {
        assert(a15.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a15.m_arr[6] == 1, "");
    assert(a15.m_arr[7] == 3, "");

    int512_t b1 = 3;
    b1.m_arr[6] = 1;

    int512_t b11 = int512_t::operator_plus_wide_int(b1, uint128_t(5));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b11.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b11.m_arr[6] == 1, "");
    assert(b11.m_arr[7] == 8, "");

    int512_t b12 = int512_t::operator_plus_wide_int(b1, uint512_t(0));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b12.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b12.m_arr[6] == 1, "");
    assert(b12.m_arr[7] == 3, "");

    int512_t b13 = int512_t::operator_minus_wide_int(b1, uint128_t(5));
    for (int idx = 0; idx < 7; ++idx) {
        assert(b13.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b13.m_arr[7] == 0xfffffffffffffffe, "");

    int512_t b14 = int512_t::operator_minus_wide_int(b1, int128_t(0));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b14.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(b14.m_arr[6] == 1, "");
    assert(b14.m_arr[7] == 3, "");

    int512_t b2 = -3;
    b2.m_arr[6] = -2;

    int512_t b21 = int512_t::operator_minus_wide_int(b2, uint128_t(5));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b21.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b21.m_arr[6] == 0xfffffffffffffffe, "");
    assert(static_cast<int64_t>(b21.m_arr[7]) == -8, "");

    int512_t b22 = int512_t::operator_plus_wide_int(b2, int256_t(0));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b22.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b22.m_arr[6] == 0xfffffffffffffffe, "");
    assert(static_cast<int64_t>(b22.m_arr[7]) == -3, "");

    int512_t b23 = int512_t::operator_plus_wide_int(b2, uint128_t(5));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b23.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b23.m_arr[6] == 0xffffffffffffffff, "");
    assert(b23.m_arr[7] == 0x0000000000000002, "");

    int512_t b3 = -3;

    int512_t b31 = int512_t::operator_plus_wide_int(b3, int128_t(5));
    for (int idx = 0; idx < 7; ++idx) {
        assert(b31.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(static_cast<int64_t>(b31.m_arr[7]) == 2, "");

    int512_t b4 = -1;
    b4.m_arr[6] = -2;
    b4.m_arr[7] = 3;

    int512_t b41 = int512_t::operator_plus_wide_int(b4, uint256_t(5));
    for (int idx = 0; idx < 6; ++idx) {
        assert(b41.m_arr[idx] == 0xffffffffffffffff, std::to_string(idx));
    }
    assert(b41.m_arr[6] == 0xfffffffffffffffe, "");
    assert(static_cast<int64_t>(b41.m_arr[7]) == 8, "");

    // test cast
    assert(typeid(uint512_t) == typeid(uint512_t::operator_plus_wide_int(uint512_t(0), uint128_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_plus_wide_int(uint512_t(0), uint256_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_plus_wide_int(uint512_t(0), uint512_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_plus_wide_int(int512_t(0), int128_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_plus_wide_int(int512_t(0), int256_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_plus_wide_int(int512_t(0), int512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_plus_wide_int(uint512_t(0), int128_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_plus_wide_int(uint512_t(0), int256_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_plus_wide_int(uint512_t(0), int512_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_plus_wide_int(int512_t(0), uint128_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_plus_wide_int(int512_t(0), uint256_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_plus_wide_int(int512_t(0), uint512_t(3))), "");

    assert(typeid(uint512_t) == typeid(uint128_t::operator_plus_wide_int(uint128_t(0), uint512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint256_t::operator_plus_wide_int(uint256_t(0), uint512_t(3))), "");
    assert(typeid(int512_t) == typeid(int128_t::operator_plus_wide_int(int128_t(0), int512_t(3))), "");
    assert(typeid(int512_t) == typeid(int256_t::operator_plus_wide_int(int256_t(0), int512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint128_t::operator_plus_wide_int(uint128_t(0), int512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint256_t::operator_plus_wide_int(uint256_t(0), int512_t(3))), "");
    assert(typeid(int512_t) == typeid(int128_t::operator_plus_wide_int(int128_t(0), uint512_t(3))), "");
    assert(typeid(int512_t) == typeid(int256_t::operator_plus_wide_int(int256_t(0), uint512_t(3))), "");


    assert(typeid(uint512_t) == typeid(uint512_t::operator_minus_wide_int(uint512_t(0), uint128_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_minus_wide_int(uint512_t(0), uint256_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_minus_wide_int(uint512_t(0), uint512_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_minus_wide_int(int512_t(0), int128_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_minus_wide_int(int512_t(0), int256_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_minus_wide_int(int512_t(0), int512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_minus_wide_int(uint512_t(0), int128_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_minus_wide_int(uint512_t(0), int256_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint512_t::operator_minus_wide_int(uint512_t(0), int512_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_minus_wide_int(int512_t(0), uint128_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_minus_wide_int(int512_t(0), uint256_t(3))), "");
    assert(typeid(int512_t) == typeid(int512_t::operator_minus_wide_int(int512_t(0), uint512_t(3))), "");

    assert(typeid(uint512_t) == typeid(uint128_t::operator_minus_wide_int(uint128_t(0), uint512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint256_t::operator_minus_wide_int(uint256_t(0), uint512_t(3))), "");
    assert(typeid(int512_t) == typeid(int128_t::operator_minus_wide_int(int128_t(0), int512_t(3))), "");
    assert(typeid(int512_t) == typeid(int256_t::operator_minus_wide_int(int256_t(0), int512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint128_t::operator_minus_wide_int(uint128_t(0), int512_t(3))), "");
    assert(typeid(uint512_t) == typeid(uint256_t::operator_minus_wide_int(uint256_t(0), int512_t(3))), "");
    assert(typeid(int512_t) == typeid(int128_t::operator_minus_wide_int(int128_t(0), uint512_t(3))), "");
    assert(typeid(int512_t) == typeid(int256_t::operator_minus_wide_int(int256_t(0), uint512_t(3))), "");
}

void testOperatorStar() {
    uint512_t a1 = 256;

    uint512_t a11 = uint512_t::operator_star(a1, uint512_t(1));
    for (int idx = 0; idx < 7; ++idx) {
        assert(a11.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a11.m_arr[7] == 256, "");

    uint512_t a12 = uint512_t::operator_star(a1, uint512_t(0));
    for (int idx = 0; idx < 8; ++idx) {
        assert(a12.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a13 = uint512_t::operator_star(a1, uint512_t(2));
    for (int idx = 0; idx < 7; ++idx) {
        assert(a13.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a13.m_arr[7] == 512, "");

    uint512_t a2 = std::numeric_limits<uint64_t>::max();
    uint512_t a24 = uint512_t::operator_star(a2, uint512_t(2));
    for (int idx = 0; idx < 6; ++idx) {
        assert(a24.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a24.m_arr[6] == 1, "");
    assert(a24.m_arr[7] == 0xfffffffffffffffe, "");

    uint512_t a3 = 256;

    uint512_t a31 = uint512_t::operator_star(a3, 1);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a31.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a31.m_arr[7] == 256, "");

    uint512_t a32 = uint512_t::operator_star(a3, 0);
    for (int idx = 0; idx < 8; ++idx) {
        assert(a32.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a33 = uint512_t::operator_star(a3, 2);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a33.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a33.m_arr[7] == 512, "");

    uint512_t a4 = std::numeric_limits<uint64_t>::max();
    uint512_t a44 = uint512_t::operator_star(a4, 2);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a44.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a44.m_arr[6] == 1, "");
    assert(a44.m_arr[7] == 0xfffffffffffffffe, "");
}

void testOperatorMore() {
    assert(int512_t::operator_more(15, -18), "");
    assert(!uint512_t::operator_more(15, 18U), "");
    assert(uint512_t::operator_more(18, 15U), "");
    assert(!uint512_t::operator_more(15, 18U), "");
    assert(int512_t::operator_more(-15, -18), "");
    assert(!int512_t::operator_more(-18, -15), "");
}

void testOperatorEq() {
    assert(uint512_t::operator_eq(uint512_t(12), int64_t(12)), "");
    assert(uint512_t::operator_eq(12, 12), "");
    assert(uint512_t::operator_eq(0, 0), "");
}

void testOperatorPipe() {
    uint512_t a1 = 0x0102030405060708;
    a1.m_arr[0]  = 0x0101010101010101;
    uint512_t a2 = uint512_t::operator_pipe(a1, 0xf0f0f0f0f0f0f0f0);

    assert(a2.m_arr[0] == 0x0101010101010101, "");
    for (int idx = 1; idx < 7; ++idx) {
        assert(a2.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a2.m_arr[7] == 0xf1f2f3f4f5f6f7f8, "");

    uint512_t a3 = 0xf0f0f0f0f0f0f0f0;
    a3.m_arr[0]  = 0xf0f0f0f0f0f0f0f0;

    uint512_t a4 = uint512_t::operator_pipe(a1, a3);

    assert(a4.m_arr[0] == 0xf1f1f1f1f1f1f1f1, "");
    for (int idx = 1; idx < 7; ++idx) {
        assert(a4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a4.m_arr[7] == 0xf1f2f3f4f5f6f7f8, "");
}

void testOperatorAmp() {
    uint512_t a1 = 0x0102030405060708;
    a1.m_arr[0]  = 0x0101010101010101;
    uint512_t a2 = uint512_t::operator_amp(a1, 0xf0f0f0f0f0f0f0f0);

    for (int idx = 0; idx < 8; ++idx) {
        assert(a2.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a3 = 0xffffffffffffffff;
    a3.m_arr[0]  = 0xf0f0f0f0f0f0f0f0;

    uint512_t a4 = uint512_t::operator_amp(a1, a3);

    for (int idx = 0; idx < 7; ++idx) {
        assert(a4.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a4.m_arr[7] == 0x0102030405060708, "");
}

void testOperatorSlash() {
    uint512_t a1 = uint512_t::operator_slash(15, 3);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a1.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a1.m_arr[7] == 5, "");

    uint512_t a2 = uint512_t::operator_slash(17, 3);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a2.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a2.m_arr[7] == 5, "");

    uint512_t a3 = uint512_t::operator_slash(0, 3);
    for (int idx = 0; idx < 0; ++idx) {
        assert(a3.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a4 = 2048;
    a4.m_arr[6] = 2;
    uint512_t a41 = uint512_t::operator_slash(a4, 2);
    for (int idx = 0; idx < 6; ++idx) {
        assert(a41.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a41.m_arr[6] == 1, "");
    assert(a41.m_arr[7] == 1024, "");
}

void testOperatorPercent() {
    uint512_t a1 = uint512_t::operator_percent(15, 3);
    for (int idx = 0; idx < 8; ++idx) {
        assert(a1.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a2 = uint512_t::operator_percent(17, 3);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a2.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a2.m_arr[7] == 2, "");

    uint512_t a3 = uint512_t::operator_percent(0, 3);
    for (int idx = 0; idx < 0; ++idx) {
        assert(a3.m_arr[idx] == 0, std::to_string(idx));
    }

    uint512_t a4 = 2049;
    a4.m_arr[6] = 2;
    uint512_t a41 = uint512_t::operator_percent(a4, 2);
    for (int idx = 0; idx < 7; ++idx) {
        assert(a41.m_arr[idx] == 0, std::to_string(idx));
    }
    assert(a41.m_arr[7] == 1, "");
}

void testToString() {
    assert(to_string(uint512_t(123455)) == std::string("123455"), "");
    assert(to_string(int512_t(-123455)) == std::string("-123455"), "");
    std::cout << int512_t(-123455) << std::endl;
}

void testCast() {
    assert(int(uint512_t(18)) == 18, "");

    uint128_t a1 = uint512_t(18);
    assert(a1.m_arr[0] == 0, "");
    assert(a1.m_arr[1] == 18, "");
}

void tests() {
    static_assert(std::is_pod<int512_t>::value, "");
    static_assert(std::is_pod<uint512_t>::value, "");
    static_assert(std::is_standard_layout<int512_t>::value, "");
    static_assert(std::is_standard_layout<uint512_t>::value, "");

    testCtors();
    testShifts();
    testAssign();
    testOperatorPlus();
    testOperatorTilda();
    testOperatorUnaryMinus();
    testOperatorPlusWide();
    testOperatorStar();
    testOperatorMore();
    testOperatorEq();
    testOperatorPipe();
    testOperatorAmp();
    testOperatorSlash();
    testOperatorPercent();
    testToString();
    testCast();
}

int main() {
    tests();

    wide_int<512, true> a(13);
    a.m_arr[0] = std::numeric_limits<uint64_t>::max();
    std::cout << "--- " << (wide_int<512, true>::shift_right(a, 0)).m_arr[7] << std::endl;

//    for (uint64_t u : wide_int<512, true>::shift_right(a, 0).m_arr) {
//        std::cout <<std::hex << std::setw(16) << std::setfill('0') << u << std::endl;
//    }

    //    std::cout << b << std::endl;

//    wide_int<256> c = 200;
//    std::cout << c << std::endl;

//    wide_int<512> d = 400;
//    std::cout << d << std::endl;
//    d = 15;
//    std::cout << d << std::endl;
//    d = c + 22;
//    std::cout << d << std::endl;
//    d = 20 + c;
//    std::cout << d << std::endl;

//    // TODO
//    std::cout << std::numeric_limits<wide_int<512>>::max() << std::endl;

//    std::cout << 111123123123123123123_uint128 << std::endl;
//    int32_t c(0x80000000);
//    std::cout << (int32_t(5) > int32_t(-1)) << std::endl;
//    std::cout << ~c << std::endl;
//    std::cout << -c << std::endl;

//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << c << std::endl;
//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << ~c << std::endl;
//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << -c << std::endl;

//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << int64_t(-4) << std::endl;
//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << (int64_t(-1) << 1) << std::endl;
//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << (int64_t(-1) << 16) << std::endl;
//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << (int64_t(-1) >> 8) << std::endl;
//    std::cout << std::hex << std::setw(16) << std::setfill('0');
//    std::cout << (int64_t(-1) >> 16) << std::endl;

    return 0;
}
