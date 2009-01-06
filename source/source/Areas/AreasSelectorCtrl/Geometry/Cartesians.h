#ifndef CARTESIANS_H__AREASSELECTOR__INCLUDED_
#define IBEHAVIOUR_H__AREASSELECTOR__INCLUDED_

namespace Geometry
{

	class Cartesians
	{
	public:

		Cartesians();

		// State initializers
		void Reset();

		// Data modifiers
		void SetViewport(int width, int height);

		void SetData(int width, int height);

		void SetXOffset(int xOffset);
		
		void SetYOffset(int yOffset);

		// Information providers
		int GetXOffset() const;
		
		int GetYOffset() const;

		int GetHorizMax() const;

		int GetHorizStep() const;

		int GetVertMax() const;

		int GetVertStep() const;

		float GetScale() const;

		// Configurators
		void ConfigurePainterWindow(int& x, int& y, int& width, int& height) const;

		void ConfigureSource(int& x, int& y, int& width, int& height) const;

		void ConfigureTarget(int& x, int& y, int& width, int& height) const;

		// Transformation tools
		int InverseX(int x) const;

		int InverseY(int y) const;

		// Controls
		bool Zoom(float ratio, int x, int y);

		// Serialization
		void BackupOffset();

		void RestoreOffset();

	private:

		int xOffset_;

		int yOffset_;

		int xOffsetBackup_;

		int yOffsetBackup_;

		float scale_;

		int viewportWidth_;

		int viewportHeight_;

		int dataWidth_;

		int dataHeight_;

	};

}

#endif // !IBEHAVIOUR_H__AREASSELECTOR__INCLUDED_
