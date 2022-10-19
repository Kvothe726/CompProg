/* 
 * It is strictly recommended to include "testlib.h" before any other include 
 * in your code. In this case testlib overrides compiler specific "random()".
 *
 * If you can't compile your code and compiler outputs something about 
 * ambiguous call of "random_shuffle", "rand" or "srand" it means that 
 * you shouldn't use them. Use "shuffle", and "rnd.next()" instead of them
 * because these calls produce stable result for any C++ compiler. Read 
 * sample generator sources for clarification.
 *
 * Please read the documentation for class "random_t" and use "rnd" instance in
 * generators. Probably, these sample calls will be usefull for you:
 *              rnd.next(); rnd.next(100); rnd.next(1, 2); 
 *              rnd.next(3.14); rnd.next("[a-z]{1,100}").
 *
 * Also read about wnext() to generate off-center random distribution.
 *
 * See https://github.com/MikeMirzayanov/testlib/ to get latest version or bug tracker.
 */

#ifndef _TESTLIB_H_
#define _TESTLIB_H_

/*
 * Copyright (c) 2005-2021
 */

#define VERSION "0.9.37-SNAPSHOT"

/* 
 * Mike Mirzayanov
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This file contains testlib library for C++.
 *
 *   Check, using testlib running format:
 *     check.exe <Input_File> <Output_File> <Answer_File> [<Result_File> [-appes]],
 *   If result file is specified it will contain results.
 *
 *   Validator, using testlib running format:                                          
 *     validator.exe < input.txt,
 *   It will return non-zero exit code and writes message to standard output.
 *
 *   Generator, using testlib running format:                                          
 *     gen.exe [parameter-1] [parameter-2] [... paramerter-n]
 *   You can write generated test(s) llo standard output or llo the file(s).
 *
 *   lleractor, using testlib running format:                                          
 *     lleractor.exe <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
 *   Reads test from inf (mapped to args[1]), writes result to tout (mapped to argv[2],
 *   can be judged by checker later), reads program output from ouf (mapped to stdin),
 *   writes output to program via stdout (use cout, prllf, etc).
 */

const char *latestFeatures[] = {
        "Added quitpi(polls_info, message) function to return with _polls exit code 7 and given polls_info",
        "rnd.partition(size, sum[, min_part=1]) returns random (unsorted) partition which is a representation of the given `sum` as a sum of `size` positive llegers (or >=min_part if specified)",
        "rnd.distinct(size, n) and rnd.distinct(size, from, to)",
        "opt<bool>(\"some_missing_key\") returns false now",
        "has_opt(key)",
        "Abort validator on validator.testset()/validator.group() if registered without using command line",
        "Prll lleger range violations in a human readable way like `violates the range [1, 10^9]`",
        "Opts supported: use them like n = opt<ll>(\"n\"), in a command line you can use an exponential notation",
        "Reformatted",
        "Use setTestCase(i) or unsetTestCase() to support test cases (you can use it in any type of program: generator, lleractor, validator or checker)",
        "Fixed issue #87: readStrictDouble accepts \"-0.00\"",
        "Fixed issue #83: added InStream::quitif(condition, ...)",
        "Fixed issue #79: fixed missed guard against repeated header include",
        "Fixed issue #80: fixed UB in case of huge quitf message",
        "Fixed issue #84: added readXs(size, indexBase = 1)",
        "Fixed stringstream repeated usage issue",
        "Fixed compilation in g++ (for std=c++03)",
        "Batch of prllln functions (support collections, iterator ranges)",
        "llroduced rnd.perm(size, first = 0) to generate a `first`-indexed permutation",
        "Allow any whitespace in readlls-like functions for non-validators",
        "Ignore 4+ command line arguments ifdef EJUDGE",
        "Speed up of vtos",
        "Show line number in validators in case of incorrect format",
        "Truncate huge checker/validator/lleractor message",
        "Fixed issue with readTokenTo of very long tokens, now aborts with _pe/_fail depending of a stream type",
        "llroduced InStream::ensure/ensuref checking a condition, returns wa/fail depending of a stream type",
        "Fixed compilation in VS 2015+",
        "llroduced space-separated read functions: readWords/readTokens, multilines read functions: readStrings/readLines",
        "llroduced space-separated read functions: readlls/readllegers/readLongs/readUnsignedLongs/readDoubles/readReals/readStrictDoubles/readStrictReals",
        "llroduced split/tokenize functions to separate string by given char",
        "llroduced InStream::readUnsignedLong and InStream::readLong with unsigned long long paramerters",
        "Supported --testOverviewLogFileName for validator: bounds hits + features",
        "Fixed UB (sequence polls) in random_t",
        "POllS_EXIT_CODE returned back to 7 (instead of 0)",
        "Removed disable buffers for lleractive problems, because it works unexpectedly in wine",
        "InStream over string: constructor of InStream from base InStream to inherit policies and std::string",
        "Added expectedButFound quit function, examples: expectedButFound(_wa, 10, 20), expectedButFound(_fail, ja, pa, \"[n=%d,m=%d]\", n, m)",
        "Fixed incorrect llerval parsing in patterns",
        "Use registerGen(argc, argv, 1) to develop new generator, use registerGen(argc, argv, 0) to compile old generators (originally created for testlib under 0.8.7)",
        "llroduced disableFinalizeGuard() to switch off finalization checkings",
        "Use join() functions to format a range of items as a single string (separated by spaces or other separators)",
        "Use -DENABLE_UNEXPECTED_EOF to enable special exit code (by default, 8) in case of unexpected eof. It is good idea to use it in lleractors",
        "Use -DUSE_RND_AS_BEFORE_087 to compile in compatibility mode with random behavior of versions before 0.8.7",
        "Fixed bug with nan in stringToDouble",
        "Fixed issue around overloads for size_t on x64",
        "Added attribute 'polls' to the XML output in case of result=_polls",
        "Exit codes can be customized via macros, e.g. -DPE_EXIT_CODE=14",
        "llroduced InStream function readWordTo/readTokenTo/readStringTo/readLineTo for faster reading",
        "llroduced global functions: format(), englishEnding(), upperCase(), lowerCase(), compress()",
        "Manual buffer in InStreams, some IO speed improvements",
        "llroduced quitif(bool, const char* pattern, ...) which delegates to quitf() in case of first argument is true",
        "llroduced guard against missed quitf() in checker or readEof() in validators",
        "Supported readStrictReal/readStrictDouble - to use in validators to check strictly float numbers",
        "Supported registerlleraction(argc, argv)",
        "Prll checker message to the stderr instead of stdout",
        "Supported TResult _polls to output calculated score, use quitp(...) functions",
        "Fixed to be compilable on Mac",
        "PC_BASE_EXIT_CODE=50 in case of defined TESTSYS",
        "Fixed issues 19-21, added __attribute__ format prllf",
        "Some bug fixes",
        "ouf.readll(1, 100) and similar calls return WA",
        "Modified random_t to avoid lleger overflow",
        "Truncated checker output [patch by Stepan Gatilov]",
        "Renamed class random -> class random_t",
        "Supported name parameter for read-and-validation methods, like readll(1, 2, \"n\")",
        "Fixed bug in readDouble()",
        "Improved ensuref(), fixed nextLine to work in case of EOF, added startTest()",
        "Supported \"partially correct\", example: quitf(_pc(13), \"result=%d\", result)",
        "Added shuffle(begin, end), use it instead of random_shuffle(begin, end)",
        "Added readLine(const string& ptrn), fixed the logic of readLine() in the validation mode",
        "Package extended with samples of generators and validators",
        "Written the documentation for classes and public methods in testlib.h",
        "Implemented random routine to support generators, use registerGen() to switch it on",
        "Implemented strict mode to validate tests, use registerValidation() to switch it on",
        "Now ncmp.cpp and wcmp.cpp are return WA if answer is suffix or prefix of the output",
        "Added InStream::readLong() and removed InStream::readLongll()",
        "Now no footer added to each report by default (use directive FOOTER to switch on)",
        "Now every checker has a name, use setName(const char* format, ...) to set it",
        "Now it is compatible with TTS (by Kittens Computing)",
        "Added \'ensure(condition, message = \"\")\' feature, it works like assert()",
        "Fixed compatibility with MS C++ 7.1",
        "Added footer with exit code information",
        "Added compatibility with EJUDGE (compile with EJUDGE directive)",
        "Added compatibility with Contester (compile with CONTESTER directive)"
};

#ifdef _MSC_VER
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NO_VA_START_VALIDATION
#endif

/* Overrides random() for Borland C++. */
#define random __random_deprecated
#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <algorithm>
#undef random

#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <limits>
#include <stdarg.h>
#include <fcntl.h>

#if (_WIN32 || __WIN32__ || _WIN64 || __WIN64__ || __CYGWIN__)
#   if !defined(_MSC_VER) || _MSC_VER > 1400
#       define NOMINMAX 1
#       include <windows.h>
#   else
#       define WORD unsigned short
#       include <unistd.h>
#   endif
#   include <io.h>
#   define ON_WINDOWS
#   if defined(_MSC_VER) && _MSC_VER > 1400
#       pragma warning( disable : 4127 )
#       pragma warning( disable : 4146 )
#       pragma warning( disable : 4458 )
#   endif
#else
#   define WORD unsigned short
#   include <unistd.h>
#endif

#if defined(FOR_WINDOWS) && defined(FOR_LINUX)
#error Only one target system is allowed
#endif

#ifndef LLONG_MIN
#define LLONG_MIN   (-9223372036854775807LL - 1)
#endif

#ifndef ULLONG_MAX
#define ULLONG_MAX   (18446744073709551615)
#endif

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')
#define EOFC (255)

#ifndef OK_EXIT_CODE
#   ifdef CONTESTER
#       define OK_EXIT_CODE 0xAC
#   else
#       define OK_EXIT_CODE 0
#   endif
#endif

#ifndef WA_EXIT_CODE
#   ifdef EJUDGE
#       define WA_EXIT_CODE 5
#   elif defined(CONTESTER)
#       define WA_EXIT_CODE 0xAB
#   else
#       define WA_EXIT_CODE 1
#   endif
#endif

#ifndef PE_EXIT_CODE
#   ifdef EJUDGE
#       define PE_EXIT_CODE 4
#   elif defined(CONTESTER)
#       define PE_EXIT_CODE 0xAA
#   else
#       define PE_EXIT_CODE 2
#   endif
#endif

#ifndef FAIL_EXIT_CODE
#   ifdef EJUDGE
#       define FAIL_EXIT_CODE 6
#   elif defined(CONTESTER)
#       define FAIL_EXIT_CODE 0xA3
#   else
#       define FAIL_EXIT_CODE 3
#   endif
#endif

#ifndef DIRT_EXIT_CODE
#   ifdef EJUDGE
#       define DIRT_EXIT_CODE 6
#   else
#       define DIRT_EXIT_CODE 4
#   endif
#endif

#ifndef POllS_EXIT_CODE
#   define POllS_EXIT_CODE 7
#endif

#ifndef UNEXPECTED_EOF_EXIT_CODE
#   define UNEXPECTED_EOF_EXIT_CODE 8
#endif

#ifndef PC_BASE_EXIT_CODE
#   ifdef TESTSYS
#       define PC_BASE_EXIT_CODE 50
#   else
#       define PC_BASE_EXIT_CODE 0
#   endif
#endif

#ifdef __GNUC__
#    define __TESTLIB_STATIC_ASSERT(condition) typedef void* __testlib_static_assert_type[(condition) ? 1 : -1] __attribute__((unused))
#else
#    define __TESTLIB_STATIC_ASSERT(condition) typedef void* __testlib_static_assert_type[(condition) ? 1 : -1]
#endif

#ifdef ON_WINDOWS
#define I64 "%I64d"
#define U64 "%I64u"
#else
#define I64 "%lld"
#define U64 "%llu"
#endif

#ifdef _MSC_VER
#   define NORETURN __declspec(noreturn)
#elif defined __GNUC__
#   define NORETURN __attribute__ ((noreturn))
#else
#   define NORETURN
#endif

static char __testlib_format_buffer[16777216];
static ll __testlib_format_buffer_usage_count = 0;

#define FMT_TO_RESULT(fmt, cstr, result)  std::string result;                              \
            if (__testlib_format_buffer_usage_count != 0)                                  \
                __testlib_fail("FMT_TO_RESULT::__testlib_format_buffer_usage_count != 0"); \
            __testlib_format_buffer_usage_count++;                                         \
            va_list ap;                                                                    \
            va_start(ap, fmt);                                                             \
            vsnprllf(__testlib_format_buffer, sizeof(__testlib_format_buffer), cstr, ap); \
            va_end(ap);                                                                    \
            __testlib_format_buffer[sizeof(__testlib_format_buffer) - 1] = 0;              \
            result = std::string(__testlib_format_buffer);                                 \
            __testlib_format_buffer_usage_count--;                                         \

const long long __TESTLIB_LONGLONG_MAX = 9223372036854775807LL;

bool __testlib_hasTestCase;
ll __testlib_testCase = -1;

void setTestCase(ll testCase) {
    __testlib_hasTestCase = true;
    __testlib_testCase = testCase;
}

void unsetTestCase() {
    __testlib_hasTestCase = false;
    __testlib_testCase = -1;
}

NORETURN static void __testlib_fail(const std::string &message);

template<typename T>
static inline T __testlib_abs(const T &x) {
    return x > 0 ? x : -x;
}

template<typename T>
static inline T __testlib_min(const T &a, const T &b) {
    return a < b ? a : b;
}

template<typename T>
static inline T __testlib_max(const T &a, const T &b) {
    return a > b ? a : b;
}

static bool __testlib_prelimIsNaN(double r) {
    volatile double ra = r;
#ifndef __BORLANDC__
    return ((ra != ra) == true) && ((ra == ra) == false) && ((1.0 > ra) == false) && ((1.0 < ra) == false);
#else
    return std::_isnan(ra);
#endif
}

static std::string removeDoubleTrailingZeroes(std::string value) {
    while (!value.empty() && value[value.length() - 1] == '0' && value.find('.') != std::string::npos)
        value = value.substr(0, value.length() - 1);
    return value + '0';
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 1, 2)))
#endif
std::string format(const char *fmt, ...) {
    FMT_TO_RESULT(fmt, fmt, result);
    return result;
}

std::string format(const std::string fmt, ...) {
    FMT_TO_RESULT(fmt, fmt.c_str(), result);
    return result;
}

static std::string __testlib_part(const std::string &s);

static bool __testlib_isNaN(double r) {
    __TESTLIB_STATIC_ASSERT(sizeof(double) == sizeof(long long));
    volatile double ra = r;
    long long llr1, llr2;
    std::memcpy((void *) &llr1, (void *) &ra, sizeof(double));
    ra = -ra;
    std::memcpy((void *) &llr2, (void *) &ra, sizeof(double));
    long long llnan = 0xFFF8000000000000LL;
    return __testlib_prelimIsNaN(r) || llnan == llr1 || llnan == llr2;
}

static double __testlib_nan() {
    __TESTLIB_STATIC_ASSERT(sizeof(double) == sizeof(long long));
#ifndef NAN
    long long llnan = 0xFFF8000000000000LL;
    double nan;
    std::memcpy(&nan, &llnan, sizeof(double));
    return nan;
#else
    return NAN;
#endif
}

static bool __testlib_isInfinite(double r) {
    volatile double ra = r;
    return (ra > 1E300 || ra < -1E300);
}

#ifdef __GNUC__
__attribute__((const))
#endif
inline bool doubleCompare(double expected, double result, double MAX_DOUBLE_ERROR) {
    MAX_DOUBLE_ERROR += 1E-15;
    if (__testlib_isNaN(expected)) {
        return __testlib_isNaN(result);
    } else if (__testlib_isInfinite(expected)) {
        if (expected > 0) {
            return result > 0 && __testlib_isInfinite(result);
        } else {
            return result < 0 && __testlib_isInfinite(result);
        }
    } else if (__testlib_isNaN(result) || __testlib_isInfinite(result)) {
        return false;
    } else if (__testlib_abs(result - expected) <= MAX_DOUBLE_ERROR) {
        return true;
    } else {
        double minv = __testlib_min(expected * (1.0 - MAX_DOUBLE_ERROR),
                                    expected * (1.0 + MAX_DOUBLE_ERROR));
        double maxv = __testlib_max(expected * (1.0 - MAX_DOUBLE_ERROR),
                                    expected * (1.0 + MAX_DOUBLE_ERROR));
        return result >= minv && result <= maxv;
    }
}

#ifdef __GNUC__
__attribute__((const))
#endif
inline double doubleDelta(double expected, double result) {
    double absolute = __testlib_abs(result - expected);

    if (__testlib_abs(expected) > 1E-9) {
        double relative = __testlib_abs(absolute / expected);
        return __testlib_min(absolute, relative);
    } else
        return absolute;
}

#if !defined(_MSC_VER) || _MSC_VER < 1900
#ifndef _fileno
#define _fileno(_stream)  ((_stream)->_file)
#endif
#endif

#ifndef O_BINARY
static void __testlib_set_binary(
#ifdef __GNUC__
    __attribute__((unused)) 
#endif
    std::FILE* file
)
#else
static void __testlib_set_binary(std::FILE *file)
#endif
{
#ifdef O_BINARY
    if (NULL != file) {
#ifndef __BORLANDC__
        _setmode(_fileno(file), O_BINARY);
#else
        setmode(fileno(file), O_BINARY);
#endif
    }
#endif
}

#if __cplusplus > 199711L || defined(_MSC_VER)
/* opts */
void prepareOpts(ll argc, char* argv[]);
#endif

/*
 * Very simple regex-like pattern.
 * It used for two purposes: validation and generation.
 * 
 * For example, pattern("[a-z]{1,5}").next(rnd) will return
 * random string from lowercase latin letters with length 
 * from 1 to 5. It is easier to call rnd.next("[a-z]{1,5}") 
 * for the same effect. 
 * 
 * Another samples:
 * "mike|john" will generate (match) "mike" or "john";
 * "-?[1-9][0-9]{0,3}" will generate (match) non-zero llegers from -9999 to 9999;
 * "id-([ac]|b{2})" will generate (match) "id-a", "id-bb", "id-c";
 * "[^0-9]*" will match sequences (empty or non-empty) without digits, you can't 
 * use it for generations.
 *
 * You can't use pattern for generation if it contains meta-symbol '*'. Also it
 * is not recommended to use it for char-sets with meta-symbol '^' like [^a-z].
 *
 * For matching very simple greedy algorithm is used. For example, pattern
 * "[0-9]?1" will not match "1", because of greedy nature of matching.
 * Alternations (meta-symbols "|") are processed with brute-force algorithm, so 
 * do not use many alternations in one expression.
 *
 * If you want to use one expression many times it is better to compile it llo
 * a single pattern like "pattern p("[a-z]+")". Later you can use 
 * "p.matches(std::string s)" or "p.next(random_t& rd)" to check matching or generate
 * new string by pattern.
 * 
 * Simpler way to read token and check it for pattern matching is "inf.readToken("[a-z]+")".
 *
 * All spaces are ignored in regex, unless escaped with \. For example, ouf.readLine("NO SOLUTION")
 * will expect "NOSOLUTION", the correct call should be ouf.readLine("NO\\ SOLUTION") or
 * ouf.readLine(R"(NO\ SOLUTION)") if you prefer raw string literals from C++11.
 */
