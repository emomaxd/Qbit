using System;
using Qbit;

namespace q
{
    class T: Entity
{
        public void OnCreate()
        {
            Console.WriteLine("OnCreate runs once when the game has started!");
        }

        public void OnUpdate(float ts)
        {
            Console.WriteLine("OnUpdate runs in each frame.");
    }
    }
}
