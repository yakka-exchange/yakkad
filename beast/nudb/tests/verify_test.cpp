//------------------------------------------------------------------------------
/*
    This file is part of Beast: https://github.com/vinniefalco/Beast
    Copyright 2014, Vinnie Falco <vinnie.falco@gmail.com>

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#include <beast/nudb/verify.h>
#include <beast/nudb/tests/common.h>
#include <beast/unit_test/suite.h>

namespace beast {
namespace nudb {
namespace test {

class verify_test : public unit_test::suite
{
public:
    // Runs verify on the database and reports statistics
    void
    do_verify (nudb::path_type const& path)
    {
        auto const dp = path + ".dat";
        auto const kp = path + ".key";
        print(log, verify(dp, kp));
    }

    void
    run() override
    {
        if (arg().empty())
            return fail("missing unit test argument");
        do_verify(arg());
        pass();
    }
};

BEAST_DEFINE_TESTSUITE_MANUAL(verify,nudb,beast);

} // test
} // nudb
} // beast

