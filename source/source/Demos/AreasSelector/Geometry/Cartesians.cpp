#include "Cartesians.h"

namespace Geometry
{

	Cartesians::Cartesians()
		: xOffset_(0)
		, yOffset_(0)
		, xOffsetBackup_(0)
		, yOffsetBackup_(0)
		, scale_(1.0f)
		, viewportWidth_(0)
		, viewportHeight_(0)
		, dataWidth_(0)
		, dataHeight_(0)
	{
	}

	// State initializers
	void Cartesians::Reset()
	{
		xOffset_ = 0;
		yOffset_ = 0;
		scale_ = 1.0f;
	}

	// Data modifiers
	void Cartesians::SetViewport(int width, int height)
	{
		viewportWidth_ = width;
		viewportHeight_ = height;
	}

	void Cartesians::SetData(int width, int height)
	{
		dataWidth_ = width;
		dataHeight_ = height;
	}

	void Cartesians::SetXOffset(int xOffset)
	{
		xOffset_ = xOffset;
		if ( xOffset_ < 0 )
			xOffset_ = 0;
	}

	void Cartesians::SetYOffset(int yOffset)
	{
		yOffset_ = yOffset;
		if ( yOffset_ < 0 )
			yOffset_ = 0;
	}

	// Information providers
	int Cartesians::GetXOffset()
	{
		return xOffset_;
	}

	int Cartesians::GetYOffset()
	{
		return yOffset_;
	}

	int Cartesians::GetHorizMax()
	{
		int max = dataWidth_ * scale_ - viewportWidth_;
		return ( max > 0 ) ? ( max ) : ( 0 );
	}

	int Cartesians::GetHorizStep()
	{
		return dataWidth_;
	}

	int Cartesians::GetVertMax()
	{
		int max = dataHeight_ * scale_ - viewportHeight_;
		return ( max > 0 ) ? ( max ) : ( 0 );
	}

	int Cartesians::GetVertStep()
	{
		return dataHeight_;
	}

	float Cartesians::GetScale()
	{
		return scale_;
	}

	// Configurators
	void Cartesians::ConfigurePainterWindow(int& x, int& y, int& width, int& height)
	{
		x = xOffset_;
		y = yOffset_;
		width = viewportWidth_;
		height = viewportHeight_;
	}

	void Cartesians::ConfigureSource(int& x, int& y, int& width, int& height)
	{
		x = xOffset_ / scale_;
		y = yOffset_ / scale_;
		width = viewportWidth_ / scale_ + 1;
		height = viewportHeight_ / scale_ + 1;

		if ( dataWidth_ * scale_ < viewportWidth_ )
		{
			x = 0;
			width = dataWidth_;
		}

		if ( dataHeight_ * scale_ < viewportHeight_ )
		{
			y = 0;
			height = dataHeight_;
		}
	}

	void Cartesians::ConfigureTarget(int& x, int& y, int& width, int& height)
	{
		x = xOffset_ / scale_;
		y = yOffset_ / scale_;
		width = viewportWidth_ / scale_ + 1;
		height = viewportHeight_ / scale_ + 1;

		int srcX, srcY, srcWidth, srcHeight;
		ConfigureSource(srcX, srcY, srcWidth, srcHeight);

		if ( dataWidth_ * scale_ < viewportWidth_ )
		{
			x = 0;
			width = srcWidth;
		}

		if ( dataHeight_ * scale_ < viewportHeight_ )
		{
			y = 0;
			height = srcHeight;
		}
	}

	// Transformation tools
	int Cartesians::InverseX(int x)
	{
		return ( x + xOffset_ ) / scale_;
	}

	int Cartesians::InverseY(int y)
	{
		return ( y + yOffset_ ) / scale_;
	}

	// Controls
	bool Cartesians::Zoom(float ratio, int x, int y)
	{
		if ( 
			( scale_ < 0.1 && ratio < 1 ) || 
			( scale_ > 10 && ratio >= 1 ) || 
			( ratio == 1 ) )
			return false;

		float oldScale = scale_;

		scale_ *= ratio;

		int xOldImgOffset = xOffset_ / oldScale;
		int yOldImgOffset = yOffset_ / oldScale;

		int imgX = ( x + xOffset_ ) / oldScale;
		int imgY = ( y + yOffset_ ) / oldScale;

		int xImgOffset = imgX - ( viewportWidth_ / 2 ) / scale_;
		int yImgOffset = imgY - ( viewportHeight_ / 2 ) / scale_;

		xOffset_ = xImgOffset * scale_;
		yOffset_ = yImgOffset * scale_;

		if ( xOffset_ < 0 )
			xOffset_ = 0;

		if ( yOffset_ < 0 )
			yOffset_ = 0;

		int horizMax = GetHorizMax();
		if ( xOffset_ > horizMax )
			xOffset_ = horizMax /* - 1 */;

		int vertMax = GetVertMax();
		if ( yOffset_ > vertMax )
			yOffset_ = vertMax /* - 1 */;

		return true;
	}

	// Serialization
	void Cartesians::BackupOffset()
	{
		xOffsetBackup_ = xOffset_;
		yOffsetBackup_ = yOffset_;
	}

	void Cartesians::RestoreOffset()
	{
		xOffset_ = xOffsetBackup_;
		yOffset_ = yOffsetBackup_;
	}

}