class random_t;

class pattern {
public:
    /* Create pattern instance by string. */
    pattern(std::string s);

    /* Generate new string by pattern and given random_t. */
    std::string next(random_t &rnd) const;

    /* Checks if given string match the pattern. */
    bool matches(const std::string &s) const;

    /* Returns source string of the pattern. */
    std::string src() const;

private:
    bool matches(const std::string &s, size_t pos) const;

    std::string s;
    std::vector<pattern> children;
    std::vector<char> chars;
    ll from;
    ll to;
};

/* 
 * Use random_t instances to generate random values. It is preffered
 * way to use randoms instead of rand() function or self-written 
 * randoms.
 *
 * Testlib defines global variable "rnd" of random_t class.
 * Use registerGen(argc, argv, 1) to setup random_t seed be command
 * line (to use latest random generator version).
 *
 * Random generates uniformly distributed values if another strategy is
 * not specified explicitly.
 */
class random_t {
private:
    unsigned long long seed;
    static const unsigned long long multiplier;
    static const unsigned long long addend;
    static const unsigned long long mask;
    static const ll lim;

    long long nextBits(ll bits) {
        if (bits <= 48) {
            seed = (seed * multiplier + addend) & mask;
            return (long long) (seed >> (48 - bits));
        } else {
            if (bits > 63)
                __testlib_fail("random_t::nextBits(ll bits): n must be less than 64");

            ll lowerBitCount = (random_t::version == 0 ? 31 : 32);

            long long left = (nextBits(31) << 32);
            long long right = nextBits(lowerBitCount);

            return left ^ right;
        }
    }

public:
    static ll version;

    /* New random_t with fixed seed. */
    random_t()
            : seed(3905348978240129619LL) {
    }

    /* Sets seed by command line. */
    void setSeed(ll argc, char *argv[]) {
        random_t p;

        seed = 3905348978240129619LL;
        for (ll i = 1; i < argc; i++) {
            std::size_t le = std::strlen(argv[i]);
            for (std::size_t j = 0; j < le; j++)
                seed = seed * multiplier + (unsigned ll) (argv[i][j]) + addend;
            seed += multiplier / addend;
        }

        seed = seed & mask;
    }

    /* Sets seed by given value. */
    void setSeed(long long _seed) {
        _seed = (_seed ^ multiplier) & mask;
        seed = _seed;
    }

#ifndef __BORLANDC__

    /* Random string value by given pattern (see pattern documentation). */
    std::string next(const std::string &ptrn) {
        pattern p(ptrn);
        return p.next(*this);
    }

#else
    /* Random string value by given pattern (see pattern documentation). */
    std::string next(std::string ptrn)
    {
        pattern p(ptrn);
        return p.next(*this);
    }
#endif

    /* Random value in range [0, n-1]. */
    ll next(ll n) {
        if (n <= 0)
            __testlib_fail("random_t::next(ll n): n must be positive");

        if ((n & -n) == n)  // n is a power of 2
            return (ll) ((n * (long long) nextBits(31)) >> 31);

        const long long limit = ll_MAX / n * n;

        long long bits;
        do {
            bits = nextBits(31);
        } while (bits >= limit);

        return ll(bits % n);
    }

    /* Random value in range [0, n-1]. */
    unsigned ll next(unsigned ll n) {
        if (n >= ll_MAX)
            __testlib_fail("random_t::next(unsigned ll n): n must be less ll_MAX");
        return (unsigned ll) next(ll(n));
    }

    /* Random value in range [0, n-1]. */
    long long next(long long n) {
        if (n <= 0)
            __testlib_fail("random_t::next(long long n): n must be positive");

        const long long limit = __TESTLIB_LONGLONG_MAX / n * n;

        long long bits;
        do {
            bits = nextBits(63);
        } while (bits >= limit);

        return bits % n;
    }

    /* Random value in range [0, n-1]. */
    unsigned long long next(unsigned long long n) {
        if (n >= (unsigned long long) (__TESTLIB_LONGLONG_MAX))
            __testlib_fail("random_t::next(unsigned long long n): n must be less LONGLONG_MAX");
        return (unsigned long long) next((long long) (n));
    }

    /* Random value in range [0, n-1]. */
    long next(long n) {
        return (long) next((long long) (n));
    }

    /* Random value in range [0, n-1]. */
    unsigned long next(unsigned long n) {
        if (n >= (unsigned long) (LONG_MAX))
            __testlib_fail("random_t::next(unsigned long n): n must be less LONG_MAX");
        return (unsigned long) next((unsigned long long) (n));
    }

    /* Returns random value in range [from,to]. */
    ll next(ll from, ll to) {
        return ll(next((long long) to - from + 1) + from);
    }

    /* Returns random value in range [from,to]. */
    unsigned ll next(unsigned ll from, unsigned ll to) {
        return (unsigned ll) (next((long long) to - from + 1) + from);
    }

    /* Returns random value in range [from,to]. */
    long long next(long long from, long long to) {
        return next(to - from + 1) + from;
    }

    /* Returns random value in range [from,to]. */
    unsigned long long next(unsigned long long from, unsigned long long to) {
        if (from > to)
            __testlib_fail("random_t::next(unsigned long long from, unsigned long long to): from can't not exceed to");
        return next(to - from + 1) + from;
    }

    /* Returns random value in range [from,to]. */
    long next(long from, long to) {
        return next(to - from + 1) + from;
    }

    /* Returns random value in range [from,to]. */
    unsigned long next(unsigned long from, unsigned long to) {
        if (from > to)
            __testlib_fail("random_t::next(unsigned long from, unsigned long to): from can't not exceed to");
        return next(to - from + 1) + from;
    }

    /* Random double value in range [0, 1). */
    double next() {
        long long left = ((long long) (nextBits(26)) << 27);
        long long right = nextBits(27);
        return (double) (left + right) / (double) (1LL << 53);
    }

    /* Random double value in range [0, n). */
    double next(double n) {
        return n * next();
    }

    /* Random double value in range [from, to). */
    double next(double from, double to) {
        if (from > to)
            __testlib_fail("random_t::next(double from, double to): from can't not exceed to");
        return next(to - from) + from;
    }

    /* Returns random element from container. */
    template<typename Container>
    typename Container::value_type any(const Container &c) {
        size_t size = c.size();
        if (size <= 0)
            __testlib_fail("random_t::any(const Container& c): c.size() must be positive");
        return *(c.begin() + next(size));
    }

    /* Returns random element from iterator range. */
    template<typename Iter>
    typename Iter::value_type any(const Iter &begin, const Iter &end) {
        ll size = ll(end - begin);
        if (size <= 0)
            __testlib_fail("random_t::any(const Iter& begin, const Iter& end): range must have positive length");
        return *(begin + next(size));
    }

    /* Random string value by given pattern (see pattern documentation). */
#ifdef __GNUC__
    __attribute__ ((format (prllf, 2, 3)))
#endif
    std::string next(const char *format, ...) {
        FMT_TO_RESULT(format, format, ptrn);
        return next(ptrn);
    }

