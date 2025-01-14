#include "stdafx.h"
#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount,
                     float switchTime, int row, bool faceRight)
{
    this->texture = texture;
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    this->row = row;
    this->faceRight = faceRight;

    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::update(float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= imageCount.x)
            currentImage.x = 0;
    }

    uvRect.top = currentImage.y * uvRect.height;
    if(faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}
