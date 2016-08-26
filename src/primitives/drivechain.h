// Copyright (c) 2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DRIVECHAIN_H
#define DRIVECHAIN_H

#include "coins.h"
#include "pubkey.h"
#include "script/script.h"
#include "serialize.h"
#include "uint256.h"

#include <limits.h>
#include <string>

using namespace std;

// uint256 hash (sidechainid) of THIS sidechain
static const uint256 SIDECHAIN_ID = uint256S("0xca85db47c45dfccfa9f5562f7383c7b3fe1746017327371771ed3f70345b72d4");

/**
 * Drivechain object for database
 */
struct drivechainObj {
    char drivechainop;
    uint32_t nHeight;
    uint256 txid;

    drivechainObj(void): nHeight(INT_MAX) { }
    virtual ~drivechainObj(void) { }

    uint256 GetHash(void) const;
    CScript GetScript(void) const;
    virtual string ToString(void) const;
};

/**
 * Create drivechain object
 */
drivechainObj *drivechainObjCtr(const CScript &script);

/**
 * Drivechain deposit from mainchain
 */
struct drivechainDeposit : public drivechainObj {
    uint256 txid;
    uint256 sidechainid;
    CKeyID keyID;
    CTransaction deposit;

    drivechainDeposit(void) : drivechainObj() { drivechainop = 'D'; }
    virtual ~drivechainDeposit(void) { }

    ADD_SERIALIZE_METHODS

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(drivechainop);
        READWRITE(txid);
        READWRITE(sidechainid);
        READWRITE(keyID);
        READWRITE(deposit);
    }

    string ToString(void) const;
};

/**
 * An individual drivechain withdraw to mainchain (wt)
 */
struct drivechainWithdraw : public drivechainObj {
    uint256 txid;
    uint256 sidechainid;
    CKeyID keyID;
    CTransaction wt;

    drivechainWithdraw(void) : drivechainObj() { drivechainop = 'W'; }
    virtual ~drivechainWithdraw(void) { }

    ADD_SERIALIZE_METHODS

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(drivechainop);
        READWRITE(txid);
        READWRITE(sidechainid);
        READWRITE(keyID);
        READWRITE(wt);
    }

    string ToString(void) const;
};

/**
 * Joined drivechain withdraw(s) to mainchain (WT^)
 */
struct drivechainJoinedWT: public drivechainObj {
    uint256 txid;
    uint256 sidechainid;
    CKeyID keyID;
    CTransaction wtJoined;

    drivechainJoinedWT(void) : drivechainObj() { drivechainop = 'J'; }
    virtual ~drivechainJoinedWT(void) { }

    ADD_SERIALIZE_METHODS

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(drivechainop);
        READWRITE(txid);
        READWRITE(sidechainid);
        READWRITE(keyID);
        READWRITE(wtJoined);
    }

    string ToString(void) const;
};

#endif // DRIVECHAIN_H
