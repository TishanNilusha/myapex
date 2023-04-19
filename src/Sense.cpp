#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"

class Sense
{
private:
    ConfigLoader *m_configLoader;
    Level *m_level;
    LocalPlayer *m_localPlayer;
    std::vector<Player *> *m_players;
    X11Utils *m_x11Utils;

public:
    Sense(ConfigLoader *configLoader,
          Level *level,
          LocalPlayer *localPlayer,
          std::vector<Player *> *players,
          X11Utils *x11Utils)
    {
        m_configLoader = configLoader;
        m_level = level;
        m_localPlayer = localPlayer;
        m_players = players;
        m_x11Utils = x11Utils;
    }
    void update()
    {
        if (!m_level->isPlayable()) return;
        for (int i = 0; i < m_players->size(); i++)
        {
            Player *player = m_players->at(i);
            if (!player->isValid())
                continue;
            if ((player->getTeamNumber() == m_localPlayer->getTeamNumber()) && !m_level->isTrainingArea())
		
		 continue;
		if (player->isVisible())
            {
                player->setGlowEnable(1);
                player->setGlowThroughWall(1);
                player->setGlowColorRed(0);
                player->setGlowColorGreen(3);
                player->setGlowColorBlue(0);

            }
            else
            {

                const int enemyShields = player->getShieldsValue();
                const int enemyHealth = player->getHealthValue();
		double r, g, b;

		if(player->isKnocked()) {
			r = 3, g = 0, b = 0; 
		}
	 	else if (enemyShields >= 120)
                {
                    r = 3;
                    g = 0;
                    b = 0;
                }
                else if (enemyShields >= 100)
                {
                    r = 1.5;
                    g = 0;
                    b = 1.5;
                }
                else if (enemyShields >= 75)
                {
                    r = 0;
                    g = 1;
                    b = 2;
                }
                else if (enemyShields >= 1)
                {
                    r = 1;
                    g = 1;
                    b = 1;
                }
		else 
		{
		    r = 3 - (enemyHealth*0.03);
		    b = 0;
		    g = enemyHealth*0.03;
		}

                player->setGlowEnable(1);
                player->setGlowThroughWall(1);
                player->setGlowColorRed(r);
                player->setGlowColorGreen(g);
                player->setGlowColorBlue(b);
            }
        }
    }

};