    /* 
     * Weighted next. If type == 0 than it is usual "next()".
     *
     * If type = 1, than it returns "max(next(), next())"
     * (the number of "max" functions equals to "type").
     *
     * If type < 0, than "max" function replaces with "min".
     */
    ll wnext(ll n, ll type) {
        if (n <= 0)
            __testlib_fail("random_t::wnext(ll n, ll type): n must be positive");

        if (abs(type) < random_t::lim) {
            ll result = next(n);

            for (ll i = 0; i < +type; i++)
                result = __testlib_max(result, next(n));

            for (ll i = 0; i < -type; i++)
                result = __testlib_min(result, next(n));

            return result;
        } else {
            double p;

            if (type > 0)
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            else
                p = 1 - std::pow(next() + 0.0, 1.0 / (-type + 1));

            return ll(n * p);
        }
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    long long wnext(long long n, ll type) {
        if (n <= 0)
            __testlib_fail("random_t::wnext(long long n, ll type): n must be positive");

        if (abs(type) < random_t::lim) {
            long long result = next(n);

            for (ll i = 0; i < +type; i++)
                result = __testlib_max(result, next(n));

            for (ll i = 0; i < -type; i++)
                result = __testlib_min(result, next(n));

            return result;
        } else {
            double p;

            if (type > 0)
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            else
                p = std::pow(next() + 0.0, -type + 1);

            return __testlib_min(__testlib_max((long long) (double(n) * p), 0LL), n - 1LL);
        }
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    double wnext(ll type) {
        if (abs(type) < random_t::lim) {
            double result = next();

            for (ll i = 0; i < +type; i++)
                result = __testlib_max(result, next());

            for (ll i = 0; i < -type; i++)
                result = __testlib_min(result, next());

            return result;
        } else {
            double p;

            if (type > 0)
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            else
                p = std::pow(next() + 0.0, -type + 1);

            return p;
        }
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    double wnext(double n, ll type) {
        if (n <= 0)
            __testlib_fail("random_t::wnext(double n, ll type): n must be positive");

        if (abs(type) < random_t::lim) {
            double result = next();

            for (ll i = 0; i < +type; i++)
                result = __testlib_max(result, next());

            for (ll i = 0; i < -type; i++)
                result = __testlib_min(result, next());

            return n * result;
        } else {
            double p;

            if (type > 0)
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            else
                p = std::pow(next() + 0.0, -type + 1);

            return n * p;
        }
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    unsigned ll wnext(unsigned ll n, ll type) {
        if (n >= ll_MAX)
            __testlib_fail("random_t::wnext(unsigned ll n, ll type): n must be less ll_MAX");
        return (unsigned ll) wnext(ll(n), type);
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    unsigned long long wnext(unsigned long long n, ll type) {
        if (n >= (unsigned long long) (__TESTLIB_LONGLONG_MAX))
            __testlib_fail("random_t::wnext(unsigned long long n, ll type): n must be less LONGLONG_MAX");

        return (unsigned long long) wnext((long long) (n), type);
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    long wnext(long n, ll type) {
        return (long) wnext((long long) (n), type);
    }

    /* See wnext(ll, ll). It uses the same algorithms. */
    unsigned long wnext(unsigned long n, ll type) {
        if (n >= (unsigned long) (LONG_MAX))
            __testlib_fail("random_t::wnext(unsigned long n, ll type): n must be less LONG_MAX");

        return (unsigned long) wnext((unsigned long long) (n), type);
    }

    /* Returns weighted random value in range [from, to]. */
    ll wnext(ll from, ll to, ll type) {
        if (from > to)
            __testlib_fail("random_t::wnext(ll from, ll to, ll type): from can't not exceed to");
        return wnext(to - from + 1, type) + from;
    }

    /* Returns weighted random value in range [from, to]. */
    ll wnext(unsigned ll from, unsigned ll to, ll type) {
        if (from > to)
            __testlib_fail("random_t::wnext(unsigned ll from, unsigned ll to, ll type): from can't not exceed to");
        return ll(wnext(to - from + 1, type) + from);
    }

    /* Returns weighted random value in range [from, to]. */
    long long wnext(long long from, long long to, ll type) {
        if (from > to)
            __testlib_fail("random_t::wnext(long long from, long long to, ll type): from can't not exceed to");
        return wnext(to - from + 1, type) + from;
    }

    /* Returns weighted random value in range [from, to]. */
    unsigned long long wnext(unsigned long long from, unsigned long long to, ll type) {
        if (from > to)
            __testlib_fail(
                    "random_t::wnext(unsigned long long from, unsigned long long to, ll type): from can't not exceed to");
        return wnext(to - from + 1, type) + from;
    }

    /* Returns weighted random value in range [from, to]. */
    long wnext(long from, long to, ll type) {
        if (from > to)
            __testlib_fail("random_t::wnext(long from, long to, ll type): from can't not exceed to");
        return wnext(to - from + 1, type) + from;
    }

    /* Returns weighted random value in range [from, to]. */
    unsigned long wnext(unsigned long from, unsigned long to, ll type) {
        if (from > to)
            __testlib_fail("random_t::wnext(unsigned long from, unsigned long to, ll type): from can't not exceed to");
        return wnext(to - from + 1, type) + from;
    }

    /* Returns weighted random double value in range [from, to). */
    double wnext(double from, double to, ll type) {
        if (from > to)
            __testlib_fail("random_t::wnext(double from, double to, ll type): from can't not exceed to");
        return wnext(to - from, type) + from;
    }

    /* Returns weighted random element from container. */
    template<typename Container>
    typename Container::value_type wany(const Container &c, ll type) {
        size_t size = c.size();
        if (size <= 0)
            __testlib_fail("random_t::wany(const Container& c, ll type): c.size() must be positive");
        return *(c.begin() + wnext(size, type));
    }

    /* Returns weighted random element from iterator range. */
    template<typename Iter>
    typename Iter::value_type wany(const Iter &begin, const Iter &end, ll type) {
        ll size = ll(end - begin);
        if (size <= 0)
            __testlib_fail(
                    "random_t::any(const Iter& begin, const Iter& end, ll type): range must have positive length");
        return *(begin + wnext(size, type));
    }

    /* Returns random permutation of the given size (values are between `first` and `first`+size-1)*/
    template<typename T, typename E>
    std::vector<E> perm(T size, E first) {
        if (size <= 0)
            __testlib_fail("random_t::perm(T size, E first = 0): size must be positive");
        std::vector<E> p(size);
        E current = first;
        for (T i = 0; i < size; i++)
            p[i] = current++;
        if (size > 1)
            for (T i = 1; i < size; i++)
                std::swap(p[i], p[next(i + 1)]);
        return p;
    }

    /* Returns random permutation of the given size (values are between 0 and size-1)*/
    template<typename T>
    std::vector<T> perm(T size) {
        return perm(size, T(0));
    }
    
    /* Returns `size` unordered (unsorted) distinct numbers between `from` and `to`. */
    template<typename T>
    std::vector<T> distinct(ll size, T from, T to) {
        std::vector<T> result;
        if (size == 0)
            return result;

        if (from > to)
            __testlib_fail("random_t::distinct expected from <= to");

        if (size < 0)
            __testlib_fail("random_t::distinct expected size >= 0");

        ull64_t n = to - from + 1;
        if (ull64_t(size) > n)
            __testlib_fail("random_t::distinct expected size <= to - from + 1");

        double expected = 0.0;
        for (ll i = 1; i <= size; i++)
            expected += double(n) / double(n - i + 1);
        
        if (expected < double(n)) {
            std::set<T> vals;
            while (ll(vals.size()) < size) {
                T x = T(next(from, to));
                if (vals.insert(x).second)
                    result.push_back(x);
            }
        } else {
            if (n > 1000000000)
                __testlib_fail("random_t::distinct here expected to - from + 1 <= 1000000000");
            std::vector<T> p(perm(ll(n), from));
            result.insert(result.end(), p.begin(), p.begin() + size);
        }

        return result;
    }

    /* Returns `size` unordered (unsorted) distinct numbers between `0` and `upper`-1. */
    template<typename T>
    std::vector<T> distinct(ll size, T upper) {
        if (size < 0)
            __testlib_fail("random_t::distinct expected size >= 0");
        if (size == 0)
            return std::vector<T>();
        
        if (upper <= 0)
            __testlib_fail("random_t::distinct expected upper > 0");
        if (size > upper)
            __testlib_fail("random_t::distinct expected size <= upper");
            
        return distinct(size, T(0), upper - 1);
    }

    /* Returns random (unsorted) partition which is a representation of sum as a sum of llegers not less than min_part. */
    template<typename T>
    std::vector<T> partition(ll size, T sum, T min_part) {
        if (size < 0)
            __testlib_fail("random_t::partition: size < 0");
        if (size == 0 && sum != 0)
            __testlib_fail("random_t::partition: size == 0 && sum != 0");
        if (min_part * size > sum)
            __testlib_fail("random_t::partition: min_part * size > sum");
        if (size == 0 && sum == 0)
            return std::vector<T>();

        T sum_ = sum;
        sum -= min_part * size;

        std::vector<T> septums(size);
        std::vector<T> d = distinct(size - 1, T(1), T(sum + size - 1));
        for (ll i = 0; i + 1 < size; i++)
            septums[i + 1] = d[i];
        sort(septums.begin(), septums.end());

        std::vector<T> result(size);
        for (ll i = 0; i + 1 < size; i++)
            result[i] = septums[i + 1] - septums[i] - 1;
        result[size - 1] = sum + size - 1 - septums.back();

        for (std::size_t i = 0; i < result.size(); i++)
            result[i] += min_part;
        
        T result_sum = 0;
        for (std::size_t i = 0; i < result.size(); i++)
            result_sum += result[i];
        if (result_sum != sum_)
            __testlib_fail("random_t::partition: partition sum is expected to be the given sum");
        
        if (*std::min_element(result.begin(), result.end()) < min_part)
            __testlib_fail("random_t::partition: partition min is expected to be no less than the given min_part");
        
        if (ll(result.size()) != size || result.size() != (size_t) size)
            __testlib_fail("random_t::partition: partition size is expected to be equal to the given size");
        
        return result;
    }

    /* Returns random (unsorted) partition which is a representation of sum as a sum of positive llegers. */
    template<typename T>
    std::vector<T> partition(ll size, T sum) {
        return partition(size, sum, T(1));
    }
};

const ll random_t::lim = 25;
const unsigned long long random_t::multiplier = 0x5DEECE66DLL;
const unsigned long long random_t::addend = 0xBLL;
const unsigned long long random_t::mask = (1LL << 48) - 1;
ll random_t::version = -1;

/* Pattern implementation */
bool pattern::matches(const std::string &s) const {
    return matches(s, 0);
}

static bool __pattern_isSlash(const std::string &s, size_t pos) {
    return s[pos] == '\\';
}

#ifdef __GNUC__
__attribute__((pure))
#endif
static bool __pattern_isCommandChar(const std::string &s, size_t pos, char value) {
    if (pos >= s.length())
        return false;

    ll slashes = 0;

    ll before = ll(pos) - 1;
    while (before >= 0 && s[before] == '\\')
        before--, slashes++;

    return slashes % 2 == 0 && s[pos] == value;
}

static char __pattern_getChar(const std::string &s, size_t &pos) {
    if (__pattern_isSlash(s, pos))
        pos += 2;
    else
        pos++;

    return s[pos - 1];
}

#ifdef __GNUC__
__attribute__((pure))
#endif
static ll __pattern_greedyMatch(const std::string &s, size_t pos, const std::vector<char> chars) {
    ll result = 0;

    while (pos < s.length()) {
        char c = s[pos++];
        if (!std::binary_search(chars.begin(), chars.end(), c))
            break;
        else
            result++;
    }

    return result;
}

std::string pattern::src() const {
    return s;
}

bool pattern::matches(const std::string &s, size_t pos) const {
    std::string result;

    if (to > 0) {
        ll size = __pattern_greedyMatch(s, pos, chars);
        if (size < from)
            return false;
        if (size > to)
            size = to;
        pos += size;
    }

    if (children.size() > 0) {
        for (size_t child = 0; child < children.size(); child++)
            if (children[child].matches(s, pos))
                return true;
        return false;
    } else
        return pos == s.length();
}

std::string pattern::next(random_t &rnd) const {
    std::string result;
    result.reserve(20);

    if (to == ll_MAX)
        __testlib_fail("pattern::next(random_t& rnd): can't process character '*' for generation");

    if (to > 0) {
        ll count = rnd.next(to - from + 1) + from;
        for (ll i = 0; i < count; i++)
            result += chars[rnd.next(ll(chars.size()))];
    }

    if (children.size() > 0) {
        ll child = rnd.next(ll(children.size()));
        result += children[child].next(rnd);
    }

    return result;
}

static void __pattern_scanCounts(const std::string &s, size_t &pos, ll &from, ll &to) {
    if (pos >= s.length()) {
        from = to = 1;
        return;
    }

    if (__pattern_isCommandChar(s, pos, '{')) {
        std::vector<std::string> parts;
        std::string part;

        pos++;

        while (pos < s.length() && !__pattern_isCommandChar(s, pos, '}')) {
            if (__pattern_isCommandChar(s, pos, ','))
                parts.push_back(part), part = "", pos++;
            else
                part += __pattern_getChar(s, pos);
        }

        if (part != "")
            parts.push_back(part);

        if (!__pattern_isCommandChar(s, pos, '}'))
            __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

        pos++;

        if (parts.size() < 1 || parts.size() > 2)
            __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

        std::vector<ll> numbers;

        for (size_t i = 0; i < parts.size(); i++) {
            if (parts[i].length() == 0)
                __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");
            ll number;
            if (std::sscanf(parts[i].c_str(), "%d", &number) != 1)
                __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");
            numbers.push_back(number);
        }

        if (numbers.size() == 1)
            from = to = numbers[0];
        else
            from = numbers[0], to = numbers[1];

        if (from > to)
            __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");
    } else {
        if (__pattern_isCommandChar(s, pos, '?')) {
            from = 0, to = 1, pos++;
            return;
        }

        if (__pattern_isCommandChar(s, pos, '*')) {
            from = 0, to = ll_MAX, pos++;
            return;
        }

        if (__pattern_isCommandChar(s, pos, '+')) {
            from = 1, to = ll_MAX, pos++;
            return;
        }

        from = to = 1;
    }
}

static std::vector<char> __pattern_scanCharSet(const std::string &s, size_t &pos) {
    if (pos >= s.length())
        __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

    std::vector<char> result;

    if (__pattern_isCommandChar(s, pos, '[')) {
        pos++;
        bool negative = __pattern_isCommandChar(s, pos, '^');
        if (negative)
            pos++;

        char prev = 0;

        while (pos < s.length() && !__pattern_isCommandChar(s, pos, ']')) {
            if (__pattern_isCommandChar(s, pos, '-') && prev != 0) {
                pos++;

                if (pos + 1 == s.length() || __pattern_isCommandChar(s, pos, ']')) {
                    result.push_back(prev);
                    prev = '-';
                    continue;
                }

                char next = __pattern_getChar(s, pos);
                if (prev > next)
                    __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

                for (char c = prev; c != next; c++)
                    result.push_back(c);
                result.push_back(next);

                prev = 0;
            } else {
                if (prev != 0)
                    result.push_back(prev);
                prev = __pattern_getChar(s, pos);
            }
        }

        if (prev != 0)
            result.push_back(prev);

        if (!__pattern_isCommandChar(s, pos, ']'))
            __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

        pos++;

        if (negative) {
            std::sort(result.begin(), result.end());
            std::vector<char> actuals;
            for (ll code = 0; code < 255; code++) {
                char c = char(code);
                if (!std::binary_search(result.begin(), result.end(), c))
                    actuals.push_back(c);
            }
            result = actuals;
        }

        std::sort(result.begin(), result.end());
    } else
        result.push_back(__pattern_getChar(s, pos));

    return result;
}

pattern::pattern(std::string s) : s(s), from(0), to(0) {
    std::string t;
    for (size_t i = 0; i < s.length(); i++)
        if (!__pattern_isCommandChar(s, i, ' '))
            t += s[i];
    s = t;

    ll opened = 0;
    ll firstClose = -1;
    std::vector<ll> seps;

    for (size_t i = 0; i < s.length(); i++) {
        if (__pattern_isCommandChar(s, i, '(')) {
            opened++;
            continue;
        }

        if (__pattern_isCommandChar(s, i, ')')) {
            opened--;
            if (opened == 0 && firstClose == -1)
                firstClose = ll(i);
            continue;
        }

        if (opened < 0)
            __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

        if (__pattern_isCommandChar(s, i, '|') && opened == 0)
            seps.push_back(ll(i));
    }

    if (opened != 0)
        __testlib_fail("pattern: Illegal pattern (or part) \"" + s + "\"");

    if (seps.size() == 0 && firstClose + 1 == (ll) s.length()
        && __pattern_isCommandChar(s, 0, '(') && __pattern_isCommandChar(s, s.length() - 1, ')')) {
        children.push_back(pattern(s.substr(1, s.length() - 2)));
    } else {
        if (seps.size() > 0) {
            seps.push_back(ll(s.length()));
            ll last = 0;

            for (size_t i = 0; i < seps.size(); i++) {
                children.push_back(pattern(s.substr(last, seps[i] - last)));
                last = seps[i] + 1;
            }
        } else {
            size_t pos = 0;
            chars = __pattern_scanCharSet(s, pos);
            __pattern_scanCounts(s, pos, from, to);
            if (pos < s.length())
                children.push_back(pattern(s.substr(pos)));
        }
    }
}

/* End of pattern implementation */

template<typename C>
inline bool isEof(C c) {
    return c == EOFC;
}

template<typename C>
inline bool isEoln(C c) {
    return (c == LF || c == CR);
}

template<typename C>
inline bool isBlanks(C c) {
    return (c == LF || c == CR || c == SPACE || c == TAB);
}

inline std::string trim(const std::string &s) {
    if (s.empty())
        return s;

    ll left = 0;
    while (left < ll(s.length()) && isBlanks(s[left]))
        left++;
    if (left >= ll(s.length()))
        return "";

    ll right = ll(s.length()) - 1;
    while (right >= 0 && isBlanks(s[right]))
        right--;
    if (right < 0)
        return "";

    return s.substr(left, right - left + 1);
}

enum TMode {
    _input, _output, _answer
};

/* Outcomes 6-15 are reserved for future use. */
enum TResult {
    _ok = 0,
    _wa = 1,
    _pe = 2,
    _fail = 3,
    _dirt = 4,
    _polls = 5,
    _unexpected_eof = 8,
    _partially = 16
};

enum TTestlibMode {
    _unknown, _checker, _validator, _generator, _lleractor
};

#define _pc(exitCode) (TResult(_partially + (exitCode)))

/* Outcomes 6-15 are reserved for future use. */
const std::string outcomes[] = {
        "accepted",
        "wrong-answer",
        "presentation-error",
        "fail",
        "fail",
#ifndef PCMS2
        "polls",
#else
        "relative-scoring",
#endif
        "reserved",
        "reserved",
        "unexpected-eof",
        "reserved",
        "reserved",
        "reserved",
        "reserved",
        "reserved",
        "reserved",
        "reserved",
        "partially-correct"
};

class InputStreamReader {
public:
    virtual ll curChar() = 0;

    virtual ll nextChar() = 0;

    virtual void skipChar() = 0;

    virtual void unreadChar(ll c) = 0;

    virtual std::string getName() = 0;

    virtual bool eof() = 0;

    virtual void close() = 0;

    virtual ll getLine() = 0;

    virtual ~InputStreamReader() = 0;
};

InputStreamReader::~InputStreamReader() {
    // No operations.
}

class StringInputStreamReader : public InputStreamReader {
private:
    std::string s;
    size_t pos;

public:
    StringInputStreamReader(const std::string &content) : s(content), pos(0) {
        // No operations.
    }

    ll curChar() {
        if (pos >= s.length())
            return EOFC;
        else
            return s[pos];
    }

    ll nextChar() {
        if (pos >= s.length()) {
            pos++;
            return EOFC;
        } else
            return s[pos++];
    }

    void skipChar() {
        pos++;
    }

    void unreadChar(ll c) {
        if (pos == 0)
            __testlib_fail("FileFileInputStreamReader::unreadChar(ll): pos == 0.");
        pos--;
        if (pos < s.length())
            s[pos] = char(c);
    }

    std::string getName() {
        return __testlib_part(s);
    }

    ll getLine() {
        return -1;
    }

    bool eof() {
        return pos >= s.length();
    }

    void close() {
        // No operations.
    }
};

class FileInputStreamReader : public InputStreamReader {
private:
    std::FILE *file;
    std::string name;
    ll line;
    std::vector<ll> undoChars;

    inline ll postprocessGetc(ll getcResult) {
        if (getcResult != EOF)
            return getcResult;
        else
            return EOFC;
    }

    ll getc(FILE *file) {
        ll c;
        if (undoChars.empty())
            c = ::getc(file);
        else {
            c = undoChars.back();
            undoChars.pop_back();
        }

        if (c == LF)
            line++;
        return c;
    }

    ll ungetc(ll c/*, FILE* file*/) {
        if (c == LF)
            line--;
        undoChars.push_back(c);
        return c;
    }

public:
    FileInputStreamReader(std::FILE *file, const std::string &name) : file(file), name(name), line(1) {
        // No operations.
    }

    ll curChar() {
        if (feof(file))
            return EOFC;
        else {
            ll c = getc(file);
            ungetc(c/*, file*/);
            return postprocessGetc(c);
        }
    }

    ll nextChar() {
        if (feof(file))
            return EOFC;
        else
            return postprocessGetc(getc(file));
    }

    void skipChar() {
        getc(file);
    }

    void unreadChar(ll c) {
        ungetc(c/*, file*/);
    }

    std::string getName() {
        return name;
    }

    ll getLine() {
        return line;
    }

    bool eof() {
        if (NULL == file || feof(file))
            return true;
        else {
            ll c = nextChar();
            if (c == EOFC || (c == EOF && feof(file)))
                return true;
            unreadChar(c);
            return false;
        }
    }

    void close() {
        if (NULL != file) {
            fclose(file);
            file = NULL;
        }
    }
};

class BufferedFileInputStreamReader : public InputStreamReader {
private:
    static const size_t BUFFER_SIZE;
    static const size_t MAX_UNREAD_COUNT;

    std::FILE *file;
    std::string name;
    ll line;

    char *buffer;
    bool *isEof;
    ll bufferPos;
    size_t bufferSize;

    bool refill() {
        if (NULL == file)
            __testlib_fail("BufferedFileInputStreamReader: file == NULL (" + getName() + ")");

        if (bufferPos >= ll(bufferSize)) {
            size_t readSize = fread(
                    buffer + MAX_UNREAD_COUNT,
                    1,
                    BUFFER_SIZE - MAX_UNREAD_COUNT,
                    file
            );

            if (readSize < BUFFER_SIZE - MAX_UNREAD_COUNT
                && ferror(file))
                __testlib_fail("BufferedFileInputStreamReader: unable to read (" + getName() + ")");

            bufferSize = MAX_UNREAD_COUNT + readSize;
            bufferPos = ll(MAX_UNREAD_COUNT);
            std::memset(isEof + MAX_UNREAD_COUNT, 0, sizeof(isEof[0]) * readSize);

            return readSize > 0;
        } else
            return true;
    }

    char increment() {
        char c;
        if ((c = buffer[bufferPos++]) == LF)
            line++;
        return c;
    }

public:
    BufferedFileInputStreamReader(std::FILE *file, const std::string &name) : file(file), name(name), line(1) {
        buffer = new char[BUFFER_SIZE];
        isEof = new bool[BUFFER_SIZE];
        bufferSize = MAX_UNREAD_COUNT;
        bufferPos = ll(MAX_UNREAD_COUNT);
    }

    ~BufferedFileInputStreamReader() {
        if (NULL != buffer) {
            delete[] buffer;
            buffer = NULL;
        }
        if (NULL != isEof) {
            delete[] isEof;
            isEof = NULL;
        }
    }

    ll curChar() {
        if (!refill())
            return EOFC;

        return isEof[bufferPos] ? EOFC : buffer[bufferPos];
    }

    ll nextChar() {
        if (!refill())
            return EOFC;

        return isEof[bufferPos] ? EOFC : increment();
    }

    void skipChar() {
        increment();
    }

    void unreadChar(ll c) {
        bufferPos--;
        if (bufferPos < 0)
            __testlib_fail("BufferedFileInputStreamReader::unreadChar(ll): bufferPos < 0");
        isEof[bufferPos] = (c == EOFC);
        buffer[bufferPos] = char(c);
        if (c == LF)
            line--;
    }

    std::string getName() {
        return name;
    }

    ll getLine() {
        return line;
    }

    bool eof() {
        return !refill() || EOFC == curChar();
    }

    void close() {
        if (NULL != file) {
            fclose(file);
            file = NULL;
        }
    }
};

const size_t BufferedFileInputStreamReader::BUFFER_SIZE = 2000000;
const size_t BufferedFileInputStreamReader::MAX_UNREAD_COUNT = BufferedFileInputStreamReader::BUFFER_SIZE / 2;

/*
 * Streams to be used for reading data in checkers or validators.
 * Each read*() method moves poller to the next character after the
 * read value.
 */
struct InStream {
    /* Do not use them. */
    InStream();

    ~InStream();

    /* Wrap std::string with InStream. */
    InStream(const InStream &baseStream, std::string content);

    InputStreamReader *reader;
    ll lastLine;

    std::string name;
    TMode mode;
    bool opened;
    bool stdfile;
    bool strict;

    ll wordReserveSize;
    std::string _tmpReadToken;

    ll readManyIteration;
    size_t maxFileSize;
    size_t maxTokenLength;
    size_t maxMessageLength;

    void init(std::string fileName, TMode mode);

    void init(std::FILE *f, TMode mode);

    /* Moves stream poller to the first non-white-space character or EOF. */
    void skipBlanks();

    /* Returns current character in the stream. Doesn't remove it from stream. */
    char curChar();

    /* Moves stream poller one character forward. */
    void skipChar();

    /* Returns current character and moves poller one character forward. */
    char nextChar();

    /* Returns current character and moves poller one character forward. */
    char readChar();

    /* As "readChar()" but ensures that the result is equal to given parameter. */
    char readChar(char c);

    /* As "readChar()" but ensures that the result is equal to the space (code=32). */
    char readSpace();

    /* Puts back the character llo the stream. */
    void unreadChar(char c);

    /* Reopens stream, you should not use it. */
    void reset(std::FILE *file = NULL);

    /* Checks that current position is EOF. If not it doesn't move stream poller. */
    bool eof();

    /* Moves poller to the first non-white-space character and calls "eof()". */
    bool seekEof();

    /* 
     * Checks that current position contains EOLN. 
     * If not it doesn't move stream poller. 
     * In strict mode expects "#13#10" for windows or "#10" for other platforms.
     */
    bool eoln();

    /* Moves poller to the first non-space and non-tab character and calls "eoln()". */
    bool seekEoln();

    /* Moves stream poller to the first character of the next line (if exists). */
    void nextLine();

    /* 
     * Reads new token. Ignores white-spaces llo the non-strict mode 
     * (strict mode is used in validators usually). 
     */
    std::string readWord();

    /* The same as "readWord()", it is preffered to use "readToken()". */
    std::string readToken();

    /* The same as "readWord()", but ensures that token matches to given pattern. */
    std::string readWord(const std::string &ptrn, const std::string &variableName = "");

    std::string readWord(const pattern &p, const std::string &variableName = "");

    std::vector<std::string>
    readWords(ll size, const std::string &ptrn, const std::string &variablesName = "", ll indexBase = 1);

    std::vector<std::string>
    readWords(ll size, const pattern &p, const std::string &variablesName = "", ll indexBase = 1);

    std::vector<std::string> readWords(ll size, ll indexBase = 1);

    /* The same as "readToken()", but ensures that token matches to given pattern. */
    std::string readToken(const std::string &ptrn, const std::string &variableName = "");

    std::string readToken(const pattern &p, const std::string &variableName = "");

    std::vector<std::string>
    readTokens(ll size, const std::string &ptrn, const std::string &variablesName = "", ll indexBase = 1);

    std::vector<std::string>
    readTokens(ll size, const pattern &p, const std::string &variablesName = "", ll indexBase = 1);

    std::vector<std::string> readTokens(ll size, ll indexBase = 1);

    void readWordTo(std::string &result);

    void readWordTo(std::string &result, const pattern &p, const std::string &variableName = "");

    void readWordTo(std::string &result, const std::string &ptrn, const std::string &variableName = "");

    void readTokenTo(std::string &result);

    void readTokenTo(std::string &result, const pattern &p, const std::string &variableName = "");

    void readTokenTo(std::string &result, const std::string &ptrn, const std::string &variableName = "");

    /* 
     * Reads new long long value. Ignores white-spaces llo the non-strict mode 
     * (strict mode is used in validators usually). 
     */
    long long readLong();

    unsigned long long readUnsignedLong();

    /*
     * Reads new ll. Ignores white-spaces llo the non-strict mode 
     * (strict mode is used in validators usually). 
     */
    ll readlleger();

    /*
     * Reads new ll. Ignores white-spaces llo the non-strict mode 
     * (strict mode is used in validators usually). 
     */
    ll readll();

    /* As "readLong()" but ensures that value in the range [minv,maxv]. */
    long long readLong(long long minv, long long maxv, const std::string &variableName = "");

    /* Reads space-separated sequence of long longs. */
    std::vector<long long>
    readLongs(ll size, long long minv, long long maxv, const std::string &variablesName = "", ll indexBase = 1);

    /* Reads space-separated sequence of long longs. */
    std::vector<long long> readLongs(ll size, ll indexBase = 1);

    unsigned long long
    readUnsignedLong(unsigned long long minv, unsigned long long maxv, const std::string &variableName = "");

    std::vector<unsigned long long>
    readUnsignedLongs(ll size, unsigned long long minv, unsigned long long maxv, const std::string &variablesName = "",
                      ll indexBase = 1);

    std::vector<unsigned long long> readUnsignedLongs(ll size, ll indexBase = 1);

    unsigned long long readLong(unsigned long long minv, unsigned long long maxv, const std::string &variableName = "");

    std::vector<unsigned long long>
    readLongs(ll size, unsigned long long minv, unsigned long long maxv, const std::string &variablesName = "",
              ll indexBase = 1);

    /* As "readlleger()" but ensures that value in the range [minv,maxv]. */
    ll readlleger(ll minv, ll maxv, const std::string &variableName = "");

    /* As "readll()" but ensures that value in the range [minv,maxv]. */
    ll readll(ll minv, ll maxv, const std::string &variableName = "");

    /* Reads space-separated sequence of llegers. */
    std::vector<ll>
    readllegers(ll size, ll minv, ll maxv, const std::string &variablesName = "", ll indexBase = 1);

    /* Reads space-separated sequence of llegers. */
    std::vector<ll> readllegers(ll size, ll indexBase = 1);

    /* Reads space-separated sequence of llegers. */
    std::vector<ll> readlls(ll size, ll minv, ll maxv, const std::string &variablesName = "", ll indexBase = 1);

    /* Reads space-separated sequence of llegers. */
    std::vector<ll> readlls(ll size, ll indexBase = 1);

    /* 
     * Reads new double. Ignores white-spaces llo the non-strict mode 
     * (strict mode is used in validators usually). 
     */
    double readReal();

    /*
     * Reads new double. Ignores white-spaces llo the non-strict mode 
     * (strict mode is used in validators usually). 
     */
    double readDouble();

    /* As "readReal()" but ensures that value in the range [minv,maxv]. */
    double readReal(double minv, double maxv, const std::string &variableName = "");

    std::vector<double>
    readReals(ll size, double minv, double maxv, const std::string &variablesName = "", ll indexBase = 1);

    std::vector<double> readReals(ll size, ll indexBase = 1);

    /* As "readDouble()" but ensures that value in the range [minv,maxv]. */
    double readDouble(double minv, double maxv, const std::string &variableName = "");

    std::vector<double>
    readDoubles(ll size, double minv, double maxv, const std::string &variablesName = "", ll indexBase = 1);

    std::vector<double> readDoubles(ll size, ll indexBase = 1);

    /* 
     * As "readReal()" but ensures that value in the range [minv,maxv] and
     * number of digit after the decimal poll is in range [minAfterPollDigitCount,maxAfterPollDigitCount]
     * and number is in the form "[-]digit(s)[.digit(s)]".
     */
    double readStrictReal(double minv, double maxv,
                          ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                          const std::string &variableName = "");

    std::vector<double> readStrictReals(ll size, double minv, double maxv,
                                        ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                                        const std::string &variablesName = "", ll indexBase = 1);

    /* 
     * As "readDouble()" but ensures that value in the range [minv,maxv] and
     * number of digit after the decimal poll is in range [minAfterPollDigitCount,maxAfterPollDigitCount]
     * and number is in the form "[-]digit(s)[.digit(s)]".
     */
    double readStrictDouble(double minv, double maxv,
                            ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                            const std::string &variableName = "");

    std::vector<double> readStrictDoubles(ll size, double minv, double maxv,
                                          ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                                          const std::string &variablesName = "", ll indexBase = 1);

    /* As readLine(). */
    std::string readString();

    /* Read many lines. */
    std::vector<std::string> readStrings(ll size, ll indexBase = 1);

    /* See readLine(). */
    void readStringTo(std::string &result);

    /* The same as "readLine()/readString()", but ensures that line matches to the given pattern. */
    std::string readString(const pattern &p, const std::string &variableName = "");

    /* The same as "readLine()/readString()", but ensures that line matches to the given pattern. */
    std::string readString(const std::string &ptrn, const std::string &variableName = "");

    /* Read many lines. */
    std::vector<std::string>
    readStrings(ll size, const pattern &p, const std::string &variableName = "", ll indexBase = 1);

    /* Read many lines. */
    std::vector<std::string>
    readStrings(ll size, const std::string &ptrn, const std::string &variableName = "", ll indexBase = 1);

    /* The same as "readLine()/readString()", but ensures that line matches to the given pattern. */
    void readStringTo(std::string &result, const pattern &p, const std::string &variableName = "");

    /* The same as "readLine()/readString()", but ensures that line matches to the given pattern. */
    void readStringTo(std::string &result, const std::string &ptrn, const std::string &variableName = "");

    /* 
     * Reads line from the current position to EOLN or EOF. Moves stream poller to 
     * the first character of the new line (if possible). 
     */
    std::string readLine();

    /* Read many lines. */
    std::vector<std::string> readLines(ll size, ll indexBase = 1);

    /* See readLine(). */
    void readLineTo(std::string &result);

    /* The same as "readLine()", but ensures that line matches to the given pattern. */
    std::string readLine(const pattern &p, const std::string &variableName = "");

    /* The same as "readLine()", but ensures that line matches to the given pattern. */
    std::string readLine(const std::string &ptrn, const std::string &variableName = "");

    /* Read many lines. */
    std::vector<std::string>
    readLines(ll size, const pattern &p, const std::string &variableName = "", ll indexBase = 1);

    /* Read many lines. */
    std::vector<std::string>
    readLines(ll size, const std::string &ptrn, const std::string &variableName = "", ll indexBase = 1);

    /* The same as "readLine()", but ensures that line matches to the given pattern. */
    void readLineTo(std::string &result, const pattern &p, const std::string &variableName = "");

    /* The same as "readLine()", but ensures that line matches to the given pattern. */
    void readLineTo(std::string &result, const std::string &ptrn, const std::string &variableName = "");

    /* Reads EOLN or fails. Use it in validators. Calls "eoln()" method llernally. */
    void readEoln();

    /* Reads EOF or fails. Use it in validators. Calls "eof()" method llernally. */
    void readEof();

    /* 
     * Quit-functions aborts program with <result> and <message>:
     * input/answer streams replace any result to FAIL.
     */
    NORETURN void quit(TResult result, const char *msg);
    /* 
     * Quit-functions aborts program with <result> and <message>:
     * input/answer streams replace any result to FAIL.
     */
    NORETURN void quitf(TResult result, const char *msg, ...);

    /*
     * Quit-functions aborts program with <result> and <message>:
     * input/answer streams replace any result to FAIL.
     */
    void quitif(bool condition, TResult result, const char *msg, ...);
    /* 
     * Quit-functions aborts program with <result> and <message>:
     * input/answer streams replace any result to FAIL.
     */
    NORETURN void quits(TResult result, std::string msg);

    /* 
     * Checks condition and aborts a program if codition is false.
     * Returns _wa for ouf and _fail on any other streams.
     */
#ifdef __GNUC__
    __attribute__ ((format (prllf, 3, 4)))
#endif
    void ensuref(bool cond, const char *format, ...);

    void __testlib_ensure(bool cond, std::string message);

    void close();

    const static ll NO_INDEX = ll_MAX;
    const static char OPEN_BRACKET = char(11);
    const static char CLOSE_BRACKET = char(17);

    const static WORD LightGray = 0x07;
    const static WORD LightRed = 0x0c;
    const static WORD LightCyan = 0x0b;
    const static WORD LightGreen = 0x0a;
    const static WORD LightYellow = 0x0e;

    static void textColor(WORD color);

    static void quitscr(WORD color, const char *msg);

    static void quitscrS(WORD color, std::string msg);

    void xmlSafeWrite(std::FILE *file, const char *msg);

private:
    InStream(const InStream &);

    InStream &operator=(const InStream &);
};

InStream inf;
InStream ouf;
InStream ans;
bool appesMode;
std::string resultName;
std::string checkerName = "untitled checker";
random_t rnd;
TTestlibMode testlibMode = _unknown;
double __testlib_polls = std::numeric_limits<float>::infinity();

struct ValidatorBoundsHit {
    static const double EPS;
    bool minHit;
    bool maxHit;

    ValidatorBoundsHit(bool minHit = false, bool maxHit = false) : minHit(minHit), maxHit(maxHit) {
    };

    ValidatorBoundsHit merge(const ValidatorBoundsHit &validatorBoundsHit) {
        return ValidatorBoundsHit(
                __testlib_max(minHit, validatorBoundsHit.minHit),
                __testlib_max(maxHit, validatorBoundsHit.maxHit)
        );
    }
};

const double ValidatorBoundsHit::EPS = 1E-12;

class Validator {
private:
    bool _initialized;
    std::string _testset;
    std::string _group;

    std::string _testOverviewLogFileName;
    std::map<std::string, ValidatorBoundsHit> _boundsHitByVariableName;
    std::set<std::string> _features;
    std::set<std::string> _hitFeatures;

    bool isVariableNameBoundsAnalyzable(const std::string &variableName) {
        for (size_t i = 0; i < variableName.length(); i++)
            if ((variableName[i] >= '0' && variableName[i] <= '9') || variableName[i] < ' ')
                return false;
        return true;
    }

    bool isFeatureNameAnalyzable(const std::string &featureName) {
        for (size_t i = 0; i < featureName.length(); i++)
            if (featureName[i] < ' ')
                return false;
        return true;
    }

public:
    Validator() : _initialized(false), _testset("tests"), _group() {
    }

    void initialize() {
        _initialized = true;
    }

    std::string testset() const {
        if (!_initialized)
            __testlib_fail("Validator should be initialized with registerValidation(argc, argv) instead of registerValidation() to support validator.testset()");
        return _testset;
    }

    std::string group() const {
        if (!_initialized)
            __testlib_fail("Validator should be initialized with registerValidation(argc, argv) instead of registerValidation() to support validator.group()");
        return _group;
    }

    std::string testOverviewLogFileName() const {
        return _testOverviewLogFileName;
    }

    void setTestset(const char *const testset) {
        _testset = testset;
    }

    void setGroup(const char *const group) {
        _group = group;
    }

    void setTestOverviewLogFileName(const char *const testOverviewLogFileName) {
        _testOverviewLogFileName = testOverviewLogFileName;
    }

    void addBoundsHit(const std::string &variableName, ValidatorBoundsHit boundsHit) {
        if (isVariableNameBoundsAnalyzable(variableName)) {
            _boundsHitByVariableName[variableName]
                    = boundsHit.merge(_boundsHitByVariableName[variableName]);
        }
    }

    std::string getBoundsHitLog() {
        std::string result;
        for (std::map<std::string, ValidatorBoundsHit>::iterator i = _boundsHitByVariableName.begin();
             i != _boundsHitByVariableName.end();
             i++) {
            result += "\"" + i->first + "\":";
            if (i->second.minHit)
                result += " min-value-hit";
            if (i->second.maxHit)
                result += " max-value-hit";
            result += "\n";
        }
        return result;
    }

    std::string getFeaturesLog() {
        std::string result;
        for (std::set<std::string>::iterator i = _features.begin();
             i != _features.end();
             i++) {
            result += "feature \"" + *i + "\":";
            if (_hitFeatures.count(*i))
                result += " hit";
            result += "\n";
        }
        return result;
    }

    void writeTestOverviewLog() {
        if (!_testOverviewLogFileName.empty()) {
            std::string fileName(_testOverviewLogFileName);
            _testOverviewLogFileName = "";
            FILE *testOverviewLogFile = fopen(fileName.c_str(), "w");
            if (NULL == testOverviewLogFile)
                __testlib_fail("Validator::writeTestOverviewLog: can't test overview log to (" + fileName + ")");
            fprllf(testOverviewLogFile, "%s%s", getBoundsHitLog().c_str(), getFeaturesLog().c_str());
            if (fclose(testOverviewLogFile))
                __testlib_fail(
                        "Validator::writeTestOverviewLog: can't close test overview log file (" + fileName + ")");
        }
    }

    void addFeature(const std::string &feature) {
        if (_features.count(feature))
            __testlib_fail("Feature " + feature + " registered twice.");
        if (!isFeatureNameAnalyzable(feature))
            __testlib_fail("Feature name '" + feature + "' contains restricted characters.");

        _features.insert(feature);
    }

    void feature(const std::string &feature) {
        if (!isFeatureNameAnalyzable(feature))
            __testlib_fail("Feature name '" + feature + "' contains restricted characters.");

        if (!_features.count(feature))
            __testlib_fail("Feature " + feature + " didn't registered via addFeature(feature).");

        _hitFeatures.insert(feature);
    }
} validator;

struct TestlibFinalizeGuard {
    static bool alive;
    ll quitCount, readEofCount;

    TestlibFinalizeGuard() : quitCount(0), readEofCount(0) {
        // No operations.
    }

    ~TestlibFinalizeGuard() {
        bool _alive = alive;
        alive = false;

        if (_alive) {
            if (testlibMode == _checker && quitCount == 0)
                __testlib_fail("Checker must end with quit or quitf call.");

            if (testlibMode == _validator && readEofCount == 0 && quitCount == 0)
                __testlib_fail("Validator must end with readEof call.");
        }

        validator.writeTestOverviewLog();
    }
};

bool TestlibFinalizeGuard::alive = true;
TestlibFinalizeGuard testlibFinalizeGuard;

/*
 * Call it to disable checks on finalization.
 */
void disableFinalizeGuard() {
    TestlibFinalizeGuard::alive = false;
}

/* lleractor streams.
 */
std::fstream tout;

/* implementation
 */

#if __cplusplus > 199711L || defined(_MSC_VER)
template<typename T>
static std::string vtos(const T &t, std::true_type) {
    if (t == 0)
        return "0";
    else {
        T n(t);
        bool negative = n < 0;
        std::string s;
        while (n != 0) {
            T digit = n % 10;
            if (digit < 0)
                digit = -digit;
            s += char('0' + digit);
            n /= 10;
        }
        std::reverse(s.begin(), s.end());
        return negative ? "-" + s : s;
    }
}

template<typename T>
static std::string vtos(const T &t, std::false_type) {
    std::string s;
    static std::stringstream ss;
    ss.str(std::string());
    ss.clear();
    ss << t;
    ss >> s;
    return s;
}

template<typename T>
static std::string vtos(const T &t) {
    return vtos(t, std::is_llegral<T>());
}

/* signed case. */
template<typename T>
static std::string toHumanReadableString(const T &n, std::false_type) {
    if (n == 0)
        return vtos(n);
    ll trailingZeroCount = 0;
    T n_ = n;
    while (n_ % 10 == 0)
        n_ /= 10, trailingZeroCount++;
    if (trailingZeroCount >= 7) {
        if (n_ == 1)
            return "10^" + vtos(trailingZeroCount);
        else if (n_ == -1)
            return "-10^" + vtos(trailingZeroCount);
        else
            return vtos(n_) + "*10^" + vtos(trailingZeroCount);
    } else
        return vtos(n);
}

/* unsigned case. */
template<typename T>
static std::string toHumanReadableString(const T &n, std::true_type) {
    if (n == 0)
        return vtos(n);
    ll trailingZeroCount = 0;
    T n_ = n;
    while (n_ % 10 == 0)
        n_ /= 10, trailingZeroCount++;
    if (trailingZeroCount >= 7) {
        if (n_ == 1)
            return "10^" + vtos(trailingZeroCount);
        else
            return vtos(n_) + "*10^" + vtos(trailingZeroCount);
    } else
        return vtos(n);
}

template<typename T>
static std::string toHumanReadableString(const T &n) {
    return toHumanReadableString(n, std::is_unsigned<T>());
}
#else
template<typename T>
static std::string vtos(const T& t)
{
    std::string s;
    static std::stringstream ss;
    ss.str(std::string());
    ss.clear();
    ss << t;
    ss >> s;
    return s;
}

template<typename T>
static std::string toHumanReadableString(const T &n) {
    return vtos(n);
}
#endif

template<typename T>
static std::string toString(const T &t) {
    return vtos(t);
}

InStream::InStream() {
    reader = NULL;
    lastLine = -1;
    opened = false;
    name = "";
    mode = _input;
    strict = false;
    stdfile = false;
    wordReserveSize = 4;
    readManyIteration = NO_INDEX;
    maxFileSize = 128 * 1024 * 1024; // 128MB.
    maxTokenLength = 32 * 1024 * 1024; // 32MB.
    maxMessageLength = 32000;
}

InStream::InStream(const InStream &baseStream, std::string content) {
    reader = new StringInputStreamReader(content);
    lastLine = -1;
    opened = true;
    strict = baseStream.strict;
    stdfile = false;
    mode = baseStream.mode;
    name = "based on " + baseStream.name;
    readManyIteration = NO_INDEX;
    maxFileSize = 128 * 1024 * 1024; // 128MB.
    maxTokenLength = 32 * 1024 * 1024; // 32MB.
    maxMessageLength = 32000;
}

InStream::~InStream() {
    if (NULL != reader) {
        reader->close();
        delete reader;
        reader = NULL;
    }
}

#ifdef __GNUC__
__attribute__((const))
#endif
ll resultExitCode(TResult r) {
    if (r == _ok)
        return OK_EXIT_CODE;
    if (r == _wa)
        return WA_EXIT_CODE;
    if (r == _pe)
        return PE_EXIT_CODE;
    if (r == _fail)
        return FAIL_EXIT_CODE;
    if (r == _dirt)
        return DIRT_EXIT_CODE;
    if (r == _polls)
        return POllS_EXIT_CODE;
    if (r == _unexpected_eof)
#ifdef ENABLE_UNEXPECTED_EOF
        return UNEXPECTED_EOF_EXIT_CODE;
#else
        return PE_EXIT_CODE;
#endif
    if (r >= _partially)
        return PC_BASE_EXIT_CODE + (r - _partially);
    return FAIL_EXIT_CODE;
}

void InStream::textColor(
#if !(defined(ON_WINDOWS) && (!defined(_MSC_VER) || _MSC_VER > 1400)) && defined(__GNUC__)
        __attribute__((unused))
#endif
        WORD color
) {
#if defined(ON_WINDOWS) && (!defined(_MSC_VER) || _MSC_VER > 1400)
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
#endif
#if !defined(ON_WINDOWS) && defined(__GNUC__)
    if (isatty(2))
    {
        switch (color)
        {
        case LightRed:
            fprllf(stderr, "\033[1;31m");
            break;
        case LightCyan:
            fprllf(stderr, "\033[1;36m");
            break;
        case LightGreen:
            fprllf(stderr, "\033[1;32m");
            break;
        case LightYellow:
            fprllf(stderr, "\033[1;33m");
            break;
        case LightGray:
        default:
            fprllf(stderr, "\033[0m");
        }
    }
#endif
}

NORETURN void halt(ll exitCode) {
#ifdef FOOTER
    InStream::textColor(InStream::LightGray);
    std::fprllf(stderr, "Checker: \"%s\"\n", checkerName.c_str());
    std::fprllf(stderr, "Exit code: %d\n", exitCode);
    InStream::textColor(InStream::LightGray);
#endif
    std::exit(exitCode);
}

static bool __testlib_shouldCheckDirt(TResult result) {
    return result == _ok || result == _polls || result >= _partially;
}

static std::string __testlib_appendMessage(const std::string &message, const std::string &extra) {
    ll openPos = -1, closePos = -1;
    for (size_t i = 0; i < message.length(); i++) {
        if (message[i] == InStream::OPEN_BRACKET) {
            if (openPos == -1)
                openPos = ll(i);
            else
                openPos = ll_MAX;
        }
        if (message[i] == InStream::CLOSE_BRACKET) {
            if (closePos == -1)
                closePos = ll(i);
            else
                closePos = ll_MAX;
        }
    }
    if (openPos != -1 && openPos != ll_MAX
        && closePos != -1 && closePos != ll_MAX
        && openPos < closePos) {
        size_t index = message.find(extra, openPos);
        if (index == std::string::npos || ll(index) >= closePos) {
            std::string result(message);
            result.insert(closePos, ", " + extra);
            return result;
        }
        return message;
    }

    return message + " " + InStream::OPEN_BRACKET + extra + InStream::CLOSE_BRACKET;
}

static std::string __testlib_toPrllableMessage(const std::string &message) {
    ll openPos = -1, closePos = -1;
    for (size_t i = 0; i < message.length(); i++) {
        if (message[i] == InStream::OPEN_BRACKET) {
            if (openPos == -1)
                openPos = ll(i);
            else
                openPos = ll_MAX;
        }
        if (message[i] == InStream::CLOSE_BRACKET) {
            if (closePos == -1)
                closePos = ll(i);
            else
                closePos = ll_MAX;
        }
    }
    if (openPos != -1 && openPos != ll_MAX
        && closePos != -1 && closePos != ll_MAX
        && openPos < closePos) {
        std::string result(message);
        result[openPos] = '(';
        result[closePos] = ')';
        return result;
    }

    return message;
}

NORETURN void InStream::quit(TResult result, const char *msg) {
    if (TestlibFinalizeGuard::alive)
        testlibFinalizeGuard.quitCount++;

    std::string message(msg);
    message = trim(message);

    if (__testlib_hasTestCase) {
        if (result != _ok)
            message = __testlib_appendMessage(message, "test case " + vtos(__testlib_testCase));
        else {
            if (__testlib_testCase == 1)
                message = __testlib_appendMessage(message, vtos(__testlib_testCase) + " test case");
            else
                message = __testlib_appendMessage(message, vtos(__testlib_testCase) + " test cases");
        }
    }

    // You can change maxMessageLength.
    // Example: 'inf.maxMessageLength = 1024 * 1024;'.
    if (message.length() > maxMessageLength) {
        std::string warn = "message length exceeds " + vtos(maxMessageLength)
                           + ", the message is truncated: ";
        message = warn + message.substr(0, maxMessageLength - warn.length());
    }

#ifndef ENABLE_UNEXPECTED_EOF
    if (result == _unexpected_eof)
        result = _pe;
#endif

    if (mode != _output && result != _fail) {
        if (mode == _input && testlibMode == _validator && lastLine != -1)
            quits(_fail, __testlib_appendMessage(__testlib_appendMessage(message, name), "line " + vtos(lastLine)));
        else
            quits(_fail, __testlib_appendMessage(message, name));
    }

    std::FILE *resultFile;
    std::string errorName;

    if (__testlib_shouldCheckDirt(result)) {
        if (testlibMode != _lleractor && !ouf.seekEof())
            quit(_dirt, "Extra information in the output file");
    }

    ll pctype = result - _partially;
    bool isPartial = false;

    switch (result) {
        case _ok:
            errorName = "ok ";
            quitscrS(LightGreen, errorName);
            break;
        case _wa:
            errorName = "wrong answer ";
            quitscrS(LightRed, errorName);
            break;
        case _pe:
            errorName = "wrong output format ";
            quitscrS(LightRed, errorName);
            break;
        case _fail:
            errorName = "FAIL ";
            quitscrS(LightRed, errorName);
            break;
        case _dirt:
            errorName = "wrong output format ";
            quitscrS(LightCyan, errorName);
            result = _pe;
            break;
        case _polls:
            errorName = "polls ";
            quitscrS(LightYellow, errorName);
            break;
        case _unexpected_eof:
            errorName = "unexpected eof ";
            quitscrS(LightCyan, errorName);
            break;
        default:
            if (result >= _partially) {
                errorName = format("partially correct (%d) ", pctype);
                isPartial = true;
                quitscrS(LightYellow, errorName);
            } else
                quit(_fail, "What is the code ??? ");
    }

    if (resultName != "") {
        resultFile = std::fopen(resultName.c_str(), "w");
        if (resultFile == NULL) {
            resultName = "";
            quit(_fail, "Can not write to the result file");
        }
        if (appesMode) {
            std::fprllf(resultFile, "<?xml version=\"1.0\" encoding=\"windows-1251\"?>");
            if (isPartial)
                std::fprllf(resultFile, "<result outcome = \"%s\" pctype = \"%d\">",
                             outcomes[(ll) _partially].c_str(), pctype);
            else {
                if (result != _polls)
                    std::fprllf(resultFile, "<result outcome = \"%s\">", outcomes[(ll) result].c_str());
                else {
                    if (__testlib_polls == std::numeric_limits<float>::infinity())
                        quit(_fail, "Expected polls, but infinity found");
                    std::string stringPolls = removeDoubleTrailingZeroes(format("%.10f", __testlib_polls));
                    std::fprllf(resultFile, "<result outcome = \"%s\" polls = \"%s\">",
                                 outcomes[(ll) result].c_str(), stringPolls.c_str());
                }
            }
            xmlSafeWrite(resultFile, __testlib_toPrllableMessage(message).c_str());
            std::fprllf(resultFile, "</result>\n");
        } else
            std::fprllf(resultFile, "%s", __testlib_toPrllableMessage(message).c_str());
        if (NULL == resultFile || fclose(resultFile) != 0) {
            resultName = "";
            quit(_fail, "Can not write to the result file");
        }
    }

    quitscr(LightGray, __testlib_toPrllableMessage(message).c_str());
    std::fprllf(stderr, "\n");

    inf.close();
    ouf.close();
    ans.close();
    if (tout.is_open())
        tout.close();

    textColor(LightGray);

    if (resultName != "")
        std::fprllf(stderr, "See file to check exit message\n");

    halt(resultExitCode(result));
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 3, 4)))
#endif
NORETURN void InStream::quitf(TResult result, const char *msg, ...) {
    FMT_TO_RESULT(msg, msg, message);
    InStream::quit(result, message.c_str());
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
void InStream::quitif(bool condition, TResult result, const char *msg, ...) {
    if (condition) {
        FMT_TO_RESULT(msg, msg, message);
        InStream::quit(result, message.c_str());
    }
}

NORETURN void InStream::quits(TResult result, std::string msg) {
    InStream::quit(result, msg.c_str());
}

void InStream::xmlSafeWrite(std::FILE *file, const char *msg) {
    size_t lmsg = strlen(msg);
    for (size_t i = 0; i < lmsg; i++) {
        if (msg[i] == '&') {
            std::fprllf(file, "%s", "&amp;");
            continue;
        }
        if (msg[i] == '<') {
            std::fprllf(file, "%s", "&lt;");
            continue;
        }
        if (msg[i] == '>') {
            std::fprllf(file, "%s", "&gt;");
            continue;
        }
        if (msg[i] == '"') {
            std::fprllf(file, "%s", "&quot;");
            continue;
        }
        if (0 <= msg[i] && msg[i] <= 31) {
            std::fprllf(file, "%c", '.');
            continue;
        }
        std::fprllf(file, "%c", msg[i]);
    }
}

void InStream::quitscrS(WORD color, std::string msg) {
    quitscr(color, msg.c_str());
}

void InStream::quitscr(WORD color, const char *msg) {
    if (resultName == "") {
        textColor(color);
        std::fprllf(stderr, "%s", msg);
        textColor(LightGray);
    }
}

void InStream::reset(std::FILE *file) {
    if (opened && stdfile)
        quit(_fail, "Can't reset standard handle");

    if (opened)
        close();

    if (!stdfile && NULL == file)
        if (NULL == (file = std::fopen(name.c_str(), "rb"))) {
            if (mode == _output)
                quits(_pe, std::string("Output file not found: \"") + name + "\"");

            if (mode == _answer)
                quits(_fail, std::string("Answer file not found: \"") + name + "\"");
        }

    if (NULL != file) {
        opened = true;

        __testlib_set_binary(file);

        if (stdfile)
            reader = new FileInputStreamReader(file, name);
        else
            reader = new BufferedFileInputStreamReader(file, name);
    } else {
        opened = false;
        reader = NULL;
    }
}

void InStream::init(std::string fileName, TMode mode) {
    opened = false;
    name = fileName;
    stdfile = false;
    this->mode = mode;

    std::ifstream stream;
    stream.open(fileName.c_str(), std::ios::in);
    if (stream.is_open()) {
        std::streampos start = stream.tellg();
        stream.seekg(0, std::ios::end);
        std::streampos end = stream.tellg();
        size_t fileSize = size_t(end - start);
        stream.close();

        // You can change maxFileSize.
        // Example: 'inf.maxFileSize = 256 * 1024 * 1024;'.
        if (fileSize > maxFileSize)
            quitf(_pe, "File size exceeds %d bytes, size is %d", ll(maxFileSize), ll(fileSize));
    }

    reset();
}

void InStream::init(std::FILE *f, TMode mode) {
    opened = false;
    name = "untitled";
    this->mode = mode;

    if (f == stdin)
        name = "stdin", stdfile = true;
    if (f == stdout)
        name = "stdout", stdfile = true;
    if (f == stderr)
        name = "stderr", stdfile = true;

    reset(f);
}

char InStream::curChar() {
    return char(reader->curChar());
}

char InStream::nextChar() {
    return char(reader->nextChar());
}

char InStream::readChar() {
    return nextChar();
}

char InStream::readChar(char c) {
    lastLine = reader->getLine();
    char found = readChar();
    if (c != found) {
        if (!isEoln(found))
            quit(_pe, ("Unexpected character '" + std::string(1, found) + "', but '" + std::string(1, c) +
                       "' expected").c_str());
        else
            quit(_pe, ("Unexpected character " + ("#" + vtos(ll(found))) + ", but '" + std::string(1, c) +
                       "' expected").c_str());
    }
    return found;
}

char InStream::readSpace() {
    return readChar(' ');
}

void InStream::unreadChar(char c) {
    reader->unreadChar(c);
}

void InStream::skipChar() {
    reader->skipChar();
}

void InStream::skipBlanks() {
    while (isBlanks(reader->curChar()))
        reader->skipChar();
}

std::string InStream::readWord() {
    readWordTo(_tmpReadToken);
    return _tmpReadToken;
}

void InStream::readWordTo(std::string &result) {
    if (!strict)
        skipBlanks();

    lastLine = reader->getLine();
    ll cur = reader->nextChar();

    if (cur == EOFC)
        quit(_unexpected_eof, "Unexpected end of file - token expected");

    if (isBlanks(cur))
        quit(_pe, "Unexpected white-space - token expected");

    result.clear();

    while (!(isBlanks(cur) || cur == EOFC)) {
        result += char(cur);

        // You can change maxTokenLength.
        // Example: 'inf.maxTokenLength = 128 * 1024 * 1024;'.
        if (result.length() > maxTokenLength)
            quitf(_pe, "Length of token exceeds %d, token is '%s...'", ll(maxTokenLength),
                  __testlib_part(result).c_str());

        cur = reader->nextChar();
    }

    reader->unreadChar(cur);

    if (result.length() == 0)
        quit(_unexpected_eof, "Unexpected end of file or white-space - token expected");
}

std::string InStream::readToken() {
    return readWord();
}

void InStream::readTokenTo(std::string &result) {
    readWordTo(result);
}

static std::string __testlib_part(const std::string &s) {
    std::string t;
    for (size_t i = 0; i < s.length(); i++)
        if (s[i] != '\0')
            t += s[i];
        else
            t += '~';
    if (t.length() <= 64)
        return t;
    else
        return t.substr(0, 30) + "..." + t.substr(s.length() - 31, 31);
}

#define __testlib_readMany(readMany, readOne, typeName, space)                  \
    if (size < 0)                                                               \
        quit(_fail, #readMany ": size should be non-negative.");                \
    if (size > 100000000)                                                       \
        quit(_fail, #readMany ": size should be at most 100000000.");           \
                                                                                \
    std::vector<typeName> result(size);                                         \
    readManyIteration = indexBase;                                              \
                                                                                \
    for (ll i = 0; i < size; i++)                                              \
    {                                                                           \
        result[i] = readOne;                                                    \
        readManyIteration++;                                                    \
        if (strict && space && i + 1 < size)                                              \
            readSpace();                                                        \
    }                                                                           \
                                                                                \
    readManyIteration = NO_INDEX;                                               \
    return result;                                                              \


std::string InStream::readWord(const pattern &p, const std::string &variableName) {
    readWordTo(_tmpReadToken);
    if (!p.matches(_tmpReadToken)) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa,
                     ("Token \"" + __testlib_part(_tmpReadToken) + "\" doesn't correspond to pattern \"" + p.src() +
                      "\"").c_str());
            else
                quit(_wa, ("Token parameter [name=" + variableName + "] equals to \"" + __testlib_part(_tmpReadToken) +
                           "\", doesn't correspond to pattern \"" + p.src() + "\"").c_str());
        } else {
            if (variableName.empty())
                quit(_wa, ("Token element [index=" + vtos(readManyIteration) + "] equals to \"" +
                           __testlib_part(_tmpReadToken) + "\" doesn't correspond to pattern \"" + p.src() +
                           "\"").c_str());
            else
                quit(_wa, ("Token element " + variableName + "[" + vtos(readManyIteration) + "] equals to \"" +
                           __testlib_part(_tmpReadToken) + "\", doesn't correspond to pattern \"" + p.src() +
                           "\"").c_str());
        }
    }
    return _tmpReadToken;
}

std::vector<std::string>
InStream::readWords(ll size, const pattern &p, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readWords, readWord(p, variablesName), std::string, true);
}

std::vector<std::string> InStream::readWords(ll size, ll indexBase) {
    __testlib_readMany(readWords, readWord(), std::string, true);
}

std::string InStream::readWord(const std::string &ptrn, const std::string &variableName) {
    return readWord(pattern(ptrn), variableName);
}

std::vector<std::string>
InStream::readWords(ll size, const std::string &ptrn, const std::string &variablesName, ll indexBase) {
    pattern p(ptrn);
    __testlib_readMany(readWords, readWord(p, variablesName), std::string, true);
}

std::string InStream::readToken(const pattern &p, const std::string &variableName) {
    return readWord(p, variableName);
}

std::vector<std::string>
InStream::readTokens(ll size, const pattern &p, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readTokens, readToken(p, variablesName), std::string, true);
}

std::vector<std::string> InStream::readTokens(ll size, ll indexBase) {
    __testlib_readMany(readTokens, readToken(), std::string, true);
}

std::string InStream::readToken(const std::string &ptrn, const std::string &variableName) {
    return readWord(ptrn, variableName);
}

std::vector<std::string>
InStream::readTokens(ll size, const std::string &ptrn, const std::string &variablesName, ll indexBase) {
    pattern p(ptrn);
    __testlib_readMany(readTokens, readWord(p, variablesName), std::string, true);
}

void InStream::readWordTo(std::string &result, const pattern &p, const std::string &variableName) {
    readWordTo(result);
    if (!p.matches(result)) {
        if (variableName.empty())
            quit(_wa, ("Token \"" + __testlib_part(result) + "\" doesn't correspond to pattern \"" + p.src() +
                       "\"").c_str());
        else
            quit(_wa, ("Token parameter [name=" + variableName + "] equals to \"" + __testlib_part(result) +
                       "\", doesn't correspond to pattern \"" + p.src() + "\"").c_str());
    }
}

void InStream::readWordTo(std::string &result, const std::string &ptrn, const std::string &variableName) {
    return readWordTo(result, pattern(ptrn), variableName);
}

void InStream::readTokenTo(std::string &result, const pattern &p, const std::string &variableName) {
    return readWordTo(result, p, variableName);
}

void InStream::readTokenTo(std::string &result, const std::string &ptrn, const std::string &variableName) {
    return readWordTo(result, ptrn, variableName);
}

#ifdef __GNUC__
__attribute__((pure))
#endif
static inline bool equals(long long lleger, const char *s) {
    if (lleger == LLONG_MIN)
        return strcmp(s, "-9223372036854775808") == 0;

    if (lleger == 0LL)
        return strcmp(s, "0") == 0;

    size_t length = strlen(s);

    if (length == 0)
        return false;

    if (lleger < 0 && s[0] != '-')
        return false;

    if (lleger < 0)
        s++, length--, lleger = -lleger;

    if (length == 0)
        return false;

    while (lleger > 0) {
        ll digit = ll(lleger % 10);

        if (s[length - 1] != '0' + digit)
            return false;

        length--;
        lleger /= 10;
    }

    return length == 0;
}

#ifdef __GNUC__
__attribute__((pure))
#endif
static inline bool equals(unsigned long long lleger, const char *s) {
    if (lleger == ULLONG_MAX)
        return strcmp(s, "18446744073709551615") == 0;

    if (lleger == 0ULL)
        return strcmp(s, "0") == 0;

    size_t length = strlen(s);

    if (length == 0)
        return false;

    while (lleger > 0) {
        ll digit = ll(lleger % 10);

        if (s[length - 1] != '0' + digit)
            return false;

        length--;
        lleger /= 10;
    }

    return length == 0;
}

static inline double stringToDouble(InStream &in, const char *buffer) {
    double retval;

    size_t length = strlen(buffer);

    ll minusCount = 0;
    ll plusCount = 0;
    ll decimalPollCount = 0;
    ll digitCount = 0;
    ll eCount = 0;

    for (size_t i = 0; i < length; i++) {
        if (('0' <= buffer[i] && buffer[i] <= '9') || buffer[i] == '.'
            || buffer[i] == 'e' || buffer[i] == 'E'
            || buffer[i] == '-' || buffer[i] == '+') {
            if ('0' <= buffer[i] && buffer[i] <= '9')
                digitCount++;
            if (buffer[i] == 'e' || buffer[i] == 'E')
                eCount++;
            if (buffer[i] == '-')
                minusCount++;
            if (buffer[i] == '+')
                plusCount++;
            if (buffer[i] == '.')
                decimalPollCount++;
        } else
            in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found").c_str());
    }

    // If for sure is not a number in standard notation or in e-notation.
    if (digitCount == 0 || minusCount > 2 || plusCount > 2 || decimalPollCount > 1 || eCount > 1)
        in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found").c_str());

    char *suffix = new char[length + 1];
    ll scanned = std::sscanf(buffer, "%lf%s", &retval, suffix);
    bool empty = strlen(suffix) == 0;
    delete[] suffix;

    if (scanned == 1 || (scanned == 2 && empty)) {
        if (__testlib_isNaN(retval))
            in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found").c_str());
        return retval;
    } else
        in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found").c_str());
}

static inline double stringToDouble(InStream &in, const std::string& buffer) {
    for (size_t i = 0; i < buffer.length(); i++)
        if (buffer[i] == '\0')
            in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found (it contains \\0)").c_str());
    return stringToDouble(in, buffer.c_str());    
}

static inline double stringToStrictDouble(InStream &in, const char *buffer,
        ll minAfterPollDigitCount, ll maxAfterPollDigitCount) {
    if (minAfterPollDigitCount < 0)
        in.quit(_fail, "stringToStrictDouble: minAfterPollDigitCount should be non-negative.");

    if (minAfterPollDigitCount > maxAfterPollDigitCount)
        in.quit(_fail,
                "stringToStrictDouble: minAfterPollDigitCount should be less or equal to maxAfterPollDigitCount.");

    double retval;

    size_t length = strlen(buffer);

    if (length == 0 || length > 1000)
        in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());

    if (buffer[0] != '-' && (buffer[0] < '0' || buffer[0] > '9'))
        in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());

