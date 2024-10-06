using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Qbit;

namespace Sandbox
{
    class Player : Entity
    {
        Rigidbody2DComponent rb;
        public void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");

            rb = GetComponent<Rigidbody2DComponent>();

        }
        public void OnUpdate(float ts)
        {
            float speed = 1.0f;
            Vector3 velocity = Vector3.Zero;
            if (Input.IsKeyDown(KeyCode.W))
                velocity.Y = 1.0f;
            else if (Input.IsKeyDown(KeyCode.S))
                velocity.Y = -1.0f;

            if (Input.IsKeyDown(KeyCode.A))
                velocity.X = -1.0f;
            else if (Input.IsKeyDown(KeyCode.D))
                velocity.X = 1.0f;

            rb.ApplyLinearImpulse(velocity.XY * ts, false);

            //Vector3 translation = Translation;
            //translation += velocity * speed *ts;
            //this.Translation = translation;
        }
    }
}
