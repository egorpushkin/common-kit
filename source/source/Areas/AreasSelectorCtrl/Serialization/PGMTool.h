#ifndef PGMTOOL_H
#define PGMTOOL_H

namespace Serialization
{

	class PGMTool
	{

		PGMTool(const PGMTool&);
		const PGMTool& operator=(const PGMTool&);	

	public:

		PGMTool(const char* filename);
		virtual ~PGMTool();

		unsigned char* GetBuffer();
		unsigned int GetWidth();
		unsigned int GetHeight();

	private:

		void PGMTool::Load(const char* filename);

	private:

		unsigned char* pBuffer_;
		unsigned int width_;
		unsigned int height_;

	};

}

#endif // !PGMTOOL_H
