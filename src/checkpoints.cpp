// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
       (      0, uint256("0x000002cac270a01e29300abaaeb7d412ca00fa7f43f0d547a57b9ff9c85d95e8"))
       (    100, uint256("0x00000c8f8f6fb876b152e184f73f5e3268d539ec0bce3705fac501af0de42031"))
       (   1000, uint256("0x000006bf4aa4a8da4933675be303ade4e361e38eb561d108b9dd9b07e6350f2a"))
       (  10000, uint256("0xbfb0a611b1c045c502c1839bb60ddb8d4828ee35ad524a8a4e44fbde96f9b0fd"))
       (  50000, uint256("0x00000000001fc332b5cdcdea04d168c81c311161c47c0c68f549a7941196e0a2"))
       ( 100000, uint256("0xde54b5cc380063f32f90dc1af4f5b7bb0e7226376bc81c50adf804c772478d59"))
       ( 150000, uint256("0xdb39ebc6c0653fc0a415cb625feb63b000253f4a9a04530ca5ca6cd5bebfec3d"))
       ( 200000, uint256("0x0000000002f9f5cfd7c9ea589583220fa9eb86c22576f73d40d611dc5cd9b2ba"))
       ( 250000, uint256("0x62a249523891e824591b0ad11f9fbe9eede6e468b451d6a23c45f1df7d293fec"))
       ( 300000, uint256("0x0000000000b7e25fba047eafe4f63b795e09d1123fe4eab726d6d0a6dd5d5b56"))
       ( 400000, uint256("0x0000000002ba3bbb771bb96003b05b05e8e390aba69d566fe80e16c82687e1e5"))
       ( 500000, uint256("0x0bb0c31492c2822a300283de9efc30b4a0b8330816494df862c6a8f6eedd4295"))
       ( 600000, uint256("0x6e3d7789ba9884df704cedffb379bbaa818155de945cabdbb5070d547b356144"))
       ( 700000, uint256("0x8b468893fbd92361c54837cf4bbe7d9a52cf3818e324457a19100dd7258347f7"))
       ( 800000, uint256("0xeee5f95e742dc7dfb98ddd889e231e4a2390a9ab96541941859ed8f5a0112653"))
       ( 900000, uint256("0x0000000002c01bbcf8b54a450f6709e710905326ef3b05a6182ae49150801238"))
       (1000000, uint256("0x0000000000b4a5f3a11c52d7495e789ab3dbca8313d54736f803efba81bfb057"))
       (1100000, uint256("0x0000000001a6ca32cd6c8fee3dadabcff15b610b4e447af005f8b8687aeb32bf"))
       (1200000, uint256("0x91953f74c55fce96e4c37e81a880faf58523960f91275a9a7453dbd9376b16fd"))
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
