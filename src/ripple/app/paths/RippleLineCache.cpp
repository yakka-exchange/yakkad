//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

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

#include <ripple/app/paths/RippleLineCache.h>
#include <ripple/app/paths/TrustLine.h>
#include <ripple/ledger/OpenView.h>

namespace ripple {

RippleLineCache::RippleLineCache(
    std::shared_ptr<ReadView const> const& ledger,
    beast::Journal j)
    : journal_(j)
{
    mLedger = ledger;

    JLOG(journal_.debug()) << "RippleLineCache created for ledger "
                           << mLedger->info().seq;
}

RippleLineCache::~RippleLineCache()
{
    JLOG(journal_.debug()) << "~RippleLineCache destroyed for ledger "
                           << mLedger->info().seq << " with " << lines_.size()
                           << " accounts";
}

std::vector<PathFindTrustLine> const&
RippleLineCache::getRippleLines(AccountID const& accountID)
{
    AccountKey key(accountID, hasher_(accountID));

    std::lock_guard sl(mLock);

    auto [it, inserted] = lines_.emplace(key, std::vector<PathFindTrustLine>());

    if (inserted)
        it->second = PathFindTrustLine::getItems(accountID, *mLedger);

    JLOG(journal_.debug()) << "RippleLineCache getRippleLines for ledger "
                           << mLedger->info().seq << " found "
                           << it->second.size() << " lines for "
                           << (inserted ? "new " : "existing ") << accountID
                           << " out of a total of " << lines_.size()
                           << " accounts";

    return it->second;
}

}  // namespace ripple
