#include <stdio.h>
#include <string.h>

#include "PGMTool.h"

namespace Serialization
{

	PGMTool::PGMTool(const char* filename)
		: pBuffer_(NULL)
		, width_(0)
		, height_(0)
	{
		try
		{
			Load(filename);
		}
		catch ( ... )
		{
		}
	}

	PGMTool::~PGMTool()
	{
	}	

	unsigned char* PGMTool::GetBuffer()
	{
		return pBuffer_;
	}

	unsigned int PGMTool::GetWidth()
	{
		return width_;
	}

	unsigned int PGMTool::GetHeight()
	{
		return height_;
	}
	
	void PGMTool::Load(const char* filename)
	{
		FILE* fp = fopen(filename, "rb");
		if ( !fp )
			return;

		int	count;
		char line[255];
		int	maxg2;
		char* next;
		int	step;
		int	width;
		char word[255];

		step = 0;

		bool bFinishCondition = true;
		while ( bFinishCondition )
		{
			char* pRead = fgets(line, sizeof(line), fp);

			if ( !pRead )
				return;

			next = line;

			if ( line[0] == '#' )
				continue;

			if ( step == 0 )
			{
				count = sscanf(next, "%s%n", word, &width);
				if ( count == EOF )
					continue;

				next = next + width;
				if ( strcmp(word, "P5" ) != 0 && strcmp(word, "p5") != 0)
					return;

				step = 1;
			}

			if ( step == 1 )
			{
				count = sscanf(next, "%d%n", &width_, &width);
				next = next + width;

				if (count == EOF)
					continue;

				step = 2;
			}

			if (step == 2)
			{
				count = sscanf(next, "%d%n", &height_, &width);
				next = next + width;

				if (count == EOF)
					continue;

				step = 3;
			}

			if (step == 3)
			{
				count = sscanf(next, "%d%n", &maxg2, &width);
				next = next + width;

				if (count == EOF)
					continue;

				break;
			}
		}

		pBuffer_ = new unsigned char[width_ * height_];
		
		fread(pBuffer_, width_ * height_, 1, fp);

		fclose(fp);
	}

}