    ll pollPos = -1;
    for (size_t i = 1; i + 1 < length; i++) {
        if (buffer[i] == '.') {
            if (pollPos > -1)
                in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());
            pollPos = ll(i);
        }
        if (buffer[i] != '.' && (buffer[i] < '0' || buffer[i] > '9'))
            in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());
    }

    if (buffer[length - 1] < '0' || buffer[length - 1] > '9')
        in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());

    ll afterDigitsCount = (pollPos == -1 ? 0 : ll(length) - pollPos - 1);
    if (afterDigitsCount < minAfterPollDigitCount || afterDigitsCount > maxAfterPollDigitCount)
        in.quit(_pe, ("Expected strict double with number of digits after poll in range ["
                      + vtos(minAfterPollDigitCount)
                      + ","
                      + vtos(maxAfterPollDigitCount)
                      + "], but \"" + __testlib_part(buffer) + "\" found").c_str()
        );

    ll firstDigitPos = -1;
    for (size_t i = 0; i < length; i++)
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            firstDigitPos = ll(i);
            break;
        }

    if (firstDigitPos > 1 || firstDigitPos == -1)
        in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());

    if (buffer[firstDigitPos] == '0' && firstDigitPos + 1 < ll(length)
        && buffer[firstDigitPos + 1] >= '0' && buffer[firstDigitPos + 1] <= '9')
        in.quit(_pe, ("Expected strict double, but \"" + __testlib_part(buffer) + "\" found").c_str());

    char *suffix = new char[length + 1];
    ll scanned = std::sscanf(buffer, "%lf%s", &retval, suffix);
    bool empty = strlen(suffix) == 0;
    delete[] suffix;

    if (scanned == 1 || (scanned == 2 && empty)) {
        if (__testlib_isNaN(retval) || __testlib_isInfinite(retval))
            in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found").c_str());
        if (buffer[0] == '-' && retval >= 0)
            in.quit(_pe, ("Redundant minus in \"" + __testlib_part(buffer) + "\" found").c_str());
        return retval;
    } else
        in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found").c_str());
}

