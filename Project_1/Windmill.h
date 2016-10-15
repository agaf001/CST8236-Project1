#include <string>
#include <SFML/Graphics.hpp>
#include "TransformNode.h"

class Windmill 
{
public:
	Windmill(std::string bodyTexture, std::string bladeTexture);
	sf::Vector2<float> DrawWindmill(sf::RenderTarget *target, float xMov, float yMov, float roatPointX, float rotPointY, const sf::Transform &parentTransform = sf::Transform::Identity);
	void CreateWindmill(sf::Vector2<float> position);
	void Windmill::ResetPosiiton();

private:
	std::string m_bodyTexturePath;
	std::string m_bladeTexutrePath;
	TransformNode m_baseN;
	TransformNode m_bladeNT;
	TransformNode m_bladeNR;
	TransformNode m_bladeNB;
	TransformNode m_bladeNL;

	sf::Sprite m_windMillBaseSprite;
	sf::Sprite m_windMillBladeSpriteT;
	sf::Sprite m_windMillBladeSpriteR;
	sf::Sprite m_windMillBladeSpriteB;
	sf::Sprite m_windMillBladeSpriteL;
	

	sf::Texture m_windMillBaseTexture;
	sf::Texture m_windMillBladeTexture;

	sf::Vector2<float> m_windMillBodyOrigin;

	float m_elaspedTime;

	sf::Clock m_deltaTime;

	sf::Vector2<float> m_position;
	sf::Transform m_transform;
	sf::Transform m_ParentTransform;
	
};