#include "CircularButton.hpp"
#include "GraphicsObject.hpp"

CircularButton::CircularButton(std::string name, int16 x, int16 y, int16 z, int16 radius, bool drawUVsInReverse)
: Button(x, y)
, buttonQuad_(x, y, z, radius*2, radius*2, 0)
, radius_(radius)
, buttonMaterial_(0)
, buttonTexture_(0)
, drawUVsInReverse_(drawUVsInReverse)
{
	buttonTexture_ = new CIwTexture;
	buttonTexture_->LoadFromFile(name.c_str());

// Replace texture assignment with the following in order to use resource groups
// The group name will need to be either hardcoded or passed to this method
//	CIwResGroup* group = IwGetResManager()->GetGroupNamed(group_name);
//	buttonTexture_ = (CIwTexture*)group->GetResNamed(name.c_str(), "CIwTexture");

	buttonTexture_->Upload();

	buttonMaterial_ = new Material;
	buttonMaterial_->setTexture(buttonTexture_);
}

CircularButton::~CircularButton()
{
	if(buttonTexture_)
	{
		delete buttonTexture_;

		buttonTexture_ = 0;
	}

	delete buttonMaterial_;
	buttonMaterial_ = 0;
}

void CircularButton::render()
{
	buttonMaterial_->use(drawUVsInReverse_);
	
	// Render the image
	buttonQuad_.render();
}

bool CircularButton::collisionDetection(const int16 touchX, const int16 touchY) const
{
	int xDis = (touchX - x_) * ( touchX - x_);
	int yDis = (touchY - y_) * ( touchY - y_);
	int radiusSquared = radius_* radius_ ;
	
	if( ( xDis + yDis ) < ( radiusSquared ) )
	{
		// return being collided with
		return true;
	}
	else
	{
		// Return not being collided with
		return false;
	}
}