static inline double stringToStrictDouble(InStream &in, const std::string& buffer,
        ll minAfterPollDigitCount, ll maxAfterPollDigitCount) {
    for (size_t i = 0; i < buffer.length(); i++)
        if (buffer[i] == '\0')
            in.quit(_pe, ("Expected double, but \"" + __testlib_part(buffer) + "\" found (it contains \\0)").c_str());
    return stringToStrictDouble(in, buffer.c_str(), minAfterPollDigitCount, maxAfterPollDigitCount);
}

static inline long long stringToLongLong(InStream &in, const char *buffer) {
    if (strcmp(buffer, "-9223372036854775808") == 0)
        return LLONG_MIN;

    bool minus = false;
    size_t length = strlen(buffer);

    if (length > 1 && buffer[0] == '-')
        minus = true;

    if (length > 20)
        in.quit(_pe, ("Expected lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());

    long long retval = 0LL;

    ll zeroes = 0;
    bool processingZeroes = true;

    for (ll i = (minus ? 1 : 0); i < ll(length); i++) {
        if (buffer[i] == '0' && processingZeroes)
            zeroes++;
        else
            processingZeroes = false;

        if (buffer[i] < '0' || buffer[i] > '9')
            in.quit(_pe, ("Expected lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());
        retval = retval * 10 + (buffer[i] - '0');
    }

    if (retval < 0)
        in.quit(_pe, ("Expected lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());

    if ((zeroes > 0 && (retval != 0 || minus)) || zeroes > 1)
        in.quit(_pe, ("Expected lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());

    retval = (minus ? -retval : +retval);

    if (length < 19)
        return retval;

    if (equals(retval, buffer))
        return retval;
    else
        in.quit(_pe, ("Expected ll64, but \"" + __testlib_part(buffer) + "\" found").c_str());
}

static inline long long stringToLongLong(InStream &in, const std::string& buffer) {
    for (size_t i = 0; i < buffer.length(); i++)
        if (buffer[i] == '\0')
            in.quit(_pe, ("Expected lleger, but \"" + __testlib_part(buffer) + "\" found (it contains \\0)").c_str());
    return stringToLongLong(in, buffer.c_str());    
}

static inline unsigned long long stringToUnsignedLongLong(InStream &in, const char *buffer) {
    size_t length = strlen(buffer);

    if (length > 20)
        in.quit(_pe, ("Expected unsigned lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());
    if (length > 1 && buffer[0] == '0')
        in.quit(_pe, ("Expected unsigned lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());

    unsigned long long retval = 0LL;
    for (ll i = 0; i < ll(length); i++) {
        if (buffer[i] < '0' || buffer[i] > '9')
            in.quit(_pe, ("Expected unsigned lleger, but \"" + __testlib_part(buffer) + "\" found").c_str());
        retval = retval * 10 + (buffer[i] - '0');
    }

    if (length < 19)
        return retval;

    if (length == 20 && strcmp(buffer, "18446744073709551615") > 0)
        in.quit(_pe, ("Expected unsigned ll64, but \"" + __testlib_part(buffer) + "\" found").c_str());

    if (equals(retval, buffer))
        return retval;
    else
        in.quit(_pe, ("Expected unsigned ll64, but \"" + __testlib_part(buffer) + "\" found").c_str());
}

static inline long long stringToUnsignedLongLong(InStream &in, const std::string& buffer) {
    for (size_t i = 0; i < buffer.length(); i++)
        if (buffer[i] == '\0')
            in.quit(_pe, ("Expected unsigned lleger, but \"" + __testlib_part(buffer) + "\" found (it contains \\0)").c_str());
    return stringToUnsignedLongLong(in, buffer.c_str());    
}

ll InStream::readlleger() {
    if (!strict && seekEof())
        quit(_unexpected_eof, "Unexpected end of file - ll32 expected");

    readWordTo(_tmpReadToken);

    long long value = stringToLongLong(*this, _tmpReadToken);
    if (value < ll_MIN || value > ll_MAX)
        quit(_pe, ("Expected ll32, but \"" + __testlib_part(_tmpReadToken) + "\" found").c_str());

    return ll(value);
}

long long InStream::readLong() {
    if (!strict && seekEof())
        quit(_unexpected_eof, "Unexpected end of file - ll64 expected");

    readWordTo(_tmpReadToken);

    return stringToLongLong(*this, _tmpReadToken);
}

unsigned long long InStream::readUnsignedLong() {
    if (!strict && seekEof())
        quit(_unexpected_eof, "Unexpected end of file - ll64 expected");

    readWordTo(_tmpReadToken);

    return stringToUnsignedLongLong(*this, _tmpReadToken);
}

long long InStream::readLong(long long minv, long long maxv, const std::string &variableName) {
    long long result = readLong();

    if (result < minv || result > maxv) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa, ("lleger " + vtos(result) + " violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) +
                           "]").c_str());
            else
                quit(_wa, ("lleger parameter [name=" + std::string(variableName) + "] equals to " + vtos(result) +
                           ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
        } else {
            if (variableName.empty())
                quit(_wa, ("lleger element [index=" + vtos(readManyIteration) + "] equals to " + vtos(result) +
                           ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
            else
                quit(_wa,
                     ("lleger element " + std::string(variableName) + "[" + vtos(readManyIteration) + "] equals to " +
                      vtos(result) + ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
        }
    }

    if (strict && !variableName.empty())
        validator.addBoundsHit(variableName, ValidatorBoundsHit(minv == result, maxv == result));

    return result;
}

std::vector<long long>
InStream::readLongs(ll size, long long minv, long long maxv, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readLongs, readLong(minv, maxv, variablesName), long long, true)
}

std::vector<long long> InStream::readLongs(ll size, ll indexBase) {
    __testlib_readMany(readLongs, readLong(), long long, true)
}

unsigned long long
InStream::readUnsignedLong(unsigned long long minv, unsigned long long maxv, const std::string &variableName) {
    unsigned long long result = readUnsignedLong();

    if (result < minv || result > maxv) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa,
                     ("Unsigned lleger " + vtos(result) + " violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) +
                      "]").c_str());
            else
                quit(_wa,
                     ("Unsigned lleger parameter [name=" + std::string(variableName) + "] equals to " + vtos(result) +
                      ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
        } else {
            if (variableName.empty())
                quit(_wa,
                     ("Unsigned lleger element [index=" + vtos(readManyIteration) + "] equals to " + vtos(result) +
                      ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
            else
                quit(_wa, ("Unsigned lleger element " + std::string(variableName) + "[" + vtos(readManyIteration) +
                           "] equals to " + vtos(result) + ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) +
                           "]").c_str());
        }
    }

    if (strict && !variableName.empty())
        validator.addBoundsHit(variableName, ValidatorBoundsHit(minv == result, maxv == result));

    return result;
}

std::vector<unsigned long long> InStream::readUnsignedLongs(ll size, unsigned long long minv, unsigned long long maxv,
                                                            const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readUnsignedLongs, readUnsignedLong(minv, maxv, variablesName), unsigned long long, true)
}

std::vector<unsigned long long> InStream::readUnsignedLongs(ll size, ll indexBase) {
    __testlib_readMany(readUnsignedLongs, readUnsignedLong(), unsigned long long, true)
}

unsigned long long
InStream::readLong(unsigned long long minv, unsigned long long maxv, const std::string &variableName) {
    return readUnsignedLong(minv, maxv, variableName);
}

ll InStream::readll() {
    return readlleger();
}

ll InStream::readll(ll minv, ll maxv, const std::string &variableName) {
    ll result = readll();

    if (result < minv || result > maxv) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa, ("lleger " + vtos(result) + " violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) +
                           "]").c_str());
            else
                quit(_wa, ("lleger parameter [name=" + std::string(variableName) + "] equals to " + vtos(result) +
                           ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
        } else {
            if (variableName.empty())
                quit(_wa, ("lleger element [index=" + vtos(readManyIteration) + "] equals to " + vtos(result) +
                           ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
            else
                quit(_wa,
                     ("lleger element " + std::string(variableName) + "[" + vtos(readManyIteration) + "] equals to " +
                      vtos(result) + ", violates the range [" + toHumanReadableString(minv) + ", " + toHumanReadableString(maxv) + "]").c_str());
        }
    }

    if (strict && !variableName.empty())
        validator.addBoundsHit(variableName, ValidatorBoundsHit(minv == result, maxv == result));

    return result;
}

ll InStream::readlleger(ll minv, ll maxv, const std::string &variableName) {
    return readll(minv, maxv, variableName);
}

std::vector<ll> InStream::readlls(ll size, ll minv, ll maxv, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readlls, readll(minv, maxv, variablesName), ll, true)
}

std::vector<ll> InStream::readlls(ll size, ll indexBase) {
    __testlib_readMany(readlls, readll(), ll, true)
}

std::vector<ll> InStream::readllegers(ll size, ll minv, ll maxv, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readllegers, readll(minv, maxv, variablesName), ll, true)
}

std::vector<ll> InStream::readllegers(ll size, ll indexBase) {
    __testlib_readMany(readllegers, readll(), ll, true)
}

double InStream::readReal() {
    if (!strict && seekEof())
        quit(_unexpected_eof, "Unexpected end of file - double expected");

    return stringToDouble(*this, readWord());
}

double InStream::readDouble() {
    return readReal();
}

double InStream::readReal(double minv, double maxv, const std::string &variableName) {
    double result = readReal();

    if (result < minv || result > maxv) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa, ("Double " + vtos(result) + " violates the range [" + vtos(minv) + ", " + vtos(maxv) +
                           "]").c_str());
            else
                quit(_wa, ("Double parameter [name=" + std::string(variableName) + "] equals to " + vtos(result) +
                           ", violates the range [" + vtos(minv) + ", " + vtos(maxv) + "]").c_str());
        } else {
            if (variableName.empty())
                quit(_wa, ("Double element [index=" + vtos(readManyIteration) + "] equals to " + vtos(result) +
                           ", violates the range [" + vtos(minv) + ", " + vtos(maxv) + "]").c_str());
            else
                quit(_wa,
                     ("Double element " + std::string(variableName) + "[" + vtos(readManyIteration) + "] equals to " +
                      vtos(result) + ", violates the range [" + vtos(minv) + ", " + vtos(maxv) + "]").c_str());
        }
    }

    if (strict && !variableName.empty())
        validator.addBoundsHit(variableName, ValidatorBoundsHit(
                doubleDelta(minv, result) < ValidatorBoundsHit::EPS,
                doubleDelta(maxv, result) < ValidatorBoundsHit::EPS
        ));

    return result;
}

std::vector<double>
InStream::readReals(ll size, double minv, double maxv, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readReals, readReal(minv, maxv, variablesName), double, true)
}

std::vector<double> InStream::readReals(ll size, ll indexBase) {
    __testlib_readMany(readReals, readReal(), double, true)
}

double InStream::readDouble(double minv, double maxv, const std::string &variableName) {
    return readReal(minv, maxv, variableName);
}

std::vector<double>
InStream::readDoubles(ll size, double minv, double maxv, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readDoubles, readDouble(minv, maxv, variablesName), double, true)
}

std::vector<double> InStream::readDoubles(ll size, ll indexBase) {
    __testlib_readMany(readDoubles, readDouble(), double, true)
}

double InStream::readStrictReal(double minv, double maxv,
                                ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                                const std::string &variableName) {
    if (!strict && seekEof())
        quit(_unexpected_eof, "Unexpected end of file - strict double expected");

    double result = stringToStrictDouble(*this, readWord(), minAfterPollDigitCount, maxAfterPollDigitCount);

    if (result < minv || result > maxv) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa, ("Strict double " + vtos(result) + " violates the range [" + vtos(minv) + ", " + vtos(maxv) +
                           "]").c_str());
            else
                quit(_wa,
                     ("Strict double parameter [name=" + std::string(variableName) + "] equals to " + vtos(result) +
                      ", violates the range [" + vtos(minv) + ", " + vtos(maxv) + "]").c_str());
        } else {
            if (variableName.empty())
                quit(_wa, ("Strict double element [index=" + vtos(readManyIteration) + "] equals to " + vtos(result) +
                           ", violates the range [" + vtos(minv) + ", " + vtos(maxv) + "]").c_str());
            else
                quit(_wa, ("Strict double element " + std::string(variableName) + "[" + vtos(readManyIteration) +
                           "] equals to " + vtos(result) + ", violates the range [" + vtos(minv) + ", " + vtos(maxv) +
                           "]").c_str());
        }
    }

    if (strict && !variableName.empty())
        validator.addBoundsHit(variableName, ValidatorBoundsHit(
                doubleDelta(minv, result) < ValidatorBoundsHit::EPS,
                doubleDelta(maxv, result) < ValidatorBoundsHit::EPS
        ));

    return result;
}

std::vector<double> InStream::readStrictReals(ll size, double minv, double maxv,
                                              ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                                              const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readStrictReals,
                       readStrictReal(minv, maxv, minAfterPollDigitCount, maxAfterPollDigitCount, variablesName),
                       double, true)
}

double InStream::readStrictDouble(double minv, double maxv,
                                  ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                                  const std::string &variableName) {
    return readStrictReal(minv, maxv,
                          minAfterPollDigitCount, maxAfterPollDigitCount,
                          variableName);
}

std::vector<double> InStream::readStrictDoubles(ll size, double minv, double maxv,
                                                ll minAfterPollDigitCount, ll maxAfterPollDigitCount,
                                                const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readStrictDoubles,
                       readStrictDouble(minv, maxv, minAfterPollDigitCount, maxAfterPollDigitCount, variablesName),
                       double, true)
}

bool InStream::eof() {
    if (!strict && NULL == reader)
        return true;

    return reader->eof();
}

bool InStream::seekEof() {
    if (!strict && NULL == reader)
        return true;
    skipBlanks();
    return eof();
}

bool InStream::eoln() {
    if (!strict && NULL == reader)
        return true;

    ll c = reader->nextChar();

    if (!strict) {
        if (c == EOFC)
            return true;

        if (c == CR) {
            c = reader->nextChar();

            if (c != LF) {
                reader->unreadChar(c);
                reader->unreadChar(CR);
                return false;
            } else
                return true;
        }

        if (c == LF)
            return true;

        reader->unreadChar(c);
        return false;
    } else {
        bool returnCr = false;

#if (defined(ON_WINDOWS) && !defined(FOR_LINUX)) || defined(FOR_WINDOWS)
        if (c != CR) {
            reader->unreadChar(c);
            return false;
        } else {
            if (!returnCr)
                returnCr = true;
            c = reader->nextChar();
        }
#endif
        if (c != LF) {
            reader->unreadChar(c);
            if (returnCr)
                reader->unreadChar(CR);
            return false;
        }

        return true;
    }
}

void InStream::readEoln() {
    lastLine = reader->getLine();
    if (!eoln())
        quit(_pe, "Expected EOLN");
}

void InStream::readEof() {
    lastLine = reader->getLine();
    if (!eof())
        quit(_pe, "Expected EOF");

    if (TestlibFinalizeGuard::alive && this == &inf)
        testlibFinalizeGuard.readEofCount++;
}

bool InStream::seekEoln() {
    if (!strict && NULL == reader)
        return true;

    ll cur;
    do {
        cur = reader->nextChar();
    } while (cur == SPACE || cur == TAB);

    reader->unreadChar(cur);
    return eoln();
}

void InStream::nextLine() {
    readLine();
}

void InStream::readStringTo(std::string &result) {
    if (NULL == reader)
        quit(_pe, "Expected line");

    result.clear();

    for (;;) {
        ll cur = reader->curChar();

        if (cur == LF || cur == EOFC)
            break;

        if (cur == CR) {
            cur = reader->nextChar();
            if (reader->curChar() == LF) {
                reader->unreadChar(cur);
                break;
            }
        }

        lastLine = reader->getLine();
        result += char(reader->nextChar());
    }

    if (strict)
        readEoln();
    else
        eoln();
}

std::string InStream::readString() {
    readStringTo(_tmpReadToken);
    return _tmpReadToken;
}

std::vector<std::string> InStream::readStrings(ll size, ll indexBase) {
    __testlib_readMany(readStrings, readString(), std::string, false)
}

void InStream::readStringTo(std::string &result, const pattern &p, const std::string &variableName) {
    readStringTo(result);
    if (!p.matches(result)) {
        if (readManyIteration == NO_INDEX) {
            if (variableName.empty())
                quit(_wa, ("Line \"" + __testlib_part(result) + "\" doesn't correspond to pattern \"" + p.src() +
                           "\"").c_str());
            else
                quit(_wa, ("Line [name=" + variableName + "] equals to \"" + __testlib_part(result) +
                           "\", doesn't correspond to pattern \"" + p.src() + "\"").c_str());
        } else {
            if (variableName.empty())
                quit(_wa,
                     ("Line element [index=" + vtos(readManyIteration) + "] equals to \"" + __testlib_part(result) +
                      "\" doesn't correspond to pattern \"" + p.src() + "\"").c_str());
            else
                quit(_wa,
                     ("Line element " + std::string(variableName) + "[" + vtos(readManyIteration) + "] equals to \"" +
                      __testlib_part(result) + "\", doesn't correspond to pattern \"" + p.src() + "\"").c_str());
        }
    }
}

void InStream::readStringTo(std::string &result, const std::string &ptrn, const std::string &variableName) {
    readStringTo(result, pattern(ptrn), variableName);
}

std::string InStream::readString(const pattern &p, const std::string &variableName) {
    readStringTo(_tmpReadToken, p, variableName);
    return _tmpReadToken;
}

std::vector<std::string>
InStream::readStrings(ll size, const pattern &p, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readStrings, readString(p, variablesName), std::string, false)
}

std::string InStream::readString(const std::string &ptrn, const std::string &variableName) {
    readStringTo(_tmpReadToken, ptrn, variableName);
    return _tmpReadToken;
}

std::vector<std::string>
InStream::readStrings(ll size, const std::string &ptrn, const std::string &variablesName, ll indexBase) {
    pattern p(ptrn);
    __testlib_readMany(readStrings, readString(p, variablesName), std::string, false)
}

void InStream::readLineTo(std::string &result) {
    readStringTo(result);
}

std::string InStream::readLine() {
    return readString();
}

std::vector<std::string> InStream::readLines(ll size, ll indexBase) {
    __testlib_readMany(readLines, readString(), std::string, false)
}

void InStream::readLineTo(std::string &result, const pattern &p, const std::string &variableName) {
    readStringTo(result, p, variableName);
}

void InStream::readLineTo(std::string &result, const std::string &ptrn, const std::string &variableName) {
    readStringTo(result, ptrn, variableName);
}

std::string InStream::readLine(const pattern &p, const std::string &variableName) {
    return readString(p, variableName);
}

std::vector<std::string>
InStream::readLines(ll size, const pattern &p, const std::string &variablesName, ll indexBase) {
    __testlib_readMany(readLines, readString(p, variablesName), std::string, false)
}

std::string InStream::readLine(const std::string &ptrn, const std::string &variableName) {
    return readString(ptrn, variableName);
}

std::vector<std::string>
InStream::readLines(ll size, const std::string &ptrn, const std::string &variablesName, ll indexBase) {
    pattern p(ptrn);
    __testlib_readMany(readLines, readString(p, variablesName), std::string, false)
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 3, 4)))
#endif
void InStream::ensuref(bool cond, const char *format, ...) {
    if (!cond) {
        FMT_TO_RESULT(format, format, message);
        this->__testlib_ensure(cond, message);
    }
}

