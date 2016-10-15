#include "Windmill.h"
#include "TransformNode.h"

Windmill::Windmill(std::string bodyTexture, std::string bladeTexture)
{
	m_bodyTexturePath = bodyTexture;
	m_bladeTexutrePath = bladeTexture;
}

void Windmill::CreateWindmill(sf::Vector2<float> position)
{
	m_position = position;

	m_windMillBaseTexture.loadFromFile(m_bodyTexturePath);

	m_windMillBladeTexture.loadFromFile(m_bladeTexutrePath);


	m_windMillBaseSprite.setTexture(m_windMillBaseTexture);
	m_windMillBaseSprite.setScale(0.5f, 0.5f);
	m_windMillBaseSprite.setPosition(m_position);

	m_windMillBodyOrigin.x = -m_windMillBaseSprite.getLocalBounds().width;
	m_windMillBodyOrigin.y = -50.0f;

	m_windMillBaseSprite.setOrigin(m_windMillBaseSprite.getLocalBounds().width/2, m_windMillBaseSprite.getLocalBounds().height/2);
	

	//TOP BLADE
	m_windMillBladeSpriteT.setTexture(m_windMillBladeTexture);
	m_windMillBladeSpriteT.setScale(1.2f, 1.0f);
	m_windMillBladeSpriteT.setOrigin(0.0f, m_windMillBladeSpriteT.getLocalBounds().height);
	m_windMillBladeSpriteT.setPosition(0.0f, -m_windMillBaseSprite.getLocalBounds().height / 2);


	//RIGHT BLADE
	m_windMillBladeSpriteR.setTexture(m_windMillBladeTexture);
	m_windMillBladeSpriteT.setScale(1.2f, 1.0f);
	m_windMillBladeSpriteR.setOrigin(0.0f, m_windMillBladeSpriteR.getLocalBounds().height);
	m_windMillBladeSpriteR.setPosition(0.0f, -m_windMillBaseSprite.getLocalBounds().height / 2);
	m_windMillBladeSpriteR.setRotation(90);

	//BOTTOM BLADE
	m_windMillBladeSpriteB.setTexture(m_windMillBladeTexture);
	m_windMillBladeSpriteT.setScale(1.2f, 1.0f);
	m_windMillBladeSpriteB.setOrigin(0.0f, m_windMillBladeSpriteB.getLocalBounds().height);
	m_windMillBladeSpriteB.setPosition(0.0f, -m_windMillBaseSprite.getLocalBounds().height / 2);
	m_windMillBladeSpriteB.setRotation(180);

	//LEFT BLADE
	m_windMillBladeSpriteL.setTexture(m_windMillBladeTexture);
	m_windMillBladeSpriteT.setScale(1.2f, 1.0f);
	m_windMillBladeSpriteL.setOrigin(0.0f, m_windMillBladeSpriteL.getLocalBounds().height);
	m_windMillBladeSpriteL.setPosition(0.0f, -m_windMillBaseSprite.getLocalBounds().height / 2);
	m_windMillBladeSpriteL.setRotation(270);



	m_baseN.m_CurrentShape = &m_windMillBaseSprite;
	m_bladeNT.m_CurrentShape = &m_windMillBladeSpriteT;
	m_bladeNR.m_CurrentShape = &m_windMillBladeSpriteR;
	m_bladeNB.m_CurrentShape = &m_windMillBladeSpriteB;
	m_bladeNL.m_CurrentShape = &m_windMillBladeSpriteL;

	m_baseN.AddChild(&m_bladeNT);
	m_baseN.AddChild(&m_bladeNR);
	m_baseN.AddChild(&m_bladeNB);
	m_baseN.AddChild(&m_bladeNL);

}

void Windmill::ResetPosiiton() 
{
	m_windMillBaseSprite.setRotation(0);
	m_transform = m_ParentTransform;
	
}

sf::Vector2<float> Windmill::DrawWindmill(sf::RenderTarget *target, float xMov, float yMov, float roatPointX, float rotPointY, const sf::Transform &parentTransform)
{
	float angleAmount = 90.0f;
	m_ParentTransform = parentTransform;

	m_elaspedTime = m_deltaTime.restart().asSeconds();

	m_windMillBladeSpriteT.rotate(angleAmount * m_elaspedTime);
	m_windMillBladeSpriteR.rotate(angleAmount * m_elaspedTime);
	m_windMillBladeSpriteB.rotate(angleAmount * m_elaspedTime);
	m_windMillBladeSpriteL.rotate(angleAmount * m_elaspedTime);

	m_windMillBaseSprite.rotate(xMov);
	m_transform.rotate(yMov , { roatPointX, rotPointY });

	m_baseN.Draw(target, m_transform);

	sf::Vector2<float> position;
	position.x = m_windMillBaseSprite.getGlobalBounds().left;
	position.y = m_windMillBaseSprite.getGlobalBounds().top;

	return position;
}
