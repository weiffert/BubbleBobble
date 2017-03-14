#include "GameState.h"

GameState::GameState(std::string level)
{
}

GameState::~GameState()
{
    //dtor
}

void GameState::pause()
{

}

void GameState::processEvents(sf::RenderWindow &window, sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
    }
    //Loops through all entities
    for(int i = 0; i < objectVector.size(); i++)
    {
        //Loops through entities ID's
        for(int r = 0; r < objectVector.at(i)->getID().size(); r++ )
        {
            if( objectVector.at(i)->getID().at(r) == "playerEvents")
            {
                PlayerEvents(*objectVector.at(i), event);
            }
        }
    }
 }

void GameState::process(sf::RenderWindow &window)
{
    //Loops through all entities
    for(int i = 0; i < objectVector.size(); ++i)
    {
        //Loops through entities ID's
        for(int r = 0; r < objectVector.at(i)->getID().size(); r++ )
        {
            //Handles Entities with playerMovement ID
            if( objectVector.at(i)->getID().at(r) == "playerMovement")
            {
                PlayerMovement(*objectVector.at(i));

            }
            if( objectVector.at(i)->getID().at(r) == "gravity")
            {
                gravity(*objectVector.at(i));
            }
            if(objectVector.at(i)->getID().at(r) == "moves")
            {
                collide(*objectVector.at(i));
            }
        }
    }
    Cleanup();
}
void GameState::gravity(GameObject& entity)
{
}

//Moves the player based on keyboard input
void GameState::PlayerMovement(GameObject& player)
{
}

void GameState::PlayerEvents(Entity& player, sf::Event& event)
{
  
}

void GameState::draw(sf::RenderWindow & window)
{

    window.setView(camera);
    //Loops through all entities
    for(int i = 0; i < objectVector.size(); i++)
    {
		for (int r = 0; r < objectVector.at(i).size(); r++)
		{
			window.draw(objectVector.at(i).at(r)->render());
		}
    }
}

void GameState::Cleanup()
{
    for(int i = 0; i < killList.size(); i++)
    {
        for(int x = 0; x < objectVector.size(); x++)
        {
            if(objectVector.at(x) == killList.at(i))
				objectVector.erase(objectVector.begin() + x);
        }
    }
}

void GameState::collide(Entity& entity)
{
    int meme;
    entity.grounded = false;
    sf::FloatRect box1 = entity.getBoundingBox();
    sf::FloatRect oldBox1 = entity.getBoundingBox("old");
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); i++)
    {
        if(entityVector.at(i) == &entity)
            continue;
        sf::FloatRect box2 = entityVector.at(i)->getBoundingBox();
        if(box1.intersects(box2))
        {
            if(entity.hasID("playerMovement") && entityVector.at(i)->hasID("enemy") && entity.invincibility())
            {
                entity.damaged(entityVector.at(i)->fromRight());
            }
            if(entityVector.at(i)->hasID("pickup") && entity.hasID("playerMovement"))
            {
                entity.pickup(entityVector.at(i)->getType());
                killList.push_back(entityVector.at(i));
            }
            if(entity.hasID("projectile") && entityVector.at(i)->hasID("enemy"))
            {
                killList.push_back(entityVector.at(i));
                killList.push_back(&entity);
            }
            else if(entity.hasID("playerMovement") && entityVector.at(i)->hasID("ladder") && !entity.dead())
            {
                entity.onLadder = true;
            }
            else if(entityVector.at(i)->hasID("tile"))
            {
                float box1_bottom = box1.top + box1.height;
                float OldBox1_bottom = oldBox1.top + oldBox1.height;
                float box2_bottom = box2.top + box2.height;
                float box1_right = box1.left + box1.width;
                float OldBox1_right = oldBox1.left + oldBox1.width;
                float box2_right = box2.left + box2.width;

                float left_collision = box1_right - box2.left;
                float right_collision = box2_right - box1.left;
                float top_collision = box1_bottom - box2.top;
                float bot_collision = box2_bottom - box1.top;

                //box1 right colliding with box2 left
                if (OldBox1_right <= box2.left
                    && box1_right > box2.left)
                    entity.moveEntity(-left_collision,0);

                //box1 left colliding with box2 right
                else if (oldBox1.left >= box2_right
                         && box1.left < box2_right)
                    entity.moveEntity(right_collision,0);


                //box1 bottom colliding with box2 top
                else if (OldBox1_bottom <= box2.top
                         && box1_bottom > box2.top)
                {
                    entity.moveEntity(0, -top_collision);
                    entity.grounded = true;
                }

                //box1 top colliding with box2 bottom
                else if (oldBox1.top <= box2_bottom
                         && box1_bottom > box2_bottom && !entityVector.at(i)->hasID("zombie"))
                    entity.moveEntity(0, bot_collision);
            }

        }
    }
}