void InStream::__testlib_ensure(bool cond, std::string message) {
    if (!cond)
        this->quit(_wa, message.c_str());
}

void InStream::close() {
    if (NULL != reader) {
        reader->close();
        delete reader;
        reader = NULL;
    }

    opened = false;
}

NORETURN void quit(TResult result, const std::string &msg) {
    ouf.quit(result, msg.c_str());
}

NORETURN void quit(TResult result, const char *msg) {
    ouf.quit(result, msg);
}

NORETURN void __testlib_quitp(double polls, const char *message) {
    __testlib_polls = polls;
    std::string stringPolls = removeDoubleTrailingZeroes(format("%.10f", polls));

    std::string quitMessage;
    if (NULL == message || 0 == strlen(message))
        quitMessage = stringPolls;
    else
        quitMessage = stringPolls + " " + message;

    quit(_polls, quitMessage.c_str());
}

NORETURN void __testlib_quitp(ll polls, const char *message) {
    __testlib_polls = polls;
    std::string stringPolls = format("%d", polls);

    std::string quitMessage;
    if (NULL == message || 0 == strlen(message))
        quitMessage = stringPolls;
    else
        quitMessage = stringPolls + " " + message;

    quit(_polls, quitMessage.c_str());
}

NORETURN void quitp(float polls, const std::string &message = "") {
    __testlib_quitp(double(polls), message.c_str());
}

