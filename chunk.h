#pragma once
#include <vector>
#include <block.h>
using namespace std;

enum ChunkConstants
{
	SectionsPerChunk = 16,

	BlockEdgeWidthInSection = 16,
	
	BlocksInSection = BlockEdgeWidthInSection * BlockEdgeWidthInSection * BlockEdgeWidthInSection
};

class ChunkSectionStorage
{
public:
	ChunkSectionStorage() {};
	BlockState Data[ChunkConstants::BlockEdgeWidthInSection][ChunkConstants::BlockEdgeWidthInSection][ChunkConstants::BlockEdgeWidthInSection];

	/*byte[, , ] BlockLight{ get; } = new byte[ChunkConstants.ChunkConstantsBlockEdgeWidthInSection, ChunkConstants.BlockEdgeWidthInSection, ChunkConstants.BlockEdgeWidthInSection];

	byte[, , ] SkyLight{ get; }*/

	ChunkSectionStorage(bool hasSkylight)
	{
		/*if (hasSkylight)
			SkyLight = new byte[ChunkConstants.BlockEdgeWidthInSection, ChunkConstants.BlockEdgeWidthInSection, ChunkConstants.BlockEdgeWidthInSection];*/
	}

	/*ChunkSectionCompactStorage Compact()
	{
		void CompactNibble(byte[, , ] source, byte[] dest)
		{
			int index = 0;
			for (int y = 0; y < ChunkConstants.BlockEdgeWidthInSection; y++)
			{
				for (int z = 0; z < ChunkConstants.BlockEdgeWidthInSection; z++)
				{
					for (int x = 0; x < ChunkConstants.BlockEdgeWidthInSection / 2; x++)
					{
						dest[index++] = (byte)((source[x * 2, y, z] << 4) | (source[x * 2 + 1, y, z] & 0xF));
					}
				}
			}
		}

		var storage = new ChunkSectionCompactStorage(SkyLight != null);
		CompactNibble(BlockLight, storage.BlockLight.Storage);
		if (SkyLight != null)
			CompactNibble(SkyLight, storage.SkyLight.Storage);

		int indexOffset = 0;
		int bitOffset = 0;
		var data = storage.Data.Storage;
		for (int y = 0; y < ChunkConstants.BlockEdgeWidthInSection; y++)
		{
			for (int z = 0; z < ChunkConstants.BlockEdgeWidthInSection; z++)
			{
				for (int x = 0; x < ChunkConstants.BlockEdgeWidthInSection; x++)
				{
					ulong blockValue = ChunkSectionCompactStorage.ToUInt32(ref Data[x, y, z]);

					var tmpValue = data[indexOffset];
					var mask = ChunkSectionCompactStorage.BlockMask << bitOffset;
					var toWrite = Math.Min(storage.BitsPerBlock, 64 - bitOffset);
					data[indexOffset] = (tmpValue & ~mask) | (blockValue << bitOffset);
					bitOffset += toWrite;
					var rest = storage.BitsPerBlock - toWrite;
					if (rest > 0)
					{
						mask = (1u << rest) - 1;
						blockValue >>= toWrite;
						data[++indexOffset] = blockValue & mask;
						bitOffset = rest;
					}

					if (bitOffset == 64)
					{
						indexOffset++;
						bitOffset = 0;
					}
				}
			}
		}

		return storage;
	}*/
};

class ChunkColumnStorage
{
public:
	ChunkColumnStorage() {};
	ChunkSectionStorage Sections[ChunkConstants::SectionsPerChunk];

	int Biomes[256];

	BlockState& operator ()(int x, int y, int z)
	{
		return Sections[y / 16].Data[x][y % 16][z];
		/*get = > Sections[y / 16].Data[x, y % 16, z];
		set = > Sections[y / 16].Data[x, y % 16, z] = value;*/
	}

	/*	public ChunkColumnCompactStorage Compact()
	{
		var storage = new ChunkColumnCompactStorage();
		for (int i = 0; i < Sections.Length; i++)
			storage.Sections[i] = Sections[i] ? .Compact();

		Buffer.BlockCopy(Biomes, 0, storage.Biomes, 0, Biomes.Length);
		return storage;
	}*/
};