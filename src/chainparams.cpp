// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX Developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "pow.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"



//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
 static bool regenerate = true;

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000004a52cbc6eeab60f685b9eced6322f08054fde6e66f84be90f1aaced149a"))
    (25, uint256("0x000003ae47f0ddb3bc5d5f00b60cec8cb4a7af8eeda56fd2b4f8b69e37654067"))
    (50, uint256("0x000000290cc059e3d3c359c3f6d22ddc6ffdad30e65f65e5bb0b9f1db4b043bb"))
    (75, uint256("0x0000003322f39bc94a4bf0cf0fa76a699756d962a241a863d3c759fb8457d75a"))
    (100, uint256("0x0000000ebc5aca23a5f995941ca518dca50c7d592ebc7ce83b16647816d96c10"))
    (200, uint256("0x00000000527d3e30820e35c6ff834a00feaa8f59e1a4318d7087154206c7bdd9"))
    (90686, uint256("0x3d004615ce7548e9ea730c0739dd2839a1b711d251151e43a6170e61b827e7ab"))
    (167728, uint256("0x9a1ee047f5f0563ca85dda46108fdbd79afa282a8d6535191215621d930e44a8"))
    (167770, uint256("0xcccdddf22bde232ba81d104e59fd34c07028504512cddb386a8a74e79282c2e9"))
    (499999, uint256("0x6110243f208ecfdfca48eaf687aa1489e96fe57021efd2385bc5c632bb89ee19")) // Chain got stuck at block 499,999
    (727500, uint256("0x65dbf7329cf1daf6e4a07eb1d08b3faddc6efb50e4862b2db0e08c361d7e9390")); //Hopefully the final checkpoint before we move to the new chain

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1567999894, // * UNIX timestamp of last checkpoint block
    1582214182,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc1;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xc8;
        pchMessageStart[3] = 0x0b;
        vAlertPubKey = ParseHex("0000098d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50");
        nP2pPort = 9050;
        nRpcPort = 7050;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // RUPAYA starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // RUPAYA: 1 day
        nTargetSpacing = 1 * 60;  // RUPAYA: 1 minute
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 82000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPoWBlock = 200;
        //nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 210;
        nZerocoinStartTime = 1537326760; // October 17, 2017 4:30:00 AM
        //nBlockEnforceSerialRange = 895400; //Enforce serial range starting this block
        //nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        //nBlockFirstFraudulent = 891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 210; //Last valid accumulator checkpoint
        //nBlockEnforceInvalidUTXO = 902850; //Start enforcing the invalid UTXO's
        //nInvalidAmountFiltered = 268200*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 210; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        //nEnforceNewSporkKey = 1525158000; //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        //nRejectOldSporkKey = 1527811200; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         */
        const char* pszTimestamp = "Rupaya - Empowering individuals with financial freedom and privacy";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0498df5a68624f744686dfe66e3cbc053307c43c8970621a1371dcd772bd748058b29424c9edb86711913525693b1f160efa3d89b802db053982324e7a4b63c4ef") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 5;
        genesis.nAccumulatorCheckpoint = 0;
        genesis.nTime = 1676040784;
        genesis.nBits = 504365040;
        genesis.nNonce = 462387;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            assert(hashGenesisBlock == uint256("0x000004a52cbc6eeab60f685b9eced6322f08054fde6e66f84be90f1aaced149a"));
            assert(genesis.hashMerkleRoot == uint256("0x4dca438430ad9ca73a7b6f5403c4e1ba597501828f3ea5700f23b994facc78b7"));
        }


        vSeeds.push_back(CDNSSeedData("seeder-1.rupx.io", "seeder-1.rupx.io"));
        vSeeds.push_back(CDNSSeedData("seeder-2.rupx.io", "seeder-2.rupx.io"));
        vSeeds.push_back(CDNSSeedData("seeder-2.rupx.io", "seeder-3.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-01.rupx.io", "node-01.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-02.rupx.io", "node-02.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-03.rupx.io", "node-03.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-04.rupx.io", "node-04.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-05.rupx.io", "node-05.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-06.rupx.io", "node-06.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-07.rupx.io", "node-07.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-08.rupx.io", "node-08.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-09.rupx.io", "node-09.rupx.io"));
        vSeeds.push_back(CDNSSeedData("node-10.rupx.io", "node-10.rupx.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60); // Rupaya's wallet address starts with a R
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 15); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 55); // P
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04ea22754eced5252fd71def2b9f690459a8a7eb4f1335638be4723f75ae340d6b6df4b6ed29e443cb767ef38459435a3b636d2dd3baa4c6875f8f5b58e0d96930";
        strObfuscationPoolDummyAddress = "RHD3HxhEkWGsupqZeN1p3QkvZq7EjQTCQH";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zrupx to be stakable
        nStakeMinAge = 60 * 60; //The number of seconds that a utxo must be old before it can qualify for staking
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x4c;
        pchMessageStart[1] = 0x7e;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("0441368f7cdaaf61526a27262b255af8c8453f967e543b32faee550439f13138fccdf6b8196ddb290081c2796dc053164a849d64ef9331e8ace3f7ebf9d438d846");
        nP2pPort = 10500;
        nRpcPort = 11000;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // RUPAYA: 1 day
        nTargetSpacing = 1 * 60;  // RUPAYA: 1 minute
        nLastPoWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        //nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        //nZerocoinStartHeight = 201576;
        //nZerocoinStartTime = 1501776000;
        //nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        //nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        //nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        //nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        //nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        //nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        //nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        //nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        //nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1549065600;
        genesis.nNonce = 2390925;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            assert(hashGenesisBlock == uint256("0x000003df45253cc78109cec5f9f11d602bd55d9665b6f4710ebbe8ddf89e1a37"));
            assert(genesis.hashMerkleRoot == uint256("0x4dca438430ad9ca73a7b6f5403c4e1ba597501828f3ea5700f23b994facc78b7"));
        }

        vSeeds.clear();
         vSeeds.push_back(CDNSSeedData("tnseeder-01.rupaya.io", "tnseeder-01.rupaya.io"));
         vSeeds.push_back(CDNSSeedData("testnode-01.rupaya.io", "testnode-01.rupaya.io"));
         vSeeds.push_back(CDNSSeedData("testnode-02.rupaya.io", "testnode-02.rupaya.io"));
         vSeeds.push_back(CDNSSeedData("testnode-03.rupaya.io", "testnode-03.rupaya.io"));
         vSeeds.push_back(CDNSSeedData("testnode-04.rupaya.io", "testnode-04.rupaya.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 17); // Testnet rupaya addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet rupaya script addresses start with '8'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 65);     // Testnet private keys start with 'T'
        // Testnet rupaya BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet rupaya BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet rupaya BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04acff02fc6183191a8f109cd4d7787e4e5c68e760284e7ab22d95337ac2c76669abf2b9350218a43ae56b5b9fa5b6817881a3f901273091232b6ab85bda068e27";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // RUPAYA: 1 day
        nTargetSpacing = 1 * 60;        // RUPAYA: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1533927507;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        nP2pPort = 51476;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtest ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            assert(hashGenesisBlock == uint256("0x7dbb050fde7e11bdfbfed6ef3cee609af3c0a33b0f984e76a3b7c0259dd7e285"));
            assert(genesis.hashMerkleRoot == uint256("0x4dca438430ad9ca73a7b6f5403c4e1ba597501828f3ea5700f23b994facc78b7"));
        }
        if (regenerate)
            exit(0);

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nP2pPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