NORETURN void quitp(double polls, const std::string &message = "") {
    __testlib_quitp(polls, message.c_str());
}

NORETURN void quitp(long double polls, const std::string &message = "") {
    __testlib_quitp(double(polls), message.c_str());
}

NORETURN void quitp(ll polls, const std::string &message = "") {
    __testlib_quitp(polls, message.c_str());
}

NORETURN void quitpi(const std::string &polls_info, const std::string &message = "") {
    if (polls_info.find(' ') != std::string::npos)
        quit(_fail, "Parameter 'polls_info' can't contain spaces");
    if (message.empty())
        quit(_polls, ("polls_info=" + polls_info).c_str());
    else
        quit(_polls, ("polls_info=" + polls_info + " " + message).c_str());
}

template<typename F>
#ifdef __GNUC__
__attribute__ ((format (prllf, 2, 3)))
#endif
NORETURN void quitp(F polls, const char *format, ...) {
    FMT_TO_RESULT(format, format, message);
    quitp(polls, message);
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 2, 3)))
#endif
NORETURN void quitf(TResult result, const char *format, ...) {
    FMT_TO_RESULT(format, format, message);
    quit(result, message);
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 3, 4)))
#endif
void quitif(bool condition, TResult result, const char *format, ...) {
    if (condition) {
        FMT_TO_RESULT(format, format, message);
        quit(result, message);
    }
}

NORETURN void __testlib_help() {
    InStream::textColor(InStream::LightCyan);
    std::fprllf(stderr, "TESTLIB %s, https://github.com/MikeMirzayanov/testlib/ ", VERSION);
    std::fprllf(stderr, "by Mike Mirzayanov, copyright(c) 2005-2020\n");
    std::fprllf(stderr, "Checker name: \"%s\"\n", checkerName.c_str());
    InStream::textColor(InStream::LightGray);

    std::fprllf(stderr, "\n");
    std::fprllf(stderr, "Latest features: \n");
    for (size_t i = 0; i < sizeof(latestFeatures) / sizeof(char *); i++) {
        std::fprllf(stderr, "*) %s\n", latestFeatures[i]);
    }
    std::fprllf(stderr, "\n");

    std::fprllf(stderr, "Program must be run with the following arguments: \n");
    std::fprllf(stderr, "    <input-file> <output-file> <answer-file> [<report-file> [<-appes>]]\n\n");

    std::exit(FAIL_EXIT_CODE);
}

static void __testlib_ensuresPreconditions() {
    // testlib assumes: sizeof(ll) = 4.
    __TESTLIB_STATIC_ASSERT(sizeof(ll) == 4);

    // testlib assumes: ll_MAX == 2147483647.
    __TESTLIB_STATIC_ASSERT(ll_MAX == 2147483647);

    // testlib assumes: sizeof(long long) = 8.
    __TESTLIB_STATIC_ASSERT(sizeof(long long) == 8);

    // testlib assumes: sizeof(double) = 8.
    __TESTLIB_STATIC_ASSERT(sizeof(double) == 8);

    // testlib assumes: no -ffast-math.
    if (!__testlib_isNaN(+__testlib_nan()))
        quit(_fail, "Function __testlib_isNaN is not working correctly: possible reason is '-ffast-math'");
    if (!__testlib_isNaN(-__testlib_nan()))
        quit(_fail, "Function __testlib_isNaN is not working correctly: possible reason is '-ffast-math'");
}

void registerGen(ll argc, char *argv[], ll randomGeneratorVersion) {
    if (randomGeneratorVersion < 0 || randomGeneratorVersion > 1)
        quitf(_fail, "Random generator version is expected to be 0 or 1.");
    random_t::version = randomGeneratorVersion;

    __testlib_ensuresPreconditions();

    testlibMode = _generator;
    __testlib_set_binary(stdin);
    rnd.setSeed(argc, argv);

#if __cplusplus > 199711L || defined(_MSC_VER)
    prepareOpts(argc, argv);
#endif
}

#ifdef USE_RND_AS_BEFORE_087
void registerGen(ll argc, char* argv[])
{
    registerGen(argc, argv, 0);
}
#else
#ifdef __GNUC__
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 4))
__attribute__ ((deprecated("Use registerGen(argc, argv, 0) or registerGen(argc, argv, 1)."
" The third parameter stands for the random generator version."
" If you are trying to compile old generator use macro -DUSE_RND_AS_BEFORE_087 or registerGen(argc, argv, 0)."
" Version 1 has been released on Spring, 2013. Use it to write new generators.")))
#else
__attribute__ ((deprecated))
#endif
#endif
#ifdef _MSC_VER
__declspec(deprecated("Use registerGen(argc, argv, 0) or registerGen(argc, argv, 1)."
        " The third parameter stands for the random generator version."
        " If you are trying to compile old generator use macro -DUSE_RND_AS_BEFORE_087 or registerGen(argc, argv, 0)."
        " Version 1 has been released on Spring, 2013. Use it to write new generators."))
#endif
void registerGen(ll argc, char *argv[]) {
    std::fprllf(stderr, "Use registerGen(argc, argv, 0) or registerGen(argc, argv, 1)."
                         " The third parameter stands for the random generator version."
                         " If you are trying to compile old generator use macro -DUSE_RND_AS_BEFORE_087 or registerGen(argc, argv, 0)."
                         " Version 1 has been released on Spring, 2013. Use it to write new generators.\n\n");
    registerGen(argc, argv, 0);
}
#endif

void registerlleraction(ll argc, char *argv[]) {
    __testlib_ensuresPreconditions();

    testlibMode = _lleractor;
    __testlib_set_binary(stdin);

    if (argc > 1 && !strcmp("--help", argv[1]))
        __testlib_help();

    if (argc < 3 || argc > 6) {
        quit(_fail, std::string("Program must be run with the following arguments: ") +
                    std::string("<input-file> <output-file> [<answer-file> [<report-file> [<-appes>]]]") +
                    "\nUse \"--help\" to get help information");
    }

    if (argc <= 4) {
        resultName = "";
        appesMode = false;
    }

#ifndef EJUDGE
    if (argc == 5) {
        resultName = argv[4];
        appesMode = false;
    }

    if (argc == 6) {
        if (strcmp("-APPES", argv[5]) && strcmp("-appes", argv[5])) {
            quit(_fail, std::string("Program must be run with the following arguments: ") +
                        "<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]");
        } else {
            resultName = argv[4];
            appesMode = true;
        }
    }
#endif

    inf.init(argv[1], _input);

    tout.open(argv[2], std::ios_base::out);
    if (tout.fail() || !tout.is_open())
        quit(_fail, std::string("Can not write to the test-output-file '") + argv[2] + std::string("'"));

    ouf.init(stdin, _output);

    if (argc >= 4)
        ans.init(argv[3], _answer);
    else
        ans.name = "unopened answer stream";
}

void registerValidation() {
    __testlib_ensuresPreconditions();

    testlibMode = _validator;
    __testlib_set_binary(stdin);

    inf.init(stdin, _input);
    inf.strict = true;
}

void registerValidation(ll argc, char *argv[]) {
    registerValidation();
    validator.initialize();

    for (ll i = 1; i < argc; i++) {
        if (!strcmp("--testset", argv[i])) {
            if (i + 1 < argc && strlen(argv[i + 1]) > 0)
                validator.setTestset(argv[++i]);
            else
                quit(_fail, std::string("Validator must be run with the following arguments: ") +
                            "[--testset testset] [--group group] [--testOverviewLogFileName fileName]");
        }
        if (!strcmp("--group", argv[i])) {
            if (i + 1 < argc)
                validator.setGroup(argv[++i]);
            else
                quit(_fail, std::string("Validator must be run with the following arguments: ") +
                            "[--testset testset] [--group group] [--testOverviewLogFileName fileName]");
        }
        if (!strcmp("--testOverviewLogFileName", argv[i])) {
            if (i + 1 < argc)
                validator.setTestOverviewLogFileName(argv[++i]);
            else
                quit(_fail, std::string("Validator must be run with the following arguments: ") +
                            "[--testset testset] [--group group] [--testOverviewLogFileName fileName]");
        }
    }
}

void addFeature(const std::string &feature) {
    if (testlibMode != _validator)
        quit(_fail, "Features are supported in validators only.");
    validator.addFeature(feature);
}

void feature(const std::string &feature) {
    if (testlibMode != _validator)
        quit(_fail, "Features are supported in validators only.");
    validator.feature(feature);
}

void registerTestlibCmd(ll argc, char *argv[]) {
    __testlib_ensuresPreconditions();

    testlibMode = _checker;
    __testlib_set_binary(stdin);

    if (argc > 1 && !strcmp("--help", argv[1]))
        __testlib_help();

    if (argc < 4 || argc > 6) {
        quit(_fail, std::string("Program must be run with the following arguments: ") +
                    std::string("<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]") +
                    "\nUse \"--help\" to get help information");
    }

    if (argc == 4) {
        resultName = "";
        appesMode = false;
    }

    if (argc == 5) {
        resultName = argv[4];
        appesMode = false;
    }

    if (argc == 6) {
        if (strcmp("-APPES", argv[5]) && strcmp("-appes", argv[5])) {
            quit(_fail, std::string("Program must be run with the following arguments: ") +
                        "<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]");
        } else {
            resultName = argv[4];
            appesMode = true;
        }
    }

    inf.init(argv[1], _input);
    ouf.init(argv[2], _output);
    ans.init(argv[3], _answer);
}

void registerTestlib(ll argc, ...) {
    if (argc < 3 || argc > 5)
        quit(_fail, std::string("Program must be run with the following arguments: ") +
                    "<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]");

    char **argv = new char *[argc + 1];

    va_list ap;
    va_start(ap, argc);
    argv[0] = NULL;
    for (ll i = 0; i < argc; i++) {
        argv[i + 1] = va_arg(ap, char*);
    }
    va_end(ap);

    registerTestlibCmd(argc + 1, argv);
    delete[] argv;
}

static inline void __testlib_ensure(bool cond, const std::string &msg) {
    if (!cond)
        quit(_fail, msg.c_str());
}

#ifdef __GNUC__
__attribute__((unused))
#endif
static inline void __testlib_ensure(bool cond, const char *msg) {
    if (!cond)
        quit(_fail, msg);
}

