#pragma once
#include "qvector.h"
#include "Team.h"
#include "NewDistance.h"

class Map
{
private:
    QVector<Team> map;

public:

    Map()
    {
    }

    int size()
    {
        return map.size();
    }

    bool empty()
    {
        return map.empty();
    }

    QVector<Team>::iterator find(QString key)
    {
        QVector<Team>::iterator searchIt = map.begin();

        bool found = false;

        while (searchIt != map.end() && !found)
        {
            if (searchIt->getTeamName() == key)
            {
                found = true;
            }
            else
            {
                searchIt++;
            }
        }

        return searchIt;
    }

    QVector<Team>::iterator insert(QString key, Team value)
    {

        QVector<Team>::iterator foundIt = find(key);

        if (foundIt == map.end())
        {
            map.push_back(value);

            foundIt--;
        }
        else
        {
            *foundIt = value;
        }

        return foundIt;
    }


    Team operator[](const int index)
    {
        return map.at(index);
    }


    QVector<Team>::iterator begin()
    {
        return map.begin();
    }


    QVector<Team>::iterator end()
    {
        return map.end();
    }


};
