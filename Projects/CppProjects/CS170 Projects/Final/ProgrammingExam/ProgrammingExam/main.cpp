#include <iostream>
#include "ObjectManager.h"
#include "GameObject.h"
#include "Hero.h"
#include "Enemy.h"
#include "Point.h"

void Test1(void)
{
    Hero h1("Hero1", Point(1, 1), 3);
    h1.IncrementItem(0);
    h1.IncrementItem(2);
    h1.IncrementItem(2);

    Hero h2(h1);
    h2.SetName("Hero2");
    h2.SetCenter(2, 2);
    h2.IncrementItem(1);

    Hero h3("Hero3", Point(3, 5), 2);
    h3 = h2;
    h3.SetName("Hero3");


    Enemy e1("Enemy1", Point(2, 2));
    Enemy e2(e1);

    e2.SetName("Enemy2");


    GameObject *objects[5] = { &h1, &h2, &h3, &e1, &e2 };
    for (int i = 0; i < 5; ++i)
    {
        objects[i]->Update();
        objects[i]->Display();
    }
}

void Test2(void)
{
    GameObject *objects[2];
    objects[0] = new Hero("Hero1", Point(1, 1), 4);
    objects[1] = new Enemy("Enemy", Point(1, 1));

    objects[0]->SetName("Hero");
    objects[1]->SetCenter(2, 2);

    for (int i = 0; i < 2; ++i)
    {
        objects[i]->Update();
        objects[i]->Display();
    }

    for (int i = 0; i < 2; ++i)
    {
        delete objects[i];
    }
}

void Test3(void)
{
    ObjectManager om;

    Hero *h1 = new Hero("Hero1", Point(1, 1), 3);
    h1->IncrementItem(0);
    h1->IncrementItem(2);
    h1->IncrementItem(2);
    om.AddObject(h1);

    GameObject *e1 = new Enemy("Enemy1", Point(2, 2));
    om.AddObject(e1);

    Hero *h2 = new Hero(*h1);
    om.AddObject(h2);

    GameObject * h3 = new Hero("Hero1", Point(3, 3), 5);
    om.AddObject(h3);

    GameObject *e2 = new Enemy("Enemy2", Point(3, 4));
    om.AddObject(e2);

    std::cout << "Updating the ObjectManager for the 1st time" << std::endl;
    std::cout << "********************************************" << std::endl;
    om.Update();

    std::cout << std::endl;
    std::cout << "Displaying the ObjectManager for the 1st time" << std::endl;
    std::cout << "**********************************************" << std::endl;
    om.Display();

    om.RemoveObjectByName("Enemy1");
    om.RemoveObjectByName("Hero1");

    std::cout << std::endl;
    std::cout << "Displaying the ObjectManager for the 2nd time" << std::endl;
    std::cout << "**********************************************" << std::endl;
    om.Display();

    om.RemoveAllObjectsByName("Hero1");

    std::cout << std::endl;
    std::cout << "Displaying the ObjectManager for the 3rd time" << std::endl;
    std::cout << "**********************************************" << std::endl;
    om.Display();

    std::cout << std::endl;
    std::cout << "Clearing the ObjectManager " << std::endl;
    std::cout << "***************************" << std::endl;
    om.Clear();

    std::cout << std::endl;
    std::cout << "Displaying the ObjectManager for the 4th time" << std::endl;
    std::cout << "**********************************************" << std::endl;
    om.Display();

    Hero *h4 = new Hero("Hero4", Point(1, 1), 3);
    om.AddObject(h4);

    GameObject *e3 = new Enemy("Enemy3", Point(2, 2));
    om.AddObject(e3);
}

int main(void)
{
    Test1();
    Test2();
    Test3();

    system("pause");
    return 0;
}