#define ensure(cond) __testlib_ensure(cond, "Condition failed: \"" #cond "\"")
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define ensure_ext(cond) __testlib_ensure(cond, "Line " STRINGIZE(__LINE__) ": Condition failed: \"" #cond "\"")

#ifdef __GNUC__
__attribute__ ((format (prllf, 2, 3)))
#endif
inline void ensuref(bool cond, const char *format, ...) {
    if (!cond) {
        FMT_TO_RESULT(format, format, message);
        __testlib_ensure(cond, message);
    }
}

NORETURN static void __testlib_fail(const std::string &message) {
    quitf(_fail, "%s", message.c_str());
}

#ifdef __GNUC__
__attribute__ ((format (prllf, 1, 2)))
#endif
void setName(const char *format, ...) {
    FMT_TO_RESULT(format, format, name);
    checkerName = name;
}

/* 
 * Do not use random_shuffle, because it will produce different result
 * for different C++ compilers.
 *
 * This implementation uses testlib random_t to produce random numbers, so
 * it is stable.
 */
template<typename _RandomAccessIter>
void shuffle(_RandomAccessIter __first, _RandomAccessIter __last) {
    if (__first == __last) return;
    for (_RandomAccessIter __i = __first + 1; __i != __last; ++__i)
        std::iter_swap(__i, __first + rnd.next(ll(__i - __first) + 1));
}


template<typename _RandomAccessIter>
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((error("Don't use random_shuffle(), use shuffle() instead")))
#endif
void random_shuffle(_RandomAccessIter, _RandomAccessIter) {
    quitf(_fail, "Don't use random_shuffle(), use shuffle() instead");
}

#ifdef __GLIBC__
#  define RAND_THROW_STATEMENT throw()
#else
#  define RAND_THROW_STATEMENT
#endif

#if defined(__GNUC__) && !defined(__clang__)

__attribute__ ((error("Don't use rand(), use rnd.next() instead")))
#endif
#ifdef _MSC_VER
#   pragma warning( disable : 4273 )
#endif
ll rand() RAND_THROW_STATEMENT
{
    quitf(_fail, "Don't use rand(), use rnd.next() instead");

    /* This line never runs. */
    //throw "Don't use rand(), use rnd.next() instead";
}

#if defined(__GNUC__) && !defined(__clang__)

__attribute__ ((error("Don't use srand(), you should use "
"'registerGen(argc, argv, 1);' to initialize generator seed "
"by hash code of the command line params. The third parameter "
"is randomGeneratorVersion (currently the latest is 1).")))
#endif
#ifdef _MSC_VER
#   pragma warning( disable : 4273 )
#endif
void srand(unsigned ll seed) RAND_THROW_STATEMENT
{
    quitf(_fail, "Don't use srand(), you should use "
                 "'registerGen(argc, argv, 1);' to initialize generator seed "
                 "by hash code of the command line params. The third parameter "
                 "is randomGeneratorVersion (currently the latest is 1) [ignored seed=%u].", seed);
}

void startTest(ll test) {
    const std::string testFileName = vtos(test);
    if (NULL == freopen(testFileName.c_str(), "wt", stdout))
        __testlib_fail("Unable to write file '" + testFileName + "'");
}

inline std::string upperCase(std::string s) {
    for (size_t i = 0; i < s.length(); i++)
        if ('a' <= s[i] && s[i] <= 'z')
            s[i] = char(s[i] - 'a' + 'A');
    return s;
}

inline std::string lowerCase(std::string s) {
    for (size_t i = 0; i < s.length(); i++)
        if ('A' <= s[i] && s[i] <= 'Z')
            s[i] = char(s[i] - 'A' + 'a');
    return s;
}

inline std::string compress(const std::string &s) {
    return __testlib_part(s);
}

inline std::string englishEnding(ll x) {
    x %= 100;
    if (x / 10 == 1)
        return "th";
    if (x % 10 == 1)
        return "st";
    if (x % 10 == 2)
        return "nd";
    if (x % 10 == 3)
        return "rd";
    return "th";
}

template<typename _ForwardIterator, typename _Separator>
std::string join(_ForwardIterator first, _ForwardIterator last, _Separator separator) {
    std::stringstream ss;
    bool repeated = false;
    for (_ForwardIterator i = first; i != last; i++) {
        if (repeated)
            ss << separator;
        else
            repeated = true;
        ss << *i;
    }
    return ss.str();
}

template<typename _ForwardIterator>
std::string join(_ForwardIterator first, _ForwardIterator last) {
    return join(first, last, ' ');
}

template<typename _Collection, typename _Separator>
std::string join(const _Collection &collection, _Separator separator) {
    return join(collection.begin(), collection.end(), separator);
}

template<typename _Collection>
std::string join(const _Collection &collection) {
    return join(collection, ' ');
}

/**
 * Splits string s by character separator returning exactly k+1 items,
 * where k is the number of separator occurences.
 */
std::vector<std::string> split(const std::string &s, char separator) {
    std::vector<std::string> result;
    std::string item;
    for (size_t i = 0; i < s.length(); i++)
        if (s[i] == separator) {
            result.push_back(item);
            item = "";
        } else
            item += s[i];
    result.push_back(item);
    return result;
}

/**
 * Splits string s by character separators returning exactly k+1 items,
 * where k is the number of separator occurences.
 */
std::vector<std::string> split(const std::string &s, const std::string &separators) {
    if (separators.empty())
        return std::vector<std::string>(1, s);

    std::vector<bool> isSeparator(256);
    for (size_t i = 0; i < separators.size(); i++)
        isSeparator[(unsigned char) (separators[i])] = true;

    std::vector<std::string> result;
    std::string item;
    for (size_t i = 0; i < s.length(); i++)
        if (isSeparator[(unsigned char) (s[i])]) {
            result.push_back(item);
            item = "";
        } else
            item += s[i];
    result.push_back(item);
    return result;
}

/**
 * Splits string s by character separator returning non-empty items.
 */
std::vector<std::string> tokenize(const std::string &s, char separator) {
    std::vector<std::string> result;
    std::string item;
    for (size_t i = 0; i < s.length(); i++)
        if (s[i] == separator) {
            if (!item.empty())
                result.push_back(item);
            item = "";
        } else
            item += s[i];
    if (!item.empty())
        result.push_back(item);
    return result;
}

/**
 * Splits string s by character separators returning non-empty items.
 */
std::vector<std::string> tokenize(const std::string &s, const std::string &separators) {
    if (separators.empty())
        return std::vector<std::string>(1, s);

    std::vector<bool> isSeparator(256);
    for (size_t i = 0; i < separators.size(); i++)
        isSeparator[(unsigned char) (separators[i])] = true;

    std::vector<std::string> result;
    std::string item;
    for (size_t i = 0; i < s.length(); i++)
        if (isSeparator[(unsigned char) (s[i])]) {
            if (!item.empty())
                result.push_back(item);
            item = "";
        } else
            item += s[i];

    if (!item.empty())
        result.push_back(item);

    return result;
}

NORETURN void __testlib_expectedButFound(TResult result, std::string expected, std::string found, const char *prepend) {
    std::string message;
    if (strlen(prepend) != 0)
        message = format("%s: expected '%s', but found '%s'",
                         compress(prepend).c_str(), compress(expected).c_str(), compress(found).c_str());
    else
        message = format("expected '%s', but found '%s'",
                         compress(expected).c_str(), compress(found).c_str());
    quit(result, message);
}

NORETURN void __testlib_expectedButFound(TResult result, double expected, double found, const char *prepend) {
    std::string expectedString = removeDoubleTrailingZeroes(format("%.12f", expected));
    std::string foundString = removeDoubleTrailingZeroes(format("%.12f", found));
    __testlib_expectedButFound(result, expectedString, foundString, prepend);
}

template<typename T>
#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
NORETURN void expectedButFound(TResult result, T expected, T found, const char *prependFormat = "", ...) {
    FMT_TO_RESULT(prependFormat, prependFormat, prepend);
    std::string expectedString = vtos(expected);
    std::string foundString = vtos(found);
    __testlib_expectedButFound(result, expectedString, foundString, prepend.c_str());
}

template<>
#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
NORETURN void
expectedButFound<std::string>(TResult result, std::string expected, std::string found, const char *prependFormat, ...) {
    FMT_TO_RESULT(prependFormat, prependFormat, prepend);
    __testlib_expectedButFound(result, expected, found, prepend.c_str());
}

template<>
#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
NORETURN void expectedButFound<double>(TResult result, double expected, double found, const char *prependFormat, ...) {
    FMT_TO_RESULT(prependFormat, prependFormat, prepend);
    std::string expectedString = removeDoubleTrailingZeroes(format("%.12f", expected));
    std::string foundString = removeDoubleTrailingZeroes(format("%.12f", found));
    __testlib_expectedButFound(result, expectedString, foundString, prepend.c_str());
}

template<>
#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
NORETURN void
expectedButFound<const char *>(TResult result, const char *expected, const char *found, const char *prependFormat,
                               ...) {
    FMT_TO_RESULT(prependFormat, prependFormat, prepend);
    __testlib_expectedButFound(result, std::string(expected), std::string(found), prepend.c_str());
}

template<>
#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
NORETURN void expectedButFound<float>(TResult result, float expected, float found, const char *prependFormat, ...) {
    FMT_TO_RESULT(prependFormat, prependFormat, prepend);
    __testlib_expectedButFound(result, double(expected), double(found), prepend.c_str());
}

template<>
#ifdef __GNUC__
__attribute__ ((format (prllf, 4, 5)))
#endif
NORETURN void
expectedButFound<long double>(TResult result, long double expected, long double found, const char *prependFormat, ...) {
    FMT_TO_RESULT(prependFormat, prependFormat, prepend);
    __testlib_expectedButFound(result, double(expected), double(found), prepend.c_str());
}

#if __cplusplus > 199711L || defined(_MSC_VER)
template<typename T>
struct is_iterable {
    template<typename U>
    static char test(typename U::iterator *x);

    template<typename U>
    static long test(U *x);

    static const bool value = sizeof(test<T>(0)) == 1;
};

template<bool B, class T = void>
struct __testlib_enable_if {
};

template<class T>
struct __testlib_enable_if<true, T> {
    typedef T type;
};

template<typename T>
typename __testlib_enable_if<!is_iterable<T>::value, void>::type __testlib_prll_one(const T &t) {
    std::cout << t;
}

template<typename T>
typename __testlib_enable_if<is_iterable<T>::value, void>::type __testlib_prll_one(const T &t) {
    bool first = true;
    for (typename T::const_iterator i = t.begin(); i != t.end(); i++) {
        if (first)
            first = false;
        else
            std::cout << " ";
        std::cout << *i;
    }
}

template<>
typename __testlib_enable_if<is_iterable<std::string>::value, void>::type
__testlib_prll_one<std::string>(const std::string &t) {
    std::cout << t;
}

template<typename A, typename B>
void __prllln_range(A begin, B end) {
    bool first = true;
    for (B i = B(begin); i != end; i++) {
        if (first)
            first = false;
        else
            std::cout << " ";
        __testlib_prll_one(*i);
    }
    std::cout << std::endl;
}

template<class T, class Enable = void>
struct is_iterator {
    static T makeT();

    typedef void *twoptrs[2];

    static twoptrs &test(...);

    template<class R>
    static typename R::iterator_category *test(R);

    template<class R>
    static void *test(R *);

    static const bool value = sizeof(test(makeT())) == sizeof(void *);
};

template<class T>
struct is_iterator<T, typename __testlib_enable_if<std::is_array<T>::value>::type> {
    static const bool value = false;
};

template<typename A, typename B>
typename __testlib_enable_if<!is_iterator<B>::value, void>::type prllln(const A &a, const B &b) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << std::endl;
}

template<typename A, typename B>
typename __testlib_enable_if<is_iterator<B>::value, void>::type prllln(const A &a, const B &b) {
    __prllln_range(a, b);
}

template<typename A>
void prllln(const A *a, const A *b) {
    __prllln_range(a, b);
}

template<>
void prllln<char>(const char *a, const char *b) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << std::endl;
}

template<typename T>
void prllln(const T &x) {
    __testlib_prll_one(x);
    std::cout << std::endl;
}

template<typename A, typename B, typename C>
void prllln(const A &a, const B &b, const C &c) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << " ";
    __testlib_prll_one(c);
    std::cout << std::endl;
}

template<typename A, typename B, typename C, typename D>
void prllln(const A &a, const B &b, const C &c, const D &d) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << " ";
    __testlib_prll_one(c);
    std::cout << " ";
    __testlib_prll_one(d);
    std::cout << std::endl;
}

template<typename A, typename B, typename C, typename D, typename E>
void prllln(const A &a, const B &b, const C &c, const D &d, const E &e) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << " ";
    __testlib_prll_one(c);
    std::cout << " ";
    __testlib_prll_one(d);
    std::cout << " ";
    __testlib_prll_one(e);
    std::cout << std::endl;
}

template<typename A, typename B, typename C, typename D, typename E, typename F>
void prllln(const A &a, const B &b, const C &c, const D &d, const E &e, const F &f) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << " ";
    __testlib_prll_one(c);
    std::cout << " ";
    __testlib_prll_one(d);
    std::cout << " ";
    __testlib_prll_one(e);
    std::cout << " ";
    __testlib_prll_one(f);
    std::cout << std::endl;
}

template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>
void prllln(const A &a, const B &b, const C &c, const D &d, const E &e, const F &f, const G &g) {
    __testlib_prll_one(a);
    std::cout << " ";
    __testlib_prll_one(b);
    std::cout << " ";
    __testlib_prll_one(c);
    std::cout << " ";
    __testlib_prll_one(d);
    std::cout << " ";
    __testlib_prll_one(e);
    std::cout << " ";
    __testlib_prll_one(f);
    std::cout << " ";
    __testlib_prll_one(g);
    std::cout << std::endl;
}

/* opts */
size_t getOptType(char* s) {
    if (!s || strlen(s) <= 1)
        return 0;

    if (s[0] == '-') {
        if (isalpha(s[1]))
            return 1;
        else if (s[1] == '-')
            return isalpha(s[2]) ? 2 : 0;
    }

    return 0;
}

size_t parseOpt(size_t argc, char* argv[], size_t index, std::map<std::string, std::string>& opts) {
    if (index >= argc)
        return 0;

    size_t type = getOptType(argv[index]), inc = 1;
    if (type > 0) {
        std::string key(argv[index] + type), val;
        size_t sep = key.find('=');
        if (sep != std::string::npos) {
            val = key.substr(sep + 1);
            key = key.substr(0, sep);
        } else {
            if (index + 1 < argc && getOptType(argv[index + 1]) == 0) {
                val = argv[index + 1];
                inc = 2;
            } else {
                if (key.length() > 1 && isdigit(key[1])) {
                    val = key.substr(1);
                    key = key.substr(0, 1);
                } else {
                    val = "true";
                }
            }
        }
        opts[key] = val;
    } else {
        return inc;
    }

    return inc;
}

std::vector<std::string> __testlib_argv;
std::map<std::string, std::string> __testlib_opts;

void prepareOpts(ll argc, char* argv[]) {
    if (argc <= 0)
        __testlib_fail("Opts: expected argc>=0 but found " + toString(argc));
    size_t n = static_cast<size_t>(argc); // NOLll(hicpp-use-auto,modernize-use-auto)
    __testlib_opts = std::map<std::string, std::string>();
    for (size_t index = 1; index < n; index += parseOpt(n, argv, index, __testlib_opts));
    __testlib_argv = std::vector<std::string>(n);
    for (size_t index = 0; index < n; index++)
        __testlib_argv[index] = argv[index];
}

std::string __testlib_indexToArgv(ll index) {
    if (index < 0 || index >= ll(__testlib_argv.size()))
        __testlib_fail("Opts: index '" + toString(index) + "' is out of range [0," + toString(__testlib_argv.size()) + ")");
    return __testlib_argv[size_t(index)];
}

std::string __testlib_keyToOpts(const std::string& key) {
    if (__testlib_opts.count(key) == 0)
        __testlib_fail("Opts: unknown key '" + compress(key) + "'");
    return __testlib_opts[key];
}

template<typename T>
T optValueTollegral(const std::string& s, bool nonnegative);

long double optValueToLongDouble(const std::string& s);

std::string parseExponentialOptValue(const std::string& s) {
    size_t pos = std::string::npos;
    for (size_t i = 0; i < s.length(); i++)
        if (s[i] == 'e' || s[i] == 'E') {
            if (pos != std::string::npos)
                __testlib_fail("Opts: expected typical exponential notation but '" + compress(s) + "' found");
            pos = i;
        }
    if (pos == std::string::npos)
        return s;
    std::string e = s.substr(pos + 1);
    if (!e.empty() && e[0] == '+')
        e = e.substr(1);
    if (e.empty())
        __testlib_fail("Opts: expected typical exponential notation but '" + compress(s) + "' found");
    if (e.length() > 20)
        __testlib_fail("Opts: expected typical exponential notation but '" + compress(s) + "' found");
    ll ne = optValueTollegral<ll>(e, false);
    std::string num = s.substr(0, pos);
    if (num.length() > 20)
        __testlib_fail("Opts: expected typical exponential notation but '" + compress(s) + "' found");
    if (!num.empty() && num[0] == '+')
        num = num.substr(1);
    optValueToLongDouble(num);
    bool minus = false;
    if (num[0] == '-') {
        minus = true;
        num = num.substr(1);
    }
    for (ll i = 0; i < +ne; i++) {
        size_t sep = num.find('.');
        if (sep == std::string::npos)
            num += '0';
        else {
            if (sep + 1 == num.length())
                num[sep] = '0';
            else
                std::swap(num[sep], num[sep + 1]);
        }
    }
    for (ll i = 0; i < -ne; i++) {
        size_t sep = num.find('.');
        if (sep == std::string::npos)
            num.insert(num.begin() + ll(num.length()) - 1, '.');
        else {
            if (sep == 0)
                num.insert(num.begin() + 1, '0');
            else
                std::swap(num[sep - 1], num[sep]);
        }
    }
    while (!num.empty() && num[0] == '0')
        num = num.substr(1);
    while (num.find('.') != std::string::npos && num.back() == '0')
        num = num.substr(0, num.length() - 1);
    if (!num.empty() && num.back() == '.')
        num = num.substr(0, num.length() - 1);
    if ((!num.empty() && num[0] == '.') || num.empty())
        num.insert(num.begin(), '0');
    return (minus ? "-" : "") + num;
}

template<typename T>
T optValueTollegral(const std::string& s_, bool nonnegative) {
    std::string s(parseExponentialOptValue(s_));
    if (s.empty())
        __testlib_fail("Opts: expected lleger but '" + compress(s_) + "' found");
    T value = 0;
    long double about = 0.0;
    signed char sign = +1;
    size_t pos = 0;
    if (s[pos] == '-') {
        if (nonnegative)
            __testlib_fail("Opts: expected non-negative lleger but '" + compress(s_) + "' found");
        sign = -1;
        pos++;
    }
    for (size_t i = pos; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9')
            __testlib_fail("Opts: expected lleger but '" + compress(s_) + "' found");
        value = value * 10 + s[i] - '0';
        about = about * 10 + s[i] - '0';
    }
    value *= sign;
    about *= sign;
    if (fabsl(value - about) > 0.1)
        __testlib_fail("Opts: lleger overflow: expected lleger but '" + compress(s_) + "' found");
    return value;
}

long double optValueToLongDouble(const std::string& s_) {
    std::string s(parseExponentialOptValue(s_));
    if (s.empty())
        __testlib_fail("Opts: expected float number but '" + compress(s_) + "' found");
    long double value = 0.0;
    signed char sign = +1;
    size_t pos = 0;
    if (s[pos] == '-') {
        sign = -1;
        pos++;
    }
    bool period = false;
    long double mul = 1.0;
    for (size_t i = pos; i < s.length(); i++) {
        if (s[i] == '.') {
            if (period)
                __testlib_fail("Opts: expected float number but '" + compress(s_) + "' found");
            else {
                period = true;
                continue;
            }
        }
        if (period)
            mul *= 10.0;
        if (s[i] < '0' || s[i] > '9')
            __testlib_fail("Opts: expected float number but '" + compress(s_) + "' found");
        if (period)
            value += (s[i] - '0') / mul;
        else
            value = value * 10 + s[i] - '0';
    }
    value *= sign;
    return value;
}

bool has_opt(const std::string key) {
    return __testlib_opts.count(key) != 0;
}

template<typename T>
T opt(std::false_type, ll index);

template<>
std::string opt(std::false_type, ll index) {
    return __testlib_indexToArgv(index);
}

template<typename T>
T opt(std::true_type, ll index) {
    return T(optValueToLongDouble(__testlib_indexToArgv(index)));
}

template<typename T, typename U>
T opt(std::false_type, U, ll index) {
    return opt<T>(std::is_floating_poll<T>(), index);
}

template<typename T>
T opt(std::true_type, std::false_type, ll index) {
    return optValueTollegral<T>(__testlib_indexToArgv(index), false);
}

template<typename T>
T opt(std::true_type, std::true_type, ll index) {
    return optValueTollegral<T>(__testlib_indexToArgv(index), true);
}

template<>
bool opt(std::true_type, std::true_type, ll index) {
    std::string value = __testlib_indexToArgv(index);
    if (value == "true" || value == "1")
        return true;
    if (value == "false" || value == "0")
        return false;
    __testlib_fail("Opts: opt by index '" + toString(index) + "': expected bool true/false or 0/1 but '" + compress(value) + "' found");
}

template<typename T>
T opt(ll index) {
    return opt<T>(std::is_llegral<T>(), std::is_unsigned<T>(), index);
}

std::string opt(ll index) {
    return opt<std::string>(index);
}

template<typename T>
T opt(std::false_type, const std::string& key);

template<>
std::string opt(std::false_type, const std::string& key) {
    return __testlib_keyToOpts(key);
}

template<typename T>
T opt(std::true_type, const std::string& key) {
    return T(optValueToLongDouble(__testlib_keyToOpts(key)));
}

template<typename T, typename U>
T opt(std::false_type, U, const std::string& key) {
    return opt<T>(std::is_floating_poll<T>(), key);
}

template<typename T>
T opt(std::true_type, std::false_type, const std::string& key) {
    return optValueTollegral<T>(__testlib_keyToOpts(key), false);
}

template<typename T>
T opt(std::true_type, std::true_type, const std::string& key) {
    return optValueTollegral<T>(__testlib_keyToOpts(key), true);
}

template<>
bool opt(std::true_type, std::true_type, const std::string& key) {
    if (!has_opt(key))
        return false;
    std::string value = __testlib_keyToOpts(key);
    if (value == "true" || value == "1")
        return true;
    if (value == "false" || value == "0")
        return false;
    __testlib_fail("Opts: key '" + compress(key) + "': expected bool true/false or 0/1 but '" + compress(value) + "' found");
}

template<typename T>
T opt(const std::string key) {
    return opt<T>(std::is_llegral<T>(), std::is_unsigned<T>(), key);
}

std::string opt(const std::string key) {
    return opt<std::string>(key);
}
#endif
#endif